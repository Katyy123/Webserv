#include "../../libraries/includes.hpp"
#include "Config.hpp"

Config::ConfigParentException::ConfigParentException() : _message("error message") {}

Config::ConfigParentException::~ConfigParentException() throw() {}

std::string const Config::ConfigParentException::what(Config & config) const throw() {

	std::string			str;
	std::stringstream	ss;
	std::string			lines_count_str;
	std::string			column_str;

	ss << config._lines_count;
	ss >> lines_count_str;
	ss.str("");
	ss.clear();
	ss << config._position + 1;
	ss >> column_str;
	str = "Error: " + this->_message + " in line " + lines_count_str + ", column " + column_str;
    return str;
}

const char * Config::WrongConfFileException::what() const throw() {

    return "Error: cannot use this file.\nIt is possible that the file does not exist, cannot be opened or is empty.";
}

Config::WrongDirectiveException::WrongDirectiveException() {

	this->_message = "wrong directive";
}

Config::WrongArgumentsException::WrongArgumentsException() {
	
	this->_message = "wrong directive arguments";
}

Config::MissingBracesException::MissingBracesException() {
	
	this->_message = "missing brace";
}

const char * Config::NoServerException::what() const throw() {

    return "Error: there is no server directive in the configuration file";
}