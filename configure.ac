AC_INIT([thirdpartylibs], [0.0.1])
AC_CONFIG_AUX_DIR([scripts])
AM_INIT_AUTOMAKE([1.9 foreign])


AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL

AM_PROG_LIBTOOL
AC_PROG_LIBTOOL

AC_PATH_XTRA

AC_CHECK_LIB(m, sqrt)
AC_CHECK_LIB(pthread, pthread_create)
AC_CHECK_LIB(tiff, TIFFOpen, TIFF_LIBS="-ltiff" , , -lm)
AC_SUBST([TIFF_LIBS])

AC_CONFIG_FILES([Makefile
                 cgats/Makefile
				 numlib/Makefile
				 rspl/Makefile])
AC_OUTPUT

