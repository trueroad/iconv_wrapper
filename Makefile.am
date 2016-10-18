bin_PROGRAMS = simple-sample advanced-sample
simple_sample_SOURCES = simple-sample.cc iconv_wrapper.hh
advanced_sample_SOURCES = advanced-sample.cc iconv_wrapper.hh

LDADD = $(LIBICONV)

dist_doc_DATA = README.md README.ja.md LICENSE
EXTRA_DIST = config.rpath autogen.sh

ACLOCAL_AMFLAGS = -I m4

install:
	echo Files can not be installed.
	echo Please copy iconv_wrapper.hh to your project directory.
	exit 1
