/*
** File Name:	range.hpp
** Author:	Aditya Ramesh
** Date:	01/21/2014
** Contact:	_@adityaramesh.com
*/

#ifndef Z2CDD8E18_3354_4CA7_A001_5D32122EEAE7
#define Z2CDD8E18_3354_4CA7_A001_5D32122EEAE7

#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <ccbase/filesystem/directory_iterator.hpp>
#include <ccbase/filesystem/glob_matcher.hpp>

namespace cc {

boost::iterator_range<directory_iterator>
list_files(const char* path)
{
	return {
		directory_iterator{path},
		directory_iterator{}
	};
}

boost::iterator_range<boost::filter_iterator<glob_matcher, directory_iterator>>
match_files(const char* glob)
{
	const auto* end = std::strrchr(glob, '/');
	if (end == nullptr) {
		throw std::invalid_argument{"Invalid glob string."};
	}

	char buf[end - glob + 1];
	std::copy(glob, end, buf);
	buf[end - glob] = '\0';

	return {
		boost::make_filter_iterator(
			glob_matcher{end + 1},
			directory_iterator{buf},
			directory_iterator{}
		),
		boost::make_filter_iterator(
			glob_matcher{},
			directory_iterator{},
			directory_iterator{}
		)
	};
}

}

#endif
