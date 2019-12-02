#include <GModel_System.hxx>

#include <Cad_CurveInfo.hxx>
#include <GModel_FixWireInfo.hxx>

std::shared_ptr<AutLib::Cad_CurveInfo>
AutLib::gModelSys::par_curve_info = std::make_shared<AutLib::Cad_CurveInfo>();

std::shared_ptr<AutLib::Cad_CurveInfo>
AutLib::gModelSys::curve_info = std::make_shared<AutLib::Cad_CurveInfo>();

std::shared_ptr<AutLib::GModel_FixWireInfo>
AutLib::gModelSys::fix_wire = std::make_shared<AutLib::GModel_FixWireInfo>();

void AutLib::gModelSys::InitRunTime()
{
	par_curve_info->SetNbDivisions(20);
	curve_info->SetNbDivisions(40);

	fix_wire->SetPrecision(1.0E-3);
	fix_wire->SetMaxTolerance(1.0E-2);
	fix_wire->SetMinTolerance(1.0E-6);
}