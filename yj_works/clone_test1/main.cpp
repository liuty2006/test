#include <QCoreApplication>
#include <iostream>
#include <QDebug>

class CA
{
public:
    int value;
    CA* clone() const { return new CA( *this );}
    //仅一个构造函数
    CA(int a ){value=a;}
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CA* objA=new CA(10);
    CA* objtemp=objA->clone();
    delete objA;
    //std::cout<<objtemp->value;
    //qDebug << objtemp->value;

    int n = objtemp->value;

    delete objtemp;

    return a.exec();
}
