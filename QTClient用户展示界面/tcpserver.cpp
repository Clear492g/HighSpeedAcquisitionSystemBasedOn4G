#include "tcpserver.h"


TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
  for(int i =0;i<8;i++)
  {
      ADC_Value[i]=0;
  }

  this->TcpSocket= new QTcpSocket(this);
  connect(this,SIGNAL(newConnection()),              //新连接
            this,SLOT(TCPAcceptConnection()));

}

TcpServer::~TcpServer()
{
    TcpSocket->deleteLater();
    this->close();
}

void TcpServer::TCPAcceptConnection()
{
  // 当有客户来访时将tcpSocket接受tcpServer建立的scoket
  TcpSocket = this->nextPendingConnection();
  connect(TcpSocket,SIGNAL(readyRead()),
              this,SLOT(SocketAnalyze()));// 连接读取数据槽函数
  connect(TcpSocket,SIGNAL(disconnected()),
          TcpSocket,SLOT(deleteLater()));
}

void TcpServer::SocketAnswer(QString AnswerData)
{
   TcpSocket->write(AnswerData.toLatin1());
}

void TcpServer::SocketAnalyze()//分析接受到的Socket
{

    QString CMD;


    QString TcpSocketRes;// 创建一个字符串用于存储接收的数据
    TcpSocketRes+=TcpSocket->readAll();// 将tcpsocket中的所有数据读到字符串中
            //qDebug()<<"TCP："+TcpSocketRes;
//{"CMD":"ADCDateUpdate","Channal0":0,"Channal1":0,"Channal2":0,"Channal3":0,"Channal4":0,"Channal5":0,"Channal6":0,"Channal7":0}

    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(TcpSocketRes.toUtf8(), &jsonError);

    if (jsonError.error == QJsonParseError::NoError)
       { if (jsonDocument.isObject())
        {
          QJsonObject rootObject = jsonDocument.object();


          QJsonValue JCMD = rootObject.value("CMD");
          QJsonValue JValue0 = rootObject.value("Channal0");
          QJsonValue JValue1 = rootObject.value("Channal1");
          QJsonValue JValue2 = rootObject.value("Channal2");
          QJsonValue JValue3 = rootObject.value("Channal3");
          QJsonValue JValue4 = rootObject.value("Channal4");
          QJsonValue JValue5 = rootObject.value("Channal5");
          QJsonValue JValue6 = rootObject.value("Channal6");
          QJsonValue JValue7 = rootObject.value("Channal7");


            CMD = JCMD.toString();
            ADC_Value[0]  = JValue0.toDouble();
            ADC_Value[1]  = JValue1.toDouble();
            ADC_Value[2]  = JValue2.toDouble();
            ADC_Value[3]  = JValue3.toDouble();
            ADC_Value[4]  = JValue4.toDouble();
            ADC_Value[5]  = JValue5.toDouble();
            ADC_Value[6]  = JValue6.toDouble();
            ADC_Value[7]  = JValue7.toDouble();
        }


        if(CMD=="ADCDateUpdate")
        {
            emit DateUpdate(ADC_Value);
        }


    }

}

//-------------------------------------------------------------------------------------------------------

QString TcpServer::SocketGetIpAddress()//获取本机IP地址
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
              break;
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}
