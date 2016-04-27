/*
 * salibc.c
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

/* Simple C Array Library */

/* Use:
 * const MYVARIABLE = value
 * instead of:
 * value
 * or
 * #define MYVAR value
 * in your code.
 */
#include "salibc.h"

static bool element_null (void *element);
static bool memory_overlaps (void *chunk1, void *chunk2, size_t fullsize);
static void realarray_delete (Array a);
static char *array_indexpointer (Array a, int index);
static bool array_indexoutofbounds (Array a, int index);
static bool array_memcopy (Array a, int index, void *element);
/*
 ***************************
 *General purpose methods. *
 ***************************
 */
static bool
element_null (void *element)
{
  return (element == NULL);
}

static bool
memory_overlaps (void *chunk1, void *chunk2, size_t fullsize)
{
  char *c1 = chunk1, *c2 = chunk2;

  if (element_null (chunk1) || element_null (chunk2))
    return false;

  /* |-----------|
   * |     |-----|-------|
   * c1   c2  c1+fullsize  c2+smt
   * c2   c1  c2+fullsize  c1+smt
   *
   */
  return ((c1 <= c2) && (c1 + fullsize >= c2)) || ((c2 <= c1)
						   && (c2 + fullsize >= c1));
}

/*
 ******************
 * Mixed methods. *
 ******************
 */
/* Delete the non-ADT part of the array (as well as some fields of the ADT). */
static void
realarray_delete (Array a)
{
  if (array_null (a))
    return;

  /* Free the real array. */
  free (array_pointer (a));
  a->ptr = NULL;
  a->nmemb = 0;
}

/*
 ***************************
 * Array specific methods. *
 ***************************
 */
static bool
array_indexoutofbounds (Array a, int index)
{
  return ((index < 0) || (index > array_length (a) - 1));
}

static char *
array_indexpointer (Array a, int index)
{
  if (array_null (a))
    return NULL;

  /* Array bound check. */
  if (array_indexoutofbounds (a, index))
    return NULL;

  return (array_pointer (a) + (((size_t) index) * array_size (a)));
}

/* It is assumed that element has the same size of a->ptr. */
static bool
array_memcopy (Array a, int index, void *element)
{
  if (array_null (a))
    return false;

  /* Even though the array_indexoutofbounds function is called inside the 
     array_indexpointer function, this returns NULL, so memcpy would be done on a 
     dest of NULL. */
  if (!element_null (element)
      && !memory_overlaps (a, element, array_fullsize (a))
      && !array_indexoutofbounds (a, index))
    {
      memcpy (array_indexpointer (a, index), element, array_size (a));
      return true;
    }
  else
    return false;
}


bool
array_null (Array a)
{
  return (element_null (a));
}

bool
array_empty (Array a)
{
  assert (!array_null (a));
  return (array_length (a) == 0);
}

size_t
array_size (Array a)
{
  assert (!array_null (a));
  return (a->size);
}

int
array_length (Array a)
{
  assert (!array_null (a));
  return (a->nmemb);
}

/* This shouldn't go out of bounds. */
size_t
array_fullsize (Array a)
{
  assert (!array_null (a));
  return (((size_t) array_length (a)) * array_size (a));
}

char *
array_pointer (Array a)
{
  if (array_null (a))
    return NULL;

  return (a->ptr);
}

/* memcmp works well in checking equality even for floating point numbers. */
bool
array_equal (Array a1, Array a2)
{
  if (array_null (a1) || array_null (a2))
    return false;

  if ((array_length (a1) == array_length (a2))
      && (array_fullsize (a1) == array_fullsize (a2))
      && (memcmp (array_pointer (a1), array_pointer (a2), array_fullsize (a1))
	  == 0))
    return true;

  return false;
}

/* Array constructor. */
Array
array_new (int nmemb, size_t size)
{
  Array new_array = NULL;

  if (nmemb >= 0 && size > 0)
    {
      new_array = malloc (sizeof (struct Array));
      if (element_null (new_array))
	return NULL;

      new_array->size = size;
      new_array->nmemb = nmemb;
      new_array->ptr = calloc (nmemb, size);
      if (element_null (array_pointer (new_array)))
	array_delete (&new_array);
    }

  /* This may be NULL. */
  return new_array;
}

void
array_delete (Array * a_ref)
{
  if (!element_null (a_ref) && !array_null (*a_ref))
    {
      /* Free the real array. */
      realarray_delete (*a_ref);
      /* Free the ADT. */
      (*a_ref)->size = 0;
      free (*a_ref);
      *a_ref = NULL;
    }
}

/* true = success
 * false = failure
 */
bool
array_put (Array a, int index, void *element)
{
  return (array_memcopy (a, index, element));
}


/* Set the every index of array with the same value. */
bool
array_set (Array a, void *element)
{
  int i;

  for (i = 0; i < array_length (a); i++)
    {
      if (!array_memcopy (a, i, element))
	return false;
    }

  return true;
}

/* Get pointer to index. If you cast to the correct pointer type, then
 * reference it you get the stored value in the index.
 * This is an interface to array_indexpointer.
 */
char *
array_get (Array a, int index)
{
  return (array_indexpointer (a, index));
}

/* BUGGY PART--------------------------------------------- */
void
array_printelement (Array a, int index, const char *format)
{
  char buf[128];

  sprintf (buf, format, *(array_indexpointer (a, index)));
  printf ("%s", buf);
/*    printf (format, * (array_indexpointer (a, index) ) );*/
}

void
array_print (Array a, const char *format)
{
  int i;
  assert (!array_empty (a));

  for (i = 0; i < array_length (a); i++)
    array_printelement (a, i, format);
}

bool
array_orderedasc (Array a)
{
  int i;

  /* With 1 or 0 elements the array is surely ordered. */
  if (array_length (a) <= 1)
    return true;

  for (i = 0; i < array_length (a) - 1; i++)
    {
      if (*((double *) array_indexpointer (a, i)) < *
	  ((double *) array_indexpointer (a, i + 1)))
	printf ("in--OK\n");

      if (memcmp (array_indexpointer (a, i + i), array_indexpointer (a, i),
		  array_size (a)) < 0)
	return false;
    }

  return true;
}

/* END OF BUGGY PART------------------------------------------ */

Array
array_copy (Array a1)
{
  int i;
  Array a2;

  if (array_null (a1))
    return NULL;

  /* Allocate a new array with the same ADT characteristics. */
  a2 = array_new (array_length (a1), array_size (a1));
  if (array_null (a2))
    return NULL;

  /* Copy the real array using the previously defined functions. */
  for (i = 0; i < array_length (a1); i++)
    if (!array_memcopy (a2, i, array_indexpointer (a1, i)))
      return NULL;

  return a2;
}

bool
array_resize (Array a, int new_length)
{
  char *tmp;
  int memdiff;

  if (array_null (a))
    return NULL;

  /* Invalid new length. */
  if (new_length < 0)
    return false;
  /* new_length is set to 0 -> leave ADT, but delete internal array. */
  else if (new_length == 0)
    {
      realarray_delete (a);
      return true;
    }
  /* Same size -> do nothing. */
  else if (array_length (a) == new_length)
    return true;
  /* Array's length != new_length, so realloc can now be used directly. */
  else
    {
      /* Safe realloc (to avoid losing the stored array if realloc fails). */
      tmp =
	realloc (array_pointer (a),
		 array_fullsize (a) +
		 (array_size (a) * ((size_t) new_length)));
      if (!element_null (tmp))
	a->ptr = tmp;
      else
	return false;

      /* memset to 0 new part of the array. 
       * To do this we must go to the first byte of the new array and put 0 
       * until we get to (memdiff * a->size) bytes.
       */
      memdiff = new_length - array_length (a);
      if (memdiff > 0)
	memset (array_pointer (a) + array_fullsize (a) + array_size (a), 0,
		((size_t) memdiff) * array_size (a));

      /* Set the new array length. */
      a->nmemb = new_length;
    }

  return true;
}

bool
array_append (Array a, void *element)
{
  int initial_length = array_length (a);

  if (array_resize (a, initial_length + 1)
      && array_memcopy (a, initial_length, element))
    return true;
  else
    return false;
}

char *
array_trim (Array a)
{
  int initial_length = array_length (a);
  char *element, *element_copy;

  element = array_indexpointer (a, initial_length - 1);
  /* Copy *element int *element_copy.  */
  element_copy = malloc (array_size (a));
  memcpy (element_copy, element, array_size (a));

  if (!element_null (element_copy) && array_resize (a, initial_length - 1))
    return element_copy;
  else
    return NULL;
}

/* Array array_merge (Array a1, Array a2) */
/* Array array_sum (Array a ) */
/* Array array_merge (Array a1, Array a2) */
/* The following two return the pointer to the elements. If referenced they
 * return the value. */
/* char *array_maxelement (Array a ) */
/* char *array_minelement (Array a ) */
/* ? array_ascorder (Array a) */
/* ? array_dscorder (Array a) */
