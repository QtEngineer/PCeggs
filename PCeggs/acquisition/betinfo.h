#ifndef BETINFO_H
#define BETINFO_H

#include <QObject>
#include <QRegExp>
#include<QTextCodec>
#include<QNetworkAccessManager>
#include<QUrl>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QEventLoop>
#include<QString>
#include<QStringList>
class BetInfo : public QObject
{
    Q_OBJECT
public:
    explicit BetInfo(QObject *parent = nullptr);
    void processData();
    QString getIssue(int);
    QString getCTime(int);
    QString getLID();
    QString getStatus();
    QString getResults(int);
    QString getAccount();
    //void setCookie(QNetworkCookieJar*);
    QNetworkAccessManager *manager=nullptr;
    void setManager( QNetworkAccessManager*);
    void initial();
    void initNetwork();

signals:

public slots:
    void replyfinished(QNetworkReply*);

private:
    //QUrl url;
    int issue_no;
    QNetworkRequest request;
    QString info;
    QRegExp e_issue;
    QRegExp e_CTime;
    QRegExp e_LID;
    QRegExp e_status;
    QRegExp e_results;
    QRegExp e_account;
    QStringList issue;
    QStringList CTime;
    QStringList LID;
    QStringList status;
    QStringList results;
    QStringList account;

};

#endif // BETINFO_H
