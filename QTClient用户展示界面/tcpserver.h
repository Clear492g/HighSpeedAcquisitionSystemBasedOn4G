#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

class TcpServer:public QTcpServer
{
    Q_OBJECT

public:
   explicit TcpServer(QObject *parent = 0);
    ~TcpServer();


private:

public:
     QTcpSocket *TcpSocket;

     QString SocketGetIpAddress();

     void SocketAnswer(QString AnswerData);
     double ADC_Value[8];


private slots:
     void SocketAnalyze();
     void TCPAcceptConnection();


 signals:
     void DateUpdate(double* );//ADC数据更新



};

#endif // TCPSERVER_H
