#include "Melodii1.h"
#include <QtWidgets/QApplication>

#include "Repo.h"
#include "Service.h"
#include "Teste.h"

int main(int argc, char *argv[])
{
    testAll();
    {
        QApplication a(argc, argv);
        Repo rep{ "melodii.txt" };
        Service serv{ rep };
        Melodii1 w{ serv };
        w.show();
        return a.exec();
    }
}
