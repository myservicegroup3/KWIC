#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <iostream>
#include<qmessagebox.h>
#include "filter.h"
#include "strategy.h"
#include "observer.h"
#include "subject.h"
#include<QTextBlock>
using namespace std;
int length=0;
int ifEnter=0;
map<string,int>p;
int pp[1024]={0};
inputFilter filter1;
transFilter filter2;
outputFilter filter4;

subjectText sub;
subjectText sub1;
observerText1 t1;
observerText2 t2;
bool flag = true;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t1.q = ui->plainTextEdit;
    t2.q = ui->plainTextEdit_2;
    connect(ui->enter,SIGNAL(clicked()),this,SLOT(enter()));
    connect(ui->enter_2,SIGNAL(clicked()),this,SLOT(enter_2()));
    connect(ui->search,SIGNAL(clicked()),this,SLOT(search()));
    connect(ui->plainTextEdit,SIGNAL(textChanged()),this,SLOT(on_changed()));
    connect(ui->plainTextEdit_2,SIGNAL(textChanged()),this,SLOT(on_changed_1()));
    sub.attach(&t1);
    sub.attach(&t2);
}

void MainWindow::enter()
{
    sortFilter filter3(new quicksortAlgorithm);
    Input=ui->textEdit->toPlainText().split("\n");
    //memcpy(text,Input,strlen(Input));
    //text=ui->textEdit->toPlainText().toStdString();
    //QString a=QString::fromStdString(text);
    //QMessageBox::information(this, tr("a"),tr("%1!").arg(a));
    filter4.outputclean();
    filter1.read();
    filter1.trans();
    transport(&filter1.output,&filter2.input);
    filter1.inputclean();
    filter1.outputclean();

    filter2.exchange();
    transport(&filter2.output,&filter3.input);
    filter2.inputclean();
    filter2.outputclean();

    filter3.sortd();
    transport(&filter3.output,&filter4.input);
    filter3.inputclean();
    filter3.outputclean();

    filter4.trans();
    filter4.put();
    ifEnter = 1;
    ui->plainTextEdit->setPlainText(output1);
    sub.change(output1.toStdString());
    //

    //
    filter4.inputclean();
    //filter4.outputclean();
}

void MainWindow::enter_2()
{
    sortFilter filter3(new bubblesortAlgorithm);
    Input=ui->textEdit->toPlainText().split("\n");
    //memcpy(text,Input,strlen(Input));
    //text=ui->textEdit->toPlainText().toStdString();
    //QString a=QString::fromStdString(text);
    //QMessageBox::information(this, tr("a"),tr("%1!").arg(a));
    filter4.outputclean();
    filter1.read();
    filter1.trans();
    transport(&filter1.output,&filter2.input);
    filter1.inputclean();
    filter1.outputclean();

    filter2.exchange();
    transport(&filter2.output,&filter3.input);
    filter2.inputclean();
    filter2.outputclean();

    filter3.sortd();
    transport(&filter3.output,&filter4.input);
    filter3.inputclean();
    filter3.outputclean();

    filter4.trans();
    filter4.put();
    ifEnter = 1;
    ui->plainTextEdit->setPlainText(output1);
    sub.change(output1.toStdString());
    //
    //
    filter4.inputclean();
    //filter4.outputclean();
}



void MainWindow::on_changed()
{
    if(flag)
    {
        flag = false;
        if(ui->plainTextEdit->document()->toPlainText().length() < ui->plainTextEdit_2->document()->toPlainText().length())
        {
            QTextCursor tc1 = ui->plainTextEdit->textCursor();
            QTextLayout *pLayout1 = tc1.block().layout();
            QTextCursor tc2 = ui->plainTextEdit_2->textCursor();
            int nCurpos1 = tc1.position();
            int nTextline1 = pLayout1->lineForTextPosition(nCurpos1).lineNumber();
            tc2.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, nTextline1);
            tc2.setPosition(nCurpos1 + 1);
            tc2.deletePreviousChar();
            ui->plainTextEdit_2->setTextCursor(tc2);
        }
        else if(ui->plainTextEdit->document()->toPlainText().length() > ui->plainTextEdit_2->document()->toPlainText().length())
        {
            subjectText sub1;
            sub1.attach(&t2);
            sub1.change(ui->plainTextEdit->document()->toPlainText().toStdString());
            sub1.detach(&t2);
        }
        flag = true;
    }
}

void MainWindow::on_changed_1()
{
    if(ui->plainTextEdit->document()->toPlainText() != ui->plainTextEdit_2->document()->toPlainText() && flag)
    {
        flag = false;
        ui->plainTextEdit->setPlainText(ui->plainTextEdit_2->document()->toPlainText());
        flag = true;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void observerText2::updata(string newState)
{
    observerState = newState;
    //qDebug() << "imformation:" + QString::fromStdString(newState)<< endl;
    q->setPlainText(QString::fromStdString(newState));
    //
    QTextCursor cursor = q->textCursor();
    QStringList stringList = q->toPlainText().split( "\n" );//利用内容中的回车换行符截取，来获知行数
    qDebug()<<" *************************************** "+QString::number(ifEnter)<<endl;
    if(ifEnter==1)
       {
           ifEnter=2;
           for(int i=0;i<stringList.length()-1;i++)
           {

               QString tt=q->document()->findBlockByLineNumber(i).text();

               string temps=tt.toStdString();
               string temps2 = filter4.output.buffer[i];
               p[temps]=filter4.output.t[temps2];
               pp[i]=p[temps];
           }
       }
       else
       {
        for(int i=0;i<stringList.length()-1;i++)
        {
            QString tt=q->document()->findBlockByLineNumber(i).text();
            string temps=tt.toStdString();
            int a=p[temps];
            qDebug()<<" **************************************** "+QString::fromStdString(temps)<<endl;
            qDebug()<<" *************************************** "+QString::number(a)<<endl;
            if(a!=0) pp[i]=p[temps];
        }
       }

    int h=0;

    for(int i=0;i<stringList.length()-1;i++)
    {

        QString t=q->document()->findBlockByLineNumber(i).text();
        string temps=t.toStdString();

      //  string temps = filter4.output.buffer[i];
      //int a = i%7;
        int a = filter4.output.t[temps];
        //qDebug()<<"-------------------------------- "+QString::fromStdString(filter4.output.buffer[i])<<endl;
         //qDebug()<<"------------------------------- "+QString::number( a)<<endl;


        cursor.setPosition(h,QTextCursor::MoveAnchor);
        //QMessageBox::information(this, tr("h"),tr("%1").arg(h));
        cursor.select(QTextCursor::WordUnderCursor);
        QTextCharFormat fmt;
        switch(pp[i])
        {
        case 7:fmt.setBackground(QColor(255,0,0));
               break;
        case 1:fmt.setBackground(QColor(0,255,0));
               break;
        case 2:fmt.setBackground(QColor(0,245,255));
               break;
        case 3:fmt.setBackground(QColor(132,112,255));
               break;
        case 4:fmt.setBackground(QColor(255 ,255, 0));
               break;
        case 5:fmt.setBackground(QColor(255 ,165, 0));
               break;
        case 6:fmt.setBackground(QColor(255, 239 ,219));
               break;
        }
        h+=q->document()->findBlockByLineNumber(i).length();
        //h+=filter4.output.buffer[i].size();
        //QMessageBox::information(this, tr("h"),tr("%1 %2 %3").arg(cursor.position()).arg(ui->plainTextEdit_2->document()->findBlockByLineNumber(i).length()).arg(h));

        cursor.setPosition(h,QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(fmt);
        cursor.clearSelection(); //撤销选中
    }
}
void MainWindow::search()
{
    //filter的find函数需要修改

    Input=ui->textEdit->toPlainText().split("\n");
    filter1.read();
    filter1.trans();
    s=ui->lineEdit->text().toStdString();//输入的关键字
    findFilter filter5(new quick_search);
    transport(&filter1.output,&filter5.input);
    filter1.inputclean();
    filter1.outputclean();

    filter5.searchd();
    filter5.change();
    //
    ui->plainTextEdit_3->setPlainText(output2);
    output2.clear();
    //
    filter5.inputclean();
    filter5.outputclean();
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    Input=ui->textEdit->toPlainText().split("\n");
    filter1.read();
    filter1.trans();
    s=ui->lineEdit->text().toStdString();//输入的关键字
    findFilter filter5(new normal_search);
    transport(&filter1.output,&filter5.input);
    filter1.inputclean();
    filter1.outputclean();

    filter5.searchd();
    filter5.change();
    //
    ui->plainTextEdit_3->setPlainText(output2);
    output2.clear();
    //
    filter5.inputclean();
    filter5.outputclean();
}
