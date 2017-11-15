/*
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Console handler implementation of shell.h API
 */


#include <zephyr.h>
#include <stdio.h>
#include <string.h>

#include <console/console.h>
#include <misc/printk.h>
#include <misc/util.h>

#ifdef CONFIG_UART_CONSOLE
#include <console/uart_console.h>
#endif
#ifdef CONFIG_TELNET_CONSOLE
#include <console/telnet_console.h>
#endif

#include <shell/shell.h>

#define ARGC_MAX 10
#define COMMAND_MAX_LEN 50
#define MODULE_NAME_MAX_LEN 20
/* additional chars are " >" (include '\0' )*/
#define PROMPT_SUFFIX 3
#define PROMPT_MAX_LEN (MODULE_NAME_MAX_LEN + PROMPT_SUFFIX)

/* command table is located in the dedicated memory segment (.shell_) */
extern struct shell_module __shell_cmd_start[];
extern struct shell_module __shell_cmd_end[];
#define NUM_OF_SHELL_ENTITIES (__shell_cmd_end - __shell_cmd_start)

static const char *prompt;
static char default_module_prompt[PROMPT_MAX_LEN];
static int default_module = -1;

#define STACKSIZE CONFIG_CONSOLE_SHELL_STACKSIZE
static K_THREAD_STACK_DEFINE(stack, STACKSIZE);
static struct k_thread shell_thread;

#define MAX_CMD_QUEUED CONFIG_CONSOLE_SHELL_MAX_CMD_QUEUED
static struct console_input buf[MAX_CMD_QUEUED];

static struct k_fifo avail_queue;
static struct k_fifo cmds_queue;

static shell_cmd_function_t app_cmd_handler;
static shell_prompt_function_t app_prompt_handler;

static const char *get_prompt(void)
{
	if (app_prompt_handler) {
		const char *str;

		str = app_prompt_handler();
		if (str) {
			return str;
		}
	}

	if (default_module != -1) {
		if (__shell_cmd_start[default_module].prompt) {
			const char *ret;

			ret = __shell_cmd_start[default_module].prompt();
			if (ret) {
				return ret;
			}
		}

		return default_module_prompt;
	}

	return prompt;
}

static void line_queue_init(void)
{
	int i;

	for (i = 0; i < MAX_CMD_QUEUED; i++) {
		k_fifo_put(&avail_queue, &buf[i]);
	}
}

static size_t line2argv(char *str, char *argv[], size_t size)
{
	size_t argc = 0;

	if (!strlen(str)) {
		return 0;
	}

	while (*str && *str == ' ') {
		str++;
	}

	if (!*str) {
		return 0;
	}

	argv[argc++] = str;

	while ((str = strchr(str, ' '))) {
		*str++ = '\0';

		while (*str && *str == ' ') {
			str++;
		}

		if (!*str) {
			break;
		}

		argv[argc++] = str;

		if (argc == size) {
			printk("Too many parameters (max %zu)\n", size - 1);
			return 0;
		}
	}

	/* keep it POSIX style where argv[argc] is required to be NULL */
	argv[argc] = NULL;

	return argc;
}

static int get_destination_module(const char *module_str)
{
	int i;

	for (i = 0; i < NUM_OF_SHELL_ENTITIES; i++) {
		if (!strncmp(module_str,
			     __shell_cmd_start[i].module_name,
			     MODULE_NAME_MAX_LEN)) {
			return i;
		}
	}

	return -1;
}

static int show_cmd_help(const struct shell_cmd *cmd, bool full)
{
	printk("Usage: %s %s\n", cmd->cmd_name, cmd->help ? cmd->help : "");

	if (full && cmd->desc) {
		printk("%s\n", cmd->desc);
	}

	return 0;
}

static void print_module_commands(const int module)
{
	const struct shell_module *shell_module = &__shell_cmd_start[module];
	int i;

	printk("help\n");

	for (i = 0; shell_module->commands[i].cmd_name; i++) {
		printk("%-28s %s\n",
		       shell_module->commands[i].cmd_name,
		       shell_module->commands[i].help ?
		       shell_module->commands[i].help : "");
	}
}

static const struct shell_cmd *get_cmd(const struct shell_cmd cmds[],
				       const char *cmd_str)
{
	int i;

	for (i = 0; cmds[i].cmd_name; i++) {
		if (!strcmp(cmd_str, cmds[i].cmd_name)) {
			return &cmds[i];
		}
	}

	return NULL;
}

static const struct shell_cmd *get_mod_cmd(int module, const char *cmd_str)
{
	return get_cmd(__shell_cmd_start[module].commands, cmd_str);
}

static int cmd_help(int argc, char *argv[])
{
	int module = default_module;

	/* help per command */
	if (argc > 1) {
		const struct shell_cmd *cmd;
		const char *cmd_str;

		module = get_destination_module(argv[1]);
		if (module != -1) {
			if (argc == 2) {
				goto module_help;
			}

			cmd_str = argv[2];
		} else if (argc > 2) {
			cmd_str = argv[1];
		} else {
			printk("Unknown module or command\n");
			return -EINVAL;
		}

		if (module == -1) {
			printk("No help found for '%s'\n", cmd_str);
			return -EINVAL;
		}

		cmd = get_mod_cmd(module, cmd_str);
		if (cmd) {
			return show_cmd_help(cmd, true);
		} else {
			printk("Unknown command '%s'\n", cmd_str);
			return -EINVAL;
		}
	}

module_help:
	/* help per module */
	if (module != -1) {
		print_module_commands(module);
		printk("\nEnter 'exit' to leave current module.\n");
	} else { /* help for all entities */
		printk("Available modules:\n");
		for (module = 0; module < NUM_OF_SHELL_ENTITIES; module++) {
			printk("%s\n", __shell_cmd_start[module].module_name);
		}
		printk("\nTo select a module, enter 'select <module name>'.\n");
	}

	return 0;
}

static int set_default_module(const char *name)
{
	int module;

	if (strlen(name) > MODULE_NAME_MAX_LEN) {
		printk("Module name %s is too long, default is not changed\n",
			name);
		return -EINVAL;
	}

	module = get_destination_module(name);

	if (module == -1) {
		printk("Illegal module %s, default is not changed\n", name);
		return -EINVAL;
	}

	default_module = module;

	strncpy(default_module_prompt, name, MODULE_NAME_MAX_LEN);
	strcat(default_module_prompt, "> ");

	return 0;
}

static int cmd_select(int argc, char *argv[])
{
	if (argc == 1) {
		default_module = -1;
		return 0;
	}

	return set_default_module(argv[1]);
}

static int cmd_exit(int argc, char *argv[])
{
	if (argc == 1) {
		default_module = -1;
	}

	return 0;
}

static const struct shell_cmd *get_internal(const char *command)
{
	static const struct shell_cmd internal_commands[] = {
		{ "help", cmd_help, "[command]" },
		{ "select", cmd_select, "[module]" },
		{ "exit", cmd_exit, NULL },
		{ NULL },
	};

	return get_cmd(internal_commands, command);
}

int shell_exec(char *line)
{
	char *argv[ARGC_MAX + 1], **argv_start = argv;
	const struct shell_cmd *cmd;
	int argc, err;

	argc = line2argv(line, argv, ARRAY_SIZE(argv));
	if (!argc) {
		return -EINVAL;
	}

	cmd = get_internal(argv[0]);
	if (cmd) {
		goto done;
	}

	if (argc == 1 && default_module == -1) {
		printk("No module selected. Use 'select' or 'help'.\n");
		return -EINVAL;
	}

	if (default_module != -1) {
		cmd = get_mod_cmd(default_module, argv[0]);
	}

	if (!cmd && argc > 1) {
		int module;

		module = get_destination_module(argv[0]);
		if (module != -1) {
			cmd = get_mod_cmd(module, argv[1]);
			if (cmd) {
				argc--;
				argv_start++;
			}
		}
	}

	if (!cmd) {
		if (app_cmd_handler) {
			return app_cmd_handler(argc, argv);
		}

		printk("Unrecognized command: %s\n", argv[0]);
		printk("Type 'help' for list of available commands\n");
		return -EINVAL;
	}

done:
	err = cmd->cb(argc, argv_start);
	if (err < 0) {
		show_cmd_help(cmd, false);
	}

	return err;
}

static void shell(void *p1, void *p2, void *p3)
{
	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	while (1) {
		struct console_input *cmd;

		printk("%s", get_prompt());

		cmd = k_fifo_get(&cmds_queue, K_FOREVER);

		shell_exec(cmd->line);

		k_fifo_put(&avail_queue, cmd);
	}
}

static int get_command_to_complete(char *str, char **command_prefix)
{
	char dest_str[MODULE_NAME_MAX_LEN];
	int dest = -1;
	char *start;

	/* remove ' ' at the beginning of the line */
	while (*str && *str == ' ') {
		str++;
	}

	if (!*str) {
		return -1;
	}

	start = str;

	if (default_module != -1) {
		dest = default_module;
		/* caller function already checks str len and put '\0' */
		*command_prefix = str;
	}

	/*
	 * In case of a default module: only one parameter is possible.
	 * Otherwise, only two parameters are possibles.
	 */
	str = strchr(str, ' ');
	if (default_module != -1) {
		return (str == NULL) ? dest : -1;
	}

	if (str == NULL) {
		return -1;
	}

	if ((str - start + 1) >= MODULE_NAME_MAX_LEN) {
		return -1;
	}

	strncpy(dest_str, start, (str - start + 1));
	dest_str[str - start] = '\0';
	dest = get_destination_module(dest_str);
	if (dest == -1) {
		return -1;
	}

	str++;

	/* caller func has already checked str len and put '\0' at the end */
	*command_prefix = str;
	str = strchr(str, ' ');

	/* only two parameters are possibles in case of no default module */
	return (str == NULL) ? dest : -1;
}

static u8_t completion(char *line, u8_t len)
{
	const char *first_match = NULL;
	int common_chars = -1, space = 0;
	int i, dest, command_len;
	const struct shell_module *module;
	char *command_prefix;

	if (len >= (MODULE_NAME_MAX_LEN + COMMAND_MAX_LEN - 1)) {
		return 0;
	}

	/*
	 * line to completion is not ended by '\0' as the line that gets from
	 * k_fifo_get function
	 */
	line[len] = '\0';
	dest = get_command_to_complete(line, &command_prefix);
	if (dest == -1) {
		return 0;
	}

	command_len = strlen(command_prefix);

	module = &__shell_cmd_start[dest];

	for (i = 0; module->commands[i].cmd_name; i++) {
		int j;

		if (strncmp(command_prefix,
			module->commands[i].cmd_name, command_len)) {
			continue;
		}

		if (!first_match) {
			first_match = module->commands[i].cmd_name;
			continue;
		}

		/* more commands match, print first match */
		if (first_match && (common_chars < 0)) {
			printk("\n%s\n", first_match);
			common_chars = strlen(first_match);
		}

		/* cut common part of matching names */
		for (j = 0; j < common_chars; j++) {
			if (first_match[j] != module->commands[i].cmd_name[j]) {
				break;
			}
		}

		common_chars = j;

		printk("%s\n", module->commands[i].cmd_name);
	}

	/* no match, do nothing */
	if (!first_match) {
		return 0;
	}

	if (common_chars >= 0) {
		/* multiple match, restore prompt */
		printk("%s", get_prompt());
		printk("%s", line);
	} else {
		common_chars = strlen(first_match);
		space = 1;
	}

	/* complete common part */
	for (i = command_len; i < common_chars; i++) {
		printk("%c", first_match[i]);
		line[len++] = first_match[i];
	}

	/* for convenience add space after command */
	if (space) {
		printk(" ");
		line[len] = ' ';
	}

	return common_chars - command_len + space;
}


void shell_init(const char *str)
{
	k_fifo_init(&cmds_queue);
	k_fifo_init(&avail_queue);

	line_queue_init();

	prompt = str ? str : "";

	k_thread_create(&shell_thread, stack, STACKSIZE, shell, NULL, NULL,
			NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);

	/* Register serial console handler */
#ifdef CONFIG_UART_CONSOLE
	uart_register_input(&avail_queue, &cmds_queue, completion);
#endif
#ifdef CONFIG_TELNET_CONSOLE
	telnet_register_input(&avail_queue, &cmds_queue, completion);
#endif
}

/** @brief Optionally register an app default cmd handler.
 *
 *  @param handler To be called if no cmd found in cmds registered with
 *  shell_init.
 */
void shell_register_app_cmd_handler(shell_cmd_function_t handler)
{
	app_cmd_handler = handler;
}

void shell_register_prompt_handler(shell_prompt_function_t handler)
{
	app_prompt_handler = handler;
}

void shell_register_default_module(const char *name)
{
	int result = set_default_module(name);

	if (result != -1) {
		printk("\n%s", default_module_prompt);
	}
}
