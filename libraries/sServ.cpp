#include "structures.hpp"

sServ::sServ() : domain_names(1, ""), port(80), root("www"), cli_max_body_size("1M"), autoindex(false), default_pages(1, "index.html"), redirection(0, "") {

		ip_address = "0.0.0.0";

        this->error_pages[400] = "errors/400.html";
        this->error_pages[403] = "errors/403.html";
        this->error_pages[404] = "errors/404.html";
        this->error_pages[405] = "errors/405.html";
        this->error_pages[413] = "errors/413.html";
        this->error_pages[500] = "errors/500.html";
        this->error_pages[504] = "errors/504.html";
        this->error_pages[505] = "errors/505.html";
    }

sServ::~sServ() {}

std::ostream & operator<<(std::ostream & o, sServ const & serv) {
    o << "Domain names: " << vectorElementsList(serv.domain_names) << std::endl;
    o << "Ip address: " << serv.ip_address << std::endl;
    o << "Port: " << serv.port << std::endl;
    o << "Root: " << serv.root << std::endl;
    o << "Error pages:" << std::endl << mapElementsList(serv.error_pages, 0);
    o << "Client max body size: " << serv.cli_max_body_size << std::endl;
    o << std::boolalpha << "Autoindex: " << serv.autoindex << std::endl;
    o << "Default pages: " << vectorElementsList(serv.default_pages) << std::endl;
    o << "Redirection:" << std::endl << "    code: " << serv.redirection.first << \
            ", new URL: " << serv.redirection.second << std::endl;
    for (size_t i = 0; i < serv.locations.size() ; i++)
		std::cout << std::endl << "LOCATION " << i << ":" << std::endl << serv.locations[i];

    return o;
}