//---------------------------------------------------------------------------

#ifndef TroupeauH
#define TroupeauH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>

#include "AgriSaisie.h"
#include "MvtAnnee.h"
#include "CL_MvtAnnee.h"
#include "InvAniProCha.h"
#include "LBChoixBestiaux.h"

/*
 #include "Olympe.hse"
 #include "olympedec.h"
 #include "LesClassesApp.h"
 #include "LesVecteurs.hse"
 */
#include "FichierLire.h"
#include <Graphics.hpp>
#include <CheckLst.hpp>
/*
 #include "Forme0.h"
 #include "Forme01.h"
 #include "AgriSaisieEnum.h"
 */
//---------------------------------------------------------------------------
class TTroupeauFrm: public TForme00Frm {
	friend class TMvtAnneeFrm;
	friend class TLBChoixBestiauxFrm;

	__published: // Composants gérés par l'EDI
TPageControl	*PC;
	TBitBtn *BtReportDroit;
	TBitBtn *BtReportBas;

	TLabel *LabNomTroupeau;

	TTabSheet *TSNature; //Nature
	TPanel *PanNature;
	TLabel *LabNature;
	TGroupBox *GBTroupeau;
	TListBox *LBTroupeau;
	TBitBtn *BtBnSup;

	TTabSheet *TSMaxi;//Effectifs Maxi
	TPanel *PanMaxi;
	TLabel *LabEffMax;
	TStringGrid *GrilleMaxi;

	TTabSheet *TSPrix;//Prix Vente
	TPanel *PanPrix;
	TLabel *LabPrix;
	TStringGrid *GrillePrix;

	TTabSheet *TSValInv;//Valeur inventaire
	TPanel *PanValInv;
	TLabel *LabValInv;
	TStringGrid *GrilleValInv;

	TTabSheet *TSMouvement;//Mouvement
	TPanel *PanMvtHaut;
	TLabel *LabMvt;
	TStringGrid *GrilleMvt;
	TPanel *PanMvtBas;
	TRadioGroup *RGCouS;//avec mvt ou constant
	TBitBtn *BtBnSimuler;
	TGroupBox *GBResultat;
	TTreeView *TVMvtEffectif;
	TTreeView *TVMvtValeur;
	TBitBtn *BtBnSansBorne;

	TTabSheet *TSProCha;//Produits Charges
	TPanel *PanChaPro;
	TLabel *LabProCha;
	TBitBtn *BtBnProcha;
	TBitBtn *BtBnRien;
	TStringGrid *GrilleProCha;

	TTabSheet *TSAchat;//Achat décidé par l'utilisateur
	TPanel *PanAchat;
	TLabel *LabAchat;
	TStringGrid *GrilleAchat;

	TTabSheet *TSPrixAchat;//Prix d'Achat
	TPanel *PanPrixAchat;
	TLabel *LabPrixAchat;
	TStringGrid *GrillePrixAchat;

	TTabSheet *RSResultat;//Resultats
	TPanel *PanResTroup;
	TLabel *LabResTroup;
	TGroupBox *GBTrARetenir;
	TCheckListBox *ChLBTroupeau;
	TGroupBox *GBResultats;
	TTreeView *TVResultat;
	TGroupBox *GBSortie;
	TImage *Image1;
	TImage *Image2;
	TRadioButton *RBQR;
	TRadioButton *RBExcel;
	TRadioButton *RBEcran;
	TBitBtn *BtBnAide;
	TBitBtn *BtBnMazVenteAchat;
	TBitBtn *BtBnMazMvt;
	TLabel *LabFinAnnee;

	void __fastcall FormActivate(TObject *Sender);
	void __fastcall PCChange(TObject *Sender);
	void __fastcall Grille0KeyPress(TObject *Sender, char &Key);
	void __fastcall Grille0Click(TObject *Sender);
	void __fastcall BtBnProchaClick(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall BtReportBasClick(TObject *Sender);
	void __fastcall RGCouSClick(TObject *Sender);
	void __fastcall BtBnSimulerClick(TObject *Sender);
	void __fastcall BtBnMazClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall PCChanging(TObject *Sender, bool &AllowChange);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall GrilleInvValKeyPress(TObject *Sender, char &Key);
	void __fastcall BtBnSansBorneClick(TObject *Sender);
	void __fastcall LBTroupeauClick(TObject *Sender);
	void __fastcall BtBnSupClick(TObject *Sender);
	void __fastcall BtBnRienClick(TObject *Sender);
	void __fastcall TVResultatClick(TObject *Sender);
	void __fastcall GrilleMaxiMouseDown(TObject *Sender,
			TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall GrilleMaxiMouseMove(TObject *Sender, TShiftState Shift,
			int X, int Y);
	void __fastcall GrilleMaxiMouseUp(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
	void __fastcall BtBnMazVenteAchatClick(TObject *Sender);
	void __fastcall BtBnMazMvtClick(TObject *Sender);

private:// Déclarations de l'utilisateur
	TTabSheet* DernierePage;
	bool AStocker;
	bool ASimuler;
	int Col0;
	TList *LstMvtAni;
//    TList   *LstAchat; //contient les AACHETER  pour ne pas modifier structure du fichier oly
	void __fastcall Debuter(void);
	void __fastcall CreeLstAchat(void);
	bool __fastcall VerifTroupeauEnCours(void);
	CL_InvAni* __fastcall TrouveInvAni(int no,CL_Bestiaux *animal,CL_Vecteur<CL_InvAni>*vInvAni);

//TroupeauIni
	void __fastcall IniTSNature(void);
	void __fastcall IniTSResultats(void);

	void __fastcall IniGrilleNum(TStringGrid *grille,int larCol);
	void __fastcall IniGrilleMvt(TStringGrid *grille);
	void __fastcall IniGrilleValInv(TStringGrid *grille);

	void __fastcall VersGrilleMaxi(TStringGrid *grille);
	void __fastcall VersGrillePrix(TStringGrid *grille);
	void __fastcall VersGrilleValInv(TStringGrid *grille);
	void __fastcall VersGrilleMvt(TStringGrid *grille);
	void __fastcall VersGrilleProCha(TStringGrid *grille);
	void __fastcall VersGrilleAchat(TStringGrid *grille);
	void __fastcall VersGrillePrixAchat(TStringGrid *grille);

//TroupeauDE
	void __fastcall DeGrilleMaxi(TStringGrid *grille);
	void __fastcall DeGrillePrix(TStringGrid *grille);
	void __fastcall DeGrilleAchat(TStringGrid *grille);
	void __fastcall DeGrillePrixAchat(TStringGrid *grille);

	void __fastcall DeGrilleValInv(TStringGrid *grille);
	void __fastcall DeGrilleProCha(TStringGrid *grille);
	void __fastcall CreeLstMvtAni(void);
	void __fastcall EtablitAchatPrixAchat(void);

	void __fastcall BtRepDroitNum(void);
	void __fastcall BtRepDroitProCha(void);
	void __fastcall BtRepBasNum(void);
	void __fastcall BtRepBasProCha(void);
//TroupeauMvt
	void __fastcall Filiation(void);
	bool __fastcall RemplitLesMvtAnnee(void);
	void __fastcall EffaceVente(void);
	int TrouveColOrigine(int no,CL_MvtAnnee *mvtOr);
	int TrouveColDest(int no,CL_MvtAnnee *mvtDest);
	int TrouveColVente(CL_MvtAnnee *mvt,float prixMoy);
// utilitaire
	int __fastcall TrouverNoAnimal(int r);
	CL_InvAni* __fastcall TrouverAnimalNo(int no);
//	CL_MvtAnnee* __fastcall TrouverMvt(int noAnimal,int c);
	void __fastcall MazTout(void);
//TroupeauEffVal
	void __fastcall CompleteInvAni(void);
//TroupeauBouton
	void __fastcall ProChaQ(void);
	void __fastcall ProChaV(void);
	void __fastcall EnsembleEffectif(int qOuV,int aOuV);

	void IniLesTreeView(void);//250507

protected:
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
	void __fastcall SansSimuler(void);
	void __fastcall EffConstant(void);

public:// Déclarations de l'utilisateur
	int Origine;
	int An_0;
	CL_Agriculteur *Agri;
	CL_Troupeau *TroupeauEnCours;
	bool Erreur;
	__fastcall TTroupeauFrm(TComponent* Owner);
	//pour test
	void __fastcall EcritLstMvtAni(TList *lstMvtAni);

	// utilisés par MvtAnneeFrm
	void __fastcall Simuler(void);
	void __fastcall AffEffectifs(void);
//    int __fastcall TrouverLigne(int noAnimal);

	void TexteCaption(void);
	void IniCaption(void);
	void TexteChaine(void);

	AnsiString L_Recommencer;

	AnsiString LC_LabPrix;
	AnsiString LC_LabAchat;
	AnsiString LC_RBEcran;
	AnsiString LC_LabEffMax;
	AnsiString LC_BtEffectif;
	AnsiString LC_GroupBox1;
	AnsiString LC_TSMaxi;
	AnsiString LC_MvtAnneeFrm;
	AnsiString LC_DefBestiauxFrm;
	AnsiString LC_RGNatureG;
	AnsiString LC_LabNomTroupeau;
	AnsiString LC_TSPrixAchat;
	AnsiString LC_LabPrixAchat;
	AnsiString LC_TSPrix;
//    AnsiString LC_[0]TLabel;
	AnsiString LC_BtBnResultat;
	AnsiString LC_LabResTroup;
	AnsiString LC_BtBnRien;
	AnsiString LC_BtBnSansBorne;
	AnsiString LC_BtBnSimuler;
	AnsiString LC_GBSortie;
	AnsiString LC_BtBnSupBesTrav;
	AnsiString LC_LBChoixBestiauxFrm;
	AnsiString LC_GBTrARetenir;
	AnsiString LC_LabNature;
	AnsiString LC_TSValInv;
	AnsiString LC_LabValInv;

	AnsiString LC_PrixAchat;//090206
	AnsiString LC_ProCha;
	AnsiString LC_ProChaT;
	AnsiString LC_AvecMvt;
	AnsiString LC_Constant;
	//180507
	AnsiString LC_Procha;

	AnsiString LC_Effectif;
	AnsiString LC_Achat;
	AnsiString LC_Vente;
	AnsiString LC_Valeur;
	AnsiString LC_Inventaire;
	AnsiString LC_ProdCha;
	AnsiString LC_Quantite;
	AnsiString LC_LabFinAnnee;

	AnsiString LC_EffAchat;
	AnsiString LC_EffVente;
	AnsiString LC_ValAchat;
	AnsiString LC_ValVente;
	AnsiString LC_ValInv;

	AnsiString LC_MazVenteAchat;
	AnsiString LC_MazMvt;

};
//---------------------------------------------------------------------------
extern PACKAGE TTroupeauFrm *TroupeauFrm;
//---------------------------------------------------------------------------
#endif
