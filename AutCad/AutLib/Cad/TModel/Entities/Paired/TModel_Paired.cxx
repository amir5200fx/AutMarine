#include <TModel_Paired.hxx>

#include <error.hxx>
#include <OSstream.hxx>

const std::shared_ptr<AutLib::TModel_Edge>& 
AutLib::TModel_Paired::Other
(
	const std::shared_ptr<TModel_Edge>& theEdge
) const
{
	if (theEdge == theEdge0_)
	{
		return theEdge1_;
	}

	if (theEdge == theEdge1_)
	{
		return theEdge0_;
	}

	FatalErrorIn("const std::shared_ptr<TModel_Edge>& Other(const std::shared_ptr<TModel_Edge>& theEdge) const")
		<< "Invalid Data" << endl
		<< abort(FatalError);

	return theEdge0_;
}