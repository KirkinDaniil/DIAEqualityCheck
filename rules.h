#include <string>
#include <iostream>
#include <vector>

#ifndef _B
#define _B


class rule
{
public:
	char from;
	bool is_ending;
	std::vector<char> to;

	void print()
	{
		std::string to_str = "";
		for (char not_term : to)
		{
			to_str += not_term;
		}
		std::cout << "From: " << from << " Is ending? " << is_ending << "Not terminals: " << to_str << std::endl;
	}

	bool operator<(const rule r) const
	{
		return this->from < r.from;
	}
};

#endif
