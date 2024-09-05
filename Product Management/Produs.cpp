#include "Produs.h"

int Produs::getId() const {
	return id;
}

string Produs::getNume() const {
	return nume;
}

string Produs::getTip() const {
	return tip;
}

double Produs::getPret() const {
	return pret;
}

int Produs::getVocale() const {
	int nr_vocale = 0;
	char vocale[11] = "aeiouAEIOU";
	for (auto& litera : nume) {
		if (std::strchr(vocale, litera)) {
			nr_vocale++;
		}
	}
	return nr_vocale;
}