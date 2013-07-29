#include "gtest/gtest.h"

#include "Event.h"
#include "IOEvent.h"
#include "IORequest.h"
#include "IOBegin.h"
#include "IOComplete.h"

using des::Event;
using iosim::IOEvent;
using iosim::IORequest;
using iosim::IOBegin;
using iosim::IOComplete;
using iosim::IOAccess;

struct IOEventExecute_EventCallbackBehavior_tests: public ::testing::Test
	{

	IOEventExecute_EventCallbackBehavior_tests() :
			access1234(1, 2)
		{
		access1234.setBeginTime(3);
		access1234.setCompleteTime(4);
		}

	void SetUp()
		{
		// back up functions
		dispatchFollowUpEvent = IOEvent::dispatchFollowUpEvent;
		enqueueIORequest = IOEvent::enqueueIORequest;
		getNextSectorAccess = IOEvent::getNextSectorAccess;
		isDiskIdle = IOEvent::isDiskIdle;
		accessSectorOnDisk = IOEvent::accessSectorOnDisk;
		isIORequestPending = IOEvent::isIORequestPending;
		setDiskToIdle = IOEvent::setDiskToIdle;

		// bind checker functions
		IOEvent::dispatchFollowUpEvent = followUpCheck;
		IOEvent::enqueueIORequest = enqueueCheck;
		IOEvent::getNextSectorAccess = nextSectorCheck;
		IOEvent::isDiskIdle = isIdleCheck;
		IOEvent::accessSectorOnDisk = accessSectorCheck;
		IOEvent::isIORequestPending = pendingCheck;
		IOEvent::setDiskToIdle = setIdleCheck;

		// other
		calledBits = 0;
		_nextSector = &access1234;
		}

	void TearDown()
		{
		IOEvent::dispatchFollowUpEvent = dispatchFollowUpEvent;
		IOEvent::enqueueIORequest = enqueueIORequest;
		IOEvent::getNextSectorAccess = getNextSectorAccess;
		IOEvent::isDiskIdle = isDiskIdle;
		IOEvent::accessSectorOnDisk = accessSectorOnDisk;
		IOEvent::isIORequestPending = isIORequestPending;
		IOEvent::setDiskToIdle = setDiskToIdle;

		_nextSector = NULL;
		}

	std::function<void(des::Event*)> dispatchFollowUpEvent;
	std::function<void(IOAccess*)> enqueueIORequest;
	std::function<IOAccess *(void)> getNextSectorAccess;
	std::function<bool(void)> isDiskIdle;
	std::function<unsigned int(unsigned int)> accessSectorOnDisk;
	std::function<bool(void)> isIORequestPending;
	std::function<void(void)> setDiskToIdle;

	enum CallT
		{
		FOLLOW_UP,
		ENQUEUE_REQ,
		NEXT_SECTOR,
		IS_IDLE,
		ACCESS_SECTOR,
		REQ_PENDING,
		SET_IDLE
		};

	static unsigned long calledBits;

	static void call(CallT c)
		{
		calledBits |= (1 << c);
		}

	static IOAccess * _nextSector;
	static unsigned int _accessTime;
	static bool _isIdle, _isPending;

	static void followUpCheck(des::Event*)
		{
		call(FOLLOW_UP);
		}
	static void enqueueCheck(IOAccess * s)
		{
		call(ENQUEUE_REQ);
		}
	static IOAccess * nextSectorCheck()
		{
		call(NEXT_SECTOR);
		return _nextSector;
		}
	static bool isIdleCheck()
		{
		call(IS_IDLE);
		return _isIdle;
		}
	static unsigned int accessSectorCheck(unsigned int s)
		{
		call(ACCESS_SECTOR);
		return _accessTime;
		}
	static bool pendingCheck()
		{
		call(REQ_PENDING);
		return _isPending;
		}
	static void setIdleCheck()
		{
		call(SET_IDLE);
		}

	IOAccess access1234;

	template<typename EventType>
	bool executeAndCheck(CallT c)
		{
		EventType event(&access1234);
		des::Event * e = &event;
		e->execute();
		return (calledBits & (1 << c)) != 0;
		}

	};

unsigned long IOEventExecute_EventCallbackBehavior_tests::calledBits = 0;
bool IOEventExecute_EventCallbackBehavior_tests::_isIdle = true;
bool IOEventExecute_EventCallbackBehavior_tests::_isPending = false;
unsigned int IOEventExecute_EventCallbackBehavior_tests::_accessTime = 1;
IOAccess * IOEventExecute_EventCallbackBehavior_tests::_nextSector = NULL;

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskIdle_CalledDiskIdle)
	{
	_isIdle = true;
	ASSERT_TRUE(executeAndCheck<IORequest>(IS_IDLE));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskIdle_CalledEnqueueReq)
	{
	_isIdle = true;
	ASSERT_TRUE(executeAndCheck<IORequest>(ENQUEUE_REQ));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskIdle_CalledNextSector)
	{
	_isIdle = true;
	ASSERT_TRUE(executeAndCheck<IORequest>(NEXT_SECTOR));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskIdle_CalledFollowUp)
	{
	_isIdle = true;
	ASSERT_TRUE(executeAndCheck<IORequest>(FOLLOW_UP));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskBusy_CalledDiskIdle)
	{
	_isIdle = false;
	ASSERT_TRUE(executeAndCheck<IORequest>(IS_IDLE));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskBusy_CalledEnqueueReq)
	{
	_isIdle = false;
	ASSERT_TRUE(executeAndCheck<IORequest>(ENQUEUE_REQ));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskBusy_NoCallNextSector)
	{
	_isIdle = false;
	ASSERT_FALSE(executeAndCheck<IORequest>(NEXT_SECTOR));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Request_DiskBusy_NoCallFollowUP)
	{
	_isIdle = false;
	ASSERT_FALSE(executeAndCheck<IORequest>(FOLLOW_UP));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Begin_CalledFollowUp)
	{
	ASSERT_TRUE(executeAndCheck<IOBegin>(FOLLOW_UP));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Begin_CalledAccessSector)
	{
	ASSERT_TRUE(executeAndCheck<IOBegin>(ACCESS_SECTOR));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_ReqPending_CalledReqPending)
	{
	_isPending = true;
	ASSERT_TRUE(executeAndCheck<IOComplete>(REQ_PENDING));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_ReqPending_CalledSetIdle)
	{
	_isPending = true;
	ASSERT_TRUE(executeAndCheck<IOComplete>(SET_IDLE));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_ReqPending_CalledNextSector)
	{
	_isPending = true;
	ASSERT_TRUE(executeAndCheck<IOComplete>(NEXT_SECTOR));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_ReqPending_CalledFollowUp)
	{
	_isPending = true;
	ASSERT_TRUE(executeAndCheck<IOComplete>(FOLLOW_UP));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_NoReqPending_CalledReqPending)
	{
	_isPending = false;
	ASSERT_TRUE(executeAndCheck<IOComplete>(REQ_PENDING));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_NoReqPending_CalledSetIdle)
	{
	_isPending = false;
	ASSERT_TRUE(executeAndCheck<IOComplete>(SET_IDLE));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_NoReqPending_NoCallNextSector)
	{
	_isPending = false;
	ASSERT_FALSE(executeAndCheck<IOComplete>(NEXT_SECTOR));
	}

TEST_F(IOEventExecute_EventCallbackBehavior_tests, Complete_NoReqPending_NoCallFollowUp)
	{
	_isPending = false;
	ASSERT_FALSE(executeAndCheck<IOComplete>(FOLLOW_UP));
	}
