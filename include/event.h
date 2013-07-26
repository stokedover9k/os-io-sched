#ifndef __EVENT_H__
#define __EVENT_H__ 

namespace des
{

  struct Event
  {
    Event(unsigned int time);
    virtual ~Event();

    virtual void execute() = 0;

    unsigned int getTime() const;
    virtual int getPriority() const;

  private:
    unsigned int _time;
  };

};

#endif //__EVENT_H__
