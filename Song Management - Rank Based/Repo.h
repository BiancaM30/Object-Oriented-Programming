#pragma once
#include "Melodie.h"

#include <vector>
using std::vector;

class Repo
{
private:
	string fileName;
	vector<Melodie> melodii;
	void loadFromFile();
	void writeToFile();

public:
	//Constructor
	Repo(string fileName) : fileName{ fileName } {
		loadFromFile();
	};

	//Constructor de copiere
	Repo(const Repo& ot) = delete;

	void add(const Melodie& mel);

	const vector<Melodie>& getAll();

	void update(int id, string titlu_nou, int rank_nou);

	void remove(int id);
};

