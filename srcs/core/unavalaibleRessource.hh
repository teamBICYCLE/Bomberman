/**************************************************************************
** unavalaibleRessource.hh: Created on 3 Jun 2012 by duplom_t
** for class : unavalaibleRessource
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#ifndef UNAVALAIBLERESSOURCE_HH
#define UNAVALAIBLERESSOURCE_HH

#include <string>
#include <exception>

class unavalaibleRessource : public std::exception
{
public:
  unavalaibleRessource(const std::string & msg);
  virtual ~unavalaibleRessource() throw();
  virtual const char *what() const throw();

private:
  std::string   what_;
};

#endif // UNAVALAIBLERESSOURCE_HH
