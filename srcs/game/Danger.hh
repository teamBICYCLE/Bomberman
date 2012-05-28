//
// Danger.hh for  in /home/carpen_t/projets/c++/Bomberman
//
// Made by thibault carpentier
// Login   <carpen_t@epitech.net>
//
// Started on  Sat May 26 15:55:31 2012 thibault carpentier
// Last update Mon May 28 14:27:12 2012 Jonathan Machado
//

#ifndef _DANGER_H_
# define _DANGER_H_

# define DANGER_MAX 10
# define DANGER_MIN -10

# define DANGER_BOMB (DANGER_MAX - (getTimeOut() * 3))
# define DANGER_BLOCK 0
# define DANGER_MONSTER 0
# define DANGER_PLAYER DANGER_MIN
# define DANGER_POWERUP (DANGER_MIN / 2)
# define DANGER_MINE DANGER_MAX
# define DANGER_EXPLOSION DANGER_MAX
# define DANGER_FIREBLOCK (DANGER_MAX - (getTimeout() *3))

#endif /*!_DANGER_H_*/
