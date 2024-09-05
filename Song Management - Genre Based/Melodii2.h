#pragma once
#include "Service.h"
#include "MyTableModel.h"

#include <QtWidgets/QMainWindow>
#include "ui_Melodii2.h"
#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QPainter>

class Observer {
public:
	virtual void update() = 0;
};

class Melodii2 : public QWidget, Observer
{
private:
	Service& serv;
	QTableView* tblView = new QTableView();
	MyTableModel* tbl = new MyTableModel();
	
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtArtist = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QPushButton* btnAdd = new QPushButton("&Add");

	QPushButton* btnDelete = new QPushButton("&Delete");
	QLineEdit* txtId = new QLineEdit; //il vom folosi ca sa retinem id-ul selectiei curente

	void loadData(const vector<Melodie>& melodii) {
		tbl->setMelodii(melodii);

	}
	void initGUI() {
		QHBoxLayout* lyMain = new QHBoxLayout();
		setLayout(lyMain);

		QVBoxLayout* lyLeft = new QVBoxLayout();
		tblView->setModel(tbl);
		lyLeft->addWidget(tblView);
		lyMain->addLayout(lyLeft);

		QVBoxLayout* lyRight = new QVBoxLayout();
		QFormLayout* formLy = new QFormLayout();
		formLy->addRow("Titlu: ", txtTitlu);
		formLy->addRow("Artist: ", txtArtist);
		formLy->addRow("Gen: ", txtGen);
		lyRight->addLayout(formLy);
		lyRight->addWidget(btnAdd);

		lyRight->addWidget(btnDelete);
		lyMain->addLayout(lyRight);
	}
	void initConnect() {
		QObject::connect(tblView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
			int selRow = tblView->selectionModel()->selectedIndexes().at(0).row();

			auto cellIndex = tblView->model()->index(selRow, 0);
			auto cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtId->setText(cellValue);

			});

		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			
			string titlu = txtTitlu->text().toStdString();
			string artist = txtArtist->text().toStdString();
			string gen = txtGen->text().toStdString();
		
			serv.add(titlu, artist, gen);
			loadData(serv.sortAuthor());

			});

		QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			serv.remove(id);
			loadData(serv.sortAuthor());

			});
	}
	void paintEvent(QPaintEvent* ev) override {
		ev;
		QPainter p{ this };
		for (int i = 0; i < 10; i++) {
			QPainter p{ this };
			int x = 10;
			for (i = 0; i <= 10; i++) {

				//p.drawArc(9,80, 90);
				x += 40;
			}

		}
	}
	void update() override {
		this->repaint();
	}
public:
	Melodii2(Service& serv) : serv{ serv } {
		loadData(serv.sortAuthor());
		initGUI();
		initConnect();
	};

};