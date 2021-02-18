#pragma once
#include"Image.h"
class MyFormater
{
	public:
	static void exportImage(const Image& i, const char* path);

	static std::vector<Layer>   importImage(const char* path,int prov,Image&i);

};

