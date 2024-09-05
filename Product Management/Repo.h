#pragma once
#include "Produs.h"

#include <vector>

using std::vector;

class Repo
{
private:
	string fileName;
	vector<Produs> produse;
	void loadFromFile();
	void writeToFile();
	bool exist(const Produs& p) const;

public:
	//Constructor
	Repo(string fileName) : fileName{ fileName } {
		loadFromFile();
	};

	//Constructor de copiere
	Repo(const Repo& ot) = delete;

	void add(const Produs& p);

	const vector<Produs>& getAll();
};


class RepoException {
	string msg;
public:
	RepoException(const string  msg) : msg{ msg } {};
	const string getMsg() {
		return msg;
	}
};