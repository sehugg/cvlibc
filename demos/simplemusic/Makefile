CC = sdcc
CFLAGS = -mz80 -c "-I../../include/" --std-c99
CFLAGS-SMS = $(CFLAGS) -DCV_SMS
ABC2CVM = abc2cvm -v

.PHONY: all clean

all: Music.rom Music.sms

Music.rom: main.rel downbytheriverside.abc.music.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x8100 --data-loc 0x7000 ../../bin/libcvu.lib ../../bin/libcv.lib ../../bin/crt0.rel main.rel downbytheriverside.abc.music.rel -o Music.ihx; objcopy --input-target=ihex --output-target=binary Music.ihx Music.rom

Music.sms: main-sms.rel downbytheriverside.abc.music.rel
	$(CC) -mz80 --no-std-crt0 --code-loc 0x0100 --data-loc 0xc000 ../../bin/libcvu-sms.lib ../../bin/libcv-sms.lib ../../bin/crt0-sms.rel main-sms.rel downbytheriverside.abc.music.rel -o Music-sms.ihx; objcopy --input-target=ihex --output-target=binary Music-sms.ihx Music.sms

main.rel: main.c
	$(CC) $(CFLAGS) main.c

main-sms.rel: main.c
	$(CC) $(CFLAGS-SMS) main.c -o main-sms.rel

downbytheriverside.abc.music.rel: downbytheriverside.abc.music.c
	$(CC) $(CFLAGS) downbytheriverside.abc.music.c

downbytheriverside.abc.music.c: downbytheriverside.abc
	$(ABC2CVM) downbytheriverside.abc

clean:
	rm -f *.rel *.map *.lst *.lnk *.lk *.sym *.asm *~ *.o *.rel *.noi *.ihx *.abc.music.c

