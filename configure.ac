AC_PREREQ([2.68])
AC_INIT([Cinamo], [1.0], [nasda60___at___hotmail.com], [cinamo], [http://ledyba.org/])
AM_INIT_AUTOMAKE([1.10 no-define foreign])
AC_CONFIG_HEADERS([include/cinamo/Config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CC
CXXFLAGS=
CFLAGS=
AM_PROG_AS
AC_PROG_CPP
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AX_CHECK_COMPILE_FLAG([-std=gnu++11], [CXXFLAGS="$CXXFLAGS -std=gnu++11"])
AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
			   [enable debugging, default: no]),
	[case "${enableval}" in
				 yes) debug=true ;;
				 no)  debug=false ;;
				 *)    AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

# Initialize libtool
LT_PATH_LD
LT_LIB_DLLOAD
LT_PREREQ([2.4])
LT_INIT([win32-dll disable-fast-install])
LT_LANG([C++])

AC_DEFUN([PKG_CHECK_MODULES_STATIC],
[
	AC_REQUIRE([PKG_PROG_PKG_CONFIG])
	_save_PKG_CONFIG=$PKG_CONFIG
	PKG_CONFIG="$PKG_CONFIG --static"
	PKG_CHECK_MODULES([$1], [$2], [$3], [$4])
	PKG_CONFIG=$_save_PKG_CONFIG[]dnl
])

##---------------------------
## libs
##---------------------------
PKG_CHECK_MODULES_STATIC([ICU], [icu-uc icu-i18n], [AC_DEFINE([HAVE_ICU], [1],[HAVE ICU])], [])
ACX_PTHREAD([have_pthread=yes])
##---------------------------
## gtest
##---------------------------
GTEST_VERSION="1.7.0"
if test "x$have_pthread" = "xyes"; then
  GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=1"
  GTEST_CXXFLAGS="$PTHREAD_CFLAGS"
  GTEST_LDFLAGS=
  GTEST_LIBS="$PTHREAD_LIBS"
else
  GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=0"
  GTEST_CXXFLAGS=
  GTEST_LDFLAGS=
  GTEST_LIBS=
fi
AC_SUBST([GTEST_VERSION])
AC_SUBST([GTEST_CPPFLAGS])
AC_SUBST([GTEST_CXXFLAGS])
AC_SUBST([GTEST_LDFLAGS])
AC_SUBST([GTEST_LIBS])
##---------------------------

AC_SUBST(EXT_PKGS)
AC_SUBST(LIBS)
AC_CONFIG_FILES([Makefile
				 pkgconfig/libcinamo.pc
				 include/Makefile
				 src/Makefile
				 external/gtest/Makefile
				 test/Makefile])
AC_OUTPUT

AC_MSG_RESULT([
$PACKAGE $VERSION is now configured
Configure Information:
  C Compiler        : $CC
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CFLAGS          :   $CFLAGS

  C++ Compiler      : $CXX
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CXXFLAGS        :   $CXXFLAGS

  Linker            : $LD
    LDFLAGS         :   $LDFLAGS
    LIBS            :   $LIBS

  Google Test 
    GTEST_CPPFLAGS  : $GTEST_CPPFLAGS
    GTEST_CXXFLAGS  : $GTEST_CXXFLAGS
    GTEST_LDFLAGS   : $GTEST_LDFLAGS
    GTEST_LIBS      : $GTEST_LIBS
])