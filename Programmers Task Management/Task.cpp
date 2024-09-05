#include "Task.h"

int Task::getId() const {
	return id;
}

string Task::getDescriere() const {
	return descriere;
}

vector<string> Task::getProgramatori() const {
	return programatori;
}

string Task::getStare() const {
	return stare;
}
void Task::setStare(string newStare) {
	stare = newStare;
}