#include "../../libraries/includes.hpp"
#include "Config.hpp"

//reads a listen directive and store the value inside sServ struct
void Config::_read_listen_directive(sServ & serv_struct)
{
	//std::cout << "_read_listen_directive" << std::endl;
	std::string	ip_string = "";
	std::string	port_string = "";
	std::size_t end_ip = std::string::npos;
	std::size_t end_port = std::string::npos;

	// std::cout << "line: " << _line << std::endl;
	// std::cout << "position 1: " << _position << std::endl;
	this->_position += std::string("listen").length();
	// std::cout << "position 2: " << _position << std::endl;
	this->_position = _line.find_first_of("abcdefghijklmnopqrstuvwxyz0123456789}", _position);
	// std::cout << "position 3: " << _position << std::endl;
	if (_position == std::string::npos || _line[_position] == '}') {
		//vuol dire che la directive listen è vuota. Da gestire (dopo)
		return;
	}
	end_ip = _line.find(':', _position) - 1;
	// std::cout << "end_ip: " << end_ip << std::endl;
	ip_string = (_line.substr(_position, end_ip - _position + 1));
	//std::cout << "ip_string: " << ip_string << std::endl;
	serv_struct.ip_address = ip_string;
	//std::cout << "serv_struct.ip_address: " << serv_struct.ip_address << std::endl;
	_position = end_ip + 2;
	end_port = _line.find(';', _position) - 1;
	port_string = (_line.substr(_position, end_port - _position + 1));
	serv_struct.port = std::atoi(port_string.c_str());
	_position = end_port + 2;
}

//reads a server_name directive and store the value inside sServ struct
void Config::_read_server_name_directive(sServ & serv_struct)
{
	//std::cout << "_read_server_name_directive" << std::endl;
	std::size_t	end_domain;
	std::string	domain_string;

	this->_position += std::string("server_name").length();
	this->_position = _line.find_first_of("abcdefghijklmnopqrstuvwxyz0123456789}", _position);
	if (_position == std::string::npos || _line[_position] == '}') {
		//vuol dire che la directive listen è vuota. Da gestire (dopo)
		return;
	}
	end_domain = _line.find(';', _position) - 1;
	domain_string = (_line.substr(_position, end_domain - _position + 1));
	serv_struct.domain_names.clear();
	serv_struct.domain_names.push_back(domain_string);
	_position = end_domain + 2;
}

// void Config::_read_root_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }

// void Config::_read_error_page_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }

// void Config::_read_client_max_body_size_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }

// void Config::_read_autoindex_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }

// void Config::_read_index_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }

// void Config::_read_return_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }

// void Config::_read_methods_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }

// void Config::_read_alias_directive(sServ & serv_struct)
// {
// 	(void)serv_struct;
// }