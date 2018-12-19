#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Forme01.h"

#include "AgriSaisie.h"
#include "Brouillon.h"

#include "InvAni.h"
#include "CL_MvtAnnee.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>

//---------------------------------------------------------------------------

#ifndef MvtAniH
#define MvtAniH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>
/*
 //TLabel *LabelModifie;
 class CL_MvtAnnee
 {
 public:
 CL_MvtAnnee();
 void CopieVers(CL_MvtAnnee *vers);
 void Maz(void);
 int Debut,Fin;
 int Ne,Mort;

 int   Vente[3],iVente;
 float PrixVente[3];
 int   TotVente;
 float ValVente;

 int   Achat[3],iAchat;
 float PrixAchat[3];
 int   TotAchat;
 float ValAchat;

 int Entree[3], Origine[3],  iOr;
 int Sortie[3], Destin[3],   iDest;
 bool adLib;        //true on cliqué sur Tout je prends tous les animaux
 // de l'origine
 void Solde(void);  //doit remplacer EffFin
 bool EstVide(void);
 };

 */
class CL_MvtAnnee;
class TMvtAniFrm: public TForm {
	__published: // Composants gérés par l'EDI
TStringGrid	*GrMvt;

	TStringGrid *SGVente;
	TStringGrid *SGAchat;
	TStringGrid *SGEntree;
	TStringGrid *SGSortie;

	TLabel *LabNom;
	TLabel *LabMvtModif;

	TLabel *LabVente;
	TLabel *LabAchat;
	TLabel *LabEntree;
	TLabel *LabSortie;

	TLabel *LabEffVente;
	TLabel *LabEffAchat;
	TLabel *LabEffEntree;
	TLabel *LabEffSortie;

	TLabel *LabPrixVente;
	TLabel *LabPrixAchat;
	TLabel *LabDestin;
	TLabel *LabOrig;

	TLabel *LabVenteModif;
	TLabel *LabAchatModif;
	TLabel *LabEntreeModif;
	TLabel *LabSortieModif;

	TBitBtn *BtBnOK;
	TListBox *LBAnimaux;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall GrMvtClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall GrMvtSelectCell(TObject *Sender, int ACol, int ARow,
			bool &CanSelect);
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall GrMvtKeyPress(TObject *Sender, char &Key);

	void __fastcall DeSGAchat (int &total);
	void __fastcall DeSGVente (int &total);
	bool __fastcall DeSGEntree (int &total);
	bool __fastcall DeSGSortie (int &total);

	void __fastcall SGKeyPress(TObject *Sender, char &Key);
	void __fastcall SGExit(TObject *Sender);
	void __fastcall SGKeyDown(TObject *Sender, WORD &Key,
			TShiftState Shift);
	/*
	 void __fastcall BtBnEAchatClick(TObject *Sender);
	 void __fastcall BtBnEVenteClick(TObject *Sender);
	 void __fastcall BtBnVAchatClick(TObject *Sender);
	 void __fastcall BtBnVVenteClick(TObject *Sender);
	 void __fastcall BtBnInventaireClick(TObject *Sender);
	 */
	void __fastcall SGEntreeEnter(TObject *Sender);
	void __fastcall SGSortieEnter(TObject *Sender);
	void __fastcall LBAnimauxClick(TObject *Sender);
//    void __fastcall BtBnToutClick(TObject *Sender);
//    void __fastcall LBDblClick(TObject *Sender);

private:// Déclarations utilisateur
	float Debut;
	TStringGrid *GrilleEnCours;
	CL_InvAni *InvAni;
	CL_MvtAnnee *MvtAnnee;
	TStringGrid *GrilleInv;
	void __fastcall VideGrille(TStringGrid *grille);
	int Entree[3][2];//comme dans grille
	int Sortie[3][2];
	void __fastcall MaZMvtAnnee(int col);
	void __fastcall MaJMvtAnnee(int col);
//    void __fastcall FaitEvoluer(int r);
//    void __fastcall ActualiseEntree(int r);
//    void __fastcall ActualiseSortie(int r);
//    void __fastcall ActualiseSuite(void);
//    int  __fastcall TrouverLigne(int noAnimal);
//    int  __fastcall TrouverNoAnimal(int r);
//    CL_MvtAnnee* __fastcall TrouverMvt(int noAnimal,int c);
	void __fastcall MetDansEntree(CL_MvtAnnee *mvtAnnee,int noOrigine,int eff,bool tout);
//    void __fastcall Mouvt(int date);
	int __fastcall RemplirEntree(TStringGrid *grille,int no, int date);
	int __fastcall RemplirSortie(TStringGrid *grille,int no, int date);

//    CL_MvtAnnee*  __fastcall TrouveMvtAnnee(int no,int date);
	int __fastcall RemplirOrigine (TStringGrid *grille,int no, int date, int *eff, int vientDe);
	int __fastcall RemplirDestination(TStringGrid *grille,int no, int date, int *eff, int* vaVers);
	void __fastcall CalculValeur(void);
	void __fastcall ImpMvt(void);

public:// Déclarations utilisateur
//    int Origine;
	int N;
	int An_0;
	void __fastcall AffMvtAnnee(CL_MvtAnnee *mvtAnnee);
//    void __fastcall MarquerCell(TStringGrid *grille,int col,int row); //a généraliser si OK
//    void __fastcall RepDroitInvAni(void);
	void __fastcall RepInvIni(void);

	void __fastcall CreeLstMvtAni(void);
	void __fastcall Quitter(void);

	CL_Agriculteur *Agri;
	__fastcall TMvtAniFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMvtAniFrm *MvtAniFrm;
//---------------------------------------------------------------------------
#endif
