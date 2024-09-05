#pragma once

#include <QAbstractTableModel>
#include "Joc.h"

using std::vector;

class MyTableModel :public QAbstractTableModel {
private:
	vector<Joc> jocuri;
public:
	MyTableModel() {};

	MyTableModel(const vector<Joc>& jocuri) : jocuri{ jocuri } {};

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return jocuri.size();
	}

	void setJocuri(const vector<Joc>& jocuri) {
		this->jocuri = jocuri;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}

	QVariant data(const QModelIndex& index, int role) const override {
		if (role == Qt::DisplayRole) {
			Joc j = jocuri[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(std::to_string(j.getId()));
			}
			if (index.column() == 1) {
				return QString::fromStdString(std::to_string(j.getDim()));
			}
			if (index.column() == 2) {
				return QString::fromStdString(j.getTabla());
			}
			if (index.column() == 3) {
				return QString::fromStdString(std::string(1,j.getJucator()));
			}
			if (index.column() == 4) {
				return QString::fromStdString(j.getStare());
			}
		}
		return QVariant{};
	}
};