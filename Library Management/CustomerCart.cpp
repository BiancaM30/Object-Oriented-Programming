#include "CustomerCart.h"

void CustomerCart::addBook(const Book& b) {
	cart.push_back(b);
}

const vector<Book>& CustomerCart::getAll() const noexcept {
	return cart;
}

void CustomerCart::deleteAllCart() noexcept {
	cart.clear();
}