#pragma once
#include "Repo.h"
#include "TaskValidator.h"

class Service
{
private:
	Repo& rep;
	TaskValidator& val;

public:
	//Constructor
	Service(Repo& rep, TaskValidator& validator) : rep{ rep }, val{ validator } {};

	//Constructor de copiere
	Service(const Service& ot) = delete;

	void add(int id, string descriere, vector<string> programatori, string stare);

	const vector<Task>& getAll();

	vector<Task> sortStare() const;

	//Cauta doar numele programatorilor care contin stringul dat
	vector<Task> filtrareString(string s) const;

	//filtreaza dupa stare
	vector<Task> filtrareStare(string stare) const;

	void updateStare(int id, string stare);
};

