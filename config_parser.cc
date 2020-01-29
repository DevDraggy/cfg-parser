#include "config_parser.hh"
#include <regex>

//#include <algorithms>

using namespace cfg;
cfg_data cfg::parse_config_file(const std::string& str)
{
	std::ifstream stream(str);
	cfg_data f = parse_config_file(stream);
	stream.close();
	return f;
}

parse_exception::parse_exception(const std::string& message)
{
	this->message = message;
}

const char* parse_exception::what() const noexcept
{
	return message.c_str();
}


cfg_data cfg::parse_config_file(std::ifstream& stream)
{
	cfg_data data;
	std::string line;
	std::string matchstring;
	size_t pos;
	for (size_t i = 0; stream >> line; ++i)
	{
		if (line.at(0) != '#')
		{
			pos = line.find_first_of('=');
			if (pos == std::string::npos)
				throw parse_exception("At line " + std::to_string(i) + " \"=\" not found.");
			else
			{
				matchstring = line.substr(pos + 1);
				std::regex regex("\\\\n");
				matchstring = std::regex_replace(matchstring, regex, "\n");//   std::replace(matchstring.begin(),matchstring.end(),std::string("\\n"),std::string("\n"));
				data.insert(std::pair<std::string, std::string>(line.substr(0, pos), matchstring));
			}
		}
	}
	return data;
}