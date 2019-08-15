#include <GeoProcessor.hxx>

#include <error.hxx>
#include <OSstream.hxx>

//Standard_Boolean 
//AutLib::Processor::IsCcwOrder
//(
//	const std::vector<Pnt2d>& thePts
//)
//{
//	if (thePts.size() < 3)
//	{
//		FatalErrorIn("Standard_Boolean AutLib::Processor::IsCcwOrder(const std::vector<Pnt2d>& thePts)")
//			<< "Invalid Chain: there must be at least 3 points" << endl
//			<< abort(FatalError);
//	}
//
//	Standard_Real sum = 0;
//	Standard_Real sum1 = 0;
//	forThose(Index, 1, thePts.size() - 1)
//	{
//		sum1 += CrossProduct(thePts[Index - 1], thePts[Index]);	
//		const auto& P0 = thePts[Index - 1];
//		const auto& P1 = thePts[Index];
//
//		sum += (P1.X() - P0.X())*(P0.Y() + P1.Y());
//	}
//	sum1 += CrossProduct(thePts[thePts.size() - 1], thePts[0]);
//	const auto& P0 = thePts[thePts.size() - 1];
//	const auto& P1 = thePts[0];
//	//sum += CrossProduct(thePts[thePts.size() - 1], thePts[0]);
//	sum += (P1.X() - P0.X())*(P0.Y() + P1.Y());
//	cout << "sum = " << sum << std::endl;
//	cout << "sum1 = " << sum1 << std::endl;
//	return sum < 0;
//}

AutLib::Pnt2d 
AutLib::Processor::IntersectionTwoLines
(
	const Pnt2d & P0, 
	const Pnt2d & t0,
	const Pnt2d & P1,
	const Pnt2d & t1
)
{
	if (ABS(CrossProduct(t0, t1)) <= 1.0E-12)
	{
		FatalErrorIn("Pnt2d IntersectionTwoLines(const Pnt2d& P0, const Pnt2d& t0, const Pnt2d& P1, const Pnt2d& t1)")
			<< "Two vectors are parallel" << endl
			<< abort(FatalError);
	}

	auto vcr = P1 - P0;
	auto denom = CrossProduct(t0, t1);
	auto numer = CrossProduct(vcr, t1);

	auto alf = numer / denom;
	auto IP = P0 + alf * t0;

	return std::move(IP);
}