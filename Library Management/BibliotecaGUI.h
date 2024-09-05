#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BibliotecaGUI.h"

#include "Biblioteca.h"
#include "CartGUI.h"
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



class BibliotecaGUI : public QWidget {
private:
    Biblioteca& serv;

    // QListWidget* lst = new QListWidget;
    QTableWidget* tbl = new QTableWidget();
    QPushButton* btnAdd = new QPushButton{ "&Adauga" };
    QPushButton* btnDelete = new QPushButton{ "&Sterge" };
    QPushButton* btnUpdate = new QPushButton{ "&Modifica" };
    QPushButton* btnExit = new QPushButton{ "&Iesire" };

    QPushButton* btnSearch = new QPushButton{ "&Cauta carte" };
    QPushButton* btnFilterByTitle = new QPushButton{ "&Filtreaza dupa titlu" };
    QPushButton* btnFilterByYear = new QPushButton{ "&Filtreaza dupa an aparitie" };
    QPushButton* btnRaport = new QPushButton("&Raport");

    QLineEdit* txtTitle = new QLineEdit;
    QLineEdit* txtAuthor = new QLineEdit;
    QLineEdit* txtGen = new QLineEdit;
    QLineEdit* txtYear = new QLineEdit;
    QLineEdit* txtFilterByTitle = new QLineEdit;
    QLineEdit* txtFilterByYear = new QLineEdit;

    QPushButton* btnSortByTitle = new QPushButton{ "&Sorteaza dupa titlu" };
    QPushButton* btnSortByAuthor = new QPushButton{ "&Sorteaza dupa autor" };
    QPushButton* btnSortByYearGen = new QPushButton{ "&Sorteaza dupa an si gen" };

    QPushButton* btnUndo = new QPushButton{ "&Undo" };
    QPushButton* btnRedo = new QPushButton{ "&Redo" };

    QPushButton* btnCart = new QPushButton{ "Mergi la cosul de inchirieri" };

    void loadData(const vector<Book>& books) {
        //tabel

        tbl->clear();

        tbl->setRowCount(serv.getAll().size());
        tbl->setColumnCount(4);
        tbl->setHorizontalHeaderLabels(QStringList() << "Titlu" << "Autor" << "Gen" << "An aparitie");

        int line = 0;
        for (const auto& book : books) {
            //QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(book.getTitle()));
            //item->setData(Qt::UserRole, QString::fromStdString(book.getAuthor()));
            //item->setData(Qt::BackgroundRole, QBrush{Qt::red, Qt::SolidPattern});

            QTableWidgetItem* cellItem1 = new QTableWidgetItem(QString::fromStdString(book.getTitle()));
            QTableWidgetItem* cellItem2 = new QTableWidgetItem(QString::fromStdString(book.getAuthor()));
            QTableWidgetItem* cellItem3 = new QTableWidgetItem(QString::fromStdString(book.getGenre()));
            QTableWidgetItem* cellItem4 = new QTableWidgetItem(QString::fromStdString(std::to_string(book.getYear())));

            // daca se cere colorarea in rosu a unei celule
            //cellItem1->setBackground(QColor(Qt::red));

            tbl->setItem(line, 0, cellItem1);
            tbl->setItem(line, 1, cellItem2);
            tbl->setItem(line, 2, cellItem3);
            tbl->setItem(line, 3, cellItem4);

            line++;
        }

        //Daca am tine elementele intr-o lista

        /*lst->clear();
        for (const auto& book : books) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.getTitle()));
            item->setData(Qt::UserRole, QString::fromStdString(book.getAuthor()));
            //item->setBackground(QBrush{ Qt::yellow, Qt::SolidPattern });
            lst->addItem(QString::fromStdString(book.getTitle()) + ", " + QString::fromStdString(book.getAuthor()) + ", " + QString::fromStdString(book.getGenre()) + ", " + QString::fromStdString(std::to_string(book.getYear())));

        }*/


    }

    void loadDataColored(const vector<Book>& books) {
        //functia incarca elementele tabelului, colorand in verde acele elemente care apartin
        //vectorului transmis ca parametru.
        //restul elementelor raman necolorate
        //
        tbl->clear();
        tbl->setHorizontalHeaderLabels(QStringList() << "Titlu" << "Autor" << "Gen" << "An aparitie");
        tbl->setRowCount(serv.getAll().size());
        tbl->setColumnCount(4);

        int line = 0;
        auto serviceBooks = serv.getAll();
        for (const auto& book : serviceBooks) {
            QTableWidgetItem* cellItem1 = new QTableWidgetItem(QString::fromStdString(book.getTitle()));
            QTableWidgetItem* cellItem2 = new QTableWidgetItem(QString::fromStdString(book.getAuthor()));
            QTableWidgetItem* cellItem3 = new QTableWidgetItem(QString::fromStdString(book.getGenre()));
            QTableWidgetItem* cellItem4 = new QTableWidgetItem(QString::fromStdString(std::to_string(book.getYear())));

            for (const auto& i : books)
                if (i.getTitle() == book.getTitle() && i.getAuthor() == book.getAuthor()) {
                    // coloram in verde linia
                    cellItem1->setBackground(QColor(Qt::green));
                    cellItem2->setBackground(QColor(Qt::green));
                    cellItem3->setBackground(QColor(Qt::green));
                    cellItem4->setBackground(QColor(Qt::green));
                }

            tbl->setItem(line, 0, cellItem1);
            tbl->setItem(line, 1, cellItem2);
            tbl->setItem(line, 2, cellItem3);
            tbl->setItem(line, 3, cellItem4);

            line++;
        }
    }

    void initGUI() {
        QHBoxLayout* lyMain = new QHBoxLayout();
        setLayout(lyMain);

        QVBoxLayout* lyLeft = new QVBoxLayout{};
        //lyLeft->addWidget(lst);
        lyLeft->addWidget(tbl);

        lyLeft->addWidget(btnSortByTitle);
        lyLeft->addWidget(btnSortByAuthor);
        lyLeft->addWidget(btnSortByYearGen);

        lyMain->addLayout(lyLeft);

        QVBoxLayout* rightLy = new QVBoxLayout;
        QFormLayout* formLy = new QFormLayout();
        formLy->addRow("Titlu: ", txtTitle);
        formLy->addRow("Autor: ", txtAuthor);
        formLy->addRow("Gen: ", txtGen);
        formLy->addRow("An aparitie: ", txtYear);

        rightLy->addLayout(formLy);

        //layout butoane  CRUD
        QHBoxLayout* lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdd);
        lyBtn->addWidget(btnDelete);
        lyBtn->addWidget(btnUpdate);

        rightLy->addLayout(lyBtn);
        rightLy->addWidget(btnSearch);

        lyMain->addLayout(rightLy);


        //layout butoane filtrare
        QVBoxLayout* lyBtnFilter = new QVBoxLayout{};

        QHBoxLayout* lyFilterByAuthor = new QHBoxLayout{};
        lyFilterByAuthor->addWidget(btnFilterByTitle);
        lyFilterByAuthor->addWidget(txtFilterByTitle);
        lyBtnFilter->addLayout(lyFilterByAuthor);

        QHBoxLayout* lyFilterByYear = new QHBoxLayout{};
        lyFilterByYear->addWidget(btnFilterByYear);
        lyFilterByYear->addWidget(txtFilterByYear);
        lyBtnFilter->addLayout(lyFilterByYear);

        rightLy->addLayout(lyBtnFilter);

        //layout butoane undo si redo
        QHBoxLayout* lyBtnUndo = new QHBoxLayout{};
        lyBtnUndo->addWidget(btnUndo);
        lyBtnUndo->addWidget(btnRedo);

        rightLy->addLayout(lyBtnUndo);

        rightLy->addWidget(btnRaport);

        rightLy->addWidget(btnExit);

        lyMain->addLayout(rightLy);

        lyMain->addWidget(btnCart);
    }

    void initConnect() {
        QObject::connect(btnExit, &QPushButton::clicked, [&] {
            close();
            });

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            auto title = txtTitle->text();
            auto author = txtAuthor->text();
            auto gen = txtGen->text();
            auto year = txtYear->text();

            const auto stdTitle = title.toStdString();
            const auto stdAuthor = author.toStdString();
            const auto stdGen = gen.toStdString();
            auto intYear = year.toInt();

            try {
                serv.addBook(stdTitle, stdAuthor, stdGen, intYear);
                loadData(serv.getAll());
            }
            catch (BooksRepoException& ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
            }
            catch (ValidateException& ex) {
                vector<string> errors = ex.getMsg();
                for (auto error : errors) {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(error));
                }


            }
            });

        QObject::connect(btnDelete, &QPushButton::clicked, [&]() {

            auto title = txtTitle->text();
            auto author = txtAuthor->text();

            const auto stdTitle = title.toStdString();
            const auto stdAuthor = author.toStdString();

            try {
                serv.removeBook(stdTitle, stdAuthor);
                loadData(serv.getAll());
            }
            catch (BooksRepoException& ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
            }
            catch (ValidateException& ex) {
                vector<string> errors = ex.getMsg();
                for (auto error : errors) {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(error));
                }


            }
            });

        QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
            auto title = txtTitle->text();
            auto author = txtAuthor->text();
            auto newGen = txtGen->text();
            auto newYear = txtYear->text();

            const auto stdTitle = title.toStdString();
            const auto stdAuthor = author.toStdString();
            const auto stdGen = newGen.toStdString();
            auto intYear = newYear.toInt();


            try {
                serv.updateBook(stdTitle, stdAuthor, stdGen, intYear);
                loadData(serv.getAll());
            }
            catch (BooksRepoException& ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
            }
            catch (ValidateException& ex) {
                vector<string> errors = ex.getMsg();
                for (auto error : errors) {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(error));
                }


            }


            });

        QObject::connect(btnSearch, &QPushButton::clicked, [&]() {
            auto title = txtTitle->text().toStdString();
            auto author = txtAuthor->text().toStdString();
            try {
                Book b = serv.getBook(title, author);
                QMessageBox* box = new QMessageBox{};
                QString msg = "Titlu: " + QString::fromStdString(title) + "\nAutor: " + QString::fromStdString(author) + "\nGen: " + QString::fromStdString(b.getGenre()) + "\nAn aparitie: " + QString::fromStdString(std::to_string(b.getYear()));
                box->setText(msg);
                box->show();
            }
            catch (BooksRepoException& ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
            }

            });

        QObject::connect(btnFilterByTitle, &QPushButton::clicked, [&]() {
            auto title = txtFilterByTitle->text().toStdString();

            if (serv.filterByTitle(title).size() == 0) {
                QMessageBox::warning(this, "Warning", QString::fromStdString("Nu am gasit carti cu acest titlu!"));
            }

            else loadDataColored(serv.filterByTitle(title));

            });

        QObject::connect(btnFilterByYear, &QPushButton::clicked, [&]() {
            auto year = txtFilterByYear->text().toInt();

            if (serv.filterByYear(year).size() == 0) {
                QMessageBox::warning(this, "Warning", QString::fromStdString("Nu am gasit carti cu acest an de aparitie!"));
            }

            else loadDataColored(serv.filterByYear(year));
            });

        QObject::connect(btnSortByTitle, &QPushButton::clicked, [&]() {
            loadData(serv.sortByTitle());
            });

        QObject::connect(btnSortByAuthor, &QPushButton::clicked, [&]() {
            loadData(serv.sortByAuthor());
            });

        QObject::connect(btnSortByYearGen, &QPushButton::clicked, [&]() {
            loadData(serv.sortByYearGen());
            });

        /*QObject::connect(lst, &QListWidget::itemSelectionChanged, [&] {
            auto select = lst->selectedItems();
            if (select.isEmpty()) {
                txtTitle->setText("");
                txtAuthor->setText("");
                txtGen->setText("");
                txtYear->setText("");
            }
            else {
                auto selItem = select.at(0); //putem lua doar un singur element selectat
                auto line = selItem->text().toStdString();

                string title;
                const string delim = ",";


                auto pos = line.find(delim);
                title = line.substr(0, pos);
                txtTitle->setText(QString::fromStdString(title));
                line.erase(0, pos + 2);

                pos = line.find(delim);
                auto author = line.substr(0, pos);
                txtAuthor->setText(QString::fromStdString(author));
                line.erase(0, pos + 2);

                pos = line.find(delim);
                auto gen = line.substr(0, pos);
                txtGen->setText(QString::fromStdString(gen));
                line.erase(0, pos + 2);

                txtYear->setText(QString::fromStdString(line));
            }

            });*/

        QObject::connect(tbl, &QTableWidget::itemSelectionChanged, [&] {
            auto select = tbl->selectedItems();
            if (select.isEmpty()) {
                txtTitle->setText("");
                txtAuthor->setText("");
                txtGen->setText("");
                txtYear->setText("");
            }
            else {
                txtTitle->setText(select.at(0)->text());
                txtAuthor->setText(select.at(1)->text());
                txtGen->setText(select.at(2)->text());
                txtYear->setText(select.at(3)->text());

            }

            });

        QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
            try {
                serv.Undo();
                loadData(serv.getAll());
            }
            catch (ValidateException& ex) {
                //avem un vector de stringuri pe care trebuie sa il transformam in QString
                auto msg = ex.getMsg();
                QString err = "";
                for (auto word : msg) {
                    err = err + QString::fromStdString(word);
                }
                QMessageBox::warning(this, "Warning", err);
            }
            });

        QObject::connect(btnRedo, &QPushButton::clicked, [&]() {
            try {
                serv.Redo();
                loadData(serv.getAll());
            }
            catch (ValidateException& ex) {
                //avem un vector de stringuri pe care trebuie sa il transformam in QString
                auto msg = ex.getMsg();
                QString err = "";
                for (auto word : msg) {
                    err = err + QString::fromStdString(word);
                }
                QMessageBox::warning(this, "Warning", err);
            }
            });

        QObject::connect(btnCart, &QPushButton::clicked, [&]() {
            auto cartGui = new CartGUI{ serv };
            cartGui->show();
            });

        QObject::connect(btnRaport, &QPushButton::clicked, [&]() {
            const auto& rap = serv.raport();
            QMessageBox* box = new QMessageBox;

            QString msg = "";
            for (auto it = rap.begin(); it != rap.end(); it++)
            {
                msg = msg + QString::fromStdString(it->first) + ": " + QString::fromStdString(std::to_string(it->second.getCount())) + '\n';

            }
            box->setText(msg);
            box->show();

            });
    }

public:
    BibliotecaGUI(Biblioteca& service) : serv{ service } {
        loadData(serv.getAll());
        initGUI();
        initConnect();
    }
};


