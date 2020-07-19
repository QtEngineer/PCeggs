#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //,stackedWidget(new QStackedWidget(this))
    //,formLogin(new FormLogin(ui->stackedWidget))
    //,manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    //add forms to stackedWidget
    formLogin=new FormLogin(ui->stackedWidget);
    formPredict=new FormPredict(ui->stackedWidget);
    ui->stackedWidget->insertWidget(0,formLogin);
    ui->stackedWidget->insertWidget(1,formPredict);
    ui->stackedWidget->setCurrentIndex(0);

    //initial
    manager=new QNetworkAccessManager(this);
    formLogin->setManager(manager);
    formLogin->initialNetwork();

    //connect
    connect(formLogin,&FormLogin::Success,this,&MainWindow::LoginSuccess);

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete manager;
}

void MainWindow::LoginSuccess()
{
    ui->stackedWidget->setCurrentIndex(1); //switch page
    qDebug()<<"success";
    //get source data

    betInformation.setCookie(manager->cookieJar());
    betInformation.initial();
    betInformation.downloadData();
    //qDebug()<<QCoreApplication::applicationDirPath();
}
