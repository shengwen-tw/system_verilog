PROCESSOR_H = ./386-GCC.h
SOFTFLOAT_MACROS = ./softfloat-macros

EXECUTABLE = pg
CC = gcc
CFLAGS=-I. -I.. -iquote -O2

build: softfloat.o $(EXECUTABLE)

softfloat.o: milieu.h softfloat.h softfloat-specialize $(SOFTFLOAT_MACROS) ./softfloat.c
	$(CC) -c -o $@ $(CFLAGS) ./softfloat.c

fptpg.o: milieu.h softfloat.h ./fptpg.c
	$(CC) -c -o $@ $(CFLAGS) ./fptpg.c

$(EXECUTABLE): softfloat.o fptpg.o
	$(CC) -o $@ softfloat.o fptpg.o

clean:
	rm -rf $(EXECUTABLE) softfloat.o fptpg.o
