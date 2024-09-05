#pragma once
#include "BooksRepoLab.h"

#include "BookValidator.h"
#include "CustomerCart.h"
#include "Undo.h"
#include "DTO.h"

#include <random>
#include <chrono>
#include <functional>
#include <algorithm>

#include <vector>
#include <string>
#include <sstream>
#include <map>

using std::vector;
using std::string;
using std::ostream;
using std::function;
using std::map;
using std::unique_ptr;

// Comparing function for 2 books
typedef bool(*cmpFunction) (const Book&, const Book&);

class Biblioteca
{
private:

	Repo& rep;

	BookValidator& val;
	CustomerCart cart;
	vector<unique_ptr<Undo>> undo;
	vector<unique_ptr<Undo>> redo;

	/*
	* Generic filter function
	* param: f(function) - field after the filter is made
	* Return the filtred vector of books
	*/
	vector <Book> filter(function <bool(const Book&)> f) const;

	/*
	* Generic sort function
	* param: f(cmpFunction) - compare funcion after the sorting is made
	* Return the sorted vector of books
	*/
	vector <Book> Sort(cmpFunction f) const;

public:

	Biblioteca(Repo& repo, BookValidator& validator) noexcept : rep{ repo }, val{ validator }{}

	//nu permitem copierea de obiecte Biblioteca
	Biblioteca(const Biblioteca& ot) = delete;

	/*
	 Return the list of books from service
	*/
	const vector<Book>& getAll();

	/*
	* Add a new book to the service
	* param: title(string), author(string),genre(string), year(int)
	* post: book is added to service
	* Throw exception if the book is not valid or it already exists
	*/
	void addBook(const string& title, const string& author, const string& genre, int year);

	/*
	* Remove the book with the given title and author from service
	* param: title(string), author(string)
	* post: book is removed from service
	* Throw exception if the book does not exist
	*/
	void removeBook(const string& title, const string& author);

	/*
	* Update the book with the given title and author in service
	* param: title(string), author(string), new_genre(string), new_year(int)
	* post: book is updated in service
	* Throw exception if the book does not exist
	*/
	void updateBook(const string& title, const string& author, const string& new_genre, int new_year);

	/*
	* Get the book with the given title and author from service
	* param: title(string), author(string)
	* Return the book
	* Throw exception if the book does not exist
	*/
	const Book getBook(const string& title, const string& author);


	/*
	* Get the book with the given title from service
	* param: title(string)
	* Return the book
	* Throw exception if the book does not exist
	*/
	const Book getBookByTitle(const string& title);

	/*
	* Filter by title
	* param: title(string)
	* Return the filtred vector of books
	*/
	vector <Book> filterByTitle(string title) const;

	/*
	* Filter by year
	* param: year(int)
	* Return the filtred vector of books
	*/
	vector <Book> filterByYear(int year) const;

	/*
	* Sort books by title
	* Return the sorted vector of books
	*/
	vector <Book> sortByTitle() const;

	/*
	* Sort books by author
	* Return the sorted vector of books
	*/
	vector <Book> sortByAuthor() const;

	/*
	* Sort books by year and genre
	* Return the sorted vector of books
	*/
	vector <Book> sortByYearGen() const;

	/*
	* Add a book to the cart by title
	* param: string title
	*/
	void addBookToCart(const string& title);

	/*
	* Get all books from cart
	* Return the vector of books
	*/
	const vector<Book>& getAllBooksFromCart() const noexcept;

	/*
	* Delete all the books from cart
	* post: cart is empty
	*/
	void emptyCart() noexcept;

	/*
	* Populate the cart with n books
	* param: n(integer)
	* post: cart is populated with n random books
	*/
	void random(int n);

	map<string, DTO> raport();

	void Undo();

	void Redo();

	/*
	* Export cart content to csv file
	* param: string fileName
	*/
	void exportCSV(const string& fileName);

	/*
	* Export cart content to html file
	* param: string fileName
	*/
	void exportHTML(const string& fileName);

};

