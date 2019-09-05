#pragma once
#ifndef _Mesh_Element_Header
#define _Mesh_Element_Header

#include <Global_AccessMethod.hxx>
#include <Mesh_Entity.hxx>
#include <Mesh_ElementAdaptor.hxx>
#include <Mesh_ElementType.hxx>

#include <memory>

namespace AutLib
{

	template<class ElementTraits, Mesh_ElementType ElmType = Mesh_ElementType_Tetrahedron>
	class Mesh_Element
		: public Mesh_Entity
		, public Mesh_ElementAdaptor<typename ElementTraits::elementType, ElmType>
	{

	public:

		typedef typename ElementTraits::nodeType nodeType;
		typedef typename ElementTraits::edgeType edgeType;
		typedef typename ElementTraits::facetType facetType;
		typedef typename ElementTraits::elementType elementType;

	private:

		/*Private Data*/

		std::shared_ptr<nodeType> theNodes_[4];

		std::shared_ptr<edgeType> theEdges_[6];
		std::shared_ptr<facetType> theFacets_[4];

	public:

		Mesh_Element()
		{}

		Mesh_Element
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode0,
			const std::shared_ptr<nodeType>& theNode1,
			const std::shared_ptr<nodeType>& theNode2,
			const std::shared_ptr<nodeType>& theNode3
		)
			: Mesh_Entity(theIndex)
		{
			Node0() = theNode0;
			Node1() = theNode1;
			Node2() = theNode2;
			Node3() = theNode3;
		}

		Point Centre() const
		{
			Point pt = 
				(Node0()->Coord() + Node1()->Coord() + Node2()->Coord() + Node3()->Coord())
				/ (Standard_Real)4.0;
			return std::move(pt);
		}

		//- Static function and operators

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<Mesh_Element>& theElement0,
				const std::shared_ptr<Mesh_Element>& theElement1
			)
		{
			Debug_Null_Pointer(theElement0);
			Debug_Null_Pointer(theElement1);

			return theElement0->Index() < theElement1->Index();
		}

		//- Marcos

		GLOBAL_ACCESS_VECTOR(std::shared_ptr<nodeType>, Node, 0)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<nodeType>, Node, 1)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<nodeType>, Node, 2)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<nodeType>, Node, 3)

			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 0)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 1)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 2)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 3)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 4)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 5)

			GLOBAL_ACCESS_VECTOR(std::shared_ptr<facetType>, Face, 0)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<facetType>, Face, 1)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<facetType>, Face, 2)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<facetType>, Face, 3)
	};

	template<class ElementTraits>
	class Mesh_Element<ElementTraits, Mesh_ElementType_Triangle3D>
		: public Mesh_Entity
	{

	public:

		typedef typename ElementTraits::nodeType nodeType;
		typedef typename ElementTraits::edgeType edgeType;
		typedef typename ElementTraits::facetType facetType;
		typedef typename ElementTraits::elementType elementType;

		typedef typename nodeType::ptType Point;

	private:

		/*Private Data*/

		std::shared_ptr<nodeType> theNodes_[3];

		std::shared_ptr<edgeType> theEdges_[3];

	public:

		Mesh_Element()
		{}

		Mesh_Element
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode0,
			const std::shared_ptr<nodeType>& theNode1,
			const std::shared_ptr<nodeType>& theNode2,
			const std::shared_ptr<nodeType>& theNode3
		)
			: Mesh_Entity(theIndex)
		{
			Node0() = theNode0;
			Node1() = theNode1;
			Node2() = theNode2;
		}

		Point Centre() const
		{
			Point pt = 
				(Node0()->Coord() + Node1()->Coord() + Node2()->Coord()) 
				/ (Standard_Real)3.0;
			return std::move(pt);
		}


		//- Static function and operators


		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<Mesh_Element>& theElement0,
				const std::shared_ptr<Mesh_Element>& theElement1
			)
		{
			Debug_Null_Pointer(theElement0);
			Debug_Null_Pointer(theElement1);

			return theElement0->Index() < theElement1->Index();
		}

		//- Marcos

		GLOBAL_ACCESS_VECTOR(std::shared_ptr<nodeType>, Node, 0)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<nodeType>, Node, 1)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<nodeType>, Node, 2)

			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 0)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 1)
			GLOBAL_ACCESS_VECTOR(std::shared_ptr<edgeType>, Edge, 2)
	};


	template<class ElementTraits>
	class Mesh_Element<ElementTraits, Mesh_ElementType_Triangle2D>
		: public Mesh_Element<ElementTraits, Mesh_ElementType_Triangle3D>
		, public Mesh_ElementAdaptor<typename ElementTraits::elementType, Mesh_ElementType_Triangle2D>
	{

	public:

		typedef typename ElementTraits::nodeType nodeType;
		typedef typename ElementTraits::edgeType edgeType;
		typedef typename ElementTraits::facetType facetType;
		typedef typename ElementTraits::elementType elementType;

		typedef typename nodeType::ptType Point;
		typedef Mesh_Element<ElementTraits, Mesh_ElementType_Triangle3D> base;

	private:

		/*Private Data*/

	public:

		Mesh_Element()
		{}

		Mesh_Element
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Mesh_Element
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode0,
			const std::shared_ptr<nodeType>& theNode1,
			const std::shared_ptr<nodeType>& theNode2,
			const std::shared_ptr<nodeType>& theNode3
		)
			: base(theIndex, theNode0, theNode1, theNode2, theNode3)
		{}

	};


	
}

#endif // !_Mesh_Element_Header
