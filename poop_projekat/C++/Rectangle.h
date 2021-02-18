#pragma once
class Rectangle
{

	int x,y,sirina,visina;


public:

	Rectangle(int _x, int _y, int _sirina, int _visina);
	~Rectangle();

	int Get_x()const;
	int Get_y()const;
	int Get_sirina()const;
	int Get_visina()const;

};

