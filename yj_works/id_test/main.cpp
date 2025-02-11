#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

#include <QUuid>
static QString getObjectID() {
    static int adjustID = 1;
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    adjustID ++;
    time = time + adjustID;
    return QString::number( time );
}

void get_random_number()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int a = qrand();
    qDebug()<< a;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //s
    //QString s = getObjectID();

    //
    //get_random_number();

    //
    //QTime time;
    //time= QTime::currentTime();

    QUuid id = QUuid::createUuid();
    QString strId = id.toString();

    // branch_1 test
    // branch_1 test_1
    // master test
    // branch_1 test_3

    return a.exec();
}
