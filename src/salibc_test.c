/**
 * @file salibc_test.c
 * @author Franco Masotti
 * @date 28 Apr 2016
 * @brief Test file
 */

/*
 * salibc_test.c
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
 * @brief if this flag is defined then the main function in this file is
 * included.
 */
#if defined (SALIBC_TEST) || DOXYGEN

/**
 * @note Use:
 * const MYVARIABLE = value
 * instead of:
 * value
 * or
 * #define MYVAR value
 * in your code.
 */
int
main (void)
{

  int i;
  Array arr0, arr1, arr2, arr3, arr4, arr5;
  char a = 'f';
  int b = 421;
  double c = 3223.554;
  long double d = 123423509.99999999, e = 1435.654;

  arr0 = array_new (50, sizeof (char));
  arr1 = array_new (50, sizeof (int));
  arr2 = array_new (50, sizeof (double));
  arr3 = array_new (50, sizeof (long double));

  array_put (arr0, 20, &a);
  array_put (arr1, 21, &b);
  array_put (arr2, 22, &c);
  array_put (arr3, 23, &d);

  printf ("%c\n", *((char *) array_get (arr0, 20)));
  printf ("%d\n", *((int *) array_get (arr1, 21)));
  printf ("%f\n", *((double *) array_get (arr2, 22)));
  printf ("%.9Lf\n", *((long double *) array_get (arr3, 23)));

  array_append (arr0, &a);
  array_append (arr0, &a);
  array_append (arr0, &a);
  printf ("%c\n", *((char *) array_get (arr0, 50)));
  printf ("%c\n", *((char *) array_get (arr0, 51)));
  printf ("%c\n", *((char *) array_get (arr0, 52)));

  printf ("%c\n", *((char *) array_trim (arr0)));
  printf ("%c\n", *((char *) array_trim (arr0)));
  printf ("%c\n", *((char *) array_trim (arr0)));
  printf ("null char: %c\n", *((char *) array_trim (arr0)));

  array_resize (arr2, 0);
  if (array_empty (arr2))
    printf ("arr2's length is now equal to zero\n");

  arr4 = array_new (3, sizeof (long double));
  array_put (arr4, 0, &d);
  array_put (arr4, 1, &d);
  array_put (arr4, 2, &e);

  printf ("Length before merge = %d\n", array_length (arr3));
  if (array_null (arr5 = array_merge (arr3, arr4)))
    printf ("Merge failed.\n");
  printf ("Length after merge = %d\n", array_length (arr5));

  for (i = 0; i < array_length (arr4); i++)
    printf ("%Lf\n", *((long double *) array_get (arr4, i)));

  if (*((long double *) array_get (arr4, 1)) >
      *((long double *) array_get (arr4, 2)))
    printf ("%Lf is greater than %Lf\n",
	    *((long double *) array_get (arr4, 1)),
	    *((long double *) array_get (arr4, 2)));

  return 0;
}

#endif
