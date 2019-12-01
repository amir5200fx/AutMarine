#pragma once
#ifndef _CadOpts_PlnIntsct_EdgePlane_Header
#define _CadOpts_PlnIntsct_EdgePlane_Header

#include <Global_Done.hxx>
#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace AutLib
{

	// Forward Declarations
	class Pln_Edge;
	class Cad2d_Plane;
	class CadOpts_PlnIntsctEdgeEdge_Data;
	class CadOpts_PlnIntsct_EdgeEdge_Info;

	template<class ObjectSearch>
	class CadOpts_PlnIntsct_EdgePlane
		: public Global_Done
	{

		typedef CadOpts_PlnIntsct_EdgeEdge_Info info;

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge_;
		std::shared_ptr<Cad2d_Plane> thePlane_;

		const std::shared_ptr<info>& theInfo_;

		std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpts_PlnIntsctEdgeEdge_Data>
			>
			theRegister_;

	public:

		CadOpts_PlnIntsct_EdgePlane(const std::shared_ptr<info>& theInfo)
			: theInfo_(theInfo)
		{}

		const std::shared_ptr<Pln_Edge>& Edge() const
		{
			return theEdge_;
		}

		const std::shared_ptr<Cad2d_Plane>& Plane() const
		{
			return thePlane_;
		}

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		const std::map
			<
			Standard_Integer,
			std::shared_ptr<CadOpts_PlnIntsctEdgeEdge_Data>
			>& Register() const
		{
			return theRegister_;
		}

		Standard_Boolean HasIntersection() const
		{
			return (Standard_Boolean)theRegister_.size();
		}

		void Perform();

		void LoadEdge(const std::shared_ptr<Pln_Edge>& theEdge)
		{
			theEdge_ = theEdge;
		}

		void LoadPlane(const std::shared_ptr<Cad2d_Plane>& thePlane)
		{
			thePlane_ = thePlane;
		}
	};
}

#include <CadOpts_PlnIntsct_EdgePlaneI.hxx>

#endif // !_CadOpts_PlnIntsct_EdgePlane_Header
