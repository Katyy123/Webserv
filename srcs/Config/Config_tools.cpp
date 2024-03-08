#include "../../libraries/includes.hpp"
#include "Config.hpp"

// Check if the directive in conf file is valid
bool Config::_is_keywords(std::string word, std::vector<std::string> keywords) const {

	std::vector<std::string>::const_iterator it;

	for (it = keywords.begin(); it != keywords.end(); ++it) {
		if (word == *it)
			return true;
	}
	return false;
}

// Delete spaces at the beginning and at the and of a string
void Config::_cleanTrim(std::string & str)
{
    str.erase(0, str.find_first_not_of(" "));
    while (!str.empty() && str[str.length() - 1] == ' ')
        str.erase(str.length() - 1);
}

// Checks if a line in config file contains just spaces and comments
bool Config::_is_anything_inside_line() {
	this->_position = this->_line.find_first_not_of(' ', _position);
	return (!(_position == std::string::npos || _line[_position] == '#'));
}

// Checks if there is the word "word" in the current position in the config file
bool Config::_is_that_word_now(std::string word) const {

    std::size_t		word_pos = std::string::npos;

    word_pos = _line.find(word, this-> _position);
	return (word_pos == _position);
}