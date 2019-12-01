#pragma once
#ifndef _CadOpts_PlnIntsct_Data_Header
#define _CadOpts_PlnIntsct_Data_Header

#include <Pnt2d.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Indexed.hxx>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;

	class CadOpts_PlnIntsctData_Point
	{

		/*private Data*/

		Pnt2d theCoord_;

		Standard_Real theParameter1_;
		Standard_Real theParameter2_;

	public:

		CadOpts_PlnIntsctData_Point()
		{}

		CadOpts_PlnIntsctData_Point
		(
			const Standard_Real theParameter1, 
			const Standard_Real theParameter2,
			const Pnt2d& theCoord
		)
			: theCoord_(theCoord)
			, theParameter1_(theParameter1)
			, theParameter2_(theParameter2)
		{}

		//- Macros

		GLOBAL_ACCESS_SINGLE(Pnt2d, Coord)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter1)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter2)
	};

	class CadOpts_PlnIntsctData_Segment
	{

		/*Private Data*/

		std::shared_ptr<CadOpts_PlnIntsctData_Point> theEnt1_;
		std::shared_ptr<CadOpts_PlnIntsctData_Point> theEnt2_;

		/*Handle(Geom2d_Curve) theGeometry1_;
		Handle(Geom2d_Curve) theGeometry2_;*/

		Standard_Boolean IsOpposite_;

	public:

		CadOpts_PlnIntsctData_Segment()
			: IsOpposite_(Standard_True)
		{}

		Standard_Boolean IsOpposite() const
		{
			return IsOpposite_;
		}

		void SetOpposite(const Standard_Boolean cond)
		{
			IsOpposite_ = cond;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpts_PlnIntsctData_Point>, Ent1)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<CadOpts_PlnIntsctData_Point>, Ent2)

			/*GLOBAL_ACCESS_SINGLE(Handle(Geom2d_Curve), Geometry1)
			GLOBAL_ACCESS_SINGLE(Handle(Geom2d_Curve), Geometry2)*/
	};

	class CadOpts_PlnIntsctEdgeEdge_Data
		: public Global_Indexed
	{

		/*Private Data*/

		std::vector<std::shared_ptr<CadOpts_PlnIntsctData_Point>> thePoints_;
		std::vector<std::shared_ptr<CadOpts_PlnIntsctData_Segment>> theSegments_;

		const std::shared_ptr<Pln_Edge>& theEdge1_;
		const std::shared_ptr<Pln_Edge>& theEdge2_;

	public:

		CadOpts_PlnIntsctEdgeEdge_Data
		(
			const std::shared_ptr<Pln_Edge>& theEdge1,
			const std::shared_ptr<Pln_Edge>& theEdge2
		)
			: theEdge1_(theEdge1)
			, theEdge2_(theEdge2)
		{}

		Standard_Integer NbPoints() const
		{
			return (Standard_Integer)thePoints_.size();
		}

		Standard_Integer NbSegments() const
		{
			return (Standard_Integer)theSegments_.size();
		}

		Standard_Boolean HasIntersection() const
		{
			return (NbPoints()) || (NbSegments());
		}

		const std::shared_ptr<Pln_Edge>& Edge1() const
		{
			return theEdge1_;
		}

		const std::shared_ptr<Pln_Edge>& Edge2() const
		{
			return theEdge2_;
		}

		const std::vector<std::shared_ptr<CadOpts_PlnIntsctData_Point>>& Points() const
		{
			return thePoints_;
		}

		std::vector<std::shared_ptr<CadOpts_PlnIntsctData_Point>>& Points()
		{
			return thePoints_;
		}

		const std::vector<std::shared_ptr<CadOpts_PlnIntsctData_Segment>>& Segments() const
		{
			return theSegments_;
		}

		std::vector<std::shared_ptr<CadOpts_PlnIntsctData_Segment>>& Segments()
		{
			return theSegments_;
		}
	};
}

#endif // !_CadOpts_PlnIntsct_Data_Header
