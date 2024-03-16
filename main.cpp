#include <iostream>
#include <cstring>

#include "include.h"
#include "util.h"
#include "melialib.h"
using namespace std;




int main(int argc, char **argv) {
    medialib med;
    for(int i=0; i<med._channel_list.size(); i++)
        cout << med._channel_list[i]->_desc << endl;

    return 0;
}
