#include <SingularCurve2d_PoleAnIso_Base.hxx>

#include <Geom2d_Curve.hxx>

namespace AutLib
{
	template<>
	static std::shared_ptr<Entity2d_Chain>
		SingularCurve_Pole_Base::Mesh<Geo2d_SizeFunction, Geo2d_MetricFunction>
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_CurveInfo>& theInfo
			)
	{
		if (NOT theCurve)
		{
			FatalErrorIn(FunctionSIG)
				<< "No curve has been loaded!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(theMap);
		Debug_Null_Pointer(theInfo);

		auto chain = std::make_shared<Entity2d_Chain>();
		Debug_Null_Pointer(chain);

		auto& pts = chain->Points();
		pts.reserve(3);

		pts.push_back(theCurve->Value(theU0));
		pts.push_back(theCurve->Value(MEAN(theU0, theU1)));
		pts.push_back(theCurve->Value(theU1));

		auto& indices = chain->Connectivity();
		indices.reserve(2);

		connectivity::dual I0;
		I0.Value(0) = 1;
		I0.Value(1) = 2;
		indices.push_back(I0);

		connectivity::dual I1;
		I1.Value(0) = 2;
		I1.Value(1) = 3;
		indices.push_back(I1);

		return std::move(chain);
	}
}