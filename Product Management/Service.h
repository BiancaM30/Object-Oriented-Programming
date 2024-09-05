#pragma once
#include "Repo.h"
#include "ProdusValidator.h"

class Service
{
private:
	Repo& rep;
	ProdusValidator& val;

public:
	//Constructor
	Service(Repo& rep, ProdusValidator& validator) : rep{ rep }, val{validator} {};

	//Constructor de copiere
	Service(const Service& ot) = delete;

	void add(int id, string nume, string tip, double pret);

	const vector<Produs>& getAll();

	vector<Produs> sortPret() const;
};

