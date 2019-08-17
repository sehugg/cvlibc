//	(c) 2005 Philipp Krause pkk@spth.de

//	This library is free software; you can redistribute it and/or modify it
//	under the terms of the GNU Library General Public License as published by the
//	Free Software Foundation; either version 2, or (at your option) any
//	later version.
   
//	This library is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Library General Public License for more details.
   
//	You should have received a copy of the GNU Library General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include "cv.h"
#include "cvu_sound.h"

extern const uint16_t CVU_TUNING_ISO16_EQUAL[15];

// Todo: Adjust this!
const uint8_t CVU_VOLUME_DEFAULT[4] = {20, 16, 12, 8};

const uint16_t CVU_EMPTY_MUSIC = 0xffff;

void cvu_init_music(struct cvu_music *music)
{
	music->channel = CV_SOUNDCHANNEL_0;
	music->volume = CVU_VOLUME_DEFAULT;
	music->tuning = CVU_TUNING_ISO16_EQUAL;
	music->sixteenth_notes_per_second = 10;
	music->note_ticks_remaining = 0;
	music->pause_ticks_remaining = 0;
	music->notes = &CVU_EMPTY_MUSIC;
}

