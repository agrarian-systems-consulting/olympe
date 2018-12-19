//---------------------------------------------------------------------------

#ifndef AppelFctH
#define AppelFctH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TAppelFctFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TPanel	*PanB2;
	TPanel *PanH1;
	TBitBtn *BtBnDico;
	TOpenDialog *OpenDialog;
	TBitBtn *BtBnALancer;
	TLabel *Label1;
	TLabel *LabExecutable;
	TLabel *LabLigneCommande;
	TEdit *EdExecutable;
	TEdit *EdLigneCommande;
	TLabel *LabProcedure;
	TEdit *EdProcedure;
	TRadioGroup *RGExecutable;
	void __fastcall BtBnDicoClick(TObject *Sender);
	void __fastcall BtBnALancerClick(TObject *Sender);
	void __fastcall EdLigneCommandeClick(TObject *Sender);
	void __fastcall EdExecutableClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	void __fastcall AffAn(int col0);

public:// Déclarations de l'utilisateur
public:// Déclarations utilisateur
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
	__fastcall TAppelFctFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAppelFctFrm *AppelFctFrm;
//---------------------------------------------------------------------------
#endif
