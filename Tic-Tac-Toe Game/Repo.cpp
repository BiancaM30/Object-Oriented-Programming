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
		int dim;
		string tabla;
		string jucator;
		string stare;

		auto pos = linie.find(delim);
		id = stoi(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		dim = stoi(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		tabla = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		jucator = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		stare = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		Joc j{ id, dim, tabla, jucator[0], stare };
		Repo::add(j);

	}
	in.close();
}

void Repo::writeToFile() {
	ofstream out(fileName);

	for (auto& j : jocuri) {
		string delim = ",";
		string linie;
		linie = std::to_string(j.getId()) + delim + std::to_string(j.getDim()) + delim + j.getTabla() + delim + j.getJucator() + delim + j.getStare() + '\n';
		out << linie;
	}
	out.close();
}


bool Repo::exist(const Joc& j) const {
	for (auto& joc : jocuri) {
		if (joc.getId() == j.getId()) {
			throw RepoException("Exista un produs cu acelasi id!\n");
		}
	}
	return false;
}

void Repo::add(const Joc& j) {
	if (!exist(j)) {
		jocuri.push_back(j);
	}
	writeToFile();
}

void Repo::update(const Joc& j) {
	for (auto& joc : jocuri) {
		if (joc.getId() == j.getId()) {
			joc.setDim(j.getDim());
			joc.setTabla(j.getTabla());
			joc.setJucator(j.getJucator());
			joc.setStare(j.getStare());
		}
	}
}

const vector<Joc>& Repo::getAll() {
	return jocuri;
}

