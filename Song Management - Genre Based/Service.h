#pragma once
#include "Repo.h"

class Service
{
private:
	Repo& rep;
public:
	Service(Repo& rep) : rep{ rep } {};

	Service(const Service& ot) = delete;

	void add(const string titlu, const string artist, const string gen);

	const vector<Melodie>& getAll();

	vector<Melodie> sortAuthor() const;

	void remove(int id);
};

