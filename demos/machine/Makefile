CC = sdcc
CVLIBPATH = "../.."
CFLAGS = --opt-code-size --fverbose-asm --std-c99 -mz80 -c -I$(CVLIBPATH)/include/
CFLAGS-SMS = $(CFLAGS) -DCV_SMS
SED = sed
PNG2CV = png2cv

.PHONY: all clean

all: Machine.rom Machine.sms Machine.sc Machine.sg

Machine.rom: main.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x8100 --data-loc 0x7000 $(CVLIBPATH)/bin/libcvu.lib ../../bin/libcv.lib ../../bin/crt0.rel main.rel -o Machine.ihx; objcopy --input-target=ihex --output-target=binary Machine.ihx Machine.rom
Machine.sms: main-sms.rel tiles.png.pattern.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x0100 --data-loc 0xc000 $(CVLIBPATH)/bin/libcvu-sms.lib ../../bin/libcv-sms.lib ../../bin/crt0-sms.rel main-sms.rel tiles.png.pattern.rel -o Machine-sms.ihx; objcopy --input-target=ihex --output-target=binary Machine-sms.ihx Machine.sms
Machine.sc: Machine.sms
	ln -s $< $@
Machine.sg: Machine.sms
	ln -s $< $@

main.rel: main.c
	$(CC) $(CFLAGS) main.c
main-sms.rel: main.c
	$(CC) $(CFLAGS-SMS) main.c -o main-sms.rel

tiles.png.pattern.rel: tiles.png.pattern.c
	$(CC) $(CFLAGS-SMS) tiles.png.pattern.c
tiles.png.pattern.c: tiles.png
	$(PNG2CV) tiles.png

clean:
	rm -f *.rel *.map *.lst *.lnk *.lk *.sym *.asm *~ *.o *.rel *.noi *.ihx

