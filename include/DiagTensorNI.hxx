#pragma once
#include <SphericalTensorN.hxx>
namespace AutLib
{
	template <class Cmpt, int length>
	const char* const DiagTensorN<Cmpt, length>::typeName =
		("diagTensor" + name(length)).c_str();

	template <class Cmpt, int length>
	const DiagTensorN<Cmpt, length> DiagTensorN<Cmpt, length>::zero(0);

	template <class Cmpt, int length>
	const DiagTensorN<Cmpt, length> DiagTensorN<Cmpt, length>::one(1);
}

template<class Cmpt, int length>
inline AutLib::DiagTensorN<Cmpt, length>::DiagTensorN()
{}

template<class Cmpt, int length>
inline AutLib::DiagTensorN<Cmpt, length>::DiagTensorN(const VectorSpace<DiagTensorN<Cmpt, length>, Cmpt, length>& vs)
	: VectorSpace<DiagTensorN<Cmpt, length>, Cmpt, length>(vs)
{}

template<class Cmpt, int length>
inline AutLib::DiagTensorN<Cmpt, length>::DiagTensorN(Istream & is)
	: VectorSpace<DiagTensorN<Cmpt, length>, Cmpt, length>(is)
{}

template<class Cmpt, int length>
inline AutLib::DiagTensorN<Cmpt, length>::DiagTensorN(const Cmpt & tx)
{
	VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::eqOpS(*this, tx, eqOp<Cmpt>());
}

template<class Cmpt, int length>
inline AutLib::DiagTensorN<Cmpt, length> AutLib::DiagTensorN<Cmpt, length>::diag() const
{
	return *this;
}

template<class Cmpt, int length>
inline AutLib::DiagTensorN<Cmpt, length> AutLib::DiagTensorN<Cmpt, length>::T() const
{
	return *this;
}

namespace AutLib
{

	template<class Cmpt, int length>
	inline void DiagTensorN<Cmpt, length>::operator=(const SphericalTensorN<Cmpt, length>& st)
	{
		const Cmpt& s = st.v_[0];
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::eqOpS(*this, s, eqOp<Cmpt>());
	}
}

namespace AutLib
{

	//- Addition of DiagTensorN and DiagTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator+(const DiagTensorN<Cmpt, length>& dt1, const DiagTensorN<Cmpt, length>& dt2)
	{
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::op
		(
			res,
			dt1,
			dt2,
			plusOp<Cmpt>()
		);

		return res;
	}


	//- Addition of DiagTensorN and SphericalTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator+(const DiagTensorN<Cmpt, length>& dt1, const SphericalTensorN<Cmpt, length>& st2)
	{
		const Cmpt& s = st2.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opVS
		(
			res,
			dt1,
			s,
			plusOp<Cmpt>()
		);

		return res;
	}


	//- Addition of SphericalTensorN and DiagTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator+(const SphericalTensorN<Cmpt, length>& st1, const DiagTensorN<Cmpt, length>& dt2)
	{
		const Cmpt& s = st1.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opSV
		(
			res,
			s,
			dt2,
			plusOp<Cmpt>()
		);

		return res;
	}


	//- Subtraction of DiagTensorN and DiagTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator-(const DiagTensorN<Cmpt, length>& dt1, const DiagTensorN<Cmpt, length>& dt2)
	{
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::op
		(
			res,
			dt1,
			dt2,
			minusOp<Cmpt>()
		);

		return res;
	}


	//- Subtraction of DiagTensorN and SphericalTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator-(const DiagTensorN<Cmpt, length>& dt1, const SphericalTensorN<Cmpt, length>& st2)
	{
		const Cmpt& s = st2.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opVS
		(
			res,
			dt1,
			s,
			minusOp<Cmpt>()
		);

		return res;
	}


	//- Subtraction of SphericalTensorN and DiagTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator-(const SphericalTensorN<Cmpt, length>& st1, const DiagTensorN<Cmpt, length>& dt2)
	{
		const Cmpt& s = st1.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opSV
		(
			res,
			s,
			dt2,
			minusOp<Cmpt>()
		);

		return res;
	}


	//- Inner-product between a diagonal tensor and a diagonal tensor
	template <class Cmpt, int length>
	inline typename innerProduct<DiagTensorN<Cmpt, length>, DiagTensorN<Cmpt, length> >::type operator&(const DiagTensorN<Cmpt, length>& dt1, const DiagTensorN<Cmpt, length>& dt2)
	{
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<VectorN<Cmpt, length>::nComponents, 0>::op
		(
			res,
			dt1,
			dt2,
			multiplyOp<Cmpt>()
		);

		return res;
	}


	//- Inner-product between spherical tensor and diagonal tensor
	template <class Cmpt, int length>
	inline typename innerProduct<SphericalTensorN<Cmpt, length>, DiagTensorN<Cmpt, length> >::type operator& (const SphericalTensorN<Cmpt, length>& st1, const DiagTensorN<Cmpt, length>& dt2)
	{
		const Cmpt& s = st1.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<VectorN<Cmpt, length>::nComponents, 0>::opSV
		(
			res,
			s,
			dt2,
			multiplyOp<Cmpt>()
		);

		return res;
	}


	//- Inner-product between diagonal tensor and spherical tensor
	template <class Cmpt, int length>
	inline typename innerProduct<DiagTensorN<Cmpt, length>, SphericalTensorN<Cmpt, length> >::type operator&(const DiagTensorN<Cmpt, length>& dt1, const SphericalTensorN<Cmpt, length>& st2)
	{
		const Cmpt& s = st2.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<VectorN<Cmpt, length>::nComponents, 0>::opVS
		(
			res,
			dt1,
			s,
			multiplyOp<Cmpt>()
		);

		return res;
	}


	//- Inner-product between a diagonal tensor and a vector
	template <class Cmpt, int length>
	inline typename innerProduct<DiagTensorN<Cmpt, length>, VectorN<Cmpt, length> >::type operator&(const DiagTensorN<Cmpt, length>& dt, const VectorN<Cmpt, length>& v)
	{
		VectorN<Cmpt, length> res;
		VectorSpaceOps<VectorN<Cmpt, length>::nComponents, 0>::opVV
		(
			res,
			dt,
			v,
			multiplyOp<Cmpt>()
		);

		return res;
	}



	//- Inner-product between a vector and a tensor
	template <class Cmpt, int length>
	inline typename innerProduct<VectorN<Cmpt, length>, DiagTensorN<Cmpt, length> >::type operator&(const VectorN<Cmpt, length>& v, const DiagTensorN<Cmpt, length>& dt)
	{
		VectorN<Cmpt, length> res;
		VectorSpaceOps<VectorN<Cmpt, length>::nComponents, 0>::opVV
		(
			res,
			v,
			dt,
			multiplyOp<Cmpt>()
		);

		return res;
	}


	//- Division of a scalar by a diagonalTensor
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator/(const scalar s, const DiagTensorN<Cmpt, length>& dt)
	{
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opSV
		(
			res,
			s,
			dt,
			divideOp3<Cmpt, scalar, Cmpt>()
		);

		return res;
	}


	//- Inner Product of a VectorN by an inverse diagonalTensor
	template <class Cmpt, int length>
	inline VectorN<Cmpt, length> operator/(const VectorN<Cmpt, length>& v, const DiagTensorN<Cmpt, length>& dt)
	{
		VectorN<Cmpt, length> res(v);
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::eqOp
		(
			res,
			dt,
			divideEqOp<Cmpt>()
		);

		return res;
	}


	//- Inner Product of a DiagTensorN and an inverse DiagTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator/(const DiagTensorN<Cmpt, length>& dt1, const DiagTensorN<Cmpt, length>& dt2)
	{
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::op
		(
			res,
			dt1,
			dt2,
			divideOp<Cmpt>()
		);

		return res;
	}


	//- Inner Product of a SphericalTensorN and an inverse DiagTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator/ (const SphericalTensorN<Cmpt, length>& st1, const DiagTensorN<Cmpt, length>& dt2)
	{
		const Cmpt& s = st1.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opSV
		(
			res,
			s,
			dt2,
			divideOp<Cmpt>()
		);

		return res;
	}


	//- Inner Product of a DiagTensorN and an inverse SphericalTensorN
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> operator/(const DiagTensorN<Cmpt, length>& dt1, const SphericalTensorN<Cmpt, length>& st2)
	{
		const Cmpt& s = st2.v_[0];
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opVS
		(
			res,
			dt1,
			s,
			divideOp<Cmpt>()
		);

		return res;
	}


	//- Return the inverse of a diagonal tensor
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> inv(const DiagTensorN<Cmpt, length>& dt)
	{
		DiagTensorN<Cmpt, length> res;
		VectorSpaceOps<DiagTensorN<Cmpt, length>::nComponents, 0>::opSV
		(
			res,
			1.0,
			dt,
			divideOp<Cmpt>()
		);

		return res;
	}


	//- Return tensor diagonal
	template <class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> diag(const DiagTensorN<Cmpt, length>& dt)
	{
		return dt;
	}


	//- Return the component sum
	// template <class Cmpt, int length>
	// inline Cmpt sum(const DiagTensorN<Cmpt, length>& dt)
	// {
	//     Cmpt result=Cmpt::zero;
	//     for(register label i=0; i<DiagTensorN<Cmpt, length>::nComponents; i++)
	//     {
	//         result += dt[i];
	//     }
	//     return result;
	// }


	//- Transform the spherical tensor
	//- The components are assumed to be individual scalars
	//- i.e. transform has no effect
	template<class Cmpt, int length>
	inline DiagTensorN<Cmpt, length> transform(const tensor& tt, const DiagTensorN<Cmpt, length>& v)
	{
		return v;
	}

	template<class Cmpt, int length>
	class outerProduct<DiagTensorN<Cmpt, length>, Cmpt>
	{
	public:

		typedef DiagTensorN<Cmpt, length> type;
	};

	template<class Cmpt, int length>
	class outerProduct<Cmpt, DiagTensorN<Cmpt, length> >
	{
	public:

		typedef DiagTensorN<Cmpt, length> type;
	};


	template<class Cmpt, int length>
	class innerProduct<DiagTensorN<Cmpt, length>, DiagTensorN<Cmpt, length> >
	{
	public:

		typedef DiagTensorN<Cmpt, length> type;
	};


	template<class Cmpt, int length>
	class innerProduct<SphericalTensorN<Cmpt, length>, DiagTensorN<Cmpt, length> >
	{
	public:

		typedef DiagTensorN<Cmpt, length> type;
	};


	template<class Cmpt, int length>
	class innerProduct<DiagTensorN<Cmpt, length>, SphericalTensorN<Cmpt, length> >
	{
	public:

		typedef DiagTensorN<Cmpt, length> type;
	};


	template<class Cmpt, int length>
	class innerProduct<VectorN<Cmpt, length>, DiagTensorN<Cmpt, length> >
	{
	public:

		typedef VectorN<Cmpt, length> type;
	};


	template<class Cmpt, int length>
	class innerProduct<DiagTensorN<Cmpt, length>, VectorN<Cmpt, length> >
	{
	public:

		typedef VectorN<Cmpt, length> type;
	};
}