#pragma once
#include <iostream>
#include <string>

using std::string;

class Melodie
{
private:
	int id;
	string titlu;
	string artist;
	string gen;

public:
	//Constructor
	Melodie(int id, string titlu, string artist, string gen) : id{ id }, titlu{ titlu }, artist{ artist }, gen{ gen }{
	};
	//Constructor de copiere
	Melodie(const Melodie& ot) {
		this->id = ot.getId();
		this->titlu = ot.getTitlu();
		this->artist = ot.getArtist();
		this->gen = ot.getGen();

	}

	int getId() const;

	string getTitlu() const;

	string getArtist() const;

	string getGen() const;

};

