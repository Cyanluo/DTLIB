#include "DTString.h"
#include <cstdlib>
#include <cstring>
#include "Exception.h"

namespace DTLib
{

void String::init(const char* s)
{
    char* temp = strdup(s ? s : "");

    if(temp)
    {
        m_str = temp;
        m_length = static_cast<int>(strlen(temp));
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemonyException, "No memory to create String...");
    }
}

int* String::make_pmt(const char* str)
{
    unsigned int len = strlen(str);

    int ll = 0;

    int* ret = reinterpret_cast<int*>(malloc(sizeof(int) * len));

    if(ret)
    {
        ret[0] = 0;

        for(unsigned int i=1; i<len; i++)
        {
            while ((str[ll] != str[i]) && ll>0)
            {
                ll = ret[ll - 1];
            }

            if(str[ll] == str[i])
            {
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int String::kmp(const char* s, const char* p)
{
    int ret = -1;

    unsigned int sl = strlen(s);
    unsigned int pl = strlen(p);
    int* pmt = make_pmt(p);

    if( pmt && (pl > 0) && (sl >= pl) )
    {
        for (unsigned int i=0, j=0; i<sl; i++)
        {
            while (s[i] != p[j] && j>0)
            {
                j = static_cast<unsigned int>(pmt[j - 1]);
            }

            if(s[i] == p[j])
            {
                j++;
            }

            if(j == pl)
            {
                ret = static_cast<int>(i + 1 - pl);
                break;
            }
        }
    }

    free(pmt);

    return ret;
}

String::String()
{
    init("");
}

String::String(char* s)
{
    init(s ? s : "");
}

String::String(const String& s)
{
    init(s.m_str);
}


int String::length() const
{
    return m_length;
}

const char* String::c_str() const
{
    return m_str;
}

bool String::equal(const char* s1, const char* s2, int len) const
{
    bool ret = true;

    for(int i=0; i<len && ret; i++)
    {
        ret = ret && (s1[i] == s2[i]);
    }

    return ret;
}

bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = static_cast<int>(strlen(s));

        return ((len < m_length) && equal(m_str, s, len));
    }

    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

bool String::endOf(const char * s) const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = static_cast<int>(strlen(s));

        char* pos = const_cast<char*>(m_str) + (m_length - len);

        return ((len < m_length) && equal(pos, s, len));
    }

    return ret;
}

String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
}

String& String::insert(int i, const char* s)
{
    if( (0 <= i) && (i <= m_length) )
    {
        if(s)
        {
            int len = static_cast<int>(strlen(s));

            char* temp = reinterpret_cast<char*>(malloc(static_cast<unsigned int>(len + m_length + 1)));

            if(temp)
            {
                strncpy(temp, m_str, static_cast<unsigned int>(i));

                strncpy(temp + i, s, static_cast<unsigned int>(len));

                strncpy(temp + i + len, m_str + i, static_cast<unsigned int>(m_length - i));

                temp[len + m_length] = '\0';

                free(m_str);

                m_length = len + m_length;

                m_str = temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemonyException, "No memory to insert string...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter s is invalid...");
        }
    }

    return *this;
}

String& String::trim()
{
    if(m_length > 0)
    {
        int l = 0;
        int r = m_length -1;

        while((0 <= l && l < m_length) && (m_str[l] == ' ')) l++;
        while((0 <= r && r < m_length) && (m_str[r] == ' ')) r--;

        if(l == m_length)
        {
            m_str[0] = '\0';
            m_length = 0;
        }
        else if(l == 0)
        {
            m_str[r + 1] = '\0';
            m_length = r + 1;
        }
        else
        {
            for(int x=0, y=l; y<=r; x++, y++)
            {
                m_str[x] = m_str[l];
            }

            m_str[r - l + 1] = '\0';
            m_length = r - l + 1;
        }
    }

    return *this;
}

int String::indexOf(const String& s) const
{
    return kmp(m_str, s.m_str);
}

int String::indexOf(const char* s) const
{
    return kmp(m_str, s ? s : "");
}

String& String::remove(const String& s)
{
    return remove(indexOf(s), s.m_length);
}

String& String::remove(const char* s)
{
    return remove(indexOf(s), static_cast<int>(strlen(s ? s : "")));
}

String& String::remove(int i, int len)
{
    int m = len + i;

    if((0 <= i) && (i < m_length) && (m < m_length))
    {
        while (m < m_length)
        {
            m_str[i++] = m_str[m++];
        }

        m_str[i] = '\0';

        m_length = i;
    }

    return *this;
}

String& String::replace(const char* s, const char* p)
{
    int pos = indexOf(s);

    if(pos > 0)
    {
        remove(s);
        insert(pos, p);
    }

    return *this;
}

String& String::replace(const String& s, const char* p)
{
    return replace(s.m_str, p);
}

String& String::replace(const char* s, const String& p)
{
    return replace(s, p.m_str);
}

String& String::replace(const String& s, const String& p)
{
    return replace(s.m_str, p.m_str);
}

String String::sub(int i, int len) const
{
    String ret;

    if((0 <= i) && (i < m_length))
    {
        if(len < 0) len = 0;
        if(i + len > m_length) len = m_length - i;

        char* str = reinterpret_cast<char*>(malloc(static_cast<unsigned int>(len) + 1));

        strncpy(str, m_str + i, static_cast<unsigned int>(len));

        str[len] = '\0';

        ret = str;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }

    return ret;
}

String::~String()
{
    free(m_str);
}

char& String::operator [] (int i)
{
    if((0 <= i) && (i < m_length))
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
}

char String::operator [] (int i) const
{
    return const_cast<String&>(*this).m_str[i];
}

bool String::operator == (const String& s) const
{
    return (*this == s.m_str);
}

bool String::operator == (const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") == 0);
}

bool String::operator != (const String& s) const
{
    return !(*this == s);
}

bool String::operator != (const char* s) const
{
    return !(*this == s);
}

bool String::operator > (const String& s) const
{
    return (*this > s.m_str);
}

bool String::operator > (const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") > 0);
}

bool String::operator < (const String& s) const
{
    return (*this < s.m_str);
}

bool String::operator < (const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") < 0);
}

bool String::operator >= (const String& s) const
{
    return (*this >= s.m_str);
}

bool String::operator >= (const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") >= 0);
}

bool String::operator <= (const String& s) const
{
    return (*this <= s.m_str);
}

bool String::operator <= (const char* s) const
{
    return (strcmp(this->m_str, s ? s : "") <= 0);
}

String& String::operator = (const String& s)
{
    return *this = s.m_str;
}

String& String::operator = (const char* s)
{
    if(m_str != s)
    {
        char* temp = strdup(s ? s : "");

        if(temp)
        {
            free(this->m_str);
            this->m_str = temp;
            this->m_length = static_cast<int>(strlen(s));
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "No memory to create String...");
        }
    }

    return *this;
}

String& String::operator = (char c)
{
    char s[] = {c, '\0'};

    return *this = s;
}

String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
    String ret;

    int len = this->length() + static_cast<int>(strlen(s ? s : ""));

    char* temp = reinterpret_cast<char *>(malloc(static_cast<unsigned int>(len + 1)));

    if(temp)
    {
        strcpy(temp, this->m_str);

        strcat(temp, s);

        free(ret.m_str);

        ret.m_str = temp;

        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemonyException, "No memory to create String...");
    }

    return ret;
}

String& String::operator += (const String& s)
{
    return  *this = *this + s;
}

String& String::operator += (const char* s)
{
    return  *this = *this + s;
}

String String::operator - (const String& s) const
{
    return String(*this).remove(s);
}

String String::operator - (const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator -= (const String& s)
{
    return remove(s);
}

String& String::operator -= (const char* s)
{
    return remove(s);
}

}


