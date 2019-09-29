#include <TModel_Tools.hxx>

#include <Adt_AvlTree.hxx>
#include <TModel_Edge.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Shell.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	namespace tModel
	{

		static void TrackShell
		(
			const std::shared_ptr<TModel_Surface>& theFace,
			Adt_AvlTree<std::shared_ptr<TModel_Surface>>& theRegister,
			std::vector<std::shared_ptr<TModel_Surface>>& theList
		)
		{
			Debug_Null_Pointer(theFace);
			const auto& face = *theFace;

			const auto Edges = face.Edges();
			for (const auto& x : Edges)
			{
				Debug_Null_Pointer(x);

				if (x->IsDegenerated()) continue;

				const auto& paired = x->PairedEdge().lock();

				if (NOT paired) continue;
				Debug_Null_Pointer(paired);

				const auto& neighbor = paired->Surface().lock();
				Debug_Null_Pointer(neighbor);

				if (neighbor NOT_EQUAL theFace AND theRegister.IsContains(neighbor))
				{
					theRegister.Remove(neighbor);
					theList.push_back(neighbor);

					TrackShell(neighbor, theRegister, theList);
				}
			}
		}


		static
			std::shared_ptr<std::vector<std::shared_ptr<TModel_Surface>>>
			TrackShell
			(
				Adt_AvlTree<std::shared_ptr<TModel_Surface>>& theRegister
			)
		{
			if (theRegister.IsEmpty())
			{
				FatalErrorIn("void TrackShell()")
					<< "The register container is empty" << endl
					<< abort(FatalError);
			}

			auto list_ptr = std::make_shared<std::vector<std::shared_ptr<TModel_Surface>>>();
			auto& list = *list_ptr;

			std::shared_ptr<TModel_Surface> root;
			theRegister.Root(root);

			list.push_back(root);

			theRegister.Remove(root);

			TrackShell(root, theRegister, list);

			return std::move(list_ptr);
		}
	}
}

std::shared_ptr<std::vector<std::shared_ptr<AutLib::TModel_Shell>>>
AutLib::TModel_Tools::TrackShells
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	if (theSurfaces.size() < 1)
	{
		FatalErrorIn("shellList TrackShells(const faceList& theFaces)")
			<< "Empty list" << endl
			<< abort(FatalError);
	}

	auto Edges = RetrieveEdges(theSurfaces);

	Adt_AvlTree<std::shared_ptr<TModel_Surface>> Register;
	Register.SetComparableFunction(&TModel_Surface::IsLess);

	Register.Insert(theSurfaces);

	Standard_Integer K = 0;
	auto List_ptr = std::make_shared<std::vector<std::shared_ptr<TModel_Shell>>>();
	auto& List = *List_ptr;
	while (NOT Register.IsEmpty())
	{
		List.push_back(std::make_shared<TModel_Shell>(++K, tModel::TrackShell(Register)));
	}

	return std::move(List_ptr);
}