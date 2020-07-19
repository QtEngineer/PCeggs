#ifndef SUBFORM_H
#define SUBFORM_H

#include <QWidget>

class SubForm : public QWidget
{
    Q_OBJECT
public:
    explicit SubForm(QWidget *parent = nullptr);
    virtual void initial();
    virtual void initialStyle()=0;
signals:

};

#endif // SUBFORM_H
