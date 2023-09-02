#include "utils.hpp"

//converts a string to an int
int	ft_stoi(std::string const & str) {
	
	int	i;
	int	num;

	num = 0;
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

//returns a string with all the elements of a vector of strings
std::string vectorElementsList(const std::vector<std::string> & vec) {

    std::string str = "";
	typename std::vector<std::string>::const_iterator it;

	for (it = vec.begin(); it != vec.end(); ++it) {
        str += *it + " ";
    }
    return str;
}

//returns a string with all the elements of a map<int, string>
std::string mapElementsList(const std::map<int, std::string> & map, bool indent) {

    std::string str = "";
    std::string key_str = "";
	typename std::map<int, std::string>::const_iterator it;

	for (it = map.begin(); it != map.end(); ++it) {
        std::stringstream ss;
        ss << it->first;
        key_str = ss.str();
		if (indent == 1)
			str += "    ";
        str += "    code: " + key_str + ", page: " + it->second + "\n";
	}
    return str;
}