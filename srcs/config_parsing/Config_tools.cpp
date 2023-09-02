#include "../../libraries/includes.hpp"
#include "Config.hpp"

//checks if a line in config file contains just spaces and comments
bool Config::_is_anything_inside_line() {
	this->_position = this->_line.find_first_not_of(' ', _position);
	return (!(_position == std::string::npos || _line[_position] == '#'));
}

//checks if there is the word "word" in the current position in the config file
bool Config::_is_that_word_now(std::string word) {

    std::size_t		word_pos = std::string::npos;

    word_pos = _line.find(word, this-> _position);
	return (word_pos == _position);
}