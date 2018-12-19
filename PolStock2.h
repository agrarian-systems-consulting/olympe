//---------------------------------------------------------------------------

#ifndef PolStockH
#define PolStockH
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
/*
 class CL_PolStock //: public TForme00Frm
 {
 public:
 CL_PolStock();
 CL_PolStock(CL_Item *item);

 int No;             //c'est le n° de l'item
 CL_Item *Item;
 float PcentStock;
 float Maxi;
 float PcentDeltaPrix;
 float PcentDecote;

 void AffRow(TStringGrid *grille, int r);
 void LitRow(TStringGrid *grille, int r);
 };
 */
//---------------------------------------------------------------------------
class TPolStockFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TStringGrid	*StringGrid1;
	TBitBtn *BtReportDroit;
	TBitBtn *BtReportBas;
	TBitBtn *BtRecopBas;
	void __fastcall BtReportBasClick(TObject *Sender);
	void __fastcall BtRecopBasClick(TObject *Sender);
private: // Déclarations utilisateur
//    void __fastcall StockerOrdre(CL_Vecteur<CL_Tva> *vecteur);
protected:
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille (TStringGrid *grille);
	virtual void __fastcall DeGrille (TStringGrid *grille);
	virtual void __fastcall VersGrille (TStringGrid *grille);
	virtual bool __fastcall ControleGrille(void);

//    virtual bool  __fastcall ControleCell(int col,int row);
	virtual bool __fastcall Stocker(void);
public:// Déclarations utilisateur
	CL_Agriculteur *Agri;
	__fastcall TPolStockFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPolStockFrm *PolStockFrm;
//---------------------------------------------------------------------------
#endif
