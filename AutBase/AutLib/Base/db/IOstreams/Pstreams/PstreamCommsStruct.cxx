#include <Pstream.hxx>

#include <boolList.hxx>
#include <token.hxx>

AutLib::Pstream::commsStruct::commsStruct()
	: above_(-1)
	, below_(0)
	, allBelow_(0)
	, allNotBelow_(0)
{
}


AutLib::Pstream::commsStruct::commsStruct
(
	const label above,
	const labelList& below,
	const labelList& allBelow,
	const labelList& allNotBelow
)
	: above_(above)
	, below_(below)
	, allBelow_(allBelow)
	, allNotBelow_(allNotBelow)
{
}


AutLib::Pstream::commsStruct::commsStruct
(
	const label nProcs,
	const label myProcID,
	const label above,
	const labelList& below,
	const labelList& allBelow
)
	: above_(above)
	, below_(below)
	, allBelow_(allBelow)
	, allNotBelow_(nProcs - allBelow.size() - 1)
{
	boolList inBelow(nProcs, false);

	for (AutLib::label belowI = 0; belowI < (allBelow).size(); belowI++)
	{
		inBelow[allBelow[belowI]] = true;
	}

	label notI = 0;
	for (AutLib::label procI = 0; procI < (inBelow).size(); procI++)
	{
		if ((procI != myProcID) && !inBelow[procI])
		{
			allNotBelow_[notI++] = procI;
		}
	}
	if (notI != allNotBelow_.size())
	{
		FatalErrorIn("commsStruct") << "problem!" << AutLib::abort(FatalError);
	}
}

bool AutLib::Pstream::commsStruct::operator==(const commsStruct& comm) const
{
	return
		(
		(above_ == comm.above())
			&& (below_ == comm.below())
			&& (allBelow_ == allBelow())
			&& (allNotBelow_ == allNotBelow())
			);
}


bool AutLib::Pstream::commsStruct::operator!=(const commsStruct& comm) const
{
	return !operator==(comm);
}

namespace AutLib
{
	Ostream& operator<<(Ostream& os, const Pstream::commsStruct& comm)
	{
		os << comm.above_ << token::SPACE
			<< comm.below_ << token::SPACE
			<< comm.allBelow_ << token::SPACE
			<< comm.allNotBelow_;

		os.check
		(
			"Ostream& operator<<(Ostream&, const commsStruct&)"
		);

		return os;
	}
}