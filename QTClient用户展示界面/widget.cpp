#include "widget.h"


Widget::Widget(QWidget *parent) :QWidget(parent)
{
    grid=new QGridLayout;//总布局管理器

///////////////////////////////////////////////////////////////////////////////////////////////
        this->My_TcpServer = new TcpServer;
        My_TcpServer->listen(QHostAddress::Any, 8492);
///////////////////////////////////////////////////////////////////////////////////////////////
        QHBoxLayout *Menuhb=new QHBoxLayout;//菜单栏
        //初始化下拉框，label
        QLabel *label_Legend=new QLabel("角标设置:");
        ComBox_Legend=new QComboBox;
        ComBox_Legend->addItem("无角标");
        ComBox_Legend->addItem("居上显示");
        ComBox_Legend->addItem("居下显示");
        ComBox_Legend->addItem("居左显示");
        ComBox_Legend->addItem("居右显示");

        QLabel *label_Theme=new QLabel("界面主题:");
        ComBox_Theme=new QComboBox;
        ComBox_Theme->addItem("默认");
        ComBox_Theme->addItem("蓝绿风");
        ComBox_Theme->addItem("蓝白风");
        ComBox_Theme->addItem("沙漠风");
        ComBox_Theme->addItem("科技风");

        QLabel *label_IP=new QLabel("IP:");
        label_IP->setText("    IP地址 : "+My_TcpServer->SocketGetIpAddress());
        QFont font("Microsoft YaHei", 12, 50, false);
        label_IP->setFont(font);

        Menuhb->addWidget(label_Legend);
        Menuhb->addWidget(ComBox_Legend);
        Menuhb->addWidget(label_Theme);
        Menuhb->addWidget(ComBox_Theme);
        Menuhb->addWidget(label_IP);

        Menuhb->addStretch();        //增加间距之间的可延展性。

        //两个下拉框对应的槽函数
       connect(ComBox_Legend,SIGNAL(currentTextChanged(QString)),this,SLOT(Legend_Change()));
       connect(ComBox_Theme,SIGNAL(currentTextChanged(QString)),this,SLOT(Theme_Change()));

///////////////////////////////////////////////////////////////////////////////////////////////


        QHBoxLayout *AdcValue_hb=new QHBoxLayout;//两行value值
        QHBoxLayout *AdcValue_hb2=new QHBoxLayout;

        for(int i =0;i<8;i++)
        {
            label_Value[i] = new QLabel("Chanal "+QString::number(i)+" :");
            label_Value[i]->setText("通道 "+QString::number(i)+" : "
                                    +QString::number(My_TcpServer->ADC_Value[i],10,4)+" V");
            QFont Value_font("Microsoft YaHei", 15, 50, false);
            label_Value[i]->setFont(Value_font);

            if(i<4)
            {
                AdcValue_hb->addWidget(label_Value[i]);
            }
            else
                AdcValue_hb2->addWidget(label_Value[i]);
        }


        AdcValue_hb->addStretch();        //增加间距之间的可延展性。
        AdcValue_hb2->addStretch();        //增加间距之间的可延展性。

        connect(My_TcpServer,SIGNAL(DateUpdate(double*)),this,SLOT(ValueLableUpdate()));

///////////////////////////////////////////////////////////////////////////////////////////////


        for(int i =0;i<8;i++)
        {
            Chart[i] = new AdcChart;
            Chart[i]->channal=i;

            view=new QChartView(Chart[i]);

            Chart[i]->setTitle("通道 "+QString::number(i));
            Chart[i]->legend()->hide();
            Chart[i]->setAnimationOptions(QChart::AllAnimations);
            viewlist<<view;

            if(i<4)
                grid->addWidget(viewlist.at(i),3,i);
            else
                grid->addWidget(viewlist.at(i),4,i-4);
            connect(My_TcpServer,SIGNAL(DateUpdate(double*)),Chart[i],SLOT(Update(double*)));
        }



///////////////////////////////////////////////////////////////////////////////////////////////


        grid->addLayout(Menuhb,0,0,1,4);
        grid->addLayout(AdcValue_hb,1,0,1,4);
        grid->addLayout(AdcValue_hb2,2,0,1,4);
        setLayout(grid);

}

Widget::~Widget()
{
    My_TcpServer->deleteLater();
    My_TcpServer->close();
}



void Widget::Theme_Change()
{
    QChartView *view;

    //创建调色板

    QPalette pal = window()->palette();

    foreach(view,viewlist)

    {

        switch(ComBox_Theme->currentIndex())

        {

        case 0:   break;

        case 1:view->chart()->setTheme(QChart::ChartThemeBlueCerulean);

            pal.setColor(QPalette::Window, QRgb(0x40434a));

            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));   break;

        case 2:view->chart()->setTheme(QChart::ChartThemeBlueIcy);

            pal.setColor(QPalette::Window, QRgb(0xcee7f0));

            pal.setColor(QPalette::WindowText, QRgb(0x404044));break;

        case 3:view->chart()->setTheme(QChart::ChartThemeBrownSand);

            pal.setColor(QPalette::Window, QRgb(0x9e8965));

            pal.setColor(QPalette::WindowText, QRgb(0x404044));break;

        case 4:view->chart()->setTheme(QChart::ChartThemeDark);

            pal.setColor(QPalette::Window, QRgb(0x121218));

            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));break;

        }

    }

     window()->setPalette(pal);    //这句挺重要的，没有他，就相当于设置的调色板没有生成、


}



void Widget::Legend_Change()//角标位置改变
{

    QChartView *chartView;

            if(ComBox_Legend->currentIndex()!=0)

            {

                    foreach (chartView, viewlist)
                    {

                        switch(ComBox_Legend->currentIndex())
                        {
                        case 1: chartView->chart()->legend()->setAlignment(Qt::AlignTop);break;
                        case 2: chartView->chart()->legend()->setAlignment(Qt::AlignBottom);break;
                        case 3: chartView->chart()->legend()->setAlignment(Qt::AlignLeft);break;
                        case 4: chartView->chart()->legend()->setAlignment(Qt::AlignRight);break;
                        }

                        chartView->chart()->legend()->show();
                    }

            }

            else {

                viewlist.at(0)->chart()->legend()->hide();
                viewlist.at(1)->chart()->legend()->hide();
                viewlist.at(2)->chart()->legend()->hide();
                viewlist.at(3)->chart()->legend()->hide();
                viewlist.at(4)->chart()->legend()->hide();
                viewlist.at(5)->chart()->legend()->hide();
                viewlist.at(6)->chart()->legend()->hide();
                viewlist.at(7)->chart()->legend()->hide();

            }
}


void  Widget::ValueLableUpdate()//ADC值文字面板更新
{
    for(int i =0;i<8;i++)
    {

        label_Value[i]->setText("通道 "+QString::number(i)+" : "
                                +QString::number(My_TcpServer->ADC_Value[i],10,4)+" V");

    }
}

