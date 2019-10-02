#pragma once
#ifndef _CrvMakerDof_Angle_Header
#define _CrvMakerDof_Angle_Header

#include <CrvMaker_Clamped.hxx>
#include <CrvMaker_Dimension.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class CrvMaker_Constatnt;
	class CrvMaker_FreeParameter;
	class CrvMaker_BndParameter;

	template<class ParamType, int FreeDim>
	class CrvMakerDof_Angle
		: public CrvMaker_Dof
	{

		/*Private Data*/

		std::shared_ptr<ParamType> theParameter_;

	public:

		CrvMakerDof_Angle(const std::shared_ptr<ParamType>& theParameter)
			: theParameter_(theParameter)
		{}

		void SetParameter(const std::shared_ptr<ParamType>& theParameter)
		{
			theParameter_ = theParameter;
		}

		const std::shared_ptr<ParamType>& Parameter() const
		{
			return theParameter_;
		}
	};

	template<int FreeDim>
	class CrvMakerDof_Angle<CrvMaker_Constatnt, FreeDim>
		: public CrvMaker_Clamped
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constatnt> theParameter_;

	public:

		CrvMakerDof_Angle(const std::shared_ptr<CrvMaker_Constatnt>& theParameter)
			: theParameter_(theParameter)
		{}

		void SetParameter(const std::shared_ptr<CrvMaker_Constatnt>& theParameter)
		{
			theParameter_ = theParameter;
		}

		const std::shared_ptr<ParamType>& Parameter() const
		{
			return theParameter_;
		}
	};

	namespace CrvMaker
	{
		typedef CrvMakerDof_Angle<CrvMaker_Constatnt, (int)CrvMaker_Dimension::Angle0> angle0Clamped;
		typedef CrvMakerDof_Angle<CrvMaker_FreeParameter, (int)CrvMaker_Dimension::Angle0> angle0Parameter;
		typedef CrvMakerDof_Angle<CrvMaker_BndParameter, (int)CrvMaker_Dimension::Angle0> angle0Bounded;

		typedef CrvMakerDof_Angle<CrvMaker_Constatnt, (int)CrvMaker_Dimension::Angle1> angle1Clamped;
		typedef CrvMakerDof_Angle<CrvMaker_FreeParameter, (int)CrvMaker_Dimension::Angle1> angle1Parameter;
		typedef CrvMakerDof_Angle<CrvMaker_BndParameter, (int)CrvMaker_Dimension::Angle1> angle1Bounded;

	}
}

#endif // !_CrvMakerDof_Angle_Header
