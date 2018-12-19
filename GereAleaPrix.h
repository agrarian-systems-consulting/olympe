//---------------------------------------------------------------------------

#ifndef GereAleaPrixH
#define GereAleaPrixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGereAleaPrixFrm: public TForm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnFermer;
	TBitBtn *BtBnQuitter;
	TBitBtn *BtBnImp;

	TLabel *LabelModifie;
	TTreeView *TV;
	TPanel *Panel2;
	TGroupBox *GBCategorie;
	TGroupBox *GBReclasser;
	TBitBtn *BtHaut;
	TBitBtn *BtBas;
	TBitBtn *BtBnCreer;
	TButton *Btsupprimer;
	TBitBtn *BtCopier;
	TButton *BtModifier;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall BtCopierClick(TObject *Sender);
	void __fastcall BtsupprimerClick(TObject *Sender);
	void __fastcall BtBnCreerClick(TObject *Sender);
	void __fastcall BtModifierClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
protected:
	bool __fastcall VerifNomTendance(AnsiString newNom,int action);
	void __fastcall BoutonEnabled(bool val);
	virtual void __fastcall CreeTV(void);
	virtual void __fastcall AffTendance(void);
	TForm *AleaXXFrm;
	CL_Tendance *Tendance;
//private:	// Déclarations utilisateur
//	CL_Tendance *Tendance;

public:// Déclarations utilisateur
	CL_Vecteur<CL_Tendance> *V_Tendance;
	bool OrdreModif;
	int No;
	int *Nature;
	int Origine;
	void TexteChaine(void);
	AnsiString L_Prod;
	AnsiString L_PrixTendProd;
	AnsiString L_PrixScenProd;
	AnsiString L_Charge;
	AnsiString L_PrixTendCha;
	AnsiString L_PrixScenCha;
	AnsiString L_QuantTendProd;
	AnsiString L_QuantScenProd;
	AnsiString L_QuantTendCha;
	AnsiString L_QuantScenCha;
	AnsiString L_Exter;
	AnsiString L_QuantTendExt;
	AnsiString L_QuantScenExt;

	AnsiString L_NouvTend;
	AnsiString L_NouvScen;
	AnsiString L_NouvTendCop;
	AnsiString L_Rien;
	AnsiString L_Pb;
	AnsiString L_Util;
//    AnsiString L_Impo;
	AnsiString L_Sup;
	AnsiString L_PasSel;
	AnsiString L_ModifTend;
	AnsiString L_ModifScen;
	AnsiString L_PasNom;
	AnsiString L_Existe;
//    AnsiString L_Erreur;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_GereAleaPrixFrm;
	AnsiString LC_RGCat;
	AnsiString LC_BtBnCopier;
	AnsiString LC_BtBnCreer;
	AnsiString LC_BtBnFermer;
	AnsiString LC_BtModifier;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_GBReclasser;
	AnsiString LC_BtBnSupBesTrav;

	__fastcall TGereAleaPrixFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereAleaPrixFrm *GereAleaPrixFrm;
//---------------------------------------------------------------------------
#endif
