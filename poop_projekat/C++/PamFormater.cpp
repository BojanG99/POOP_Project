#include "PamFormater.h"
#include<regex>
#include <iostream>
#include<string>
#include <fstream>
using namespace std;
Layer* PamFormater::import(const char *ch,int prov) {//pravi novi sloj od slike koja je data kao pam fajl
	string s;
	ifstream f(ch,std::ios::binary);
	if (!f) {
		cout << "Ne postoji fajl\n";
		return new Layer();

	}
	int sirina, visina, dubina,maxval;
	string opis;
	regex r("[^ ]* ([0-9]*)");
	getline(f, s);
	getline(f, s);
	smatch result;
	if (regex_match(s, result, r))
		sirina= atoi(result.str(1).c_str());
	getline(f, s);
	if (regex_match(s, result, r))
		visina= atoi(result.str(1).c_str());

	getline(f, s);
	if (regex_match(s, result, r))
		dubina= atoi(result.str(1).c_str());

	getline(f, s);
	if (regex_match(s, result, r))
		maxval= atoi(result.str(1).c_str());
	regex r1("[^ ]* ([A-Z]*)");

	getline(f, s);
	if (regex_match(s, result, r1))
	opis=(result.str(1).c_str());
	getline(f, s);
	uint8_t re, g, b,alf;
	vector<vector<Pixel>> vecp;
	vector<vector<Pixel>> vecg;
	
	
		for (int i = 0; i < visina; i++)
		{
			vector<Pixel>vec;
			for (int j = 0; j < sirina; j++)
			{
				f.read((char*)&re, 1);
				f.read((char*)&g, 1);
				f.read((char*)&b, 1);
				if (dubina == 4)(f.read((char*)&alf, 1));
				alf = (dubina == 4) ? alf : 255;
				Pixel p(re, g, b,(int)alf);
				vec.push_back(p);
			}
			vecp.push_back(vec);
		}
		for (auto iter=vecp.rbegin();iter!=vecp.rend() ;iter++)
		{
			vecg.push_back(*iter);
		}
	
	cout << opis;
	f.close();

	return new Layer(vecg,visina,sirina,prov);

}


void PamFormater::export1(vector<vector<Pixel>> p,const char* ch) {//pravi pam sliku 
	ofstream o(ch, std::ios::binary);
	
	vector<vector<Pixel>>pom;
	for (auto i=p.rbegin();i!=p.rend();i++)
	{
		pom.push_back(*i);
	}
//ubacit hedr
	int visina =p.size();
	int sirina= p[0].size();
	//cout << visina << sirina;
	const char* ime = "P7\n";
	uint8_t enter = 0x0a;
	const char* sir = "WIDTH 400\n";
	const char* vis = "HEIGHT 267\n";
	const char* dub = "DEPTH 4\n";
	const char* mv = "MAXVAL 255\n";
	const char* tip = "TUPLTYPE RGB_ALPHA\n";
	const char* end = "ENDHDR\n";
	char* s = (char*)sirina;
	char* v = (char*)visina;
	o.write(ime, 2);
	o << "\n";
	//o.write((char*)&enter, 1);
	o.write(sir, 6);
	o.write(std::to_string(sirina).c_str(), std::to_string(sirina).length());
	o << "\n";
	
	o.write((char*)vis, 7);
	o.write(std::to_string(visina).c_str(), std::to_string(visina).length());
	o << "\n";
	
	o.write((char*)dub, 8);
	o.write((char*)mv,11);
	int a1 = 0;
	o.write((char*)tip, 19);
	o.write((char*)end, 7);
	// tip RGB_ALFA
	int cnt = 1;
	for (auto a:pom)
	{

		for (auto c:a )
		{
			
			char r = (char)c.Get_red();
			char b = (char)c.Get_blue();
			char g = (char)c.Get_green();
			char a = (char)c.Get_alfa();
			if (a1++ <3) {
			//	cout <<" sdasd  " <<c.Get_red() << " " << c.Get_green() << " " << c.Get_blue() << " " << c.Get_alfa() << endl;

	}
			o.write(&r, 1);
			o.write(&g, 1);
			o.write( &b,1);
			o.write(&a, 1);
		}
	}
	o.close();
}