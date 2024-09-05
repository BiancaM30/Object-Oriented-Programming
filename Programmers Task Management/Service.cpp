#include "Service.h"

void Service::add(int id, string descriere, vector<string> programatori, string stare) {
	Task t{ id, descriere, programatori, stare };
	val.validate(t);
	rep.add(t);

}

const vector<Task>& Service::getAll() {
	return rep.getAll();
}

vector<Task> Service::sortStare() const {
	auto taskuri = rep.getAll();
	for (int i = 0; i < taskuri.size() - 1; i++) {
		for (int j = i + 1; j < taskuri.size(); j++) {
			if (taskuri.at(j).getStare() < taskuri.at(i).getStare()) {
				std::swap(taskuri.at(j), taskuri.at(i));
			}
		}
	}
	return taskuri;
}

vector<Task> Service::filtrareString(string s) const {
	auto taskuri = rep.getAll();
	vector<Task> rez;
	for (auto& task : taskuri) {
		vector<string> nume = task.getProgramatori();
		for (auto& n : nume) {
			if (n.find(s)!=string::npos) {
				rez.push_back(task);
				break;
			}
		}
	}
	return rez;
}

vector<Task> Service::filtrareStare(string stare) const {
	auto taskuri = rep.getAll();
	vector<Task> rez;
	for (auto& task : taskuri) {
		if (task.getStare() == stare) {
			rez.push_back(task);
		}
	}
	return rez;
}

void Service::updateStare(int id, string stare) {
	rep.updateStare(id, stare);
}