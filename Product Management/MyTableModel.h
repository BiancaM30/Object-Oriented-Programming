#pragma once

#include <QAbstractTableModel>
#include "Produs.h"

using std::vector;

class MyTableModel:public QAbstractTableModel{
private:
	vector<Produs> produse;

	int sliderValue = 0;
public:
	MyTableModel() {};

	MyTableModel(const vector<Produs>& produse) : produse{produse} {};

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}

	void setProduse(const vector<Produs>& produse) {
		this->produse = produse;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}

	QVariant data(const QModelIndex& index, int role) const override {
		if (role == Qt::BackgroundRole) {
			Produs p = produse[index.row()];
			if (p.getPret() < this->sliderValue) {
				return QBrush{ Qt::red };
			}
		}
		if (role == Qt::DisplayRole) {
			Produs p = produse[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(std::to_string(p.getId()));
			}
			if (index.column() == 1) {
				return QString::fromStdString(p.getNume());
			}
			if (index.column() == 2) {
				return QString::fromStdString(p.getTip());
			}
			if (index.column() == 3) {
				return QString::fromStdString(std::to_string(p.getPret()));
			}
			if (index.column() == 4) {
				return QString::fromStdString(std::to_string(p.getVocale()));
			}
		}
		return QVariant{};
	}

	void setSliderValue(int newValue) {
		this->sliderValue = newValue;
		emit this->dataChanged(this->index(0, 0), this->index(this->produse.size(), 5));
	}
};