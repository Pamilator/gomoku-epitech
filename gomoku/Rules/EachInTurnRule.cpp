#include "EachInTurnRule.h"

using namespace Rules;

EachInTurnRule::EachInTurnRule(void) : _enable(true)
{
}


EachInTurnRule::~EachInTurnRule(void)
{
}

void EachInTurnRule::enable()
{
	this->_enable = true;
}

void EachInTurnRule::disable()
{
	this->_enable = false;
}

bool EachInTurnRule::isEnable() const
{
	return this->_enable;
}

bool EachInTurnRule::execute(Goban & g, Goban::PION_TYPE pion, unsigned int, unsigned int)
{
	return g.Turns().size() == 0 || g.Turns().back().pion != pion;
}
