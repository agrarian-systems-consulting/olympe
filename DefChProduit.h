//---------------------------------------------------------------------------

#ifndef DefChProduitH
#define DefChProduitH
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
//---------------------------------------------------------------------------
class TDefChProduitFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TButton	*BtTva;
	TBitBtn *BtSup;
	TBitBtn *BtRepBas;
	TBitBtn *BtRecopBas;
	TBitBtn *BtBnVideTout;
	TLabel *LabCatVar;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtTvaClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtRepBasClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnStockerClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations de l'utilisateur
protected:
	int ColTva;
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille (TStringGrid *grille);
	virtual void __fastcall VersGrille (TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);
	bool __fastcall NomCorrect(int col,int row);
	virtual void __fastcall DeGrille (TStringGrid *grille);
	bool __fastcall VerifGrille(TStringGrid *grille);
	void __fastcall StockerOrdre(CL_Vecteur<CL_Item> *vecteur);

	void __fastcall AffItem(int row,CL_Item *item);
	void __fastcall RetourDeChoixTva (CL_Tva *tva);

	void __fastcall RepBasTva(CL_Item *item,int colTva);

public:// Déclarations de l'utilisateur
	CL_Categorie* Categorie;
	__fastcall TDefChProduitFrm(TComponent* Owner);
	void IniCaption(void);
	void TexteCaption(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefChProduitFrm *DefChProduitFrm;
//---------------------------------------------------------------------------
#endif
