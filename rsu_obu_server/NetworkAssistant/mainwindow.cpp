#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTime>

#define port 6000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sender = new QUdpSocket(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(send()));

    if(ui->lineEdit->text()=="")
    {
        ip="192.168.2.174";
    }
    else
    {
        ip=ui->lineEdit->text();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text()=="")
    {
        ip="192.168.2.174 ";
    }
    else
    {
        ip=ui->lineEdit->text();
    }
    timer->start(1000);
}

void MainWindow::send()
{
    if(!file->atEnd())
    {
        QByteArray data = QByteArray(file->readLine());
        QByteArray senddata;
        senddata.resize((data.size()-1)/3);
        for(int i=0;i<senddata.size();i++)
        {
            int k = 0,j = 0;

            if(data.at(i*3)<=57&&data.at(i*3)>=48) k=data.at(i*3)-48;
            else if(data.at(i*3)<=90&&data.at(i*3)>=65) k=data.at(i*3)-55;
            else if(data.at(i*3)<=122&&data.at(i*3)>=97) k=data.at(i*3)-87;
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "erro", "数据出错", QMessageBox::Yes | QMessageBox::No, NULL);
                if(message.exec() == QMessageBox::Yes)
                {
                        QMessageBox::aboutQt(NULL, "About Qt");
                }
            }

            if(data.at(i*3+1)<=57&&data.at(i*3+1)>=48) j=data.at(i*3+1)-48;
            else if(data.at(i*3+1)<=90&&data.at(i*3+1)>=65) j=data.at(i*3+1)-55;
            else if(data.at(i*3+1)<=122&&data.at(i*3+1)>=97) j=data.at(i*3+1)-87;
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "erro", "数据出错", QMessageBox::Yes | QMessageBox::No, NULL);
                if(message.exec() == QMessageBox::Yes)
                {
                        QMessageBox::aboutQt(NULL, "About Qt");
                }
            }

            senddata[i] = k*16+j;
        }
        sender->writeDatagram(senddata,senddata.size(),QHostAddress(ip),port);
    }
    else
    {
        file = new QFile(fileName);
        file->open(QIODevice::ReadOnly|QIODevice::Text);
        send();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("open file"), "D:\\",  tr("txt(*.txt);;Allfile(*.*)"));
    file = new QFile(fileName);
    file->open(QIODevice::ReadOnly|QIODevice::Text);
}

void MainWindow::on_pushButton_3_clicked()
{
    timer->stop();
}
