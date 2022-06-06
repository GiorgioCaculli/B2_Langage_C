AC_PREREQ([2.69])

AC_INIT([langage_c], [1.0], [la196672@student.helha.be], [https://connected.helha.be/mod/resource/view.php?id=240109])

AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror 1.16])

AC_USE_SYSTEM_EXTENSIONS

AC_PROG_CC([cc clang gcc])

AC_PROG_RANLIB

AM_PROG_AR

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/app/Makefile
    src/app/app4/Makefile
    src/app/app5/Makefile
    src/app/app6/Makefile
    src/app/app7/Makefile
])

AC_CONFIG_LINKS([
    classement.dat:data/classement.dat
    journee.dat:data/journee.dat
    cstruc001.dat:data/cstruc001.dat
    cstruc002.dat:data/cstruc002.dat
    etudiants.dat:data/etudiants.dat
    points.dat:data/points.dat
    liste.dat:data/liste.dat
    cinema.dat:data/cinema.dat
])

LIBS="$LIBS $PTHREAD_LIBS"
CFLAGS="$CFLAGS $PTHREAD_CFLAGS"

AC_OUTPUT
