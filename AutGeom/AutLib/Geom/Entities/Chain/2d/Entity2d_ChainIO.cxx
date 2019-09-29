#include <Entity2d_Chain.hxx>

#include <TecPlot.hxx>

namespace AutLib
{
	
	template<>
	void Entity2d_Chain::ExportToPlt(OFstream& File) const
	{
		Io::ExportMesh(thePoints_, theConnectivity_, File);
	}
}