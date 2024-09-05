#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Programatori.h"

#include "Service.h"
#include "MyTableModel.h"

#include <QTableView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>

class Observer {
public:
	virtual void update() = 0;
};

class FereastraStare : public Observer, QWidget {
public:
	Service& serv;
	vector <Observer*>& observers;
	string stare;

	QWidget* fereastra = new QWidget();
	QVBoxLayout* lyMain = new QVBoxLayout();
	QTableView* tblView = new QTableView();
	MyTableModel* tbl = new MyTableModel();
	QPushButton* btnClosed = new QPushButton("&Closed");
	QPushButton* btnOpen = new QPushButton("&Open");
	QPushButton* btnProgress = new QPushButton("&In progress");
	QLineEdit* txtId = new QLineEdit();

	FereastraStare(Service& serv, vector<Observer*>& observers, string stare) : serv{ serv }, observers{ observers }, stare{ stare }{
		loadData(serv.filtrareStare(stare));
		initGUI();
		update();
		initConnect();
	};

	void loadData(const vector<Task>& taskuri) {
		tbl->setTaskuri(taskuri);
	}
	void initGUI() {
		this->setLayout(lyMain);
		this->setWindowTitle(QString::fromStdString(stare));
		this->setFixedHeight(400);
		this->setFixedWidth(400);
		tblView->setModel(tbl);
		lyMain->addWidget(tblView);
		lyMain->addWidget(btnOpen);
		lyMain->addWidget(btnClosed);
		lyMain->addWidget(btnProgress);

		this->show();
	}
	void update() override {
		loadData(serv.filtrareStare(stare));
	}

	void notifyObservers() {
		for (auto& o : observers) {
			o->update();
		}
	}

	void initConnect() {
		QObject::connect(tblView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
			int selRow = tblView->selectionModel()->selectedIndexes().at(0).row();

			auto cellIndex = tblView->model()->index(selRow, 0);
			auto cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtId->setText(cellValue);


			});

		QObject::connect(btnClosed, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			serv.updateStare(id, "closed");
			update();
			notifyObservers();
			});
		QObject::connect(btnProgress, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			serv.updateStare(id, "inprogress");
			update();
			notifyObservers();
			});
		QObject::connect(btnOpen, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			serv.updateStare(id, "open");
			update();
			notifyObservers();
			});
	}
};
class Programatori : public QWidget
{
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void notifyObservers() {
		for (auto& o : observers) {
			o->update();
		}
	}

private:
	vector <Observer*> observers;

	Service& serv;
	QTableView* tblView = new QTableView();
	MyTableModel* tbl = new MyTableModel();
	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtDescriere = new QLineEdit;
	QLineEdit* txtProgramatori = new QLineEdit;
	QLineEdit* txtStare = new QLineEdit;
	QPushButton* btnAdauga = new QPushButton("&Adauga task");
	QLineEdit* txtSearch = new QLineEdit;

	void loadData(vector<Task>& taskuri) {
		tbl->setTaskuri(taskuri);
	};

	void initGUI() {
		addObserver(new FereastraStare{ serv, observers, "open" });
		addObserver(new FereastraStare{ serv, observers, "inprogress" });
		addObserver(new FereastraStare{ serv, observers, "closed" });
		
		QHBoxLayout* lyMain = new QHBoxLayout();
		setLayout(lyMain);

		QVBoxLayout* lyLeft = new QVBoxLayout();
		tblView->setModel(tbl);
		lyLeft->addWidget(tblView);
		lyMain->addLayout(lyLeft);

		QVBoxLayout* lyRight = new QVBoxLayout();
		QFormLayout* formLy = new QFormLayout();
		formLy->addRow("Id: ", txtId);
		formLy->addRow("Descriere: ", txtDescriere);
		formLy->addRow("Programatori(separati prin virgula): ", txtProgramatori);
		formLy->addRow("Stare: ", txtStare);
		lyRight->addLayout(formLy);
		lyRight->addWidget(btnAdauga);

		QFormLayout* formLy2 = new QFormLayout();
		formLy->addRow("Cauta: ", txtSearch);
		lyRight->addLayout(formLy2);

		lyMain->addLayout(lyRight);

	};
	void initConnect() {
		QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			string descriere = txtDescriere->text().toStdString();
			string nume = txtProgramatori->text().toStdString();
			string stare = txtStare->text().toStdString();
			
			vector<string> programatori;
			//trebuie sa delimitam numele programatorilor
			string delim = ",";
			while (nume.find(delim) != string::npos) {
				auto pos = nume.find(delim);
				programatori.push_back(nume.substr(0, pos));
				nume = nume.erase(0, pos + 1);
			}
			//facem separat pt ultimul
			programatori.push_back(nume);

			try {
				serv.add(id, descriere, programatori, stare);
				loadData(serv.sortStare());
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMsg()));
			}
			catch (ValidateException& ex) {
				vector<string> errors = ex.getMsg();
				for (auto error : errors) {
					QMessageBox::warning(this, "warning", QString::fromStdString(error));
				}
			}
			notifyObservers();
			});

		QObject::connect(txtSearch, &QLineEdit::textChanged, [&]() {
			string substring = txtSearch->text().toStdString();
			loadData(serv.filtrareString(substring));
			});
	};

public:
	Programatori(Service& serv) : serv{serv} {
		loadData(serv.sortStare());
		initGUI();
		initConnect();
	}
};
