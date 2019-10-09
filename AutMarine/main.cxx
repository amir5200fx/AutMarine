#include <error.hxx>
#include <OSstream.hxx>

#include <Global_Macros.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <fstream>
#include <iostream>
#include <IO_IGES.hxx>
#include <FastDiscrete_Params.hxx>
#include <Leg_Vessel_Nihad2.hxx>

using namespace boost::archive;
using namespace AutLib;

int main()
{
	/*IO_IGES reader(gl_fast_discrete_parameters);
	reader.Verbose() = 1;
	reader.ReadFile("F16 one.IGS");*/


	Leg_Nihad2_HullPatch patch;
	
	/*patch.AftSection().Tightness0()->SetValue(0.1);
	patch.AftSection().Tightness1()->SetValue(0.1);

	patch.MidSection().Tightness0()->SetValue(0.1);
	patch.MidSection().Tightness1()->SetValue(0.1);*/

	patch.FwdSection().Tightness0()->SetValue(0.9);
	patch.FwdSection().Tightness1()->SetValue(0.9);

	patch.AftSection().Trim()->SetValue(0.1);
	patch.MidSection().Trim()->SetValue(0.1);
	patch.FwdSection().Trim()->SetValue(0.1);


	patch.Perform();
	//patch.Discrete();

	patch.FileFormat() = Leg_EntityIO_Format::IGES;
	patch.ExportToFile();

	PAUSE;
	return 0;
}