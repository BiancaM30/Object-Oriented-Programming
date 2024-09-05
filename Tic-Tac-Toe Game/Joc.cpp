#include "Joc.h"

int Joc::getId() const {
	return id;
}

int Joc::getDim() const{
	return dim;
}

string Joc::getTabla() const {
	return tabla;
}

char Joc::getJucator() const {
	return jucator;
}

string Joc::getStare() const {
	return stare;
}

void Joc::setDim(int dim) {
	this->dim = dim;
}

void Joc::setTabla(string tabla) {
	this->tabla = tabla;
}

void Joc::setJucator(char jucator) {
	this->jucator = jucator;
}

void Joc::setStare(string stare) {
	this->stare = stare;
}