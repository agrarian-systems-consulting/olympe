//---------------------------------------------------------------------------

#ifndef TVDonProcH
#define TVDonProcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTVDonProcFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TPanel	*PanBas;
	TBitBtn *BtBnRafraichir;
	TTreeView *TV;
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur
	void __fastcall CreeTV(void);

	__fastcall TTVDonProcFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVDonProcFrm *TVDonProcFrm;
//---------------------------------------------------------------------------
#endif
