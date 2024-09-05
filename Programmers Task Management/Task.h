#pragma once
#include <iostream>
#include <vector>
#include <string.h>

using std::string;
using std::vector;

class Task
{
private:
	int id;
	string descriere;
	vector<string> programatori;
	string stare; //open, inprogress, closed

public:
	//Constructor
	Task(int id, string descriere, vector<string> programatori, string stare) : id{ id }, descriere{ descriere }, programatori{ programatori }, stare{ stare }{

	};
	//Constructor de copiere
	Task(const Task& ot) {
		this->id = ot.getId();
		this->descriere = ot.getDescriere();
		this->programatori = ot.getProgramatori();
		this->stare = ot.getStare();
	}

	int getId() const;

	string getDescriere() const;

	vector<string> getProgramatori() const;

	string getStare() const;

	void setStare(string newStare);

};

