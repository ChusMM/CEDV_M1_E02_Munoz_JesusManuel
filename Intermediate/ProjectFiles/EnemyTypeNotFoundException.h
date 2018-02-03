#pragma once

#include <exception>

class EnemyTypeNotFoundException : public std::exception
{
public:
	const char* what() const throw()
	{
		return "Queried enemy type cannot be found in this level";
	}
};