#ifndef __EVENT_H__
#define __EVENT_H__ 

namespace des
{

  struct Event
  {
    virtual ~Event();

    virtual void execute() = 0;
		virtual unsigned int getTime() const = 0;
		virtual int getPriority() const = 0;
  };

};

#endif //__EVENT_H__
