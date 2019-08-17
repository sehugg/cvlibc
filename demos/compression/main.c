#include "cvu.h"

#include "rle_escape.h"

#define PATTERN ((const cv_vmemp)0x0000)
#define COLOR ((const cv_vmemp)0x2000)
#define IMAGE ((const cv_vmemp)0x1c00)
#define SPRITES ((const cv_vmemp)0x3c00)

extern const unsigned char color[];
extern const unsigned char pattern[];

extern const uint8_t HUFFMAN_ROOT;
extern const uint8_t HUFFMAN_LS, HUFFMAN_BS, HUFFMAN_RS;
extern const struct cvu_huffman_node huffman_tree[255];

void main(void)
{
	unsigned int i;
	struct cvu_compression_state state;

	cv_set_screen_active(false);	
	cv_set_image_table(IMAGE);
	cv_set_color_table(0x3fff);
	cv_set_character_pattern_t(0x1fff);
	cv_set_screen_mode(CV_SCREENMODE_BITMAP);

	// Make all sprites transparent.
	cv_set_sprite_attribute_table(SPRITES);
	for(i = 0; i < 32; i++)
	{
		struct cvu_sprite s;
		cvu_set_sprite_color(&s, CV_COLOR_TRANSPARENT);
		cvu_set_sprite(SPRITES, i, &s);
	}

	// Decompress image data to video memory.
	cvu_init_compression(pattern, &state, huffman_tree, HUFFMAN_ROOT, HUFFMAN_LS, HUFFMAN_BS, HUFFMAN_RS, RLE_ESCAPE);
	cvu_memtovmemcpy_compression(PATTERN,& state, 6144);
	cvu_init_compression(color, &state, huffman_tree, HUFFMAN_ROOT, HUFFMAN_LS, HUFFMAN_BS, HUFFMAN_RS, RLE_ESCAPE);
	cvu_memtovmemcpy_compression(COLOR, &state, 6144);

	for(i = 0; i < 768; i++)
		cvu_voutb(i % 256, IMAGE + i);

	cv_set_screen_active(true);

	for(;;);
}

