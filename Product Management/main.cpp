#include "ProduseGUI.h"
#include <QtWidgets/QApplication>

#include "Teste.h"
#include "Repo.h";
#include "Service.h"
#include "ProdusValidator.h"

int main(int argc, char* argv[])
{
    TestAll();

    {
        QApplication a(argc, argv);
        Repo rep{"produse.txt"};
        ProdusValidator val;
        Service serv{ rep, val };
        ProduseGUI w{serv};
        w.show();
        return a.exec();
    }
}

