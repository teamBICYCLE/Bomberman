#include <unistd.h>
#include <iostream>
#include <GDL/Clock.hpp>
#include <GDL/Input.hpp>
#include "GameTest.hpp"

using namespace std;

int main()
{
  GameTest  t;

  t.run();
  return 0;
}
