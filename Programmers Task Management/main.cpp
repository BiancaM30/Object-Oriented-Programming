#include "Programatori.h"
#include <QtWidgets/QApplication>

#include "Teste.h"
#include "Repo.h"
#include "Service.h"
#include "TaskValidator.h"

int main(int argc, char* argv[])
{
    testAll();
    {QApplication a(argc, argv);
    Repo rep{ "taskuri.txt" };
    TaskValidator val;
    Service serv{ rep, val };
    Programatori w{ serv };
    w.show();
    return a.exec();
    }
}
