#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

# include "includes.hpp"
# include "../srcs/config_parsing/utils/utils.hpp"


// HTTP METHODS STRUCT
struct sHttpMethods
{
	bool get;
	bool post;
	bool del;

	sHttpMethods();
    sHttpMethods(sHttpMethods const & other);
    sHttpMethods & operator=(sHttpMethods const & other);
    ~sHttpMethods();
};

std::ostream & operator<<(std::ostream & o, sHttpMethods const & http_methods);


// LOCATION BLOCK STRUCT
struct sLocation
{
	//std::string proxy_pass;

	std::string 				root;
	std::map<int, std::string>	error_pages;
	std::string					cli_max_body_size;
	sHttpMethods				http_methods;
	bool						autoindex;
	std::vector<std::string>	default_pages; //index directive
	std::string					replacem_path; //alias directive
	std::pair<int, std::string>	redirection; //return directive

	sLocation();
    sLocation(sLocation const & other);
    sLocation & operator=(sLocation const & other);
    ~sLocation();
};

std::ostream & operator<<(std::ostream & o, sLocation const & serv);


// SERVER STRUCT
struct sServ 
{
	std::vector<std::string>    domain_names;
	std::string					ip_address; //can be found in listen or server_name directives
	size_t						port;
	std::string 				root;
	std::map<int, std::string>  error_pages;
	std::string				    cli_max_body_size;
	bool						autoindex;
	std::vector<std::string>	default_pages; //index directive
	std::pair<int, std::string>	redirection; //return directive
	std::vector<sLocation>		locations;

	sServ();
	~sServ();
};

std::ostream & operator<<(std::ostream & o, sServ const & serv);


#endif // STRUCTURES_HPP