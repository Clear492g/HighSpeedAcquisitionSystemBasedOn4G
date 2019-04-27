#ifndef ADCCHART_H
#define ADCCHART_H

#include <QObject>
#include <QtCharts/QChart>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>  //用于绘制平滑曲线
#include <QtCharts/QValueAxis>     //继承自QAbstractAxis,用于对坐标轴进行操作
#include <QtCore/QRandomGenerator> //随机数
#include <QtCore/QDebug>
#include <QList>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE//必须  不然找不到Qchart

class AdcChart : public QChart
{
     Q_OBJECT
public:
    AdcChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~AdcChart();
    int channal;


public slots:
    void Update(double *NewDate);

private:


    QValueAxis *m_axis;//定义坐标轴 可以对X/Y轴等进行修改
    qreal m_step;
    qreal m_x;
    qreal m_y;

    int maxSize;  // data 最多存储 maxSize 个元素
    int maxX;
    int Axis_XLenth;
    QList<double> data; // 存储业务数据的 list
    QSplineSeries *m_series;//平滑曲线


};

#endif // ADCCHART_H
