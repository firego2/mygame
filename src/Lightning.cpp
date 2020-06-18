#include "Lightning.h"

void Lightning::update()
{
	static int activation_counter = GLBL::FPS * 3;
	static int delay_counter = GLBL::FPS / 10;
	activation_counter++;

	if (activation_counter > GLBL::FPS)
	{
		delay_counter++;
		if (delay_counter >= GLBL::FPS / 10)
		{
			delay_counter = 0;
			if (animation_direction == right)
			{
				current_frame++;
				src_rect.x = current_frame * src_rect.w;
				if (current_frame == total_frame)
				{
					animation_direction = left;
				}
			}
			else
			{
				current_frame--;
				src_rect.x = current_frame * src_rect.w;
				if (current_frame == 0)
				{
					animation_direction = right;
					activation_counter = 0;
				}
			}
		}
		
	}


}
