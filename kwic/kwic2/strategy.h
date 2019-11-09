#ifndef STRATEGY_H
#define STRATEGY_H
#include "mainwindow.h"
#include "filter.h"
#include <set>
string s;
class sortStratrgy {
public:
    virtual vector<string> sortthis(vector<string>) = 0;
};

class quicksortAlgorithm : public sortStratrgy
{
public:
    vector<string> sortthis(vector<string>);
};
class bubblesortAlgorithm : public sortStratrgy
{
public:
    vector<string> sortthis(vector<string>);
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

vector<string> quicksortAlgorithm ::sortthis(vector<string> swap)
{
    sort(swap.begin(), swap.end(), comp);
    return swap;
}

vector<string> bubblesortAlgorithm ::sortthis(vector<string> swap)
{
    int l = swap.size();
    for(int i = 0; i < l-1; i++)
    {
        for(int j = 0;j < l - 1 - i; j++)
        {
            if(comp(swap[j+1],swap[j]))
            {
                string temp = swap[j];
                swap[j] = swap[j+1];
                swap[j+1] = temp;
            }
        }
    }
    return swap;
}
class  search_stratrgy
{
public:
    virtual vector<string> search(vector<string>) = 0;

};
class  normal_search :public search_stratrgy
{
public:
    vector<string> search(vector<string>);

};

class  quick_search :public search_stratrgy
{
public:
    vector<string> search(vector<string>);

};
vector<string> normal_search::search(vector <string> temp)
{
    vector<string> strcontain;
    vector <string> result;
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
    }

    for (int i = 0; i < temp.size(); i++)
    {
        set<string> strcontaintemp;
        string temps = temp[i];
        temps += ' ';
        string tempss;
        for (int j = 0; j < temps.size(); j++)
        {
            if (temps[j] == ' ')
            {
                strcontaintemp.insert(tempss);
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
            if(strcontaintemp.find(strcontain[j])!=strcontaintemp.end())
                flag = 1;
            if (flag != 1)
                break;
        }
        if (flag == 1)
        {
            result.push_back(temp[i]);
        }

    }

    return result;
}
vector<string> quick_search::search(vector <string> temp)
{

        vector<string> strcontain;
        vector <string> result;

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
        }

        for (int i = 0; i < temp.size(); i++)
        {
            vector<string> strcontaintemp;
            string temps = temp[i];
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

                result.push_back(temp[i]);
            }

        }

        return result;

}

#endif // STRATEGY_H
