#include "Biblioteca.h"

#include<fstream>

using std::istream;
using std::ofstream;

const vector<Book>& Biblioteca::getAll() {
	return rep.getAll();
}

void Biblioteca::addBook(const string& title, const string& author, const string& genre, int year) {
	Book b{ title, author, genre, year };
	val.validate(b);
	rep.store(b);

	undo.push_back(std::make_unique<UndoAdd>(rep, b));
}

void Biblioteca::removeBook(const string& title, const string& author) {
	Book b = rep.find(title, author);
	undo.push_back(std::make_unique<UndoDelete>(rep, b));

	rep.remove(title, author);
}

void Biblioteca::updateBook(const string& title, const string& author, const string& new_genre, int new_year) {
	Book b = rep.find(title, author);
	undo.push_back(std::make_unique<UndoUpdate>(rep, b, new_genre, new_year));

	rep.update(title, author, new_genre, new_year);
}


const Book Biblioteca::getBook(const string& title, const string& author) {
	return rep.find(title, author);
}

const Book Biblioteca::getBookByTitle(const string& title) {
	return rep.findByTitle(title);
}

vector <Book> Biblioteca::filter(function <bool(const Book&)> f) const {
	vector <Book> rez;
	auto v = rep.getAll();
	std::copy_if(v.begin(), v.end(), std::back_inserter(rez), f);
	return rez;

}

vector <Book> Biblioteca::filterByTitle(string title) const {
	return filter([title](const Book& b) {
		return b.getTitle() == title;
		});
}

vector <Book> Biblioteca::filterByYear(int year) const {
	return filter([year](const Book& b) {
		return b.getYear() == year;
		});
}

vector <Book> Biblioteca::Sort(cmpFunction f) const {
	vector <Book> rez{ rep.getAll() };
	if (*f != nullptr)
		sort(rez.begin(), rez.end(), f);
	return rez;
}

vector <Book> Biblioteca::sortByTitle() const {
	return Sort([](const Book& b1, const Book& b2) {
		return b1.getTitle() < b2.getTitle();
		});
}

vector <Book> Biblioteca::sortByAuthor() const {
	return Sort([](const Book& b1, const Book& b2) {
		return b1.getAuthor() < b2.getAuthor();
		});
}

vector <Book> Biblioteca::sortByYearGen() const {
	return Sort([](const Book& b1, const Book& b2) {
		if (b1.getYear() == b2.getYear())
			return b1.getGenre() < b2.getGenre();
		else {
			return b1.getYear() < b2.getYear();
		}
		});
}

void Biblioteca::addBookToCart(const string& title) {
	Book b = getBookByTitle(title);
	cart.addBook(b);
}

const vector<Book>& Biblioteca::getAllBooksFromCart() const noexcept {
	return cart.getAll();
}

void Biblioteca::emptyCart() noexcept {
	cart.deleteAllCart();
}
void Biblioteca::random(int n) {
	vector<Book> all = rep.getAll();
	std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
	for (int i = 0; i < n; i++) {
		cart.addBook(all.front());
		all.erase(all.begin());
	}
}

map<string, DTO> Biblioteca::raport() {
	map<string, DTO> dict;
	vector<Book> all = rep.getAll();
	for (const auto& b : all) {
		if (dict.find(b.getGenre()) != dict.end()) {
			dict[b.getGenre()].addCount();
		}
		else
		{
			dict[b.getGenre()] = DTO(b.getGenre());
		}
	}
	return dict;
}

void Biblioteca::Undo() {
	if (undo.empty()) {
		vector<string> mess;
		mess.push_back("Nu se mai poate face undo!");
		throw ValidateException(mess);
	}

	undo.back()->doUndo();
	redo.push_back(std::move(undo.back()));
	undo.pop_back();
}

void Biblioteca::Redo() {
	if (redo.empty()) {
		vector<string> mess;
		mess.push_back("Nu se mai poate face redo!");
		throw ValidateException(mess);
	}

	redo.back()->doRedo();
	undo.push_back(std::move(redo.back()));
	redo.pop_back();
}

void Biblioteca::exportCSV(const string& fileName) {
	ofstream out(fileName);
	for (auto& b : getAllBooksFromCart()) {
		out << b.getTitle() << "," << b.getAuthor() << "," << b.getGenre() << "," << b.getYear() << '\n';
	}
	out.close();
}

void Biblioteca::exportHTML(const string& fileName) {
	ofstream out(fileName);


	out << "<!DOCTYPE html><html><head></head><body>"; //starting html

	for (auto& b : getAllBooksFromCart()) {
		out << "<p><span style='font-weight: bold'>" << "Titlu: " << b.getTitle() << "</span></p>" << "Autor:" << b.getAuthor() << "</span></p>" << "Gen: " << b.getGenre() << "</span></p>" << "An aparitie:" << b.getYear() << "</span></p>";
	}

	out << "</body></html>";
	out.close();
}
