#include <Geo2d_MetricPrcsr.hxx>

#include <Geo_SegmentIntegrand.hxx>
#include <Geo_SegmentIntegrand_Function.hxx>
#include <Numeric_AdaptIntegration.hxx>

namespace AutLib
{

	typedef Geo_SegmentIntegrand_Function<Geo2d_MetricPrcsr, true>
		Geo2d_SegmentIntegrand_Function;
	typedef Geo_SegmentIntegrand<Geo2d_MetricPrcsr> Geo2d_SegmentIntegrand;

	template<>
	Standard_Real Geo2d_MetricPrcsr::CalcUnitDistance
	(
		const Pnt2d& theP0, 
		const Pnt2d& theP1
	) const
	{
		Geo2d_SegmentIntegrand line(theP0, theP1, *this);	
		Geo2d_SegmentIntegrand_Function func(line);

		Debug_Null_Pointer(base::Info());
		auto& inf = *base::Info();
		
		Numeric_AdaptIntegration<Geo2d_SegmentIntegrand_Function> alg(func, 0.0, 1.0, inf);
		alg.Perform();

		Debug_If_Condition_Message(NOT alg.IsDone(), "Integration has not been performed");

		if (NOT inf.IsConverged())
		{
			IterFailedIn(FunctionSIG, inf.NbInitIterations())
				<< "Algorithm is not converged!" << endl
				<< abort(IterFail);
		}
		return inf.Result();
	}
}