#pragma once

// STL
#include <string>
#include <cstdint>
#include <fstream>
#include <optional>
#include <iostream>
#include <vector>
#include <utility>

#define PROMSIM_INVALID_VAR_NUM -5432901235
#define PROMSIM_INVALID_VAR_STR "-5432901235"

namespace promsim
{

	struct Config
	{
		std::string Users, Vars;

		Config(const std::string& users, const std::string& vars);
		Config() = default;
	};

	struct Rank
	{
		std::string Name;
		std::uint8_t ID;
	};

	struct User
	{
		std::string Name;
		std::uint8_t ID, RankID;
	};

	struct Var
	{
		std::string Name, Content;
	};

	std::optional<std::string> ReadFile(const std::string& path);
	Config ReadFiles(const Config& paths);
	std::vector<Var> ParseVars(const std::string& input);
	std::pair<std::vector<Rank>, std::vector<User>> ParseUsers(const std::string& input);

}