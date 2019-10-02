#pragma once
#ifndef _CrvMaker_Frame_Header
#define _CrvMaker_Frame_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class NodeTraits>
	class CrvMaker_Node;

	template<class NodeTraits>
	class CrvMaker_Frame
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

	protected:

		CrvMaker_Frame()
		{}

		CrvMaker_Frame(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		CrvMaker_Frame
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex, theName)
		{}

	public:

		virtual Standard_Boolean IsClosed() const = 0;

		virtual Standard_Integer NbNodes() const = 0;

		virtual const std::shared_ptr<CrvMaker_Node<NodeTraits>>& Node(const Standard_Integer theIndex) const = 0;
	};
}

#endif // !_CrvMaker_Frame_Header
