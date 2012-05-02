#include "StatesManager.hh"
#include "IntroState.hh"

using namespace std;

int main(void)
{
  StatesManager   mg("Bomberman v0.1", new IntroState());

  mg.run();
  return 0;
}
