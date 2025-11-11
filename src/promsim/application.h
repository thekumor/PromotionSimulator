#pragma once

// Promotion Simulator
#include <promsim/config.h>

// STL
#include <utility>
#include <vector>

// WinAPI
#include <windows.h>

#define PROMSIM_DEFAULT_COLOR 1

namespace promsim
{

	class Application
	{
	public:
		Application(const std::string& title, const Config& config);
		Application() = default;
		~Application() = default;

		int Run();
		void Display();
		void Clear();
		void Wait(std::int32_t amount);
		std::string GetVariable(const std::string& name);
		std::int32_t GetVariableAsNumber(const std::string& name);
		BOOL SetTextColor(std::int32_t value);

	private:
		std::string m_Title;
		Config m_Config;
		std::pair<std::vector<Rank>, std::vector<User>> m_Users;
		std::vector<Var> m_Vars;
	};

}