CC = sdcc
MAX_ALLOCS_PER_NODE=10000
CFLAGS = --std-c99 -mz80 -c -Iinclude/ -I../libcv/include --opt-code-size --fverbose-asm --max-allocs-per-node $(MAX_ALLOCS_PER_NODE)  $(EXTRACFLAGS)
CFLAGSS = $(CFLAGS) -DCV_SMS
AS = sdasz80
AFLAGS = -plosgff
SDCCLIB = sdcclib
.PHONY: clean all

srcdir = ./src

all: bin/libcvu.lib bin/libcvu-sms.lib

CVU_INOBJ = src/cvu_get_spinner.rel
CVU_GRAOBJ = src/cvu_set_sprite_xy.rel src/cvu_memtovmemcpy.rel src/cvu_vmemtomemcpy.rel src/cvu_vmemset.rel src/cvu_voutb.rel src/cvu_vinb.rel
CVU_SOOBJ = src/cvu_play_music.rel src/cvu_init_music.rel src/cvu_tuning_iso16_equal.rel src/cvu_tuning_scientific_equal.rel
CVU_COMOBJ = src/cvu_init_huffman.rel src/cvu_init_rle.rel src/cvu_get_rle.rel src/cvu_init_lzk.rel src/cvu_get_lzk.rel src/cvu_get_huffman.rel src/cvu_compression.rel src/cvu_memcpy_compression.rel src/_read_from_array.rel
CVU_FOBJ = src/cvu_fmul2.rel src/cvu_fdiv2.rel src/cvu_fsincos.rel src/cvu_fatan.rel src/_u_16_16_mul.rel
CVU_COBJ = src/cvu_c.rel src/cvu_cmul.rel src/cvu_cabs.rel src/cvu_c_from_polar.rel

CVOBJ = $(CVU_INOBJ) $(CVU_GRAOBJ) $(CVU_SOOBJ) $(CVU_COMOBJ) $(CVU_FOBJ) $(CVU_COBJ) src/cvu_set_sprite_x.rel src/cvu_get_sprite_x.rel src/cvu_set_sprite_y.rel src/cvu_get_sprite_y.rel src/cvu_get_sprite_color.rel
SMSOBJ = $(CVU_GRAOBJ:.rel=-sms.rel) $(CVU_SOOBJ) $(CVU_COMOBJ) $(CVU_FOBJ) $(CVU_COBJ) src/cvu_set_sprite_x.rel src/cvu_get_sprite_x.rel src/cvu_set_sprite_y.rel src/cvu_get_sprite_y.rel src/cvu_get_sprite_color.rel src/cvu_memtocmemcpy-sms.rel

bin/libcvu.lib: $(CVOBJ)
	rm -rf bin/libcvu.lib; $(SDCCLIB) bin/libcvu.lib $(CVOBJ)
bin/libcvu-sms.lib: $(SMSOBJ)
	rm -rf bin/libcvu-sms.lib; $(SDCCLIB) bin/libcvu-sms.lib $(SMSOBJ)

src/%.rel: src/%.c include/cvu.h include/cvu_compression.h  include/cvu_f.h  include/cvu_graphics.h  include/cvu.h  include/cvu_input.h include/cvu_sound.h
	$(CC) $(CFLAGS) $< -o $@
src/%-sms.rel: src/%.c
	$(CC) $(CFLAGSS) $< -o $@

src/cvu_set_sprite_x.rel: src/cvu_set_sprite_x.s
	cd src; $(AS) $(AFLAGS) cvu_set_sprite_x.s
src/cvu_get_sprite_x.rel: src/cvu_get_sprite_x.s
	cd src; $(AS) $(AFLAGS) cvu_get_sprite_x.s
src/cvu_set_sprite_y.rel: src/cvu_set_sprite_y.s
	cd src; $(AS) $(AFLAGS) cvu_set_sprite_y.s
src/cvu_get_sprite_y.rel: src/cvu_get_sprite_y.s
	cd src; $(AS) $(AFLAGS) cvu_get_sprite_y.s

src/cvu_get_huffman.rel: src/cvu_get_huffman.s
	cd src; $(AS) $(AFLAGS) cvu_get_huffman.s
src/cvu_get_rle.rel: src/cvu_get_rle.s
	cd src; $(AS) $(AFLAGS) cvu_get_rle.s
src/_read_from_array.rel: src/_read_from_array.s
	cd src; $(AS) $(AFLAGS) _read_from_array.s

src/_u_16_16_mul.rel: src/_u_16_16_mul.s include/cvu_f.h
	cd src; $(AS) $(AFLAGS) _u_16_16_mul.s

src/cvu_cmul.rel: src/cvu_cmul.s
	cd src; $(AS) $(AFLAGS) cvu_cmul.s

clean:
	rm -f src/*.rel src/*.lst src/*.sym src/*.asm src/*.rel */*~ ./*~ bin/*.rel bin/*.lib *~

