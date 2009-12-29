#
#
#

bin_PROGRAMS = glearning
glearning_SOURCES = common.hh common.cc \
	world.hh world.cc \
	prueba.hh prueba.cc

if DEBUG
glearning_CFLAGS = -Wall -g -pedantic
else
glearning_CFLAGS = -Wall -O2
endif

if LOG
glearning_CFLAGS += -v
endif



