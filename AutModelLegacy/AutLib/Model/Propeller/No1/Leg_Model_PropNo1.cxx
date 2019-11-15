#include <Leg_Model_PropNo1.hxx>

#include <Leg_PropNo1_Parameters.hxx>
#include <Leg_PropNo1_Profiles.hxx>
#include <Leg_Prop_BladeFace.hxx>
#include <Leg_Prop_WrappedSection.hxx>
#include <Leg_Prop_PropView.hxx>

#include <TColgp_Array2OfPnt.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <Geom_BSplineSurface.hxx>

void AutLib::Leg_Model_PropNo1_Blade::AllocateMemory()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	theXparams_ = std::make_shared<Leg_PropNo1_Xparams>();
	theXparams_->AllocateMemory(nbSections);

	thePropView_ = std::make_shared<Leg_Prop_PropView>(nbSections);
}

AutLib::Leg_Model_PropNo1_Blade::Leg_Model_PropNo1_Blade()
{
	theParameters_ = std::make_shared<Leg_PropNo1_Parameters>();
	theProfiles_ = std::make_shared<Leg_PropNo1_Profile>();
}

void AutLib::Leg_Model_PropNo1_Blade::CreateBladeFaces()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();
	const auto nbSpans = params.NbSpans();

	auto bladeFaces = std::make_shared<Leg_Prop_BladeFace>();

	TColgp_Array2OfPnt Q(1, nbSections, 1, nbSpans);
	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		Get_Const_Object(Wrapped) = *thePropView_->Wrapped(Index);
		forThose(J, 0, nbSpans - 1)
		{
			Q.SetValue(Index + 1, J + 1, Wrapped.Face(J));
		}
	}

	GeomAPI_PointsToBSplineSurface Interpolation;
	Interpolation.Interpolate(Q);

	Debug_If_Condition_Message(NOT Interpolation.IsDone(), "interpolation is not performed");

	bladeFaces->SetFace(Interpolation.Surface());

	forThose
	(
		Index,
		0,
		nbSections - 1
	)
	{
		Get_Const_Object(Wrapped) = *thePropView_->Wrapped(Index);
		forThose(J, 0, nbSpans - 1)
			Q.SetValue(Index + 1, J + 1, Wrapped.Back(J));
	}

	Interpolation.Interpolate(Q);

	Debug_If_Condition_Message(NOT Interpolation.IsDone(), "interpolation is not performed");

	bladeFaces->SetBack(Interpolation.Surface());

	theBlade_ = bladeFaces;
}

void AutLib::Leg_Model_PropNo1_Blade::Make()
{
	AllocateMemory();

	CreateProfiles();
	
	CalcXParameters();

	CreateSections_NACA4Digits();

	CreateUnWrappedView();

	CreateWrappedView();

	CreateBladeFaces();
}