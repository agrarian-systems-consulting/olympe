//---------------------------------------------------------------------------

#ifndef ResGraphH
#define ResGraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TResGraphFrm: public TForm {
	friend class TResGraphLegendeFrm;

	__published: // Composants gérés par l'EDI
TPageControl	*PCGaucheDroit;
	TTabSheet *TabSheetG;
	TTabSheet *TabSheetD;
	TGroupBox *GBEchelleG;
	TGroupBox *GBEchelleD;
	TGroupBox *GBBas;

	TEdit *EditMaxG;
	TEdit *EditMaxD;

	TEdit *EditMinG;
	TEdit *EditMinD;
	TScrollBar *ScrollBarMinG;
	TScrollBar *ScrollBarMinD;
	TScrollBar *ScrollBarMaxD;
	TButton *BtImp;
	TButton *BtTableau;
	TBitBtn *BtBnClose;

	TLabel *LabMAXD;
	TLabel *LabMIND;
	TLabel *LabMAXG;
	TLabel *LabMING;
	TScrollBar *ScrollBarMaxG;
	TGroupBox *GBBornesG;
	TEdit *EdSupG;
	TEdit *EdInfG;
	TCheckBox *ChBSupG;
	TCheckBox *ChBInfG;
	TGroupBox *GBBornesD;
	TEdit *EdSupD;
	TEdit *EdInfD;
	TCheckBox *ChBSupD;
	TCheckBox *ChBInfD;
	TSpeedButton *SpBtCourbeG;
	TSpeedButton *SpBtHistoG;
	TSpeedButton *SpBtCourbeD;
	TSpeedButton *SpBtHistoD;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtTableauClick(TObject *Sender);
	void __fastcall ScrollBarMaxGScroll(TObject *Sender,
			TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall ScrollBarMinGScroll(TObject *Sender,
			TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall ScrollBarMaxDScroll(TObject *Sender,
			TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall ScrollBarMinDScroll(TObject *Sender,
			TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall BtImpClick(TObject *Sender);
	void __fastcall SpBtCourbeDClick(TObject *Sender);
	void __fastcall SpBtHistoDClick(TObject *Sender);
	void __fastcall SpBtCourbeGClick(TObject *Sender);
	void __fastcall SpBtHistoGClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall EdSupDDblClick(TObject *Sender);
	void __fastcall EdInfDDblClick(TObject *Sender);
	void __fastcall EdSupGDblClick(TObject *Sender);
	void __fastcall EdInfGChange(TObject *Sender);
	void __fastcall ChBBorneClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
//private:	// Déclarations utilisateur
protected:
	enum {COURBE,HISTO};
	int Coul,CoulMax;
	int LesCouleurs[20];
	int Motif,MotifMax;
	int LesMotifs[10];

	TCanvas *LeCanvas;
	float LaHeight;
	float LaWidth;

	float LEcran,HEcran;
	float XGauche,XDroit;
	float YBas,YHaut;
	float EchelleH;

	float VMinG,VMaxG;
	float VMinD,VMaxD;
	float UniteG,UniteD;
	float BorneSupG,BorneInfG;
	float BorneSupD,BorneInfD;

//	int   NbAxeVer;
	float LarHisto;
	float Intervalle;
	float __fastcall Xde(float x);
	float __fastcall Yde(float y);
	void __fastcall TraitHor(float y, float x0,float x1,float width);
	void __fastcall TraitVer(float x, float y0,float y1,float width);
	void __fastcall AffAnnees(int an0);

	void __fastcall TrouveMinMax(void);
	void __fastcall TrouveMinMax1(TListBox *lb,float &vMin,float &vMax);

	float __fastcall TrouveUnite(char axe);
	float __fastcall ValeurDe(AnsiString s);
	void __fastcall EchelleVer(void);
//    AnsiString  __fastcall  TrouveTitre(CL_Elt *elt);

	void __fastcall AxeOrdonnee(char position);
	void __fastcall Ordonnee(char position,float x,float y,float val);

	void __fastcall AffLesCourbes(TListBox *lb,float vMin,float vMax);
	void __fastcall Courbe(float *valeur,float vMin,float vMax);

	void __fastcall AffLesHisto(TListBox *lb,float vMin,float vMax);
	void __fastcall Histo(float *valeur,float vMin,float vMax,int i,float larHisto);

//void __fastcall Legende(TListBox *lbG,TListBox *lbD);
	void __fastcall TResGraphFrm::Legende(TListBox *lb,float xGauche);

public:// Déclarations utilisateur
	int Origine;
	int TypeCourbeG,TypeCourbeD;
	int Nature;//AGRI  COMPARAISON
	int AnDebut;//année de debut d'affichage 230908
	__fastcall void Dessiner(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtImp;
	AnsiString LC_GBBornesG;
	AnsiString LC_TabSheetD;
	AnsiString LC_GBEchelleG;
	AnsiString LC_TabSheetG;
	AnsiString LC_LabMAXG;
	AnsiString LC_LabMING;
	AnsiString LC_BtTableau;

	__fastcall TResGraphFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResGraphFrm *ResGraphFrm;
//---------------------------------------------------------------------------
#endif
