#pragma once
#include "Repo.h"

class Service
{private:
	Repo& rep;
public:
	Service(Repo& rep) : rep{ rep } {};

	Service(const Service& ot) = delete;

	void add(const Melodie& mel);

	const vector<Melodie>& getAll();

	vector<Melodie> sortRank() const;

	void update(int id, string titlu_nou, int rank_nou);

	void remove(int id);
};

