#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>
#include <QPixmap>
#include <QMovie>
#include <QByteArray>
#include <QDebug>
#include <QVariant>
#include <QPalette>
#include <QMovie>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>

#include "global.h"
#include  "subform.h"
namespace Ui {
class FormLogin;
}

class FormLogin : public SubForm
{
    Q_OBJECT

public:
    static QNetworkRequest sRequst;
    static QNetworkCookieJar* cookieJar;
    QList<QNetworkCookie> allcookies;
    void  setManager(QNetworkAccessManager*&);
    explicit FormLogin(QWidget *parent = 0);
    void initial();
    void initialNetwork();
    void initialStyle();
    ~FormLogin();

public slots:
    void replyfinished(QNetworkReply*);
    //void newreplyfinished();
private slots:

    void on_pushButton_reflash_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_bet_clicked();

signals:
    void toCookie(QNetworkCookieJar*);
    void Success();
private:
    Ui::FormLogin *ui;
    QNetworkAccessManager *manager=nullptr;
    QNetworkRequest request_vrf;
    QNetworkRequest request_login;
    QNetworkRequest request_bet;
    QNetworkReply* reply;
    QUrl url_crt;
    //BetInfo bi;



    void login();
    QString destUrl;
    QUrl baseurl;


    //QNetworkCookieJar* cook;
};

#endif // FORMLOGIN_H
