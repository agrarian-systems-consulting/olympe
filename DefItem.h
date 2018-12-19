//---------------------------------------------------------------------------

#ifndef DefItemH
#define DefItemH
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
class TDefItemFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtSup;
	TBitBtn *BtRepBas;
	TBitBtn *BtRecopBas;
	TBitBtn *BtBnVideTout;
	TLabel *LabCatVar;
	TBitBtn *BtBnNote;
	TBitBtn *BtBnUnite;
	TButton *BtBnTva;
	TBitBtn *BtBnVersExcel;
	TBitBtn *BtBnDExcel;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall BtBnNoteClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall BtRepBasClick(TObject *Sender);
	void __fastcall BtRecopBasClick(TObject *Sender);
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall BtBnVersExcelClick(TObject *Sender);
	void __fastcall BtBnDExcelClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
protected:
	int ColNom,ColTva,ColSys,ColPrix;
	bool ErreurAAfficher;
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille (TStringGrid *grille);
	virtual void __fastcall VersGrille (TStringGrid *grille);
	virtual void __fastcall DeGrille (TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);
	virtual void __fastcall AffItem(int row,CL_Item *item);
	virtual void __fastcall LireItem(CL_Item *item,int row);
	virtual bool __fastcall VerifGrille(TStringGrid *grille);

	bool __fastcall NomCorrect(int col,int row);
	void __fastcall VerifExistenceNom(TStringGrid *grille);

//	virtual void  __fastcall DeGrille    (TStringGrid *grille);
	void __fastcall StockerOrdre(CL_Vecteur<CL_Item> *vecteur);

	void __fastcall RepBasPrix(AnsiString prix,int colPrix);
	void __fastcall RepBasTva(CL_Tva *tva);
	void __fastcall RepBasSysUnite(CL_SystemeUnite *sysUnite);

private:// Déclarations de l'utilisateur
//    AnsiString L_Utilise;
//    AnsiString L_SupQ;
//	AnsiString L_Sup;
//    AnsiString L_PasDeNom;

public:// Déclarations de l'utilisateur
	int Origine;
	void Francais(void);
	void Anglais(void);
	CL_Categorie* Categorie;
//	virtual void  __fastcall DeGrille    (TStringGrid *grille);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_RGCat;
	AnsiString LC_DefItemFrm;
	AnsiString LC_BtBnTva;
	AnsiString LC_BtBnUnite;

	__fastcall TDefItemFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefItemFrm *DefItemFrm;
//---------------------------------------------------------------------------
#endif
