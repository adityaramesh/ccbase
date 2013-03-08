/*
** File Name:	round.hpp
** Author:	Aditya Ramesh
** Date:	03/07/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZE16625FA_AB14_4BEC_9D26_ECE7DFC3D437
#define ZE16625FA_AB14_4BEC_9D26_ECE7DFC3D437

#include <iomanip>
#include <ccbase/unsync.hpp>

namespace cc
{

/*
** Modifies steam to use scientific notation, using provided precision.
*/
void set_scientific(std::ostream& os, const int n = 6)
{
	os << std::scientific << std::setprecision(n);
}

/*
** Modifies stream to use fixed notation, using provided precision.
*/
void set_fixed(std::ostream& os, const int n = 6)
{
	os << std::fixed << std::setprecision(n);
}

}

#endif
