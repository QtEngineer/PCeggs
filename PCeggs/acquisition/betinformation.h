#ifndef BETINFORMATION_H
#define BETINFORMATION_H

#include <QObject>
#include <QWebEngineView>
#include <QNetworkCookieJar>
#include <QList>
#include <QString>
#include <QStringList>
#include <QEventLoop>
#include <QTimer>
#include "pceggsdatabase.h"
#include "mymsg.h"
class BetInformation: public QObject
{
    Q_OBJECT
public:
    explicit BetInformation(QObject *parent = nullptr);
    void initial();
    void setCookie(QNetworkCookieJar*);
    void downloadData();
    ~BetInformation();

    //function of getting source data
    QString getResults(int);
    QString getIssue(int);
    QString getCTime(int);
    QString getLID();
    QString getStatus();
    //QString getResults(int);
    QString getAccount();   
    void getAllInformation();
public slots:
    bool getRealTimeData();
signals:
    void getResultsFinished();
    void getNewData();
    void downloadFinished(int );
private:
    QWebEngineView* webView;
    QWebEngineHttpRequest* request;
    QUrl baseUrl;
    QString rawInfo;
    QTimer timer;
    QEventLoop loop;

    // to save source data
    QStringList results;
    QStringList issue;
    QStringList CTime;
    QStringList LID;
    QStringList status;
    //QStringList results;
    QStringList account;

    //results make up by 3 part
    QStringList results1;
    QStringList results2;
    QStringList results3;
    //filter
    QRegExp e_results;   // the direct data
    QRegExp e_issue;      //to Check data consistency,especially issue
    QRegExp e_CTime;
    QRegExp e_LID;
    QRegExp e_status;
    //QRegExp e_results;
    QRegExp e_account;

    QString current_LID; //use to test

    PCeggsDataBase db;


};

#endif // BETINFORMATION_H
