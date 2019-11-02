#pragma once
#ifndef _Mesh_PlnRegion_Header
#define _Mesh_PlnRegion_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	template<class PlnWireType>
	class Mesh_PlnRegion
		: public Global_Indexed
		, public Global_Named
	{

		typedef typedef PlnWireType::plnCurveType plnCurveType;

		typedef std::shared_ptr<PlnWireType> outer;
		typedef std::shared_ptr<std::vector<outer>> inner;
		typedef std::vector<std::shared_ptr<PlnWireType>> wireList;

		/*Private Data*/

		outer theOutter_;
		inner theInner_;

	public:

		Mesh_PlnRegion
		(
			const outer& theOuter,
			const inner& theInner = nullptr
		)
			: theOutter_(theOuter)
			, theInner_(theInner)
		{}

		Mesh_PlnRegion
		(
			const Standard_Integer theIndex,
			const word& theName,
			const outer& theOuter,
			const inner& theInner = nullptr
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theOutter_(theOuter)
			, theInner_(theInner)
		{}

		Standard_Boolean HasHole() const
		{
			return (Standard_Boolean)theInner_;
		}

		Standard_Integer NbHoles() const
		{
			if (!HasHole()) return 0;
			return (Standard_Integer)theInner_->size();
		}

		const inner& Inner() const
		{
			return theInner_;
		}

		const outer& Outer() const
		{
			return theOutter_;
		}

		void RetrieveWiresTo(wireList& theWires) const;

		void ExportToPlt(OFstream& File) const;


		//- Static functions and operators

		template<class WireType>
		static std::shared_ptr<PlnWireType> MakeMeshWire(const WireType& theWire);

	};
}

#endif // !_Mesh_PlnRegion_Header
