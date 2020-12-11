#ifndef UTILS_H
#define UTILS_H

#include <iostream>

namespace Log {

void info(std::string msg){
    std::cout<<msg;
}
void infoln(std::string msg){
    info(msg);
}

}


#endif // UTILS_H
