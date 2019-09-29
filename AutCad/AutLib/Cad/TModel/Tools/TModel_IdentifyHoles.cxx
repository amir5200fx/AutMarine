#include <TModel_Tools.hxx>

#include <Adt_AvlTree.hxx>
#include <Entity3d_Box.hxx>
#include <TModel_Shell.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	namespace tModel
	{

		static std::shared_ptr<TModel_Shell> RetrieveShell
		(
			Adt_AvlTree<std::shared_ptr<TModel_Shell>>& theRegister
		)
		{
			if (theRegister.IsEmpty())
			{
				FatalErrorIn("shell_ptr RetrieveShell(Adt_AvlTree<shell_ptr>& theRegister)")
					<< "Empty tree" << endl
					<< abort(FatalError);
			}

			std::shared_ptr<TModel_Shell> root;
			theRegister.Root(root);
			theRegister.Remove(root);

			return std::move(root);
		}

		static void IdentifyHoles
		(
			const std::shared_ptr<TModel_Shell>& InnerCandidate,
			const std::shared_ptr<TModel_Shell>& OuterCandidate,
			std::vector<std::shared_ptr<TModel_Shell>>& QInners,
			std::shared_ptr<TModel_Shell>& theOuter
		)
		{
			if (InnerCandidate)
				QInners.push_back(InnerCandidate);

			if (theOuter)
			{
				if (Entity3d_Box::IsInside(OuterCandidate->BoundingBox(), theOuter->BoundingBox()))
				{
					QInners.push_back(OuterCandidate);
				}
				else
				{
					QInners.push_back(theOuter);
					theOuter = OuterCandidate;
				}
			}
			else
			{
				theOuter = OuterCandidate;
			}
		}


		static void TrackHoles
		(
			Adt_AvlTree<std::shared_ptr<TModel_Shell>>& theRegister,
			std::vector<std::shared_ptr<TModel_Shell>>& QInners,
			std::shared_ptr<TModel_Shell>& theOuter
		)
		{
			if (theRegister.IsEmpty()) return;

			std::shared_ptr<TModel_Shell> Outer;
			std::shared_ptr<TModel_Shell> Inner;

			Outer = RetrieveShell(theRegister);

			if (theRegister.IsEmpty())
			{
				IdentifyHoles(nullptr, Outer, QInners, theOuter);
				return;
			}

			Inner = RetrieveShell(theRegister);

			const auto& OuterBox = Outer->BoundingBox();
			const auto& InnerBox = Inner->BoundingBox();

			if (Entity3d_Box::IsInside(InnerBox, OuterBox))
			{
				IdentifyHoles(Inner, Outer, QInners, theOuter);

				TrackHoles(theRegister, QInners, theOuter);
			}
			else if (Entity3d_Box::IsInside(OuterBox, InnerBox))
			{
				IdentifyHoles(Outer, Inner, QInners, theOuter);

				TrackHoles(theRegister, QInners, theOuter);
			}
			else
			{
				QInners.push_back(Inner);
				QInners.push_back(Outer);

				TrackHoles(theRegister, QInners, theOuter);
			}
		}
	}
}

Standard_Boolean 
AutLib::TModel_Tools::InnerHoles
(
	const std::vector<std::shared_ptr<TModel_Shell>>& theShells,
	std::vector<std::shared_ptr<TModel_Shell>>& theInners,
	std::shared_ptr<TModel_Shell>& theOuter
)
{
	if (theShells.empty())
	{
		FatalErrorIn("void InnerHoles(const shellList& theShells, shellList& theInners, shellList& theOuters)")
			<< "Empty shell list!" << endl
			<< abort(FatalError);
	}

	Adt_AvlTree<std::shared_ptr<TModel_Shell>> Register;
	Register.SetComparableFunction(&TModel_Shell::IsLess);

	Register.Insert(theShells);

	tModel::TrackHoles(Register, theInners, theOuter);

	if (NOT theOuter) return Standard_True;
	return Standard_False;
}