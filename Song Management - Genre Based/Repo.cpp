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
		string gen;

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
		gen = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		Melodie m{ id, nume.c_str(), artist.c_str(), gen};
		Repo::add(m);
	}
	in.close();
}

void Repo::writeToFile() {
	ofstream out(fileName);
	for (auto& melodie : melodii) {
		string delim = ",";
		string linie;
		linie = std::to_string(melodie.getId()) + delim + melodie.getTitlu() + delim + melodie.getArtist() + delim + melodie.getGen() + "\n";
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

void Repo::remove(int id) {
	int index = 0;

	for (const auto& melodie : melodii) {
		if (melodie.getId() == id) {
			melodii.erase(melodii.begin() + (index));
			break;
		}
		index++;
	}
	
	writeToFile();
}