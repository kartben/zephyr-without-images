/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @brief Generate static IDT and a bitmap of allocated interrupt vectors.
 * Creates a static IA-32 Interrupt Descriptor Table (IDT).
 *
 * This program expects to be invoked as follows:
 *  gen_idt -i <input file> -o <IDT output file> -n <# of interrupt vectors>
 *          -b <allocated vectors bitmap file>
 * All parameters are required.
 *
 * The <input file> is assumed to be a binary file containing the intList
 * section from the Zephyr Kernel ELF image.
 *
 * <number of interrupt vectors> is the same as CONFIG_IDT_NUM_VECTORS.
 *
 * It is expected that this program is invoked from within the build system
 * during the link stage.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "version.h"

/* Define __packed for the idtEntry structure defined in idtEnt.h */
#define __packed __attribute__((__packed__))

/* These come from the shared directory */
#include "segselect.h"
#include "idtEnt.h"

/* Define the following macro to see a verbose or debug output from the tool */
/* #define DEBUG_GENIDT */

#ifdef DEBUG_GENIDT
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) do {} while (0)
#endif

#if !defined(WINDOWS)
	#define O_BINARY 0
#endif

#define MAX_NUM_VECTORS           256
#define MAX_PRIORITIES            16
#define MAX_VECTORS_PER_PRIORITY  16
#define MAX_IRQS                  256

#define UNSPECIFIED_INT_VECTOR    ((unsigned int) -1)
#define UNSPECIFIED_PRIORITY      ((unsigned int) -1)
#define UNSPECIFIED_IRQ           ((unsigned int) -1)

static void get_exec_name(char *pathname);
static void usage(int len);
static void get_options(int argc, char *argv[]);
static void open_files(void);
static void read_input_file(void);
static void close_files(void);
static void validate_input_file(void);
static void generate_idt(void);
static void generate_interrupt_vector_bitmap(void);
static void clean_exit(int exit_code);

struct genidt_header_s {
	void *spurious_addr;
	void *spurious_no_error_addr;
	unsigned int num_entries;
};

struct genidt_entry_s {
	void *isr;
	unsigned int irq;
	unsigned int priority;
	unsigned int vector_id;
	unsigned int dpl;
};

static struct genidt_header_s  genidt_header;
static struct genidt_entry_s   supplied_entry[MAX_NUM_VECTORS];
static struct genidt_entry_s   generated_entry[MAX_NUM_VECTORS];

enum {
	IFILE = 0,             /* input file */
	OFILE,                 /* output file */
	BFILE,                 /* allocated interrupt vector bitmap file */
	NUSERFILES,            /* number of user-provided file names */
	EXECFILE = NUSERFILES, /* for name of executable */
	NFILES                 /* total number of file names */
};
enum { SHORT_USAGE, LONG_USAGE };

static int fds[NUSERFILES] = {-1, -1};
static char *filenames[NFILES];
static unsigned int num_vectors = (unsigned int)-1;
static struct version version = {KERNEL_VERSION, 1, 1, 5};

int main(int argc, char *argv[])
{
	get_exec_name(argv[0]);
	get_options(argc, argv); /* may exit */
	open_files();            /* may exit */
	read_input_file();       /* may exit */
	validate_input_file();   /* may exit */
	generate_idt();          /* may exit */
	generate_interrupt_vector_bitmap();
	close_files();
	return 0;
}

static void get_options(int argc, char *argv[])
{
	char *endptr;
	int ii, opt;

	while ((opt = getopt(argc, argv, "hb:i:o:n:v")) != -1) {
		switch (opt) {
		case 'b':
			filenames[BFILE] = optarg;
			break;
		case 'i':
			filenames[IFILE] = optarg;
			break;
		case 'o':
			{
			filenames[OFILE] = optarg;
			break;
			}
		case 'h':
			usage(LONG_USAGE);
			exit(0);
		case 'n':
			num_vectors = (unsigned int) strtoul(optarg, &endptr, 10);
			if ((*optarg == '\0') || (*endptr != '\0')) {
				usage(SHORT_USAGE);
				exit(-1);
				}
			break;
		case 'v':
			show_version(filenames[EXECFILE], &version);
			exit(0);
		default:
			usage(SHORT_USAGE);
			exit(-1);
	    }
	}

	if (num_vectors > MAX_NUM_VECTORS) {
		usage(SHORT_USAGE);
		exit(-1);
	}

	for (ii = IFILE; ii < NUSERFILES; ii++) {
		if (!filenames[ii]) {
			usage(SHORT_USAGE);
			exit(-1);
		}
	}
}

static void get_exec_name(char *pathname)
{
	int end = strlen(pathname) - 1;

	while (end != -1) {
		#if defined(WINDOWS) /* Might have both slashes in path */
		if ((pathname[end] == '/') || (pathname[end] == '\\'))
		#else
		if (pathname[end] == '/')
		#endif
		{
			if ((0 == end) || (pathname[end - 1] != '\\')) {
				++end;
				break;
			}
		}
		--end;
	}
	filenames[EXECFILE] = &pathname[end];
}

static void open_files(void)
{
	int ii;

	fds[IFILE] = open(filenames[IFILE], O_RDONLY | O_BINARY);
	fds[OFILE] = open(filenames[OFILE], O_WRONLY | O_BINARY |
						O_TRUNC | O_CREAT,
						S_IWUSR | S_IRUSR);
	fds[BFILE] = open(filenames[BFILE], O_WRONLY | O_BINARY | O_CREAT |
						O_TRUNC | O_BINARY,
						S_IWUSR | S_IRUSR);

	for (ii = 0; ii < NUSERFILES; ii++) {
		int invalid = fds[ii] == -1;

		if (invalid) {
			char *invalid = filenames[ii];

			fprintf(stderr, "invalid file %s\n", invalid);
			for (--ii; ii >= 0; ii--) {
				close(fds[ii]);
			}
			exit(-1);
		}
	}
}

static void show_entry(struct genidt_entry_s *entry)
{
	fprintf(stderr,
			"ISR Address: %p\n"
			"IRQ: %d\n"
			"Priority: %d\n"
			"Vector ID: %d\n"
			"DPL: %d\n"
			"---------------\n",
			entry->isr, entry->irq, entry->priority,
			entry->vector_id, entry->dpl);
}

static void read_input_file(void)
{
	ssize_t  bytes_read;
	size_t   bytes_to_read;

	/* Read the header information. */
	bytes_read = read(fds[IFILE], &genidt_header, sizeof(genidt_header));
	if (bytes_read != sizeof(genidt_header)) {
		goto read_error;
	}

	PRINTF("Spurious interrupt handlers found at %p and %p.\n",
		    genidt_header.spurious_addr, genidt_header.spurious_no_error_addr);
	PRINTF("There are %d ISR(s).\n", genidt_header.num_entries);


	if (genidt_header.num_entries > num_vectors) {
		fprintf(stderr,
				"Too many ISRs found. Got %u. Expected no more than %u.\n"
				"Malformed input file?\n",
				genidt_header.num_entries, num_vectors);
		clean_exit(-1);
	}

	bytes_to_read = sizeof(struct genidt_entry_s) * genidt_header.num_entries;
	bytes_read = read(fds[IFILE], supplied_entry, bytes_to_read);
	if (bytes_read != bytes_to_read) {
		goto read_error;
	}

#ifdef DEBUG_GENIDT
	int i;

	for (i = 0; i < genidt_header.num_entries; i++) {
		show_entry(&supplied_entry[i]);
		fprintf(stderr, "----------------------------\n");
	}
#endif
	return;

read_error:
	fprintf(stderr, "Error occurred while reading input file. Aborting...\n");
	clean_exit(-1);
}

static void validate_dpl(void)
{
	int  i;

	for (i = 0; i < genidt_header.num_entries; i++) {
		if (supplied_entry[i].dpl != 0) {
			fprintf(stderr,
					"Invalid DPL bits specified.  Must be zero.\n");
			show_entry(&supplied_entry[i]);
			clean_exit(-1);
		}
	}
}

static void validate_vector_id(void)
{
	int  i;
	int  vectors[MAX_NUM_VECTORS] = {0};

	/*
	 * NOTE: Future versions of the gen_idt tool may generate the vector ID
	 * instead of relying upon values already existing in the input file.
	 */

	for (i = 0; i < genidt_header.num_entries; i++) {
		if (supplied_entry[i].vector_id >= num_vectors) {
			fprintf(stderr,
					"Vector ID exceeds specified # of vectors (%d).\n",
					num_vectors);
			show_entry(&supplied_entry[i]);
			clean_exit(-1);
		}

		if (vectors[supplied_entry[i].vector_id] != 0) {
			fprintf(stderr, "Duplicate vector ID found.\n");
			show_entry(&supplied_entry[i]);
			clean_exit(-1);
		}
	vectors[supplied_entry[i].vector_id]++;
	}
}

static void validate_priority(void)
{
	int  i;
	int  num_priorities[MAX_PRIORITIES] = {0};
	unsigned expected_priority;

	/*
	 * Validate the priority.
	 *
	 * As the current implementation of the gen_idt tool takes the vector ID
	 * from the input file, the priority is ignored. In fact, the priority
	 * is overridden to match <vector ID> / MAX_VECTORS_PER_PRIORITY.
	 */

	for (i = 0; i < genidt_header.num_entries; i++) {
		if (supplied_entry[i].irq == UNSPECIFIED_IRQ) {
			/*
			 * This is a software interrupt.
			 * The priority is currently ignored.
			 */
			continue;
		}

		if (supplied_entry[i].priority >= MAX_PRIORITIES) {
			fprintf(stderr, "Priority must not exceed %d.\n",
					MAX_PRIORITIES - 1);
			show_entry(&supplied_entry[i]);
			clean_exit(-1);
		}

		expected_priority = supplied_entry[i].vector_id /
							MAX_VECTORS_PER_PRIORITY;
		if (expected_priority != supplied_entry[i].priority) {
			supplied_entry[i].priority = expected_priority;
			fprintf(stderr,
					"Warning! Overriding IRQ %d priority to %d!\n",
					supplied_entry[i].irq, supplied_entry[i].priority);
		}

		num_priorities[supplied_entry[i].priority]++;
	}

	for (i = 0; i < MAX_PRIORITIES; i++) {
		if (num_priorities[i] > MAX_VECTORS_PER_PRIORITY) {
			fprintf(stderr, "Too many entries for priority level %d", i);
			clean_exit(-1);
		}
	}
}

static void validate_irq(void)
{
	int  i;
	int  num_irqs[MAX_IRQS] = {0};

	/* Validate the IRQ number */
	for (i = 0; i < genidt_header.num_entries; i++) {
		if (supplied_entry[i].irq == UNSPECIFIED_IRQ) {
			/* This is a request for a software interrupt */
			continue;
		}

		if (supplied_entry[i].irq >= MAX_IRQS) {
			/*
			 * If code to support the PIC is re-introduced, then this
			 * check will need to be updated.
			 */
			fprintf(stderr, "IRQ must be between 0 and %d inclusive.\n",
					MAX_IRQS - 1);
			show_entry(&supplied_entry[i]);
			clean_exit(-1);
		}
		num_irqs[i]++;
	}

	for (i = 0; i < MAX_IRQS; i++) {
		if (num_irqs[i] > 1) {
			fprintf(stderr, "Multiple requests for IRQ %d detected.\n", i);
			clean_exit(-1);
		}
	}
}

static void validate_input_file(void)
{
	validate_dpl();          /* exits on error */
	validate_vector_id();    /* exits on error */
	validate_priority();     /* exits on error */
	validate_irq();          /* exits on error */
}

static void generate_idt(void)
{
	unsigned int  i;
	unsigned int  vector_id;

	/*
	 * Initialize the generated entries with default
	 * spurious interrupt handlers.
	 */

	for (i = 0; i < num_vectors; i++) {
		if ((((1 << i) & _EXC_ERROR_CODE_FAULTS)) && (i < 32)) {
			generated_entry[i].isr = genidt_header.spurious_addr;
		} else {
			generated_entry[i].isr = genidt_header.spurious_no_error_addr;
		}
		/* Initialize the [irq] and [priority] fields to aid in debugging.  */
		generated_entry[i].irq = UNSPECIFIED_IRQ;
		generated_entry[i].priority = UNSPECIFIED_PRIORITY;
		generated_entry[i].vector_id = i;
		generated_entry[i].dpl = 0;
	}

	/*
	 * Overwrite the generated entries as appropriate with the
	 * validated supplied entries.
	 */

	for (i = 0; i < genidt_header.num_entries; i++) {
		vector_id = supplied_entry[i].vector_id;
		generated_entry[vector_id] = supplied_entry[i];
	}

    /*
     * We now have the address of all ISR stub/functions captured in
     * generated_entry[]. Now construct the actual IDT.
     */

	for (i = 0; i < num_vectors; i++) {
		unsigned long long idt_entry;
		ssize_t bytes_written;

		 _IdtEntCreate(&idt_entry, generated_entry[i].isr,
						generated_entry[i].dpl);

		bytes_written = write(fds[OFILE], &idt_entry, sizeof(idt_entry));
		if (bytes_written != sizeof(idt_entry)) {
			fprintf(stderr, "Failed to write IDT entry %u.\n", num_vectors);
			clean_exit(-1);
		}
	}

	return;
}

static void generate_interrupt_vector_bitmap(void)
{
	int i;
	unsigned int num_elements = (num_vectors + 31) / 32;
	unsigned int interrupt_vector_bitmap[num_elements];
	unsigned int index;
	unsigned int bit;
	size_t bytes_to_write;
	ssize_t bytes_written;

	/* Initially mark each interrupt vector as available */
	for (i = 0; i < num_elements; i++) {
		interrupt_vector_bitmap[i] = 0xffffffff;
	}

	/* Loop through each supplied entry and mark its vector as allocated. */
	for (i = 0; i < genidt_header.num_entries; i++) {
		index = supplied_entry[i].vector_id / 32;
		bit = supplied_entry[i].vector_id & 31;

		interrupt_vector_bitmap[index] &= ~(1 << bit);
	}

	/* Ensure that any leftover entries are marked as allocated too. */
	for (i = num_vectors; i < num_elements * 32; i++) {
		index = i / 32;
		bit = i & 0x1f;

		interrupt_vector_bitmap[index] &= ~(1 << bit);
	}

	bytes_to_write = num_elements * sizeof(unsigned int);
	bytes_written = write(fds[BFILE], interrupt_vector_bitmap,
						bytes_to_write);
	if (bytes_written != bytes_to_write) {
		fprintf(stderr, "Failed to write all data to '%s'.\n",
				filenames[BFILE]);
		clean_exit(-1);
	}
}

static void close_files(void)
{
	int ii;

	for (ii = 0; ii < NUSERFILES; ii++) {
		close(fds[ii]);
	}
}

static void clean_exit(int exit_code)
{
	close_files();
	exit(exit_code);
}

static void usage(int len)
{
	fprintf(stderr, "\n%s -i <input file> -n <n>\n", filenames[EXECFILE]);

	if (len == SHORT_USAGE) {
		return;
	}

	fprintf(stderr,
	    "\n"
	    " options\n"
	    "\n"
	    "    -b <allocated interrupt vector bitmap output file>\n\n"
	    "        [Mandatory] The interrupt vector bitmap output file.\n\n"
	    "    -i <binary file>\n\n"
	    "        [Mandatory] The input file in binary format.\n\n"
	    "    -o <IDT output file>\n\n"
	    "        [Mandatory] The IDT output file.\n\n"
	    "    -n <n>\n\n"
	    "        [Mandatory] Number of vectors\n\n"
	    "    -v  Display version.\n\n"
	    "    -h  Display this help.\n\n"
	    "\nReturns -1 on error, 0 on success\n\n");
}
