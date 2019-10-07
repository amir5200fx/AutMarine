#include <error.hxx>
#include <OSstream.hxx>

#include <Global_Macros.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <fstream>
#include <iostream>
#include <IO_IGES.hxx>
#include <FastDiscrete_Params.hxx>

#include <Geo2d_Circle.hxx>

using namespace boost::archive;
using namespace AutLib;

int main()
{
	/*IO_IGES reader(gl_fast_discrete_parameters);
	reader.Verbose() = 1;
	reader.ReadFile("F16 one.IGS");*/

	fileName name("Plot.plt");
	OFstream myFile(name);

	Geo2d_Circle cir(Pnt2d(0, 0), 0.1, Dir2d(0.1, 0.3), 264);
	cir.ExportToPlt(myFile);

	PAUSE;
	return 0;
}