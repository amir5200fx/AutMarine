#include <Leg_Model_PropNo1.hxx>

#include <Pnt2d.hxx>
#include <Leg_PropNo1_Parameters.hxx>
#include <Leg_PropNo1_Profiles.hxx>
#include <Leg_Prop_ExpandedView.hxx>
#include <Leg_Prop_PropView.hxx>
#include <Leg_Prop_UnWrappedSection.hxx>
#include <Leg_Prop_WrappedSection.hxx>

void AutLib::Leg_Model_PropNo1_Blade::CreateSections_NACA4Digits()
{
	const auto& params = *Parameters();
	const auto nbSections = params.NbSections();

	forThose(Index, 0, nbSections - 1)
		CreateSectionProfiles_NACA4Digits(Index);
}

void AutLib::Leg_Model_PropNo1_Blade::CreateSectionProfiles_NACA4Digits(const Standard_Integer section)
{
	const auto& params = *Parameters();
	const auto& xParams = *Xparams();

	const auto n = params.NbSpans();
	const auto xCamber = xParams.xMaxCamber[section];
	const auto xCamberPosition = xParams.xMaxCamberPosition[section];

	Standard_Real Yc, Yt, Ypc, x, angle;
	Standard_Real dx = M_PI / (Standard_Real)(n - 1);

	std::vector<Standard_Real> X(n);
	std::vector<Pnt2d> TB(n), TF(n);

	forThose
	(
		Index,
		0,
		n - 2
	)
	{
		X[Index] = 0.5*(1.0 - cos(Index*dx));
	}
	X[n] = (1.0 - params.TEGap()->Value());

	forThose
	(
		Index,
		0,
		n - 1
	)
	{
		if (X[Index] <= xCamberPosition)
		{
			Yc = xCamber * (2 * xCamberPosition*X[Index] - X[Index] * X[Index]) / (xCamberPosition*xCamberPosition);
			Ypc = xCamber * (2 * xCamberPosition - 2 * X[Index]) / (xCamberPosition*xCamberPosition);
		}
		else
		{
			Yc = xCamber * ((1.0 - 2 * xCamberPosition) + 2 * xCamberPosition*X[Index] - X[Index] * X[Index]) / ((1.0 - xCamberPosition)*(1.0 - xCamberPosition));
			Ypc = xCamber * (2 * xCamberPosition - 2 * X[Index]) / ((1.0 - xCamberPosition)*(1.0 - xCamberPosition));
		}

		x = X[Index];

		Standard_Real x2 = x * x;
		Standard_Real x3 = x2 * x;
		Standard_Real x4 = x3 * x;

		Yt = (xParams.xThickness[section] / 0.2)*(0.2969*sqrt(x) - 0.1260*x - 0.3516*x2 + 0.2843*x3 - 0.1015*x4);

		angle = atan(Ypc);

		TB[Index].X() = x * xParams.xChord[section] - Yt * sin(angle);
		TF[Index].X() = x * xParams.xChord[section] + Yt * sin(angle);

		TB[Index].Y() = -Yc - Yt * cos(angle);
		TF[Index].Y() = -Yc + Yt * cos(angle);
	}

	/*Geom_Pnt2d t1 = Geom_Pnt2d(TB[n - 1].X() - TB[n - 2].X(), TB[n - 1].Y() - TB[n - 2].Y());
	Geom_Pnt2d t2 = Geom_Pnt2d(TF[n - 1].X() - TF[n - 2].X(), TF[n - 1].Y() - TF[n - 2].Y());

	Geom_Pnt2d IP = Geometry_Intersect::IntersectionTwoLines(TB[n - 2], t1, TF[n - 2], t2);

	TB[n - 1] = TF[n - 1] = IP;*/

	CreateExpandedView(section, TF, TB);
}

void AutLib::Leg_Model_PropNo1_Blade::CreateExpandedView
(
	const Standard_Integer Section,
	const std::vector<Pnt2d>& theTF,
	const std::vector<Pnt2d>& theTB
)
{
	auto expandedView = std::make_shared<Leg_Prop_ExpandedView>(Parameters()->NbSections());
	auto& expanded = *expandedView;

	const auto& xParams = *Xparams();

	forThose(Index, 0, expanded.Size() - 1)
	{
		expanded.SetX(Index, 0.5*xParams.xChord[Section] - (theTF[Index].X() + xParams.xSkew[Section]));
		expanded.SetXs(Index, 0.5*xParams.xChord[Section] - theTF[Index].X());
		expanded.SetTb(Index, theTB[Index].Y());
		expanded.SetTf(Index, theTF[Index].Y());
		expanded.SetYb(Index, theTB[Index].Y() + xParams.xXCoords[Index]);
		expanded.SetYf(Index, theTF[Index].Y() + xParams.xXCoords[Index]);
	}

	thePropView_->SetExpanded(Section, expandedView);
}

void AutLib::Leg_Model_PropNo1_Blade::CreateUnWrappedView()
{
	const auto& params = *Parameters();
	const auto& xParams = *Xparams();

	const auto nbSections = params.NbSections();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		auto SK = xParams.xSkew[Section];
		auto RK = xParams.xRake[Section];
		auto Pitch = xParams.xPitchAngle[Section];
		auto Chord = xParams.xChord[Section];

		auto UnWrappedSection = std::make_shared<Leg_Prop_UnWrappedSection>(params.NbSpans());
		auto& UnWrapped = *UnWrappedSection;

		forThose
		(
			Index,
			0,
			params.NbSpans() - 1
		)
		{
			auto Xs = thePropView_->Expanded(Section)->Xs(Index);
			auto Tb = thePropView_->Expanded(Section)->Tb(Index);
			auto Tf = thePropView_->Expanded(Section)->Tf(Index);

			UnWrapped.SetBack
			(Index,
				Pnt3d(SK*cos(Pitch) + Xs * cos(Pitch) - Tb * sin(Pitch),
					xParams.xXCoords[Section], SK*sin(Pitch) + RK - Xs * sin(Pitch) - Tb * cos(Pitch)));
			UnWrapped.SetFace
			(Index, 
				Pnt3d(SK*cos(Pitch) + Xs * cos(Pitch) - Tf * sin(Pitch),
					xParams.xXCoords[Section], SK*sin(Pitch) + RK - Xs * sin(Pitch) - Tf * cos(Pitch)));
		}
		thePropView_->SetUnWrapped(Section, UnWrappedSection);
	}
}

void AutLib::Leg_Model_PropNo1_Blade::CreateWrappedView()
{
	const auto& params = *Parameters();
	const auto& xParams = *Xparams();

	const auto nbSections = params.NbSections();
	Pnt3d Point;
	Standard_Real Omega;

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		auto SK = xParams.xSkew[Section];
		auto RK = xParams.xRake[Section];
		auto Pitch = xParams.xPitchAngle[Section];
		auto Chord = xParams.xChord[Section];

		auto WrappedSection = std::make_shared<Leg_Prop_WrappedSection>(params.NbSpans());
		auto& Wrapped = *WrappedSection;

		forThose
		(
			Index,
			0,
			params.NbSpans() - 1
		)
		{
			Standard_Real Xs = thePropView_->Expanded(Section)->Xs(Index);
			Standard_Real Tb = thePropView_->Expanded(Section)->Tb(Index);
			Standard_Real Tf = thePropView_->Expanded(Section)->Tf(Index);

			Point.Z() = SK * sin(Pitch) + Tb * cos(Pitch) - Xs * sin(Pitch);

			Omega = -(-SK * cos(Pitch) + Xs * cos(Pitch) + Tb * sin(Pitch)) / xParams.xXCoords[Section];

			Point.X() = -xParams.xXCoords[Section] * sin(Omega);
			Point.Y() = xParams.xXCoords[Section] * cos(Omega);

			Wrapped.SetBack(Index, Point);

			Point.Z() = SK * sin(Pitch) + Tf * cos(Pitch) - Xs * sin(Pitch);

			Omega = -(-SK * cos(Pitch) + Xs * cos(Pitch) + Tf * sin(Pitch)) / xParams.xXCoords[Section];

			Point.X() = -xParams.xXCoords[Section] * sin(Omega);
			Point.Y() = xParams.xXCoords[Section] * cos(Omega);

			Wrapped.SetFace(Index, Point);
		}

		thePropView_->SetWrapped(Section, WrappedSection);
	}
}