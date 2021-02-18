#include "BMPFormater.h"

#include<iostream>
#include<fstream>
Layer* BMPFormater::Ucitaj_Sliku(const char* ch, int prov) {
	uint32_t  pocetak_piksela, fleg;
	int32_t sirina, visina;
	uint16_t bpp, tip;
	std::vector<std::vector<Pixel>> sloj;
	std::ifstream file((char*)ch, std::ios::binary);
	if (file) {//dohvatamo heder
		file.read((char*)&tip, 2);
		if (tip != 0x4D42) {
			std::cout << "NEPOSTOJECI FORMAT\n";
			return nullptr;
		}
		file.seekg(10);
		
		file.read((char*)&pocetak_piksela, 4);
		file.seekg(18);
		
		file.read((char*)&sirina, 4);
		file.read((char*)&visina, 4);
	//	std::cout << sirina << " " << visina << "\n";
		file.seekg(28);
		
		file.read((char*)&bpp, 2);
		file.read((char*)&fleg, 4);
		file.seekg(pocetak_piksela);
		if (bpp == 24) {//ako je 24b format dohvatamo rgb
	
			uint8_t r,g,b;
			uint32_t pend;
			int pending = 4 - (3 * sirina % 4);
			if (pending == 4)pending = 0;
			 
				for (int j = 0; j < visina; j++) {
					std::vector<Pixel> pom;
					for (int i = 0; i < sirina ; i++) {
						file.read((char*)&b, 1);
						file.read((char*)&g, 1);
						file.read((char*)&r, 1);
						
						
						Pixel p1((int)r, (int)g, (int)b);
						pom.push_back(p1);
						
					}
					file.read((char*)&pend, pending);
					sloj.push_back(pom);
				}
			
			
			Layer* l = new Layer(sloj, visina, sirina, prov);
			return l;
		}
		else { //ako je 32b format onda rgbalfa
			uint8_t g,b,r,alf;
			for (int j = 0; j < visina; j++) {
				std::vector<Pixel> pom;
				for (int i = 0; i < sirina ; i++) {
					file.read((char*)&b, 1);
					file.read((char*)&g, 1);
					file.read((char*)&r, 1);
					file.read((char*)&alf, 1);
					
					Pixel p1(r, g, b,alf);
					pom.push_back(p1);
					
				}
				sloj.push_back(pom);
			}
			Layer* l = new Layer(sloj, visina, sirina, prov);//pravimo novi sloj sa informacijama iz fajla
			return l;
		}
	}
	else { // fajl nije otvoren

		std::cout << "LOSA PUTANJA DO FAJLA.STVORICE SE PRAZAN SLOJ"<< std::endl;
		Layer* l = new Layer();
		return l;
	}
}

	void BMPFormater::Sacuvaj_Sliku(const char*ch, std::vector<std::vector<Pixel>> l) {
		std::ofstream file(ch, std::ios::binary);

		if (file) {
			int32_t sir = l[0].size();
			int32_t vis = l.size();
			uint8_t bit;
			//setujemo heder
			bit = 0x42;
			file.write((char*)&bit, 1);
			bit = 0x4d;
			file.write((char*)&bit, 1);
			
			int pend = (((3 * sir) % 4) == 0 )? 0 : (4 - ((3 * sir )% 4));
			uint32_t vel = (vis * (3 * sir + pend));

			uint32_t size = vel + 54;
			file.write((char*)&size, 4);
			bit = 0x00;
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			bit = 0x36;
			file.write((char*)&bit, 1);
			bit = 0x00;
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			bit = 0x28;
			file.write((char*)&bit, 1);
			bit = 0x00;
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&sir, 4);
			file.write((char*)&vis, 4);
			bit = 0x01;
			file.write((char*)&bit, 1);
			bit = 0x00;
			file.write((char*)&bit, 1);
			bit = 0x18;
			file.write((char*)&bit, 1);
			bit = 0x00;
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			//velicina bitmape4
		
			file.write((char*)&vel, 4);
			bit = 0x13;
			file.write((char*)&bit, 1);
			bit = 0x0b;
			file.write((char*)&bit, 1);
			bit = 0x00;
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);

			bit = 0x13;
			file.write((char*)&bit, 1);
			bit = 0x0b;
			file.write((char*)&bit, 1);
			bit = 0x00;
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);
			file.write((char*)&bit, 1);

			bit = 0x00;
			//smjestamo piksele bajt po bajt
			for (auto a : l) {

				for (auto pix:a)
				{
					int b = pix.Get_blue();
					int r = pix.Get_red();
					int g = pix.Get_green();
					file.write((char*)&b, 1);
					file.write((char*)&g, 1);
					file.write((char*)&r, 1);

				}
				for (int i = 0; i < pend; i++)
				{
					file.write((char*)&bit, 1);
				}
			}
			file.close();
		}
		else {

			std::cout << "DESILA SE GRESKA\n";
			return;
		}

}