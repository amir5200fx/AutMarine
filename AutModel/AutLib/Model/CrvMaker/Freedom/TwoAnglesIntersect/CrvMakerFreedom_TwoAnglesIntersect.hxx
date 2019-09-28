#pragma once
#ifndef _CrvMakerFreedom_TwoAnglesIntersect_Header
#define _CrvMakerFreedom_TwoAnglesIntersect_Header

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

	template<class ParamAgl0, class ParamAgl1>
	class CrvMakerFreedom_TwoAnglesIntersect{};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_Constant, CrvMaker_Constant>
		: public CrvMaker_Clamped
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constant> theAngle0_;
		std::shared_ptr<CrvMaker_Constant> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_Constant>& theAngle0,
			const std::shared_ptr<CrvMaker_Constant>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		Standard_Real Value0() const;

		Standard_Real Value1() const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_Constant, CrvMaker_FixedParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constant> theAngle0_;
		std::shared_ptr<CrvMaker_FixedParameter> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_Constant>& theAngle0,
			const std::shared_ptr<CrvMaker_FixedParameter>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FixedParameter>& Angle1() const
		{
			return theAngle1_;
		}

		Standard_Real Value0() const;

		Standard_Real Value1() const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_FixedParameter, CrvMaker_Constant>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FixedParameter> theAngle0_;
		std::shared_ptr<CrvMaker_Constant> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_FixedParameter>& theAngle0,
			const std::shared_ptr<CrvMaker_Constant>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FixedParameter>& Angle0() const
		{
			return theAngle0_;
		}

		Standard_Real Value0() const;

		Standard_Real Value1() const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_Constant, CrvMaker_FixedParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constant> theAngle0_;
		std::shared_ptr<CrvMaker_FixedParameter> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_Constant>& theAngle0,
			const std::shared_ptr<CrvMaker_FixedParameter>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FixedParameter>& Angle1() const
		{
			return theAngle1_;
		}

		Standard_Real Value0() const;

		Standard_Real Value1() const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_FreeParameter, CrvMaker_Constant>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FreeParameter> theAngle0_;
		std::shared_ptr<CrvMaker_Constant> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_FreeParameter>& theAngle0,
			const std::shared_ptr<CrvMaker_Constant>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FreeParameter>& Angle0() const
		{
			return theAngle0_;
		}

		Standard_Real Value0(const Standard_Real x) const;

		Standard_Real Value1() const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_Constant, CrvMaker_FreeParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constant> theAngle0_;
		std::shared_ptr<CrvMaker_FreeParameter> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_Constant>& theAngle0,
			const std::shared_ptr<CrvMaker_FreeParameter>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FreeParameter>& Angle1() const
		{
			return theAngle1_;
		}

		Standard_Real Value0() const;

		Standard_Real Value1(const Standard_Real x) const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_FixedParameter, CrvMaker_FixedParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FixedParameter> theAngle0_;
		std::shared_ptr<CrvMaker_FixedParameter> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_FixedParameter>& theAngle0,
			const std::shared_ptr<CrvMaker_FixedParameter>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FixedParameter>& Angle0() const
		{
			return theAngle0_;
		}

		const std::shared_ptr<CrvMaker_FixedParameter>& Angle1() const
		{
			return theAngle1_;
		}

		Standard_Real Value0() const;

		Standard_Real Value1() const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_FixedParameter, CrvMaker_FreeParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FixedParameter> theAngle0_;
		std::shared_ptr<CrvMaker_FreeParameter> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_FixedParameter>& theAngle0,
			const std::shared_ptr<CrvMaker_FreeParameter>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FixedParameter>& Angle0() const
		{
			return theAngle0_;
		}

		const std::shared_ptr<CrvMaker_FreeParameter>& Angle1() const
		{
			return theAngle1_;
		}

		Standard_Real Value0() const;

		Standard_Real Value1(const Standard_Real x) const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_FreeParameter, CrvMaker_FixedParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FreeParameter> theAngle0_;
		std::shared_ptr<CrvMaker_FixedParameter> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_FreeParameter>& theAngle0,
			const std::shared_ptr<CrvMaker_FixedParameter>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FreeParameter>& Angle0() const
		{
			return theAngle0_;
		}

		const std::shared_ptr<CrvMaker_FixedParameter>& Angle1() const
		{
			return theAngle1_;
		}

		Standard_Real Value0(const Standard_Real x) const;

		Standard_Real Value1() const;
	};

	template<>
	class CrvMakerFreedom_TwoAnglesIntersect<CrvMaker_FreeParameter, CrvMaker_FreeParameter>
		: public CrvMaker_Freedom
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_FreeParameter> theAngle0_;
		std::shared_ptr<CrvMaker_FreeParameter> theAngle1_;

	public:

		CrvMakerFreedom_TwoAnglesIntersect
		(
			const std::shared_ptr<CrvMaker_FreeParameter>& theAngle0,
			const std::shared_ptr<CrvMaker_FreeParameter>& theAngle1
		)
			: theAngle0_(theAngle0)
			, theAngle1_(theAngle1)
		{}

		const std::shared_ptr<CrvMaker_FreeParameter>& Angle0() const
		{
			return theAngle0_;
		}

		const std::shared_ptr<CrvMaker_FreeParameter>& Angle1() const
		{
			return theAngle1_;
		}

		Standard_Real Value0(const Standard_Real x) const;

		Standard_Real Value1(const Standard_Real x) const;
	};
}

#endif // !_CrvMakerFreedom_TwoAnglesIntersect_Header
