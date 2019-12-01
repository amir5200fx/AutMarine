#include <CadOpts_PlnSubdivide_Data.hxx>

#include <CadOpts_PlnIntsct_Data.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void AutLib::CadOpts_PlnSubdivide_Data::Split
(
	const CadOpts_PlnIntsctEdgeEdge_Data& theData,
	std::shared_ptr<CadOpts_PlnSubdivide_Data>& theSplit1,
	std::shared_ptr<CadOpts_PlnSubdivide_Data>& theSplit2
)
{
	auto sp1 = std::make_shared<CadOpts_PlnSubdivide_Data>(theData.Edge1());
	Debug_Null_Pointer(sp1);
	auto sp2 = std::make_shared<CadOpts_PlnSubdivide_Data>(theData.Edge2());
	Debug_Null_Pointer(sp2);

	if (theData.NbPoints())
	{
		// edge 1
		auto& pts1 = sp1->Points();
		for (const auto& x : theData.Points())
		{
			Debug_Null_Pointer(x);
			const auto& pt = *x;
			
			auto IP = std::make_shared<CadOpts_PlnSubdivide_Point>();
			Debug_Null_Pointer(IP);

			IP->SetParameter(pt.Parameter1());

			pts1.push_back(std::move(IP));
		}

		// edge 2
		auto& pts2 = sp2->Points();
		for (const auto& x : theData.Points())
		{
			Debug_Null_Pointer(x);
			const auto& pt = *x;

			auto IP = std::make_shared<CadOpts_PlnSubdivide_Point>();
			Debug_Null_Pointer(IP);

			IP->SetParameter(pt.Parameter2());

			pts2.push_back(std::move(IP));
		}

		forThose(Index, 0, theData.NbPoints() - 1)
		{
			pts1[Index]->SetPair(pts2[Index]);
			pts2[Index]->SetPair(pts1[Index]);
		}
	}
	
	if (theData.NbSegments())
	{
		// edge1
		auto& segments1 = sp1->Segments();
		for (const auto& x : theData.Segments())
		{
			Debug_Null_Pointer(x);
			const auto& seg = *x;

			auto SG = std::make_shared<CadOpts_PlnSubdivide_Segment>();
			Debug_Null_Pointer(SG);

			auto IP1 = std::make_shared<CadOpts_PlnSubdivide_Point>();
			Debug_Null_Pointer(IP1);
			auto IP2 = std::make_shared<CadOpts_PlnSubdivide_Point>();
			Debug_Null_Pointer(IP2);

			IP1->SetParameter(seg.Ent1()->Parameter1());
			IP2->SetParameter(seg.Ent2()->Parameter1());

			SG->SetEnt1(std::move(IP1));
			SG->SetEnt2(std::move(IP2));
		}

		// edge2
		auto& segments2 = sp2->Segments();
		for (const auto& x : theData.Segments())
		{
			Debug_Null_Pointer(x);
			const auto& seg = *x;

			auto SG = std::make_shared<CadOpts_PlnSubdivide_Segment>();
			Debug_Null_Pointer(SG);

			auto IP1 = std::make_shared<CadOpts_PlnSubdivide_Point>();
			Debug_Null_Pointer(IP1);
			auto IP2 = std::make_shared<CadOpts_PlnSubdivide_Point>();
			Debug_Null_Pointer(IP2);

			if (seg.IsOpposite())
			{
				IP1->SetParameter(seg.Ent1()->Parameter2());
				IP2->SetParameter(seg.Ent2()->Parameter2());

				SG->SetEnt1(std::move(IP2));
				SG->SetEnt2(std::move(IP1));
			}
			else
			{
				IP1->SetParameter(seg.Ent1()->Parameter2());
				IP2->SetParameter(seg.Ent2()->Parameter2());

				SG->SetEnt1(std::move(IP1));
				SG->SetEnt2(std::move(IP2));
			}
		}

		forThose(Index, 0, theData.NbSegments() - 1)
		{
			segments1[Index]->SetPair(segments2[Index]);
			segments2[Index]->SetPair(segments1[Index]);
		}
	}
}