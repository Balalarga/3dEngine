#ifndef UTILS_H
#define UTILS_H


namespace Log {
#include <iostream>
using namespace std;

template <class T>
void info(T msg){
    cout<<msg;
}
template <class T>
void infoln(T msg){
    info(msg);
    info('\n');
}

}


#endif // UTILS_H
