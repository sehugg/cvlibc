.PHONY: all clean libcv libcvu

CC = sdcc
MAX_ALLOCS_PER_NODE=10000
EXTRACFLAGS =
AS = sdasz80
SDCCLIB = sdcclib

all: libcv libcvu
	cp libcv/bin/* bin/
	cp -r libcv/include/* include/
	cp libcvu/bin/* bin/
	cp libcvu/include/* include/

libcv:
	$(MAKE) MAX_ALLOCS_PER_NODE=$(MAX_ALLOCS_PER_NODE) CC=$(CC) EXTRACFLAGS="$(EXTRACFLAGS)" AS=$(AS) SDCCLIB=$(SDCCLIB) -C libcv

libcvu:
	$(MAKE) MAX_ALLOCS_PER_NODE=$(MAX_ALLOCS_PER_NODE) CC=$(CC) EXTRACFLAGS="$(EXTRACFLAGS)" AS=$(AS) SDCCLIB=$(SDCCLIB) -C libcvu

clean:
	$(MAKE) -C libcv clean
	$(MAKE) -C libcvu clean
	rm -f *~ ./bin/*
	rm -rf ./include/*

