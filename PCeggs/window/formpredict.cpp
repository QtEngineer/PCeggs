#include "formpredict.h"
#include "ui_formpredict.h"
//#include "algorithm.h"
#include <QString>
#include <QDebug>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <QTime>
FormPredict::FormPredict(QWidget *parent) :
    SubForm(parent),
    ui(new Ui::FormPredict)
{
    ui->setupUi(this);
    /*QStringList header;
    header << QStringLiteral("期号") << QStringLiteral("时间") << QStringLiteral("结果");
    ui->tableWidget->setHorizontalHeaderLabels(header);*/

    //------------------------------------------------------------
    //timer.start(30*1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(reflesh()));

}
void FormPredict::initialStyle()
{
    ui->tableWidget->horizontalHeader()->setFont(QFont("Helvetica"));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setFont(QFont("Courier"));
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->verticalHeader()->setVisible(false);
    //-------------------------设置样式--------------------------

    /*QFile file2(":/tablewidget/tablewidget.qss");
    file2.open(QFile::ReadOnly);
    QString style = tr(file2.readAll());
    ui->tableWidget->setStyleSheet(style);
    file2.close();
    QFile file(":/vbar/sb.qss");
    if(!file.open(QFile::ReadOnly))qDebug()<<"fail";
    ui->tableWidget->verticalScrollBar()->setStyleSheet(file.readAll());
    file.close();
    QFile file1(":/hbar/hsb.qss");
    if(!file1.open(QFile::ReadOnly))qDebug()<<"fail";
    ui->tableWidget->horizontalScrollBar()->setStyleSheet(file1.readAll());
    file1.close();*/
}
FormPredict::~FormPredict()
{
    delete ui;   
}

void FormPredict::fromMsg(mymsg msg)
{
    if(!timer.isActive())
        timer.start(30*1000);
    listMsg.insert(0,msg);
    //listMsg.append(msg);
    //qDebug()<<listMsg.at(0).getRst();
    /*QTableWidgetItem* item[1];
    item[0] =new QTableWidgetItem;
    item[0]->setText(QString::number(listMsg.at(0).getRst(),10));
    int row_count = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row_count + 1);
    ui->tableWidget->setItem(0,0,item[0]);*/
    //int row_count = ui->tableWidget->rowCount();
    //ui->tableWidget->setRowCount(row_count + 1);
    ui->tableWidget->setColumnCount(4);
    QStringList a;
    a<<"a"<<"b"<<"c";
    ui->tableWidget->setHorizontalHeaderLabels(a);
    addItem();
   /* QTableWidgetItem* itemResults[1];
    itemResults[0]=new QTableWidgetItem;
    itemResults[0]->setText(QString::number(listMsg.at(0).getRst(),10));
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0,1,itemResults[0]);
    QTableWidgetItem *itemIssue= new QTableWidgetItem;
    itemIssue->setText(QString::number(listMsg.at(0).getIssue(),10));
    //qDebug()<<QString::number(listMsg.at(0).getIssue(),10);
    ui->tableWidget->setItem(0,0,itemIssue);
    //QTableWidgetItem * itemCheck = new QTableWidgetItem;
    //itemCheck->setText(msg.getBS());
    //ui->tableWidget->setItem(0,1,itemCheck);*/



}

void FormPredict::reflesh()
{
    qDebug()<<"sus1";

    QTime time=QTime::currentTime();
    QString a=time.toString().mid(3,2);
    if(a.toInt()%5!=0&&listMsg.at(0).getIssue()!=ui->tableWidget->item(0,0)->text())
    {
        addItem();
        Check();
        /*algorithm ag;
        ag.createInfo(listMsg);
        QList<QList<int>> list;
        list.append(ag.Near());
        ag.showRst(list);
        QTableWidgetItem* itemResults=new QTableWidgetItem;
        itemResults->setText(ag.showRst(list).at(3));
        ui->tableWidget->setItem(0,2,itemResults);*/

    }
    //algorithm ag;
    //ag.createInfo(listMsg);
    //ag.showMsg(listMsg);
    //qDebug()<<ag.listMsg.at(0);
    //ag.Exp(4);
    //qDebug()<<ag

}
void FormPredict::addItem()
{
    int row_count = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row_count + 1);
    ui->tableWidget->insertRow(0);
    QTableWidgetItem* item[5];
    item[0]=new QTableWidgetItem;
    item[0]->setText(QString::number(listMsg.at(0).getIssue()));
    ui->tableWidget->setItem(0,0,item[0]);
    item[1]=new QTableWidgetItem;
    item[1]->setText(QString::number(listMsg.at(0).getRst()));
    ui->tableWidget->setItem(0,1,item[1]);
    item[2]=new QTableWidgetItem;
    /*algorithm ag;
    ag.createInfo(listMsg);
    QList<QList<int>> list;
    if(listMsg.size()>3)
    {

        list.append(ag.Near());
        //qDebug()<<ag.Near().at(4);
        item[2]->setText(ag.showRst(list).at(0));
        ui->tableWidget->setItem(0,2,item[2]);


    }*/


}
void FormPredict::Check()
{
    if(listMsg.at(0).getRst()==ui->tableWidget->item(1,2)->text().toInt())
    {
        QTableWidgetItem item;
        item.setText("dui");
        ui->tableWidget->setItem(0,3,&item);
    }
    else
    {
        QTableWidgetItem item;
        item.setText("cuo");
        ui->tableWidget->setItem(0,3,&item);
    }



}

void FormPredict::getAccount(QString s)
{


    ui->label_no->setText(s);

}


void FormPredict::Init()
{



}

void FormPredict::on_pushButton_clicked()
{

}
void FormPredict::getData(mymsg &msg)
{

}
