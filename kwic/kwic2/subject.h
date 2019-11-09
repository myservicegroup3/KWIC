#ifndef SRC_SUBJECT_H_
#define SRC_SUBJECT_H_

#include "observer.h"
#include <QDebug>

class subject{
private:
    vector<observer*> mObservers;
public:
    void attach(observer*);
    void detach(observer*);
    void notifyEveryone(string);
};

void subject::attach(observer* obs)
{
    mObservers.push_back(obs);
    qDebug() << "attach an observer" << endl;
}

void subject::detach(observer* obs)
{
    mObservers.push_back(obs);
    qDebug() << "detach an observer" << endl;
}
void subject::notifyEveryone(string newStates)
{
    for(int i = 0; i < mObservers.size(); i++)
    {
        mObservers[i]->updata(newStates);
    }
}

class subjectText : public subject
{
private:
    string state;

public:
    string getState() {
        return state;
    }

    void change(string newState) {
        state = newState;
        qDebug() << "concreteSubject state:" << QString::fromStdString(newState) << endl;

        //状态发生改变，通知观察者
        notifyEveryone(newState);
    }
};
#endif /* SRC_SUBJECT_H_ */
