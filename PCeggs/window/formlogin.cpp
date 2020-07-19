#include "formlogin.h"
#include "ui_formlogin.h"
//#include "savelogin.h"
#include <QMessageBox>
#include <QTcpSocket>
#include <stdio.h>
//QNetworkRequest FormLogin::sRequst;
//QNetworkCookieJar* FormLogin::cookieJar=new QNetworkCookieJar;
FormLogin::FormLogin(QWidget *parent) :
    SubForm(parent),
    ui(new Ui::FormLogin)
{

    ui->setupUi(this);
    //manager=new QNetworkAccessManager(this);
    //manager->setCookieJar(FormLogin::cookieJar);

    /*url_crt.setUrl("http://www.pceggs.com/VerifyCode_Login.aspx");
    request_vrf.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request_vrf.setUrl(QUrl("http://www.pceggs.com/VerifyCode_Login.aspx?"));
    //request_vrf.setUrl(QUrl("https://blog.csdn.net/study_more/article/details/7312015/"));
    request_login.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request_login.setUrl(QUrl("http://www.pceggs.com/nologin.aspx?Warn=6"));
    request_bet.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request_bet.setUrl(QUrl("http://www.pceggs.com/play/pg28InsertDo.aspx"));
    //reply=manager->get(request_vrf);
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    connect(manager,&QNetworkAccessManager::finished,this,&FormLogin::replyfinished);
    eventLoop.exec();*/
    //saveLogin sl;
    QString Username=ui->lineEdit_user->text();
    QString Pwd=ui->lineEdit_pwd->text();
    QString isSaved="";
   /* sl.iniRead("isSaved",isSaved);
    if(isSaved.toInt()==1)
    {
        ui->checkBox->setChecked(1);
        sl.iniRead("UserName",Username);
        sl.iniRead("PassWord",Pwd);
        ui->lineEdit_user->setText(Username);
        ui->lineEdit_pwd->setText(Pwd);
    }*/

    destUrl="http://www.pceggs.com/nologin.aspx?Warn=6";
    baseurl.setUrl(destUrl);

}

FormLogin::~FormLogin()
{
    delete ui;
    //delete manager;
   // delete reply;
}


void FormLogin::replyfinished(QNetworkReply* reply)
{
    QVariant variant = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
      //QVariant variant1 = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
     // qDebug()<<variant1.toString()<<reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString()<<"*";
    QUrl relativeUrl = QUrl(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString());
   // qDebug()<<relativeUrl.toString()<<"标识1";

    if(url_crt.toString()=="http://www.pceggs.com/VerifyCode_Login.aspx")
    {
       /* QPixmap *currentPicture=new QPixmap;
        currentPicture->loadFromData(reply->readAll());
        QDateTime now;
        QString filename = now.currentDateTime().toString("yyMMddhhmmss.jpg");
        currentPicture->save(filename);
        QMovie *move = new  QMovie(filename);
        ui->label_vrf->setMovie(move);
        move->start();*/
       // qDebug()<<"ver";
        QPixmap currentPicture;
        currentPicture.loadFromData(reply->readAll());
        ui->label_vrf->setPixmap(currentPicture);
    }
    else if(url_crt.toString()=="http://www.pceggs.com/nologin.aspx")
    {



        bool ok;


            /*if(relativeUrl.toString()=="http://www.pceggs.com/")
            {
                if(ui->checkBox->checkState()==Qt::Checked)
                {
                    saveLogin sl;
                    sl.iniWrite("isSaved","1");
                    sl.iniWrite("UserName",ui->lineEdit_user->text());
                    sl.iniWrite("PassWord",ui->lineEdit_pwd->text());
                }
                else
                {
                    saveLogin sl;
                    sl.iniWrite("isSaved","");
                    sl.iniWrite("UserName","");
                    sl.iniWrite("PassWord","");
                }

                //this->setAttribute(Qt::WA_QuitOnClose);
                //this->close();

                w.show();
                //w.formmsg->bi.manager->setCookieJar(this->manager->cookieJar());
                w.setCook(this->manager->cookieJar());
            }*/

            QString info(relativeUrl.toString());
            QRegExp e("(Warn=)(\\w)");
            int pos=e.indexIn(info);
            if(pos>-1)
            {
                //qDebug()<<e.cap(2);
                switch (e.cap(2).toInt(&ok,10)) {
                case 2:
                    QMessageBox::information(this,"登陆失败","您输入的验证码错误，请重试.");
                    break;
                case 3:
                    QMessageBox::information(this,"登陆失败","该帐号不存在，还没有PC蛋蛋帐号？.");
                    break;
                case 5:
                    QMessageBox::information(this,"登陆失败","账号已注销");
                    break;
                case 6:
                    QMessageBox::information(this,"登陆失败","密码错误，如果连续错误3次半小时内不能登录！");
                    break;
                case 20:
                    QMessageBox::information(this,"登陆失败","今日密码错误3次及以上，请于半小时后再来登录！");
                    break;
                case 21:
                    QMessageBox::information(this,"登陆失败","今日您所在IP的所有帐号密码错误9次以上，请于半小时后再来登录！.");
                    break;
                case 22:
                    QMessageBox::information(this,"登陆失败","登录失败，您所在IP今日登录的帐号过多！");
                    break;
                case 23:
                    QMessageBox::information(this,"登陆失败","登录失败，验证码失效！.");
                    break;
                case 32:
                    QMessageBox::information(this,"登陆失败","该帐号已经绑定其他PC蛋蛋帐号！.");
                    break;
                case 33:
                    QMessageBox::information(this,"登陆失败","一台电脑一天只能注册一个帐号！");
                    break;
                default:
                    break;
                }
                url_crt.setUrl("http://www.pceggs.com/VerifyCode_Login.aspx");
                manager->get(request_vrf);
            }
            else
            {
                qDebug()<<"else!";
                if(variant.toInt()==200)
                {
                    qDebug()<<200;
                     allcookies=manager->cookieJar()->cookiesForUrl(QUrl("http://www.pceggs.com"));

                     QVariant vtemp;
                     vtemp.setValue(allcookies);
                     qDebug()<<"cookieis:"<<vtemp.toString();
                    emit(Success());


                }
                else
                {

                    if(variant.toInt() == 302) {//重定向
                           QUrl relativeUrl = QUrl(reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString());//获取重定向的信息
                           qDebug()<<"not"<<200<<"url:"<<relativeUrl.toString();

                           if(relativeUrl.url()=="http://www.pceggs.com/")emit(Success());

                           //destUrl=baseurl.resolved(relativeUrl).toString();


                    }
                    url_crt.setUrl("http://www.pceggs.com/VerifyCode_Login.aspx");
                    manager->get(request_vrf);

                }

            }






        /*BetInfo bi;
        bi.setCookie(manager->cookieJar());
        bi.processData();
        bi.getCTime();*/

    }
    else if(url_crt.toString()=="http://www.pceggs.com/play/pg28InsertDo.aspx")
    {
        //qDebug()<<reply->readAll();
        QVariant variant = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
         QVariant reason=reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
          QVariant cache=reply->attribute(QNetworkRequest::CacheLoadControlAttribute);
          QVariant cacheIsSave=reply->attribute(QNetworkRequest::CacheSaveControlAttribute);
          QVariant cookieLoad=reply->attribute(QNetworkRequest::CookieLoadControlAttribute);
          QVariant cookieSave=reply->attribute(QNetworkRequest::CookieSaveControlAttribute);
        // qDebug()<<"reason:"<<reason.toString()<<"cache"<<cache.toString()<<"cache need save?"<<cacheIsSave.toString()<<"cookie need send?"<<cookieLoad.toString()<<"cookie need save?"<<cookieSave.toString();

           //allcookies=manager->cookieJar()->cookiesForUrl(QUrl("http://www.pceggs.com"));
          if (variant.isValid())
            qDebug() << variant.toInt()<<"标识3";

    }
}


void FormLogin::on_pushButton_reflash_clicked()
{
    url_crt.setUrl("http://www.pceggs.com/VerifyCode_Login.aspx");
    manager->get(request_vrf);
}

void FormLogin::on_pushButton_login_clicked()
{

    url_crt.setUrl("http://www.pceggs.com/nologin.aspx");
    /*QByteArray cnt1;
    cnt1.append("__VIEWSTATE=%2FwEPDwUKMTU0MzAzOTU4NmQYAQUeX19Db250cm9sc1JlcXVpcmVQb3N0QmFja0tleV9fFgEFDExvZ2luX1N1Ym1pdL%2Fyae69NsY163G3yuP0lxjz8oXu&__VIEWSTATEGENERATOR=DC42DE27&Head2%24WithdrawCount=7691695&txt_UserName=");
    cnt1.append("931688912@qq.com");
    //cnt1.append(ui->lineEdit_user->text());
    cnt1.append("&txt_PWD=");
    cnt1.append("zyy2130097");
    //cnt1.append(ui->lineEdit_pwd->text());
    cnt1.append("&txt_VerifyCode=");
    cnt1.append(ui->lineEdit_vrf->text());
    cnt1.append("&Login_Submit.x=49&Login_Submit.y=25&FromUrl=http://www.pceggs.com/&SMONEY=ABC");
    manager->post(request_login,cnt1);*/
    login();
    /*QEventLoop eventLoop;
    QObject::connect(manager_login, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();  */

}

void FormLogin::on_pushButton_bet_clicked()
{
    url_crt.setUrl("http://www.pceggs.com/play/pg28InsertDo.aspx");
    /*QSslConfiguration config ;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    request_bet.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request_bet.setSslConfiguration(config);
    bi.setCookie(manager->cookieJar());
    bi.processData();
    QString LID=bi.getLID();
    QString CTime=bi.getCTime(-1);
    QString issue=bi.getIssue(-1);
    qDebug()<<LID<<CTime<<issue;
    QByteArray cnt1;
    cnt1.append("LID=");
    cnt1.append(LID);
    cnt1.append("&CTIME=");
    cnt1.append(CTime);
    cnt1.append("&_issue=");
    cnt1.append(issue);
    cnt1.append("&Cheat=CAE&isdb_p=0&ALLSMONEY=973,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1&SMONEYSUM=1%2C000&lastgain=&isdb=1&SMONEYY=ALD&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox");
    QByteArray temp;
    temp.append("LID=1008102&CTIME=2020-03-16+13%3A55&Cheat=CAE&isdb_p=0&ALLSMONEY=1%2C2%2C3%2C4%2C5%2C6%2C7%2C8%2C9%2C10%2C11%2C12%2C13%2C14%2C15%2C16%2C17%2C18%2C19%2C20%2C21%2C22%2C23%2C24%2C25%2C26%2C27%2C28&SMONEYSUM=406&lastgain=&_issue=922056&isdb=1&SMONEYY=ALD&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox");
    manager->post(request_bet,temp);*/

    /*QTcpSocket client;
    client.connectToHost("183.131.4.57",8080);*/
    /* request_bet.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
     request_bet.setUrl(QUrl("http://www.pceggs.com"));
     QByteArray t;
     t.append(QUrl::toPercentEncoding(QString("LID=1162029&CTIME=2020-03-16 16:45&Cheat=CAE&isdb_p=0&ALLSMONEY=973,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1&SMONEYSUM=1000&lastgain=&_issue=1008136&isdb=1&SMONEYY=ALD&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox")));
     manager->post(request_bet,t);*/

    QByteArray cnt1;
    cnt1.append("LID=");
    cnt1.append("1176689");
    cnt1.append("&CTIME=");
    cnt1.append(QUrl::toPercentEncoding("2020-06-07 09:10"));
    cnt1.append("&_issue=");
    cnt1.append("1022716");
    cnt1.append("&Cheat=CAE&isdb_p=0&ALLSMONEY=");
    cnt1.append(QUrl::toPercentEncoding("1,,,,,,,,,,,,,,,,,,,,,,,,,,,"));
    cnt1.append("&isdb=1&SMONEYY=ALD");
    cnt1.append("&SMONEYSUM=");
    cnt1.append("1");
    cnt1.append("&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox&checkboxd=checkbox");

    //request_bet.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
   // request_bet.setHeader(QNetworkRequest::ContentLengthHeader,cnt1.size());
    request_bet.setRawHeader(QByteArray("User-Agent"),QByteArray("Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:76.0) Gecko/20100101 Firefox/76.0"));
    request_bet.setRawHeader(QByteArray("Accept"),QByteArray("application/json, text/javascript, */*; q=0.01"));
    request_bet.setRawHeader(QByteArray("Accept-Language"),QByteArray("zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2"));
    request_bet.setRawHeader(QByteArray("Host"),QByteArray("www.pceggs.com"));
    request_bet.setRawHeader(QByteArray("Accept-Encoding"),QByteArray("gzip, deflate"));
    request_bet.setRawHeader(QByteArray("X-Requested-With"),QByteArray("XMLHttpRequest"));
    request_bet.setRawHeader(QByteArray("Connection"),QByteArray("keep-alive"));
    //request_bet.setRawHeader(QByteArray("Referer"),QByteArray("http://www.pceggs.com/play/pg28Insert.aspx?LID=1176180"));
    request_bet.setRawHeader(QByteArray("Cookie"),QByteArray("UM_distinctid=17279ae528d7-0af67c83b160db8-15397740-1fa400-17279ae528e38; ckurl.pceggs.com=ckurl=http://www.pceggs.com/play/pg28Insert.aspx?LID=1176180; CLIENTKEY=5661-4628-2045; CLIENTKEY_ShowLogin=5887-9463-8574; .ADWASPX7A5C561934E_PCEGGS=E2F9FD7CDB7E2464E1C7301EBE4D81F4D65DB845F4A730266033036D0D2571A9243AB1BFDDB528637BA3BD0CA62BD607B75312A796BFF0B3BF953DF42BB186940403F14F46245749FAE8AA794568C17051032B89BB33995B76B4D31B784D935DAA44E0C308924C215AEDA1A62A28C6B581F19D8EBF02F024AA900962EB7449E28EFD124A; forever.pceggs.com=UserID=Fs3x3n/wmRwiN2dLa+5fovPEdioqdQ6U&Time=uW9K5brl0YRz4vpfH53e4YUHUWvgFDKH&Date=uW9K5brl0YTOWyCiLV1ZwQ==&Status=KAyeeDyZo6Y=; ASP.NET_SessionId=fjpqfx2kacu5wnvsbsupwqvn; CNZZDATA1262695176=303879428-1591234825-null%7C1591240225; dateflagxyh=2020-06-04"));
    request_bet.setUrl(QUrl("http://www.pceggs.com/play/pg28Insert_ajax.ashx?LID=1176694&CTIME=2020-06-07+09%3A30&ALLSMONEY=1%2C3%2C6%2C%2C%2C%2C%2C%2C%2C%2C%2C%2C%2C%2C%2C4%2C%2C%2C%2C%2C%2C%2C%2C%2C%2C%2C3%2C&isdb_p=0&SMONEYSUM=7&SMONEYY=ALD&Cheat=CAE&_=1591459597454"));



   // manager->post(request_bet,cnt1);
    //allcookies=manager->cookieJar()->cookiesForUrl(QUrl("http://www.pceggs.com"));
    QVariant var;
    var.setValue(allcookies);
    qDebug()<<var.toString();
    request_bet.setHeader(QNetworkRequest::CookieHeader,var);
    manager->get(request_bet);


   // request_bet.setUrl(QUrl("http://www.pceggs.com"));
   // manager->post(request_bet,cnt1);




}
void FormLogin::login()
{

    QByteArray cnt1;
    cnt1.append("__VIEWSTATE=%2FwEPDwUKMTU0MzAzOTU4NmQYAQUeX19Db250cm9sc1JlcXVpcmVQb3N0QmFja0tleV9fFgEFDExvZ2luX1N1Ym1pdL%2Fyae69NsY163G3yuP0lxjz8oXu&__VIEWSTATEGENERATOR=DC42DE27&Head2%24WithdrawCount=7691695&txt_UserName=");
    //cnt1.append("931688912@qq.com");
    cnt1.append(ui->lineEdit_user->text());

    cnt1.append("&txt_PWD=");
    //cnt1.append("zyy2130097");
    cnt1.append(ui->lineEdit_pwd->text());
    cnt1.append("&txt_VerifyCode=");
    cnt1.append(ui->lineEdit_vrf->text());
    cnt1.append("&Login_Submit.x=49&Login_Submit.y=25&FromUrl=http://www.pceggs.com/&SMONEY=ABC");
    //qDebug()<<destUrl;
    request_login.setUrl(QUrl(destUrl));
    manager->post(request_login,cnt1);

   /* QSslConfiguration m_sslConfig = QSslConfiguration::defaultConfiguration();
       m_sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
       m_sslConfig.setProtocol(QSsl::TlsV1_2);

    QNetworkRequest temp;
    temp.setSslConfiguration(m_sslConfig);
    temp.setUrl(QUrl("http://www.pceggs.com"));
    manager->get(temp);*/


}

void FormLogin::setManager(QNetworkAccessManager *&manager)
{
    this->manager=manager;
}

void FormLogin::initial()
{
    initialNetwork();

}

void FormLogin::initialNetwork()
{
    //request
    url_crt.setUrl("http://www.pceggs.com/VerifyCode_Login.aspx");
    request_vrf.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request_vrf.setUrl(QUrl("http://www.pceggs.com/VerifyCode_Login.aspx?"));
    //request_vrf.setUrl(QUrl("https://blog.csdn.net/study_more/article/details/7312015/"));
    request_login.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request_login.setUrl(QUrl("http://www.pceggs.com/nologin.aspx?Warn=6"));
    request_bet.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request_bet.setUrl(QUrl("http://www.pceggs.com/play/pg28InsertDo.aspx"));
    //manager
    reply=manager->get(request_vrf);
   /* QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    connect(manager,&QNetworkAccessManager::finished,this,&FormLogin::replyfinished);
    eventLoop.exec();*/
    connect(manager,&QNetworkAccessManager::finished,this,&FormLogin::replyfinished);

}

void FormLogin::initialStyle()
{
    QIcon icon(":login/sun.png");
    this->setWindowIcon(icon);
    this->setWindowTitle(QObject::tr("登录")); //useless
    //emit toCookie(QNetworkCookieJar*);
    //设置透明
    ui->lineEdit_user->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white");/*border-width:0;*/
    ui->lineEdit_pwd->setStyleSheet("background:transparent;border-style:outset;color:white");
    ui->lineEdit_vrf->setStyleSheet("background:transparent;border-style:outset;color:white");
    //ui->lineEdit_user->setStyleSheet("color:red;");
    ui->label->setStyleSheet("color:white;");
    ui->label_2->setStyleSheet("color:white;");
    ui->label_3->setStyleSheet("color:white;");
    this->setAutoFillBackground(true);
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Window,
                QBrush(QPixmap(":/in/background/1.jpg").scaled(// 缩放背景图.
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);
}
