#ifndef CONFIG_HPP
# define CONFIG_HPP
# include "../../libraries/types.hpp"
# include "../../libraries/structures.hpp"
# include "utils/utils.hpp"

struct sServ;

class Config {

	private:
		void					_read_config_file(std::string path);
		void    				_file_check();
		void					_read_http_block();
		//std::pair<bool, bool>	_parse_http_block(std::pair<bool, bool> server_block_and_brace);
		void					_read_server_block();
		void					_read_location_block(sServ & serv_struct);

		//le direttive che stanno sia nel blocco server che in quello location devono avere una template function perché la struttura presa come parametro è diversa
		
		void	_read_listen_directive(sServ & serv_struct);
		void	_read_server_name_directive(sServ & serv_struct);
		// void	_read_root_directive(sServ & serv_struct);
		// void	_read_error_page_directive(sServ & serv_struct);
		// void	_read_client_max_body_size_directive(sServ & serv_struct);
		// void	_read_autoindex_directive(sServ & serv_struct);
		// void	_read_index_directive(sServ & serv_struct);
		// void	_read_return_directive(sServ & serv_struct);
		// void	_read_methods_directive(sServ & serv_struct);
		// void	_read_alias_directive(sServ & serv_struct);

		bool	_is_anything_inside_line();
		bool	_is_that_word_now(std::string word);

		void	_error_close_ifstream();

		//exception from which all the other exceptions derive
		class ConfigParentException : public std::exception {
			public:
				ConfigParentException();
				virtual ~ConfigParentException() throw();
            	virtual std::string const what(Config & config) const throw();
			protected:
				std::string _message;
		};

		class WrongConfFileException : public ConfigParentException {
			public:
            	virtual const char *what() const throw();
		};

		class WrongDirectiveException : public ConfigParentException {
			public:
				WrongDirectiveException();
		};

		class WrongArgumentsException : public ConfigParentException {
			public:
				WrongArgumentsException();
		};

		class MissingBracesException : public ConfigParentException {
			public:
				MissingBracesException();
		};

		class NoServerException : public ConfigParentException {
			public:
            	virtual const char *what() const throw();
		};

		std::size_t			_lines_count;
		std::string			_line;
		std::size_t			_position;
		std::vector<sServ>&	_servers;
		std::size_t			_servers_count;
		std::ifstream		_in_stream;

	public:
		Config();
		Config(std::string const & path, std::vector<sServ> & servers);
		Config(Config const & other);
		Config & operator=(const Config & other);
		~Config();

		bool	_conf_file_ok;

};

#endif