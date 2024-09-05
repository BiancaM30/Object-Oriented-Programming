#include "Service.h"

void Service::add(int id, int dim, string tabla, char jucator, string stare) {
	Joc p{ id, dim,tabla,jucator,stare };
	val.validate(p);
	rep.add(p);

}

void Service::update(int id, int dim_nou, string tabla_nou, char jucator_nou, string stare_nou) {
	Joc j{ id, dim_nou,tabla_nou,jucator_nou,stare_nou };
	val.validate(j);
	rep.update(j);
}
const vector<Joc>& Service::getAll() {
	return rep.getAll();
}

vector<Joc> Service::sortStare() const {
	auto jocuri = rep.getAll();
	for (int i = 0; i < jocuri.size() - 1; i++) {
		for (int j = i + 1; j < jocuri.size(); j++) {
			if (jocuri.at(j).getStare() < jocuri.at(i).getStare()) {
				std::swap(jocuri.at(j), jocuri.at(i));
			}
		}
	}
	return jocuri;
}

Joc Service::find(int id) {
	vector<Joc> jocuri = rep.getAll();
	for (auto& joc : jocuri) {
		if (joc.getId() == id) {
			return joc;
		}
	}
}