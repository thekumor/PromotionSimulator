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

        // Config variables
        std::int32_t waitTime = GetVariableAsNumber("speed");

        bool isRunning = true;

        while (isRunning)
        {
            Clear();
            Display();
            Wait(waitTime);
        }

        return 0;
    }

    void Application::Display()
    {
        std::int32_t defaultColor = GetVariableAsNumber("col_default");

        for (auto& r : m_Users.first)
        {
            std::int32_t rankColor = GetVariableAsNumber(std::string("col_") + r.Name);
            SetTextColor(rankColor == PROMSIM_INVALID_VAR_NUM ? PROMSIM_DEFAULT_COLOR : rankColor);
            std::cout << r.Name << ":" << std::endl;

            for (auto& u : m_Users.second)
            {
                if (u.RankID == r.ID)
				{
                    SetTextColor(defaultColor == PROMSIM_INVALID_VAR_NUM ? PROMSIM_DEFAULT_COLOR : defaultColor);
                    std::cout << "\t" << u.Name << std::endl;
                }
            }

            std::cout << std::endl;
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

    std::string Application::GetVariable(const std::string& name)
    {
        for (auto& k : m_Vars)
            if (k.Name == name)
                return k.Content;

        return PROMSIM_INVALID_VAR_STR;
    }

    std::int32_t Application::GetVariableAsNumber(const std::string& name)
    {
        auto var = GetVariable(name);

        if (var != PROMSIM_INVALID_VAR_STR)
            return atoi(var.c_str());

        return PROMSIM_INVALID_VAR_NUM;
    }

    BOOL Application::SetTextColor(std::int32_t value)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        return SetConsoleTextAttribute(handle, value);
    }

}