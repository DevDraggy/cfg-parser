#ifndef CFG_PARSER_HH_AYB_PPL_DDD
#define CFG_PARSER_HH_AYB_PPL_DDD
#include <map>
#include <fstream>
namespace cfg
{
	using cfg_data = std::map<std::string, std::string>;
	struct parse_exception : public std::exception
	{
		parse_exception(const std::string& message = "parse_exception");
		virtual const char* what() const noexcept override;
		std::string message;
	};
	cfg_data parse_config_file(const std::string& filename);

	cfg_data parse_config_file(std::ifstream& stream);
}
#endif