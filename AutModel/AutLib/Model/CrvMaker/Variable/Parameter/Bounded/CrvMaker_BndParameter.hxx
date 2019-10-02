#pragma once
#ifndef _CrvMaker_BndParameter_Header
#define _CrvMaker_BndParameter_Header

#include <CrvMaker_Parameter.hxx>
#include <Global_Bound.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	class CrvMaker_BndParameter
		: public CrvMaker_Parameter
		, public Global_Bound<Standard_Real>
	{

		/*Private Data*/

		Standard_Real theValue_;

	public:

		CrvMaker_BndParameter
		(
			const Standard_Real theLower,
			const Standard_Real theUpper
		)
			: Global_Bound<Standard_Real>(theLower, theUpper)
		{
			Update(MEAN(theLower, theUpper));
		}

		void Update(const Standard_Real x)
		{
			if (NOT IsInside(x))
			{
				FatalErrorIn("void Update(const Standard_Real x)")
					<< "Invalid parameter: " << x << endl
					<< "- lower: " << Lower() << endl
					<< "- upper: " << Upper() << endl
					<< abort(FatalError);
			}

			theValue_ = Lower() + x * (Upper() - Lower());
		}

		// override functions

		Standard_Real Value() const override
		{
			return theValue_;
		}
	};
}

#endif // !_CrvMaker_BndParameter_Header
