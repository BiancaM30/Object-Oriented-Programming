#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProduseGUI.h"

#include "Service.h"
#include "MyTableModel.h"

#include <qtablewidget.h>
#include <QHeaderView>
#include <qstandarditemmodel.h>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QLabel>
#include <QFormLayout>

#include <vector>
#include <algorithm>
#include <QListView>


using std::vector;

class Observer {
public:
	virtual void update() = 0;
};

class FereastraTip : public Observer, QWidget
{
public:
	Service& serv;
	vector <Observer*>& observers;
	string tip;

	QWidget* fereastra = new QWidget();
	QVBoxLayout* lyMain = new QVBoxLayout();
	QLabel* lbl = new QLabel();
	

	FereastraTip(Service& serv, vector<Observer*>& observers, string tip) : serv{ serv }, observers{ observers }, tip{tip}{
		loadData(serv.getAll());
		initGUI();
		update();
		
	};
	void loadData(const vector<Produs>& produse) {
		int nr = 0;
		for (auto& produs : produse) {
			if (produs.getTip() == tip) {
				nr++;
			}
		}

		lbl->setText(QString::number(nr));
	}
	void initGUI() {
		this->setLayout(lyMain);
		this->setWindowTitle(QString::fromStdString(tip));
		this->setFixedHeight(400);
		this->setFixedWidth(400);
		lyMain->addWidget(lbl);
		this->show();
	}
	void update() override{
		loadData(serv.getAll());
	}
	
};

class ProduseGUI : public QWidget
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
	//QListView* tblView = new QListView();
	MyTableModel* tbl = new MyTableModel();

	QPushButton* btnAdauga = new QPushButton("&Adauga produs");
	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtNume = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;

	QSlider* slider = new QSlider(Qt::Horizontal);
	QLabel* txtSlider = new QLabel("1");

	QPushButton* btnFerestre = new QPushButton("&Deschide ferestre");

	void loadData(const vector<Produs>& produse) {
		tbl->setProduse(produse);
	}

	void initGUI() {
		auto produse = serv.getAll();
		vector<string> tipuri;
		for (auto produs : produse) {
			if (!(std::find(tipuri.begin(), tipuri.end(), produs.getTip()) != tipuri.end())) {
				addObserver(new FereastraTip{ serv,observers, produs.getTip() });
				tipuri.push_back(produs.getTip());
			}
		}

		QHBoxLayout* lyMain = new QHBoxLayout{};
		setLayout(lyMain);

		QVBoxLayout* lyLeft = new QVBoxLayout{};
		//tblView->setUniformItemSizes(true);
		tblView->setModel(tbl);
		lyLeft->addWidget(tblView);
		lyMain->addLayout(lyLeft);

		QVBoxLayout* lyRight = new QVBoxLayout{};
		QFormLayout* formLy = new QFormLayout();
		formLy->addRow("Id: ", txtId);
		formLy->addRow("Nume: ", txtNume);
		formLy->addRow("Tip: ", txtTip);
		formLy->addRow("Pret: ", txtPret);
		lyRight->addLayout(formLy);
		lyRight->addWidget(btnAdauga);

		QHBoxLayout* lySlider = new QHBoxLayout{};
		slider->setMinimum(1);
		slider->setMaximum(100);
		slider->setValue(1);
		lySlider->addWidget(slider);
		lySlider->addWidget(txtSlider);
		lyRight->addLayout(lySlider);
		lyRight->addWidget(btnFerestre);
		lyMain->addLayout(lyRight);
	}

	void initConnect() {
		QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
			auto id = txtId->text().toInt();
			auto nume = txtNume->text().toStdString();
			auto tip = txtTip->text().toStdString();
			auto pret = txtPret->text().toDouble();

			try {
				serv.add(id, nume, tip, pret);
				loadData(serv.sortPret());
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

		QObject::connect(slider, &QSlider::valueChanged, [&]() {
			txtSlider->setText(QString::number(slider->value()));
			int pret = slider->value();
			this->tbl->setSliderValue(pret);
		});

	}
public:
	ProduseGUI(Service& serv) : serv{ serv } {
		loadData(serv.sortPret());
		initGUI();
		initConnect();
	};

};
