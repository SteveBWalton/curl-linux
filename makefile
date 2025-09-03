#
# Makefile for the curl-test program.
#
# Little program to test C++ curl library in Linux.
#

#
# The processor that this computer is using
#
PROCESSOR = $(shell uname -m)

#
# Libraries
# 	prefix LIBS with -l
# 	prefix LIBDIR with -L
#
LIBS :=
LIBDIR :=

OPTIONS := -Wall -std=c++17

#
# Header files.
#
HEADERS := curl-test.o

#
# Source objects (prefix with obj/)
#
OBJS := \
obj/curl-test.o \
obj/http-simple.o

bin/curl-test : $(OBJS)
	@mkdir -p $(@D)
	g++ $(OPTIONS) -o bin/curl-test $(OBJS) $(LIBDIR) $(LIBS)

obj/curl-test.o : curl-test.cpp $(HEADERS)
	@mkdir -p $(@D)
	g++ -c $(OPTIONS) -o obj/curl-test.o curl-test.cpp

obj/http_simple.o : http-simple.cpp $(HEADERS)
	@mkdir -p $(@D)
	g++ -c $(OPTIONS) -o obj/http-simple.o http-simple.cpp


clean:
	-rm -f bin/curl-test
	-rm -f $(OBJS)

