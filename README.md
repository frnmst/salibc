# salibc
Simple Array C Library

##Documentation

The methods accessible to the user (the non `static` ones) are the ones 
described in `salibc.h`.

To generate the ducumentation, you need to install `doxygen`, `texlive-core` 
and `texlive-latexextra` (these are the names under Parabola GNU/Linux-libre 
distro). 

You can then execute the following:
```
$ cd src && make doxygen && cd latex && make
```

This will generate both LaTeX (`src/latex/refman.pdf`) and HTML 
(`src/html/index.html`) documentation. 

If you are only interested in the HTML form you don't need to install the 
LaTeX packages.

The doxygen configuration file has been generated with the following:
```
$doxygen -g doxy.conf
```

and then edited with the options I thought were useful.

##Test

You can test the library with the following:
```
$ cd src && make
```

This will generate an executable file called `salibc.out`.

##Other

`indent` and `clean` targets are also available as part of the make file.
To be able to use the `indent` target, you need to install `indent` and 
`splint`.

# License
![https://www.gnu.org/graphics/gplv3-127x51.png](https://www.gnu.org/graphics/gplv3-127x51.png)

Copyright (C) 2016 frnmst (Franco Masotti) <franco.masotti@live.com> 
<franco.masotti@student.unife.it>

salibc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
