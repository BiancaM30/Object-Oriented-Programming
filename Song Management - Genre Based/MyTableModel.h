#pragma once
#include "Melodie.h"

#include <QAbstractTableModel>

#include <vector>
using std::vector;


class MyTableModel : public QAbstractTableModel {
private:
	vector<Melodie> melodii;
public:
	MyTableModel() {};

	MyTableModel(const vector<Melodie>& melodii) : melodii{ melodii } {};

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 6;
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return melodii.size();
	}

	void setMelodii(const vector<Melodie>& melodii) {
		this->melodii = melodii;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}

	QVariant data(const QModelIndex& index, int role) const override {
		if (role == Qt::DisplayRole) {
			Melodie m = melodii[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(std::to_string(m.getId()));
			}
			if (index.column() == 1) {
				return QString::fromStdString(m.getTitlu());
			}
			if (index.column() == 2) {
				return QString::fromStdString(m.getArtist());
			}
			if (index.column() == 3) {
				return QString::fromStdString(m.getGen());
			}
			if (index.column() == 4) {
				int nr = 0;
				for (auto& melodie : melodii) {
					if (melodie.getId() != m.getId() && melodie.getArtist() == m.getArtist()) {
						nr++;
					}	
				}
				return QString::fromStdString(std::to_string(nr));
			}
			if (index.column() == 5) {
				int nr = 0;
				for (auto& melodie : melodii) {
					if (melodie.getId() != m.getId() && melodie.getGen() == m.getGen()) {
						nr++;
					}
				}
				return QString::fromStdString(std::to_string(nr));
			}
			
		}
		return QVariant{};
	}
};

