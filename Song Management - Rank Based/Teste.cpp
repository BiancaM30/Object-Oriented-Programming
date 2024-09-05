#pragma once
#include "Melodie.h";
#include "Repo.h"
#include "Service.h"

#include <assert.h>

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

using namespace std;

void testeDomain() {
	Melodie m{ 1, "ibiza", "tyga", 10 };
	assert(m.getId() == 1);
	assert(m.getTitlu() == "ibiza");
	assert(m.getArtist() == "tyga");
	assert(m.getRank() == 10);

	m.setTitlu("San Tropez");
	m.setRank(6);
	assert(m.getTitlu() == "San Tropez");
	assert(m.getRank() == 6);
}

void testeRepo() {
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

	rep.add(Melodie{ 1, "nirvana", "inna", 1 });
	rep.add(Melodie{ 2, "jameia", "antonia", 7 });
	rep.add(Melodie{ 3, "ibiza", "tyga", 7 });
		
	assert(rep.getAll().size() == 3);

	rep.update(2, "Vara", 3);
	assert(rep.getAll()[1].getTitlu() == "Vara");

	try {
		rep.remove(3);
	}
	catch (std::exception) {
		assert(true);
	}
	rep.add(Melodie{ 4, "suna-ma", "antonia", 3 });
	rep.remove(2);
	assert(rep.getAll().size() == 3);
}

void testeService() {

	//stergem continutul fisierului vechi
	std::ofstream out("teste.txt", std::ios::trunc);
	Repo rep{ "teste.txt" };
	Service serv{ rep };
	assert(serv.getAll().size() == 0);

	serv.add(Melodie{ 1, "nirvana", "inna", 1 });
	serv.add(Melodie{ 2, "jameia", "antonia", 7 });
	serv.add(Melodie{ 3, "ibiza", "tyga", 7 });

	assert(serv.getAll().size() == 3);

	serv.update(2, "Vara", 3);
	assert(serv.getAll()[1].getTitlu() == "Vara");

	try {
		serv.remove(3);
	}
	catch (std::exception) {
		assert(true);
	}
	serv.add(Melodie{ 4, "suna-ma", "antonia", 3 });
	serv.remove(2);
	assert(serv.getAll().size() == 3);
}

void testAll() {
	testeDomain();
	testeRepo();
	testeService();

}
