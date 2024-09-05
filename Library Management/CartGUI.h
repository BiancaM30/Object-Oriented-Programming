#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BibliotecaGUIObserver.h"

#include "Biblioteca.h"
#include "BibliotecaGUIObserver.h"
#include <iostream>

#include <qstring.h>
#include <QString.h>
#include <QtWidgets/qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget.h>
#include <QFormLayout.h>
#include <QLineEdit.h>
#include <QPushButton.h>
#include <qDebug>
#include <QMessageBox.h>
#include <qpalette.h>
#include <qbrush.h>
#include <QTableWidget.h>
#include <QStandardItemModel.h>
#include <QHeaderView>
#include <QLabel.h>


/*class CartGUI : public QWidget, Observer
{
private:
    Biblioteca& serv;

    QListWidget* lst = new QListWidget;
    QLabel* total = new QLabel;
    QPushButton* btnAdd = new QPushButton("&Adauga in cos");
    QPushButton* btnEmpty = new QPushButton("&Goleste cosul");
    QPushButton* btnGenerate = new QPushButton("&Genereaza cos");
    QPushButton* btnCSV = new QPushButton("&Export cos in CSV");
    QPushButton* btnHTML = new QPushButton("&Export cos in HTML");
    QLineEdit* txtAdd = new QLineEdit;
    QLineEdit* txtGenerate = new QLineEdit;
    QLineEdit* txtCSV = new QLineEdit;
    QLineEdit* txtHTML = new QLineEdit;

    vector<Observer*>& observers;

    void update() override {
        loadData(serv.getAllBooksFromCart());
    }

    void loadData(const vector<Book>& books) {
        //tinem elementele intr-o lista

        lst->clear();
        for (const auto& book : books) {
            lst->addItem(QString::fromStdString(book.getTitle()) + ", " + QString::fromStdString(book.getAuthor()) + ", " + QString::fromStdString(book.getGenre()) + ", " + QString::fromStdString(std::to_string(book.getYear())));
        }
        QString totalBooks = "In cos exista ";
        totalBooks = totalBooks + QString::fromStdString(std::to_string(serv.getAllBooksFromCart().size()));
        totalBooks = totalBooks + " carti";
        total->setText(totalBooks);
    }

    void initGUI() {
        QHBoxLayout* lyMain = new QHBoxLayout;
        setLayout(lyMain);

        QVBoxLayout* lyLeft = new QVBoxLayout;
        lyLeft->addWidget(lst);
        lyLeft->addWidget(total);

        lyMain->addLayout(lyLeft);

        QVBoxLayout* lyRight = new QVBoxLayout;

        QHBoxLayout* lyAdd = new QHBoxLayout;
        lyAdd->addWidget(btnAdd);
        lyAdd->addWidget(txtAdd);
        lyRight->addLayout(lyAdd);

        QHBoxLayout* lyGenerate = new QHBoxLayout;
        lyGenerate->addWidget(btnGenerate);
        lyGenerate->addWidget(txtGenerate);
        lyRight->addLayout(lyGenerate);

        QHBoxLayout* lyCSV = new QHBoxLayout;
        lyCSV->addWidget(btnCSV);
        lyCSV->addWidget(txtCSV);
        lyRight->addLayout(lyCSV);

        QHBoxLayout* lyHTML = new QHBoxLayout;
        lyHTML->addWidget(btnHTML);
        lyHTML->addWidget(txtHTML);
        lyRight->addLayout(lyHTML);

        lyRight->addWidget(btnEmpty);


        lyMain->addLayout(lyRight);
    }

    void initConnect() {

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            try {
                auto title = txtAdd->text().toStdString();
                serv.addBookToCart(title);
                }
            catch (BooksRepoException& ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
            }

            for (auto& o : observers) {
                o->update();
            }
            loadData(serv.getAllBooksFromCart());
            });

        QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
            auto number = txtGenerate->text().toInt();
            if (number > serv.getAll().size()) {
                QMessageBox* box = new QMessageBox;
                box->setText("Introduceti un numar mai mic!");
                box->show();
            }
            else serv.random(number);

            for (auto& o : observers) {
                o->update();
            }
            loadData(serv.getAllBooksFromCart());
            });

        QObject::connect(btnCSV, &QPushButton::clicked, [&]() {
            auto fileName = txtCSV->text().toStdString();
            serv.exportCSV(fileName);
            });

        QObject::connect(btnHTML, &QPushButton::clicked, [&]() {
            auto fileName = txtHTML->text().toStdString();
            serv.exportHTML(fileName);
            });

        QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
            if (serv.getAllBooksFromCart().size() == 0) {
                QMessageBox* box = new QMessageBox;
                box->setText("Cosul este deja gol!");
                box->show();
            }
            else serv.emptyCart();

            for (auto& o : observers) {
                o->update();
            }
            loadData(serv.getAllBooksFromCart());
            });


    }

public:
    CartGUI(Biblioteca& service, vector<Observer*>& observers) : serv{ service }, observers{ observers } {
        loadData(serv.getAllBooksFromCart());
        initGUI();
        initConnect();
        update();
    }


};
*/