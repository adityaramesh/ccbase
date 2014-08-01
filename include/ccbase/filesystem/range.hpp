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

#include <boost/range/iterator_range.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/utility/string_ref.hpp>
#include <ccbase/filesystem/directory_iterator.hpp>
#include <ccbase/filesystem/glob_matcher.hpp>

namespace cc {

boost::iterator_range<directory_iterator>
list_files(const boost::string_ref path)
{
	return {
		directory_iterator{path},
		directory_iterator{}
	};
}

boost::iterator_range<
	boost::filter_iterator<glob_matcher, directory_iterator>
>
match_files(const boost::string_ref glob)
{
	auto end = glob.rfind(PLATFORM_DIRECTORY_SEPARATOR);
	if (end == boost::string_ref::npos) {
		throw std::invalid_argument{"Invalid glob string."};
	}

	return {
		boost::make_filter_iterator(
			glob_matcher{glob.substr(end + 1)},
			directory_iterator{glob.substr(0, end)},
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
