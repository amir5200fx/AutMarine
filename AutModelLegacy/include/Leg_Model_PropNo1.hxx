#pragma once
#ifndef _Leg_Model_PropNo1_Header
#define _Leg_Model_PropNo1_Header

#include <Global_AccessMethod.hxx>
#include <Leg_Model_Propeller.hxx>

namespace AutLib
{

	// Forward Declarations
	class Leg_PropNo1_Parameters;
	struct Leg_PropNo1_Xparams;
	struct Leg_PropNo1_Profile;
	class Leg_Prop_PropView;
	class Leg_Prop_BladeFace;

	class Leg_Model_PropNo1_Blade
		: public Leg_Model_Propeller
	{

		/*Private Data*/

		std::shared_ptr<Leg_PropNo1_Parameters> theParameters_;

		std::shared_ptr<Leg_PropNo1_Xparams> theXparams_;

		std::shared_ptr<Leg_PropNo1_Profile> theProfiles_;

		std::shared_ptr<Leg_Prop_PropView> thePropView_;

		std::shared_ptr<Leg_Prop_BladeFace> theBlade_;



		void AllocateMemory();


		/* Calculate Parameters */

		void CalcXSections();

		void CalcXPitch();

		void CalcXSkew();

		void CalcXChord();

		void CalcXCamber();

		void CalcXThickness();

		void CalcXRake();

		void CalcXParameters();

		/* Create Profiles*/

		void CreatePitchProfile();

		void CreateChordProfile();

		void CreateSkewProfile();

		void CreateCamberProfile();

		void CreateThicknessProfile();

		void CreateRakeProfile();

		void CreateProfiles();

		/* Create Sections */

		void CreateSections_NACA4Digits();

		void CreateSectionProfiles_NACA4Digits(const Standard_Integer section);

		void CreateExpandedView
		(
			const Standard_Integer Section, 
			const std::vector<Pnt2d>& theTF, 
			const std::vector<Pnt2d>& theTB
		);

		void CreateUnWrappedView();

		void CreateWrappedView();

		void CreateBladeFaces();

	public:

		Leg_Model_PropNo1_Blade();

		const std::shared_ptr<Leg_Prop_BladeFace>& Blade() const
		{
			return theBlade_;
		}

		virtual void Make();

		void PerformToPreview() override
		{

		}

		//- Macros

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Leg_PropNo1_Parameters>, Parameters)			
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Leg_PropNo1_Profile>, Profiles)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Leg_Prop_PropView>, PropView)

	private:

		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Leg_PropNo1_Xparams>, Xparams)
	};
}

#endif // !_Leg_Model_PropNo1_Header
