//---------------------------------------------------------------------------

#ifndef TravCalH
#define TravCalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Math>
#include "ChoixMotif.h"
#include "CL_BesTravAtelier.h"
#include "Erreur.h"

//---------------------------------------------------------------------------
int CmpBornes(const void *a, const void *b);

class CL_Legende {
public:
//    CL_Legende(int no,AnsiString nom,TColor couleur,int style);
	CL_Legende(int no, AnsiString nom, int couleur, int style);
	TStaticText *Texte;
	TShape *Couleur;
	TShape *Motif;
	TShape *Ensemble;
	TShape *Motif1;
	TShape *Ensemble1;

};
//---------------------------------------------------------------------------
class TTravCalFrm: public TForm {
	friend class TTravGraphFrm;
	friend class TChoixMotifFrm;
	__published: // Composants gérés par l'EDI
TColorDialog	*ColorDialog;
	TBitBtn *BtBnFermer;
	TGroupBox *GB;
	TBitBtn *BtBnQuitter;
	TLabel *LabCoulMotif;
	TGroupBox *GBOrdre;
	TListBox *LBAtelier;
	TGroupBox *GBGeneral;
	TLabel *LabCalendrier;
	TListBox *LBCalendrier;
	TLabel *LabAn;
	TComboBox *CBAn;
	TLabel *LabNbOuv;
	TEdit *EdNbOuv;
	TGroupBox *GBResultat;
	TBitBtn *BtBnGraphe;
	TBitBtn *BtBnCalcul;
	TGroupBox *GBPresentation;
	TBitBtn *BtBnLegende;
	TBitBtn *BtBnOrdre;
	TPanel *PClasst;
	TBitBtn *BtClHaut;
	TBitBtn *BtClBas;
	TLabel *LabCal;
	TBitBtn *BtBnCalculer;
	TBitBtn *BtBnTotalBesoins;
	TBitBtn *BtBnAide;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBCalendrierClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtBnLegendeClick(TObject *Sender);
	void __fastcall RecCouleurMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
	void __fastcall RecMotifMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall BtBnGrapheClick(TObject *Sender);
	void __fastcall CBAnClick(TObject *Sender);
	void __fastcall BtBnCalculClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall EdNbOuvKeyPress(TObject *Sender, char &Key);
	void __fastcall EdNbOuvExit(TObject *Sender);
	void __fastcall BtBnOrdreClick(TObject *Sender);
	void __fastcall LBAtelierClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall BtBnFermClasstClick(TObject *Sender);
	void __fastcall BtBnOrdreFinClick(TObject *Sender);
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtBnCalculerClick(TObject *Sender);
	void __fastcall BtBnTotalBesoinsClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private: // Déclarations utilisateur
	int LBCalendrierItemIndex;
	int CBAnItemIndex;
	bool EstInitialise;
	int *LesBornes;
	int NBorne;
	int BorneX;
	int CoulX;
	int MotifX;
	int AnSim;
	int NbTrav;
	TList *LstSousPeriodes;
	TList *LstLegende;
	CL_Calendrier *Calendrier;
	CL_Legende *Legende;
	TDateTime DtDebut;//date de début calculé par EnCodeDate cf DatePeriode
	int NAtelier;

	void __fastcall DefinirCoulMotif(void);
	bool __fastcall DatePeriode(CL_Vecteur<CL_Periode> *v_Periode);
	void __fastcall LegendeAtelier(void);

	void __fastcall EtablirBornes(void);
	bool __fastcall EtablirBornePeriode(CL_Periode *periode);
	void __fastcall RetirerDoublon(void);

	void __fastcall DaterBornes(void);
	void __fastcall CreerSousPeriodes(void);
	void __fastcall CorrespondancePeriodeSousPeriode(void);

	void __fastcall Imprimer(void);
	void __fastcall OrdreAffichage(void);
	void __fastcall ClasseLstTravail(void);

	//TravCal1
	TList *LstBesAtelier;
//    TList *LstBesSousPer;
	float *TotBesSousPer;
	float *DispoSousPer;
	float *TravNec;
	int NbOuv;
	bool __fastcall VerifCompletude(void);
	bool __fastcall Completude(CL_Vecteur<CL_Valeur>*vecteur);
	bool __fastcall Completude(CL_Vecteur<CL_Verger>*vecteur);
	void __fastcall CalculBesPeriode(int noAn);//090306
	void __fastcall CalculBesAnnuelles(CL_Vecteur<CL_Valeur>*vecteur,int noAn);
	void __fastcall CalculBesPerennes(CL_Vecteur<CL_Verger>*vecteur,int noAn);
	void __fastcall CalculDispo(void);

public:// Déclarations utilisateur
	CL_Agriculteur *Agri;//instancié dans TravCal->FormActivate  A REVOIR
	int Origine;
//    TColor LesCouleurs[10];
	int LesCouleurs[10];
	int LesMotifs[10];
//    int NoMotif;
	void __fastcall DessineMotif(int n);
	void CalculTotBesoins(void);//040306

	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString L_PasCal;
	AnsiString L_PasPeriode;
	AnsiString L_CalNonDef;
	AnsiString L_TotBesoinsTrav;
	AnsiString L_A_Executer;

	AnsiString LC_GBAn;
	AnsiString LC_RG;
	AnsiString LC_LabCalendrier;
	AnsiString LC_LabCoulMotif;
	AnsiString LC_GB;
	AnsiString LC_BtBnGraphe;
	AnsiString LC_BtBnLegende;
	AnsiString LC_GBPresentation;
	AnsiString LC_LabNbOuv;
	AnsiString LC_BtBnOrdre;
	AnsiString LC_GBOrdre;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_BtBnResultat;
	AnsiString LC_TravCalFrm;
	AnsiString LC_BtBnCalcul;
	AnsiString LC_TotBesoins;

	__fastcall TTravCalFrm(TComponent* Owner);

};
//typedef int __fastcall (*TListSortCompare)(void *Item1, void *Item2);
//---------------------------------------------------------------------------
extern PACKAGE TTravCalFrm *TravCalFrm;
//---------------------------------------------------------------------------
#endif

