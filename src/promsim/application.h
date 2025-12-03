#pragma once

// Promotion Simulator
#include <promsim/config.h>
#include <promsim/date.h>

// STL
#include <utility>
#include <vector>
#include <string>

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
		std::wstring GetVariable(const std::wstring& name);
		std::int32_t GetVariableAsNumber(const std::wstring& name);
		std::vector<std::wstring> GetVariables(const std::wstring& name);
		std::vector<std::int32_t> GetVariablesAsNumbers(const std::wstring& name);
		BOOL SetTextColor(std::int32_t value);

	private:
		std::string m_Title;
		Config m_Config;
		Date m_Date;
		std::pair<std::vector<Rank>, std::vector<User>> m_Users;
		std::vector<Var> m_Vars;
	};

}