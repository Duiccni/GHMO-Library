#pragma once

#include <ostream>
#include <algorithm>

struct d3point
{
	int x, y, z;
};

struct d3fpoint
{
	float x, y, z;
};

inline d3point operator -(d3point p) { return { -p.x, -p.y, -p.z }; }
inline d3fpoint operator -(d3fpoint p) { return { -p.x, -p.y, -p.z }; }

inline void swap_d3point_if(d3point& s, d3point& b)
{
	if (s.x > b.x) std::swap(s.x, b.x);
	if (s.y > b.y) std::swap(s.y, b.y);
	if (s.z > b.z) std::swap(s.z, b.z);
}

inline void operator |(d3point& s, d3point& b) { swap_d3point_if(s, b); }

inline void clamp_d3point(d3point& p, d3point s, d3point b)
{
	p.x = std::clamp(p.x, s.x, b.x);
	p.y = std::clamp(p.y, s.y, b.y);
}

inline std::ostream& operator <<(std::ostream& os, d3point p)
{
	os << '(' << p.x << ',' << ' ' << p.y << ',' << ' ' << p.z << ')';
	return os;
}

#define OPA3(S) inline d3point operator S(d3point a, d3point b) { return { a.x S b.x, a.y S b.y, a.z S b.z }; }
#define OIA3(S) inline d3point operator S(d3point a, int b) { return { a.x S b, a.y S b, a.z S b }; }
#define OB3(S, J) inline bool operator S(d3point a, d3point b) { return  a.x S b.x J a.y S b.y J a.z S b.z; }
#define OPV3(S) inline void operator S(d3point& a, d3point b) { a.x S b.x; a.y S b.y;; a.z S b.z; }
#define OIV3(S) inline void operator S(d3point& a, int b) { a.x S b; a.y S b; a.z S b; }

OPA3(+)
OPA3(-)
OPA3(*)
OPA3(/)
OPA3(%)

OIA3(+)
OIA3(-)
OIA3(*)
OIA3(/)
OIA3(%)
OIA3(&)
OIA3(|)
OIA3(<<)
OIA3(>>)

OB3(==, &&)
OB3(!=, ||)
OB3(<, &&)
OB3(>, &&)
OB3(<=, &&)
OB3(>=, &&)

OPV3(+=)
OPV3(-=)

OIV3(+=)
OIV3(-=)
OIV3(<<=)
OIV3(>>=)
