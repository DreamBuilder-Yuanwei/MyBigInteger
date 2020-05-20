#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

struct BigInteger {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger(long long num = 0) { *this = num; } // 构造函数

    BigInteger operator = (long long num);// 赋值运算符
    BigInteger operator = (const string& str); // 赋值运算符

    //比较操作
    bool operator < (const BigInteger& b) const;
    bool operator > (const BigInteger& b) const;
    bool operator <= (const BigInteger& b) const;
    bool operator >= (const BigInteger& b) const;
    //比对操作
    bool operator != (const BigInteger& b) const;
    bool operator == (const BigInteger& b) const;

    BigInteger operator + (const BigInteger& b) const;//加法运算
    BigInteger operator += (const BigInteger& b){// +=运算符
        *this = *this + b;
        return *this;
    }
    BigInteger operator - (const BigInteger& b) const;//减法运算
    BigInteger operator -= (const BigInteger& b){// -=运算符
        *this = *this - b;
        return *this;
    }
    BigInteger operator * (const BigInteger& b) const;//乘法运算
    BigInteger operator *= (const BigInteger& b){// *=运算符
        *this = *this * b;
        return *this;
    }
    BigInteger operator / (const BigInteger& b) const;//除法运算
    BigInteger operator /= (const BigInteger& b){// /=运算符
        *this = *this / b;
        return *this;
    }

    BigInteger fac()const;//阶乘运算

    BigInteger operator % (const BigInteger& b) const;//取余运算
    BigInteger operator %= (const BigInteger& b){// /=运算符
        *this = *this % b;
        return *this;
    }
};

 // 赋值运算符重载
BigInteger BigInteger::operator = (long long num) {
    s.clear();
    do {
        s.push_back(num % BASE);
        num /= BASE;
    } while(num > 0);
    return *this;
}
BigInteger BigInteger::operator = (const string& str) {
    s.clear();
    int x, len = (str.length() - 1) / WIDTH + 1;
    for(int i = 0; i < len; i++) {
        int end = str.length() - i*WIDTH;
        int start = max(0, end - WIDTH);
        sscanf(str.substr(start, end-start).c_str(), "%d", &x);
        s.push_back(x);
    }
    return *this;
}
//比较操作和比对操作
bool BigInteger::operator < (const BigInteger& b) const {
    if(s.size() != b.s.size()) return s.size() < b.s.size();
    for(int i = s.size() - 1; i >= 0; i--)
        if(s[i] != b.s[i])
            return s[i] < b.s[i];
    return false;//相等
}
bool BigInteger::operator > (const BigInteger& b) const {
    return b < *this;
}
bool BigInteger::operator <= (const BigInteger& b) const {
    return !(b < *this);
}
bool BigInteger::operator >= (const BigInteger& b) const {
    return !(*this < b);
}
bool BigInteger::operator != (const BigInteger& b) const {
    return b < *this || *this < b;
}
bool BigInteger::operator == (const BigInteger& b) const {
    return !(b < *this) && !(*this < b);
}

//四则运算
BigInteger BigInteger::operator + (const BigInteger& b) const {//加法运算
    BigInteger c;
    c.s.clear();
    for(int i = 0, g = 0; ; i++) {
        if(g == 0 && i >= s.size() && i >= b.s.size()) break;
        int x = g;
        if(i < s.size()) x += s[i];
        if(i < b.s.size()) x += b.s[i];
        c.s.push_back(x % BASE);
        g = x / BASE;
    }
    return c;
}
BigInteger BigInteger::operator - (const BigInteger& b) const {//减法运算
    BigInteger c, d, e;//d,e分别存储被减数和减数，c存储差值
    int sign = 1;//差值的符号
    c.s.clear();
    if(*this < b){
        d = b;
        e = *this;
        sign = -1;
    }
    else if(b < *this){
      d = *this;
        e = b;
        sign = 1;
    }
    else//相等，差为0
    {
        c = 0;
        return c;
    }
    for(int i = 0, g = 0; i < d.s.size() ; i++) {//g标记借位情况
        if(i < e.s.size()){
            if(d.s[i] < e.s[i]){
            int temp = d.s[i] + BASE - e.s[i] - g;
            if(temp != 0 || i != d.s.size() - 1)
                c.s.push_back(temp);
            g = 1;
            }
            else if(d.s[i] > e.s[i]){
            int temp = d.s[i] - e.s[i] - g;
            if(temp != 0 || i != d.s.size() - 1)
                c.s.push_back(temp);
            g = 0;
            }
            else{
                if(g == 0){
                if(i != d.s.size() - 1)
                    c.s.push_back(0);
                g = 0;
                }
                else{
                int temp = d.s[i] + BASE - e.s[i] - g;
                if(temp != 0 || i != d.s.size() - 1)
                    c.s.push_back(temp);
                g = 1;
                }
            }
        }
        else{//*************************fixed bug*************************
            int temp = d.s[i] - g;
            
            if(temp < 0){
                temp += BASE;
                g = 1;
            }
            else
                g = 0;
            
            if(temp != 0 || i != d.s.size() - 1)
                c.s.push_back(temp);
        }
    }
    c.s[c.s.size() - 1] = c.s[c.s.size() - 1] * sign;//符号处理（将符号保存在最高“段”的数值中）
    return c;
}

BigInteger BigInteger::operator * (const BigInteger& b) const{//乘法运算
    BigInteger c;//积
    BigInteger d;
    long long t = 0;
    for(int i = 0; i < b.s.size(); i++){
        for(int j = 0; j < s.size(); j++){
            d.s.clear();
            t = static_cast<long long>(b.s[i]) * s[j];
            for(int k = 0; k < i + j; k++)
                d.s.push_back(0);
            do{
                d.s.push_back(t % BASE);
                t /= BASE;
            }while(t > 0);
            c += d;
        }
    }
    return c;
}

BigInteger BigInteger::operator / (const BigInteger& b) const {
    BigInteger c, d;//c,d分别用于存储商和余数
    c.s.clear();
    d.s.clear();
    if(b == 0){//若除数为0，则报错且退出
        cout << "error: divizor can't be 0." << endl;
        exit(0);
    }
    else if(b == 1){
        c = *this;
        d = 0;
    }
    else if(*this == 0){//若被除数为0，则商和余数都为0
        c = 0;
        d = 0;
    }
    else if(*this != b){//若被除数和除数不相等，则
        if(*this < b){//要么被除数小于除数
            c = 0;
            d = *this;
        }
        else{//*this >= b，要么被除数大于等于除数
            BigInteger f;
            f = *this;
            vector<int> temp;//temp用于存储计算过程中得到的商值

            int flen = f.s.size() - b.s.size();
            for(int i = flen; i < f.s.size(); i++)
                d.s.push_back(f.s[i]);
            for(int i = f.s.size() - 1; i > flen - 1; i--)
                f.s.pop_back();
            if(d < b){//比b小的情况下，f有可能处于最右端吗？不可能，因为若f处于最右端，则f == d,但原本 d >= b，所以此时f >= b;故f不处于最右端。
                BigInteger g;
                g = d;
                d.s.clear();
                d.s.push_back(f.s[--flen]);
                for(int i = 0; i < g.s.size(); i++)
                d.s.push_back(g.s[i]);
                f.s.pop_back();
            }
            int times = flen + 1;
            while(times--){
                int n = 0;
                while(b <= d){
                    d -= b;
                    n++;
                }
                temp.push_back(n);

                if(flen > 0)
                if(d > 0){
                    BigInteger g;
                    g = d;
                    d.s.clear();
                    d.s.push_back(f.s[--flen]);
                    f.s.pop_back();
                    for(int j = 0; j < g.s.size(); j++)
                    d.s.push_back(g.s[j]);
                }
                else{
                    d.s.clear();
                    d.s.push_back(f.s[--flen]);
                    f.s.pop_back();
                }

              //cout << temp.back() << '\t' << d << endl;
            }
            for(int i = temp.size(); i > 0; i--)//得到商
                c.s.push_back(temp[i - 1]);
        }
    }
    else//若被除数和除数相等，则商为1，余数为0
    {
        c = 1;
        d = 0;
    }
    return c;
}

BigInteger BigInteger::fac()const {//阶乘运算
    BigInteger b, c;
    b = c = *this;
    while(b > 1){
        c *= b - 1;
        b = b - 1;
    }
    return c;
}

BigInteger BigInteger::operator % (const BigInteger& b)const {//取余运算
    BigInteger c, d;//c,d分别用于存储商和余数
    c.s.clear();
    d.s.clear();
    if(b == 0){//若除数为0，则报错且退出
        cout << "error: divizor can't be 0." << endl;
        exit(0);
    }
    else if(b == 1){
        c = *this;
        d = 0;
    }
    else if(*this == 0){//若被除数为0，则商和余数都为0
        c = 0;
        d = 0;
    }
    else if(*this != b){//若被除数和除数不相等，则
        if(*this < b){//要么被除数小于除数
            c = 0;
            d = *this;
        }
        else{//*this >= b，要么被除数大于等于除数
            BigInteger f;
            f = *this;
            vector<int> temp;//temp用于存储计算过程中得到的商值

            int flen = f.s.size() - b.s.size();
            for(int i = flen; i < f.s.size(); i++)
                d.s.push_back(f.s[i]);
            for(int i = f.s.size() - 1; i > flen - 1; i--)
                f.s.pop_back();
            if(d < b){//比b小的情况下，f有可能处于最右端吗？不可能，因为若f处于最右端，则f == d,但原本 d >= b，所以此时f >= b;故f不处于最右端。
                BigInteger g;
                g = d;
                d.s.clear();
                d.s.push_back(f.s[--flen]);
                for(int i = 0; i < g.s.size(); i++)
                d.s.push_back(g.s[i]);
                f.s.pop_back();
            }
            int times = flen + 1;
            while(times--){
                int n = 0;
                while(b <= d){
                    d -= b;
                    n++;
                }
                temp.push_back(n);

                if(flen > 0)
                if(d > 0){
                    BigInteger g;
                    g = d;
                    d.s.clear();
                    d.s.push_back(f.s[--flen]);
                    f.s.pop_back();
                    for(int j = 0; j < g.s.size(); j++)
                    d.s.push_back(g.s[j]);
                }
                else{
                    d.s.clear();
                    d.s.push_back(f.s[--flen]);
                    f.s.pop_back();
                }
            }
            for(int i = temp.size(); i > 0; i--)//得到商
                c.s.push_back(temp[i - 1]);
        }
    }
    else//若被除数和除数相等，则商为1，余数为0
    {
        c = 1;
        d = 0;
    }
    return d;
}

//输入输出
ostream& operator << (ostream &out, const BigInteger& x) {
    out << x.s.back();
    for(int i = x.s.size()-2; i >= 0; i--) {
    char buf[20];
    sprintf(buf, "%08d", x.s[i]);
    for(int j = 0; j < strlen(buf); j++) out << buf[j];
    }
    return out;
}
istream& operator >> (istream &in, BigInteger& x) {
    string s;
    if(!(in >> s)) return in;
    x = s;
    return in;
}