#include <Cad3d_TModel.hxx>

#include <Adt_AvlTree.hxx>
#include <Entity3d_Chain.hxx>
#include <Merge3d_Chain.hxx>
#include <GeoProcessor.hxx>
#include <TModel_EntityManager.hxx>
#include <TModel_EntityBlock.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Edge.hxx>
#include <TModel_Ring.hxx>
#include <TModel_Curve.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Shell.hxx>
#include <TModel_Tools.hxx>

#include <iostream>

#include <TopoDS_Shape.hxx>

namespace AutLib
{

	namespace tModel
	{

		Standard_Real squareMaxDistance_1
		(
			const std::shared_ptr<TModel_Edge>& theEdge0,
			const std::shared_ptr<TModel_Edge>& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0->Geometry());
			Debug_Null_Pointer(theEdge1->Geometry());

			const auto& geometry0 = *theEdge0->Geometry();
			const auto& geometry1 = *theEdge1->Geometry();

			return SquareDistance(geometry0.NormalizedParameterValue(0.5), geometry1.NormalizedParameterValue(0.5));
		}

		static void MakeStaticChain
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& Edges,
			Entity3d_Chain& Chain
		)
		{
			auto& Points = Chain.Points();
			auto& Indices = Chain.Connectivity();

			Points.resize(2 * Edges.size());
			Indices.reserve(Edges.size());

			Standard_Integer IP = 0;
			for (const auto& x : Edges)
			{
				Debug_Null_Pointer(x);
				Debug_Null_Pointer(x->Geometry());

				const auto& curve = *x->Geometry();

				Points[IP] = curve.Start();
				IP++;

				Points[IP] = curve.Last();
				IP++;

				connectivity::dual edge;
				edge.Value(0) = IP - 1;
				edge.Value(1) = IP;

				Indices.push_back(edge);
			}
		}

		static void Pairing
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges
		)
		{
			if (theEdges.size() < 2)
			{
				FatalErrorIn("void Pairing(const edgeList& theEdges)")
					<< "Invalid Solid" << endl
					<< abort(FatalError);
			}

			Adt_AvlTree<std::shared_ptr<TModel_Edge>> tree;
			tree.SetComparableFunction(&TModel_Edge::IsLess);

			for (const auto& x : theEdges)
				tree.Insert(x);

			if (tree.IsEmpty())
			{
				FatalErrorIn("void Pairing(const edgeList& theEdges)")
					<< "Invalid Solid" << endl
					<< abort(FatalError);
			}

			std::shared_ptr<TModel_Edge> edge;
			tree.Root(edge);
			tree.Remove(edge);

			while (NOT tree.IsEmpty())
			{
				const auto& vtx0 = edge->Vtx0();
				const auto& vtx1 = edge->Vtx1();

				std::shared_ptr<TModel_Vertex> vtx;
				if (vtx0->NbEdges() <= vtx1->NbEdges())
					vtx = vtx0;
				else
					vtx = vtx1;

				const auto& compareList = vtx->Edges();
				auto v0 = vtx0->Index();
				auto v1 = vtx1->Index();

				if (edge->IsRing())
				{
					auto ring = std::dynamic_pointer_cast<TModel_Ring>(edge);
					Debug_Null_Pointer(ring);

					auto tol2 = ring->Presicion()*ring->Presicion();

					for (const auto& w_compare : compareList)
					{
						auto compare = w_compare.second.lock();
						Debug_Null_Pointer(compare);

						if (compare IS_EQUAL edge) continue;

						auto compareRing = std::dynamic_pointer_cast<TModel_Ring>(compare);
						if (compareRing)
						{
							if (squareMaxDistance_1(ring, compareRing) <= tol2)
							{
								edge->SetPairedEdge(compare);
								compare->SetPairedEdge(edge);

								tree.Remove(compare);
							}
						}
					}
				}
				else
				{
					std::vector<std::shared_ptr<TModel_Edge>> paired;

					Debug_Null_Pointer(edge->Geometry());
					auto tol2 = edge->Presicion()*edge->Presicion();

					for (const auto& w_compare : compareList)
					{
						auto compare = w_compare.second.lock();
						Debug_Null_Pointer(compare);

						if (compare IS_EQUAL edge) continue;

						if (Processor::IsPairedTwoSegments(v0, v1, compare->Vtx0()->Index(), compare->Vtx1()->Index()))
						{
							if (squareMaxDistance_1(edge, compare) <= tol2)
							{
								paired.push_back(compare);
							}

							//paired.push_back(compare);
						}
					}

					/*if (paired.empty())
				{
					cout << "nothing found!" << std::endl;
				}*/
					if (paired.size() > 1)
					{
						if (edge->PairedEdge().lock())
						{
							FatalErrorIn("void Pairing(const edgeList& theEdges)")
								<< "the solid is not a manifold type"
								<< abort(FatalError);
						}
					}

					if (paired.size() IS_EQUAL 1)
					{
						edge->SetPairedEdge(paired[0]);
						paired[0]->SetPairedEdge(edge);
					}
				}

				if (tree.IsEmpty()) break;

				tree.Root(edge);
				tree.Remove(edge);
			}
		}

		static void Assembly
		(
			const Entity3d_Chain& theChain, 
			const std::vector<std::shared_ptr<TModel_Entity>>& theVertices, 
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges
		)
		{
			const auto& Indices = theChain.Connectivity();
			if (theEdges.size() NOT_EQUAL Indices.size())
			{
				FatalErrorIn("void Assembly()")
					<< "Contradictory Data" << endl
					<< abort(FatalError);
			}

			forThose(Index, 0, Indices.size() - 1)
			{
				auto v0 = Indices[Index].Value(0);
				auto v1 = Indices[Index].Value(1);

				auto vtx0 = std::dynamic_pointer_cast<TModel_Vertex>(theVertices[Index_Of(v0)]);
				auto vtx1 = std::dynamic_pointer_cast<TModel_Vertex>(theVertices[Index_Of(v1)]);

				Debug_Null_Pointer(vtx0);
				Debug_Null_Pointer(vtx1);

				Debug_Null_Pointer(theEdges[Index]);

				theEdges[Index]->Vtx0() = vtx0;
				theEdges[Index]->Vtx1() = vtx1;

				theEdges[Index]->SetIndex(Index + 1);

				if (v0 IS_EQUAL v1)
				{
					//! For ring configuration
					vtx0->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
				}
				else
				{
					vtx0->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
					vtx1->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
				}
			}

			Pairing(theEdges);

			for (const auto& x : theVertices)
			{
				Debug_Null_Pointer(x);

				auto vertex = std::dynamic_pointer_cast<TModel_Vertex>(x);
				Debug_Null_Pointer(vertex);


				const auto& edgesAroundVertex = vertex->Edges();

				for (const auto& edge : edgesAroundVertex)
				{
					Debug_Null_Pointer(edge.second.lock());
					auto x = edge.second.lock();
					vertex->ImportToSurfaces_dup(x->Index(), x->Surface());
				}
			}
		}

		static void MakePointsOnSolid
		(
			const Entity3d_Chain& Chain,
			std::shared_ptr<TModel_EntityManager>& thePointsOnSolid,
			std::vector<std::shared_ptr<TModel_Entity>>& thePts
		)
		{
			const auto& Points = Chain.Points();

			thePts.reserve(Points.size());

			Standard_Integer K = 0;
			for (const auto& x : Points)
			{
				auto vertex = std::make_shared<TModel_Vertex>(++K, x);
				thePts.push_back(vertex);
			}

			auto block = std::make_shared<TModel_EntityBlock>("Default Block Point", thePts);
			thePointsOnSolid = std::make_shared<TModel_EntityManager>("Default Block Point", block);
		}

		static void MakePairedEdges
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges,
			std::shared_ptr<TModel_EntityManager>& thePairedEdges
		)
		{
			Adt_AvlTree<std::shared_ptr<TModel_Edge>> tree;
			tree.SetComparableFunction(&TModel_Edge::IsLess);

			tree.Insert(theEdges);

			std::shared_ptr<TModel_Edge> edge;
			tree.Root(edge);
			tree.Remove(edge);

			std::vector<std::shared_ptr<TModel_Entity>> QPaired;
			Standard_Integer k = 0;

			while (NOT tree.IsEmpty())
			{
				auto w_paired = edge->PairedEdge();
				auto paired = w_paired.lock();

				if (paired)
				{
					tree.Remove(paired);
				}

				auto pairedOnSolid = std::make_shared<TModel_Paired>(++k, edge, paired);
				QPaired.push_back(pairedOnSolid);

				edge->SetPaired(pairedOnSolid);
				if (paired) paired->SetPaired(pairedOnSolid);

				if (tree.IsEmpty()) break;

				tree.Root(edge);
				tree.Remove(edge);
			}

			auto block = std::make_shared<TModel_EntityBlock>("Default Block Edge", QPaired);
			thePairedEdges = std::make_shared<TModel_EntityManager>("Default Block Edge", block);
		}


		static void MarchingOnShell
		(
			const std::shared_ptr<TModel_Surface>& Face,
			Adt_AvlTree<std::shared_ptr<TModel_Surface>>& tree,
			std::vector<std::shared_ptr<TModel_Entity>>& QShell
		)
		{
			tree.Remove(Face);
			QShell.push_back(Face);

			const auto edges = Face->Edges();

			std::vector<std::shared_ptr<TModel_Edge>> pairedList;
			pairedList.reserve(edges.size());

			std::shared_ptr<TModel_Edge> null = nullptr;

			for (const auto& x : edges)
			{
				Debug_Null_Pointer(x);

				pairedList.push_back(x->PairedEdge().lock());
				x->SetPairedEdge(null);
			}

			for (const auto& x : pairedList)
			{
				if (x)
				{
					auto paired = x->PairedEdge().lock();
					if (paired)
					{
						Debug_Null_Pointer(paired->Surface().lock());
						MarchingOnShell(paired->Surface().lock(), tree, QShell);
					}
				}
			}
		}


		static void MakeFaces
		(
			const std::vector<std::shared_ptr<TModel_Surface>>& theList,
			std::shared_ptr<TModel_EntityManager>& theFaces
		)
		{
			std::vector<std::shared_ptr<TModel_Entity>> Faces(theList.size());
			forThose(Index, 0, theList.size() - 1)
				Faces[Index] = theList[Index];

			auto block = std::make_shared<TModel_EntityBlock>("Default Block Surface", Faces);
			theFaces = std::make_shared<TModel_EntityManager>("Default Block Surface", block);
		}


		static void LinkEdges(const std::shared_ptr<TModel_EntityManager>& theEdges)
		{
			Debug_Null_Pointer(theEdges);

			std::vector<std::shared_ptr<TModel_Entity>> edges;
			theEdges->RetrieveTo(edges);

			for (const auto& x : edges)
			{
				Debug_Null_Pointer(x);

				auto paired = std::dynamic_pointer_cast<TModel_Paired>(x);
				Debug_Null_Pointer(paired);

				auto edge0 = paired->Edge0();
				auto edge1 = paired->Edge1();

				if (NOT edge0)
				{
					FatalErrorIn("void LinkEdges(const entityManager_ptr& theEdges)")
						<< "Null pointer has been encountered!" << endl
						<< abort(FatalError);
				}

				if (edge1)
				{
					edge0->SetPairedEdge(edge1);
					edge1->SetPairedEdge(edge0);
				}
			}
		}
	}
}

std::shared_ptr<AutLib::Cad3d_TModel> 
AutLib::Cad3d_TModel::MakeSolid
(
	const TopoDS_Shape& theShape, 
	const Standard_Real theTolerance
)
{
	auto surfaces = TModel_Tools::GetSurfaces(theShape);

	auto solid = MakeSolid(surfaces, theTolerance);

	Debug_Null_Pointer(solid);
	if (solid) solid->SetShape(theShape);

	return std::move(solid);
}

std::shared_ptr<AutLib::Cad3d_TModel> 
AutLib::Cad3d_TModel::MakeSolid
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces,
	const Standard_Real theTolerance
)
{
	auto solid = std::make_shared<Cad3d_TModel>();

	solid->theBoundingBox_ = CalcBoundingBox(theSurfaces);

	const auto tol = theTolerance * solid->theBoundingBox_.Diameter();
	auto EdgesOnSolid = TModel_Tools::RetrieveNonSingularEdges(theSurfaces);

	Standard_Integer K = 0;
	for (auto& x : EdgesOnSolid)
	{
		x->SetIndex(++K);
		x->SetPrecision(tol);
	}

	Entity3d_Chain chain;
	tModel::MakeStaticChain(EdgesOnSolid, chain);

	Merge3d_Chain merge;
	merge.InfoAlg().SetRadius(tol);
	merge.Import(chain);

	merge.Perform();

	const auto& merged = *merge.Merged();

	std::vector<std::shared_ptr<TModel_Entity>> vertices;
	tModel::MakePointsOnSolid(merged, solid->theVertices_, vertices);

	Debug_Null_Pointer(solid->theVertices_);
	
	K = 0;
	for (auto& x : vertices)
	{
		++K;

		Debug_Null_Pointer(x);
		x->SetIndex(K);
		x->SetName("Vertex " + std::to_string(K));
	}

	tModel::Assembly(merged, vertices, EdgesOnSolid);

	tModel::MakePairedEdges(EdgesOnSolid, solid->theEdges_);

	Debug_Null_Pointer(solid->theEdges_);

	tModel::MakeFaces(theSurfaces, solid->theSurfaces_);

	tModel::LinkEdges(solid->theEdges_);

	return std::move(solid);
}