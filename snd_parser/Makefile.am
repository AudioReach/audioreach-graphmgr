pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sndparser.pc
EXTRA_DIST = $(pkgconfig_DATA)

AUTOMAKE_OPTIONS = subdir-objects

h_sources  = inc/snd-card-def.h

lib_include_HEADERS = $(h_sources)
lib_includedir = $(includedir)/sndparser/

AM_CFLAGS = -I $(srcdir)/inc -I $(top_srcdir)/service/inc/public
AM_CFLAGS += -Wno-unused-parameter
AM_CFLAGS += -DCARD_DEF_FILE=\"/etc/card-defs.xml\"
AM_CFLAGS += -DCARD_DEF_FILE_NATIVE=\"@CARD_DEF_FILE_NATIVE@\"
AM_CFLAGS += -Wl,-z,defs

lib_LTLIBRARIES      = libsndparser.la
libsndparser_la_SOURCES   = src/snd-card-parser.c
libsndparser_la_LIBADD = -lexpat -lpthread
libsndparser_la_LDFLAGS   = -shared -version-number @LT_VERSION_NUMBER@
libsndparser_la_CFLAGS = $(AM_CFLAGS)
if USE_GLIB
libsndparser_la_LIBADD += $(GLIB_LIBS)
libsndparser_la_CFLAGS += $(GLIB_CFLAGS) -include glib.h
endif
if USE_G_STR_FUNC
libsndparser_la_CFLAGS += -Dstrlcpy=g_strlcpy -Dstrlcat=g_strlcat
endif
