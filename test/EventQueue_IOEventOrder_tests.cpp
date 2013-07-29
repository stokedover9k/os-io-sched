#include "gtest/gtest.h"

#include <list>
#include <sstream>

#include "Event.h"
#include "EventQueue.h"

#include "IOEvent.h"
#include "IORequest.h"
#include "IOBegin.h"
#include "IOComplete.h"

using des::EventQueue;
using des::Event;
using iosim::IORequest;
using iosim::IOBegin;
using iosim::IOComplete;
using iosim::IOAccess;

struct EventQueue_IOEventOrder_tests: public ::testing::Test
	{

	EventQueue_IOEventOrder_tests() :
			access0(makeAccessWithEqualTimes(0)), access1(
					makeAccessWithEqualTimes(1)), access2(makeAccessWithEqualTimes(2))
		{
		}

	bool orderedAs(Event * in1, Event * in2, Event * out1, Event * out2) const
		{
		EventQueue q;
		q.pushEvent(in1);
		q.pushEvent(in2);
		return q.popEvent() == out1 && q.popEvent() == out2;
		}

	template<typename InputIterator>
	bool orderedAs(InputIterator inBegin, InputIterator inEnd,
			InputIterator outBegin, InputIterator outEnd) const
		{
		EventQueue q;

		for (; inBegin != inEnd; inBegin++)
			q.pushEvent(*inBegin);

		for (; outBegin != outEnd; outBegin++)
			if (q.size() == 0)
				return false;
			else if (q.popEvent() != *outBegin)
				return false;

		return q.size() == 0;
		}

	template<typename InputIterator>
	bool orderedAs(InputIterator inBegin, InputIterator inEnd,
			char const * expectedOutput)
		{
		EventQueue q;

		for (; inBegin != inEnd; inBegin++)
			q.pushEvent(*inBegin);

		std::stringstream ss;
		while (q.size())
			{
			Event * e = q.popEvent();
			ss << e->getTime() << '-' << e->getPriority() << ' ';
			}

		return ss.str() == expectedOutput;
		}

	static IOAccess makeAccessWithEqualTimes(unsigned int time)
		{
		IOAccess a(time, 0);
		a.setBeginTime(time);
		a.setCompleteTime(time);
		return a;
		}

	// events are in priority order
	static std::list<Event*> threeEventsWithAccess(IOAccess * a)
		{
		std::list<Event*> l;
		l.push_back(new IORequest(a));
		l.push_back(new IOComplete(a));
		l.push_back(new IOBegin(a));
		return l;
		}

	static void deleteEvents(std::list<Event*> & l)
		{
		for (auto i = l.begin(); i != l.end(); ++i)
			delete *i;
		}

	IOAccess access0, access1, access2;

	};

TEST_F(EventQueue_IOEventOrder_tests, SameTimeOrder_RequestBeforeComplete)
	{
	IORequest r(&access0);
	IOComplete c(&access0);

	ASSERT_TRUE(orderedAs(&r, &c, &r, &c));
	ASSERT_TRUE(orderedAs(&c, &r, &r, &c));
	}

TEST_F(EventQueue_IOEventOrder_tests, SameTimeOrder_CompleteBeforeBegin)
	{
	IOComplete c(&access0);
	IOBegin b(&access0);

	ASSERT_TRUE(orderedAs(&c, &b, &c, &b));
	ASSERT_TRUE(orderedAs(&b, &c, &c, &b));
	}

TEST_F(EventQueue_IOEventOrder_tests, DifTime_AddEarliestToHeadOfQ)
	{
	std::list<Event*> events = threeEventsWithAccess(&access1);

	events.push_back(NULL);

	events.back() = new IORequest(&access0);
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "0-1 1-1 1-2 1-3 "));
	delete events.back();

	events.back() = new IOComplete(&access0);
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "0-2 1-1 1-2 1-3 "));
	delete events.back();

	events.back() = new IOBegin(&access0);
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "0-3 1-1 1-2 1-3 "));

	deleteEvents(events);
	}

TEST_F(EventQueue_IOEventOrder_tests, DifTime_AddLatestToTailOfQ)
	{
	std::list<Event*> events = threeEventsWithAccess(&access1);

	events.push_back(NULL);

	events.back() = new IORequest(&access2);
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "1-1 1-2 1-3 2-1 "));
	delete events.back();

	events.back() = new IOComplete(&access2);
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "1-1 1-2 1-3 2-2 "));
	delete events.back();

	events.back() = new IOBegin(&access2);
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "1-1 1-2 1-3 2-3 "));

	deleteEvents(events);
	}

TEST_F(EventQueue_IOEventOrder_tests, DifTime_AddMidTimeToMiddleOfQ)
	{
	std::list<Event*> events = threeEventsWithAccess(&access0);
	std::list<Event*> events2 = threeEventsWithAccess(&access2);
	events.insert(events.end(), events2.begin(), events2.end());
	events.push_back(NULL);

	events.back() = new IORequest(&access1);            //           ...
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "0-1 0-2 0-3 1-1 2-1 2-2 2-3 "));
	delete events.back();

	events.back() = new IOComplete(&access1);           //           ...
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "0-1 0-2 0-3 1-2 2-1 2-2 2-3 "));
	delete events.back();

	events.back() = new IOBegin(&access1);              //           ...
	ASSERT_TRUE(orderedAs(events.begin(), events.end(), "0-1 0-2 0-3 1-3 2-1 2-2 2-3 "));

	deleteEvents(events);
	}
