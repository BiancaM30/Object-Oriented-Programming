#pragma once

#include <QAbstractTableModel>
#include "Task.h"

using std::vector;

class MyTableModel :public QAbstractTableModel {
private:
	vector<Task> taskuri;
public:
	MyTableModel() {};

	MyTableModel(const vector<Task>& taskuri) : taskuri{ taskuri } {};

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return taskuri.size();
	}

	void setTaskuri(const vector<Task>& taskuri) {
		this->taskuri = taskuri;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}

	QVariant data(const QModelIndex& index, int role) const override {
		if (role == Qt::DisplayRole) {
			Task t = taskuri[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(std::to_string(t.getId()));
			}
			if (index.column() == 1) {
				return QString::fromStdString(t.getDescriere());
			}
			if (index.column() == 2) {
				return QString::fromStdString(t.getStare());
			}
			if (index.column() == 3) {
				return QString::fromStdString(std::to_string(t.getProgramatori().size()));
			}
			
		}
		return QVariant{};
	}
};