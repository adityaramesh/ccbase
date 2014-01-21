/*
** File Name:	glob_matcher.hpp
** Author:	Aditya Ramesh
** Date:	08/27/2013
** Contact:	_@adityaramesh.com
*/

#ifndef Z8614FAE3_9C93_4CD5_8DDC_263814847601
#define Z8614FAE3_9C93_4CD5_8DDC_263814847601

#include <ccbase/filesystem/directory_iterator.hpp>
#include <ccbase/platform.hpp>

namespace cc {

CC_ALWAYS_INLINE bool
is_glob(const char c)
{
	return c == '?' || c == '*' || c == '[' || c == ']' || c == '\\';
}

class glob_matcher
{
private:
	const char* pat{};
public:
	explicit glob_matcher() noexcept {}

	explicit glob_matcher(const char* pat)
	noexcept : pat{pat}
	{
		// If we are in debug mode, ensure that the pattern is valid.
		assert(pat != nullptr && pat[0] != '\0');

		#ifndef NDEBUG
		auto i = 0u;

		/*
		** The following sequences are considered to be syntax
		** violations when they occur within glob patterns:
		**
		**   1. Special characters within groups.
		**   2. Empty groups.
		**   3. Any backslash not followed by a special character; this
		**   includes trailing backslashes.
		*/
		do switch (pat[i]) {
		default:
		case '*':
		case '?':     ++i;                            continue;
		case '[':     assert(pat[++i] != ']');        goto group_mode;
		// Ensure that the character escaped using a backslash is a
		// special character.
		case '\\':    assert(is_glob(pat[++i])); ++i; continue;
		regular_mode:                                 continue;
		} while (pat[i] != '\0');
		return;
		
		// Check to ensure that the current group is valid.
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

	/*
	** Determines whether the directory entry's name matches the glob
	** pattern.
	*/
	bool operator()(const directory_entry& e) const
	{
		#ifndef NDEBUG
			assert(pat != nullptr);
		#endif

		// Offset into pattern that we are matching.
		auto i = 0u;
		// Offset into the file name.
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
	/*
	** Determines whether `s[j]` matches the group of characters starting at
	** `pat[i]`.
	*/
	bool match_group(const char* s, unsigned& i, unsigned& j) const
	{
		auto b = false;
		do {
			// Skip past the backslash before an escaped character.
			i += (pat[i] == '\\');
			b = b || (pat[i] == s[j]);
			++i;
		}
		while (pat[i] != ']');
		++i;
		++j;
		return b;
	}

	/*
	** After this method is called, we must iteratively test each character
	** of `s` beginning at `s[j]` to check whether it matches the characters
	** after the wildcards beginning at `pat[i - 1]`.
	*/
	bool match_wildcard(const char* s, unsigned i, unsigned j) const
	{
		/*
		** We keep track of the index `pi` after each wildcard that we
		** are trying to match, and the index `pj` into `s` at which we
		** are looking for a match. If the characters after the wildcard
		** fail to match the string beginning at `s[j]`, then we reset
		** `i` to `pi` and `j` to `pj`.
		*/

		// First index of current subpattern for which we are looking
		// for a match. A subpattern is a pattern between a wildcard and
		// another wildcard or null character.
		auto pi = i;
		// Current index at which we are looking for a match.
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
				/*
				** If we increment `i` by one, then we will
				** interpret the following escaped character as
				** a special character at the next iteration. To
				** prevent this, we must anticipate what should
				** happen in the next iteration.
				*/
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
