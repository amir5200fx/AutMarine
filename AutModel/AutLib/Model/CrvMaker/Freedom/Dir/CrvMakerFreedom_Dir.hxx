#pragma once
#ifndef _CrvMakerDof_Dir_Header
#define _CrvMakerDof_Dir_Header

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
	class CrvMakerDof_Dir
		: public CrvMaker_Dof
	{

		/*Private Data*/

		std::shared_ptr<ParamType> theParameter_;

	public:

		CrvMakerDof_Dir
		(
			const std::shared_ptr<ParamType>& theParameter
		)
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
	class CrvMakerDof_Dir<CrvMaker_Constatnt, FreeDim>
		: public CrvMaker_Clamped
	{

		/*Private Data*/

		std::shared_ptr<CrvMaker_Constatnt> theParameter_;

	public:

		CrvMakerDof_Dir
		(
			const std::shared_ptr<CrvMaker_Constatnt>& theParameter
		)
			: theParameter_(theParameter)
		{}

		void SetParameter(const std::shared_ptr<CrvMaker_Constatnt>& theParameter)
		{
			theParameter_ = theParameter;
		}

		const std::shared_ptr<CrvMaker_Constatnt>& Parameter() const
		{
			return theParameter_;
		}
	};

	namespace CrvMaker
	{
		typedef CrvMakerDof_Dir<CrvMaker_Constatnt, (int)CrvMaker_Dimension::xDirect> xDirClamped;
		typedef CrvMakerDof_Dir<CrvMaker_FreeParameter, (int)CrvMaker_Dimension::xDirect> xDirParameter;
		typedef CrvMakerDof_Dir<CrvMaker_BndParameter, (int)CrvMaker_Dimension::xDirect> xDirBounded;

		typedef CrvMakerDof_Dir<CrvMaker_Constatnt, (int)CrvMaker_Dimension::yDirect> yDirClamped;
		typedef CrvMakerDof_Dir<CrvMaker_FreeParameter, (int)CrvMaker_Dimension::yDirect> yDirParameter;
		typedef CrvMakerDof_Dir<CrvMaker_BndParameter, (int)CrvMaker_Dimension::yDirect> yDirBounded;

	}
}

#endif // !_CrvMakerDof_Dir_Header
