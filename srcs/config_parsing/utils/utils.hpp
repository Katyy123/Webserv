#ifndef UTILS_HPP
#define UTILS_HPP

# include "../../../libraries/includes.hpp"

int	ft_stoi(std::string const & str);
std::string vectorElementsList(const std::vector<std::string> & vec);
std::string mapElementsList(const std::map<int, std::string> & map, bool indent);

#endif // __UTILS_H__