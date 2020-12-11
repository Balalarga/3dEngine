#include "utils.h"
#include <iostream>
using namespace std;

namespace Utils {


}


namespace Log {

template<class T>
void infoln(T data)
{
    info(data);
    info("\n");
}
template<class T>
void info(T data)
{
    cout<<data<<endl;
}

}
