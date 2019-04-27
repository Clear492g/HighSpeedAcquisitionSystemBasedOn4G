#include "adcchart.h"

AdcChart::AdcChart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
        QChart(QChart::ChartTypeCartesian, parent, wFlags),
        m_series(0),//必须是0 不知道为什么
        m_axis(new QValueAxis),
        m_step(0),
        m_x(15),//设置启动从Axis_XLenth开始 保持Axis_XLenth长
        m_y(1)//应该没用
{


    channal=0;

    maxSize = 18; // 只存储最新的 20 个数据
    maxX = 20;

    m_series = new QSplineSeries(this);

    QPen LinePen(Qt::green);
    LinePen.setWidth(3);
    m_series->setPen(LinePen);
    m_series->setUseOpenGL(true);//采用OpenGL来加速绘图


    m_series->append(m_x, m_y);

    addSeries(m_series);//chart->addSeries(splineSeries);
    createDefaultAxes();//创建一个默认的坐标系
    setAxisX(m_axis, m_series);//设定X轴为动态轴

    m_axis->setTickCount(20);//设置动态轴刻度 默认是5，不能小于2


    axisX()->setRange(0, 19);//设置X轴长度和范围（范围动态）
    axisX()->hide();

    axisY()->setRange(-5, 5);//设置Y轴长度和范围（静态）

}

AdcChart::~AdcChart()
{

}

void AdcChart::Update(double *NewDate)
{
    data << NewDate[this->channal];

    while (data.size() > maxSize)
       {
           data.removeFirst();
       }

            m_series->clear();
            int dx = maxX / (maxSize-1);
            int less = maxSize - data.size();

            for (int i = 0; i < data.size(); ++i)
            {
                m_series->append(less*dx+i*dx, data.at(i));

            }

}


