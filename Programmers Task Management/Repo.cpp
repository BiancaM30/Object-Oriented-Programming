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
	const string delim = ";";
	while (!in.eof()) {
		getline(in, linie);
		if (linie == "") {
			break;
		}

		int id;
		string descriere;
		vector<string> programatori;
		string stare;

		auto pos = linie.find(delim);
		id = stoi(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		descriere = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		//delimitam numele separate de virgula
		const string delim2 = ",";
		while (linie.find(delim2) != string::npos) {
			pos = linie.find(delim2);
			programatori.push_back (linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);
		}

		//inca o data pentru ultimul nume
		pos = linie.find(delim);
		programatori.push_back(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		stare = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		
		Task p{ id, descriere, programatori, stare };
		Repo::add(p);

	}
	in.close();
}

void Repo::writeToFile() {
	ofstream out(fileName);

	for (auto& p : taskuri) {
		string delim = ";";
		string linie;
		linie = std::to_string(p.getId()) + delim + p.getDescriere() + delim;
		vector<string> vec = p.getProgramatori();
		for (int i = 0; i < vec.size() - 1; i++) {
			linie = linie + vec[i] + ",";
		}

		//adaugam separat ultimul nume pentru c trebuie sa punem virgula dupa el
		linie = linie + vec[vec.size() - 1] + delim;

		//adaugam starea
		linie = linie + p.getStare() + "\n";

		out << linie;
	}
	out.close();
}

bool Repo::exist(const Task& p) const {
	for (auto& produs : taskuri) {
		if (produs.getId() == p.getId()) {
			throw RepoException("Exista un produs cu acelasi id!\n");
		}
	}
	return false;
}

void Repo::add(const Task& p) {
	if (!exist(p)) {
		taskuri.push_back(p);
	}
	writeToFile();
}

const vector<Task>& Repo::getAll() {
	return taskuri;
}

void Repo::updateStare(int id, string stare) {
	int index = 0;
	for (auto& task : taskuri) {
		if (task.getId() == id) {
			taskuri.at(index).setStare(stare);
		}
		index++;
	}
	writeToFile();
}