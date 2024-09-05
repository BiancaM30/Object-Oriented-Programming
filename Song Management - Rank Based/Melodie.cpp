#include "Melodie.h"

int Melodie::getId() const {
	return id;
}

string Melodie::getTitlu() const {
	return titlu;
}

string Melodie::getArtist() const {
	return artist;
}

int Melodie::getRank() const {
	return rank;
}

void Melodie::setTitlu(const string titlu_nou) {
	titlu = titlu_nou;
}

void Melodie::setRank(int rank_nou) {
	rank = rank_nou;
}