#ifndef _FILTER_H_
#define _FILTER_H_

#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <algorithm>
using namespace std;
double timer[5];
class pipe
{
public:
    vector<string> buffer;
};

void transport(pipe *p1, pipe *p2)
{
    vector<string>::iterator p = p1->buffer.begin();
    for (; p != p1->buffer.end(); p++)
        p2->buffer.push_back(*p);
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
public:
    void sortthis();
};
class outputFilter : public filter
{
public:
    void put();
};
class findFilter : public filter
{
public:
    void find();
};
/////
bool comp(string a, string b)
{
    int len = a.length() > b.length() ? a.length() : b.length();
    int i = 0;
    for (i; i < len; i++)
    {
        if (a[i] == b[i])
            continue;
        else
        {
            if (a[i] == '\0' || b[i] == '\0')
            {
                if (b[i] == '\0')
                    return false;
                if (a[i] == '\0')
                    return true;
            }
            else if (a[i] == ' ' || b[i] == ' ')
            {
                if (b[i] == ' ')
                    return false;
                if (a[i] == ' ')
                    return true;
            }
            else
            {
                char ap, bp;
                if (a[i] >= 'A' && a[i] <= 'Z')
                    ap = a[i] + 32;
                else
                    ap = a[i];
                if (b[i] >= 'A' && b[i] <= 'Z')
                    bp = b[i] + 32;
                else
                    bp = b[i];
                if (bp < ap)
                    return false;
                else if (ap < bp)
                    return true;
                else
                {
                    if (a[i] >= 'A' && a[i] <= 'Z')
                        return false;
                    else
                        return true;
                }
            }
        }
    }
}
void findFilter ::find()
{
    cout << "whether find?(y/n)";
    char temp;
    cin >> temp;
    getchar();
    while (temp != 'y' && temp != 'n')
    {
        cout << "please retry" << endl;
        cin >> temp;
        getchar();
    }
    if (temp == 'y')
    {
        vector<string> strcontain;
        string s;
        getline(cin, s);
        s += ' ';
        string ss;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
            {
                strcontain.push_back(ss);
                ss = "";
            }
            else
                ss += s[i];
        }//
        // vector<string>::iterator p = strcontain.begin();
        // for (; p != strcontain.end(); p++)
        //     cout << *p << endl;
        for (int i = 0; i < input.buffer.size(); i++)
        {
            vector<string> strcontaintemp;
            string temps = input.buffer[i];
            temps += ' ';
            string tempss;
            for (int j = 0; j < temps.size(); j++)
            {
                if (temps[j] == ' ')
                {
                    strcontaintemp.push_back(tempss);
                    tempss = "";
                }
                else
                    tempss += temps[j];
            }
            //cout<<1;
            int flag = 0;
            for (int j = 0; j < strcontain.size(); j++)
            {
                flag = 0;
                for (int k = 0; k < strcontaintemp.size(); k++)
                {
                    if (strcontaintemp[k] == strcontain[j])
                    {
                        // cout<<1;
                        flag = 1;
                    }
                }
                if (flag != 1)
                    break;
            }
            if (flag == 1)
            {
                cout << input.buffer[i] << endl;
            }
        }
    }
    else
    {
    }
}

void sortFilter ::sortthis()
{
    vector<string> swap = input.buffer;
    sort(swap.begin(), swap.end(), comp);
    output.buffer = swap;
    // vector<string>::iterator p = output.buffer.begin();
    // for (; p != output.buffer.end(); p++)
    // {
    //     cout << *p << endl;
    // }
}

void transFilter ::exchange()
{
    vector<string>::iterator p = input.buffer.begin();
    for (; p != input.buffer.end(); p++)
    {
        string s = *p;
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
            output.buffer.push_back(tempstr);
        }
    }
    // vector<string>::iterator q;
    // for (q = output.buffer.begin(); q != output.buffer.end(); q++)
    //     cout << *q << endl;
    // cout << endl;
}

void inputFilter ::read()
{
    string filename;
    string line, word;
    bool mark = false;
    while (!mark)
    {
        cout << "input your file name: ";
        cin >> filename;
        fstream tempfile(filename.c_str());
        if (!tempfile)
            cout << "error!" << endl;
        else
        {
            cout << "open successed!" << endl;
            while (getline(tempfile, line))
                input.buffer.push_back(line);
            mark = true;
            tempfile.close();
        }
    }
}
void filter::trans()
{
    vector<string>::iterator p;
    for (p = input.buffer.begin(); p != input.buffer.end(); p++)
        //缺少清除管道操作
        output.buffer.push_back(*p);
    // vector<string>::iterator q;
    // for (q = output.buffer.begin(); q != output.buffer.end(); q++)
    //     cout << *q << endl;
    // cout << endl;
}
void outputFilter::put()
{
    string filename;
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
}

#endif // !FILTER_H_
