#include "GUI.h"

void GUI::update()
{
	if (total_frame > 0)
	{
		src_rect.x = current_frame * src_rect.w;
	}

}
