#include "../../libraries/includes.hpp"
#include "Config.hpp"

Config::Config(std::string const & path, std::vector<sServ> & servers) : \
		_lines_count(0), _line(""), _position(0), _servers(servers), _servers_count(0), _conf_file_ok(true) {

	try {
		_read_config_file(path);
	}
	catch (WrongConfFileException & e) {
		_error_close_ifstream();
		std::cerr << e.what() << std::endl;
	}
	catch (WrongDirectiveException & e) {
		_error_close_ifstream();
		std::cerr << e.what(*this) << std::endl;
	}
	catch (WrongArgumentsException & e) {
		_error_close_ifstream();
		std::cerr << e.what(*this) << std::endl;
	}
	catch (MissingBracesException & e) {
		_error_close_ifstream();
		std::cerr << e.what(*this) << std::endl;
	}
	catch (NoServerException & e) {
		_error_close_ifstream();
		std::cerr << e.what() << std::endl;
	}
	// tutti i catch
}

// Config::Config(Config const & other) {

// }

// Config & Config::operator=(Config const & other) {


// }

Config::~Config() {


}

//reads configuration file
void Config::_read_config_file(std::string path) {

	//std::cout << "_read_config_file" << std::endl;
	bool			http_block = false;
	bool			http_brace = false;
	std::string		line_read;

	this->_in_stream.open(path.c_str(), std::ios_base::in);
	_file_check();
	while (getline(_in_stream, line_read)) {
		this->_lines_count++;
		SANITIZE_STRING(line_read, this->_line);
		_position = 0;
		if (http_block == false) {
			if (this->_is_anything_inside_line() == false)
				continue;
			if (this->_is_that_word_now("http") == false)
				throw WrongDirectiveException();
			else {
				_position += std::string("http").length();
				http_block = true;
			}
		}
		if (http_block == true && http_brace == false) {
			if (this->_is_anything_inside_line() == false)
				continue;
			if (this->_is_that_word_now("{") == false)
				throw MissingBracesException();
			else {
				_position ++;
				http_brace = true;
				_read_http_block();
			}
		}
		if (this->_is_anything_inside_line() == false)
			continue;
		else {
			throw WrongDirectiveException();
		}
	}
	_in_stream.close();
}

//check if the file exists, can be open or is empty
void Config::_file_check() {

	//std::cout << "_file_check" << std::endl;
	if (!this->_in_stream.is_open()) {
		throw WrongConfFileException();
	}
	if (_in_stream.peek() == EOF) {
		_in_stream.close();
		throw WrongConfFileException();
	}
}

//reads the http block
void Config::_read_http_block() {

	(void)_in_stream;
	//std::cout << "_read_http_block" << std::endl;
	bool		server_block = false;
	bool		server_brace = false;
	std::string	line_read;

	/* --- block 3 (identici) --- */
	while (true) {
		if (server_block == false) {
			if (this->_is_anything_inside_line() == false)
				break;
			else if (_line[_position] == '}' && this->_servers_count > 0) {
				_position++;
				return;
			}
			else if (_line[_position] == '}' && _servers_count == 0)
				throw NoServerException();
			if (this->_is_that_word_now("server") == false)
				throw WrongDirectiveException();
			else {
				_position += std::string("server").length();
				server_block = true;
			}
		}
		if (server_block == true && server_brace == false) {
			if (this->_is_anything_inside_line() == false)
				break;
			if (this->_is_that_word_now("{") == false)
				throw MissingBracesException();
			else {
				_position ++;
				server_brace = true;
				_read_server_block();
				server_block = false;
				server_brace = false;
			}
		}
	}
	/* --- end block 3 (identici) --- */
	while (getline(this->_in_stream, line_read)) {
		this->_lines_count++;
		SANITIZE_STRING(line_read, this->_line);
		this->_position = 0;
		/* --- block 3 --- */
		while (true) {
			if (server_block == false) {
				if (this->_is_anything_inside_line() == false)
					break;
				else if (_line[_position] == '}' && this->_servers_count > 0) {
					_position++;
					return;
				}
				else if (_line[_position] == '}' && _servers_count == 0)
					throw NoServerException();
				if (this->_is_that_word_now("server") == false)
					throw WrongDirectiveException();
				else {
					_position += std::string("server").length();
					server_block = true;
				}
			}
			if (server_block == true && server_brace == false) {
				if (this->_is_anything_inside_line() == false)
					break;
				if (this->_is_that_word_now("{") == false)
					throw MissingBracesException();
				else {
					_position ++;
					server_brace = true;
					_read_server_block();
					server_block = false;
					server_brace = false;
				}
			}
		}
		/* --- end block 3 --- */
	}
	_position = 0;
	throw MissingBracesException();
}

// //reads the http block (calls _parse_http_block function to do all the parsing)
// void Config::_read_http_block() {

// 	//std::cout << "_read_http_block" << std::endl;
// 	bool		server_block = false;
// 	bool		server_brace = false;
// 	std::pair<bool, bool> server_block_and_brace;
// 	std::string	line_read;

// 	server_block_and_brace.first = server_block;
// 	server_block_and_brace.second = server_brace;
// 	server_block_and_brace =_parse_http_block(server_block_and_brace);
// 	while (getline(this->_in_stream, line_read)) {
// 		this->_lines_count++;
// 		SANITIZE_STRING(line_read, this->_line);
// 		this->_position = 0;
// 		server_block_and_brace =_parse_http_block(server_block_and_brace);
// 	}
// 	_position = 0;
// 	throw MissingBracesException();
// }

// //parses the http block
// std::pair<bool, bool> Config::_parse_http_block(std::pair<bool, bool> server_block_and_brace) {

// 	bool		server_block = server_block_and_brace.first;
// 	bool		server_brace = server_block_and_brace.second;

// 	while (true) {
// 		if (server_block == false) {
// 			if (this->_is_anything_inside_line() == false)
// 				break;
// 			else if (_line[_position] == '}' && this->_servers_count > 0) {
// 				_position++;
// 				server_block_and_brace.first = server_block;
// 				server_block_and_brace.second = server_brace;
// 				return (server_block_and_brace);
// 			}
// 			else if (_line[_position] == '}' && _servers_count == 0)
// 				throw NoServerException();
// 			if (this->_is_that_word_now("server") == false)
// 				throw WrongDirectiveException();
// 			else {
// 				_position += std::string("server").length();
// 				server_block = true;
// 			}
// 		}
// 		if (server_block == true && server_brace == false) {
// 			if (this->_is_anything_inside_line() == false)
// 				break;
// 			if (this->_is_that_word_now("{") == false)
// 				throw MissingBracesException();
// 			else {
// 				_position ++;
// 				server_brace = true;
// 				_read_server_block();
// 				server_block = false;
// 				server_brace = false;
// 			}
// 		}
// 	}
// 	server_block_and_brace.first = server_block;
// 	server_block_and_brace.second = server_brace;
// 	return (server_block_and_brace);
// }

//reads a server block and adds the sServ struct to _servers vector
void Config::_read_server_block() {

	//std::cout << "_read_server_block" << std::endl;
	sServ		serv_struct;
	//sLocation 	location; //poi cancellarla perché location deve essere instanziata nella funzione _read_location_block
	std::size_t	end_word_pos;
	std::string	line_read;

	this->_servers_count++;
	while (getline(this->_in_stream, line_read)) {
		this->_lines_count++;
		SANITIZE_STRING(line_read, this->_line);
		this->_position = 0;
		end_word_pos = 0;
		while (true) {
			this->_position = _line.find_first_of("abcdefghijklmnopqrstuvwxyz}", _position);
			if (_position == std::string::npos || _line[_position] == '}') {
				break;
			}
			end_word_pos = _line.find(' ', _position) - 1;
			if (_line.substr(_position, end_word_pos - _position + 1) == "listen") {
				_read_listen_directive(serv_struct);
			}
			else if (_line.substr(_position, end_word_pos - _position + 1) == "server_name")
				_read_server_name_directive(serv_struct);
			else if (_line.substr(_position, end_word_pos - _position + 1) == "location")
				_read_location_block(serv_struct);
			//aggiungere ogni else if per ogni directive (ricorda che alcune funzioni devono essere dei template) (farlo dopo)
			else {
				;//errore
			}
		}
		if (_position != std::string::npos && _line[_position] == '}') {
			//std::cout << "check ---" << std::endl;
			_position ++;
			break;
		}
		//considerare il caso in cui non viene trovata '}' prima di EOF
	}
	this->_servers.push_back(serv_struct);//add sServ struct to _servers vector
}

//reads the location block
void Config::_read_location_block(sServ & serv_struct) {

	(void)serv_struct;

	sLocation location;

	serv_struct.locations.push_back(location);
	this->_position += std::string("location").length();
}

//Closes the ifstream and sets _conf_file_ok to false
void	Config::_error_close_ifstream() {
	
	this->_in_stream.close();
	this->_conf_file_ok = false;
}
