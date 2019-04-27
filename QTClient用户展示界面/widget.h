#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QtCharts/QChartView>

//#include "chart.h"
#include "tcpserver.h"
#include "adcchart.h"

QT_CHARTS_USE_NAMESPACE//必须  不然找不到Qchart


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QGridLayout *grid;

    QComboBox *ComBox_Theme;
    QComboBox *ComBox_Legend;

    QLabel *label_Value[8];

    AdcChart *Chart[8];

    QChartView *view;
    QVector<QChartView*>viewlist;

    TcpServer *My_TcpServer;

public slots:
    void Legend_Change();//设置标签函数
    void Theme_Change();//设置主题函数
    void ValueLableUpdate();


};

#endif // WIDGET_H
