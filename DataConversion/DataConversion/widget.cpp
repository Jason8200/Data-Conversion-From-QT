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
     QString myWrite;
     unsigned int myInt;
     unsigned int i,j,NumGroupsPro,NumGroups;
     unsigned int myHbit,myLbit,mycount;
     int8_t myBuf[12];
     union myintToFloat
     {
         int8_t intBuf[12];
         float fBuf[3];
     };
     union myintToFloat myresult;

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
        NumGroupsPro = myRead.toInt(&ok,16); //上一帧数据的第一个字节代表组数
        finalText.seek(0);
        while(!finalText.atEnd())
        {
             finalText>>myRead;
             NumGroups = myRead.toInt(&ok,16); //组数
            if(NumGroups!=NumGroupsPro)
            {
              NumGroupsPro = NumGroups;
              finalout << "\n";
            }
             finalText>>myRead;  //"3A"
             finalText>>myRead;  //"28" / "0C"
             j = myRead.toInt(&ok,16);
             mycount=0;
             if(j==12)
             {
                 for (i=0;i<j; i++)
                 {
                    finalText>>myRead;
                    myBuf[i] = myRead.toInt(&ok,16);
                 }
                 myresult.intBuf[0] = myBuf[1];
                 myresult.intBuf[1] = myBuf[0];
                 myresult.intBuf[2] = myBuf[3];
                 myresult.intBuf[3] = myBuf[2];
                 myresult.intBuf[4] = myBuf[5];
                 myresult.intBuf[5] = myBuf[4];
                 myresult.intBuf[6] = myBuf[7];
                 myresult.intBuf[7] = myBuf[6];
                 myresult.intBuf[8] = myBuf[9];
                 myresult.intBuf[9] = myBuf[8];
                 myresult.intBuf[10] = myBuf[11];
                 myresult.intBuf[11] = myBuf[10];

                 finalout << myresult.fBuf[0];
                 finalout << " ";
                 finalout << myresult.fBuf[1];
                 finalout << " ";
                 finalout << myresult.fBuf[2];
                 finalout << " ";
             }else
             {
                 for (i=0;i<j; i++)
                 {
                    finalText>>myRead;
                    myInt = myRead.toInt(&ok,16);
                    if(mycount==0)
                    {
                        myHbit = 256*myInt;
                        mycount++;
                    }else if(mycount==1)
                    {
                        myLbit = myInt;
                        mycount=0;
                        myInt = myHbit+myLbit;
                        myWrite = myWrite.asprintf("%d",myInt);
                        finalout << myWrite;
                        finalout << " ";
                    }
                 }
             }

             if(i==12)  //计算结果单独一行
             {
                 finalout << "\n";
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

