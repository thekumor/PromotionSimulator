// ================================================
// 
//	Project: Promotion Simulator
//	Game resembling Awans the Game from 2017.
//	by The Kumor
// 
// ================================================

#pragma execution_character_set("utf-8")

// STL
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fcntl.h>
#include <io.h>

// Promotion Simulator
#include <promsim/application.h>

int main()
{
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
	srand(time(nullptr));

	promsim::Config paths;
	paths.Users = L"config/users.txt";
	paths.Vars = L"config/vars.txt";

	promsim::Config config = promsim::ReadFiles(paths);

	promsim::Application app("Promotion Simulator", config);
	return app.Run();
}