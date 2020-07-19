#ifndef MYMSG_H
#define MYMSG_H

#include<QString>
class mymsg
{
public:
    mymsg(int is=0,int n1=0,int n2=0,int n3=0);
    mymsg(int rst);
    void setIssue(int);
    void setNo1(int);
    void setNo2(int);
    void setNo3(int);
    void setResults(int);
    int getIssue() const;
    int getNo1();
    int getNo2();
    int getNo3();
    int getRst() const;
    int getBS() const;
    int getPS() const;
    int getMS() const;
    //QString getBS() const;
    //QString getPS() const;
    //QString getMS() const;

    QString getTextNo();
    int getNo1ByIssue(int);
private:
    int issue;
    int no1;
    int no2;
    int no3;
    int rst;

};

#endif // MYMSG_H
