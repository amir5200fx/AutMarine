
#define ParametricCurve_Pole_Declaration(CurveType, SurfPrefix)						\
	template<> std::shared_ptr<CurveType>											\
	CadSingularity_##SurfPrefix##Detection_Base::ParametricCurve_Pole				\
	(const Pnt2d& theP0, const Pnt2d& theP1)										\
	{																				\
		CadPlnModel_Segment LineSegMaker;											\
		auto pcurve = LineSegMaker(theP0, theP1, sysLib::gl_pln_curve_info);		\
		auto curve = std::make_shared<CadSingularity_PoleCurve<CurveType>>			\
		(																			\
				Cad_Tools::ConvertToBSpline(pcurve->Curve()),						\
				pcurve->FirstParam(),												\
				pcurve->LastParam(),												\
				sysLib::gl_pln_curve_info											\
				);																	\
		curve->SetMid(MEAN(theP0, theP1));											\
		return std::move(curve);													\
	}

#define ParametricCurve_Line_Declaration(CurveType, SurfPrefix)						\
	template<> std::shared_ptr<CurveType>											\
	CadSingularity_##SurfPrefix##Detection_Base::ParametricCurve_Line				\
	(const Pnt2d& theP0, const Pnt2d& theP1)										\
	{																				\
		CadPlnModel_Segment LineSegMaker;											\
		auto pcurve = LineSegMaker(theP0, theP1, sysLib::gl_pln_curve_info);		\
		auto curve = std::make_shared<CadSingularity_LineCurve<CurveType>>			\
		(																			\
				Cad_Tools::ConvertToBSpline(pcurve->Curve()),						\
				pcurve->FirstParam(),												\
				pcurve->LastParam(),												\
				sysLib::gl_pln_curve_info											\
				);																	\
		return std::move(curve);													\
	}