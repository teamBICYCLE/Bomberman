//
// Select.hpp for plazza in /home/burg_l//Work/tek2/cpp/plazza/plazza-2015-burg_l
//
// Made by lois burg
// Login   <burg_l@epitech.net>
//
// Started on  Thu Apr 12 13:51:05 2012 lois burg
// Last update Sun Apr 15 12:47:12 2012 lois burg
//

#ifndef		__SELECT_HPP__
# define	__SELECT_HPP__

# include	<sys/select.h>

class	Select
{
public:
  Select();
  ~Select();

public:
  void		addRead(int fd);
  void		addWrite(int fd);
  void		addExcept(int fd);
  void		setTimeOut(int sec, int microsec);
  void		reset(void);
  void		setNonBlock(void);
  int		watch(void);

public:
  bool		canRead(int fd) const;
  bool		canWrite(int fd) const;
  bool		hasExcept(int fd) const;
  bool		hasTimedOut(void) const;

private:
  Select(const Select& other);
  Select&	operator=(const Select& other);

private:
  int			mRetValue;
  int			mMaxFd;
  fd_set		mReadSet;
  fd_set		mWriteSet;
  fd_set		mExceptSet;
  struct timeval	mTimeOut;
};

#endif /* !__SELECT_HPP__*/
