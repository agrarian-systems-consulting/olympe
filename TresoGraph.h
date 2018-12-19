//---------------------------------------------------------------------------

#ifndef TresoGraphH
#define TresoGraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ResGraph.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTresoGraphFrm: public TResGraphFrm {
	__published: // Composants gérés par l'EDI
TGroupBox	*GBAff;
	TRadioGroup *RGNbAnnee;
	TComboBox *CBMois;
	TLabel *LabMois;
	TLabel *LabAn;
	TComboBox *CBAn;
	TBitBtn *BtBnOK;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpBtCourbeGClick(TObject *Sender);
	void __fastcall SpBtHistoGClick(TObject *Sender);
	void __fastcall BtImpClick(TObject *Sender);
	void __fastcall RGNbAnneeClick(TObject *Sender);
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall CBAnClick(TObject *Sender);
	void __fastcall CBMoisClick(TObject *Sender);
	void __fastcall SpBtCourbeDClick(TObject *Sender);
	void __fastcall SpBtHistoDClick(TObject *Sender);
	void __fastcall BtTableauClick(TObject *Sender);
	void __fastcall ScrollBarMaxGScroll(TObject *Sender,
			TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall ScrollBarMinGScroll(TObject *Sender,
			TScrollCode ScrollCode, int &ScrollPos);
private: // Déclarations de l'utilisateur
	int NbAnnee;//courbe sur toutes les années ou 1 annéé
	int Annee;
	int MDeb;
	int Nmin,Nmax;

	int AnDeb;//170512

	AnsiString AsUniteQuantite;
	TStringGrid *SG;
	TList *LstTresoMensG;
	TList *LstTresoMensD;

	void __fastcall TrouveMinMax(void);
	void __fastcall TrouveVMinMax(TList *lstTresoMens,float &vMin,float &vMax);
	void __fastcall LegendeTreso(TList *lstTresoMens,float xGauche);
	void __fastcall AffAnnees(int an0);
	void __fastcall AffMois(int an0);

	void __fastcall EchelleVer(void);
	void __fastcall AffLesCourbes(TList *lstTresoMens,float vMin,float vMax);
	void __fastcall Courbe(float *valeur,float vMin,float vMax);
	void __fastcall AffLesHisto(TList *lstTresoMens,float vMin,float vMax);
	void __fastcall Histo(float *valeur,float vMin,float vMax,int i,float larHisto);

	void AffTableau(int an0);//170512

public:// Déclarations de l'utilisateur
	void __fastcall Dessiner(void);

	void TexteCaption(void);
	void IniCaption(void);

	void AffTableauPlus12(void);//170512
	void AffTableauMoins12(void);

	AnsiString LC_GBAff;
	AnsiString LC_GBAn;
	AnsiString LC_LabMois;
	AnsiString LC_RGNbAnnee;
	AnsiString LC_TresoGraphFrm;

	__fastcall TTresoGraphFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoGraphFrm *TresoGraphFrm;
//---------------------------------------------------------------------------
#endif
