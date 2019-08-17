CC = sdcc
MAX_ALLOCS_PER_NODE=10000
CFLAGS = --std-c99 -mz80 -c -Iinclude --opt-code-size --fverbose-asm --max-allocs-per-node $(MAX_ALLOCS_PER_NODE) $(EXTRACFLAGS)
CFLAGSS = $(CFLAGS) -DCV_SMS
AS = sdasz80
AFLAGS = -plosgff
SDCCLIB = sdcclib
.PHONY: clean all

srcdir = ./src

all: bin/libcv.lib bin/crt0.rel bin/libcv-sms.lib bin/crt0-sms.rel
	
GENOBJ = src/cv_init.rel src/cv_vint.rel src/cv_vdpout.rel src/cv_get_vint_handler.rel src/cv_set_vint_handler.rel src/cv_get_vint_frequency.rel src/cv_get_machine.rel src/cv_machine_config.rel src/cv_get_r.rel
INOBJ = src/cv_get_controller_state.rel src/cv_set_spint_handler.rel
GRAOBJ = src/cv_get_external_video.rel src/cv_set_external_video.rel src/cv_get_screen_active.rel src/cv_set_screen_active.rel src/cv_get_screen_mode.rel src/cv_set_screen_mode.rel src/cv_get_sprite_big.rel src/cv_set_sprite_big.rel src/cv_get_sprite_collission.rel src/cv_get_sprite_invalid.rel src/cv_get_sprite_magnification.rel src/cv_set_sprite_magnification.rel src/cv_set_character_pattern_table.rel src/cv_set_color_table.rel src/cv_set_colors.rel src/cv_set_image_table.rel src/cv_set_sprite_attribute_table.rel src/cv_set_sprite_pattern_table.rel src/cv_set_read_vram_address.rel src/cv_set_write_vram_address.rel src/cv_memtovmemcpy_slow.rel src/cv_vmemtomemcpy_slow.rel src/cv_vmemset_slow.rel src/cv_memtovmemcpy_fast.rel src/cv_vmemtomemcpy_fast.rel src/cv_vmemset_fast.rel src/cv_voutb.rel src/cv_vinb.rel
SOOBJ = src/cv_set_attenuation.rel src/cv_set_frequency.rel src/cv_set_noise.rel
OBJ = $(GENOBJ) $(INOBJ) $(GRAOBJ) $(SOOBJ)
OBJ-SMS = $(OBJ:.rel=-sms.rel) src/cv_set_write_cram_address-sms.rel src/cv_set_left_column_blank-sms.rel src/cv_set_sprite_shift.rel src/cv_set_scroll_inhibit-sms.rel src/cv_set_hscroll-sms.rel src/cv_set_vscroll-sms.rel

bin/libcv.lib: $(OBJ)
	rm -f bin/libcv.lib; $(SDCCLIB) bin/libcv.lib $(OBJ)

bin/libcv-sms.lib: $(OBJ-SMS)
	rm -f bin/libcv-sms.lib; $(SDCCLIB) bin/libcv-sms.lib $(OBJ-SMS)

bin/crt0.rel: src/crt0.rel
	cp src/crt0.rel bin/
bin/crt0-sms.rel: src/crt0-sms.rel
	cp src/crt0-sms.rel bin/

src/crt0.rel: src/crt0.s
	cd src; $(AS) $(AFLAGS) crt0.s
src/crt0-sms.rel: src/crt0-sms.s
	cd src; $(AS) $(AFLAGS) crt0-sms.s

src/%.rel: src/%.c include/cv.h include/cv_graphics.h include/cv_input.h include/cv_sound.h include/cv_support.h
	$(CC) $(CFLAGS) $< -o $@
src/%-sms.rel: src/%.c
	$(CC) $(CFLAGSS) $< -o $@

src/cv_machine_config.rel: src/cv_machine_config.s
	cd src; $(AS) $(AFLAGS) cv_machine_config.s
src/cv_machine_config-sms.rel: src/cv_machine_config-sms.s
	cd src; $(AS) $(AFLAGS) cv_machine_config-sms.s

src/cv_get_r.rel: src/cv_get_r.s
	cd src; $(AS) $(AFLAGS) cv_get_r.s
src/cv_get_r-sms.rel: src/cv_get_r.rel
	cd src; cp cv_get_r.rel cv_get_r-sms.rel

src/cv_vdpout.rel: src/cv_vdpout.s
	cd src; $(AS) $(AFLAGS) cv_vdpout.s
src/cv_vdpout-sms.rel: src/cv_vdpout.rel
	cd src; cp cv_vdpout.rel cv_vdpout-sms.rel

src/cv_set_read_vram_address.rel: src/cv_set_read_vram_address.s
	cd src; $(AS) $(AFLAGS) cv_set_read_vram_address.s
src/cv_set_read_vram_address-sms.rel: src/cv_set_read_vram_address.rel
	cd src; cp cv_set_read_vram_address.rel cv_set_read_vram_address-sms.rel

src/cv_set_write_vram_address.rel: src/cv_set_write_vram_address.s
	cd src; $(AS) $(AFLAGS) cv_set_write_vram_address.s
src/cv_set_write_vram_address-sms.rel: src/cv_set_write_vram_address.rel
	cd src; cp cv_set_write_vram_address.rel cv_set_write_vram_address-sms.rel
src/cv_set_write_cram_address-sms.rel: src/cv_set_write_cram_address-sms.s
	cd src; $(AS) $(AFLAGS) cv_set_write_cram_address-sms.s

src/cv_memtovmemcpy_slow.rel: src/cv_memtovmemcpy_slow.s
	cd src; $(AS) $(AFLAGS) cv_memtovmemcpy_slow.s
src/cv_memtovmemcpy_slow-sms.rel: src/cv_memtovmemcpy_slow.rel
	cd src; cp cv_memtovmemcpy_slow.rel cv_memtovmemcpy_slow-sms.rel

src/cv_vmemtomemcpy_slow.rel: src/cv_vmemtomemcpy_slow.s
	cd src; $(AS) $(AFLAGS) cv_vmemtomemcpy_slow.s
src/cv_vmemtomemcpy_slow-sms.rel: src/cv_vmemtomemcpy_slow.rel
	cd src; cp cv_vmemtomemcpy_slow.rel cv_vmemtomemcpy_slow-sms.rel

src/cv_vmemset_slow.rel: src/cv_vmemset_slow.s
	cd src; $(AS) $(AFLAGS) cv_vmemset_slow.s
src/cv_vmemset_slow-sms.rel: src/cv_vmemset_slow.rel
	cd src; cp cv_vmemset_slow.rel cv_vmemset_slow-sms.rel

src/cv_memtovmemcpy_fast.rel: src/cv_memtovmemcpy_fast.s
	cd src; $(AS) $(AFLAGS) cv_memtovmemcpy_fast.s
src/cv_memtovmemcpy_fast-sms.rel: src/cv_memtovmemcpy_fast.rel
	cd src; cp cv_memtovmemcpy_fast.rel cv_memtovmemcpy_fast-sms.rel

src/cv_vmemtomemcpy_fast.rel: src/cv_vmemtomemcpy_fast.s
	cd src; $(AS) $(AFLAGS) cv_vmemtomemcpy_fast.s
src/cv_vmemtomemcpy_fast-sms.rel: src/cv_vmemtomemcpy_fast.rel
	cd src; cp cv_vmemtomemcpy_fast.rel cv_vmemtomemcpy_fast-sms.rel

src/cv_vmemset_fast.rel: src/cv_vmemset_fast.s
	cd src; $(AS) $(AFLAGS) cv_vmemset_fast.s
src/cv_vmemset_fast-sms.rel: src/cv_vmemset_fast.rel
	cd src; cp cv_vmemset_fast.rel cv_vmemset_fast-sms.rel

clean:
	rm -f src/*.rel src/*.lst src/*.lnk src/*.sym src/*.asm src/*.rel */*~ ./*~ bin/*.rel bin/*.lib *~

