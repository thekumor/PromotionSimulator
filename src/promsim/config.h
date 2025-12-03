#pragma once

// STL
#include <string>
#include <cstdint>
#include <fstream>
#include <optional>
#include <iostream>
#include <vector>
#include <utility>
#include <io.h>
#include <fcntl.h>
#include <codecvt>

#define PROMSIM_INVALID_VAR_NUM -5432901235
#define PROMSIM_INVALID_VAR_STR L"-5432901235"

namespace promsim
{

	struct Config
	{
		std::wstring Users, Vars;

		Config(const std::wstring& users, const std::wstring& vars);
		Config() = default;
	};

	struct Rank
	{
		std::wstring Name;
		std::uint8_t ID;
	};

	struct User
	{
		std::wstring Name;
		std::uint8_t ID, RankID;
	};

	struct Var
	{
		std::wstring Name;
		std::wstring Content;
	};

	std::optional<std::wstring> ReadFile(const std::wstring& path);
	Config ReadFiles(const Config& paths);
	std::vector<Var> ParseVars(const std::wstring& input);
	std::pair<std::vector<Rank>, std::vector<User>> ParseUsers(const std::wstring& input);

}