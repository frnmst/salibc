/*
 * salibc.h
 *
 * Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com>
 *                                            <franco.masotti@student.unife.it>
 *
 * This file is part of salibc.
 *
 * salibc is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * salibc is distributed in the hope that it will be
 * useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with salibc.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SALIBC
#define SALIBC

/* Check C version. */
#define ISOC99_SOURCE
#define _POSIX_C_SOURCE 199309L
#if __STDC_VERSION__ != 199901L
#error "ANSI C99 not available"
#endif

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Array
{
  size_t size;
  int nmemb;
  /* Pointer aritmetic can be doin on char star (unlike void star) . */
  char *ptr;
};

typedef struct Array *Array;

extern bool array_null (Array a);
extern bool array_empty (Array a);
extern size_t array_size (Array a);
extern int array_length (Array a);
extern size_t array_fullsize (Array a);
extern char *array_pointer (Array a);
extern bool array_equal (Array a1, Array a2);
extern void array_delete (Array * a_ref);
extern Array array_new (int nmemb, size_t size);
extern bool array_put (Array a, int index, void *element);
extern bool array_set (Array a, void *element);
extern char *array_get (Array a, int index);
extern Array array_copy (Array a1);
extern bool array_resize (Array a, int new_length);
extern bool array_append (Array a, void *element);
extern char *array_trim (Array a);
extern Array array_merge (Array a1, Array a2);

#endif
