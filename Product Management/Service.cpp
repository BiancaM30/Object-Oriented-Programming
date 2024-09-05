#include "Service.h"

void Service::add(int id, string nume, string tip, double pret) {
	Produs p{ id, nume, tip, pret };
	val.validate(p);
	rep.add(p);
	
}

const vector<Produs>& Service::getAll() {
	return rep.getAll();
}

vector<Produs> Service::sortPret() const {
	auto produse = rep.getAll();
	for (int i = 0; i < produse.size() - 1; i++) {
		for (int j = i + 1; j < produse.size(); j++) {
			if (produse.at(j).getPret() < produse.at(i).getPret()) {
				std::swap(produse.at(j), produse.at(i));
			}
		}
	}
	return produse;
}