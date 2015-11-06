#include <vix_rectangle.h>

namespace Vixen {

	const Rectangle Rectangle::EMPTY(0, 0, 0, 0);

	/*Checks whether given point is bounded by Rectangle*/
	bool Rectangle::Contains(int _x, int _y)
	{
		return ((((this->x <= _x) && (_x < (this->x + this->w)))
			   && (this->y <= _y)) && (_y < (this->y + this->h)));
	}

	/*Checks whether Rectangle has any value*/
	bool Rectangle::HasValue()
	{
		return x != 0 || y != 0 || w != 0 || h != 0;
	}

	/*Checks whether Rectangle intersects with another Rectangle*/
	bool Rectangle::Intersects(const Rect& r)
	{
		return !( r.Left() > Right()
			||  r.Right() < Left()
			||  r.Top() > Bottom()
			||  r.Bottom() < Top());
	}

}