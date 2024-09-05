#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TicTacToe.h"

#include "Service.h"
#include "MyTableModel.h"

#include <QTableView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QGridLayout>

class TicTacToe : public QWidget
{
private:
	Service& serv;
	QTableView* tblView = new QTableView();
	MyTableModel* tbl = new MyTableModel();
	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtDim = new QLineEdit;
	QLineEdit* txtTabla = new QLineEdit;
	QLineEdit* txtJucator = new QLineEdit;
	QLineEdit* txtStare = new QLineEdit("Neinceput");
	QPushButton* btnAdauga = new QPushButton("&Adauga joc");
	QPushButton* btnUpdate = new QPushButton("&Modifica joc");
	QGridLayout* grid = new QGridLayout();
	vector <QPushButton*> butoane;

	void loadData(vector<Joc>& jocuri) {
		tbl->setJocuri(jocuri);
	};

	void initGUI() {
		QHBoxLayout* lyMain = new QHBoxLayout();
		setLayout(lyMain);

		QVBoxLayout* lyLeft = new QVBoxLayout();
		tblView->setModel(tbl);
		lyLeft->addWidget(tblView);
		lyMain->addLayout(lyLeft);

		QVBoxLayout* lyRight = new QVBoxLayout();
		QFormLayout* formLy = new QFormLayout();
		formLy->addRow("Id: ", txtId);
		formLy->addRow("Dimensiune: ", txtDim);
		formLy->addRow("Tabla: ", txtTabla);
		formLy->addRow("Urmatorul jucator: ", txtJucator);
		formLy->addRow("Stare: ", txtStare);
		lyRight->addLayout(formLy);
		lyRight->addWidget(btnAdauga);
		lyRight->addWidget(btnUpdate);
		lyRight->addLayout(grid);

		lyMain->addLayout(lyRight);

	};
	void initConnect() {
		QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			int dim = txtDim->text().toInt();
			string tabla = txtTabla->text().toStdString();
			string jucator = txtJucator->text().toStdString();
			
			try {
				serv.add(id, dim, tabla, jucator[0], "Neinceput");
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
			});

		QObject::connect(tblView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
			if (tblView->selectionModel()->selectedIndexes().isEmpty()) {
				txtId->setText("");
				txtDim->setText("");
				txtTabla->setText("");
				txtJucator->setText("");
				txtStare->setText("");
			}
			int selRow = tblView->selectionModel()->selectedIndexes().at(0).row();

			auto cellIndex = tblView->model()->index(selRow, 0);
			auto cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtId->setText(cellValue);

			cellIndex = tblView->model()->index(selRow, 1);
			cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtDim->setText(cellValue);

			cellIndex = tblView->model()->index(selRow, 2);
			cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtTabla->setText(cellValue);

			cellIndex = tblView->model()->index(selRow, 3);
			cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtJucator->setText(cellValue);

			cellIndex = tblView->model()->index(selRow, 4);
			cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtStare->setText(cellValue);

			int id = txtId->text().toInt();
			auto joc = serv.find(id);

			int count = 0;
			for (int i = 0; i < joc.getDim(); i++) {

				for (int j = 0; j < joc.getDim(); j++) {
					QPushButton* btn = new QPushButton();
					butoane.push_back(btn);
					string curent = "aaaaaaaaaaaaaaaaaaaaaaaaa";
					curent[0] = joc.getTabla()[count];
					count++;
					curent[1] = '\0';
					curent.erase(1, 25);
					//QMessageBox::warning(this, "warning", QString::fromStdString(curent));
					btn->setText(QString::fromStdString(curent));
					grid->addWidget(btn, i, j);
				}
				
			}

			});

		QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			int dim = txtDim->text().toInt();
			string tabla = txtTabla->text().toStdString();
			string jucator = txtJucator->text().toStdString();
			string stare = txtStare->text().toStdString();

			try {
				serv.update(id, dim, tabla, jucator[0], stare);
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
			});

	};

public:
	TicTacToe(Service& serv) : serv{ serv } {
		loadData(serv.sortStare());
		initGUI();
		initConnect();
	}
};
