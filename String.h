#pragma once 
#include <ostream>
#include <stdexcept>

namespace jay {

typedef char byte;

class String {
    unsigned long cap, size;
    byte *inner;

public:
    String() : cap(8) , size(0) {
        this->inner = new byte[this->cap];
        fill(0);
    }

    ~String(){
        delete[] inner;
    }

    void add(const byte c){
        inner[size++] = c;
        if(size == cap){
            byte *next = new byte[cap *= 2];
            fill(next, 0, cap);
            for(int i =0; i < cap / 2; i++) next[i] = inner[i];
            delete[] inner;
            inner = next;
        }
    }

    void add(const byte *cc){
        byte *c = (byte*)cc;
        while(*c) add(*(c++));
    }

    String &operator+=(const byte c){
        add(c);
        return *this;
    }

    String &operator+=(const byte *cc){
        add(cc);
        return *this;
    }

    unsigned long getSize(){
        return size;
    }


    void fill(String &s, const byte c){
        for(int i = 0; i < s.cap; i++) inner[i] = c;
    }

    void fill(byte *buff, const byte c, unsigned int s){
        for(int i = 0; i < s; i++) buff[i] = c;
    }

    void fill(const byte c){
        fill(*this, c);
    }

    friend std::ostream &operator<<(std::ostream &stream, const String str){
        stream << str.inner;
        return stream;
    }

};
}; // jay