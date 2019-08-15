#include <PstreamGlobals.hxx>

namespace AutLib
{

	DynamicList<MPI_Request> PstreamGlobals::IPstream_outstandingRequests_;
	DynamicList<MPI_Request> PstreamGlobals::OPstream_outstandingRequests_;
}