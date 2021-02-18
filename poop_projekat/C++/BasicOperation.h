#pragma once
#include"Operation.h"
// sve klase su izvedene iz klase Operation i imaju virtuelne metode izvrsi, get_name i kopiju
class Sabiranje:public Operation
{
public:
	Sabiranje(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel**p)override {

		(**p) += konst;
	}

	virtual const char* Get_name()const {
		return "Sum";
	}
	virtual Sabiranje* kopija()override {
		return new Sabiranje(konst);
	}
};

class Oduzimanje :public Operation {
public:
	Oduzimanje(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		(**p) -= konst;
	}
	virtual const char* Get_name()const {
		return "Sub";
	}
	virtual Oduzimanje* kopija()override {
		return new Oduzimanje(konst);
	}
};

class Mnozenje :public Operation {
public:
	Mnozenje(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		(**p)*= konst;
	}
	virtual const char* Get_name()const {
		return "Mul";
	}
	virtual Mnozenje* kopija()override {
		return new Mnozenje(konst);
	}
};
class Dijeljenje :public Operation {
public:
	Dijeljenje(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		(**p) /= konst;
	}
	virtual const char*  Get_name()const {
		return "Div";
	}
	virtual Dijeljenje* kopija()override {
		return new Dijeljenje(konst);
	}
};
class IOduzimanje :public Operation {
public:
	IOduzimanje(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		(**p) - konst;
	}
	virtual const char* Get_name()const {
		return "Isub";
	}

	virtual IOduzimanje* kopija()override {
		return new IOduzimanje(konst);
	}
};
class IDijeljenje :public Operation {
public:
	IDijeljenje(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel **p)override {

		(**p) / konst;
	}
	virtual const char* Get_name()const {
		return "Idiv";
	}
	virtual IDijeljenje* kopija()override {
		return new IDijeljenje(konst);
	}
};

class Max :public Operation {
public:
	Max(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		if ((**p).Get_red() < konst) { (**p).Set_red(konst); }
		if ((**p).Get_green() < konst) { (**p).Set_green(konst); }
		if ((**p).Get_blue() < konst) { (**p).Set_blue(konst); }
	}
	virtual const char*  Get_name()const {
		return "Max";
	}
	virtual Max* kopija()override {
		return new Max(konst);
	}
};

class Min :public Operation {
public:
	Min(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		if ((**p).Get_red() > konst) { (**p).Set_red(konst); }
		if ((**p).Get_green() > konst) { (**p).Set_green(konst); }
		if ((**p).Get_blue() > konst) { (**p).Set_blue(konst); }
	}
	virtual const char* Get_name()const {
		return "Min";
	}
	virtual Min* kopija()override {
		return new Min(konst);
	}
};

class Pow :public Operation {
public:
	Pow(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		(**p).Set_red(pow((**p).Get_red() ,konst));
		(**p).Set_green(pow((**p).Get_green(),konst));
		(**p).Set_blue(pow((**p).Get_blue(),konst));
	}
	virtual const char* Get_name()const {
		return "Pow";
	}
	virtual Pow* kopija()override {
		return new Pow(konst);
	}
};

class Log :public Operation {
public:
	Log(int konst) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		(**p).Set_red(log((**p).Get_red())/log( konst));
		(**p).Set_green(log((**p).Get_green()) / log(konst));
		(**p).Set_blue(log((**p).Get_blue() )/ log(konst));
	}
	virtual const char* Get_name()const {
		return "Log";
	}
	virtual Log* kopija()override {
		return new Log(konst);
	}
	};

class Abs :public Operation {
public:
	Abs(int konst=0) :Operation(konst) {}
	virtual void izvrsi(Pixel** p)override {

		(**p).Set_red(abs((**p).Get_red()));
		(**p).Set_green(abs((**p).Get_green()));
		(**p).Set_blue(abs((**p).Get_blue()));
	}
	virtual const char* Get_name()const {
		return "Abs";
	}
	virtual Abs* kopija()override {
		return new Abs(konst);
	}
};