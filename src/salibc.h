/**
 * @file salibc.h
 * @author Franco Masotti
 * @date 28 Apr 2016
 * @brief Header file containing exportable methods.
 */

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

/**
 * @brief Tell the compiler that we want ISO C99 source, and check if the 
 * system has ANSI C 99.
 */
#define ISOC99_SOURCE
#if __STDC_VERSION__ != 199901L
#error "ANSI C99 not available"
#endif

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Array Abstract Data Type.
 */
typedef struct Array
{
  /**
   * @brief Size of a single element.
   *
   * This is expressed in bytes.
   */
  size_t size;
  /**
   * @brief Number of elements contained in the array.
   */
  int nmemb;
  /**
   * @brief Pointer to the array.
   *
   * Since pointer arithmetic cannot be done on void *, char * was the obvious
   * choice.
   */
  char *ptr;
} *Array;

/**
 * @brief Check if the array is NULL.
 *
 * @param[in] a The pointer to an array ADT instance.
 *
 * @retval true The array is NULL.
 * @retval false The array is not NULL.
 */
extern bool array_null (Array a);

/**
 * @brief Check if the array is empty.
 *
 * @param[in] a The pointer to an array ADT instance.
 *
 * @retval true The array is empty.
 * @retval false The array is not empty.
 *
 * When an array is empty, it means that it does not contain any element (i.e: 
 * its length is zero.
 */
extern bool array_empty (Array a);

/**
 * @brief Get the size in bytes of a single element of the array.
 *
 * @param[in] a The pointer to an array ADT instance.
 *
 * @retval a->size The size of the array.
 *
 * @pre a must not be NULL.
 */
extern size_t array_size (Array a);

/**
 * @brief Get the number of elements contained in the array.
 *
 * @param[in] a The pointer to an array ADT instance.
 *
 * @retval a->nmemb The length of the array.
 *
 * @pre a must not be NULL.
 */
extern int array_length (Array a);

/**
 * @brief Get the size in bytes of all the elements of the array.
 *
 * @param[in] a The pointer to an array ADT instance.
 *
 * @retval array_size(a)*array_length(a) The total size in bytes of the 
 * array.
 *
 * @pre a must not be NULL.
 */
extern size_t array_fullsize (Array a);

/**
 * @brief Get the memory address of the first element of the array.
 *
 * @param[in] a The pointer to an array ADT instance.
 *
 * @retval a->ptr The pointer to the first element of the array.
 */
extern char *array_pointer (Array a);

/**
 * @brief Check if two arrays are equal.
 *
 * @param[in] a1 The pointer to the first array ADT instance.
 * @param[in] a2 The pointer to the second array ADT instance.
 *
 * @retval true The two arrays are equal.
 * @retval false The two arrays differ.
 */
extern bool array_equal (Array a1, Array a2);

/**
 * @brief Delete the ADT instance of the array.
 *
 * @param[in] a_ref The memory address of the variable containing the pointer
 * to the array ADT instance.
 */
extern void array_delete (Array * a_ref);

/**
 * @brief Create a new array ADT instance. This is also known as the
 * constructor.
 *
 * @param[in] nmemb The length of the array.
 * @param[in] size The size of each element, in bytes.
 *
 * @retval new_array A pointer to the new array ADT instance.
 *
 * @warning The return value can also be NULL if some problem occurred.
 */
extern Array array_new (int nmemb, size_t size);

/**
 * @brief Insert an element into an array ADT instance.
 *
 * @param[in] a The pointer to an array ADT instance.
 * @param[in] index The index of the array where to store the element.
 * @param[in] element A memory address of the element to be inserted.
 *
 * @retval true The element has been inserted correctly.
 * @retval false Some problem occurred and insertion failed.
 */
extern bool array_put (Array a, int index, void *element);

/**
 * @brief Set the whole array with the same element.
 *
 * @param[in] a The pointer to an array ADT instance.
 * @param[in] element A memory address of the element to be inserted.
 *
 * @retval true The entire array has been set correctly.
 * @retval false Some problem occurred and insertion in one of the
 * array's index failed.
 *
 * @warning This function may leave an undefined state of the array.
 */
extern bool array_set (Array a, void *element);

/**
 * @brief Get the memory address corresponding to a specified index of the
 * array.
 *
 * @param[in] a The pointer to an array ADT instance.
 * @param[in] index The index of the array where to get the element.
 *
 * @retval array_indexpointer() A memory address corresponding to the input
 * index.
 *
 * @warning This function may return NULL if some problem occured.
 *
 * @note If you dereference the return value with the correct pointer type you
 * get the real value value that can be used in arthmetics and printing.
 */
extern char *array_get (Array a, int index);

/**
 * @brief Get a copy of the specified array ADT.
 *
 * @param[in] a1 The pointer to an array ADT instance.
 *
 * @retval a2 The pointer to the new array ADT istance.
 *
 * @warning This function may return NULL if some problem occured.
 */
extern Array array_copy (Array a1);

/**
 * @brief Resize an array to a new specified length.
 *
 * @param[in] a The pointer to an array ADT instance.
 * @param[in] new_length The new length of the array.
 *
 * @retval true Array resize successful.
 * @retval false Array resize unsuccessful.
 */
extern bool array_resize (Array a, int new_length);

/**
 * @brief Append (add on the tail) a new element on the array.
 *
 * @param[in] a The pointer to an array ADT instance.
 * @param[in] element A memory address of the element to be inserted.
 *
 * @retval true Array append successful.
 * @retval false Array append unsuccessful.
 */
extern bool array_append (Array a, void *element);

/**
 * @brief Get the last element of the array and remove the last position from 
 * it .
 *
 * @param[in] a The pointer to an array ADT instance.
 *
 * @retval element_copy A pointer to the value that was in the last array 
 * index.
 *
 * @warning The return value can also be NULL if some problem occurred.
 */
extern char *array_trim (Array a);

/**
 * @brief Merge two arrays in a new array.
 *
 * @param[in] a1 The pointer the first array ADT instance.
 * @param[in] a2 The pointer the second array ADT instance.
 *
 * @retval a2 The pointer to the new array ADT istance.
 *
 * @warning This function may return NULL if some problem occured.
 */
extern Array array_merge (Array a1, Array a2);

#endif
