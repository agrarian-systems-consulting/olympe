//---------------------------------------------------------------------------

#ifndef CalTravH
#define CalTravH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
int CmpBornes(const void *a, const void *b);

class CL_SousPeriode {
public:
	CL_SousPeriode(int borneD, int borneF, CL_Calendrier *calendrier);
	~CL_SousPeriode();
	int JD, JF; //exprimé par rapport au J0 de BorneDebut
	int JDeb, MDeb; //les dates du calendrier
	int JFin, MFin;
	CL_Periode** LesPeriodes;
	float* LesPcent;
	int NPeriode;
};
class CL_Legende {
public:
	CL_Legende(int no, char *nom, TColor couleur, int style);
	TStaticText *Texte;
	TShape *Couleur;
	TShape *Motif;
	TShape *Ensemble;

};
//---------------------------------------------------------------------------
class TCalTravFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	TLabel *LabCalendrier;
	TColorDialog *ColorDialog;
	TBitBtn *BtBnFermer;
	TBitBtn *BtBnLegende;
	TGroupBox *GB;
	TShape *RecMotif;
	TBitBtn *BtBnQuitter;
	TBitBtn *BtBnGraphe;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtBnLegendeClick(TObject *Sender);
	void __fastcall RecCouleurMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
	void __fastcall RecMotifMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall BtBnGrapheClick(TObject *Sender);
private: // Déclarations utilisateur
	bool EstInitialise;
	int *LesBornes;
	int NBorne;
	int BorneX;
	int CoulX;
	TList *LstSousPeriodes;
	TList *LstLegende;
	CL_Calendrier *Calendrier;
	CL_Legende *Legende;
	TDateTime DtDebut;//date de début calculé par EnCodeDate cf DatePeriode
	bool __fastcall DatePeriode(CL_Vecteur<CL_Periode> *v_Periode);

	void __fastcall EtablirBornes(void);
//    int  __fastcall CmpBornes(void *Item1,void *Item2);
//    int  __fastcall CalculDuree(CL_Borne *debut,CL_Borne *fin);
	bool __fastcall EtablirBornePeriode(CL_Periode *periode);
//    void __fastcall ClasserBornes(void);
	void __fastcall RetirerDoublon(void);

	void __fastcall DaterBornes(void);
	void __fastcall CreerSousPeriodes(void);
	void __fastcall CorrespondancePeriodeSousPeriode(void);

	void __fastcall Imprimer(void);

public:// Déclarations utilisateur
	TColor LesCouleurs[10];
	int NoMotif;
	void __fastcall DessineMotif(int n);
	__fastcall TCalTravFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCalTravFrm *CalTravFrm;
//---------------------------------------------------------------------------
#endif

