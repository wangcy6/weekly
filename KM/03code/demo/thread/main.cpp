#include "CThread.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
class CPrintB : public CThread {
public:
  virtual int Print() {
    for (int i = 0; i < 10; ++i) {
      sleep(1);
      printf("bbbbbbbbb-----\n");
    }
    return 0;
  }
};

int main() {
  // CThread obj;
  // obj.start();
  // sleep(20);

  CPrintB obj2;
  obj2.start();
  sleep(5); // bbbbbbbbb-----
  //??sleep aaaaaaaaaa
  return 0;
}