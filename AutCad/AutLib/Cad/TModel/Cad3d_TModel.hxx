#pragma once
#ifndef _Cad3d_TModel_Header
#define _Cad3d_TModel_Header

#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Cad_EntityManager.hxx>
#include <Entity3d_Box.hxx>

class TopoDS_Face;
class TopoDS_Shape;

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class TModel_Vertex;
	class TModel_Paired;
	class TModel_Surface;
	class TModel_Shell;

	class Cad3d_TModel
		: public Global_Indexed
		, public Global_Named
	{

		typedef std::shared_ptr<TModel_Shell> shell_ptr;
		typedef std::vector<shell_ptr> shellList;

		typedef shell_ptr outer;
		typedef std::shared_ptr<shellList> inner;

		/*Private Data*/

		std::shared_ptr<Cad_EntityManager<TModel_Vertex>> theVertices_;
		std::shared_ptr<Cad_EntityManager<TModel_Paired>> theEdges_;
		std::shared_ptr<Cad_EntityManager<TModel_Surface>> theSurfaces_;


		outer theOuter_;
		inner theInner_;

		Entity3d_Box theBoundingBox_;


		//- private functions and operators

		static Entity3d_Box CalcBoundingBox
		(
			const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
		);



	public:


		Cad3d_TModel(const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces);


		const Entity3d_Box& BoundingBox() const
		{
			return theBoundingBox_;
		}

		const std::shared_ptr<Cad_EntityManager<TModel_Vertex>>& Corners() const
		{
			return theVertices_;
		}

		const std::shared_ptr<Cad_EntityManager<TModel_Paired>>& Segments() const
		{
			return theEdges_;
		}

		const std::shared_ptr<Cad_EntityManager<TModel_Surface>>& Faces() const
		{
			return theSurfaces_;
		}

		Standard_Integer NbFreeSegment() const;

		Standard_Boolean hasFreeSegment() const;

		Standard_Integer NbCorners() const
		{
			Debug_Null_Pointer(theEdges_);
			return (Standard_Integer)theEdges_->Size();
		}

		Standard_Integer NbSegments() const
		{
			Debug_Null_Pointer(theEdges_);
			return theEdges_->Size();
		}

		Standard_Integer NbFaces() const
		{
			Debug_Null_Pointer(theSurfaces_);
			return theSurfaces_->Size();
		}

		const outer& OuterShell() const
		{
			return theOuter_;
		}

		const inner& InnerShells() const
		{
			return theInner_;
		}


		//- IO functions and operators

		void ExportCornersToPlt(OFstream& File) const;

		void ExportSegmentsToPlt(OFstream& File) const;

		void ExportFacesToPlt(OFstream& File) const;

		void ExportFreeSegmentsToPlt(OFstream& File) const;


		//- Static functions and operators

		
	};
}

#endif // !_Cad3d_TModel_Header
