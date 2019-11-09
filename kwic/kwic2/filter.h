#ifndef _FILTER_H_
#define _FILTER_H_
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "strategy.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include<QMessageBox>
#include <set>
using namespace std;

double timer[5];
QStringList Input;

QString output1;
QString output2;

class pipe
{
public:
    vector<string> buffer;
    map<string,int>t;

};

void transport(pipe *p1, pipe *p2)
{
    vector<string>::iterator p = p1->buffer.begin();
    for (; p != p1->buffer.end(); p++)
        {
        p2->buffer.push_back(*p);
    p2->t[*p] = p1->t[*p];
    }
    // vector<string>::iterator q;
    // for (q = p2->buffer.begin(); q != p2->buffer.end(); q++)
    //     cout << *q << endl;
    // cout << endl;
}

class filter
{
public:
    filter(){};
    void trans();
    void inputclean();
    void outputclean();

public:
    pipe input;
    pipe output;
};
class inputFilter : public filter
{
public:
    void read();
};
class transFilter : public filter
{
public:
    void exchange();
};
class sortFilter : public filter
{
    sortStratrgy *sst;
public:
    sortFilter(sortStratrgy *sortstratrgy)
    {
        sst = sortstratrgy;
    }
    void sortd()
    {
        output.buffer = sst->sortthis(input.buffer);
        vector<string>::iterator p = input.buffer.begin();
        for (; p != input.buffer.end(); p++)
        {
            output.t[*p] = input.t[*p];
        }
    }
};

class outputFilter : public filter
{
public:
    void put();
};
class findFilter : public filter
{
    search_stratrgy *sst;
public:
    findFilter(search_stratrgy * search_stratrgy_temp){
        sst = search_stratrgy_temp;

    }
    void searchd()
    {
        output.buffer = sst->search(input.buffer);

    }
    void change();
};
///

void findFilter::change()
{
    string str;
    for (vector<string>::iterator iter1 =output.buffer.begin(); iter1 !=output.buffer.end(); iter1++)
    {
        str.append((*iter1).c_str());
        str.append("\n");
        //QString a=QString::fromStdString(str);
        //QMessageBox::information(this, tr("a"),tr("%1!").arg(a));
    }
    output2=QString::fromStdString(str);
}


void transFilter ::exchange()
{


    int count = 0;
     vector<string>::iterator p = input.buffer.begin();
         for (; p != input.buffer.end(); p++)
         {
             string s = *p;
             count = input.t[s];
             s += " ";

             string temp = "";

             vector<string> ss;

             int cnt = 0;
             for (int i = 0; i < s.size(); i++)
             {
                 if (s[i] != ' ')
                     temp += s[i];
                 else
                 {
                     cnt++;
                     temp += " ";
                     ss.push_back(temp);
                     temp = "";
                 }
             }

             string tempstr = "";
             for (int i = 0; i < cnt; i++)
             {
                 tempstr = "";
                 int tempchar = (i + 1) % cnt;
                 for (int j = 0; j < cnt; j++)
                 {

                     tempstr += ss[tempchar];
                     tempchar++;
                     tempchar = tempchar % cnt;
                 }
                 tempstr[tempstr.size() - 1] = '\0';
                 output.t[tempstr] = count;
                 output.buffer.push_back(tempstr);
             }
         }
    /*vector<string>::iterator q;
    for (q = output.buffer.begin(); q != output.buffer.end(); q++)
        cout << *q << endl;
    cout << endl;
    cout<<"-------------------------------------------"<<endl;*/
}

void inputFilter ::read()
{

    for(int i =0;i<Input.size();i++)
    {
        QString temp = Input.at(i);
        string s = temp.toStdString();

        input.buffer.push_back(s);
        input.t[s] = i + 1;


    }


  /*for(int i = 0;i<Input.length();i++)
  {
      if(Input[i]=='\n')
      {
          s[j++] = '\n';


            input.buffer.push_back(s);
          s.clear();

      }
      else {
          s[j++] = Input[i];

      }


  }*/
  vector<string>::iterator q;
  for (q = input.buffer.begin(); q != input.buffer.end(); q++)
      cout << *q << endl;
  cout << endl;
  cout<<"-------------------------------------------"<<endl;



}
void filter::inputclean()
{
    input.buffer.clear();
}
void filter::outputclean()
{
    output.buffer.clear();
}
void filter::trans()
{
    vector<string>::iterator p;
    for (p = input.buffer.begin(); p != input.buffer.end(); p++)
    {
         output.t[*p] = input.t[*p];
         output.buffer.push_back(*p);
    }
        //缺少清除管道操作

     //vector<string>::iterator q;
     //for (q = output.buffer.begin(); q != output.buffer.end(); q++)
    //    cout << *q << endl;
    // cout << endl;
}
void outputFilter::put()
{
    /*string filename;
    cout << "input the filename you want to save to:";
    cin >> filename;
    ofstream tempfile(filename.c_str());
    if (!tempfile)
    {
        cout << "error!" << endl;
    }
    else
    {
        for (vector<string>::iterator iter1 = output.buffer.begin(); iter1 != output.buffer.end(); iter1++)
        {
            tempfile << (*iter1).c_str();
            tempfile << endl;
        }
    }
    cout << "save complain!" << endl;
    tempfile.close();
    */
    string str;
    for (vector<string>::iterator iter1 =output.buffer.begin(); iter1 !=output.buffer.end(); iter1++)
    {
        str.append((*iter1).c_str());
        str.append("\n");
        //QString a=QString::fromStdString(str);
        //QMessageBox::information(this, tr("a"),tr("%1!").arg(a));
    }
    output1=QString::fromStdString(str);
    //QMessageBox::information(this, tr("output"),tr("%1!").arg(Output));
}

#endif // !FILTER_H_
