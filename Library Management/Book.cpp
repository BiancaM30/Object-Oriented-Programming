#include "Book.h"


string Book::getTitle() const {
	return title;
}

string Book::getAuthor() const {
	return author;
}

string Book::getGenre() const {
	return genre;
}

int Book::getYear() const {
	return year;
}

void Book::setGenre(const string& new_genre) {
	genre = new_genre;
}

void Book::setYear(const int new_year) {
	year = new_year;
}
