/*
** File Name:	format_test.cpp
** Author:	Aditya Ramesh
** Date:	12/05/2012
** Contact:	_@adityaramesh.com
*/

#include <cstdlib>
#include <format.hpp>

int main()
{
	sf::println("These are three arguments: {0}, {1}, and {0}.", "Hello", 0.995);
	sf::println("Escaping curly backets: {{, }}, {{{{, }}}}.");
	return EXIT_SUCCESS;
}
