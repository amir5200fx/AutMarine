#pragma once
#ifndef _CadOpts_PlnSubdivide_Data_Header
#define _CadOpts_PlnSubdivide_Data_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;
	class CadOpts_PlnIntsctEdgeEdge_Data;

	class CadOpts_PlnSubdivide_Point
	{

		/*Private Data*/

		Standard_Real theParameter_;

		std::weak_ptr<CadOpts_PlnSubdivide_Point> thePair_;

	public:

		CadOpts_PlnSubdivide_Point()
		{}

		CadOpts_PlnSubdivide_Point
		(
			const Standard_Real theParameter
		)
			: theParameter_(theParameter)
		{}

		const std::weak_ptr<CadOpts_PlnSubdivide_Point>& Pair() const
		{
			return thePair_;
		}

		void SetPair(const std::shared_ptr<CadOpts_PlnSubdivide_Point>& thePair)
		{
			thePair_ = thePair;
		}

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter)
	};

	class CadOpts_PlnSubdivide_Segment
	{

		/*Private Data*/

		std::shared_ptr<CadOpts_PlnSubdivide_Point> theEnt1_;
		std::shared_ptr<CadOpts_PlnSubdivide_Point> theEnt2_;

		std::weak_ptr<CadOpts_PlnSubdivide_Segment> thePair_;

	public:

		CadOpts_PlnSubdivide_Segment()
		{}

		const std::weak_ptr<CadOpts_PlnSubdivide_Segment>& Pair() const
		{
			return thePair_;
		}

		void SetPair(const std::shared_ptr<CadOpts_PlnSubdivide_Segment>& thePair)
		{
			thePair_ = thePair;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpts_PlnSubdivide_Point>, Ent1)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpts_PlnSubdivide_Point>, Ent2)
	};

	class CadOpts_PlnSubdivide_Data
		: public Global_Indexed
	{

		/*Private Data*/

		std::vector<std::shared_ptr<CadOpts_PlnSubdivide_Point>> thePoints_;
		std::vector<std::shared_ptr<CadOpts_PlnSubdivide_Segment>> theSegments_;

		const std::shared_ptr<Pln_Edge>& theEdge_;

	public:

		CadOpts_PlnSubdivide_Data
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		)
			: theEdge_(theEdge)
		{}

		Standard_Integer NbPoints() const
		{
			return (Standard_Integer)thePoints_.size();
		}

		Standard_Integer NbSegments() const
		{
			return (Standard_Integer)theSegments_.size();
		}

		const std::vector<std::shared_ptr<CadOpts_PlnSubdivide_Point>>& Points() const
		{
			return thePoints_;
		}

		std::vector<std::shared_ptr<CadOpts_PlnSubdivide_Point>>& Points()
		{
			return thePoints_;
		}

		const std::vector<std::shared_ptr<CadOpts_PlnSubdivide_Segment>>& Segments() const
		{
			return theSegments_;
		}

		std::vector<std::shared_ptr<CadOpts_PlnSubdivide_Segment>>& Segments()
		{
			return theSegments_;
		}

		//- static functions and operators

		static void Split
		(
			const CadOpts_PlnIntsctEdgeEdge_Data& theData, 
			std::shared_ptr<CadOpts_PlnSubdivide_Data>& theSplit1, 
			std::shared_ptr<CadOpts_PlnSubdivide_Data>& theSplit2
		);
	};
}

#endif // !_CadOpts_PlnSubdivide_Data_Header
