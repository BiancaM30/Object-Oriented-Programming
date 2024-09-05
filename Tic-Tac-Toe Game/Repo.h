#pragma once
#include "Joc.h"

#include <vector>

using std::vector;

class Repo
{
private:
	string fileName;
	vector<Joc> jocuri;
	void loadFromFile();
	void writeToFile();
	bool exist(const Joc& p) const;

public:
	//Constructor
	Repo(string fileName) : fileName{ fileName } {
		loadFromFile();
	};

	//Constructor de copiere
	Repo(const Repo& ot) = delete;

	void add(const Joc& p);

	const vector<Joc>& getAll();

	//updateaza jocul de la j.id
	void update(const Joc& j);
};


class RepoException {
	string msg;
public:
	RepoException(const string  msg) : msg{ msg } {};
	const string getMsg() {
		return msg;
	}
};