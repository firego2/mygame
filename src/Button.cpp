#include "Button.h"
#include "TextureManager.h"
#include "GameState.h"

void Button::use(GameState * curr_state)
{
	curr_state->set_signal(button_signal);
}

void Button::update()
{

	if (total_frame > 0)
	{
		if (focus)
		{
			src_rect.x = src_rect.w;

		}
		else
		{
			src_rect.x = 0;
		}
	}


}
