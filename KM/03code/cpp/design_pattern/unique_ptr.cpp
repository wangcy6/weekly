
#include <iostream>
#include <memory>

class state_deleter {  // a deleter class with state
  int count_;
public:
  state_deleter() : count_(0) {}
  template <class T>
  void operator()(T* p) {
    std::cout << "[deleted #" << ++count_ << "]\n";
    delete p;
  }
};

int main () {
//   state_deleter del;

  std::unique_ptr<int> p;   // uses default deleter

  // alpha and beta use independent copies of the deleter:
  std::unique_ptr<int,state_deleter> alpha (new int);
  std::unique_ptr<int,state_deleter> beta (new int,alpha.get_deleter());

//   // gamma and delta share the deleter "del" (deleter type is a reference!):
//   std::unique_ptr<int,state_deleter&> gamma (new int,del);
//   std::unique_ptr<int,state_deleter&> delta (new int,gamma.get_deleter());

//   std::cout << "resetting alpha..."; alpha.reset(new int);
//   std::cout << "resetting beta..."; beta.reset(new int);
//   std::cout << "resetting gamma..."; gamma.reset(new int);
//   std::cout << "resetting delta..."; delta.reset(new int);

//   std::cout << "calling gamma/delta deleter...";
//   gamma.get_deleter()(new int);

//   alpha.get_deleter() = state_deleter();  // a brand new deleter for alpha

//   // additional deletions when unique_ptr objects reach out of scope
//   // (in inverse order of declaration)

  return 0;
}