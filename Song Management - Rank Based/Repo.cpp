#include "Repo.h"

#include <fstream>

using std::ifstream;
using std::ofstream;

void Repo::loadFromFile() {
	ifstream in;
	in.open(fileName);
	if (!in.is_open()) {
		throw std::exception();
	}
	string linie;
	const string delim = ",";
	while (!in.eof()) {
		getline(in, linie);
		if (linie == "") {
			break;
		}
		int id;
		string nume;
		string artist;
		int rank;

		auto pos = linie.find(delim);
		id = stoi(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		nume = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		artist = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		rank = stoi(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		Melodie m{ id, nume.c_str(), artist.c_str(), rank};
		Repo::add(m);
	}
	in.close();
}

void Repo::writeToFile() {
	ofstream out(fileName);
	for (auto& melodie : melodii) {
		string delim = ",";
		string linie;
		linie = std::to_string(melodie.getId()) + delim + melodie.getTitlu() + delim + melodie.getArtist() + delim + std::to_string(melodie.getRank()) + "\n";
		out << linie;
	}
	out.close();
}


void Repo::add(const Melodie& mel) {
	melodii.push_back(mel);
	writeToFile();
}

const vector<Melodie>& Repo::getAll() {
	return melodii;
}

void Repo::update(int id, string titlu_nou, int rank_nou) {
	int index = 0;
	for (const auto& melodie : melodii) {
		if (melodie.getId() == id) {
			melodii.at(index).setTitlu(titlu_nou);
			melodii.at(index).setRank(rank_nou);
		}
		index++;
	}
	writeToFile();
}


void Repo::remove(int id) {
	int index = 0;
	int poz_sterge = 0;
	string artist;
	//gasim artistul de la melodia cu id-ul dat ca parametru
	for (const auto& melodie : melodii) {
		if (melodie.getId() == id) {
			artist = melodie.getArtist();
			poz_sterge = index;
		}
		index++;
	}

	int nr_melodii = 0;
	//verificam cate melodii mai are artistul
	for (const auto& melodie : melodii) {
		if (melodie.getArtist() == artist) {
			nr_melodii++;
		}
	}
	if (nr_melodii == 1) {
		throw std::exception();
	}
	else {
		melodii.erase(melodii.begin() + (poz_sterge));
		writeToFile();
	}
}