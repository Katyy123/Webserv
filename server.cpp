#include "libraries/includes.hpp"
#include "libraries/types.hpp"

int main(int argc, const char **argv)
{
	if (argc != 2) // il file di configuraz può anche non essere presente (da rivedere)
	{
		std::cout << "Error: Server must be run with <path_to_config_file> argument" << std::endl;
		return (1);
	}

	try {
		WebServer	Server(argv[1]);
		std::cout << "WebServer configured: Starting..." << std::endl;
		Server.start();
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return (1);
	}

	std::cout << "WebServer closing." << std::endl;
	return (0);
}