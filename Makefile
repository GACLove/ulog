CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-g
LDLIBS=

SRCS=example.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: example

example: $(OBJS)
	g++ $(LDFLAGS) -o example $(OBJS) $(LDLIBS)

example.o: example.cc ulog.hh

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) example
