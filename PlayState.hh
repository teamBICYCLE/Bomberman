//
// PlayState.hh for bomberman in /home/burg_l//Work/tek2/cpp/Bomberman
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Wed May  2 17:54:59 2012 lois burg
// Last update Wed May  2 18:04:32 2012 lois burg
//

#ifndef		__PLAYSTATE_HH__
# define	__PLAYSTATE_HH__

# include	"AObject.hh"
# include	"AGameState.hh"

class	PlayState : public AGameState
{
public:
  virtual void init();
  virtual void cleanUp();

  virtual void update(StatesManager *mngr);
  virtual void draw(StatesManager *mngr);
  virtual void pause();
  virtual void resume();

private:
  std::vector<AObject*>	objs_;
};

#endif /* !__PLAYSTATE_HH__*/
