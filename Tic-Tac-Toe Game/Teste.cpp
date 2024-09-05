#pragma once
#include "Teste.h"
#include "Joc.h"
#include "Repo.h"
#include "Service.h"
#include "JocValidator.h"

#include <assert.h>
#include <sstream>
#include <istream>
#include <fstream>

using namespace std;

void testeDomain() {
	Joc j{ 1,3,"X-OXO-XOO",'X',"Terminat" };
	assert(j.getId() == 1);
	assert(j.getDim() == 3);
	assert(j.getTabla() == "X-OXO-XOO");
	assert(j.getJucator() == 'X');
	assert(j.getStare() == "Terminat");
}

void testeRepo() {
	try {
		Repo rep{ "aa.txt" };
	}
	catch (exception) {
		assert(true);
	}

	//stergem continutul fisierului vechi
	std::ofstream out("test.txt", std::ios::trunc);
	Repo rep{ "test.txt" };
	assert(rep.getAll().size() == 0);
	
	rep.add(Joc{1, 3,"X-OXO-XOO", 'X', "Terminat" });
	rep.add(Joc{2, 3,"-X--OX----O-",'X',"In derulare"});
	rep.add(Joc{ 3, 3,"---------",'O',"Neinceput" });

	assert(rep.getAll().size() == 3);

	Joc j{ 1, 3,"X-----XOO", 'X', "In derulare" };
	try {
		rep.add(j);
	}
	catch (RepoException& ex)
	{
		assert(ex.getMsg().size() != 0);
	}
	
}

void testeService() {

	//stergem continutul fisierului vechi
	std::ofstream out("test.txt", std::ios::trunc);
	Repo rep{ "test.txt" };
	JocValidator val;
	Service serv{ rep,val };

	assert(rep.getAll().size() == 0);

	serv.add(1, 3,"X-OXO-XOO", 'X', "Terminat");
	serv.add(2, 3,"-X--OX---",'O',"In derulare");
	serv.add(3, 3,"---------",'O',"Neinceput" );

	assert(serv.getAll().size() == 3);

	try {
		serv.add(6, 10, "X--ta---XOOgbdfvscbfd", 'p', "aaa");
	}
	catch (ValidateException& ex)
	{
		assert(ex.getMsg().size() != 0);
	}

	vector<Joc>rez = serv.sortStare();
	assert(rez[0].getStare() == "In derulare");
}

void testAll()
{
	testeDomain();
	testeRepo();
	testeService();
}