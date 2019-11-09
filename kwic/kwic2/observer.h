#ifndef OBSERVER_H
#define OBSERVER_H

#include <QDebug>
#include <QPlainTextEdit>
#include<QTextBlock>

class observer{
public:
    virtual void updata(string newState) = 0;
};

class observerText1 : public observer{
private:
    string observerState;
public:
    QPlainTextEdit *q;
    void updata(string newState)
    {
        observerState = newState;
        qDebug() << "imformation:" + QString::fromStdString(newState)<< endl;
        q->setPlainText(QString::fromStdString(newState));
    }
};

class observerText2 : public observer{
private:
    string observerState;
public:
    QPlainTextEdit *q;
    void updata(string newState);
};


#endif // OBSERVER_H
