//
// Select.cpp for plazza in /home/burg_l//Work/tek2/cpp/plazza/plazza-2015-burg_l
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu Apr 12 14:02:00 2012 lois burg
// Last update Sat May 26 12:09:33 2012 lois burg
//

#include <iostream>
#include <cstring>
#include <cerrno>
#include "Select.hh"

Select::Select()
  : mRetValue(-1), mMaxFd(0)
{
  FD_ZERO(&mReadSet);
  FD_ZERO(&mWriteSet);
  FD_ZERO(&mExceptSet);
  memset(&mTimeOut, -1, sizeof(mTimeOut));
}

Select::~Select()
{
}

void	Select::addRead(int fd)
{
  FD_SET(fd, &mReadSet);
  if (fd > mMaxFd)
    mMaxFd = fd;
}

void	Select::addWrite(int fd)
{
  FD_SET(fd, &mWriteSet);
  if (fd > mMaxFd)
    mMaxFd = fd;
}

void	Select::addExcept(int fd)
{
  FD_SET(fd, &mExceptSet);
  if (fd > mMaxFd)
    mMaxFd = fd;
}

void	Select::setTimeOut(int sec, int usec)
{
  mTimeOut.tv_sec = sec;
  mTimeOut.tv_usec = usec;
}

void	Select::setNonBlock(void)
{
  memset(&mTimeOut, 0, sizeof(mTimeOut));
}

void	Select::reset(void)
{
  FD_ZERO(&mReadSet);
  FD_ZERO(&mWriteSet);
  FD_ZERO(&mExceptSet);
  memset(&mTimeOut, -1, sizeof(mTimeOut));
}

int	Select::watch(void)
{
  if (mTimeOut.tv_sec < 0 || mTimeOut.tv_usec < 0)
      mRetValue = select(mMaxFd + 1, &mReadSet, &mWriteSet, &mExceptSet, NULL);
  else
    mRetValue = select(mMaxFd + 1, &mReadSet, &mWriteSet, &mExceptSet, &mTimeOut);
  if (mRetValue < 0 && errno != EINTR)
    std::cerr << "select error: " << strerror(errno) << std::endl;
  return (mRetValue);
}

bool	Select::canRead(int fd) const
{
  if (FD_ISSET(fd, &mReadSet))
    return (true);
  return (false);
}

bool	Select::canWrite(int fd) const
{
  if (FD_ISSET(fd, &mWriteSet))
    return (true);
  return (false);
}

bool	Select::hasExcept(int fd) const
{
  if (FD_ISSET(fd, &mExceptSet))
    return (true);
  return (false);
}

bool	Select::hasTimedOut(void) const
{
  if (!mRetValue)
    return (true);
  return (false);
}
