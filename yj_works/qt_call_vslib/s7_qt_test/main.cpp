#include <QCoreApplication>
#include "s7.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    hello();
    //hello();

    int n = Add(1,2);

    return a.exec();
}
