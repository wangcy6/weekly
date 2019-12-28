#include <iostream>
using namespace std;

class Shape {
 public:
  virtual void draw () {}
};

class Circle : public Shape {
 int radius;
 public:
  Circle () { radius = 1; }
  void draw () { cout << "drawing a circle...\n"; }
};

class Square : public Shape {
 int height;
 public:
  Square () { height = 2; }
  void draw () { cout << "drawing a square...\n"; }
};

void drawShape (class Shape &p)
{
  p.draw ();
}

int main (void)
{
  Circle a;
  Square b;
  drawShape (a);
  drawShape (b);
  return 0;
}