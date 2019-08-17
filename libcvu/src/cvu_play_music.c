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

bool cvu_play_music(struct cvu_music *restrict music)
{
	if(music->note_ticks_remaining >= music->sixteenth_notes_per_second)
		music->note_ticks_remaining -= music->sixteenth_notes_per_second;
	else if(music->pause_ticks_remaining >= music->sixteenth_notes_per_second)
	{
		cv_set_attenuation(music->channel, 0);
		music->pause_ticks_remaining -= music->sixteenth_notes_per_second;
	}
	else
	{
		bool pause = false;
		const uint16_t note = *(music->notes);

		cv_set_attenuation(music->channel, 0);

		if(note == 0xffff)
			return(false);

		// Length calculations:
		{
			uint8_t length, rel_length;
			uint16_t leftover_ticks = music->note_ticks_remaining + music->pause_ticks_remaining; // Avoid desynchronization of multi-voice music.

			length = (note >> 4) & 0xf;
			if(!length)
				length = 0x10;
			music->note_ticks_remaining = length * cv_get_vint_frequency();
			music->note_ticks_remaining += leftover_ticks;
			music->note_ticks_remaining -= music->sixteenth_notes_per_second;

			rel_length = (note >> 2) & 0x3;
			switch(rel_length)
			{
			case 0:	// Legato
				break;
			case 1:	// Staccato
				music->pause_ticks_remaining = music->note_ticks_remaining;
				music->note_ticks_remaining = music->note_ticks_remaining >> 2;
				music->pause_ticks_remaining -= music->note_ticks_remaining;
				break;
			case 2:
				music->pause_ticks_remaining = music->note_ticks_remaining >> 1;
				music->note_ticks_remaining -= music->pause_ticks_remaining;
				break;
			default:	// Standard
				music->pause_ticks_remaining = music->note_ticks_remaining >> 2;
				music->note_ticks_remaining -= music->pause_ticks_remaining;
				break;
			}
		}
		
		// Frequency calculations:
		{
			uint8_t octave, halftone;
			uint16_t frequency_divider;
			
			halftone = (note >> 8) & 0xf;
			pause = (halftone == 0xf);
			if(!pause)
			{
				frequency_divider = music->tuning[halftone];

				octave = (note >> 12);
				cv_set_frequency(music->channel, (frequency_divider >> octave) <= 32736 ? frequency_divider >> octave : frequency_divider >> (octave + 1));
			}
		}

		// Loudness calculations:
		{
			cv_set_attenuation(music->channel, pause ? 0 : (music->volume[note & 0x3]));
		}
		music->notes++;
	}
	return(true);
}

