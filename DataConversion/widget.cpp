#include "widget.h"
#include "ui_widget.h"

#include <QTextStream>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QObject::connect(ui->writeButton,SIGNAL(clicked(bool)),this,SLOT(writeButtonSlot()));
    QObject::connect(ui->readButton ,SIGNAL(clicked(bool)),this,SLOT( readButtonSlot()));
}

void Widget::readButtonSlot()
{
    fileName = QFileDialog::getOpenFileName(
                     this,
                     tr("Open File"),
                     "./Read",
                     tr("*"));
    ui->textEdit->setText(fileName);
    ui->label_4->setText("                 ");
}

void Widget::writeButtonSlot()
{
     bool ok;
     QString line;
     QString lineStart;
     QString myRead;
     QString NumGroupsPro;
     QString NumGroups;
     QString myWrite;
     int myInt;
     int i,j;

     //qDebug()<<QDir::currentPath();
     QFile file( fileName );
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         qDebug()<<"no read 1";
         ui->label_4->setText("源文件文件打开失败！");
         return;
     }
     qDebug()<<"Yes read 1";
     QTextStream in(&file);

     in.seek(0);                                                //定位到文件起始位置
     QFile data("./Write/midFile.txt");              //去除其他仪表发送到服务器的数据 写入中间过程文件
     if (data.open( QIODevice::Text | QFile::WriteOnly  ))
     {
        QTextStream out(&data);
         while(!in.atEnd())
         {
             line = in.readLine();
             lineStart = line.mid(3,5);
             if((lineStart=="3A 28")||(lineStart=="3A 0C"))     //根据数据帧头分辨是否为污泥界面发回的数据
             {
                 out << line;
                 out << "\n";
             }
         }
     }else
     {
         qDebug()<<"open falt 1";
         ui->label_4->setText("过程文件创建失败！");
         return;
     }

     file.close();
     data.close();

     QFile finalfile("./Write/midFile.txt");         //打开中间过程文件 处理过程数据 将同一组的16进制数据转换成10进制整数
     if (!finalfile.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         qDebug()<<"no read 2";
         ui->label_4->setText("过程文件打开失败！");
         return;
     }

     //qDebug()<<"go to conversion";
     ui->label_4->setText("开始转换...");
     ui->label_4->repaint();
     qDebug()<<"Yes read 2";
     QTextStream finalText(&finalfile);
     finalText.seek(0);
     QFile finaldata("./Write/Result.txt");
     if (finaldata.open( QIODevice::Text | QFile::WriteOnly  ))
     {
        QTextStream finalout(&finaldata);
        finalText>>myRead;
        NumGroupsPro = myRead; //上一帧数据的第一个字节代表组数
        finalText.seek(0);
        while(!finalText.atEnd())
        {
             finalText>>myRead;
             NumGroups = myRead; //组数
            if(NumGroups!=NumGroupsPro)
            {
              NumGroupsPro = NumGroups;
              finalout << "\r\n";
            }
             finalText>>myRead;  //"3A"
             finalText>>myRead;  //"28" / "0C"
             j = myRead.toInt(&ok,16);
             for (i=0;i<j; i++)
             {
                finalText>>myRead;
                myInt = myRead.toInt(&ok,16);
                myWrite = myWrite.asprintf("%d",myInt);
                finalout << myWrite;
                finalout << " ";
             }
       }
     }else
     {
         qDebug()<<"open falt 2";
         ui->label_4->setText("目标文件创建失败！");
         return;
     }
     qDebug()<<"write done";
     ui->label_4->setText("转换完成！");
     finalfile.close();
     finaldata.close();
}

Widget::~Widget()
{
    delete ui;
}

