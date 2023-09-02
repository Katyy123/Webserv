#include "../libraries/includes.hpp"
#include "../libraries/templates.tpp"
#include "../libraries/types.hpp"
#include "config_parsing/Config.hpp"

WebServer::WebServer()
{
	//instanciate an epoll file descriptor
	;
}

WebServer::WebServer(const char* config_path)
{
	std::string	input_path(config_path);
	std::string	sanitized_path;

	//instanciate an epoll file descriptor
	SANITIZE_STRING(input_path, sanitized_path);
	std::cout << "Parsing configuration file <" << sanitized_path << "> ..." << std::endl;
	this->_parse_config_create_servers_create_sockets(sanitized_path);
}

// void WebServer::_parse_config_create_servers_create_sockets(const std::string& path)
// {
// 	(void)path;
// 	// PARSE HERE
// 	// open file > read from file > sanitize input one line at a time > maybe skip comments
// 	// > check for unclosed blocks "{}" (throw an exception in case of unclosed ones)
// 	// > count "server { ... }" blocks
// 	// > pass a string content to _add_server()
// 	// > read std::map _servers and create sockets accordingly with _create_sockets()
// }


/* Catia's code */

void WebServer::_parse_config_create_servers_create_sockets(const std::string& path)
{
	Config config(path, this->_servers);
	if (config._conf_file_ok == true)
		this->test_sServ_struct();
}

//prints all the elements of _servers vector
void WebServer::test_sServ_struct() {

	int count = 1;

	typename std::vector<sServ>::const_iterator it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it) {
		std::cout << std::endl << "--------------- SERVER " << count << " ---------------" << std::endl << std::endl;
		std::cout << *it << std::endl;
		count++;
	}
	std::cout << std::endl;
}

/* end of Catia's code */


WebServer::~WebServer()
{
	;
}

int WebServer::start()
{
	return(0);
}

int WebServer::stop()
{
	return(0);
}