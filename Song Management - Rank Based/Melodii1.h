#pragma once
#include "Service.h"

#include <QtWidgets/QMainWindow>
#include "ui_Melodii1.h"
#include "MyTableModel.h"


#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <random>
#include <QListView>

class Observer {
public:
	virtual void update() = 0;
};

class Melodii1 : public QWidget, Observer
{
private:
	Service& serv;

	QTableView* tblView = new QTableView();
	//QListView* tblView = new QListView();
	MyTableModel* tbl = new MyTableModel();
	QLineEdit* txtTitle = new QLineEdit;
	QLineEdit* txtId = new QLineEdit;
	QSlider* slider = new QSlider(Qt::Horizontal);
	QLabel* lblSlider = new QLabel("0");
	QPushButton* btnUpdate = new QPushButton("Update");
	QPushButton* btnDelete = new QPushButton("Delete");

	void loadData(const vector<Melodie>& melodii) {
		
		tbl->setMelodii(melodii);
	}

	void initGUI() {
		QHBoxLayout* lyMain = new QHBoxLayout{};
		setLayout(lyMain);

		QVBoxLayout* lyLeft = new QVBoxLayout{};
		//tblView->setUniformItemSizes(true);
		tblView->setModel(tbl);
		lyLeft->addWidget(tblView);
		lyMain->addLayout(lyLeft);

		QVBoxLayout* lyRight = new QVBoxLayout{};
		QHBoxLayout* lySlider = new QHBoxLayout{};
		slider->setMinimum(0);
		slider->setMaximum(10);
		lySlider->addWidget(slider);
		lySlider->addWidget(lblSlider);
		lyRight->addLayout(lySlider);

		lyRight->addWidget(txtTitle);
		lyRight->addWidget(btnUpdate);
		lyRight->addWidget(btnDelete);
		lyMain->addLayout(lyRight);
	}

	void initConnect() {
		QObject::connect(tblView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
			if (tblView->selectionModel()->selectedIndexes().isEmpty()) {
				txtTitle->setText("");
			}
			int selRow = tblView->selectionModel()->selectedIndexes().at(0).row();

			auto cellIndex = tblView->model()->index(selRow, 1);
			auto cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtTitle->setText(cellValue);

			cellIndex = tblView->model()->index(selRow, 0);
			cellValue = tblView->model()->data(cellIndex, Qt::DisplayRole).toString();
			txtId->setText(cellValue);

			
			});

		QObject::connect(slider, &QSlider::valueChanged, [&]() {
			lblSlider->setText(QString::number(slider->value()));
			});


		QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			string title = txtTitle->text().toStdString();
			int rank = lblSlider->text().toInt();
			serv.update(id, title, rank);
			loadData(serv.sortRank());
			this->update();
			});

		QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			try {
				serv.remove(id);
			}
			catch (std::exception& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString("Nu se poate sterge deoarece e ultima melodie a artistului"));
			}
			loadData(serv.sortRank());
			this->update();
			});
	}
	void paintEvent(QPaintEvent* ev) override {
		ev;
		QPainter p{ this };
		for (int i = 0; i < 10; i++) {
			QPainter p{ this };
			int x = 10;
			for (i = 0; i <= 10; i++) {
				
				//p.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
				//p.drawLine(i+10, i+10, i+20, i+20);
				p.drawRect(x, 0, 20, 30);
				x += 40;
			}

		}
	}

	void update() override {
		this->repaint();
	}
	

public:
	Melodii1(Service& serv) : serv{serv} {
		loadData(serv.sortRank());
		initGUI();
		initConnect();
		update();
	}
};
