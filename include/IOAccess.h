#ifndef __IO_ACCESS_H__
#define __IO_ACCESS_H__

namespace iosim
	{

	struct IOAccess
		{
		IOAccess(unsigned int id, unsigned int sector, unsigned int requestTime);

		unsigned int getRequestTime() const;

		unsigned int getBeginTime() const;
		void setBeginTime(unsigned int beginTime);

		unsigned int getCompleteTime() const;
		void setCompleteTime(unsigned int completeTime);

		unsigned int getSector() const;

		unsigned int getId() const;

	private:
		unsigned int _requestTime, _beginTime, _completeTime, _sector, _id;
		};

	}
;

#endif //__IO_ACCESS_H__
