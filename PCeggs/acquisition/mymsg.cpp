#include "mymsg.h"

mymsg::mymsg(int is,int n1,int n2,int n3):issue(is),no1(n1),no2(n2),no3(n3)
{

}
mymsg::mymsg(int rst)
{
    this->rst=rst;
}
/*void setIssue(int);
    void setNo1(int);
    void setNo2(int);
    void setNo3(int);
    int getIssue();
    int getNo1();
    int getNo2();
    int getNo3();
    int getRst();
    QString getBS();
    QString getPS();
    QString getMS();*/
void mymsg::setIssue(int is)
{
    issue=is;
}
void mymsg::setNo1(int n1)
{
    no1=n1;
}
void mymsg::setNo2(int n2)
{
    no2=n2;
}
void mymsg::setNo3(int n3)
{
    no3=n3;
}
void mymsg::setResults(int re)
{
    rst=re;
}
int mymsg::getIssue() const
{
    return issue;
}
int mymsg::getNo1()
{
    return no1;
}
int mymsg::getNo2()
{
    return no2;
}
int mymsg::getNo3()
{
    return no3;
}
int mymsg::getRst() const
{
    return rst;
}
int mymsg::getBS() const
{
    //return rst>13?"大":"小";
    return rst>13?1:0;

}
int mymsg::getPS() const
{
    return rst%2==0?0:1;
}
int mymsg::getMS() const
{
    return rst>9&&rst<18?1:0;
}
QString  mymsg::getTextNo()
{
    return QString::number(no1)+"+"+QString::number(no2)+"+"+QString::number(no3)+"=";
}
int mymsg::getNo1ByIssue(int n1)
{
    if(this->getIssue()==n1)
        return this->getNo1();
    else
        return 0;
}
