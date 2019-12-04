#include <CadRepair_ApproxSurfMetric.hxx>

#include <Entity_StaticData.hxx>
#include <Entity_Segment.hxx>
#include <Entity_Triangle.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Metric1.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMesh2d_MetricBackground.hxx>
#include <CadRepair_ApproxSurfMetric_Info.hxx>

#include <Geom_Surface.hxx>

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))

namespace AutLib
{

	typedef Entity_StaticData<Pnt2d, connectivity::triple, true>
		staticData;
	typedef Entity_Segment<const Pnt2d&> segmentRef;
	typedef Entity_Triangle<const Pnt2d&> triangle;
	typedef Entity_Segment<Pnt2d> segment;
	typedef std::vector<std::shared_ptr<segment>> segmentList;

	struct ApproxCell
	{
		std::shared_ptr<Entity2d_Polygon> theBoundary_;
		std::shared_ptr<segmentList> thePath_;

		std::shared_ptr<staticData> theMesh_;
	};
}

namespace AutLib
{

	typedef Entity2d_Metric1 metric;
	typedef Entity2d_Box box;

	class SpaceApprx_SurfaceObjectBase
	{

		/*Private Data*/

		const Geom_Surface& thePatch_;

		Standard_Real theTolerance_;
		Standard_Real theDegeneracy_;

	public:

		typedef Pnt2d ptType;

		mutable Standard_Real MaxDeterminant;
		mutable Standard_Real MinDeterminant;

		SpaceApprx_SurfaceObjectBase
		(
			const Geom_Surface& thePatch,
			const Standard_Real theTolerance,
			const Standard_Real theDegeneracy
		)
			: thePatch_(thePatch)
			, theTolerance_(theTolerance)
			, theDegeneracy_(theDegeneracy)
			, MaxDeterminant(0)
			, MinDeterminant(RealLast())
		{}

		const Geom_Surface& Patch() const
		{
			return thePatch_;
		}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		Standard_Real Degeneracy() const
		{
			return theDegeneracy_;
		}

		virtual metric MetricAt
		(
			const Pnt2d& theCoord
		) const
		{
			gp_Vec D1U, D1V;
			gp_Pnt Pt;

			Patch().D1(theCoord.X(), theCoord.Y(), Pt, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			metric M(A, B, C);
			return std::move(M);
		}

		static Standard_Boolean doSubdivide
		(
			const box& theRegion,
			const std::shared_ptr<SpaceApprx_SurfaceObjectBase>& theObject
		)
		{
			Debug_Null_Pointer(theObject);
			const auto& obj = *theObject;

			const auto& p0 = theRegion.P0();
			auto p1 = theRegion.Corner(Box2d_PickAlgorithm_SE);
			const auto& p2 = theRegion.P1();
			auto p3 = theRegion.Corner(Box2d_PickAlgorithm_NW);

			auto m0 = obj.MetricAt(p0);
			auto m1 = obj.MetricAt(p1);
			auto m2 = obj.MetricAt(p2);
			auto m3 = obj.MetricAt(p3);

			auto d0 = m0.Determinant();
			auto d1 = m1.Determinant();
			auto d2 = m2.Determinant();
			auto d3 = m3.Determinant();

			if (d0 > obj.MaxDeterminant) obj.MaxDeterminant = d0;
			if (d1 > obj.MaxDeterminant) obj.MaxDeterminant = d1;
			if (d2 > obj.MaxDeterminant) obj.MaxDeterminant = d2;
			if (d3 > obj.MaxDeterminant) obj.MaxDeterminant = d3;

			if (d0 < obj.MinDeterminant) obj.MinDeterminant = d0;
			if (d1 < obj.MinDeterminant) obj.MinDeterminant = d1;
			if (d2 < obj.MinDeterminant) obj.MinDeterminant = d2;
			if (d3 < obj.MinDeterminant) obj.MinDeterminant = d3;

			auto tol = obj.Tolerance();
			auto deg = 100 * obj.Degeneracy() * obj.Degeneracy();

			auto l01 = metric::Distance(p0, p1, m0);
			auto l10 = metric::Distance(p1, p0, m1);

			if (l10 * l01 < deg) return Standard_True;
			if (TOLERANCE(l01, l10) > tol) return Standard_True;

			auto l02 = metric::Distance(p0, p2, m0);
			auto l20 = metric::Distance(p2, p0, m2);

			if (l20 * l02 < deg) return Standard_True;
			if (TOLERANCE(l02, l20) > tol) return Standard_True;

			auto l03 = metric::Distance(p0, p3, m0);
			auto l30 = metric::Distance(p3, p0, m3);

			if (l30 * l03 < deg) return Standard_True;
			if (TOLERANCE(l03, l30) > tol) return Standard_True;

			auto l12 = metric::Distance(p1, p2, m1);
			auto l21 = metric::Distance(p2, p1, m2);

			if (l21 * l12 < deg) return Standard_True;
			if (TOLERANCE(l12, l21) > tol) return Standard_True;

			auto l23 = metric::Distance(p2, p3, m2);
			auto l32 = metric::Distance(p3, p2, m3);

			if (l32 * l23 < deg) return Standard_True;
			if (TOLERANCE(l23, l32) > tol) return Standard_True;

			auto l13 = metric::Distance(p1, p3, m1);
			auto l31 = metric::Distance(p3, p1, m3);

			if (l31 * l13 < deg) return Standard_True;
			if (TOLERANCE(l13, l31) > tol) return Standard_True;

			return Standard_False;
		}
	};

	template<class SizeMap = void>
	class SpaceApprx_SurfaceObject
		: public SpaceApprx_SurfaceObjectBase
	{
		typedef SpaceApprx_SurfaceObject object;

		/*Private Data*/

		std::shared_ptr<SizeMap> theSize_;

	public:

		SpaceApprx_SurfaceObject
		(
			const Geom_Surface& thePatch,
			const std::shared_ptr<SizeMap>& theMap,
			const Standard_Real theTolerance,
			const Standard_Real theDegeneracy
		)
			: SpaceApprx_SurfaceObjectBase(thePatch, theTolerance, theDegeneracy)
			, theSize_(theMap)
		{}

		const std::shared_ptr<SizeMap>& Map() const
		{
			return theSize_;
		}

		metric MetricAt
		(
			const Pnt2d& theCoord
		) const override
		{
			gp_Vec D1U, D1V;
			gp_Pnt Pt;

			Patch().D1(theCoord.X(), theCoord.Y(), Pt, D1U, D1V);

			auto A = D1U.Dot(D1U);
			auto B = D1U.Dot(D1V);
			auto C = D1V.Dot(D1V);

			const auto h = Map()->Value(theCoord);
			Debug_If_Condition(h <= gp::Resolution());

			const auto landa = 1.0 / (h * h);
			metric M(landa * A, landa * B, landa * C);

			return std::move(M);
		}


	};

	template<>
	class SpaceApprx_SurfaceObject<void>
		: public SpaceApprx_SurfaceObjectBase
	{

		typedef SpaceApprx_SurfaceObject object;

		/*Private Data*/

	public:

		SpaceApprx_SurfaceObject
		(
			const Geom_Surface& thePatch,
			const Standard_Real theTolerance,
			const Standard_Real theDegeneracy
		)
			: SpaceApprx_SurfaceObjectBase(thePatch, theTolerance, theDegeneracy)
		{}

	};
}

#include <Geo_ApprxSpace.hxx>
#include <Geo2d_CdtDelTri.hxx>
#include <Geo2d_DelTri.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Merge_StaticData.hxx>
#include <CadAnalys_ApprxSurfMetricInfo.hxx>

namespace AutLib
{

	typedef Geo_ApprxSpaceNode node;
	typedef Geo_ApprxSpaceLeaf<Pnt2d, (int)Pnt2d::dim> leaf;

	std::shared_ptr<Entity2d_Polygon> GetBoundaryPolygon(const node* theNode)
	{
		auto cell = dynamic_cast<leaf*>(const_cast<node*>(theNode));
		if (NOT cell)
		{
			FatalErrorIn("std::shared_ptr<Entity2d_Polygon> GetBoundaryCell(const node* theNode)")
				<< "the pointer is not a leaf type one" << endl
				<< abort(FatalError);
		}

		auto poly = std::make_shared<Entity2d_Polygon>();
		Debug_Null_Pointer(poly);

		Standard_Integer K = 0;
		if (cell->SNeighbors().size() > 1)
		{
			if (cell->SNeighbors().size() > 2)
			{
				FatalErrorIn("std::shared_ptr<Entity2d_Polygon> GetBoundaryCell(const node* theNode)")
					<< "The leaf is not balanced" << endl
					<< abort(FatalError);
			}
			K += (Standard_Integer)cell->SNeighbors().size();
		}
		if (cell->ENeighbors().size() > 1)
		{
			if (cell->ENeighbors().size() > 2)
			{
				FatalErrorIn("std::shared_ptr<Entity2d_Polygon> GetBoundaryCell(const node* theNode)")
					<< "The leaf is not balanced" << endl
					<< abort(FatalError);
			}
			K += (Standard_Integer)cell->ENeighbors().size();
		}
		if (cell->NNeighbors().size() > 1)
		{
			if (cell->NNeighbors().size() > 2)
			{
				FatalErrorIn("std::shared_ptr<Entity2d_Polygon> GetBoundaryCell(const node* theNode)")
					<< "The leaf is not balanced" << endl
					<< abort(FatalError);
			}
			K += (Standard_Integer)cell->NNeighbors().size();
		}
		if (cell->WNeighbors().size() > 1)
		{
			if (cell->WNeighbors().size() > 2)
			{
				FatalErrorIn("std::shared_ptr<Entity2d_Polygon> GetBoundaryCell(const node* theNode)")
					<< "The leaf is not balanced" << endl
					<< abort(FatalError);
			}
			K += (Standard_Integer)cell->WNeighbors().size();
		}

		auto& Pts = poly->Points();
		Pts.reserve(K + 4);

		Debug_Null_Pointer(cell->Region());
		const auto& box = *cell->Region();

		const auto& P0 = box.P0();
		const auto& P2 = box.P1();
		auto P1 = box.Corner(Box2d_PickAlgorithm_SE);
		auto P3 = box.Corner(Box2d_PickAlgorithm_NW);

		Pts.push_back(P0);
		if (cell->SNeighbors().size() > 1) Pts.push_back(MEAN(P0, P1));
		Pts.push_back(P1);
		if (cell->ENeighbors().size() > 1) Pts.push_back(MEAN(P1, P2));
		Pts.push_back(P2);
		if (cell->NNeighbors().size() > 1) Pts.push_back(MEAN(P2, P3));
		Pts.push_back(P3);
		if (cell->WNeighbors().size() > 1) Pts.push_back(MEAN(P3, P0));

		return std::move(poly);
	}

	metric MetricAt
	(
		const Handle(Geom_Surface)& theSurface,
		const Pnt2d& theP
	)
	{
		auto u = theP.X();
		auto v = theP.Y();

		gp_Vec D1U, D1V;
		gp_Pnt P;
		theSurface->D1(u, v, P, D1U, D1V);

		auto A = D1U.Dot(D1U);
		auto B = D1U.Dot(D1V);
		auto C = D1V.Dot(D1V);

		metric M(A, B, C);
		return std::move(M);
	}

	Standard_Boolean Interpolate
	(
		const Handle(Geom_Surface)& theSurface,
		const segmentRef& s,
		const Standard_Real theDegeneracy,
		const Standard_Real theInvMaxDet,
		Pnt2d& theCoord
	)
	{
		const auto& P0 = s.P0();
		const auto& P1 = s.P1();

		auto m0 = MetricAt(theSurface, P0);
		auto m1 = MetricAt(theSurface, P1);

		auto det0 = m0.Determinant() * theInvMaxDet;
		auto det1 = m1.Determinant() * theInvMaxDet;

		if (det0 > theDegeneracy AND det1 > theDegeneracy)
			return Standard_False;

		if (det0 <= theDegeneracy AND det1 <= theDegeneracy)
			return Standard_False;

		auto t = (theDegeneracy - det0) / (det1 - det0);
		if (t < 0) return Standard_False;
		if (t > 1) return Standard_False;

		theCoord = P0 + t * (P1 - P0);
		return Standard_True;
	}

	void MergingThreePoints
	(
		const Pnt2d& P0,
		const Pnt2d& P1,
		const Pnt2d& P2,
		const Standard_Real theTol,
		Pnt2d& Q0,
		Pnt2d& Q1
	)
	{
		auto tol2 = theTol * theTol;
		if (P0.SquareDistance(P1) > tol2)
		{
			Q0 = P0;
			Q1 = P1;
			return;
		}

		if (P0.SquareDistance(P2) > tol2)
		{
			Q0 = P0;
			Q1 = P2;
			return;
		}

		if (P1.SquareDistance(P2) > tol2)
		{
			Q0 = P1;
			Q1 = P2;
			return;
		}
	}

	std::shared_ptr<Entity2d_Polygon> GetPathFromTriangle
	(
		const Handle(Geom_Surface)& theSurface,
		const triangle& theTriangle,
		const Standard_Real theDegeneracy,
		const Standard_Real theMergTol,
		const Standard_Real theInvMaxDet
	)
	{
		auto seg =
			std::make_shared<Entity2d_Polygon>();

		std::vector<Pnt2d> Pts;
		Pts.reserve(3);

		Pnt2d Coord;
		if (Interpolate(theSurface, theTriangle.Segment(0), theDegeneracy * 10, theInvMaxDet, Coord))
		{
			Pts.push_back(Coord);
		}

		if (Interpolate(theSurface, theTriangle.Segment(1), theDegeneracy * 10, theInvMaxDet, Coord))
		{
			Pts.push_back(Coord);
		}

		if (Interpolate(theSurface, theTriangle.Segment(2), theDegeneracy * 10, theInvMaxDet, Coord))
		{
			Pts.push_back(Coord);
		}

		if (Pts.empty())
		{
			return nullptr;
		}

		Pnt2d Q0, Q1;
		if (Pts.size() > 2)
		{
			MergingThreePoints(Pts[0], Pts[1], Pts[2], theMergTol, Q0, Q1);
		}
		else
		{
			Q0 = Pts[0];
			Q1 = Pts[1];
		}

		auto& points = seg->Points();
		points.resize(2);

		points[0] = Q0;
		points[1] = Q1;
		return std::move(seg);
	}

	std::vector<std::shared_ptr<Entity2d_Polygon>> GetPathFromMesh
	(
		const Handle(Geom_Surface)& theSurface,
		const std::shared_ptr<staticData>& theMesh,
		const Standard_Real theDegeneracy,
		const Standard_Real theMergTol,
		const Standard_Real theInvMaxDet
	)
	{
		const auto& triangles = theMesh->Connectivity();
		const auto& Pts = theMesh->Points();

		std::vector<std::shared_ptr<Entity2d_Polygon>> segList;
		for (const auto& x : triangles)
		{
			const auto& P0 = Pts[Index_Of(x.Value(0))];
			const auto& P1 = Pts[Index_Of(x.Value(1))];
			const auto& P2 = Pts[Index_Of(x.Value(2))];

			triangle t(P0, P1, P2);
			auto path = GetPathFromTriangle(theSurface, t, theDegeneracy, theMergTol, theInvMaxDet);

			if (path)
			{
				segList.push_back(path);
			}
		}
		return std::move(segList);
	}

	void OptMesh
	(
		const Handle(Geom_Surface)& theSurface,
		const std::shared_ptr<staticData>& theMesh
	)
	{
		// the mesh will be optimized here! - not implemented yet
	}

	std::shared_ptr<staticData> GetMeshFromBndPolygon
	(
		const Handle(Geom_Surface)& theSurface,
		const std::shared_ptr<Entity2d_Polygon>& theBndPoly
	)
	{
		Geo2d_DelTri del(theBndPoly->Points());
		del.Triangulate();

		auto mesh = del.Data();
		OptMesh(theSurface, mesh);

		return std::move(mesh);
	}

	std::shared_ptr<staticData> GetMeshFromCell
	(
		const Handle(Geom_Surface)& theSurface,
		const std::vector<Pnt2d>& thePts
	)
	{
		Geo2d_DelTri del(thePts);
		del.Triangulate();

		auto mesh = del.Data();
		OptMesh(theSurface, mesh);

		return std::move(mesh);
	}

	std::shared_ptr<Entity_StaticData<Pnt2d, connectivity::triple, false>>
		GetMeshFromCell
		(
			const Handle(Geom_Surface)& theSurface,
			const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePath,
			const std::vector<Pnt2d>& thePts
		)
	{
		Geo2d_CdtDelTri del(thePts, thePath);
		del.SetToHandleDegeneracy();
		del.Perform();

		auto mesh = del.Data();
		return mesh;
	}

	std::shared_ptr<staticData>
		GetMeshFromCell
		(
			const Handle(Geom_Surface)& theSurface,
			const node* theCell,
			const Standard_Real theDegeneracy,
			const Standard_Real theMergTol,
			const Standard_Real theInvMaxDet
		)
	{
		if (NOT theSurface)
		{
			FatalErrorIn("std::shared_ptr<staticData> GetMeshFromCell()")
				<< "Null surface" << endl
				<< abort(FatalError);
		}

		if (NOT theCell)
		{
			FatalErrorIn("std::shared_ptr<staticData> GetMeshFromCell()")
				<< "Null cell" << endl
				<< abort(FatalError);
		}

		auto boundaryPoly =
			GetBoundaryPolygon(theCell);
		Debug_Null_Pointer(boundaryPoly);

		auto bMesh =
			GetMeshFromBndPolygon(theSurface, boundaryPoly);
		Debug_Null_Pointer(bMesh);

		return std::move(bMesh);
	}

	std::shared_ptr<Entity2d_Triangulation> GetMeshFromSurface
	(
		const Handle(Geom_Surface)& theSurface,
		const Entity2d_Box& theBoundingBox,
		const std::shared_ptr<Geo2d_SizeFunction>& theSizeMap,
		CadRepair_ApproxSurfMetric_Info& theInfo,
		std::shared_ptr<SpaceApprx_SurfaceObjectBase>& obj
	)
	{

		if (theSizeMap)
		{
			obj =
				std::make_shared<SpaceApprx_SurfaceObject<Geo2d_SizeFunction>>
				(
					*theSurface,
					theSizeMap,
					theInfo.Tolerance(),
					theInfo.Degeneracy()
					);
		}
		else
		{
			obj =
				std::make_shared<SpaceApprx_SurfaceObject<>>
				(
					*theSurface,
					theInfo.Tolerance(),
					theInfo.Degeneracy()
					);
		}

		auto info = std::make_shared<Geo_ApprxSpaceInfo>();
		info->Min_Level = theInfo.MinLevel();
		info->Max_Level = theInfo.MaxLevel();

		Geo_ApprxSpace<SpaceApprx_SurfaceObjectBase>
			apprxSurface(theBoundingBox, obj, &SpaceApprx_SurfaceObjectBase::doSubdivide, info);

		apprxSurface.Init();
		apprxSurface.Perform();


		apprxSurface.PostBalancing();

		std::vector<Geo_ApprxSpaceNode*> cells;
		apprxSurface.RetrieveTo(cells);

		std::vector<std::shared_ptr<Entity2d_Triangulation>>
			discretizedCells;
		discretizedCells.reserve(cells.size());

		auto maxInvDet = (Standard_Real)1.0 / obj->MaxDeterminant;

		for (const auto& x : cells)
		{
			Debug_Null_Pointer(x);
			discretizedCells.push_back
			(
				GetMeshFromCell
				(
					theSurface,
					x,
					theInfo.Degeneracy(),
					theInfo.Tolerance(),
					maxInvDet
				)
			);
		}

		/*for (const auto& x : discretizedCells)
			x->ExportToPlt(file);*/

		Merge_StaticData<Entity2d_Triangulation, Merge_PntAlg_Mean>
			merging;

		//merging.SetRemoveDegeneracy();
		merging.InfoAlg().SetRadius(1.0E-6);
		merging.Import(discretizedCells);
		merging.Perform();

		Debug_If_Condition_Message(NOT merging.IsDone(), "The merging is not performed");



		return merging.Merged();
	}

	void ChaeckTriangles(const Entity2d_Triangulation& triangulation)
	{
		const auto& triangles = triangulation.Connectivity();
		for (const auto& x : triangles)
		{
			if (x.IsDegenerated())
			{
				FatalErrorIn("void ChaeckTriangles(const Entity2d_Triangulation& triangulation)")
					<< "Invalid triangle" << endl
					<< abort(FatalError);
			}
		}
	}
}

#include <GeoMesh2d_Data.hxx>
#include <Mesh2d_Element.hxx>
#include <Mesh2d_Node.hxx>

void AutLib::CadRepair_ApproxSurfMetric::Perform()
{
	if (NOT theSurface_)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the surface has not been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT theInfo_)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the info has not been loaded!" << endl
			<< abort(FatalError);
	}

	std::shared_ptr<SpaceApprx_SurfaceObjectBase> obj;

	auto staticData =
		GetMeshFromSurface
		(
			theSurface_,
			theBoundingBox_,
			theSizeFun_,
			*Info(),
			obj
		);
	Debug_Null_Pointer(staticData);

	ChaeckTriangles(*staticData);

	/*fileName filename = "temp.plt";
	OFstream file(filename);

	staticData->ExportToPlt(file);*/

	auto mesh = std::make_shared<GeoMesh2d_Data>();
	Debug_Null_Pointer(mesh);

	mesh->Construct(*staticData);

	std::vector<std::shared_ptr<Mesh2d_Node>> nodes;
	mesh->RetrieveNodesTo(nodes);

	auto metrics_ptr = std::make_shared<std::vector<Entity2d_Metric1>>(nodes.size());
	Debug_Null_Pointer(metrics_ptr);

	auto& metrics = *metrics_ptr;
	const auto& Object = *obj;
	for (const auto& x : nodes)
	{
		metrics[Index_Of(x->Index())] = Object.MetricAt(x->Coord());
	}

	theApprox_ =
		std::make_shared<GeoMesh2d_MetricBackground>(mesh, metrics_ptr);

	ChangeMaxDet() = obj->MaxDeterminant;
	ChangeMinDet() = obj->MinDeterminant;

	if (obj->MinDeterminant < Info()->Degeneracy())
	{
		Change_HasDegeneracy() = Standard_True;
	}

	Change_IsDone() = Standard_True;
}