# Bin Paking Solver
=======================

Given a set of objects with sizes and an integer K, can the objects be placed
into K subsets of fixed size?

## Depends
-------

- C++ compiler
- Autoconf
- Automake
- Libtool

## Build
-----

In order to compile the project:

    autoreconf -ivf
	cd build
    ../configure
    make

Run the tests with

    make check

Author: Nicolas Agostini <n.b.agostini@gmail.com>
Author: Matan Kaminski <kaminski.ma@husky.neu.edu>
Jan 2017
