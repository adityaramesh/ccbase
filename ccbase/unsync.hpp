/*
** File Name:	unsync.hpp
** Author:	Aditya Ramesh
** Date:	03/07/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z73BD8CFF_B71B_4F5E_AC42_4465D065D60C
#define Z73BD8CFF_B71B_4F5E_AC42_4465D065D60C

#include <iostream>

namespace cc
{

static bool initialize()
{
	std::ios_base::sync_with_stdio(false);
	return true;
}

static bool success = initialize();

}

#endif
