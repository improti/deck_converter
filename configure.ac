# deck_converter$ aclocal ; automake -a ; autoconf ; ./configure ; make

AC_PREREQ([2.69])
AC_INIT([deck_converter], [0.1], [zarku@gmx.net])
AM_INIT_AUTOMAKE([-Wall])

AC_MSG_NOTICE([Checking for components to compile deck_converter.])

AC_LANG(C++)
AC_PROG_CXX
AC_PROG_CC

AC_CHECK_HEADER_STDBOOL
#AC_CHECK_LIB([dl], [main])
AC_CHECK_LIB([sqlite3], [sqlite3_open])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
