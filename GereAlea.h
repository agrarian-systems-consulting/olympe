//---------------------------------------------------------------------------

#ifndef GereAleaH
#define GereAleaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGereAleaFrm: public TForm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnFermer;
	TBitBtn *BtBnQuitter;
	TBitBtn *BtBnImp;
	TLabel *LabelModifie;
	TPanel *Panel1;
	TButton *Btsupprimer;
	TButton *BtModifier;
	TGroupBox *GBReclasser;
	TBitBtn *BtHaut;
	TBitBtn *BtBas;
	TBitBtn *BtBnCreer;
	TTreeView *TV;
	TBitBtn *BtCopier;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall BtCopierClick(TObject *Sender);
	void __fastcall BtsupprimerClick(TObject *Sender);
	void __fastcall BtBnCreerClick(TObject *Sender);
	void __fastcall BtModifierClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	bool OrdreModif;
	int No;
	int *Nature;
	int Origine;
	bool ReCreeTV;
	__fastcall TGereAleaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereAleaFrm *GereAleaFrm;
//---------------------------------------------------------------------------
#endif
