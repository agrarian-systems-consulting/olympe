//---------------------------------------------------------------------------

#ifndef MvtAnneeH
#define MvtAnneeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Forme01.h"

#include "AgriSaisie.h"
#include "Brouillon.h"

#include "CL_MvtAnnee.h"

//#include "InvAni.h"
#include "Troupeau.h"

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
class TMvtAnneeFrm: public TForm {
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
	TBitBtn *BitBtn1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall GrMvtClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall GrMvtSelectCell(TObject *Sender, int ACol, int ARow,
			bool &CanSelect);
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall GrMvtKeyPress(TObject *Sender, char &Key);

	void __fastcall DeSGAchat (CL_MvtAnnee *mvt,int &total);
	void __fastcall DeSGVente (CL_MvtAnnee *mvt,int &total);
	bool __fastcall DeSGEntree (CL_MvtAnnee *mvt,int &total);
	bool __fastcall DeSGSortie (CL_MvtAnnee *mvt,int &total);

	void __fastcall SGKeyPress(TObject *Sender, char &Key);
	void __fastcall SGExit(TObject *Sender);
	void __fastcall SGKeyDown(TObject *Sender, WORD &Key,
			TShiftState Shift);

	void __fastcall SGEntreeEnter(TObject *Sender);
	void __fastcall SGSortieEnter(TObject *Sender);
	void __fastcall LBAnimauxClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);

private: // Déclarations utilisateur
	float Debut;
	int Col0;
	TStringGrid *GrilleEnCours;
	CL_InvAni *InvAni;
//    CL_MvtAnnee  *MvtAnnee;
	TStringGrid *GrilleInv;
	void __fastcall VideGrille(TStringGrid *grille);
	int Entree[3][2];//comme dans grille
	int Sortie[3][2];
	void __fastcall MetDansEntree(CL_MvtAnnee *mvtAnnee,int noOrigine,int eff,bool tout);
	int __fastcall RemplirEntree(TStringGrid *grille,int no, int date);
	int __fastcall RemplirSortie(TStringGrid *grille,int no, int date);
	void CorrigerDeficit(CL_MvtAnnee *mvtAnnee);

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
	void MajMvt(CL_MvtAnnee *mvt);
	CL_Agriculteur *Agri;

	void TexteCaption(void);
	void IniCaption(void);

	void TexteChaine(void);

	AnsiString L_Debut;//"Début";
	AnsiString L_Vente;//"Vente";
	AnsiString L_Achat;//"Achat";
	AnsiString L_Ne;//"Né";
	AnsiString L_Mort;//"Mort";
	AnsiString L_Entree;//"Entrée";
	AnsiString L_Sortie;//"Sortie";
	AnsiString L_Fin;//"Fin";

	AnsiString LC_LabAchat;
	AnsiString LC_RG;
	AnsiString LC_LabEffEntree;
	AnsiString LC_LabEntree;
	AnsiString LC_LabelModifie;
	AnsiString LC_MvtAnneeFrm;
	AnsiString LC_GBPrix;
	AnsiString LC_LabSortie;
	AnsiString LC_LabDestin;
	AnsiString LC_BtBnVenteQ;
	AnsiString LC_LabOrig;

	__fastcall TMvtAnneeFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMvtAnneeFrm *MvtAnneeFrm;
//---------------------------------------------------------------------------
#endif
