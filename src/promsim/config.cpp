#include "config.h"

namespace promsim
{

    std::optional<std::string> ReadFile(const std::string& path)
    {
        std::fstream file(path.c_str(), std::ios::in);
        if (!file.is_open())
        {
            return {};
        }

        std::string content, line;
        while (std::getline(file, line))
            content += line + "\n";

        file.close();

        return content;
    }

    Config ReadFiles(const Config& paths)
    {
        auto users = ReadFile(paths.Users);
        auto vars = ReadFile(paths.Vars);

        if (!users || !vars)
            return {};

        return Config(users.value(), vars.value());
    }

    std::vector<Var> ParseVars(const std::string& input)
    {
        std::vector<Var> vars = {};

        std::string line;
        size_t prevPos = 0, pos = input.find('\n');
        while (pos != std::string::npos)
        {
            std::string line = input.substr(prevPos, pos - prevPos);

            // Check to see if it's not a comment.
            if (line[0] != '#')
            {
                size_t equals = line.find('=');
                if (equals != std::string::npos)
                {
                    std::string left = line.substr(0, equals);
                    std::string right = line.substr(equals + 1, line.size() - equals + 1);

                    Var var;
                    var.Name = left;
                    var.Content = right;

                    vars.push_back(var);
                }
            }

			prevPos = pos + 1;
			pos = input.find('\n', pos + 1);
        }

        return vars;
    }

    static std::uint8_t s_RankID = 0;
    static std::uint8_t s_UserID = 0;

    std::pair<std::vector<Rank>, std::vector<User>> ParseUsers(const std::string& input)
	{
		std::vector<User> users = {};
		std::vector<Rank> ranks = {};

        std::string line;
        size_t prevPos = 0, pos = input.find('\n');

		while (pos != std::string::npos)
		{
            std::string line = input.substr(prevPos, pos - prevPos);
            
            // Check to see if it's not a comment.
            if (line[0] != '#')
            {
                // Check if it's user (has a tab at the start).
                size_t tab = line.find('\t');
                if (tab != std::string::npos)
                {
                    std::string name = line.substr(1, line.size() - 1);
                    User user;
                    user.Name = name;
                    user.ID = ++s_UserID;
                    user.RankID = s_RankID;

                    users.push_back(user);
                }
                // Check if it's rank (has a colon at the end).
                else
                {
                    size_t colon = line.find(':');
                    if (colon != std::string::npos)
                    {
                        Rank rank;
                        rank.Name = line.substr(0, line.size() - 1);
                        rank.ID = ++s_RankID;

                        ranks.push_back(rank);
                    }
                }
            }

            prevPos = pos + 1;
            pos = input.find('\n', pos + 1);
		}

        return std::pair<std::vector<Rank>, std::vector<User>>(ranks, users);
	}

    Config::Config(const std::string& users, const std::string& vars)
        : Users(users), Vars(vars)
    {
    }

}