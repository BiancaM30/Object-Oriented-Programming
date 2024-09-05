#pragma once
#include "Task.h"

#include <vector>

using std::vector;

class Repo
{
private:
	string fileName;
	vector<Task> taskuri;
	void loadFromFile();
	void writeToFile();
	bool exist(const Task& p) const;

public:
	//Constructor
	Repo(string fileName) : fileName{ fileName } {
		loadFromFile();
	};

	//Constructor de copiere
	Repo(const Repo& ot) = delete;

	void add(const Task& p);

	const vector<Task>& getAll();

	void updateStare(int id, string stare);
};


class RepoException {
	string msg;
public:
	RepoException(const string  msg) : msg{ msg } {};
	const string getMsg() {
		return msg;
	}
};