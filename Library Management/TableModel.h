#pragma once
#include <QAbstractTableModel>
#include "Book.h"

using std::vector;

class MyTableModel : public QAbstractTableModel {
	vector<Book> books;


public:
	MyTableModel() {}
	

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return books.size();
	}
	
	void setBooks(const std::vector<Book>& books) {
		this->books = books;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}

	QVariant data(const QModelIndex& index , int role) const override {
		if (role == Qt::DisplayRole) {
			Book b = books[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(b.getTitle());
			if (index.column() == 1)
				return QString::fromStdString(b.getAuthor());
			if (index.column() == 2)
				return QString::fromStdString(b.getGenre());
			if (index.column() == 3) {
				char year[10];
				return QString::fromStdString(itoa(b.getYear(), year,10));
			}
		}
		return QVariant{};
	}
	
	
	MyTableModel(const vector<Book>& books) : books{ books } {};
};
