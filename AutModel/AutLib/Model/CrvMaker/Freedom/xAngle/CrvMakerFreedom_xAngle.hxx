#pragma once
#ifndef _CrvMakerFreedom_xAngle_Header
#define _CrvMakerFreedom_xAngle_Header

#include <CrvMaker_Freedom.hxx>
#include <CrvMaker_Clamped.hxx>
#include <Standard_TypeDef.hxx>
#include <Global_Bound.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CrvMaker_Constant;
	class CrvMaker_FreeParameter;
	class CrvMaker_FixedParameter;

	template<class Param>
	class CrvMakerFreedom_xAngle{};

	template<>
	class CrvMakerFreedom_xAngle<CrvMaker_Constant>
		: public CrvMaker_Clamped
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constant> theParameter_;

	public:

		CrvMakerFreedom_xAngle
		(
			const std::shared_ptr<CrvMaker_Constant>& theParameter
		)
			: theParameter_(theParameter)
		{}

		Standard_Real Value() const;

	};

	template<>
	class CrvMakerFreedom_xAngle<CrvMaker_FixedParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FixedParameter> theParameter_;

	public:

		CrvMakerFreedom_xAngle
		(
			const std::shared_ptr<CrvMaker_FixedParameter>& theParameter
		)
			: theParameter_(theParameter)
		{}

		const std::shared_ptr<CrvMaker_FixedParameter>& Parameter() const
		{
			return theParameter_;
		}

		Standard_Real Value() const;

	};

	template<>
	class CrvMakerFreedom_xAngle<CrvMaker_FreeParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<realBound> theBoundary_;

		std::shared_ptr<CrvMaker_FreeParameter> theParameter_;

	public:

		CrvMakerFreedom_xAngle
		(
			const std::shared_ptr<realBound>& theBoundary,
			const std::shared_ptr<CrvMaker_FreeParameter>& theParameter
		)
			: theBoundary_(theBoundary)
			, theParameter_(theParameter)
		{}

		const std::shared_ptr<realBound>& Boundary() const
		{
			return theBoundary_;
		}

		const std::shared_ptr<CrvMaker_FreeParameter>& Parameter() const
		{
			return theParameter_;
		}

		Standard_Real Value(const Standard_Real x) const;

	};
}

#endif // !_CrvMakerFreedom_xAngle_Header
