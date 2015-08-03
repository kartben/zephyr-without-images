/* dtls -- a very basic DTLS implementation
 *
 * Copyright (C) 2011 Olaf Bergmann <bergmann@tzi.org>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* test vectors from RFC 3610 */

struct test_vector {
  size_t M, L;
  size_t lm;			/* overall message length */
  size_t la;			/* number of bytes additional data */
  unsigned char key[DTLS_CCM_BLOCKSIZE];
  unsigned char nonce[DTLS_CCM_BLOCKSIZE];
  unsigned char msg[200];
  size_t r_lm;			/* overall result length */
  unsigned char result[200];	/* result */
};

struct test_vector data[] = {
  /* #1 */
  { 8, 2, 31, 8,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x03, 0x02, 0x01, 0x00, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E},	/* msg */
    39,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x58, 0x8C, 0x97, 0x9A, 0x61, 0xC6, 0x63, 0xD2, 0xF0, 0x66, 0xD0, 0xC2, 0xC0, 0xF9, 0x89, 0x80, 0x6D, 0x5F, 0x6B, 0x61, 0xDA, 0xC3, 0x84, 0x17, 0xE8, 0xD1, 0x2C, 0xFD, 0xF9, 0x26, 0xE0}	/* result */
  },
  
  /* #2 */
  { 8, 2, 32, 8,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x04, 0x03, 0x02, 0x01, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F},	/* msg */
    40,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x72, 0xC9, 0x1A, 0x36, 0xE1, 0x35, 0xF8, 0xCF, 0x29, 0x1C, 0xA8, 0x94, 0x08, 0x5C, 0x87, 0xE3, 0xCC, 0x15, 0xC4, 0x39, 0xC9, 0xE4, 0x3A, 0x3B, 0xA0, 0x91, 0xD5, 0x6E, 0x10, 0x40, 0x09, 0x16}	/* result */
  },

  /* #3 */
  { 8, 2, 33, 8,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x05, 0x04, 0x03, 0x02, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20},	/* msg */
    41,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x51, 0xB1, 0xE5, 0xF4, 0x4A, 0x19, 0x7D, 0x1D, 0xA4, 0x6B, 0x0F, 0x8E, 0x2D, 0x28, 0x2A, 0xE8, 0x71, 0xE8, 0x38, 0xBB, 0x64, 0xDA, 0x85, 0x96, 0x57, 0x4A, 0xDA, 0xA7, 0x6F, 0xBD, 0x9F, 0xB0, 0xC5}	/* result */
  },

  /* #4 */
  { 8, 2, 31, 12,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x06, 0x05, 0x04, 0x03, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E},	/* msg */
    39,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xA2, 0x8C, 0x68, 0x65, 0x93, 0x9A, 0x9A, 0x79, 0xFA, 0xAA, 0x5C, 0x4C, 0x2A, 0x9D, 0x4A, 0x91, 0xCD, 0xAC, 0x8C, 0x96, 0xC8, 0x61, 0xB9, 0xC9, 0xE6, 0x1E, 0xF1}	/* result */
  },

  /* #5 */
  { 8, 2, 32, 12,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x07, 0x06, 0x05, 0x04, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F},	/* msg */
    40,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xDC, 0xF1, 0xFB, 0x7B, 0x5D, 0x9E, 0x23, 0xFB, 0x9D, 0x4E, 0x13, 0x12, 0x53, 0x65, 0x8A, 0xD8, 0x6E, 0xBD, 0xCA, 0x3E, 0x51, 0xE8, 0x3F, 0x07, 0x7D, 0x9C, 0x2D, 0x93}	/* result */
  },

  /* #6 */
  { 8, 2, 33, 12,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x08, 0x07, 0x06, 0x05, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20},	/* msg */
    41,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x6F, 0xC1, 0xB0, 0x11, 0xF0, 0x06, 0x56, 0x8B, 0x51, 0x71, 0xA4, 0x2D, 0x95, 0x3D, 0x46, 0x9B, 0x25, 0x70, 0xA4, 0xBD, 0x87, 0x40, 0x5A, 0x04, 0x43, 0xAC, 0x91, 0xCB, 0x94}	/* result */
  },

  /* #7 */
  { 10, 2, 31, 8,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x09, 0x08, 0x07, 0x06, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E},	/* msg */
    41,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x01, 0x35, 0xD1, 0xB2, 0xC9, 0x5F, 0x41, 0xD5, 0xD1, 0xD4, 0xFE, 0xC1, 0x85, 0xD1, 0x66, 0xB8, 0x09, 0x4E, 0x99, 0x9D, 0xFE, 0xD9, 0x6C, 0x04, 0x8C, 0x56, 0x60, 0x2C, 0x97, 0xAC, 0xBB, 0x74, 0x90}	/* result */
  },

  /* #8 */
  { 10, 2, 32, 8,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x0A, 0x09, 0x08, 0x07, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F},	/* msg */
    42,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x7B, 0x75, 0x39, 0x9A, 0xC0, 0x83, 0x1D, 0xD2, 0xF0, 0xBB, 0xD7, 0x58, 0x79, 0xA2, 0xFD, 0x8F, 0x6C, 0xAE, 0x6B, 0x6C, 0xD9, 0xB7, 0xDB, 0x24, 0xC1, 0x7B, 0x44, 0x33, 0xF4, 0x34, 0x96, 0x3F, 0x34, 0xB4}	/* result */
  },

  /* #9 */
  { 10, 2, 33, 8,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x0B, 0x0A, 0x09, 0x08, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20},	/* msg */
    43,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x82, 0x53, 0x1A, 0x60, 0xCC, 0x24, 0x94, 0x5A, 0x4B, 0x82, 0x79, 0x18, 0x1A, 0xB5, 0xC8, 0x4D, 0xF2, 0x1C, 0xE7, 0xF9, 0xB7, 0x3F, 0x42, 0xE1, 0x97, 0xEA, 0x9C, 0x07, 0xE5, 0x6B, 0x5E, 0xB1, 0x7E, 0x5F, 0x4E}	/* result */
  },

  /* #10 */
  { 10, 2, 31, 12,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x0C, 0x0B, 0x0A, 0x09, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E},	/* msg */
    41,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x07, 0x34, 0x25, 0x94, 0x15, 0x77, 0x85, 0x15, 0x2B, 0x07, 0x40, 0x98, 0x33, 0x0A, 0xBB, 0x14, 0x1B, 0x94, 0x7B, 0x56, 0x6A, 0xA9, 0x40, 0x6B, 0x4D, 0x99, 0x99, 0x88, 0xDD}	/* result */
  },

  /* #11 */
  { 10, 2, 32, 12,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x0D, 0x0C, 0x0B, 0x0A, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F},	/* msg */
    42,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x67, 0x6B, 0xB2, 0x03, 0x80, 0xB0, 0xE3, 0x01, 0xE8, 0xAB, 0x79, 0x59, 0x0A, 0x39, 0x6D, 0xA7, 0x8B, 0x83, 0x49, 0x34, 0xF5, 0x3A, 0xA2, 0xE9, 0x10, 0x7A, 0x8B, 0x6C, 0x02, 0x2C}	/* result */
  },

  /* #12 */
  { 10, 2, 33, 12,
    { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},	/* AES key */
    { 0x00, 0x00, 0x00, 0x0E, 0x0D, 0x0C, 0x0B, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},	/* Nonce */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20},	/* msg */
    43,	/* length of result */
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xC0, 0xFF, 0xA0, 0xD6, 0xF0, 0x5B, 0xDB, 0x67, 0xF2, 0x4D, 0x43, 0xA4, 0x33, 0x8D, 0x2A, 0xA4, 0xBE, 0xD7, 0xB2, 0x0E, 0x43, 0xCD, 0x1A, 0xA3, 0x16, 0x62, 0xE7, 0xAD, 0x65, 0xD6, 0xDB}	/* result */
  },

  /* #13 */
  { 8, 2, 31, 8,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x41, 0x2B, 0x4E, 0xA9, 0xCD, 0xBE, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0x0B, 0xE1, 0xA8, 0x8B, 0xAC, 0xE0, 0x18, 0xB1, 0x08, 0xE8, 0xCF, 0x97, 0xD8, 0x20, 0xEA, 0x25, 0x84, 0x60, 0xE9, 0x6A, 0xD9, 0xCF, 0x52, 0x89, 0x05, 0x4D, 0x89, 0x5C, 0xEA, 0xC4, 0x7C},	/* msg */
    39,	/* length of result */
    { 0x0B, 0xE1, 0xA8, 0x8B, 0xAC, 0xE0, 0x18, 0xB1, 0x4C, 0xB9, 0x7F, 0x86, 0xA2, 0xA4, 0x68, 0x9A, 0x87, 0x79, 0x47, 0xAB, 0x80, 0x91, 0xEF, 0x53, 0x86, 0xA6, 0xFF, 0xBD, 0xD0, 0x80, 0xF8, 0xE7, 0x8C, 0xF7, 0xCB, 0x0C, 0xDD, 0xD7, 0xB3}	/* result */
  },

  /* #14 */
  { 8, 2, 32, 8,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x33, 0x56, 0x8E, 0xF7, 0xB2, 0x63, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0x63, 0x01, 0x8F, 0x76, 0xDC, 0x8A, 0x1B, 0xCB, 0x90, 0x20, 0xEA, 0x6F, 0x91, 0xBD, 0xD8, 0x5A, 0xFA, 0x00, 0x39, 0xBA, 0x4B, 0xAF, 0xF9, 0xBF, 0xB7, 0x9C, 0x70, 0x28, 0x94, 0x9C, 0xD0, 0xEC},	/* msg */
    40,	/* length of result */
    { 0x63, 0x01, 0x8F, 0x76, 0xDC, 0x8A, 0x1B, 0xCB, 0x4C, 0xCB, 0x1E, 0x7C, 0xA9, 0x81, 0xBE, 0xFA, 0xA0, 0x72, 0x6C, 0x55, 0xD3, 0x78, 0x06, 0x12, 0x98, 0xC8, 0x5C, 0x92, 0x81, 0x4A, 0xBC, 0x33, 0xC5, 0x2E, 0xE8, 0x1D, 0x7D, 0x77, 0xC0, 0x8A}	/* result */
  },

  /* #15 */
  { 8, 2, 33, 8,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x10, 0x3F, 0xE4, 0x13, 0x36, 0x71, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0xAA, 0x6C, 0xFA, 0x36, 0xCA, 0xE8, 0x6B, 0x40, 0xB9, 0x16, 0xE0, 0xEA, 0xCC, 0x1C, 0x00, 0xD7, 0xDC, 0xEC, 0x68, 0xEC, 0x0B, 0x3B, 0xBB, 0x1A, 0x02, 0xDE, 0x8A, 0x2D, 0x1A, 0xA3, 0x46, 0x13, 0x2E},	/* msg */
    41,	/* length of result */
    { 0xAA, 0x6C, 0xFA, 0x36, 0xCA, 0xE8, 0x6B, 0x40, 0xB1, 0xD2, 0x3A, 0x22, 0x20, 0xDD, 0xC0, 0xAC, 0x90, 0x0D, 0x9A, 0xA0, 0x3C, 0x61, 0xFC, 0xF4, 0xA5, 0x59, 0xA4, 0x41, 0x77, 0x67, 0x08, 0x97, 0x08, 0xA7, 0x76, 0x79, 0x6E, 0xDB, 0x72, 0x35, 0x06}	/* result */
  },

  /* #16 */
  { 8, 2, 31, 12,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x76, 0x4C, 0x63, 0xB8, 0x05, 0x8E, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0xD0, 0xD0, 0x73, 0x5C, 0x53, 0x1E, 0x1B, 0xEC, 0xF0, 0x49, 0xC2, 0x44, 0x12, 0xDA, 0xAC, 0x56, 0x30, 0xEF, 0xA5, 0x39, 0x6F, 0x77, 0x0C, 0xE1, 0xA6, 0x6B, 0x21, 0xF7, 0xB2, 0x10, 0x1C},	/* msg */
    39,	/* length of result */
    { 0xD0, 0xD0, 0x73, 0x5C, 0x53, 0x1E, 0x1B, 0xEC, 0xF0, 0x49, 0xC2, 0x44, 0x14, 0xD2, 0x53, 0xC3, 0x96, 0x7B, 0x70, 0x60, 0x9B, 0x7C, 0xBB, 0x7C, 0x49, 0x91, 0x60, 0x28, 0x32, 0x45, 0x26, 0x9A, 0x6F, 0x49, 0x97, 0x5B, 0xCA, 0xDE, 0xAF}	/* result */
  },

  /* #17 */
  { 8, 2, 32, 12,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0xF8, 0xB6, 0x78, 0x09, 0x4E, 0x3B, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0x77, 0xB6, 0x0F, 0x01, 0x1C, 0x03, 0xE1, 0x52, 0x58, 0x99, 0xBC, 0xAE, 0xE8, 0x8B, 0x6A, 0x46, 0xC7, 0x8D, 0x63, 0xE5, 0x2E, 0xB8, 0xC5, 0x46, 0xEF, 0xB5, 0xDE, 0x6F, 0x75, 0xE9, 0xCC, 0x0D},	/* msg */
    40,	/* length of result */
    { 0x77, 0xB6, 0x0F, 0x01, 0x1C, 0x03, 0xE1, 0x52, 0x58, 0x99, 0xBC, 0xAE, 0x55, 0x45, 0xFF, 0x1A, 0x08, 0x5E, 0xE2, 0xEF, 0xBF, 0x52, 0xB2, 0xE0, 0x4B, 0xEE, 0x1E, 0x23, 0x36, 0xC7, 0x3E, 0x3F, 0x76, 0x2C, 0x0C, 0x77, 0x44, 0xFE, 0x7E, 0x3C}	/* result */
  },

  /* #18 */
  { 8, 2, 33, 12,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0xD5, 0x60, 0x91, 0x2D, 0x3F, 0x70, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0xCD, 0x90, 0x44, 0xD2, 0xB7, 0x1F, 0xDB, 0x81, 0x20, 0xEA, 0x60, 0xC0, 0x64, 0x35, 0xAC, 0xBA, 0xFB, 0x11, 0xA8, 0x2E, 0x2F, 0x07, 0x1D, 0x7C, 0xA4, 0xA5, 0xEB, 0xD9, 0x3A, 0x80, 0x3B, 0xA8, 0x7F},	/* msg */
    41,	/* length of result */
    { 0xCD, 0x90, 0x44, 0xD2, 0xB7, 0x1F, 0xDB, 0x81, 0x20, 0xEA, 0x60, 0xC0, 0x00, 0x97, 0x69, 0xEC, 0xAB, 0xDF, 0x48, 0x62, 0x55, 0x94, 0xC5, 0x92, 0x51, 0xE6, 0x03, 0x57, 0x22, 0x67, 0x5E, 0x04, 0xC8, 0x47, 0x09, 0x9E, 0x5A, 0xE0, 0x70, 0x45, 0x51}	/* result */
  },

  /* #19 */
  { 10, 2, 31, 8,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x42, 0xFF, 0xF8, 0xF1, 0x95, 0x1C, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0xD8, 0x5B, 0xC7, 0xE6, 0x9F, 0x94, 0x4F, 0xB8, 0x8A, 0x19, 0xB9, 0x50, 0xBC, 0xF7, 0x1A, 0x01, 0x8E, 0x5E, 0x67, 0x01, 0xC9, 0x17, 0x87, 0x65, 0x98, 0x09, 0xD6, 0x7D, 0xBE, 0xDD, 0x18},	/* msg */
    41,	/* length of result */
    { 0xD8, 0x5B, 0xC7, 0xE6, 0x9F, 0x94, 0x4F, 0xB8, 0xBC, 0x21, 0x8D, 0xAA, 0x94, 0x74, 0x27, 0xB6, 0xDB, 0x38, 0x6A, 0x99, 0xAC, 0x1A, 0xEF, 0x23, 0xAD, 0xE0, 0xB5, 0x29, 0x39, 0xCB, 0x6A, 0x63, 0x7C, 0xF9, 0xBE, 0xC2, 0x40, 0x88, 0x97, 0xC6, 0xBA}	/* result */
  },

  /* #20 */
  { 10, 2, 32, 8,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x92, 0x0F, 0x40, 0xE5, 0x6C, 0xDC, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0x74, 0xA0, 0xEB, 0xC9, 0x06, 0x9F, 0x5B, 0x37, 0x17, 0x61, 0x43, 0x3C, 0x37, 0xC5, 0xA3, 0x5F, 0xC1, 0xF3, 0x9F, 0x40, 0x63, 0x02, 0xEB, 0x90, 0x7C, 0x61, 0x63, 0xBE, 0x38, 0xC9, 0x84, 0x37},	/* msg */
    42,	/* length of result */
    { 0x74, 0xA0, 0xEB, 0xC9, 0x06, 0x9F, 0x5B, 0x37, 0x58, 0x10, 0xE6, 0xFD, 0x25, 0x87, 0x40, 0x22, 0xE8, 0x03, 0x61, 0xA4, 0x78, 0xE3, 0xE9, 0xCF, 0x48, 0x4A, 0xB0, 0x4F, 0x44, 0x7E, 0xFF, 0xF6, 0xF0, 0xA4, 0x77, 0xCC, 0x2F, 0xC9, 0xBF, 0x54, 0x89, 0x44}	/* result */
  },

  /* #21 */
  { 10, 2, 33, 8,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x27, 0xCA, 0x0C, 0x71, 0x20, 0xBC, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0x44, 0xA3, 0xAA, 0x3A, 0xAE, 0x64, 0x75, 0xCA, 0xA4, 0x34, 0xA8, 0xE5, 0x85, 0x00, 0xC6, 0xE4, 0x15, 0x30, 0x53, 0x88, 0x62, 0xD6, 0x86, 0xEA, 0x9E, 0x81, 0x30, 0x1B, 0x5A, 0xE4, 0x22, 0x6B, 0xFA},	/* msg */
    43,	/* length of result */
    { 0x44, 0xA3, 0xAA, 0x3A, 0xAE, 0x64, 0x75, 0xCA, 0xF2, 0xBE, 0xED, 0x7B, 0xC5, 0x09, 0x8E, 0x83, 0xFE, 0xB5, 0xB3, 0x16, 0x08, 0xF8, 0xE2, 0x9C, 0x38, 0x81, 0x9A, 0x89, 0xC8, 0xE7, 0x76, 0xF1, 0x54, 0x4D, 0x41, 0x51, 0xA4, 0xED, 0x3A, 0x8B, 0x87, 0xB9, 0xCE}	/* result */
  },

  /* #22 */
  { 10, 2, 31, 12,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x5B, 0x8C, 0xCB, 0xCD, 0x9A, 0xF8, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0xEC, 0x46, 0xBB, 0x63, 0xB0, 0x25, 0x20, 0xC3, 0x3C, 0x49, 0xFD, 0x70, 0xB9, 0x6B, 0x49, 0xE2, 0x1D, 0x62, 0x17, 0x41, 0x63, 0x28, 0x75, 0xDB, 0x7F, 0x6C, 0x92, 0x43, 0xD2, 0xD7, 0xC2},	/* msg */
    41,	/* length of result */
    { 0xEC, 0x46, 0xBB, 0x63, 0xB0, 0x25, 0x20, 0xC3, 0x3C, 0x49, 0xFD, 0x70, 0x31, 0xD7, 0x50, 0xA0, 0x9D, 0xA3, 0xED, 0x7F, 0xDD, 0xD4, 0x9A, 0x20, 0x32, 0xAA, 0xBF, 0x17, 0xEC, 0x8E, 0xBF, 0x7D, 0x22, 0xC8, 0x08, 0x8C, 0x66, 0x6B, 0xE5, 0xC1, 0x97}	/* result */
  },

  /* #23 */
  { 10, 2, 32, 12,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x3E, 0xBE, 0x94, 0x04, 0x4B, 0x9A, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0x47, 0xA6, 0x5A, 0xC7, 0x8B, 0x3D, 0x59, 0x42, 0x27, 0xE8, 0x5E, 0x71, 0xE2, 0xFC, 0xFB, 0xB8, 0x80, 0x44, 0x2C, 0x73, 0x1B, 0xF9, 0x51, 0x67, 0xC8, 0xFF, 0xD7, 0x89, 0x5E, 0x33, 0x70, 0x76},	/* msg */
    42,	/* length of result */
    { 0x47, 0xA6, 0x5A, 0xC7, 0x8B, 0x3D, 0x59, 0x42, 0x27, 0xE8, 0x5E, 0x71, 0xE8, 0x82, 0xF1, 0xDB, 0xD3, 0x8C, 0xE3, 0xED, 0xA7, 0xC2, 0x3F, 0x04, 0xDD, 0x65, 0x07, 0x1E, 0xB4, 0x13, 0x42, 0xAC, 0xDF, 0x7E, 0x00, 0xDC, 0xCE, 0xC7, 0xAE, 0x52, 0x98, 0x7D}	/* result */
  },

  /* #24 */
  { 10, 2, 33, 12,
    { 0xD7, 0x82, 0x8D, 0x13, 0xB2, 0xB0, 0xBD, 0xC3, 0x25, 0xA7, 0x62, 0x36, 0xDF, 0x93, 0xCC, 0x6B},	/* AES key */
    { 0x00, 0x8D, 0x49, 0x3B, 0x30, 0xAE, 0x8B, 0x3C, 0x96, 0x96, 0x76, 0x6C, 0xFA},	/* Nonce */
    { 0x6E, 0x37, 0xA6, 0xEF, 0x54, 0x6D, 0x95, 0x5D, 0x34, 0xAB, 0x60, 0x59, 0xAB, 0xF2, 0x1C, 0x0B, 0x02, 0xFE, 0xB8, 0x8F, 0x85, 0x6D, 0xF4, 0xA3, 0x73, 0x81, 0xBC, 0xE3, 0xCC, 0x12, 0x85, 0x17, 0xD4},	/* msg */
    43,	/* length of result */
    { 0x6E, 0x37, 0xA6, 0xEF, 0x54, 0x6D, 0x95, 0x5D, 0x34, 0xAB, 0x60, 0x59, 0xF3, 0x29, 0x05, 0xB8, 0x8A, 0x64, 0x1B, 0x04, 0xB9, 0xC9, 0xFF, 0xB5, 0x8C, 0xC3, 0x90, 0x90, 0x0F, 0x3D, 0xA1, 0x2A, 0xB1, 0x6D, 0xCE, 0x9E, 0x82, 0xEF, 0xA1, 0x6D, 0xA6, 0x20, 0x59}	/* result */
  },

  /* #25 */
  /* Cipher: AES-128 M=16 L=2 K_LEN=1 N_LEN=13 K=0x00 N=0x00000000000000000000000000 */
  { 16, 2, 0, 0,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* AES key */  
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Nonce */
    { },	/* msg */
    16,		/* length of result */
    { 0x8b, 0x60, 0xab, 0xcd, 0x60, 0x43, 0x81, 0x0b, 
      0xa3, 0x78, 0xa0, 0x1d, 0x4a, 0x29, 0x83, 0x0b
    }		/* result */
  },

  /* #26 */
  /* Cipher: AES-128 M=16 L=2 K_LEN=1 N_LEN=13 K=0x00 N=0x00000000000000000000000000 */
  { 16, 2, 37, 0,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, /* AES key */  
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00 }, /* Nonce */
    { 0x45, 0x69, 0x6e, 0x20, 0x6b, 0x6c, 0x65, 0x69, 
      0x6e, 0x65, 0x72, 0x20, 0x54, 0x65, 0x78, 0x74,
      0x0a, 0x7a, 0x75, 0x6d, 0x20, 0x54, 0x65, 0x73,
      0x74, 0x65, 0x6e, 0x20, 0x76, 0x6f, 0x6e, 0x20,
      0x43, 0x43, 0x4d, 0x2e, 0x0a
    },	/* msg */
    53,		/* length of result */
    { 0x90, 0x11, 0x9c, 0x2d, 0x6b, 0xf9, 0xe9, 0x05,
      0x3e, 0x0b, 0x44, 0x56, 0xca, 0xc8, 0xb6, 0x1a,
      0x00, 0x57, 0xa9, 0x8b, 0x6b, 0x69, 0x09, 0x7e, 
      0x8e, 0x50, 0x50, 0x63, 0x50, 0x58, 0x0f, 0x78,
      0x75, 0x69, 0x6e, 0x9f, 0x3d, 0x63, 0x93, 0xe7,
      0x7a, 0x84, 0xe9, 0x9f, 0x11, 0x93, 0x95, 0xa0,
      0x9a, 0xef, 0x0d, 0xa0, 0xed
    } /* result */
  },

  /* #27 */
  /* Cipher: AES-128 M=8 L=5 K_LEN=16 N_LEN=10 K=0x001234567890abcdefdcaffeed3921ee N=0x00112233445566778899 */
  { 8, 5, 0, 0,
    { 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd,
      0xef, 0xdc, 0xaf, 0xfe, 0xed, 0x39, 0x21, 0xee }, /* AES key */
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99 }, /* Nonce */
    { },	    /* msg */
    8,		    /* length of result */
    { 0xb1, 0x33, 0x51, 0xc8, 0xb3, 0xd5, 0x10, 0xa7 } /* result */
  },

  /* #28 */
  /* Cipher: AES-128 M=8 L=5 K_LEN=16 N_LEN=10 K=0x001234567890abcdefdcaffeed3921ee N=0x00112233445566778899 */
  { 8, 5, 37, 0,
    { 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd,
      0xef, 0xdc, 0xaf, 0xfe, 0xed, 0x39, 0x21, 0xee }, /* AES key */
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99 }, /* Nonce */
    { 0x45, 0x69, 0x6e, 0x20, 0x6b, 0x6c, 0x65, 0x69, 
      0x6e, 0x65, 0x72, 0x20, 0x54, 0x65, 0x78, 0x74,
      0x0a, 0x7a, 0x75, 0x6d, 0x20, 0x54, 0x65, 0x73,
      0x74, 0x65, 0x6e, 0x20, 0x76, 0x6f, 0x6e, 0x20,
      0x43, 0x43, 0x4d, 0x2e, 0x0a
    },	/* msg */
    45,		    /* length of result */
    { 0x44, 0x7a, 0x82, 0x70, 0x1d, 0xd0, 0x35, 0x7b,
      0x68, 0xf7, 0x35, 0x4d, 0xbf, 0xd9, 0x16, 0x15,
      0x97, 0x41, 0x3d, 0x1e, 0x89, 0xc1, 0x25, 0xe7,
      0xd6, 0xa7, 0xde, 0x90, 0x1e, 0xf1, 0x69, 0x69,
      0x9f, 0xce, 0x40, 0xdc, 0xf0, 0xd1, 0x74, 0x53,
      0x2c, 0xa3, 0xb0, 0xcf, 0xb9
    } /* result */
  },

  /* #29 */
  /* Cipher: AES-128 M=14 L=3 K_LEN=16 N_LEN=12 K=0x001234567890abcdefdcaffeed3921ee N=0x001122334455667788990000 */
  { 14, 3, 0, 0,
    { 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd,
      0xef, 0xdc, 0xaf, 0xfe, 0xed, 0x39, 0x21, 0xee }, /* AES key */
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0x00, 0x00 }, /* Nonce */
    { },	    /* msg */
    14,		    /* length of result */
    { 0xa4, 0x06, 0xa4, 0x23, 0x93, 0x3d, 0xa0, 0xca,
      0xb5, 0x90, 0xdb, 0x69, 0x69, 0x33 } /* result */
  },

  /* #30 */
  /* Cipher: AES-128 M=14 L=3 K_LEN=16 N_LEN=12 K=0x001234567890abcdefdcaffeed3921ee N=0x001122334455667788990000 */
  { 14, 3, 37, 0,
    { 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd,
      0xef, 0xdc, 0xaf, 0xfe, 0xed, 0x39, 0x21, 0xee }, /* AES key */
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0x00, 0x00 }, /* Nonce */
    { 0x45, 0x69, 0x6e, 0x20, 0x6b, 0x6c, 0x65, 0x69, 
      0x6e, 0x65, 0x72, 0x20, 0x54, 0x65, 0x78, 0x74,
      0x0a, 0x7a, 0x75, 0x6d, 0x20, 0x54, 0x65, 0x73,
      0x74, 0x65, 0x6e, 0x20, 0x76, 0x6f, 0x6e, 0x20,
      0x43, 0x43, 0x4d, 0x2e, 0x0a
    },	/* msg */
    51,
    { 0x60, 0xaf, 0x87, 0x67, 0x4d, 0x9d, 0x54, 0x17,
      0x16, 0xc0, 0x29, 0x10, 0x7e, 0x3e, 0x34, 0x93,
      0x78, 0xe8, 0xd3, 0xc8, 0xc1, 0x03, 0x4f, 0xd6,
      0xf5, 0x3b, 0xaf, 0xd3, 0xf0, 0xd7, 0x0b, 0xdd,
      0x63, 0x93, 0xed, 0xf2, 0xb2, 0x72, 0xdc, 0xae,
      0x7c, 0xa0, 0x01, 0xdb, 0x56, 0x2a, 0x06, 0xb6,
      0xe9, 0xcf, 0x3c } /* result */
  },

  /* #31 */
  /* Cipher: AES-128 M=8 L=5 K_LEN=6 N_LEN=10 K=0x11223344aabb N=0x00112233445566778899 */
  { 8, 5, 0, 0,
    { 0x11, 0x22, 0x33, 0x44, 0xaa, 0xbb }, 	/* AES key */
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99 },				/* Nonce */
    { },					/* msg */
    8,
    { 0x28, 0x15, 0xfe, 0x81, 0xdd, 0xc3, 0x79, 0x04 } /* result */
  },

  /* #32 */
  /* Cipher: AES-128 M=8 L=5 K_LEN=6 N_LEN=10 K=0x11223344aabb N=0x00112233445566778899 */

  { 8, 5, 37, 0,
    { 0x11, 0x22, 0x33, 0x44, 0xaa, 0xbb }, 	/* AES key */
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99 },				/* Nonce */
    { 0x45, 0x69, 0x6e, 0x20, 0x6b, 0x6c, 0x65, 0x69, 
      0x6e, 0x65, 0x72, 0x20, 0x54, 0x65, 0x78, 0x74,
      0x0a, 0x7a, 0x75, 0x6d, 0x20, 0x54, 0x65, 0x73,
      0x74, 0x65, 0x6e, 0x20, 0x76, 0x6f, 0x6e, 0x20,
      0x43, 0x43, 0x4d, 0x2e, 0x0a
    },	/* msg */
    45,
    { 0xdb, 0x31, 0x55, 0x9d, 0xab, 0x70, 0xdc, 0x62,
      0xd7, 0x76, 0x41, 0xb2, 0x14, 0x9e, 0x9c, 0x26,
      0x70, 0x61, 0xea, 0x36, 0xf8, 0x0e, 0xdf, 0x19,
      0xa6, 0xc7, 0x46, 0x3d, 0x5a, 0xc3, 0x0a, 0x73,
      0x14, 0x96, 0xa4, 0x84, 0x7f, 0x37, 0x55, 0x42,
      0xce, 0x7e, 0xf9, 0x3b, 0xe5 } /* result */
  }
};
