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
	Melodie m{ 1, "ibiza", "tyga", "pop" };
	assert(m.getId() == 1);
	assert(m.getTitlu() == "ibiza");
	assert(m.getArtist() == "tyga");
	assert(m.getGen() == "pop");

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

	rep.add(Melodie{ 1, "nirvana", "inna", "disco" });
	rep.add(Melodie{ 2, "jameia", "antonia", "folk" });
	rep.add(Melodie{ 3, "ibiza", "tyga", "pop" });

	assert(rep.getAll().size() == 3);
	
	rep.remove(3);
	
	assert(rep.getAll().size() == 2);
}

void testeService() {

	//stergem continutul fisierului vechi
	std::ofstream out("teste.txt", std::ios::trunc);
	Repo rep{ "teste.txt" };
	Service serv{ rep };
	assert(serv.getAll().size() == 0);

	serv.add("nirvana", "inna", "disco" );
	serv.add("jameia", "antonia", "folk" );
	serv.add("ibiza", "tyga", "pop" );

	assert(serv.getAll().size() == 3);

	serv.remove(3);
	//assert(serv.getAll().size() == 2);
}

void testAll() {
	testeDomain();
	testeRepo();
	testeService();

}
