#include "QMainWindow"
#include "QWidget"
#include "QLayout"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>

#include <QApplication>
#include <QDebug>

#include "tcpserver.h"

#include "adcchart.h"
#include <QtCharts/QChartView>

#include "widget.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget *mainWidget = new Widget();
    QMainWindow window;
    window.setCentralWidget(mainWidget);
    window.setWindowTitle("基于4G的高速高精度采集系统 V1.0");
    window.resize(1280, 720);
    window.show();




    return a.exec();
}
