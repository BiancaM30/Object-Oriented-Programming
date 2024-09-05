#include "Service.h"
#include <time.h>

void Service::add(const string titlu, const string artist, const string gen) {
	srand(time(NULL));
	auto melodii = rep.getAll();
	bool gasit = 0;
	int id;
	while (gasit == 0) {
		id = rand() % 100;
		gasit = 1;
		for (auto& melodie : melodii) {
			if (melodie.getId() == id) {
				gasit = 0; //inseamna ca id-ul exista deja si trebuie sa generam alt numar
			}
		}
	}
	Melodie m{ id, titlu, artist, gen };
	rep.add(m);
}

const vector<Melodie>& Service::getAll() {
	return rep.getAll();
}

vector<Melodie> Service::sortAuthor() const {
	auto melodii = rep.getAll();
	for (int i = 0; i < melodii.size() - 1; i++) {
		for (int j = i + 1; j < melodii.size(); j++) {
			if (melodii.at(j).getArtist() < melodii.at(i).getArtist()) {
				std::swap(melodii.at(j), melodii.at(i));
			}
		}
	}
	return melodii;
}

void Service::remove(int id) {
	rep.remove(id);
}