AM_CFLAGS = -Wall -O2 -DUNIX -I../h -I../numlib -I../plot

noinst_LIBRARIES = librspl.a

librspl_a_SOURCES = rspl.h rspl_imp.h mlbs.h rspl.c scat.c rev.c rev.h spline.c opt.c

LDADD=./librspl.a ../numlib/libargyllnum.a ../plot/libplot.a $(X_LIBS) $(TIFF_LIBS)

EXTRA_DIST = License.txt Readme.txt
