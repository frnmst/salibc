#include "salibc.h"

#ifdef SALIBC_TEST

int main (void )
{

    Array arr0, arr1, arr2, arr3;
    char a = 'f';
    int b = 421;
    double c = 3223.554;
    long double d=123423509.99999999;

    arr0 = array_new ( 50, sizeof ( char ) );
    arr1 = array_new ( 50, sizeof ( int ) );
    arr2 = array_new ( 50, sizeof ( double ) );
    arr3 = array_new ( 50, sizeof ( long double ) );

    array_put ( arr0, 20, &a );
    array_put ( arr1, 21, &b );
    array_put ( arr2, 22, &c );
    array_put ( arr3, 23, &d );

    printf ( "%c\n", * ((char *) array_get ( arr0, 20 ) ) );
    printf ( "%d\n", * ((int *) array_get ( arr1, 21 ) ) );
    printf ( "%f\n", * ((double *) array_get ( arr2, 22 ) ) );
    printf ( "%.9Lf\n", * ((long double *) array_get ( arr3, 23 ) ) );

    array_append ( arr0, &a );
    array_append ( arr0, &a );
    array_append ( arr0, &a );
    printf ( "%c\n", * ((char *) array_get ( arr0, 50 ) ) );
    printf ( "%c\n", * ((char *) array_get ( arr0, 51 ) ) );
    printf ( "%c\n", * ((char *) array_get ( arr0, 52 ) ) );

    printf ( "%c\n", * ((char *) array_trim ( arr0 ) ) );
    printf ( "%c\n", * ((char *) array_trim ( arr0 ) ) );
    printf ( "%c\n", * ((char *) array_trim ( arr0 ) ) );
    printf ( "null char: %c\n", * ((char *) array_trim ( arr0 ) ) );

    array_resize ( arr2, 0 );
    if ( array_empty ( arr2 ) )
        printf ("arr2's length is now equal to zero\n");

    return 0;
}

#endif
