#pragma once
#include "Book.h"

#include <vector>
#include <ostream>

using std::vector;
using std::ostream;

//functie pur virtuala
class Repo {
public:
	Repo() = default;

	virtual ~Repo() = default;

	Repo(const Repo& ot) = delete;

	virtual const Book find(string title, string author) const = 0;

	virtual const Book findByTitle(string title) const = 0;

	virtual void store(const Book& b) = 0;

	virtual const int findIndex(string title, string author) const = 0;

	virtual void remove(string title, string author) = 0;

	virtual void update(string title, string author, string new_genre, int new_year) = 0;

	virtual size_t size() const noexcept = 0;

	virtual const vector<Book>& getAll() = 0;

};

class BooksRepoException {
private:
	string msg;
public:
	BooksRepoException(const string message) : msg{ message } {
	}

	//functie friend (vreau sa folosesc membru privat msg)
	//nu trebuie la gui
	friend ostream& operator<<(ostream& out, const BooksRepoException& ex);

	const string getMsg() {
		return msg;
	}
};

ostream& operator<<(ostream& out, const BooksRepoException& ex);