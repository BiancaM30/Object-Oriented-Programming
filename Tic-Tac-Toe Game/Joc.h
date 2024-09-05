#pragma once
#include <iostream>
#include <string.h>

using std::string;


class Joc
{
private:
	int id;
	int dim;
	string tabla;
	char jucator; //jucatorul care urmeaza sa mute
	string stare;

public:
	//Constructor
	Joc(int id, int dim, string tabla, char jucator, string stare) : id{ id }, dim{dim}, tabla{ tabla }, jucator{ jucator }, stare{ stare }{

	};
	//Constructor de copiere
	Joc(const Joc& ot) {
		this->id = ot.getId();
		this->dim = ot.getDim();
		this->tabla = ot.getTabla();
		this->jucator = ot.getJucator();
		this->stare = ot.getStare();
	}

	int getId() const;

	int getDim() const;

	string getTabla() const;

	char getJucator() const;

	string getStare() const;

	void setDim(int dim);

	void setTabla(string tabla);

	void setJucator(char jucator);

	void setStare(string stare);
};



