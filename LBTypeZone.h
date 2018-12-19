//---------------------------------------------------------------------------

#ifndef LBTypeZoneH
#define LBTypeZoneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLBTypeZoneFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LBTypeZone;
	void __fastcall LBTypeZoneClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	void __fastcall AgriDefSimClick(void);
	void __fastcall NouvAgriClick(void);

public:// Déclarations utilisateur
	AnsiString Origine;
	void __fastcall CreeLB(int posG,int posH,int r,CL_Categorie *categorie);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LBTypeZoneFrm;
	__fastcall TLBTypeZoneFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBTypeZoneFrm *LBTypeZoneFrm;
//---------------------------------------------------------------------------
#endif
