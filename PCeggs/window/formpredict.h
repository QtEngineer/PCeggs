#ifndef FORMPREDICT_H
#define FORMPREDICT_H

#include <QWidget>
#include <QList>
#include "acquisition/mymsg.h"
#include <QTimer>
#include "subform.h"
namespace Ui {
class FormPredict;
}

class FormPredict : public SubForm
{
    Q_OBJECT

public:
    explicit FormPredict(QWidget *parent = 0);
    ~FormPredict();
    void addItem();
    void Check();
    void Init();
    void initialStyle() override;

    void getData(mymsg &msg);

private:
    Ui::FormPredict *ui;
    QList<mymsg> listMsg;
    QTimer timer;
private slots:
    void fromMsg(mymsg);
     void reflesh();
    void getAccount(QString);
     void on_pushButton_clicked();
};

#endif // FORMPREDICT_H
