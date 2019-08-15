#include <error.hxx>
#include <OSstream.hxx>

#include <Global_Macros.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <fstream>
#include <iostream>

using namespace boost::archive;
using namespace AutLib;

int main()
{
	std::fstream file;
	file.open("save.txt", ios::out);

	text_oarchive oa(file);
	oa << Pnt2d(1, 3);

	Entity2d_Box b1(Pnt2d(0.2, 1.3), Pnt2d(0.86, 4.8));
	oa << b1;

	PAUSE;
	return 0;
}