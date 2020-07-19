      #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include "formlogin.h"
#include "formpredict.h"
#include "acquisition/betinformation.h"
#include "tools/networkcookie.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //QStackedWidget* stackedWidget;
    FormLogin* formLogin;
    FormPredict* formPredict;
    QNetworkAccessManager* manager;
    BetInformation betInformation;
    //NetworkCookie cookie;
private slots:
    void LoginSuccess();
};
#endif // MAINWINDOW_H
