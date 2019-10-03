#include <GModel_parWire.hxx>

#include <Entity2d_Box.hxx>
#include <GModel_parCurve.hxx>

AutLib::Entity2d_Box 
AutLib::GModel_parWire::CalcParametricBoundingBox() const
{
	const auto& curves = Curves();

	if (curves.empty())
	{
		FatalErrorIn("Entity2d_Box CalcParametricBoundingBox() const")
			<< "the curve list is empty" << endl
			<< abort(FatalError);
	}

	auto iter = curves.cbegin();
	auto box = (*iter)->BoundingBox();
	iter++;

	while (iter NOT_EQUAL curves.cend())
	{
		box = Entity2d_Box::Union(box, (*iter)->BoundingBox());
		iter++;
	}
	return std::move(box);
}

std::vector<std::shared_ptr<AutLib::GModel_parCurve>> 
AutLib::GModel_parWire::RetrieveCurves
(
	const std::vector<std::shared_ptr<GModel_parWire>>& theWires
)
{
	std::vector<std::shared_ptr<GModel_parCurve>> merged;
	Standard_Integer nbCurves = 0;
	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		nbCurves += x->NbCurves();
	}

	for (const auto& x : theWires)
	{
		Debug_Null_Pointer(x);
		const auto& curves = x->Curves();

		for (const auto& icurve : curves)
		{
			Debug_Null_Pointer(icurve);
			merged.push_back(icurve);
		}
	}
	return std::move(merged);
}