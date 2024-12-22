#include"classes.hpp"

using namespace std;
int main()
{
	Gra g;
	while(g.get_stan() == true)
	{
		g.akcja_gracza();
	}
	return 0;
}