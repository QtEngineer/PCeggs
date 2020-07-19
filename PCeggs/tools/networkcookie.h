#ifndef NETWORKCOOKIE_H
#define NETWORKCOOKIE_H

#include <QObject>
#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkCookieJar>
class NetworkCookie : public QNetworkCookieJar
{
    Q_OBJECT
public:
    explicit NetworkCookie(QObject *parent = nullptr);
    ~NetworkCookie();
    QList<QNetworkCookie> getCookies();
    void setCookies(const QList<QNetworkCookie>& cookieList);
    void setCookies(QNetworkCookieJar*);
private:
    QNetworkCookieJar cookieJar;

signals:

};

#endif // NETWORKCOOKIE_H
