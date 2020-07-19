#include "betinfo.h"

BetInfo::BetInfo(QObject *parent) : QObject(parent),
    e_issue("(height=\"32\" bgcolor=\"#FFFaC7\">)(\\w+)"),
    e_CTime("(height=\"28\" bgcolor=\")(#FFFFFF|#f8f8f8)(\">)(\\S+\\s\\S+)(</td>)"),
    e_LID("(chkwin\\('\\w+',\\s')(\\w+)"),
    e_status("(chkStatus\\(')(\\w+)"),
    e_results("(chkResult\\(')(\\w+)(\\s\\+\\s)(\\w+)(\\s\\+\\s)(\\w+)(\\s=\\s',\\s')(\\w+)"),    //7 + 0 + 2 = ', '19
    e_account("(金蛋：<b>)(\\S+)")
{

    //manager=new QNetworkAccessManager(this);
    /*request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");    //temp
    request.setUrl(QUrl("http://www.pceggs.com/play/pxya.aspx"));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyfinished(QNetworkReply*)));*/
    //e_issue=new QRegExp("(height=\"32\" bgcolor=\"#FFFaC7\">)(\\w+)");


}

void BetInfo::replyfinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    info = codec->toUnicode(reply->readAll());
    //qDebug()<<info;
}

void BetInfo::processData()
{
    /*QByteArray ba;
    ba.append("__VIEWSTATE=%2FwEPDwUKMTU5OTU1NjAyNWRkJUnSVGTCSZ%2BCjUD%2F8xBj6URqqMM%3D&__VIEWSTATEGENERATOR=5B815096&soundshow=&reloadshow=&Head2%24WithdrawCount=7712274&CurrentPageIndex=2");
    manager->post(request,ba);*/
    manager->get(request);
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

}

QString BetInfo::getIssue(int i)
{


    issue.clear();
    bool ok;
    QString temp(info);
    //qDebug()<<temp;
    int pos=e_issue.indexIn(temp);
    //issue_no=e_issue.cap(2).toInt(&ok,10);
    //qDebug()<<pos;

    while(pos>-1)
    {



        issue.append(e_issue.cap(2));
        //qDebug()<<e_issue.cap(2);
        temp=temp.mid(pos+e_issue.cap(1).length());
        pos=e_issue.indexIn(temp);

    }
    //qDebug()<<issue;

    return issue[i+6];
}

QString BetInfo::getCTime(int i)
{
    CTime.clear();
    QString temp(info);
    int pos=e_CTime.indexIn(temp);
    while(pos>-1)
    {
        CTime.append(e_CTime.cap(4));
        temp=temp.mid(pos+e_CTime.cap(1).length());
        pos=e_CTime.indexIn(temp);

    }
    //qDebug()<<CTime;
    return CTime[i+6];

}

QString BetInfo::getLID()
{

    LID.clear();
    QString temp(info);
    int pos=e_LID.indexIn(temp);
    while(pos>-1)
    {
        LID.append(e_LID.cap(2));
        temp=temp.mid(pos+e_LID.cap(1).length());
        pos=e_LID.indexIn(temp);

    }
    //qDebug()<<LID;
    return LID[5];

}
QString BetInfo::getStatus()
{
    status.clear();
    QString temp(info);
    int pos=e_status.indexIn(temp);
    while(pos>-1)
    {
        status.append(e_status.cap(2));
        temp=temp.mid(pos+e_status.cap(1).length());
        pos=e_status.indexIn(temp);

    }
    //qDebug()<<status;
    return status[5];


}
QString BetInfo::getResults(int i)
{
    bool ok;
    results.clear();
    QString temp(info);
    int pos=e_results.indexIn(temp);
    while(pos>-1)
    {
        results.append(QString::number( e_results.cap(8).toInt(&ok,10)-10,10));
        temp=temp.mid(pos+e_results.cap(1).length());
        pos=e_results.indexIn(temp);

    }

    //qDebug()<<results;
    return results[i];

}
QString BetInfo::getAccount()
{

    //account.clear();
    QString temp(info);
    int pos=e_account.indexIn(temp);
    /*while(pos>-1)
    {

        a=e_account.cap(2).toInt();

        temp=temp.mid(pos+e_account.cap(1).length());
        pos=e_account.indexIn(temp);
    }*/
    QString s=e_account.cap(2);
    return  s;

}
/*void BetInfo::setCookie(QNetworkCookieJar *cook)
{
    manager->setCookieJar(cook);
}*/
void BetInfo::setManager(QNetworkAccessManager *manager)
{
    this->manager=manager;
}
void BetInfo::initNetwork()
{
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setUrl(QUrl("http://www.pceggs.com/play/pxya.aspx"));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyfinished(QNetworkReply*)));
}
void BetInfo::initial()
{
    initNetwork();
}
