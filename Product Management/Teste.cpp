#include "Teste.h"
#include "Produs.h"
#include "ProdusValidator.h"
#include "Repo.h"
#include "Service.h"

#include <assert.h>
#include <sstream>
#include <fstream>
#include <ostream>

using namespace std;

void TesteDomain() {
	Produs p{ 1,"zuzu", "lactate", 8.5 };
	assert(p.getId() == 1);
	assert(p.getNume() == "zuzu");
	assert(p.getTip() == "lactate");
	assert(p.getPret() == 8.5);
	assert(p.getVocale() == 2);

	ProdusValidator val;
	Produs p2{ 3, "", "lactate", 133333 };
	try
	{	
		val.validate(p2);
	}
	catch (ValidateException & ex)
	{
		assert(ex.getMsg().size() == 2);
	}
}

void TesteRepo() {
	try {
		Repo rep{ "aa.txt" };
	}
	catch (exception) {
		assert(true);
	}

	//stergem continutul fisierului vechi
	std::ofstream out("teste.txt", std::ios::trunc);
	Repo rep{ "teste.txt" };
	assert(rep.getAll().size() == 0);
	
	rep.add(Produs{ 1, "zuzu", "lactate", 8.3 });
	rep.add(Produs{ 2, "milka", "dulciuri", 4.6 });
	rep.add(Produs{ 3, "dorna", "lactate", 7.1 });
	rep.add(Produs{ 4,"coca cola","bauturi",3.0});

	assert(rep.getAll().size() == 4);

	Produs p{ 3,"apa","bauturi",2};
	try
	{
		rep.add(p);
	}
	catch (RepoException& ex)
	{
		assert(ex.getMsg().size() != 0);
	}
}

void TesteService() {
	//stergem continutul fisierului vechi
	std::ofstream out("teste.txt", std::ios::trunc);
	Repo rep{ "teste.txt" };
	ProdusValidator val;
	Service serv{ rep , val };
	assert(serv.getAll().size() == 0);

	serv.add(1, "zuzu", "lactate", 8.3 );
	serv.add( 2, "milka", "dulciuri", 4.6 );
	serv.add(3, "dorna", "lactate", 7.1 );
	serv.add(4,"coca cola","bauturi",3.0 );

	assert(serv.getAll().size() == 4);

}

void TestAll() {
	TesteDomain();
	TesteRepo();
	TesteService();
}
