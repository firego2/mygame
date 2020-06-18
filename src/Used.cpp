#include "Used.h"

bool Used::in_focus(const GLBL::position & position)
{
	if (position.x_pos >= dst_rect.x && position.x_pos <= dst_rect.x + dst_rect.w && position.y_pos >= dst_rect.y && position.y_pos <= dst_rect.y + dst_rect.h)
	{
		focus = true;
		return true;
	}
	focus = false;
	return false;
}
