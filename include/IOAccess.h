#ifndef __IO_ACCESS_H__
#define __IO_ACCESS_H__

namespace iosim
	{

	struct IOAccess
		{
		IOAccess(unsigned int requestTime, unsigned int sector);

		unsigned int getRequestTime() const;

		unsigned int getBeginTime() const;
		void setBeginTime(unsigned int beginTime);

		unsigned int getCompleteTime() const;
		void setCompleteTime(unsigned int completeTime);

		unsigned int getSector() const;

	private:
		unsigned int _requestTime, _beginTime, _completeTime, _sector;
		};

	}
;

#endif //__IO_ACCESS_H__
