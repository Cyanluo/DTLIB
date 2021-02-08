#ifndef DTSTRING_H
#define DTSTRING_H

#include "Object.h"

namespace DTLib
{

class String:public Object
{
protected:
    char* m_str;
    int m_length;
    void init(const char* s);
    bool equal(const char* s1, const char* s2, int len) const;
    static int* make_pmt(const char* str);
    static int kmp(const char* s, const char* p);
public:
    String();
    String(char* s);
    String(const String& s);
    int length() const;
    const char* c_str() const;
    bool startWith(const String& s) const;
    bool startWith(const char* s) const;
    bool endOf(const String& s) const;
    bool endOf(const char * s) const;
    String& insert(int i, const String& s);
    String& insert(int i, const char* s);
    String& trim();
    int indexOf(const String& s) const;
    int indexOf(const char* s) const;
    String& remove(const String& s);
    String& remove(const char* s);
    String& remove(int i, int len);
    String& replace(const char* s, const char* p);
    String& replace(const String& s, const char* p);
    String& replace(const char* s, const String& p);
    String& replace(const String& s, const String& p);
    String sub(int i, int len) const;
    ~String();

    char& operator [] (int i);
    char operator [] (int i) const;
    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator > (const String& s) const;
    bool operator > (const char* s) const;
    bool operator < (const String& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String& operator += (const String& s);
    String& operator += (const char* s);

    String operator - (const String& s) const;
    String operator - (const char* s) const;
    String& operator -= (const String& s);
    String& operator -= (const char* s);
};


}


#endif // DTSTRING_H
