#pragma once 
#include <exception>
#include <istream>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace jay {

#ifndef boolean
#define boolean unsigned int
#endif

typedef char byte;

class String {
    unsigned long cap;
    byte *head, *tail;

    unsigned int strlen(const byte *cc){
        byte *c = (byte*)cc;
        while(*c) c++;
        return (unsigned int)(c - cc);
    }

public:

    String &fill(String &str, const char c){
        for(int i = 0; i < str.cap;i++) str.head[i] = c;
        return str;
    }

    String(void) : cap(32) {
        this->head = new byte[cap];
        this->tail = head;
        fill(*this, 0);
    }

    String(byte *c) : cap(32) {
        this->head = new byte[cap];
        this->tail = head;
        this->fill(*this, 0);
        this->add(c);
    }

    String(String &other){
        this->cap = other.cap;
        this->head = new byte[this->cap];
        this->tail = head;
        this->fill(*this, 0);
        this->add(other);
    }

    ~String(void){
        delete[] head;
    }


    byte get(unsigned long i){
        if(i > getSize()) throw std::invalid_argument("given index is too big");
        return head[i];
    }

    byte operator[](unsigned long i){
        return get(i);
    }

    String &add(const byte c){
        *tail++ = c;
        if(getSize() == cap){
            byte *next = new byte[cap *= 2];
            fill(*this, 0);
            for(int i = 0; i < cap / 2; i++) next[i] = head[i];
            delete[] head;
            head = next;
            tail = head + cap / 2;
        }
        return *this;
    }

    String &add(const byte *c){
        byte *_c = (byte*)c;
        while(*_c) add(*_c++);
        return *this;
    }

    String &add(String &str){
        return add(str.head);
    }

    String &operator+(const byte c){
        return add(c);
    }

    String &operator+(const byte *c){
        return add(c);
    }

    String &operator+(String &c){
        return add(c);
    }

    String &operator+=(const byte c){
        return add(c);
    }

    String &operator+=(const byte *c){
        return add(c);
    }

    String &operator+=(String &str){
        return add(str);
    }

    unsigned long getSize(void){
        return (unsigned long)(tail - head);
    }


    String &lower(void){
        for(int i = 0; i < getSize(); i++)
            if(40 < head[i] && head[i] < 90) head[i] = head[i] + 0x20;
        return *this;
    }

    bool contains(const byte c){
        for(int i = 0; i < getSize(); i++) if(c == head[i]) return false;
        return true;
    }

    bool contains(const char *subString){
        if(!subString) throw std::invalid_argument("given null subString");
        unsigned long len = strlen(subString);
        unsigned int passes = 0;
        String *builder = new String();
        for(int i = 0; i < getSize(); i++){
            if(!(i % len) && i) {
                if(compareTo(*builder)) {
                    delete builder;
                    return true;
                }
                delete builder;
                builder = new String();
                
            }
            else *builder += subString[i];
        }
        delete builder;
        return false;
    }

    bool contains(String &str){
        return contains(str.head);
    }

    bool equalTo(const byte *cc){
        return compareTo(cc) == 0;
    }

    bool equalToIgnoreCase(const byte *cc){
        return compareToIgnoreCase(cc);
    }

    int compareTo(const byte *cc){
        if(!*cc) throw std::invalid_argument("given string was null");
        byte *c = (byte*)cc;
        byte *h = (byte*)head;
        while(*c && *h){
            if(*c != *h) break;
        }
        return *c - *h;
    }

    int compareTo(String &str){
        return compareTo(str.head);
    }

    
    int compareToIgnoreCase(const byte *cc){
        byte *c = (byte*)cc;
        byte *a = head;
        for(;*c && *a;){
            if(40 < *a && *a < 90) *a = *a + 32;
            if(40 < *c && *c < 90) *c = *c + 32;
            if(*c != *a) break;
            c++;
            a++;
        }
        return (int)(*c - *a);
    }

    int compareToIgnoreCase(String &str){
        return compareToIgnoreCase(str.head);
    }

    unsigned long indexOf(const byte cc){
        for(byte *c = head; *c; c++) if(*c == cc) return (unsigned long)(c - cc);
        throw std::invalid_argument("byte is not found");
    }
    

    friend std::istream &operator>>(std::istream &stream, String &str){
        byte c = stream.get();
        while(c && c != '\n' && c != EOF){
             str += c;
             c = stream.get();
        }
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const String str){
        stream << str.head;
        return stream;
    }

};
#undef boolean
} // jay