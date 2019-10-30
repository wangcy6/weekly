
#include "foo.h"

// foo.cpp - implementation file
class foo::impl
{
  public:
    void do_internal_work()
    {
      internal_data = 5;
    }
  private:
    int internal_data = 0;
};
foo::foo()
  : pimpl{std::make_unique<impl>()}
{
  pimpl->do_internal_work();
}
foo::~foo() = default;
foo::foo(foo&&) = default;
foo& foo::operator=(foo&&) = default;