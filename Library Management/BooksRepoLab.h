#pragma once

#include "Book.h"
#include "AbstractRepo.h"

#include <string>
#include <map>
//#include <iterator>
#include <vector>

//using std::iterator;
using std::string;
using std::vector;
using std::map;


class BooksRepoLab :public Repo
{
private:
	map<int, Book> books;
	double P;
	int id = 1;
	vector<Book> v; //getAll vector

	void throwRandomExcept();

public:
	BooksRepoLab(double probability) : P{ probability } {}

	BooksRepoLab(const BooksRepoLab& ot) = delete;

	~BooksRepoLab() = default;

	const Book find(string title, string author) const override;

	bool exist(const Book& b) const;

	void store(const Book& b) override;

	const Book findByTitle(string title) const override;

	const int findIndex(string title, string author) const override;

	void remove(string title, string author) override;

	void update(string title, string author, string new_genre, int new_year) override;

	size_t size() const noexcept override;

	const vector<Book>& getAll() override;
};
