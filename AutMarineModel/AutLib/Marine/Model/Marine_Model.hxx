#pragma once
#ifndef _Marine_Model_Header
#define _Marine_Model_Header

#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Entity3d_Box.hxx>

#include <gp_Ax2.hxx>
#include <TopoDS_Shape.hxx>

#include <memory>

namespace AutLib
{

	class Marine_Model_System
	{

		/*Private Data*/

		gp_Ax2 theSystem_;

	protected:

		gp_Ax2& ChangeSystem()
		{
			return theSystem_;
		}

		void SetSystem(const gp_Ax2& theSys)
		{
			theSystem_ = theSys;
		}

		Marine_Model_System()
		{}

	public:


	};

	class Marine_Model
		: public Global_Indexed
		, public Global_Named
		, public Marine_Model_System
		, public std::enable_shared_from_this<Marine_Model>
	{

		/*Private Data*/

		Entity3d_Box theBoundingBox_;

		TopoDS_Shape theModel_;
		TopoDS_Shape thePreview_;

	protected:

		Marine_Model()
		{}

		Marine_Model(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}


		Entity3d_Box& ChangeBoundingBox()
		{
			return theBoundingBox_;
		}

		TopoDS_Shape& ChangeModel()
		{
			return theModel_;
		}

		TopoDS_Shape& ChangePreviewModel()
		{
			return thePreview_;
		}

	public:

		virtual ~Marine_Model()
		{}

		const Entity3d_Box& BoundingBox() const
		{
			return theBoundingBox_;
		}

		const TopoDS_Shape& Model() const
		{
			return theModel_;
		}

		const TopoDS_Shape& PreviewModel()
		{
			return thePreview_;
		}

		virtual void PerformPreview() = 0;


	};
}

#endif // !_Marine_Model_Header
