#include "Teste.h"

#include "BibliotecaGUIObserver.h"
#include <QtWidgets/QApplication>
#include "AbstractRepo.h"
#include "BooksRepo.h"
#include "BooksRepoFile.h"
#include "BooksRepoLab.h"
#include "Biblioteca.h"
#include "BookValidator.h"
#include "CustomerCart.h"

void initEntities(Biblioteca& ctr) {
	//adaug cateva elemente in service
	try {
		ctr.addBook("Fata din Tren", "Paula Hawkins", "thriller", 2015);
		ctr.addBook("Ion", "Liviu Rebreanu", "drama", 1920);
		ctr.addBook("Padurea spanzuratilor", "Liviu Rebreanu", "psihologic", 1920);
		ctr.addBook("Institutul", "Stephen King", "thriller", 2019);
		ctr.addBook("Adam si Eva", "Liviu Rebreanu", "psihologic", 1925);
		ctr.addBook("Robinson Crusoe", "Daniel Defoe", "actiune", 1719);
		ctr.addBook("Amintiri din copilarie", "Ion Creanga", "autobiografie", 1879);
		ctr.addBook("Martianul", "Andy Weir", "actiune", 2015);
	}
	catch (BooksRepoException&) {
		return;
	}

}

int main(int argc, char* argv[])
{
	testAll();
	{
		QApplication a(argc, argv);

		//BooksRepo rep;
		BooksRepoFile rep{ "books.txt" };
		BookValidator val;
		Biblioteca serv{ rep,val };
		initEntities(serv);
		BibliotecaGUIObserver gui{ serv };
		gui.show();
		return a.exec();
	}
}


