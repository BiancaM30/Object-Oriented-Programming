#include "TaskValidator.h"


void TaskValidator::validate(const Task& t) {
	vector<string> errors;
	if (t.getDescriere() == "") {
		errors.push_back("Descrierea nu poate fi vida!\n");
	}
	if (t.getProgramatori().size() < 1) {
		errors.push_back("Minim un programator!\n");
	}
	if (t.getProgramatori().size() > 4) {
		errors.push_back("Maxim 4 programatori!\n");
	}
	if (t.getStare() != "open" && t.getStare() != "inprogress" && t.getStare() != "closed") {
		errors.push_back("Starea trebuie sa fie open/inprogress/closed");
	}
	if (errors.size() != 0) {
		throw ValidateException(errors);
	}
}