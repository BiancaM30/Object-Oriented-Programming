#pragma once
#include "Task.h"
#include "Repo.h"
#include "Service.h"
#include "TaskValidator.h"

#include <assert.h>
#include <QDebug>
#include <sstream>
#include <fstream>
#include <ostream>

using namespace std;

void testeDomain() {
	vector<string> nume = { "bogdan", "ana" };
	Task t1{ 1, "combo box", nume, "open" };
	assert(t1.getId() == 1);
	assert(t1.getDescriere() == "combo box");
	assert(t1.getProgramatori() == nume);
	assert(t1.getStare() == "open");
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
	
	vector<string> nume = { "bogdan", "ana" };
	Task t1{ 1, "combo box", nume, "open" };
	vector<string> nume2 = { "silviu,ana,marius" };
	Task t2{ 2, "slider an", nume2, "inprogress" };
	vector<string> nume3 = { "ana,paul,radu" };
	Task t3{ 3, "tabel", nume3, "inprogress" };

	rep.add(t1);
	rep.add(t2);
	rep.add(t3);
	assert(rep.getAll().size() == 3);

	Task t4{ 3, "aaa", nume3, "inprogress" };
	try
	{
		rep.add(t4);
	}
	catch (RepoException& ex)
	{
		assert(ex.getMsg().size() != 0);
	}
}

void testeService() {
	//stergem continutul fisierului vechi
	std::ofstream out("teste.txt", std::ios::trunc);
	Repo rep{ "teste.txt" };
	TaskValidator val;
	Service serv{ rep, val };
	assert(rep.getAll().size() == 0);

	vector<string> nume = { "bogdan", "ana" };
	vector<string> nume2 = { "silviu,ana,marius" };
	vector<string> nume3 = { "ana,paul,radu" };
	serv.add(1, "combo box", nume, "open");
	serv.add(2, "slider an", nume2, "inprogress");
	serv.add(3, "tabel", nume3, "inprogress");
	assert(serv.getAll().size() == 3);

	try {
		serv.add(1, "", {}, "aaa");
	}
	catch (ValidateException& ex) {
		assert(true);
	}
	vector<Task> rez = serv.sortStare();
	assert(rez.at(0).getStare() == "inprogress");
}

void testAll() {
	testeDomain();
	testeRepo();
	testeService();
}