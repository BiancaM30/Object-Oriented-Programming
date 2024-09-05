#pragma once
#include <iostream>
#include <string>

using std::string;

class Melodie
{private:
	int id;
	string titlu;
	string artist;
	int rank; //intre 0 si 10
public:
	//Constructor
	Melodie(int id, string titlu, string artist, int rank) : id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank }{
	};
	//Constructor de copiere
	Melodie(const Melodie& ot) {
		this->id = ot.getId();
		this->titlu = ot.getTitlu();
		this->artist = ot.getArtist();
		this->rank = ot.getRank();

	}

	int getId() const;

	string getTitlu() const;

	string getArtist() const;

	int getRank() const;

	void setTitlu(const string titlu_nou);

	void setRank(int rank_nou);
};

