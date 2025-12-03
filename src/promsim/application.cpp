#include "application.h"

namespace promsim
{

	Application::Application(const std::string& title, const Config& config)
		: m_Title(title), m_Config(config)
	{
	}

	int Application::Run()
	{
		m_Users = ParseUsers(m_Config.Users);
		m_Vars = ParseVars(m_Config.Vars);

		std::int32_t waitTime = GetVariableAsNumber(L"speed");
		std::vector<std::wstring> demotionReasons = GetVariables(L"dem_");

		m_Date = Date(2025, 11, 20);
		bool isRunning = true;

		while (isRunning)
		{
			Clear();
			Display();
			Wait(waitTime);

			std::uint32_t dayProgress = rand() % GetVariableAsNumber(L"maxLeap") + GetVariableAsNumber(L"minLeap");
			m_Date.Fastforward(dayProgress);
		}

		return 0;
	}

	void Application::Display()
	{
		std::int32_t defaultColor = GetVariableAsNumber(L"col_default");

		SetTextColor(defaultColor);
		std::wcout << m_Date.ToString(L"Y-M-D") << std::endl;

		for (std::int32_t i = 0; i < 30; i++)
			std::wcout << L"-";

		std::wcout << std::endl;

		for (auto& r : m_Users.first)
		{
			std::int32_t rankColor = GetVariableAsNumber(std::wstring(L"col_") + r.Name);
			SetTextColor(rankColor == PROMSIM_INVALID_VAR_NUM ? PROMSIM_DEFAULT_COLOR : rankColor);
			std::wcout << r.Name << ":" << std::endl;

			for (auto& u : m_Users.second)
			{
				if (u.RankID == r.ID)
				{
					SetTextColor(defaultColor == PROMSIM_INVALID_VAR_NUM ? PROMSIM_DEFAULT_COLOR : defaultColor);
					std::wcout << "\t" << u.Name << std::endl;
				}
			}

			std::wcout << std::endl;
		}
	}

	void Application::Clear()
	{
		std::system("cls");
	}

	void Application::Wait(std::int32_t amount)
	{
		Sleep(amount);
	}

	std::wstring Application::GetVariable(const std::wstring& name)
	{
		for (auto& k : m_Vars)
			if (k.Name == name)
				return k.Content;

		return PROMSIM_INVALID_VAR_STR;
	}

	std::int32_t Application::GetVariableAsNumber(const std::wstring& name)
	{
		auto var = GetVariable(name);

		if (var != PROMSIM_INVALID_VAR_STR)
			return _wtoi(var.c_str());

		return PROMSIM_INVALID_VAR_NUM;
	}

	std::vector<std::wstring> Application::GetVariables(const std::wstring& name)
	{
		std::vector<std::wstring> vars = {};
		
		for (std::int32_t i = 1;; i++)
		{
			std::wstring var = GetVariable(name + std::to_wstring(i));

			if (var != PROMSIM_INVALID_VAR_STR)
				vars.push_back(var);
			else // Run out of indexes (the end).
				break;
		}

		return vars;
	}

	std::vector<std::int32_t> Application::GetVariablesAsNumbers(const std::wstring& name)
	{
		std::vector<std::int32_t> vars = {};

		for (std::int32_t i = 1;; i++)
		{
			std::int32_t var = GetVariableAsNumber(name + std::to_wstring(i));

			if (var != PROMSIM_INVALID_VAR_NUM)
				vars.push_back(var);
			else // Run out of indexes (the end).
				break;
		}

		return vars;
	}

	BOOL Application::SetTextColor(std::int32_t value)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		return SetConsoleTextAttribute(handle, value);
	}

}