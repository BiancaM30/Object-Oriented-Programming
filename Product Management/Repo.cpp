#include "Repo.h"

#include <fstream>
#include <string>

using std::ifstream;
using std::ofstream;

using std::string;

void Repo::loadFromFile() {
	ifstream in;
	in.open(fileName);
	if (!in.is_open()) {
		//
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
		string tip;
		double pret;

		auto pos = linie.find(delim);
		id = stoi(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);
		
		pos = linie.find(delim);
		nume = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		tip = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		pret = stod(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		Produs p{ id, nume.c_str(), tip.c_str(), pret };
		Repo::add(p);

	}
	in.close();
}

void Repo::writeToFile() {
	ofstream out(fileName);

	for (auto& p : produse) {
		string delim = ",";
		string linie;
		linie = std::to_string(p.getId()) + delim + p.getNume() + delim + p.getTip() + delim + std::to_string(p.getPret()) + '\n';
		out << linie;
	}
	out.close();
}

bool Repo::exist(const Produs& p) const {
	for (auto& produs : produse) {
		if (produs.getId() == p.getId()) {
			throw RepoException("Exista un produs cu acelasi id!\n");
		}
	}
	return false;
}

void Repo::add(const Produs& p) {
	if (!exist(p)) {
		produse.push_back(p);	
	}
	writeToFile();
}

const vector<Produs>& Repo::getAll() {
	return produse;
}

