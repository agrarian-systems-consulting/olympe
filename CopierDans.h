//---------------------------------------------------------------------------

#ifndef CopierDansH
#define CopierDansH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCopierDansFrm: public TForm {
	__published: // Composants gérés par l'EDI
TEdit	*EdNom;
	TLabel *LabAncNom;
	TLabel *LabCategorie;
	TCheckListBox *ChLB;
	TPanel *PanBas;
	TBitBtn *BtOk;
	TBitBtn *BtAnnuler;
	TRadioGroup *RGCat;
	void __fastcall BtAnnulerClick(TObject *Sender);
	void __fastcall BtOkClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall RGCatClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	bool __fastcall VerifNom(void);
	bool __fastcall SansDouble(AnsiString newNom,CL_Categorie *cat);

public:// Déclarations de l'utilisateur
	bool Retour;
	AnsiString NewNom;
	CL_Atelier *Atelier;
	void __fastcall EntrerNom(CL_Atelier *atelier);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LabAncNom;
	AnsiString LC_RGCat;
	AnsiString LC_BtBnCopier_A;
	AnsiString LC_LabCategorie;

//--

	__fastcall TCopierDansFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCopierDansFrm *CopierDansFrm;
//---------------------------------------------------------------------------
#endif
