#ifndef VALUE_H
#define VALUE_H

#include <cstring>
#include <string>
#include <iostream>

template <class A>
class Value{
public:
    static inline A min(A data1, A data2){
        return ((compare(data1, data2)<0)? data1: data2);
    }

    static inline A max(A data1, A data2){
        return ((compare(data1, data2)>0)? data1: data2);
    }
    static inline double compare(A data1, A data2);
};

template <class A>
inline double Value<A>::compare(A data1, A data2){
    return (double)(data1-data2);
}

template <>
inline double Value<char*>::compare(char *data1, char *data2){
    return (double)strcmp(data1, data2);
}

template <>
inline double Value<std::string>::compare(std::string data1, std::string data2){
    return (double)strcmp(data1.c_str(),data2.c_str());
}




#endif // VALUE_H
