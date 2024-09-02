#include "Lab11_QT.h"
#include "ServiceDisciplineGUI.h"
#include <QtWidgets/QApplication>
#include <Tests.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tests t;
    t.testAll();
    Lab11_QT w;
    Validator val;
    VectorRepository vr;
    RepoFile file_repo{ "discipline.txt" };
    Service sv{ &file_repo,val };
    Contract ct{ file_repo.getAll() };
    ServiceDisciplineGUI gui{ sv ,ct};
    gui.show();
    //w.show();
    return a.exec();
}
