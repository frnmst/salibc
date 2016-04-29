# salibc
Simple Array C Library

##Documentation

The methods accessible to the user (the non `static` ones) are the ones 
described in `salibc.h`.

The first thing to do i to move to the `src` directory:
```
$ cd src
```

To generate the documentation, you need to install the following packages:
```
doxygen
texlive-core
texlive-latexextra
```

These are the names under Parabola GNU/Linux-libre distro. 

You can then execute the following if you are only interested in the HTML form:
```
$ make doxygen
```

Or, if you want a pdf file (`../refman.pdf`):
```
$ make doxygenlatex
```

You can also remove the whole documentation like this:
```
$ make cleandoxygen
```

The doxygen configuration file has been generated with the following:
```
$ doxygen -g doxy.conf
```

where `doxy.conf` was edited with the options I thought were useful.

##Test

You can test the library with the following:
```
$ make
```

This will generate an executable file called `salibc.out`.

##Other

`indent` and `clean` targets are also available as part of the make file.

To be able to use the `indent` target, you need to install `indent` and 
`splint` packages.

# License
![https://www.gnu.org/graphics/gplv3-127x51.png](https://www.gnu.org/graphics/gplv3-127x51.png)

Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com> 
<franco.masotti@student.unife.it>

salibc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
