#include <iostream>
#include "filter.h"
using namespace std;
int main()
{
    inputFilter filter1;
    filter1.read();
    filter1.trans();
    findFilter filter2;
    transport(&filter1.output,&filter2.input);
    filter2.find();
    filter2.trans();
    transFilter filter3;
    transport(&filter2.output,&filter3.input);
    filter3.exchange();
    sortFilter filter4;
    transport(&filter3.output,&filter4.input);
    filter4.sortthis();
    outputFilter filter5;
    transport(&filter4.output,&filter5.input);
    filter5.trans();
    filter5.put();
    return 0;
}