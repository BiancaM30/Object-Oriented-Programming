#include "Melodii2.h"
#include <QtWidgets/QApplication>

#include "Teste.h"
#include "Repo.h"
#include "Service.h"

int main(int argc, char* argv[])
{
    testAll();
    {
        QApplication a(argc, argv);
        Repo rep{ "melodii.txt" };
        Service serv{ rep };
        Melodii2 w{ serv };
        w.show();
        return a.exec();
    }
}
