#ifndef _GOBAN_H_
# define _GOBAN_H_

#include <stdio.h>

#include <functional>

template<int direction> struct Moves { };
template<> struct Moves<0> { enum Values {x = 0, y =-1 };};
template<> struct Moves<1> { enum Values {x = 1, y =-1 };};
template<> struct Moves<2> { enum Values {x = 1, y = 0 };};
template<> struct Moves<3> { enum Values {x = 1, y = 1 };};
template<> struct Moves<4> { enum Values {x = 0, y = 1 };};
template<> struct Moves<5> { enum Values {x =-1, y = 1 };};
template<> struct Moves<6> { enum Values {x =-1, y = 0 };};
template<> struct Moves<7> { enum Values {x =-1, y =-1 };};

template<int direction, int dist>
struct Padding
{
	enum Values
	{
		x = Moves<direction>::x * dist,
		y = Moves<direction>::y * dist
	};
};


class Goban
{
public:
    typedef long long int Case;
    typedef std::pair<unsigned int, unsigned int> Move;
    static const long long int PIONMASK = 0x3;
    static const long long int PATTERNMASK = 0xF;
    static const unsigned int HEADERSIZE = 2;
    static const unsigned int PATTERNSIZE = 4;
    static const unsigned int COLORSIZE = 2;
    static const unsigned int SAFESIZE = 1;
    static const unsigned int CONTENTSIZE = 4;

    enum PION_TYPE
    {
        EMPTY,
        BLACK = 0x1,
        RED = 0x2
    };

    Goban();
    Goban(Goban const &);
    ~Goban(void);

    void Putin(PION_TYPE, unsigned int, unsigned int);
    void subIn(unsigned int, unsigned int);

   inline unsigned int Goban::getWidth() const
	{
		return this->_width;
	}

	inline unsigned int Goban::getHeight() const
	{
		return this->_height;
	}

	inline bool Goban::InBound(unsigned int x, unsigned int y) const
	{
		return x < this->_width && y < this->_height;
	}

	Case * operator[](unsigned int);

protected:

private:
    Case _map[19][19];
    int update_serie(unsigned int i, unsigned int j, int decal_x, int decal_y, int dir, int depth);
    void update_pattern(unsigned int, unsigned int, int);
    unsigned int _width;
    unsigned int _height;
};

template<int nbBits>
struct PatternMask
{
    static const unsigned long long int value = (1 << (nbBits - 1)) | PatternMask<nbBits - 1>::value;
};
template<>
struct PatternMask<0>
{
    static const unsigned long long int value = 0;
};

template<bool safe, int size, unsigned long long int content>
struct Pattern
{
    static const unsigned long long int value = (safe | (content << 1)) << Goban::COLORSIZE;
    static const unsigned long long int mask = PatternMask<size + safe + Goban::COLORSIZE>::value;
};

#endif
