#include <memory>
class foo
{
  public:
    foo();
    ~foo();
    foo(foo&&);
    foo& operator=(foo&&);
  private:
    class impl;
    std::unique_ptr<impl> pimpl;
};