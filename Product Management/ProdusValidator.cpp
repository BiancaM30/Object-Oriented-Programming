#include "ProdusValidator.h"

void ProdusValidator::validate(const Produs& p) {
	vector<string> errors;
	if (p.getNume() == "") {
		errors.push_back("Numele nu poate fi vid!\n");
	}
	if (p.getPret() < 1.0 || p.getPret() > 100.0) {
		errors.push_back("Pretul trebuie sa fie intre 1.0 si 100.0");
	}
	if (errors.size() != 0) {
		throw ValidateException(errors);
	}
}