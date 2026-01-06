#include "Rect.h"

void Rect::SetShape(float width_, float height_, Vector3 center_)
{
	left = -width_ * 0.5f + center_.x;
	right = width_ * 0.5f + center_.x;
	bottom = -height_ * 0.5f + center_.y;
	top = height_ * 0.5f + center_.y;

}

Rect Rect::ConvertToWorld(Vector3 center_)
{
	Rect ret = *this;

	ret.left += center_.x;
	ret.right += center_.x;
	ret.bottom += center_.y;
	ret.top += center_.y;

	return ret;
}
