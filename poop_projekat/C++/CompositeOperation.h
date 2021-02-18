#pragma once
#include"Operation.h"
class CompositeOperation:public Operation
{
	std::vector<Operation*> Koperacije;

	void kopiraj(const CompositeOperation&);
	void premjesti(CompositeOperation&);
public:
	CompositeOperation() {}
	CompositeOperation(const char* ch);
	
	
	virtual void izvrsi(Pixel** p)override; 

		void dodaj(Operation* o) {
			Koperacije.push_back(o);
		}
		void exportuj(std::string p);//eksportuje kompozitnu funkciju
		virtual const char* Get_name()const {
			return "Comp";
		}
		std::vector<Operation*> get_vector() const{
			return Koperacije;
		}
		CompositeOperation(const CompositeOperation&);
		CompositeOperation( CompositeOperation&&);
		CompositeOperation& operator =(const CompositeOperation&);
		CompositeOperation& operator =( CompositeOperation&&);
		virtual CompositeOperation* kopija()override {
			return new CompositeOperation();
		}
		~CompositeOperation();
		void obrisi();
};

