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

	struct MemberMoveData
	{
		MemberMoveData(const std::pair<std::vector<Rank>, std::vector<User>>& users, size_t memberID, std::int8_t places, const std::wstring& reason);
		MemberMoveData() = default;

		std::wstring MemberName, OldRank, NewRank, Reason;
		bool IsPromotion;
		std::int8_t Places;

		friend std::wostream& operator<<(std::wostream& wos, const MemberMoveData& data);
	};

	class Application
	{
	public:
		Application(const std::string& title, const Config& config);
		Application() = default;
		~Application() = default;

		int Run();
		void Display();
		void Clear();
		void Logic();
		void Wait(std::int32_t amount);
		void DrawLine(std::int32_t times);
		bool MoveMember(size_t id, std::uint8_t places = 1);
		std::wstring GetVariable(const std::wstring& name);
		std::int32_t GetVariableAsNumber(const std::wstring& name);
		std::vector<std::wstring> GetVariables(const std::wstring& name);
		std::vector<std::int32_t> GetVariablesAsNumbers(const std::wstring& name);
		BOOL SetTextColor(std::int32_t value);

	private:
		std::string m_Title;
		MemberMoveData m_Message;
		Config m_Config;
		Date m_Date;
		std::pair<std::vector<Rank>, std::vector<User>> m_Users;
		std::vector<Var> m_Vars;
	};

}