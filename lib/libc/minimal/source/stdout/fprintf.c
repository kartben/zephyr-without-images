/* fprintf.c */

/*
 * Copyright (c) 1997-2010, 2013-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdarg.h>
#include <stdio.h>

#define DESC(d) ((void *)d)

extern int _prf(int (*func)(), void *dest,
				const char *format, va_list vargs);

int fprintf(FILE *_Restrict F, const char *_Restrict format, ...)
{
	va_list vargs;
	int     r;

	va_start(vargs, format);
	r = _prf(fputc, DESC(F), format, vargs);
	va_end(vargs);

	return r;
}

int vfprintf(FILE *_Restrict F, const char *_Restrict format, va_list vargs)
{
	int r;

	r = _prf(fputc, DESC(F), format, vargs);

	return r;
}

int printf(const char *_Restrict format, ...)
{
	va_list vargs;
	int     r;

	va_start(vargs, format);
	r = _prf(fputc, DESC(stdout), format, vargs);
	va_end(vargs);

	return r;
}

int vprintf(const char *_Restrict format, va_list vargs)
{
	int r;

	r = _prf(fputc, DESC(stdout), format, vargs);

	return r;
}
