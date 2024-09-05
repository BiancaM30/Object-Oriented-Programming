#pragma once
#include "Repo.h"
#include "JocValidator.h"

class Service
{
private:
	Repo& rep;
	JocValidator& val;

public:
	//Constructor
	Service(Repo& rep, JocValidator& validator) : rep{ rep }, val{ validator } {};

	//Constructor de copiere
	Service(const Service& ot) = delete;

	void add(int id, int dim, string tabla, char jucator, string stare);

	void update(int id, int dim_nou, string tabla_nou, char jucator_nou, string stare_nou);

	const vector<Joc>& getAll();

	vector<Joc> sortStare() const;

	Joc find(int id);
};

