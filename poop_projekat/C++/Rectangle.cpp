#include "Rectangle.h"
int Rectangle::Get_sirina()const {
	return this->sirina;
}
int Rectangle::Get_visina()const {
	return this->visina;
}
int Rectangle::Get_x()const {
	return this->x;
}
int Rectangle::Get_y()const {
	return this->y;
}

Rectangle::Rectangle(int _x, int _y, int _sirina, int _visina) :x(_x), y(_y), sirina(_sirina), visina(_visina) {}

Rectangle::~Rectangle()
{
}

