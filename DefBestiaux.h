//---------------------------------------------------------------------------

#ifndef DefBestiauxH
#define DefBestiauxH
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
//---------------------------------------------------------------------------
class TDefBestiauxFrm: public TDefItemFrm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnAide;
	void __fastcall BtRepBasClick(TObject *Sender);
	void __fastcall BtBnTvaClick(TObject *Sender);
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnNoteClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private: // Déclarations de l'utilisateur
protected:
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);

	virtual void __fastcall VersGrille(TStringGrid *grille);
	virtual void __fastcall DeGrille(TStringGrid *grille);

	void __fastcall AffBestiaux(int row,CL_Bestiaux *bestiaux);
	bool __fastcall VerifGrille(TStringGrid *grille);
	void __fastcall LireBestiaux(CL_Bestiaux *bestiaux,int row);
	void __fastcall StockerOrdreBestiaux(CL_Vecteur<CL_Bestiaux> *vecteur);

private:// Déclarations de l'utilisateur
	AnsiString L_MvtTroupeau;
	AnsiString L_Titre;
//    AnsiString L_NonDef;
	AnsiString L_PasValInv;
	AnsiString L_PasPrix;
	AnsiString L_PasOrigine;
	AnsiString L_OretDest;
	AnsiString L_MemeOrig;
	AnsiString L_Utilise;
	AnsiString L_AttSupp;
//	AnsiString L_Supp;
	AnsiString L_DonModif;
//    AnsiString L_Modif;

public:// Déclarations de l'utilisateur
	void __fastcall RetourDeChoixTva (CL_Tva *tva);
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_DefBestiauxFrm;

	__fastcall TDefBestiauxFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefBestiauxFrm *DefBestiauxFrm;
//---------------------------------------------------------------------------
#endif
