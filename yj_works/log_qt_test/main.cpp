#include <QCoreApplication>
#include "utility.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str= "你好";
    TRACE_YJ("hello - %s", str.toStdString().c_str());

    return a.exec();
}
