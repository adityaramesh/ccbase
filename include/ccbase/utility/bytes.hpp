/*
** File Name: bytes.hpp
** Author:    Aditya Ramesh
** Date:      07/09/2014
** Contact:   _@adityaramesh.com
*/

#ifndef Z66BE627C_AD04_47FD_9360_9A51E7280DC8
#define Z66BE627C_AD04_47FD_9360_9A51E7280DC8

#include <cstdint>

constexpr uint64_t
operator ""_KB(unsigned long long int x)
{ return x << 10; }

constexpr uint64_t
operator ""_MB(unsigned long long int x)
{ return x << 20; }

constexpr uint64_t
operator ""_GB(unsigned long long int x)
{ return x << 30; }

constexpr uint64_t
operator ""_TB(unsigned long long int x)
{ return x << 40; }

#endif
