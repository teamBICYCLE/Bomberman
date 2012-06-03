/**************************************************************************
** unavalaibleRessource.cpp: Created on 3 Jun 2012 by duplom_t
** for class : unavalaibleRessource
** "THE BEER-WARE LICENSE" (Revision 42):
**  <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return duplom_t
**************************************************************************/

#include "unavalaibleRessource.hh"

unavalaibleRessource::unavalaibleRessource(const std::string &msg)
  : what_(msg)
{
}

unavalaibleRessource::~unavalaibleRessource() throw()
{
}

const char *unavalaibleRessource::what() const throw()
{
  return ("Ressource unavalaible: " + what_).c_str();
}