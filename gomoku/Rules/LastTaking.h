#ifndef LASTTAKING_H_
# define LASTTACKING_H_

#include "IRule.h"

namespace Rules
{
	class LastTaking : public IRule
	{
	public:
		LastTaking(void);
		virtual ~LastTaking(void);

		virtual void enable();
		virtual void disable();
		virtual bool isEnable() const;
		virtual bool execute(Goban &, Goban::PION_TYPE, unsigned int, unsigned int);

	private:
		bool _enable;
	};
}

#endif