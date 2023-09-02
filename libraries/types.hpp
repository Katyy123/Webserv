#ifndef TYPES_HPP
# define TYPES_HPP
# include "includes.hpp"

class BadInputException : public std::exception {
public:
	const char* what() const throw() {
		return "Error: Bad Input";
	}
};


// SERVER STRUCTURES
typedef struct s_location
{
	std::string proxy_pass;
}	t_location;

typedef	struct s_serv 
{
	size_t		port;
	std::string name;
	std::vector<t_location>	locations;
}	t_serv;

#endif