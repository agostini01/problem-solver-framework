AM_CPPFLAGS = -isystem $(top_srcdir)/lib/gtest/include -I$(top_srcdir)/src $(GTEST_CPPFLAGS)
AM_CXXFLAGS = $(GTEST_CXXFLAGS)
AM_LDFLAGS = $(GTEST_LDFLAGS) $(GTEST_LIBS) \
	     $(top_srcdir)/lib/gtest/lib/libgtest_main.la \
	     $(top_srcdir)/lib/gtest/lib/libgtest.la

# TESTS -- Programs run automatically by "make check"
# check_PROGRAMS -- Programs built by "make check" but not necessarily run
TESTS =
check_PROGRAMS =

TESTS += testing
check_PROGRAMS += testing
testing_SOURCES = testing.cpp
testing_LDADD = $(top_srcdir)/src/util.o
