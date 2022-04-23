
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "this is a jserver instance." << endl;

    return app.exec();
}





