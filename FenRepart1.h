//---------------------------------------------------------------------------

#ifndef FenRepart1H
#define FenRepart1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "CL_Repart.h"

//---------------------------------------------------------------------------
class TFenRepartFrm1: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panell;
	TBitBtn *BoutFermer;
	TBitBtn *BtBnQuitter;

	TGroupBox *GBCode;
	TGroupBox *GBAn;
	TGroupBox *GBProduit;
	TGroupBox *GBValeur;

	TEdit *EdCode;
	TEdit *EdAn;
	TEdit *EdProduit;
	TEdit *EdValeur;

	TLabel *LabelModifie;

	TLabel *LabPcent; //ce que contient la Grille Pourcent
	TLabel *LabVal;
	TStringGrid *LaGrille;

	TLabel *LabTotPcent;
	TLabel *LabTotalVal;

	TEdit *EdTotPcent;
	TEdit *EdTotValeur;

	TBitBtn *BtRepBas;
	TBitBtn *BtBn100;
	TBitBtn *BtBnEgal;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall SGKeyPress(TObject *Sender, char &Key);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtRepBasClick(TObject *Sender);
	void __fastcall SGSelectCell(TObject *Sender, int ACol, int ARow,
			bool &CanSelect);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBn100Click(TObject *Sender);
	void __fastcall BtBnEgalClick(TObject *Sender);
private:// Déclarations utilisateur
	int Col,Row;
public:// Déclarations utilisateur
	CL_Repart *Repart;
	CL_Item *Item;
	float ValTot;
	__fastcall TFenRepartFrm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFenRepartFrm1 *FenRepartFrm1;
//---------------------------------------------------------------------------
#endif
