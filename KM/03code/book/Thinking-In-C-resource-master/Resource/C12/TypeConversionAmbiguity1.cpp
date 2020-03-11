#include <iostream>
#define BYTES 8
using namespace std ;

class huge {
private:
    unsigned char data[BYTES];
public:
    void setval(unsigned int);
    void setval(const char *);  
};

void huge::setval(unsigned int t) {
    for(int i = 0; i< BYTES ; i++) {
        data[i] = t;
        t = t >> 1;
    }
}

void huge::setval(const char *s) {
    for(int i = 0; i< BYTES ; i++)
        data[i] = s[i];
}

int main() {
    huge p;
    p.setval(0);
	//setval(static_cast<const char *>(0));
	//p.setval(static_cast<unsigned int>(0));
	//https://stackoverflow.com/questions/4672152/call-of-overloaded-function-is-ambiguous
	//http://www.cplusplus.com/forum/beginner/3165/
    return 0;
}