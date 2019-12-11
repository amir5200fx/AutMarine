#include <CadSingularity_gDetection_Base.hxx>

#include <Cad_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Cad2d_Plane_System.hxx>
#include <CadPlnModel_Curve.hxx>
#include <CadPlnModel_Segment.hxx>
#include <CadSingularity_PoleCurve.hxx>
#include <CadSingularity_LineCurve.hxx>

#include <CadSingularity_Detection_BaseM.cxx>

namespace AutLib
{

	ParametricCurve_Pole_Declaration(GModel_parCurve, g)
		ParametricCurve_Line_Declaration(GModel_parCurve, g)
	
}