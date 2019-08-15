#pragma once
#ifndef _Geom_PrTree_Header
#define _Geom_PrTree_Header

#include <Pnt2d.hxx>
#include <Geom_Search.hxx>
#include <Traits.hxx>

namespace AutLib
{

	enum Geo_Quadrant
	{
		Geo_Quadrant_SW,
		Geo_Quadrant_SE,
		Geo_Quadrant_NW,
		Geo_Quadrant_NE
	};

	inline Geo_Quadrant CalcQuadrant
	(
		const Pnt2d& theCoord,
		const Pnt2d& theCentre
	);


	template<class T>
	class Geom_PrTreeBucket
		: public Stl_List<T>
	{

		/*Private Data*/

	public:

		Geom_PrTreeBucket()
		{}
	};


	// Forward Declarations
	template<class T, int Dim, bool Balanced> class Geom_PrTreeLeaf;
	template<class T, int Dim> class Geom_PrTreeInternalHub;
	template<class Point> class Geom_PrTreeNode;

	template<class T, int Dim, bool Balanced = false>
	class Geom_PrTreeLeafHub
	{};

	template<class T>
	class Geom_PrTreeLeafHub<T, 2, true>
	{

		/*Private Data*/

		typedef Stl_List<Geom_PrTreeLeaf<T, 2, true>*> leafList;

		leafList theSNeighbors_;
		leafList theENeighbors_;
		leafList theNNeighbors_;
		leafList theWNeighbors_;

	public:

		Geom_PrTreeLeafHub()
		{}

		const leafList& SNeighbors() const
		{
			return theSNeighbors_;
		}

		leafList& SNeighbors()
		{
			return theSNeighbors_;
		}

		const leafList& ENeighbors() const
		{
			return theENeighbors_;
		}

		leafList& ENeighbors()
		{
			return theENeighbors_;
		}

		const leafList& NNeighbors() const
		{
			return theNNeighbors_;
		}

		leafList& NNeighbors()
		{
			return theNNeighbors_;
		}

		const leafList& WNeighbors() const
		{
			return theWNeighbors_;
		}

		leafList& WNeighbors()
		{
			return theWNeighbors_;
		}

	};

	template<class Point, int Dim>
	class Geom_PrTreeInternalHub {};

	template<class Point>
	class Geom_PrTreeInternalHub<Point, 2>
	{

		/*Private Data*/
		typedef Geom_PrTreeNode<Point> node;

		node* theSwPtr_;
		node* theSePtr_;
		node* theNePtr_;
		node* theNwPtr_;

	public:

		Geom_PrTreeInternalHub()
			: theSwPtr_(0)
			, theSePtr_(0)
			, theNePtr_(0)
			, theNwPtr_(0)
		{}

		node* Sw() const
		{
			return theSwPtr_;
		}

		node*& Sw()
		{
			return theSwPtr_;
		}

		node* Se() const
		{
			return theSePtr_;
		}

		node*& Se()
		{
			return theSePtr_;
		}

		node* Ne() const
		{
			return theNePtr_;
		}

		node*& Ne()
		{
			return theNePtr_;
		}

		node* Nw() const
		{
			return theNwPtr_;
		}

		node*& Nw()
		{
			return theNwPtr_;
		}
	};

	template<class Point>
	class Geom_PrTreeNode
	{

		/*Private Data*/

		typedef Entity_Box<Point> BoxType;

		BoxType theBox_;

	public:

		Geom_PrTreeNode()
		{}

		Geom_PrTreeNode(const BoxType& theBox)
			: theBox_(theBox)
		{}

		virtual ~Geom_PrTreeNode()
		{}

		const BoxType& Box() const
		{
			return theBox_;
		}

		BoxType& Box()
		{
			return theBox_;
		}
	};

	template<class T, int Dim, bool Balanced>
	class Geom_PrTreeLeaf
		: public Geom_PrTreeNode<typename remove_pointer<T>::type::ptType>
		, public Geom_PrTreeBucket<T>
		, public Geom_PrTreeLeafHub<T, Dim, Balanced>
	{

		/*Private Data*/

	public:

		Geom_PrTreeLeaf()
		{}

		~Geom_PrTreeLeaf() override
		{}
	};

	template<class Point, int Dim>
	class Geom_PrTreeInternal
		: public Geom_PrTreeNode<Point>
		, public Geom_PrTreeInternalHub<Point, Dim>
	{

		/*Private Data*/

	public:

		Geom_PrTreeInternal()
		{}

		~Geom_PrTreeInternal() override
		{}
	};

	class Geom_PrTreeBase
		: public Geom_SearchBase
	{

		/*Private Data*/

		Standard_Integer theNbSubDivide_;

	protected:

		Geom_PrTreeBase()
			: theNbSubDivide_(0)
		{}

		Standard_Integer NbSubdivide() const
		{
			return theNbSubDivide_;
		}

		Standard_Integer& NbSubdivide()
		{
			return theNbSubDivide_;
		}
	};

	struct Geom_PrTreeInfo
	{
		int BUCKET_SIZE;
		int MAX_INNER_SUBDIVIDE;

		Geom_PrTreeInfo()
			: BUCKET_SIZE(8)
			, MAX_INNER_SUBDIVIDE(20)
		{}
	};

	template
		<
		class T,
		bool Balanced = false
		>
		class Geom_PrTree
		: public Geom_PrTreeBase
		, public Geom_Search<T>
		, public Geom_PrTreeInfo
	{

		/*Private Data*/

		typedef typename remove_pointer<T>::type Type;
		typedef typename Type::ptType Point;

		typedef Geom_PrTreeBase Base;
		typedef Geom_Search<T> geom;

		typedef Geom_PrTreeNode<Point> node;
		typedef Geom_PrTreeLeaf<T, (int)Point::dim, Balanced> leafNode;
		typedef Geom_PrTreeInternal<Point, (int)Point::dim> internalNode;
		typedef Entity_Box<Point> boxType;

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		node* theRoot_;

		Standard_Boolean IsFull(const leafNode* t) const
		{
			return t->size() >= BUCKET_SIZE;
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			SwitchToClear(internalNode*& t)
		{
			if (t->Sw()) Clear(t->Sw());
			if (t->Se()) Clear(t->Se());
			if (t->Ne()) Clear(t->Ne());
			if (t->Nw()) Clear(t->Nw());
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			SwitchToClear(internalNode*& t);

		void Clear(node*& t)
		{
			leafNode* leaf =
				dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				delete t;
				t = nullptr;
			}
			else
			{
				internalNode* Internal =
					dynamic_cast<internalNode*>(t);

				SwitchToClear(Internal);
				delete t;
				t = nullptr;
			}
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			SwitchToInsert
			(
				const T& theItem,
				const Point& theCentre,
				const boxType& theBox,
				internalNode*& t
			)
		{
			switch (CalcQuadrant(geom::CoordinateOf(theItem), theCentre))
			{
			case Geo_Quadrant_SW:
				Insert(theItem, theBox.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW), t->Sw());
				break;
			case Geo_Quadrant_SE:
				Insert(theItem, theBox.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE), t->Se());
				break;
			case Geo_Quadrant_NE:
				Insert(theItem, theBox.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE), t->Ne());
				break;
			case Geo_Quadrant_NW:
				Insert(theItem, theBox.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW), t->Nw());
				break;
			}
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			SwitchToInsert
			(
				const T& theItem,
				const Point& theCentre,
				const boxType& theBox,
				internalNode*& t
			);

		void Insert
		(
			const T& theItem,
			const boxType& theBox,
			node*& t
		)
		{
			if (!t)
			{
				leafNode* leaf = new leafNode;
				leaf->Box() = theBox;
				leaf->push_back(theItem);

				t = leaf;

				Base::Increment();
				return;
			}

			leafNode* leaf = dynamic_cast<leafNode*>(t);
			if (leaf)
			{
				if (IsFull(leaf))
				{
					Base::NbSubdivide()++;

					if (NbSubdivide() >= MAX_INNER_SUBDIVIDE)
					{
						FatalErrorIn(FunctionSIG)
							<< " Max Inner Subdivision EXCEEDED: Items are close too much!"
							<< abort(FatalError);
					}

					internalNode* Internal = new internalNode;
					Internal->Box() = std::move(t->Box());

					Base::NbItems() -= BUCKET_SIZE;

					const auto& box = Internal->Box();
					const auto& coord = box.CalcCentre();

					for (const auto& item : *leaf)
					{
						SwitchToInsert(item, coord, box, Internal);
					}

					SwitchToInsert(theItem, coord, box, Internal);

					delete t;
					t = Internal;
				}
				else
				{
					leaf->push_back(theItem);

					Base::Increment();
					return;
				}
			}
			else
			{
				internalNode* Internal =
					dynamic_cast<internalNode*>(t);

				SwitchToInsert
				(
					theItem,
					Internal->Box().CalcCentre(),
					Internal->Box(),
					Internal
				);
			}
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			SwitchToRemove
			(
				const T& theItem,
				internalNode*& t
			)
		{
			switch (CalcQuadrant(geom::CoordinateOf(theItem), t->Box().CalcCentre()))
			{
			case Geo_Quadrant_SW:
				Remove(theItem, t->Sw());
				break;
			case Geo_Quadrant_SE:
				Remove(theItem, t->Se());
				break;
			case Geo_Quadrant_NE:
				Remove(theItem, t->Ne());
				break;
			case Geo_Quadrant_NW:
				Remove(theItem, t->Nw());
				break;
			}
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			SwitchToRemove
			(
				const T& theItem,
				internalNode*& t
			);

		void Remove(const T& theItem, node*& t)
		{
			if (!t)
			{
				FatalErrorIn(FunctionSIG)
					<< "Item is not in tree"
					<< abort(FatalError);
			}

			leafNode* leaf =
				dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				Standard_Integer bSize = leaf->size();
				leaf->remove(theItem);

				if (leaf->size() >= bSize)
				{
					FatalErrorIn(FunctionSIG)
						<< "Item is not in tree"
						<< abort(FatalError);
				}

				Base::Decrement();

				if (leaf->empty())
				{
					delete t;
					t = nullptr;
				}
			}
			else
			{
				internalNode* Internal =
					dynamic_cast<internalNode*>(t);

				SwitchToRemove(theItem, Internal);

				if
					(
						!Internal->Sw() &&
						!Internal->Se() &&
						!Internal->Ne() &&
						!Internal->Nw()
						)
				{
					delete t;
					t = nullptr;
				}
			}
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			SwitchToRetrieveTo
			(
				internalNode* Internal,
				Stl_List<T>& theItems
			) const
		{
			if (Internal->Sw()) RetrieveTo(Internal->Sw(), theItems);
			if (Internal->Se()) RetrieveTo(Internal->Se(), theItems);
			if (Internal->Ne()) RetrieveTo(Internal->Ne(), theItems);
			if (Internal->Nw()) RetrieveTo(Internal->Nw(), theItems);
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			SwitchToRetrieveTo
			(
				internalNode* Internal,
				Stl_List<T>& theItems
			) const;

		void RetrieveTo(node* t, Stl_List<T>& theItems) const
		{
			leafNode* leaf = dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				for (const auto& item : *leaf)
					theItems.push_back(item);
			}
			else
			{
				internalNode* Internal =
					dynamic_cast<internalNode*>(t);

				SwitchToRetrieveTo(Internal, theItems);
			}
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)Point::dim>::value, U
			>
			SwitchToSearch
			(
				const boxType& theRegion,
				internalNode* t,
				Stl_List<T>& theItems
			) const
		{
			if (t->Sw())
			{
				if (theRegion.IsIntersect(t->Sw()->Box()))
					Search(theRegion, t->Sw(), theItems);
			}

			if (t->Se())
			{
				if (theRegion.IsIntersect(t->Se()->Box()))
					Search(theRegion, t->Se(), theItems);
			}

			if (t->Ne())
			{
				if (theRegion.IsIntersect(t->Ne()->Box()))
					Search(theRegion, t->Ne(), theItems);
			}

			if (t->Nw())
			{
				if (theRegion.IsIntersect(t->Nw()->Box()))
					Search(theRegion, t->Nw(), theItems);
			}
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)Point::dim>::value, U
			>
			SwitchToSearch
			(
				const boxType& theRegion,
				internalNode* t,
				Stl_List<T>& theItems
			) const;

		void Search
		(
			const boxType& theBox,
			node* t,
			Stl_List<T>& theItems
		) const
		{
			leafNode* leaf = dynamic_cast<leafNode*>(t);

			if (leaf)
			{
				for (const auto& item : *leaf)
				{
					if (theBox.IsInside(geom::CoordinateOf(item)))
					{
						theItems.push_back(item);
					}
				}
			}
			else
			{
				internalNode* Internal =
					dynamic_cast<internalNode*>(t);

				SwitchToSearch(theBox, Internal, theItems);
			}
		}

	public:

		Geom_PrTree()
			: theRoot_(nullptr)
		{}

		~Geom_PrTree()
		{
			Clear();
		}

		Standard_Integer Size() const
		{
			return Base::NbItems();
		}

		Standard_Boolean IsEmpty() const
		{
			return !theRoot_;
		}

		void InsertToGeometry(const T& theItem)
		{
			Debug_If_Condition_Message
			(
				!geom::CoordinateOf, " No coordinate function for Pr-Tree"
			);
			Insert(theItem, geom::GeometryBoundingBox(), theRoot_);
		}

		void InsertToGeometry(const Stl_Vector<T>& theItems)
		{
			for (const auto& item : theItems)
				InsertToGeometry(item);
		}

		void RemoveFromGeometry(const T& theItem)
		{
			Remove(theItem, theRoot_);
		}

		void RetrieveFromGeometryTo(Stl_List<T>& theItems) const
		{
			RetrieveTo(theRoot_, theItems);
		}

		void RetrieveFromGeometryTo
		(
			Stl_Vector<T>& theItems
		) const
		{
			RetrieveTo(theRoot_, theItems);
		}

		void GeometrySearch
		(
			const Standard_Real theRadius,
			const Point& theCentre,
			Stl_List<T>& theList
		) const
		{
			Search
			(
				Entity_Box<Point>::Box(theCentre, theRadius),
				theRoot_,
				theList
			);
		}

		void GeometrySearch
		(
			const Standard_Real theRadius,
			const Point& theCentre,
			Stl_Vector<T>& theList
		) const
		{
			Search
			(
				Entity_Box<Point>::Box(theCentre, theRadius),
				theRoot_,
				theList
			);
		}

		void GeometrySearch
		(
			const Entity_Box<Point>& theRegion,
			Stl_List<T>& theList
		) const
		{
			Search
			(
				theRegion,
				theRoot_,
				theList
			);
		}

		void GeometrySearch
		(
			const Entity_Box<Point>& theRegion,
			Stl_Vector<T>& theList
		) const
		{
			Search
			(
				theRegion,
				theRoot_,
				theList
			);
		}

		void Clear()
		{
			Clear(theRoot_);
		}

	};
}

#include <Geom_PrTreeI.hxx>

#endif // !_Geom_PrTree_Header
