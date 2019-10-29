#include <Pln_IntsctTools.hxx>

#include <Geom_ItemSort.hxx>
#include <Pln_IntsctEntity.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void AutLib::Pln_IntsctTools::Sort
(
	std::vector<std::shared_ptr<Pln_IntsctEntity>>& theEntities
)
{
	Geom_ItemSort<std::shared_ptr<Pln_IntsctEntity>> sort(&Pln_IntsctEntity::IsLess);

	sort.Perform(theEntities);
}

void AutLib::Pln_IntsctTools::SubdivideEdge
(
	const std::vector<std::shared_ptr<Pln_IntsctEntity>>& theEntities,
	std::shared_ptr<Pln_CmpEdge>& theC0,
	std::shared_ptr<Pln_CmpEdge>& theC1
)
{
	if (theEntities.empty())
	{
		FatalErrorIn("void SubdivideEdge(const std::vector<std::shared_ptr<Pln_IntsctEntity>>& theEntities, std::shared_ptr<Pln_CmpEdge>& theC0, std::shared_ptr<Pln_CmpEdge>& theC1)")
			<< "Empty list" << endl
			<< abort(FatalError);
	}

	const auto& edge = theEntities[0]->Edge();

	for (const auto& x : theEntities)
	{
		if (x->IsPoint())
		{

		}

		if (x->IsSegment())
		{

		}
	}
}