#pragma once
#ifndef _CrvMaker_Node_Header
#define _CrvMaker_Node_Header

#include <CrvMaker_Pole.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	template<class NodeTraits>
	class CrvMaker_Segment;

	template<class NodeTraits>
	class CrvMaker_Node
		: public CrvMaker_Pole
	{

		typedef typename NodeTraits::xDofType xDofType;
		typedef typename NodeTraits::yDofType yDofType;
		typedef typename NodeTraits::paramType paramType;

		/*Private Data*/

		std::shared_ptr<xDofType> theX_;
		std::shared_ptr<yDofType> theY_;

		std::shared_ptr<paramType> theParameter_;

	protected:

		CrvMaker_Node()
		{}

		CrvMaker_Node(const Standard_Integer theIndex)
			: CrvMaker_Pole(theIndex)
		{}

		CrvMaker_Node
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: CrvMaker_Pole(theIndex, theName)
		{}

	public:

		typedef CrvMaker_Segment<NodeTraits> segment;

		const std::shared_ptr<xDofType>& xDof() const
		{
			return theX_;
		}

		std::shared_ptr<xDofType>& xDof()
		{
			return theX_;
		}

		const std::shared_ptr<yDofType>& yDof() const
		{
			return theY_;
		}

		std::shared_ptr<yDofType>& yDof()
		{
			return theY_;
		}

		const std::shared_ptr<paramType>& Parameter() const
		{
			return theParameter_;
		}

		std::shared_ptr<paramType>& Parameter()
		{
			return theParameter_;
		}


		// virtual functions and operators

		virtual Standard_Integer NbSegments() const = 0;

		virtual const std::weak_ptr<segment>& Segment(const Standard_Integer theIndex) const = 0;


		//- override functions and operators

		Standard_Real xValue() const override
		{
			Debug_Null_Pointer(theX_);
			return theX_->Value();
		}

		Standard_Real yValue() const override
		{
			Debug_Null_Pointer(theY_);
			return theY_->Value();
		}

	};
}

#endif // !_CrvMaker_Node_Header
