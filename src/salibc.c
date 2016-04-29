/*
 * @file salibc.c
 * @author Franco Masotti
 * @date 28 Apr 2016
 * @brief Implementation file.
 *
 * Simple C Array Library.
 */

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

#include "salibc.h"

/**
 * @brief Check if the input memory address points to NULL.
 *
 * @param[in] element A generic memory address.
 *
 * @retval true Input address points to NULL.
 * @retval false Input address does not point to NULL.
 */
static bool element_null (void *element);

/**
 * @brief Check if two memory areas overlap.
 *
 * @param[in] chunk1 The first generic memory address.
 * @param[in] chunk2 The second generic memory address.
 * @param[in] fullsize Full size of the first chunk of memory.
 *
 * @retval true The two memory areas overlap.
 * @retval false The two memory areas do not overlap.
 *
 * @warning This function is not reliable.
 */
static bool memory_overlaps (void *chunk1, void *chunk2, size_t fullsize);

/**
 * @brief Delete the array but not its ADT.
 *
 * @param[in] a The pointer to an array ADT instance.
 */
static void realarray_delete (Array a);

/**
 * @brief This functions is the same as array_get.
 */
static char *array_indexpointer (Array a, int index);

/**
 * @param[in] a The pointer to an array ADT instance.
 * @param[in] index The index to be checked.
 *
 * @retval true The selected index is part of the array.
 * @retval false The selected index is not part of the array.
 */
static bool array_indexoutofbounds (Array a, int index);

/**
 * @brief This functions is the same as array_put.
 */
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

#if defined (MEMORY_OVERLAP_CHECK) || DOXYGEN

/**
 * @brief If this flag is defined memory_overlaps function will work normally,
 * otherwise it will only return false. By default this flag is deactivated.
 */
#define MEMORY_OVERLAP_CHECK

/**
 * @note Since memory is not always allocated consecutively, the following
 * controls may fail because only memory addresses are checked and the
 * system does not know if the memory in between belongs to something else.
 */
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
#else
static bool
memory_overlaps (void *chunk1, void *chunk2, size_t fullsize)
{
  (void) chunk1;
  (void) chunk2;
  (void) fullsize;
  return false;
}
#endif

/*
 ******************
 * Mixed methods. *
 ******************
 */

/**
 * @note The non-ADT part of the array is deleted (as well as some fields of
 * the ADT).
 */
static void
realarray_delete (Array a)
{
  if (array_null (a))
    return;

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

/**
 * @note It is assumed that element has the same size of a->ptr.
 */
static bool
array_memcopy (Array a, int index, void *element)
{
  if (array_null (a))
    return false;

  /**
   * @note Even though the array_indexoutofbounds function is called inside the
   * array_indexpointer function, this returns NULL, so memcpy would be done
   * on a dest of NULL. That's why we need to call that function here as well
   */
   /** @code */
  if (!element_null (element)
      && !memory_overlaps (a, element, array_fullsize (a))
      && !array_indexoutofbounds (a, index))
    {
      memcpy (array_indexpointer (a, index), element, array_size (a));
      return true;
    }
  /** @endcode */
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

/**
 * @note This function should not return an out of bound value.
 */
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

/**
 * @note memcmp works well in checking equality even for floating point
 * numbers.
 */
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

/**
 * @note This function is also known as the array constructor.
 */
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

  return new_array;
}

void
array_delete (Array * a_ref)
{
  if (!element_null (a_ref) && !array_null (*a_ref))
    {
      realarray_delete (*a_ref);
      (*a_ref)->size = 0;
      free (*a_ref);
      *a_ref = NULL;
    }
}

bool
array_put (Array a, int index, void *element)
{
  return (array_memcopy (a, index, element));
}


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

/**
 * @note This function is an interface to array_indexpointer.
 */
char *
array_get (Array a, int index)
{
  return (array_indexpointer (a, index));
}

Array
array_copy (Array a1)
{
  int i;
  Array a2;

  if (array_null (a1))
    return NULL;

  /**
   * @note Allocate a new array with the same ADT characteristics.
   */
  /** @code */
  a2 = array_new (array_length (a1), array_size (a1));
  if (array_null (a2))
    return NULL;
  /** @endcode */

  /**
   * @note Copy the real array using the previously defined functions.
   */
  /** @code */
  for (i = 0; i < array_length (a1); i++)
    if (!array_memcopy (a2, i, array_indexpointer (a1, i)))
      return NULL;
  /** @endcode */

  return a2;
}

bool
array_resize (Array a, int new_length)
{
  char *tmp;
  int memdiff;

  if (array_null (a))
    return NULL;

  /** @code */
  /*
   * Invalid new length.
   */
  if (new_length < 0)
    return false;
  /*
   * new_length is set to zero, so leave the ADT, but delete internal array.
   */
  else if (new_length == 0)
    {
      realarray_delete (a);
      return true;
    }
  /*
   * Same size as before, then do nothing.
   */
  else if (array_length (a) == new_length)
    return true;
  /*
   * Array's length != new_length, so realloc can now be used directly.
   */
  else
    {
      /*
       * Safe realloc (to avoid losing the stored array if realloc fails).
       */
      tmp =
	realloc (array_pointer (a),
		 array_fullsize (a) +
		 (array_size (a) * ((size_t) new_length)));
      if (!element_null (tmp))
	a->ptr = tmp;
      else
	return false;
      /*
       * memset to 0 new part of the array.
       * To do this we must go to the first byte of the new array and put 0
       * until we get to (memdiff * a->size) bytes.
       */
      memdiff = new_length - array_length (a);
      if (memdiff > 0)
	memset (array_pointer (a) + array_fullsize (a) + array_size (a), 0,
		((size_t) memdiff) * array_size (a));

      /*
       * Set the new array length.
       */
      a->nmemb = new_length;
    }

  return true;
  /** @endcode */
}

/**
 * @note This function alters the input.
 */
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

  /**
   * @note Copy *element int *element_copy.
   */
  /** @code */
  element = array_indexpointer (a, initial_length - 1);
  element_copy = malloc (array_size (a));
  memcpy (element_copy, element, array_size (a));
  /** @endcode */

  if (!element_null (element_copy) && array_resize (a, initial_length - 1))
    return element_copy;
  else
    return NULL;
}

Array
array_merge (Array a1, Array a2)
{
  Array new_array;
  int i, j, total_length = array_length (a1) + array_length (a2);

  /**
   * @note Safety controls.
   */
  /** @code */
  if ((array_null (a1) && array_null (a2)) || (array_size (a1) !=
					       array_size (a2)))
    return NULL;
  /** @endcode */

  new_array = array_new (total_length, array_size (a1));
  if (array_null (new_array))
    return NULL;

  for (i = 0; i < array_length (a1); i++)
    if (!array_memcopy (new_array, i, array_indexpointer (a1, i)))
      return NULL;
  j = 0;
  for (i = array_length (a1); i < total_length; i++)
    {
      if (!array_memcopy (new_array, i, array_indexpointer (a1, j)))
	return NULL;
      j++;
    }

  return new_array;
}
