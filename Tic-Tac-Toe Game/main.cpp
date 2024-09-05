#include "TicTacToe.h"
#include <QtWidgets/QApplication>

#include "Teste.h"
#include "Repo.h"
#include "Service.h"
#include "JocValidator.h"

int main(int argc, char* argv[])
{
    testAll();
    {QApplication a(argc, argv);
    Repo rep{ "jocuri.txt" };
    JocValidator val;
    Service serv{ rep, val };
    TicTacToe w{ serv };
    w.show();
    return a.exec();
    }
}
