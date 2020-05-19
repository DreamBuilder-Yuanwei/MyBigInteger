#include<set>
#include<map>
#include "BigInteger.h"

set<BigInteger> s;
map<BigInteger, int> m;
int main(){
    BigInteger a, b, c, d, e, f, g, h, k = 300;
    a = 12345678;
    b = "87654321234567890";
    c = a + b;
    d = b - a;
    e = c * d;
    f = c / d;
    g = e % f;
    h = k.fac();
    cout << a << endl << b << endl << c << endl << d << endl << e << endl << f << endl << g << endl << h << endl;
    return 0;
}