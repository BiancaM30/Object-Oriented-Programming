#include "JocValidator.h"

void JocValidator::validate(const Joc& j) {
	vector<string> errors;
	if (j.getDim() < 3 || j.getDim() > 5) {
		errors.push_back("Dimensiunea poate fi 3,4,5!\n");
	}
	if (j.getJucator() != 'X' && j.getJucator() != 'O') {
		errors.push_back("Jucatorul care urmeaza poate fi X sau O");
	}
	if (j.getStare() != "Neinceput" && j.getStare() != "In derulare" && j.getStare() != "Terminat") {
		errors.push_back("Starea jocului poate fi doar Neinceput/In derulare/Terminat");
	}
	string tabla = j.getTabla();
	if (tabla.size() != j.getDim() * j.getDim()) {
		errors.push_back("Tabla invalida!");
	}
	for (auto& litera : tabla) {
		if (litera != 'X' && litera != 'O' && litera != '-') {
			errors.push_back("Tabla contine un caracter invalid!");
			break;
		}
	}
	if (errors.size() != 0) {
		throw ValidateException(errors);
	}
}
