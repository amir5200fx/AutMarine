#pragma once
#ifndef _CrvMakerFreedom_xDir_Header
#define _CrvMakerFreedom_xDir_Header

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
	class CrvMakerFreedom_xDir {};

	template<>
	class CrvMakerFreedom_xDir<CrvMaker_Constant>
		: public CrvMaker_Clamped
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constant> theValue_;

	public:

		CrvMakerFreedom_xDir(const std::shared_ptr<CrvMaker_Constant>& theValue)
			: theValue_(theValue)
		{}

		Standard_Real Value() const;
	};


	template<>
	class CrvMakerFreedom_xDir<CrvMaker_FixedParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FixedParameter> theValue_;

	public:

		CrvMakerFreedom_xDir
		(
			const std::shared_ptr<CrvMaker_FixedParameter>& theValue
		)
			: theValue_(theValue)
		{}

		Standard_Real Value() const;
	};

	template<>
	class CrvMakerFreedom_xDir<CrvMaker_FreeParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<realBound> theBoundary_;

		std::shared_ptr<CrvMaker_FreeParameter> theParameter_;

	public:

		CrvMakerFreedom_xDir
		(
			const std::shared_ptr<realBound>& theBoundary,
			const std::shared_ptr<CrvMaker_FreeParameter>& theParam
		)
			: theBoundary_(theBoundary)
			, theParameter_(theParam)
		{}

		const std::shared_ptr<realBound>& Boundary() const
		{
			return theBoundary_;
		}

		const std::shared_ptr<CrvMaker_FreeParameter>& Parameter() const
		{
			return theParameter_;
		}

		Standard_Real Value(const Standard_Real t) const;
	};
}

#endif // !_CrvMakerFreedom_xDir_Header
