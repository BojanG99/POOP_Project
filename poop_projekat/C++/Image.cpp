#include "Image.h"
#include<iostream>
#include"PamFormater.h"
#include<regex>

void Image::Poravnaj(Layer l){
if (width > l.GetS()) {//popunjava l po sirini

	std::for_each(l.mat.begin(), l.mat.end(), [&](std::vector<Pixel>&p) {
		for (int i = 0; i < (width-(int)l.GetS()); i++)
		{
			p.push_back(Pixel(0, 0, 0, 0));
		}
		
	});
	
	l.SetS(width);
	
}
else if (width < l.GetS()) {//popunjava sve ostale slojeve po sirini

	std::for_each(slojevi.begin(), slojevi.end(), [&](Layer& nl) {


		std::for_each(nl.mat.begin(), nl.mat.end(), [&](std::vector<Pixel>& p) {
			for (int i = 0; i < (l.GetS() - width); i++)
			{
				p.push_back(Pixel(0, 0, 0, 0));
			}
		});
		nl.SetS(width);

	});

	width = l.GetS();
	
}

if (height > l.GetV()) {//popunjava l po visini
	std::vector<Pixel> dop;
	for (int i = 0; i < width; i++)
	{
		dop.push_back(Pixel(0, 0, 0, 0));
	}
	for (int i = 0; i < (height - l.GetV()); i++)
	{
		l.mat.push_back(dop);
	}
	
	l.SetV(height);
	
}
else if (height < l.GetV()) {//popunjava ostale slojeve po visini

	
	std::for_each(slojevi.begin(), slojevi.end(), [&](Layer& nl) {
	
		std::vector<Pixel> dop;
		for (int i = 0; i < width; i++)
		{
			dop.push_back(Pixel(0, 0, 0, 0));
		}
		for (int i = 0; i < (l.GetV() - nl.GetV()); i++)
		{
			nl.mat.push_back(dop);
		}

		nl.SetV(height);

	});
	
	height = l.GetV();
	
	}



slojevi.push_back(Layer(l));// ubacuje sloj l




	}
 Image::Image():numSel(0),height(0),width(0) {
	for (int i = 0; i < 2000; i++)
	{
		std::vector<int> tmp;
		for (int j = 0; j < 2000; j++)//popunjava matricu za slojeve nulama
		{
			tmp.push_back(0);
		}
		change.push_back(tmp);
	}
	save = true;
}

void Image::Dodaj_Selekciju(std::string s, std::vector<Rectangle>&r, bool akt ) {
	save = false;

	if (selekcije.find(s) == selekcije.end()) {//ako ne postoji selekcija sa tim imenom
		save = false;
		selekcije[s] = Selection(r, akt);
		if (akt) {
			numSel++;//ako je aktivna poveca broj aktivnih selekcija
			
			for (auto x:r )
			{
				int xkor=x.Get_x();
				int ykor=x.Get_y();
				int sir=x.Get_sirina();
				int vis = x.Get_visina();
			//	std::cout << sir << vis <<xkor <<ykor<<std::endl;
				for (int i = 0; (i < vis) && ((i+xkor)<2000); i++)
				{
					for (int j = 0; (j < sir) && ((j + ykor) < 2000); j++)
					{
						change[i + xkor][j + ykor]++;//poveca za 1 matricu za one piksele koje obuhvata ova selekcija
					//	std::cout << (i + xkor) << "," << (j + ykor) << std::endl;
					}
				}
			}
		}
	}
	else {
		//throw postoji selekcija sa ovim imenom

	}


}
int Image::Dodaj_Sloj(std::string c, int prov) {
	std::regex r("[^\\.]*.(.*)");//gledamo koji je format
	std::string s = c;
	
	std::smatch res;

	std::string q;
	if (std::regex_match(s, res, r)) {
		q= res.str(1).c_str();
	
	}
	
	else { 
		std::cout << "GRESKA SA FORMATOM SLIKE\n";
		return -1;
	}

	//strcat(pom,q.c_str());
	//std::cout << pom;
	if (q=="bmp") {//zavisno od formata poziva odredjenu funkciju za ucitavanje sloja
		Layer* l = BMPFormater::Ucitaj_Sliku(c.c_str(), prov);
		if (l == nullptr) {
			std::cout << "GRESKA SA UCITAVANJEM SLIKE\n";
			return -1;
		}
		Poravnaj(*l);//vrsi popunjavanje potrebnih slojeva
		delete l;
		save = false;
	}
	else if (q=="pam")
	{
		Layer* l = PamFormater::import(c.c_str(), prov);
		if (l == nullptr) {
			std::cout << "GRESKA SA UCITAVANJEM SLIKE\n";
			return -1;
		}
		Poravnaj(*l);
		delete l;
		save = false;
	}
	else if (q=="xml") {
		std::vector<Layer> vl=MyFormater::importImage(c.c_str(), prov,*this);
		if (vl.empty()) {
			std::cout << "GRESKA SA UCITAVANJEM SLIKE\n";
			return -1;
		}
		for (auto x : vl) {
			Poravnaj(x);
		}
		save = false;
	}
	else {
		std::cout << "PROGRAM NE PRIHVATA OVAJ FORMAT\n";
		return -1;
		
	}
	return 0;
}
void Image::Exportuj_sliku(std::string ch)const {
	save = true;
	std::regex r("[^\\.]*.(.*)");//trazimo ekstenziju slike
	std::string s = ch;
	//std::cout << s;
	std::smatch res;
	//	 char* pom="";
	std::string q;
	if (std::regex_match(s, res, r)) {
		q = res.str(1).c_str();
		//	std::cout << q;
	}

	else {
		std::cout << "GRESKA SA FORMATOM SLIKE\n";
		return ;
	}

	//strcat(pom,q.c_str());
	//std::cout << pom;
	if (q == "bmp") {//zavisno od formata zovemo odredjenu funkciju za cuvanje slike
		
		
		BMPFormater::Sacuvaj_Sliku(ch.c_str(), Napravi_Sliku());
		
	}
	else if (q == "pam")
	{
	
		PamFormater::export1(Napravi_Sliku(), ch.c_str());
	}
	else if (q == "xml") {
		MyFormater::exportImage(*this, ch.c_str());
	}
	else {
		std::cout << "PROGRAM NE PRIHVATA OVAJ FORMAT\n";
		return ;

	}
	return ;
}
std::vector<std::vector<Pixel>> Image::Napravi_Sliku()const {
	int count = width * height;
	std::vector<std::vector<int>>d;//napravimo pomocnu matricu preko koje racunamo preostalu providnost
	std::vector<std::vector<Pixel>>slika;//pravimo sliku koju cemo ispisati
	for (int i = 0; i < height; i++)//inicijalizujemo sve matrice na pocetne vrijednosti d na 100 a sliku na nulte piksele
	{
		std::vector<int>tmp;
		std::vector<Pixel>tmps;
		for (int j = 0; j < width; j++)
		{
			tmp.push_back(100);
			tmps.push_back(Pixel(0, 0, 0));
		}
		slika.push_back(tmps);
		d.push_back(tmp);
	}
	
	for (auto x : slojevi)//prolazimo kroz svaki sloj
	{

		if (x.ucestvuje) {//ako cvor ucestvuje u formiranju slike
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{

					if (d[i][j] > 0) {//ako je ostalo providnosti
						int prov = (x.proz * x.mat[i][j].Get_alfa() * d[i][j]);//izracunamo providnost koliko piksel utice u slici
						

							slika[i][j].Set_blue(slika[i][j].Get_blue() + ((x.mat[i][j].Get_blue() * prov) / 1000000));//dodamo tu vrijedost 
						slika[i][j].Set_red(slika[i][j].Get_red() + ((x.mat[i][j].Get_red() * prov) / 1000000));
						slika[i][j].Set_green(slika[i][j].Get_green() + ((x.mat[i][j].Get_green() * prov) / 1000000));
						
						d[i][j] -= (prov) / 10000;// smanjimo preostalu providnost sloja
						if (d[i][j] <= 0)count--;//smanjujemo broj preostalih piksela za promjenu

					}
					if (count == 0)break;//ako nije ostalo vise piksela zavrsimo sa pravljenjem slike
				}
				if (count == 0)break;

			}
			if (count == 0)break;
		}
	}
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			slika[i][j].Set_alfa(255);
			if (d[i][j] > 0) {//ako neki piksel nije do kraja ispunjen, popunjavamo bijelom pozadinom
			


				slika[i][j].Set_blue(slika[i][j].Get_blue() +255*d[i][j]/100 );
				slika[i][j].Set_red(slika[i][j].Get_red() + 255 * d[i][j] / 100);
				slika[i][j].Set_green(slika[i][j].Get_green() + 255 * d[i][j] / 100);
			

			}
			
		}
	
	}


	
	return slika;
}
void Image::Aktiviraj_Selekciju(std::string ch) {

	if (selekcije.find(ch) == selekcije.end()) {//provjera da li postoji selekcija
		std::cout << "Ne postoji ova selekcija" << std::endl;
		return;
	}
	Selection &s=selekcije[ch];
	if (s.Get_aktivnost())return;//ako je vec bila aktivna ne radimo nista
	else(s.Set_aktivnost(true));//ako nije
	numSel++;//povecamo broj aktivnih selekcija
	save = false;
	for (auto x:s.okviri)//prodjemo kroz svaki okvir
	{
		int xkor = x.Get_x();
		int ykor = x.Get_y();
		int sir = x.Get_sirina();
		int vis = x.Get_visina();
		for (int i = 0; i < vis && (i + xkor) < 2000; i++)//u matrici sve povecamo za 1(pretpostavka da slika nece biti veca od 2000*2000)
		{
			for (int j = 0; j < sir && (j + ykor) < 2000; j++)
			{
				change[i + xkor][j + ykor]++;
			}
		}
	}
}
void Image::Deaktiviraj_Selekciju(std::string ch) {

	if (selekcije.find(ch) == selekcije.end()) {//provjera da li postoji selekcija
		std::cout << "Ne postoji ova selekcija" << std::endl;
		return;
	}
	Selection& s = selekcije[ch];
	if (!s.Get_aktivnost())return;//ako je vec bila neaktivna ne radimo nista
	else(s.Set_aktivnost(false));//ako nije
	numSel--;//smanjimo broj aktivnih selekcija
	save = false;//naznacimo da smo radili nesto sa slikom
	for (auto x : s.okviri)//prodjemo kroz svaki okvir
	{
		int xkor = x.Get_x();
		int ykor = x.Get_y();
		int sir = x.Get_sirina();
		int vis = x.Get_visina();
		for (int i = 0; i < vis && (i + xkor) < 2000; i++)
		{
			for (int j = 0; j < sir && (j + ykor) < 2000; j++)//u matrici change smanjimo za 1 svaki piksel koji je obuhvacen ovim slojem
			{
				change[i + xkor][j + ykor]--;
			}
		}
	}
}
void Image::Izvrsi_Operaciju() {
	save = false;
	for (auto& x : slojevi) {
		if (x.activan) {//operacije radimo ako je sloj aktivan
		
			if (numSel!=0) {//ako postoji neka aktivna selekcija
				for (int i = 0; i < x.v; i++)
				{
					for (int j = 0; j < x.s; j++)
					{
						if (change[i][j]) {//piksel na poziciji [i][j] je aktivan u nekoj selekciji ako je change[i][j]>0
							
							Pixel* niz[5] = { &x.mat[i][j],&x.mat[ux(i)][j] ,&x.mat[i][uy(j)] ,&x.mat[d(i)][j] ,&x.mat[i][d(j)] };
							//prosledjujemo sve piksele susjedne piksele jer je moguce da u operaciji bude medijana




							for (auto o : kompoper) {//prodjemo kroz sve kompozitne funkcije u slici
								o.izvrsi(niz);
								x.mat[i][j].Poravnaj_Piksel();
							}
							

						}
						

					}
				}
			}
			else {//ako nema aktivne selekcije radimo za sve piksele u aktivnom sloju
			
				for (int i = 0; i < x.v; i++)
				{
					for (int j = 0; j < x.s; j++)
					{
						Pixel* niz[5] = { &x.mat[i][j],&x.mat[ux(i)][j] ,&x.mat[i][uy(j)] ,&x.mat[d(i)][j] ,&x.mat[i][d(j)] };
				
					
						
					
						for (auto o : kompoper) {
							o.izvrsi(niz);
							x.mat[i][j].Poravnaj_Piksel();
						}
						
							
					}
				}
			}

		}


	}
}
Image* Image::Get_Image() {
	if (imginst == nullptr) {
		imginst = new Image();
		return imginst;
	}

	return imginst;
}
Image* Image::imginst = nullptr;
int Image::d(int a)const {
	return a == 0 ? 0 : (a - 1);//Koristimo za nalazenje susjednih piksela
}
int Image::ux(int a)const {
	return a == (height - 1) ? (height - 1) : (a + 1);//Koristimo za nalazenje susjednih piksela
}
int Image::uy(int a)const {
	return a == (width - 1) ? (width - 1) : (a + 1);//Koristimo za nalazenje susjednih piksela
}
void Image::Izbrisi_Sloj(int indx) {
	if (slojevi.size() <= indx || indx < 0) {
		std::cout << "NE POSTOJI SLOJ NA DATOM INDEKSU\n";
		return;
	}
	slojevi.erase(slojevi.begin() + indx);
}
void Image::Aktiviraj_Sloj_Operation(int at) {

	if (slojevi.size() <= at || at < 0) {
		std::cout << "NE POSTOJI SLOJ NA DATOM INDEKSU\n";
		return;
}
	slojevi[at].activan = false;
	save = false;
}
void Image::Deaktiviraj_Sloj_Operation(int at) {
	if (slojevi.size() <= at || at < 0) {
		std::cout << "NE POSTOJI SLOJ NA DATOM INDEKSU\n";
		return;
	}
	slojevi[at].activan = false;
	save = false;
}
void Image::Aktiviraj_Sloj_Save(int at) {
	if (slojevi.size() <= at || at < 0) {
		std::cout << "NE POSTOJI SLOJ NA DATOM INDEKSU\n";
		return;
	}
	slojevi[at].ucestvuje = false;
	save = false;
}
void Image::Deaktiviraj_Sloj_Save(int at) {
	if (slojevi.size() <= at || at < 0) {
		std::cout << "NE POSTOJI SLOJ NA DATOM INDEKSU\n";
		return;
	}
	slojevi[at].ucestvuje = false;
	save = false;
}
void Image::Dodaj_Kompozitnu_funkciju(CompositeOperation op) {
	kompoper.push_back(op);//ubacuje kompozitnu operaciju
	save = false;
}