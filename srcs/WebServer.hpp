#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP
# include "../libraries/types.hpp"
# include "../libraries/structures.hpp"
# include "config_parsing/utils/utils.hpp"
# include "config_parsing/Config.hpp"

/* Catia's code */

struct sServ;//added this
class	Config;

class WebServer {
private:
	std::vector<sServ>  		_servers; //modified this
	int*						_sockets;
	int							_epollfd;
	Config						_conf(std::vector<sServ> _servers);
	
	void	_parse_config_create_servers_create_sockets(const std::string& path);
	void	_create_sockets();
public:
	WebServer();
	WebServer(const char* config_path);
//	WebServer(const WebServer& instance);
	~WebServer();

	int	start();
	int	stop();
	void test_sServ_struct();//added this

	//OPERATOR OVERLOADS
	WebServer& operator=(const WebServer& instance);
};

/* end of Catia's code */

#endif