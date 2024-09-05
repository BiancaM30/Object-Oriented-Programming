#pragma once
#include "Book.h"

#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> messages;
public:
	ValidateException(const vector<string>& errors) :messages{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)

	//nu trebuie la gui
	friend ostream& operator<<(ostream& out, const ValidateException& ex);

	const vector<string>& getMsg() {
		return messages;
	}
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class BookValidator
{
public:
	/*
	* Validate the given book
	* param: b(Book)
	* throw ValidateException if the book is invalid(title/author/genre is empty or year is a negative number)
	*/
	void validate(const Book& b);
};

