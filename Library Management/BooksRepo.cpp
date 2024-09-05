#include "BooksRepo.h"

#include <sstream>
#include <iostream>


using std::ostream;
using std::stringstream;

const Book BooksRepo::find(string title, string author) const {
	auto it = std::find_if(books.begin(), books.end(), [title, author](Book b) {return b.getTitle() == title && b.getAuthor() == author; });

	if (it != books.end()) {
		return *it;
	}
	//daca nu exista arunc o exceptie
	throw BooksRepoException("Nu exista cartea cu titlul: " + title + " si autorul: " + author);
}

const Book BooksRepo::findByTitle(string title) const {
	auto it = std::find_if(books.begin(), books.end(), [title](Book b) {return b.getTitle() == title; });

	if (it != books.end()) {
		return *it;
	}
	//daca nu exista arunc o exceptie
	throw BooksRepoException("Nu exista cartea cu titlul: " + title);
}


bool BooksRepo::exist(const Book& b) const {
	try {
		find(b.getTitle(), b.getAuthor());
		return true;
	}
	catch (BooksRepoException&) {
		return false;
	}
}

void BooksRepo::store(const Book& b)
{
	if (exist(b)) {
		throw BooksRepoException("Exista deja cartea cu titlul: " + b.getTitle() + " si autorul: " + b.getAuthor());
	}
	books.push_back(b);
}

const int BooksRepo::findIndex(string title, string author) const {
	int index = 0;
	for (const auto& b : books) {
		index++;
		if (b.getTitle() == title && b.getAuthor() == author) {
			return index;
		}
	}
	//daca nu exista arunc o exceptie
	throw BooksRepoException("Nu exista cartea cu titlul: " + title + " si autorul: " + author);
}

void BooksRepo::remove(string title, string author) {
	try {
		const int index = findIndex(title, author);
		books.erase(books.begin() + (index - 1));
	}
	catch (const BooksRepoException& ex) {
		throw BooksRepoException(ex);
	}
}

void BooksRepo::update(string title, string author, string new_genre, int new_year) {
	try {
		const int index = findIndex(title, author);
		books.at(index - 1).setGenre(new_genre);
		books.at(index - 1).setYear(new_year);
	}
	catch (const BooksRepoException& ex) {
		throw BooksRepoException(ex);
	}
}

const vector<Book>& BooksRepo::getAll() {
	return books;
}

size_t BooksRepo::size() const noexcept {
	return books.size();
}

ostream& operator<<(ostream& out, const BooksRepoException& ex) {
	out << ex.msg;
	return out;
}


