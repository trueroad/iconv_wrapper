#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([One header file iconv wrapper for C++11],
    [2016-10-18.23], , [iconv_wrapper],
    [https://github.com/trueroad/iconv_wrapper/])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([advanced-sample.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for libraries.
AM_ICONV

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
