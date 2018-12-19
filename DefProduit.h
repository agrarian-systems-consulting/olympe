//---------------------------------------------------------------------------

#ifndef DefProduitH
#define DefProduitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DefItem.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "DefItem.h"
//---------------------------------------------------------------------------
class TDefProduitFrm: public TDefItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall BtRepBasClick(TObject *Sender);void __fastcall BtBnTvaClick(TObject *Sender);void __fastcall BtBnUniteClick(TObject *Sender);void __fastcall BtRecopBasClick(TObject *Sender);void __fastcall BtBnNoteClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations de l'utilisateur
	AnsiString L_Titre;
	AnsiString L_PrixEg1;
//    AnsiString L_ErrNom;
	AnsiString L_UnParDef;
//    AnsiString L_Erreur;
//    AnsiString L_NonDef;
//    AnsiString L_PasUnite;    

protected:
	virtual void __fastcall Personnaliser(void);void __fastcall AffItem(int row,CL_Item *item);bool __fastcall VerifGrille(TStringGrid *grille);virtual void __fastcall LireItem(CL_Item *item,int row);virtual bool __fastcall ControleCell(int col,int row);

public:
	// Déclarations de l'utilisateur
	void __fastcall RetourDeChoixTva (CL_Tva *tva);void __fastcall RetourDeChoixUnite(CL_SystemeUnite *sysUnit);
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_DefProduitFrm;

	__fastcall TDefProduitFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefProduitFrm *DefProduitFrm;
//---------------------------------------------------------------------------
#endif
