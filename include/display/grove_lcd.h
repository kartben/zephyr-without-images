/* grove_lcd.h - Public API for the Grove RGB LCD device */
/*
 * Copyright (c) 2015 Intel Corporation
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
#ifndef DISPLAY_GROVE_LCD_H
#define DISPLAY_GROVE_LCD_H

#define GROVE_LCD_NAME			"GLCD"

/**
 *  @brief Send text to the screen
 *
 *  @param port Pointer to device structure for driver instance.
 *  @param data the ASCII text to display
 *  @param size the length of the text in bytes
 */
void glcd_print(struct device *port, unsigned char *data, uint32_t size);


/**
 *  @brief Set text cursor position for next additions
 *
 *  @param port Pointer to device structure for driver instance.
 *  @param col the column for the cursor to be moved to (0-15)
 *  @param row the row it should be moved to (0 or 1)
 */
void glcd_cursor_pos_set(struct device *port, uint8_t col, uint8_t row);

/**
 *  @brief Clear the current display
 *
 *  @param port Pointer to device structure for driver instance.
 */
void glcd_clear(struct device *port);

/* Defines for the GLCD_CMD_DISPLAY_SWITCH options */
#define GLCD_DS_DISPLAY_ON		(1 << 2)
#define GLCD_DS_DISPLAY_OFF		(0 << 2)
#define GLCD_DS_CURSOR_ON		(1 << 1)
#define GLCD_DS_CURSOR_OFF		(0 << 1)
#define GLCD_DS_BLINK_ON		(1 << 0)
#define GLCD_DS_BLINK_OFF		(0 << 0)
/**
 *  @brief Function to change the display state.
 *  @details This function provides the user the ability to change the state
 *  of the display as per needed. Controlling things like powering on or off
 *  the screen, the option to display the cusror or not, and the ability to
 *  blink the cursor.
 *
 *  @param port Pointer to device structure for driver instance.
 *  @param opt An 8bit bitmask of GLCD_DS_* options.
 *
 */
void glcd_display_state_set(struct device *port, uint8_t opt);

/**
 * @brief return the display feature set associated with the device
 *
 * @param port the Grove LCD to get the display features set
 *
 * @return the display feature set associated with the device.
 */
uint8_t glcd_display_state_get(struct device *port);

/* Defines for the GLCD_CMD_INPUT_SET to change text direction */
#define GLCD_IS_SHIFT_INCREMENT	(1 << 1)
#define GLCD_IS_SHIFT_DECREMENT	(0 << 1)
#define GLCD_IS_ENTRY_LEFT	(1 << 0)
#define GLCD_IS_ENTRY_RIGHT	(0 << 0)
/**
 *  @brief Function to change the input state.
 *  @details This function provides the user the ability to change the state
 *  of the text input. Controlling things like text entry from the left or
 *  right side, and how far to increment on new text
 *
 *  @param port Pointer to device structure for driver instance.
 *  @param opt A bitmask of GLCD_IS_* options
 *
 */
void glcd_input_state_set(struct device *port, uint8_t opt);

/**
 * @brief return the input set associated with the device
 *
 * @param port the Grove LCD to get the input features set
 *
 * @return the input set associated with the device.
 */
uint8_t glcd_input_state_get(struct device *port);

/* Defines for the LCD_FUNCTION_SET */
#define GLCD_FS_8BIT_MODE	(1 << 4)
#define GLCD_FS_ROWS_2		(1 << 3)
#define GLCD_FS_ROWS_1		(0 << 3)
#define GLCD_FS_DOT_SIZE_BIG	(1 << 2)
#define GLCD_FS_DOT_SIZE_LITTLE	(0 << 2)
/* Bits 0, 1 are not defined for this register */

/**
 *  @brief Function to set the functional state of the display.
 *  @param port Pointer to device structure for driver instance.
 *  @param opt A bitmask of GLCD_FS_* options
 *
 *  @details This function provides the user the ability to change the state
 *  of the display as per needed.  Controlling things like the number of rows,
 *  dot size, and text display quality.
 */
void glcd_function_set(struct device *port, uint8_t opt);

/**
 * @brief return the function set associated with the device
 *
 * @param port the Grove LCD to get the functions set
 *
 * @return the function features set associated with the device.
 */
uint8_t glcd_function_get(struct device *port);


/* Available color selections */
#define GROVE_RGB_WHITE		0
#define GROVE_RGB_RED		1
#define GROVE_RGB_GREEN		2
#define GROVE_RGB_BLUE		3
/**
 *  @brief Set LCD background to a predfined color
 *  @param port Pointer to device structure for driver instance.
 *  @param color One of the pre-defined color options
 */
void glcd_color_select(struct device *port, uint8_t color);


/**
 *  @brief Set LCD background to custom RGB color value
 *
 *  @param port Pointer to device structure for driver instance.
 *  @param r A numeric value for the red color (max is 255)
 *  @param g A numeric value for the green color (max is 255)
 *  @param b A numeric value for the blue color (max is 255)
 */
void glcd_color_set(struct device *port, uint8_t r, uint8_t g, uint8_t b);


/**
 *  @brief Initialize the Grove LCD panel
 *
 *  @param port Pointer to device structure for driver instance.
 *
 *  @return Returns DEV_OK if all passes
 */
int glcd_initialize(struct device *port);

#endif /* DISPLAY_GROVE_LCD_H */
