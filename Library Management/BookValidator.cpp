#include "BookValidator.h"

void BookValidator::validate(const Book& b) {
	vector <string> errors;
	if (b.getTitle().size() == 0)
		errors.push_back("Titlul este vid!");
	if (b.getAuthor().size() == 0)
		errors.push_back("Autorul este vid!");
	if (b.getGenre().size() == 0)
		errors.push_back("Genul este vid");
	if (b.getYear() < 0)
		errors.push_back("Anul este negativ!");
	if (errors.size() != 0)
		throw ValidateException(errors);
}


ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.messages) {
		out << msg << " ";
	}
	return out;
}