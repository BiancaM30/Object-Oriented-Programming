#pragma once
#include <string>
#include <iostream>
using std::string;

class Book
{
private:
	string title;
	string author;
	string genre;
	int year;

public:

	/*
	* Constructor
	* param: title(string), author(string), gen(string), year(integer)
	* post: Book is created
	*/
	Book(const string title, const string author, const string gen, int year) : title{ title }, author{ author }, genre{ gen }, year{ year }{
	}

	/*
	* Copy constructor
	*/
	Book(const Book& ot) {
		std::cout << "Copy constructor called" << '\n';
		this->author = ot.getAuthor();
		this->genre = ot.getGenre();
		this->title = ot.getTitle();
		this->year = ot.getYear();
	}

	/*
	* Get the title
	* param: -
	* return the title of book (string)
	*/
	string getTitle() const;
	/*
	* Get the author
	* param: -
	* return the author of book (string)
	*/
	string getAuthor() const;
	/*
	* Get the genre
	* param: -
	* return the genre of book (string)
	*/
	string getGenre() const;

	/*
	* Get the year of publication
	* param: -
	* return the year of publication (integer)
	*/
	int getYear() const;

	/*
	* Set the genre of a book
	* param: new_genre(string)
	*/
	void setGenre(const string& new_genre);

	/*
	* Set the year of a book
	* param: new_year(new_year)
	*/
	void setYear(const int new_year);

};

