#pragma once
#include <iostream>
#include <string.h>

using std::string;
class Produs
{
private:
	int id;
	string nume;
	string tip;
	double pret;

public:
	//Constructor
	Produs(int id, string nume, string tip, double pret) : id{ id }, nume{ nume }, tip{ tip }, pret{ pret }{

	};
	//Constructor de copiere
	Produs(const Produs& ot) {
		this->id = ot.getId();
		this->nume = ot.getNume();
		this->tip = ot.getTip();
		this->pret = ot.getPret();
	}

	int getId() const;

	string getNume() const;

	string getTip() const;

	double getPret() const;

	int getVocale() const;
};

