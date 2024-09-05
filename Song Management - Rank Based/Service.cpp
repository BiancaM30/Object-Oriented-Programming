#include "Service.h"

void Service::add(const Melodie& mel) {
	rep.add(mel);
}

const vector<Melodie>& Service::getAll() {
	return rep.getAll();
}

vector<Melodie> Service::sortRank() const {
	auto melodii = rep.getAll();
	for (int i = 0; i < melodii.size() - 1; i++) {
		for (int j = i + 1; j < melodii.size(); j++) {
			if (melodii.at(j).getRank() < melodii.at(i).getRank()) {
				std::swap(melodii.at(j), melodii.at(i));
			}
		}
	}
	return melodii;
}

void Service::update(int id, string titlu_nou, int rank_nou) {
	rep.update(id, titlu_nou, rank_nou);
}

void Service::remove(int id) {
	rep.remove(id);
}