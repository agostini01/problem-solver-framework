AM_CXXFLAGS = $(WARN_CXXFLAGS)

SUBDIRS = \
	core \
	util

bin_PROGRAMS = main

main_SOURCES = main.cpp

LDADD = \
    ../lib/cpp/libcpp.a \
	\
	./util/libprogramutil.a \
	\
    ./core/binpacking/libbinpacking.a \
	./core/libprogramcore.a 
