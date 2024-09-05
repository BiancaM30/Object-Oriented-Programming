#pragma once
#include "Book.h"
#include "AbstractRepo.h"

#include <vector>
#include <ostream>
#include <string>
#include <algorithm>
#include <functional>

using std::vector;
using std::string;
using std::ostream;
using std::function;



class BooksRepo :public Repo
{
private:
	vector<Book> books;

	/*
	* Private method
	* Verifies if a book already exists in repository
	* param: b (const Book&)
	* Return true if book exists
	* Catch exception if book does not exist
	*/
	bool exist(const Book& b) const;

public:

	// Constructor
	BooksRepo() = default;

	//Copy constructor (nu permitem copierea de obiecte)
	BooksRepo(const BooksRepo& ot) = delete;

	/*
	* Find the book in repository with the given title and author
	* param: title(string), author(string)
	* Return the book if it exists in repository
	* Throw BooksRepoException if book does not exist
	*/
	const Book find(string title, string author) const override;


	/*
	* Find the book in repository with the given title
	* param: title(string)
	* Return the book if it exists in repository
	* Throw BooksRepoException if book does not exist
	*/
	const Book findByTitle(string title) const override;

	/*
	* Store a book to the repository
	* param: b(Book)
	* post: Book is stored to the repository
	* Throw BooksRepoException if book already exists
	*/
	virtual void store(const Book& b) override;

	/*
	* Find the index of a book in repository with the given title and author
	* param: title(string), author(string)
	* Return the index if the book exists in repository
	* Throw BooksRepoException if book does not exist
	*/
	const int findIndex(string title, string author) const override;

	/*
	* Remove the book with the given title and author from repository
	* param: title(string), author(string)
	* post: Book is removed from repository
	* Throw BooksRepoException if book does not exist
	*/
	virtual void remove(string title, string author) override;

	/*
	* Update the book with the given title and author in repository
	* param: title(string), author(string)
	* post: Book is updated in repository
	* Throw BooksRepoException if book does not exist
	*/
	virtual void update(string title, string author, string new_genre, int new_year) override;

	/*
	* Return all the books from repository
	* param: -
	* return a list of books
	*/
	const vector<Book>& getAll() override;
	/*
	* Return the number of books from repository
	* param: -
	* return an integer
	*/
	size_t size() const noexcept override;

};

