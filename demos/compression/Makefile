CC = sdcc
CFLAGS = -mz80 -c "-I../../include/" --std-c99
CFLAGS-SMS = $(CFLAGS) -DCV_SMS
SED = sed
PNG2CV = png2cv #Make this ../../../png2cv/png2cv or whatever if png2cv is not in path.

.PHONY: all clean

all: compression.rom compression.sms

compression.rom: main.rel picture.color.rel picture.pattern.rel huffman_tree.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x8100 --data-loc 0x7000 ../../bin/libcvu.lib ../../bin/libcv.lib ../../bin/crt0.rel main.rel picture.color.rel picture.pattern.rel huffman_tree.rel -o compression.ihx; objcopy --input-target=ihex --output-target=binary compression.ihx compression.rom
compression.sms: main-sms.rel picture.color.rel picture.pattern.rel huffman_tree.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x0100 --data-loc 0xc000 ../../bin/libcvu-sms.lib ../../bin/libcv-sms.lib ../../bin/crt0-sms.rel main-sms.rel picture.color.rel picture.pattern.rel huffman_tree.rel -o compression-sms.ihx; objcopy --input-target=ihex --output-target=binary compression-sms.ihx compression.sms

main.rel: main.c rle_escape.h
	$(CC) $(CFLAGS) main.c -o main.rel
main-sms.rel: main.c rle_escape.h
	$(CC) $(CFLAGS-SMS) main.c -o main-sms.rel

huffman_tree.rel: huffman_tree.c
	$(CC) $(CFLAGS) huffman_tree.c
picture.color.rel: picture.color.c
	$(CC) $(CFLAGS) picture.color.c
picture.color.c: picture.png.color.bin.rle.c
	$(SED) -e 's/data\[\]/color\[\]/' picture.png.color.bin.rle.c > picture.color.c
picture.pattern.rel: picture.pattern.c
	$(CC) $(CFLAGS) picture.pattern.c
picture.pattern.c: picture.png.pattern.bin.rle.c
	$(SED) -e 's/data\[\]/pattern\[\]/' picture.png.pattern.bin.rle.c > picture.pattern.c
picture.png.color.bin.rle.c: huffman_encoder picture.png.color.bin.rle
	./huffman_encoder picture.png.color.bin.rle
picture.png.pattern.bin.rle.c: huffman_encoder picture.png.pattern.bin.rle
	./huffman_encoder picture.png.pattern.bin.rle
huffman_encoder: huffman_encoder_tree.o
	g++ -Wall -I../../../compression/ -o huffman_encoder ../../../compression/huffman_encoder.cc huffman_encoder_tree.o
huffman_encoder_tree.o: huffman_tree.c
	gcc --std=c99 -Wall -I../../../compression/ -o huffman_encoder_tree.o -c huffman_tree.c
huffman_tree.c: picture.png.color.bin.rle picture.png.pattern.bin.rle
	../../../compression/huffman_analyzer picture.png.color.bin.rle picture.png.pattern.bin.rle
picture.png.color.bin.rle: rle_encoder picture.png.color.bin
	./rle_encoder picture.png.color.bin
picture.png.pattern.bin.rle: rle_encoder picture.png.pattern.bin
	./rle_encoder picture.png.pattern.bin
rle_encoder: rle_escape.h
	gcc --std=c99 -Wall -I. -o rle_encoder ../../../compression/rle_encoder.c
rle_escape.h: picture.png.color.bin picture.png.pattern.bin
	../../../compression/rle_analyzer picture.png.color.bin picture.png.pattern.bin
picture.png.color.bin: picture.png
	$(PNG2CV) --binary picture.png
picture.png.pattern.bin: picture.png
	$(PNG2CV) --binary picture.png

clean:
	rm -f *.rel *.map *.lst *.lnk *.lk *.sym *.asm *~ *.o *.rel *.noi *.ihx *.sprite.* *.pattern.* *.color.* huffman* rle*

