//---------------------------------------------------------------------------
#ifndef GraphH
#define GraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <checklst.hpp>
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
class CL_Graphique {
public:
	int NbrSeries;
	int MaxG, MinG;
	int MaxD, MinD;
	bool TypeGraph;
	AnsiString TitreGraph, TitreAbs, TitreOrd;
	int BornSup, BornInf;
	int NbAn;
	int ClFond;
	bool TD;
};

class CL_Courbe {
public:
	int Couleur;
	int Epaisseur;
	int Trait;
	bool AxeD;
};

class TGraphiqueFrm: public TForm {
	__published: // Composants gérés par l'EDI
TButton	*ButtonZoom2;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBoxEch;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *EditMaxG;
	TEdit *EditMinG;
	TButton *ButtonAuto;
	TButton *ButtonApply;
	TGroupBox *GroupBox1;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *EditMaxD;
	TEdit *EditMinD;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel1;
	TScrollBar *ScrollBarMaxG;
	TScrollBar *ScrollBarMinG;
	TScrollBar *ScrollBarMinD;
	TLabel *Label5;
	TEdit *EditIncG;
	TLabel *Label6;
	TEdit *EditIncD;
	TScrollBar *ScrollBarMaxD;
	TBevel *Bevel2;
	TGroupBox *GroupBox2;
	TEdit *EditSup;
	TEdit *EditInf;
	TCheckBox *CheckBoxInf;
	TCheckBox *CheckBoxSup;
	TGroupBox *GroupBox3;
	TSpeedButton *SpeedButtonTrait;
	TSpeedButton *SpeedButtonHisto;
	TButton *ButtonFormat;
	TButton *ButtonZoom;
	TButton *ButtonPrint;
	TBitBtn *BitBtn1;
	TButton *ButtonSave;
	TSaveDialog *SaveDialog;
	TButton *BtTableau;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ButtonPrintClick(TObject *Sender);
	void __fastcall ButtonFormatClick(TObject *Sender);
	void __fastcall ButtonApplyClick(TObject *Sender);
	void __fastcall ButtonZoomClick(TObject *Sender);
	void __fastcall ButtonZoom2Click(TObject *Sender);
	void __fastcall SpeedButtonHistoClick(TObject *Sender);
	void __fastcall SpeedButtonTraitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ScrollBarMaxGChange(TObject *Sender);
	void __fastcall ScrollBarMinGChange(TObject *Sender);
	void __fastcall ScrollBarMaxDChange(TObject *Sender);
	void __fastcall ScrollBarMinDChange(TObject *Sender);
	void __fastcall EditIncDChange(TObject *Sender);
	void __fastcall CheckBoxSupClick(TObject *Sender);
	void __fastcall CheckBoxInfClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall EdKeyPress(TObject *Sender, char &Key);
	void __fastcall BtTableauClick(TObject *Sender);

private: // Déclarations de l'utilisateur
	CL_Elt *Elt;
	void Effacer(void);
//    void Effacer(void);
	void erreur(void);
	void Incrementation(void);
//    TColor LesCouleurs[10];
	TColor LesCouleurs[10];
	int Coul;
	TList *LstSerie;
public:// Déclarations de l'utilisateur
	TStringList *Series;
	TList *ListGraph;
	bool EstInitialise;
	int An_0;//informé dans Resultat
	void Demarrer(void);

	void CreeSerie(void);
//    void GrapheLine(TCheckListBox* lbCourbe, bool ligne);
//    void GrapheLine(TListBox* lbCourbe);
	void GrapheLine(TListBox *lBCourbe,char axe,int k);

	void GrapheBar (TListBox *lbCourbe,char axe,int k);

	__fastcall TGraphiqueFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphiqueFrm *GraphiqueFrm;
//---------------------------------------------------------------------------
#endif
