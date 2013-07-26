#include "gtest/gtest.h"

#include <vector>
#include <iostream>
#include <set>

#include "event.h"
#include "event_queue.h"

using namespace des;

class EventQueueOrderTests : public ::testing::Test {
public: 

  struct PriorityEvent : public Event
  {
    PriorityEvent() : Event(0), _priority(0) { }
    PriorityEvent(unsigned int time, int priority) : Event(time), _priority(priority) { }

    virtual void execute() { }
    virtual int getPriority() const { return _priority; }

  private:
    int _priority;
  };

  EventQueueOrderTests( ) {
    for (int t = 0; t < 3; ++t)
      for (int p = 0; p < 3; ++p)
      {
        events[t][p] = PriorityEvent(t, p);
      }
  }

  void SetUp( ) { 
    // code here will execute just before the test ensues 
  }

  void TearDown( ) {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~EventQueueOrderTests( )  { 
    // cleanup any pending stuff, but no exceptions allowed
  }

  EventQueue queue;
  PriorityEvent events[3][3];
};

TEST_F(EventQueueOrderTests, DifTimeDifPrio_OrderByTime)
{
  queue.pushEvent( &events[0][0] );                 // Q: 00
  queue.pushEvent( &events[2][2] );                 // Q: 00 22
  queue.pushEvent( &events[1][1] );                 // Q: 00 11 22
  ASSERT_EQ( &events[0][0], queue.popEvent() );
  ASSERT_EQ( &events[1][1], queue.popEvent() );
  ASSERT_EQ( &events[2][2], queue.popEvent() );

  queue.pushEvent( &events[0][2] );                 // Q: 02
  queue.pushEvent( &events[2][0] );                 // Q: 02 20
  queue.pushEvent( &events[1][1] );                 // Q: 02 11 20
  ASSERT_EQ( &events[0][2], queue.popEvent() );
  ASSERT_EQ( &events[1][1], queue.popEvent() );
  ASSERT_EQ( &events[2][0], queue.popEvent() );
}

TEST_F(EventQueueOrderTests, DifTimeSamePrio_OrderByTime)
{
  queue.pushEvent( &events[0][0] );
  queue.pushEvent( &events[2][0] );
  queue.pushEvent( &events[1][0] );
  ASSERT_EQ( &events[0][0], queue.popEvent() );
  ASSERT_EQ( &events[1][0], queue.popEvent() );
  ASSERT_EQ( &events[2][0], queue.popEvent() );
}

TEST_F(EventQueueOrderTests, SameTimeDifPrio_OrderByPrio)
{
  queue.pushEvent( &events[0][0] );  // 00
  queue.pushEvent( &events[0][2] );  // 00 02
  queue.pushEvent( &events[0][1] );  // 00 01 02
  ASSERT_EQ( &events[0][0], queue.popEvent() );
  ASSERT_EQ( &events[0][1], queue.popEvent() );
  ASSERT_EQ( &events[0][2], queue.popEvent() );
}

TEST_F(EventQueueOrderTests, SameTimeSamePrio_OrderByArrival)
{
  PriorityEvent e1(1, 0);  // out of order, to ensure that
  PriorityEvent e3(1, 0);  // address does not play a role
  PriorityEvent e2(1, 0);

  queue.pushEvent( &events[0][0] );
  queue.pushEvent( &events[2][0] );
  queue.pushEvent( &e1 );
  queue.pushEvent( &e2 );
  queue.pushEvent( &e3 );
  ASSERT_EQ( &events[0][0], queue.popEvent() );
  ASSERT_EQ( &e1, queue.popEvent() );
  ASSERT_EQ( &e2, queue.popEvent() );
  ASSERT_EQ( &e3, queue.popEvent() );
  ASSERT_EQ( &events[2][0], queue.popEvent() );
}
