#include "BooksRepoFile.h"

#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;

using std::cout;


void BooksRepoFile::loadFromFile() {
	ifstream in;
	in.open(fileName);
	if (!in.is_open()) {
		//verify if stream is opened
		throw BooksRepoException("Error opening " + fileName);
	}

	string linie;
	const string delim = ",";

	while (!in.eof()) {
		getline(in, linie);
		if (linie == "") {
			break;
		}

		string title;
		string author;
		string genre;
		int year = 0;

		auto pos = linie.find(delim);
		title = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		author = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		genre = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);

		pos = linie.find(delim);
		year = stoi(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);

		Book b{ title.c_str(), author.c_str(), genre.c_str(), year };
		BooksRepo::store(b);

	}
	in.close();
}

void BooksRepoFile::writeToFile() {
	std::ofstream out(fileName);

	/*if (!out.is_open()) {
		//verify if stream is opened
		std::string msg("Error opening file");
		throw BooksRepoException(msg);
	}*/

	for (auto& b : getAll()) {
		string delim = ",";
		string linie;
		linie = b.getTitle() + delim + b.getAuthor() + delim + b.getGenre() + delim + std::to_string(b.getYear()) + '\n';
		out << linie;
	}

	out.close();
}
