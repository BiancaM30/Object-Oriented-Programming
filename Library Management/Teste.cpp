#include "Teste.h"
#include "Book.h"
#include "BookValidator.h"
#include "BooksRepo.h"
#include "BooksRepoFile.h"
#include "BooksRepoLab.h"
#include "Biblioteca.h"
#include "CustomerCart.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include "assert.h"

using namespace std;

void testDomain() {
	Book b{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 };
	assert(b.getTitle() == "Robinson Crusoe");
	assert(b.getAuthor() == "Daniel Defoe");
	assert(b.getGenre() == "aventura");
	assert(b.getYear() == 1719);
	b.setGenre("drama");
	assert(b.getGenre() == "drama");
	b.setYear(1890);
	assert(b.getYear() == 1890);
}

void testValidator() {
	BookValidator validator;
	Book b{ "", "", "", -1232 };
	try {
		validator.validate(b);
	}
	catch (ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("Titlul") >= 0);
		assert(mesaj.find("Autorul") >= 0);
		assert(mesaj.find("Genul") >= 0);
		assert(mesaj.find("negativ") >= 0);

		auto mess = ex.getMsg();
	}

}

void testSearchRepo() {
	BooksRepo rep;
	rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	rep.store(Book{ "Ion", "Liviu Rebreanu", "drama", 1920 });

	auto b = rep.find("Ion", "Liviu Rebreanu");
	assert(b.getTitle() == "Ion");
	assert(b.getAuthor() == "Liviu Rebreanu");

	//arunca exceptie daca nu gaseste
	try {
		rep.find("Amandoi", "Liviu Rebreanu");
	}
	catch (BooksRepoException& ex) {
		const string msg = ex.getMsg();
		assert(true);
	}

	//cautam indexul unui element
	int index = rep.findIndex("Robinson Crusoe", "Daniel Defoe");
	assert(index == 1);
	//arunca exceptie daca nu gaseste
	try {
		index = rep.findIndex("Amandoi", "Liviu Rebreanu");
	}
	catch (BooksRepoException&) {
		assert(true);
	}
}

void testStoreRepo() {
	BooksRepo rep;
	rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	assert(rep.getAll().size() == 1);

	rep.store(Book("Ion", "Liviu Rebreanu", "drama", 1920));
	assert(rep.size() == 2);

	//nu pot adauga 2 cu acelasi titlu si autor
	try {
		rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	}
	catch (const BooksRepoException&) {
		assert(true);
	}

	//cauta inexistent
	try {
		rep.find("Amintiri din copilarie", "Ion Creanga");
	}
	catch (const BooksRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}

}

void testDeleteRepo() {
	BooksRepo rep;
	rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	rep.store(Book("Ion", "Liviu Rebreanu", "drama", 1920));
	assert(rep.size() == 2);

	rep.remove("Ion", "Liviu Rebreanu");

	//incercam sa stergem ceva ce nu exista
	try {
		rep.remove("Primavara", "Andrei P");
	}
	catch (BooksRepoException&) {
		assert(true);
	}
}

void testUpdateRepo() {
	BooksRepo rep;
	rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	rep.store(Book("Ion", "Liviu Rebreanu", "drama", 1920));
	assert(rep.size() == 2);

	rep.update("Ion", "Liviu Rebreanu", "dragoste", 1980);

	//incercam sa modificam ceva ce nu exista
	try {
		rep.update("Primavara", "Andrei P", "drama", 1999);
	}
	catch (BooksRepoException&) {
		assert(true);
	}
}

void testAddDelUpdateService() {
	BooksRepo rep;
	BookValidator val;
	Biblioteca ctr{ rep,val };
	assert(ctr.getAll().size() == 0);
	ctr.addBook("Robinson Crusoe", "Daniel Defoe", "aventura", 1719);
	ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
	assert(ctr.getAll().size() == 2);

	//incerc sa adaug ceva ce exista deja
	try {
		ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
	}
	catch (BooksRepoException&) {
		assert(true);
	}

	//adaug ceva invalid
	try {
		ctr.addBook("Ion", "Liviu Rebreanu", "drama", -12);
	}
	catch (ValidateException&) {
		assert(true);
	}
	assert(ctr.getAll().size() == 2);

	ctr.removeBook("Amintiri din copilarie", "Ion Creanga");
	assert(ctr.getAll().size() == 1);

	ctr.updateBook("Robinson Crusoe", "Daniel Defoe", "aventura", 1450);
	Book b = ctr.getBook("Robinson Crusoe", "Daniel Defoe");
	assert(b.getYear() == 1450);

}

void testFilterService() {
	BooksRepo rep;
	BookValidator val;
	Biblioteca ctr{ rep,val };

	ctr.addBook("Padurea spanzuratilor", "Liviu Rebreanu", "psihologic", 1920);
	ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
	ctr.addBook("Ion", "Liviu Rebreanu", "drama", 1920);

	vector<Book> rez1;
	rez1 = ctr.filterByTitle("Amintiri din copilarie");
	assert(rez1.size() == 1);

	vector<Book> rez2;
	rez2 = ctr.filterByYear(1920);
	assert(rez2.size() == 2);
}

void testSort() {
	BooksRepo rep;
	BookValidator val;
	Biblioteca ctr{ rep,val };

	ctr.addBook("Padurea spanzuratilor", "Liviu Rebreanu", "psihologic", 1920);
	ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
	ctr.addBook("Ion", "Liviu Rebreanu", "drama", 1920);

	vector<Book> rez1, rez2, rez3;
	rez1 = ctr.sortByTitle();
	assert(rez1.at(1).getTitle() == "Ion");
	rez2 = ctr.sortByAuthor();
	assert(rez2.at(0).getAuthor() == "Ion Creanga");
	rez3 = ctr.sortByYearGen();
	assert(rez3.at(2).getTitle() == "Padurea spanzuratilor");

	ctr.removeBook("Padurea spanzuratilor", "Liviu Rebreanu");
	ctr.addBook("Martianul", "Andy Weir", "actiune", 2015);
	ctr.addBook("Robinson Crusoe", "Daniel Defoe", "actiune", 1719);

	rez3 = ctr.sortByYearGen();
	assert(rez3.at(3).getTitle() == "Martianul");
}

void testCart() {
	CustomerCart cart;
	Book b1{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 };
	Book b2{ "Ion", "Liviu Rebreanu", "drama", 1920 };
	cart.addBook(b1);
	cart.addBook(b2);
	assert(cart.getAll().size() == 2);
	cart.deleteAllCart();
	assert(cart.getAll().size() == 0);
}

void testCartService() {
	BooksRepo rep;
	BookValidator val;
	Biblioteca ctr{ rep,val };

	ctr.addBook("Padurea spanzuratilor", "Liviu Rebreanu", "psihologic", 1920);
	ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
	ctr.addBook("Ion", "Liviu Rebreanu", "drama", 1920);

	ctr.addBookToCart("Ion");
	assert(ctr.getAllBooksFromCart().size() == 1);

	try {
		ctr.addBookToCart("Iarna");
	}
	catch (BooksRepoException) {
		assert(true);
	}

	ctr.emptyCart();
	assert(ctr.getAllBooksFromCart().size() == 0);

	ctr.random(2);
	assert(ctr.getAllBooksFromCart().size() == 2);

	string fileName1 = "testExp.csv";
	string fileName2 = "testExp.html";
	ctr.exportCSV(fileName1);
	ctr.exportHTML(fileName2);
}

void testMap() {
	BooksRepo rep;
	BookValidator val;
	Biblioteca ctr{ rep,val };

	ctr.addBook("Padurea spanzuratilor", "Liviu Rebreanu", "drama", 1920);
	ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
	ctr.addBook("Ion", "Liviu Rebreanu", "drama", 1920);

	const auto& raport = ctr.raport();
	for (const auto& it : raport) {
		DTO d = it.second;
		if (it.first == "drama") {
			assert(d.getCount() == 2);
			assert(d.getGen() == "drama");
		}

	}
}

void testUndo() {
	BooksRepo rep;
	BookValidator val;
	Biblioteca ctr{ rep,val };

	try {
		ctr.Undo();
	}
	catch (ValidateException&) {
		assert(true);
	}

	try {
		ctr.Redo();
	}
	catch (ValidateException&) {
		assert(true);
	}

	ctr.addBook("Padurea spanzuratilor", "Liviu Rebreanu", "drama", 1920);
	ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
	ctr.addBook("Ion", "Liviu Rebreanu", "drama", 1920);
	ctr.removeBook("Amintiri din copilarie", "Ion Creanga");
	assert(rep.size() == 2);
	ctr.Undo();
	assert(rep.size() == 3);
	ctr.Undo();
	assert(rep.size() == 2);
	ctr.updateBook("Padurea spanzuratilor", "Liviu Rebreanu", "comedie", 1800);
	assert(ctr.getBook("Padurea spanzuratilor", "Liviu Rebreanu").getYear() == 1800);
	ctr.Undo();
	assert(ctr.getBook("Padurea spanzuratilor", "Liviu Rebreanu").getYear() == 1920);
	ctr.Redo();
	ctr.Redo();
	ctr.Redo();
}

void testRepoFile() {
	try {
		BooksRepoFile rep{ "aa.txt" };
	}
	catch (BooksRepoException&) {
		assert(true);
	}

	//stergem continutul fisierului vechi
	std::ofstream out("teste.txt", std::ios::trunc);

	BooksRepoFile rep{ "teste.txt" };

	rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	assert(rep.getAll().size() == 1);

	rep.store(Book("Ion", "Liviu Rebreanu", "drama", 1920));
	assert(rep.size() == 2);

	//nu pot adauga 2 cu acelasi titlu si autor
	try {
		rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	}
	catch (const BooksRepoException&) {
		assert(true);
	}

	//cauta inexistent
	try {
		rep.find("Amintiri din copilarie", "Ion Creanga");
	}
	catch (const BooksRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}

	assert(rep.size() == 2);

	rep.remove("Ion", "Liviu Rebreanu");

	//incercam sa stergem ceva ce nu exista
	try {
		rep.remove("Primavara", "Andrei P");
	}
	catch (BooksRepoException&) {
		assert(true);
	}

	rep.update("Robinson Crusoe", "Daniel Defoe", "dragoste", 1980);

	//incercam sa modificam ceva ce nu exista
	try {
		rep.update("Primavara", "Andrei P", "drama", 1999);
	}
	catch (BooksRepoException&) {
		assert(true);
	}

	rep.findByTitle("Robinson Crusoe");

	try {
		rep.findByTitle("Robinson");
	}
	catch (BooksRepoException&) {
		assert(true);
	}

	//test Load
	BooksRepoFile rep2{ "testLoad.txt" };
	assert(rep2.getAll().size() == 4);

}




void testRepoLab() {


	BooksRepoLab rep{ 0.3 };
	int ok = 0;
	while (ok == 0) {
		try {
			rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
			assert(rep.getAll().size() == 1);
			ok = 1;
		}
		catch (BooksRepoException&) {
			ok = 0;
		}

	}

	ok = 0;
	while (ok == 0) {
		try {
			rep.store(Book("Ion", "Liviu Rebreanu", "drama", 1920));
			assert(rep.size() == 2);
			ok = 1;
		}
		catch (BooksRepoException&) {
			ok = 0;
		}

	}

	//nu pot adauga 2 cu acelasi titlu si autor
	try {
		rep.store(Book{ "Robinson Crusoe", "Daniel Defoe", "aventura", 1719 });
	}
	catch (const BooksRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.find("Amintiri din copilarie", "Ion Creanga");
	}
	catch (const BooksRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}


	ok = 0;
	while (ok == 0) {
		//try {
		rep.remove("Ion", "Liviu Rebreanu");
		ok = 1;//}
	//catch (BooksRepoException&) {ok = 0;}
	}

	//incercam sa stergem ceva ce nu exista
	try {
		rep.remove("Primavara", "Andrei P");
	}
	catch (BooksRepoException&) {
		assert(true);
	}

	ok = 0;
	while (ok == 0) {
		try {
			rep.update("Robinson Crusoe", "Daniel Defoe", "dragoste", 1980);
			ok = 1;
		}
		catch (BooksRepoException&) { ok = 0; }
	}

	//incercam sa modificam ceva ce nu exista
	try {
		rep.update("Primavara", "Andrei P", "drama", 1999);
	}
	catch (BooksRepoException&) {
		assert(true);
	}

	rep.findByTitle("Robinson Crusoe");

	try {
		rep.findByTitle("Robinson");
	}
	catch (BooksRepoException&) {
		assert(true);
	}
}


void testAll() {
	testDomain();
	testValidator();
	testSearchRepo();
	testStoreRepo();
	testDeleteRepo();
	testUpdateRepo();
	testAddDelUpdateService();
	testFilterService();
	testSort();
	testCart();
	testCartService();
	testMap();
	testUndo();
	testRepoFile();
	testRepoLab();
}

