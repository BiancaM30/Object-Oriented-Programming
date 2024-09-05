#pragma once

#include "BookValidator.h"

#include <vector>
using std::vector;

class CustomerCart {
private:
	vector<Book> cart;
public:
	CustomerCart() = default;

	/*
	* Add a book to the cart
	* param: b(Book)
	* post: book is added to cart
	*/
	void addBook(const Book& b);

	/*
	* Get all books from cart
	* post: return the vector of books from cart
	*/
	const vector<Book>& getAll() const noexcept;

	/*
	* Delete all the books from cart
	* post: cart is empty
	*/
	void deleteAllCart() noexcept;
};