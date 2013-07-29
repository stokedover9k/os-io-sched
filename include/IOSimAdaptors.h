#ifndef __IO_SIM_ADAPTORS_H__
#define __IO_SIM_ADAPTORS_H__

namespace des
	{
	struct EventQueue;
	struct Event;
	}

namespace iosim
	{

	struct IOAccess;
	struct IOStrategy;
	struct Disk;

	struct EventDispatcher
		{

		EventDispatcher(des::EventQueue* eventQueue);

		void operator ()(des::Event* event);

	private:
		des::EventQueue * _eventQueue;
		};

	struct EnqueueSectorRequest
		{

		EnqueueSectorRequest(IOStrategy* strategy);

		void operator ()(IOAccess* a);

	private:
		IOStrategy * _strategy;
		};

	struct NextSectorRequest
		{

		NextSectorRequest(IOStrategy* strategy);

		IOAccess* operator ()();

	private:
		IOStrategy * _strategy;
		};

	struct DiskIdle
		{
		DiskIdle(Disk* disk);

		bool operator ()();

	private:
		Disk * _disk;
		};

	struct DiskSetIdle
		{
		DiskSetIdle(Disk* disk);

		void operator ()();

	private:
		Disk * _disk;
		};

	struct AccessSector
		{
		AccessSector(Disk* disk);

		unsigned int operator ()(unsigned int sector);

	private:
		Disk * _disk;
		};

	struct RequestPending
		{
		RequestPending(IOStrategy* strategy);

		bool operator ()();

	private:
		IOStrategy * _strategy;
		};

	}
;

#endif //__IO_SIM_ADAPTORS_H__
