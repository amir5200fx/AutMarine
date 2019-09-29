#include <TModel_System.hxx>

#include <Cad_CurveInfo.hxx>
#include <TModel_FixWireInfo.hxx>

std::shared_ptr<AutLib::Cad_CurveInfo>
AutLib::tModelSys::par_curve_info = std::make_shared<AutLib::Cad_CurveInfo>();

std::shared_ptr<AutLib::Cad_CurveInfo>
AutLib::tModelSys::curve_info = std::make_shared<AutLib::Cad_CurveInfo>();

void AutLib::tModelSys::InitRunTime()
{
	par_curve_info->SetNbDivisions(20);
	curve_info->SetNbDivisions(40);

	fix_wire->SetPrecision(1.0E-3);
	fix_wire->SetMaxTolerance(1.0E-2);
	fix_wire->SetMinTolerance(1.0E-6);
}