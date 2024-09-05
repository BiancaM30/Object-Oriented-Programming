#include "BooksRepoLab.h"


void BooksRepoLab::store(const Book& b) {
	this->throwRandomExcept();

	if (exist(b)) {
		throw BooksRepoException("Exista deja cartea cu titlul: " + b.getTitle() + " si autorul: " + b.getAuthor());
	}
	books.insert({ id,b });
	id = id + 1;
}

const Book BooksRepoLab::find(string title, string author) const {
	for (auto it = books.begin(); it != books.end(); ++it) {
		if (it->second.getTitle() == title && it->second.getAuthor() == author) {
			return it->second;
		}
	}
	//daca nu exista arunc o exceptie
	throw BooksRepoException("Nu exista cartea cu titlul: " + title + " si autorul: " + author);
}

const Book BooksRepoLab::findByTitle(string title) const {
	for (auto it = books.begin(); it != books.end(); ++it) {
		if (it->second.getTitle() == title) {
			return it->second;
		}
	}
	//daca nu exista arunc o exceptie
	throw BooksRepoException("Nu exista cartea cu titlul: " + title);
}

bool BooksRepoLab::exist(const Book& b) const {
	try {
		find(b.getTitle(), b.getAuthor());
		return true;
	}
	catch (BooksRepoException&) {
		return false;
	}
}

const int BooksRepoLab::findIndex(string title, string author) const {
	for (auto it = books.begin(); it != books.end(); ++it) {
		if (it->second.getTitle() == title && it->second.getAuthor() == author) {
			return it->first;
		}
	}
	//daca nu exista arunc o exceptie
	throw BooksRepoException("Nu exista cartea cu titlul: " + title + " si autorul: " + author);
}

void BooksRepoLab::remove(string title, string author) {
	this->throwRandomExcept();

	try {
		const int index = findIndex(title, author);
		books.erase(index);
	}
	catch (const BooksRepoException& ex) {
		throw BooksRepoException(ex);
	}
}

void BooksRepoLab::update(string title, string author, string new_genre, int new_year) {
	this->throwRandomExcept();

	try {
		const int index = findIndex(title, author);
		books.at(index).setGenre(new_genre);
		books.at(index).setYear(new_year);
	}
	catch (const BooksRepoException& ex) {
		throw BooksRepoException(ex);
	}
}

size_t BooksRepoLab::size() const noexcept {
	return books.size();
}

const vector<Book>& BooksRepoLab::getAll() {
	v.clear();
	for (auto it = books.begin(); it != books.end(); ++it) {
		v.push_back(it->second);
	}
	return v;
}

double randomDouble() {
	return ((double)rand()) / (double)RAND_MAX;
}

void BooksRepoLab::throwRandomExcept() {
	const double val = randomDouble();
	if (val <= this->P) {
		throw BooksRepoException("Random Exception!");
	}
}

