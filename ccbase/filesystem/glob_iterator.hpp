/*
** File Name:	glob_iterator.hpp
** Author:	Aditya Ramesh
** Date:	08/27/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z8614FAE3_9C93_4CD5_8DDC_263814847601
#define Z8614FAE3_9C93_4CD5_8DDC_263814847601

#include <iostream>
#include <boost/iterator/filter_iterator.hpp>
#include <ccbase/filesystem/directory_iterator.hpp>
#include <ccbase/platform.hpp>

namespace cc
{

CC_ALWAYS_INLINE bool
is_glob(const char c)
{
	return c == '?' || c == '*' || c == '[' || c == ']' || c == '\\';
}

class glob_matcher
{
private:
	const char* pat;
public:
	explicit glob_matcher(const char* pat)
	noexcept : pat{pat}
	{
		// If we are in debug mode, ensure that the pattern is valid.
		assert(pat != nullptr && pat[0] != '\0');

		#ifndef NDEBUG
		auto i = 0u;

		// These sequences are considered to be syntax violations when
		// they occur within glob patterns supplied to this constructor:
		// 1. Special characters within groups.
		// 2. Empty groups.
		// 3. Any backslash not followed by special character; this
		// includes trailing backslashes.

		do switch (pat[i]) {
		default:
		case '*':
		case '?':     ++i;                            continue;
		case '[':     assert(pat[++i] != ']');        goto group_mode;
		case '\\':    assert(is_glob(pat[++i])); ++i; continue;
		regular_mode:                                 continue;
		} while (pat[i] != '\0');
		return;

	group_mode:
		for(;;) switch (pat[i]) {
		default:   ++i;                            continue;
		case ']':  ++i;                            goto regular_mode;
		case '\\': assert(is_glob(pat[++i])); ++i; continue;
		case '*':
		case '?':
		case '\0': assert(false);
		}

		#endif
	}

	bool operator()(const directory_entry& e) const
	{
		auto i = 0u;
		auto j = 0u;
		auto s = e.name();
		do switch(pat[i]) {
		default:   if (pat[i++] != s[j++])           return false; continue;
		case '*':  ++i; return match_wildcard(s, i, j);
		case '?':  ++i; ++j;                                       continue;
		case '[':  ++i; if (!match_group(s, i, j))   return false; continue;
		case '\\': ++i; if (pat[i++] != s[j++])      return false; continue;
		} while (pat[i] != '\0' && s[j] != '\0');
		return (pat[i] == '\0' || pat[i] == '*') && s[j] == '\0';
	}
private:
	bool match_group(const char* s, unsigned& i, unsigned& j) const
	{
		auto b = false;
		do {
			i += (pat[i] == '\\');
			b = b || (pat[i] == s[j]);
			++i;
		}
		while (pat[i] != ']');
		++i;
		++j;
		return b;
	}

	bool match_wildcard(const char* s, unsigned i, unsigned j) const
	{
		// First index of current subpattern for which we are finding a
		// match. A subpattern is a pattern between a wildcard and
		// another wildcard or null character.
		auto pi = i;
		// Current index at which we are checking for a match.
		auto pj = j;

		while (s[j] != '\0') switch (pat[i]) {
			default:
				if (pat[i] != s[j]) {
					++pj;
					i = pi;
					j = pj;
					continue;
				}
				else {
					++i;
					++j;
					continue;
				}
			case '*':
				++i;
				pi = i;
				pj = j;
				continue;
			case '?':
				++i;
				++j;
				continue;
			case '[':
				++i;
				if (!match_group(s, i, j)) {
					++pj;
					i = pi;
					j = pj;
				}
				continue;
			case '\\':
				// We have to be careful about how we increment
				// i before continuing to the next iteration, or
				// else we may treat the escaped character as a
				// special character.
				if (pat[i + 1] != s[j]) {
					++pj;
					i = pi;
					j = pj;
					continue;
				}
				else {
					i += 2;
					++j;
					continue;
				}
		}
		return pat[i] == '\0';
	}
};

}

#endif
