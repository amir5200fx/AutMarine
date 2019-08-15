#include <PstreamReduceOps.hxx>

#include <mpi.h>

#if defined(WM_SP)
#   define MPI_SCALAR MPI_FLOAT
#elif defined(WM_DP)
#   define MPI_SCALAR MPI_DOUBLE
#elif defined(WM_LDP)
#   define MPI_SCALAR MPI_LONG_DOUBLE
#endif

void AutLib::reduce(scalar& Value, const sumOp<scalar>& bop)
{
	if (!Pstream::parRun())
	{
		return;
	}

	if (Pstream::nProcs() <= Pstream::nProcsSimpleSum())
	{
		if (Pstream::master())
		{
			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave();
					slave++
					)
			{
				scalar value;

				if
					(
						MPI_Recv
						(
							&value,
							1,
							MPI_SCALAR,
							Pstream::procID(slave),
							Pstream::msgType(),
							MPI_COMM_WORLD,
							MPI_STATUS_IGNORE
						)
						)
				{
					FatalErrorIn
					(
						"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
					) << "MPI_Recv failed"
						<< AutLib::abort(FatalError);
				}

				Value = bop(Value, value);
			}
		}
		else
		{
			if
				(
					MPI_Send
					(
						&Value,
						1,
						MPI_SCALAR,
						Pstream::procID(Pstream::masterNo()),
						Pstream::msgType(),
						MPI_COMM_WORLD
					)
					)
			{
				FatalErrorIn
				(
					"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
				) << "MPI_Send failed"
					<< AutLib::abort(FatalError);
			}
		}


		if (Pstream::master())
		{
			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave();
					slave++
					)
			{
				if
					(
						MPI_Send
						(
							&Value,
							1,
							MPI_SCALAR,
							Pstream::procID(slave),
							Pstream::msgType(),
							MPI_COMM_WORLD
						)
						)
				{
					FatalErrorIn
					(
						"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
					) << "MPI_Send failed"
						<< AutLib::abort(FatalError);
				}
			}
		}
		else
		{
			if
				(
					MPI_Recv
					(
						&Value,
						1,
						MPI_SCALAR,
						Pstream::procID(Pstream::masterNo()),
						Pstream::msgType(),
						MPI_COMM_WORLD,
						MPI_STATUS_IGNORE
					)
					)
			{
				FatalErrorIn
				(
					"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
				) << "MPI_Recv failed"
					<< AutLib::abort(FatalError);
			}
		}
	}
	else
	{
		scalar sum;
		MPI_Allreduce(&Value, &sum, 1, MPI_SCALAR, MPI_SUM, MPI_COMM_WORLD);
		Value = sum;

		/*
		int myProcNo = Pstream::myProcNo();
		int nProcs = Pstream::nProcs();

		//
		// receive from children
		//
		int level = 1;
		int thisLevelOffset = 2;
		int childLevelOffset = thisLevelOffset/2;
		int childProcId = 0;

		while
		(
		(childLevelOffset < nProcs)
		&& (myProcNo % thisLevelOffset) == 0
		)
		{
		childProcId = myProcNo + childLevelOffset;

		scalar value;

		if (childProcId < nProcs)
		{
		if
		(
		MPI_Recv
		(
		&value,
		1,
		MPI_SCALAR,
		Pstream::procID(childProcId),
		Pstream::msgType(),
		MPI_COMM_WORLD,
		MPI_STATUS_IGNORE
		)
		)
		{
		FatalErrorIn
		(
		"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
		)   << "MPI_Recv failed"
		<< AutLib::abort(FatalError);
		}

		Value = bop(Value, value);
		}

		level++;
		thisLevelOffset <<= 1;
		childLevelOffset = thisLevelOffset/2;
		}

		//
		// send and receive from parent
		//
		if (!Pstream::master())
		{
		int parentId = myProcNo - (myProcNo % thisLevelOffset);

		if
		(
		MPI_Send
		(
		&Value,
		1,
		MPI_SCALAR,
		Pstream::procID(parentId),
		Pstream::msgType(),
		MPI_COMM_WORLD
		)
		)
		{
		FatalErrorIn
		(
		"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
		)   << "MPI_Send failed"
		<< AutLib::abort(FatalError);
		}

		if
		(
		MPI_Recv
		(
		&Value,
		1,
		MPI_SCALAR,
		Pstream::procID(parentId),
		Pstream::msgType(),
		MPI_COMM_WORLD,
		MPI_STATUS_IGNORE
		)
		)
		{
		FatalErrorIn
		(
		"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
		)   << "MPI_Recv failed"
		<< AutLib::abort(FatalError);
		}
		}


		//
		// distribute to my children
		//
		level--;
		thisLevelOffset >>= 1;
		childLevelOffset = thisLevelOffset/2;

		while (level > 0)
		{
		childProcId = myProcNo + childLevelOffset;

		if (childProcId < nProcs)
		{
		if
		(
		MPI_Send
		(
		&Value,
		1,
		MPI_SCALAR,
		Pstream::procID(childProcId),
		Pstream::msgType(),
		MPI_COMM_WORLD
		)
		)
		{
		FatalErrorIn
		(
		"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
		)   << "MPI_Send failed"
		<< AutLib::abort(FatalError);
		}
		}

		level--;
		thisLevelOffset >>= 1;
		childLevelOffset = thisLevelOffset/2;
		}
		*/
	}
}