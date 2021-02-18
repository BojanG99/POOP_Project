#pragma once
#include<iostream>

class Pixel
{
	int  R, G, B,alf;


public:
	Pixel(int Red=0, int Green=0, int Blue=0, int alfa=255) :R(Red), B(Blue), G(Green) {
		alf = (alfa * 100) / 255;

	}
	friend class Operation;
	int Get_red()const {
		return R ;
	}
	int Get_green()const {
		return G;
	}
	int Get_blue() const {
		return B;
	}
	int Get_alfa() const {
		return alf;
	}
	void Set_red(int p) {
		R = p;
	}
	void Set_green(int p) {
		G = p;
	}
	void Set_blue(int p) {
		B = p;
	}
	void Set_alfa(int p) {
		alf = p;
	}

	//preklopljeni neki operatori radi lakseg izvrsavanja operacija
	void operator +=(int p){
		R += p;
		G += p;
		B += p;

	}
	void operator -(int p) {
		R = p-R;
		G = p-G;
		B = p-B;
	}
	void operator -=(int p) {

		R -= p;
		G -= p;
		B -= p;
	}

	void operator *=(int p) {
		R *= p;
		G *= p;
		B *= p;
	}
	void operator /=(int p) {
		R /= p;
		G /= p;
		B /= p;
	}
	void operator /(int p) {
		R = p/R;
		G = p/G;
		B= p/B;
	}
	friend std::ostream& operator<<(std::ostream& os, const Pixel& p) {
		os << "(" << p.R << "," << p.G << "," << p.B << "." << p.alf << ")" << std::endl;

		return os;
	}
	void Poravnaj_Piksel() {
		if (R < 0)R = 0;
		else if (R > 255)R = 255;

		if (G < 0)G = 0;
		else if (G > 255)G = 255;

		if (B < 0)B = 0;
		else if (B > 255)B = 255;
	}
};

