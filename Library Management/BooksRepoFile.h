#pragma once
#include "BooksRepo.h"

#include <string.h>

using std::string;

class BooksRepoFile :public BooksRepo {
private:
	string fileName;
	void loadFromFile();
	void writeToFile();

public:
	BooksRepoFile(string fileName) :fileName{ fileName } {
		loadFromFile();
	}

	void store(const Book& b) override {
		BooksRepo::store(b);
		writeToFile();
	}

	void remove(string title, string author) override {
		BooksRepo::remove(title, author);
		writeToFile();
	}

	void update(string title, string author, string new_genre, int new_year) override {
		BooksRepo::update(title, author, new_genre, new_year);
		writeToFile();
	}

};

