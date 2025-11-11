// ================================================
// 
//	Project: Promotion Simulator
//	Game resembling Awans the Game from 2017.
//	by The Kumor
// 
// ================================================

#include <promsim/application.h>

int main()
{
	promsim::Config paths;
	paths.Users = "config/users.txt";
	paths.Vars = "config/vars.txt";

	promsim::Config config = promsim::ReadFiles(paths);

	promsim::Application app("Promotion Simulator", config);
	return app.Run();
}