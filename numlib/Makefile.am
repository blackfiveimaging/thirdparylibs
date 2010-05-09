AM_CFLAGS = -Wall -O2 -DUNIX
AM_LDFLAGS = -lm

noinst_LTLIBRARIES = libargyllnum.la

libargyllnum_la_SOURCES = numlib.h numsup.c numsup.h dnsq.c dnsq.h powell.c powell.h \
	dhsx.c dhsx.h ludecomp.c ludecomp.h svd.c svd.h zbrent.c zbrent.h rand.c rand.h sobol.c sobol.h

LDADD=./libargyllnum.la
check_PROGRAMS = dnsqtest tpowell tdhsx LUtest svdtest zbrenttest soboltest

EXTRA_DIST = License.txt Readme.txt
