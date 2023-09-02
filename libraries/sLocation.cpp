#include "structures.hpp"

sLocation::sLocation() :	root("www"), cli_max_body_size("1M"), autoindex(false), default_pages(1, "index.html"), replacem_path(""), redirection(0, "") {

        this->error_pages[400] = "errors/400.html";
        this->error_pages[403] = "errors/403.html";
        this->error_pages[404] = "errors/404.html";
        this->error_pages[405] = "errors/405.html";
        this->error_pages[413] = "errors/413.html";
        this->error_pages[500] = "errors/500.html";
        this->error_pages[504] = "errors/504.html";
        this->error_pages[505] = "errors/505.html";
    }

sLocation::~sLocation() {}

sLocation::sLocation(sLocation const & other) {

    *this = other;
}

sLocation & sLocation::operator=(sLocation const & other) {

    this->root = other.root;
    this->error_pages = other.error_pages;
    this->cli_max_body_size = other.cli_max_body_size;
    this->http_methods = other.http_methods;
    this->autoindex = other.autoindex;
    this->default_pages = other.default_pages;
    this->replacem_path = other.replacem_path;
    this->redirection = other.redirection;

    return *this;
}

std::ostream & operator<<(std::ostream & o, sLocation const & location) {
    o << "    root: " << location.root << std::endl;
    o << "    error pages:" << std::endl << mapElementsList(location.error_pages, 1);
    o << "    client max body size: " << location.cli_max_body_size << std::endl;
    o << "    HTTP methods: " << location.http_methods;
    o << std::boolalpha << "    autoindex: " << location.autoindex << std::endl;
    o << "    default pages: " << vectorElementsList(location.default_pages) << std::endl;
    o << "    replacement path: " << location.replacem_path << std::endl;
    o << "    redirection:" << std::endl << "        code: " << location.redirection.first << \
            ", new URL: " << location.redirection.second << std::endl;

    return o;
}