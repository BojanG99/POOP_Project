#pragma once
#include"Rectangle.h"
#include<vector>
#include<string>
class Selection
{
	std::vector < Rectangle> okviri;
	//std::string ime;
	bool aktivan;
public:
	friend class MyFormater;
	friend class Image;
	Selection(std::vector < Rectangle> okv,bool akt=false) :okviri(okv),aktivan(akt) {}
	Selection():aktivan(false) {}
	void Set_aktivnost(bool act){
		aktivan = act;
	}

	bool Get_aktivnost()const {
		return aktivan;
	}

};

