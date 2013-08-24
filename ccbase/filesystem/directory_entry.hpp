/*
** File Name:	directory_entry.hpp
** Author:	Aditya Ramesh
** Date:	08/23/2013
** Contact:	_@adityaramesh.com
*/

#ifndef ZDDEA7CE4_14FD_40C7_AA27_9BBF59D67383
#define ZDDEA7CE4_14FD_40C7_AA27_9BBF59D67383

#include <cstdint>
#include <sys/types.h>
#include <sys/dirent.h>

namespace cc
{

class directory_entry
{
private:
	const uint8_t* name;
	const uint8_t len;

public:
	explicit directory_entry()
};

}

#endif
