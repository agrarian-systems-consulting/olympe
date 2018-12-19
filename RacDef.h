//---------------------------------------------------------------------------

#ifndef RacDefH
#define RacDefH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
/*
 #define STANDARD  1
 #define ETAT      2
 #define DICO      3
 #define POSTE     4
 #define COMP      5
 */
class CL_EltRac {
public:
	AnsiString Origine;
	AnsiString Famille;
	AnsiString Categorie;
	AnsiString Nom;
	char Type; //T table C Comparaison G Graphique
	AnsiString Alias;
	int NoOrigine;
	int NoFamille;
	int NoCategorie;
	int NoNom;
	CL_EltRac(void) {
		Origine = "";
		Famille = "  -";
		Categorie = "  -";
		Nom = "";
		Type = ' ';
		Alias = "";
		NoOrigine = 0;
		NoFamille = 0;
		NoCategorie = 0;
		NoNom = 0;
	}
	void DeSG(TStringGrid *sG, int r) {
		Famille = "  -";
		Categorie = "  -";
		Origine = sG->Cells[1][r];
		if (sG->Cells[2][r] != "")
			Famille = sG->Cells[2][r];
		if (sG->Cells[3][r] != "")
			Categorie = sG->Cells[3][r];
		Nom = sG->Cells[4][r];
		Type = sG->Cells[5][r][1];
		Alias = sG->Cells[6][r];
	}
	void VersSG(TStringGrid *sG, int r) {
		sG->Cells[1][r] = Origine;
		if (Famille != "  -")
			sG->Cells[2][r] = Famille;
		if (Categorie != "  -")
			sG->Cells[3][r] = Categorie;
		sG->Cells[4][r] = Nom;
		sG->Cells[5][r] = AnsiString(Type);
		sG->Cells[6][r] = Alias;
	}
};
//---------------------------------------------------------------------------
class TRacDefFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanH;
	TPanel *PanB;
	TPanel *PanD;
	TTreeView *TV;
	TStringGrid *SG;
	TLabel *LabelModifie;
	TGroupBox *GBClasser;
	TBitBtn *BtClHaut;
	TBitBtn *BtClBas;
	TBitBtn *BtSup;
	TBitBtn *BtBnVideTout;
	TBitBtn *BtBnSave;
	TBitBtn *BtBnClose;
	TBitBtn *BtBnTest;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TVChange(TObject *Sender, TTreeNode *Node);
	void __fastcall SGKeyPress(TObject *Sender, char &Key);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtBnClHautClick(TObject *Sender);
	void __fastcall BtBnClBasClick(TObject *Sender);
	void __fastcall BtBnSaveClick(TObject *Sender);
	void __fastcall SGClick(TObject *Sender);
	void __fastcall BtBnTestClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	TStringList *SLstCode;
	void VersSG(void);
	void DeSG(void);
	void TailleSG(int r);
	void EcrireFichier(void);
	void Concatener(void);
	void ConcatTV(TTreeView *tVDest,TTreeNode *tN0,TTreeView *tVSrc);
	void ConcatLB(TTreeView *tVDest,TTreeNode *tN0,TListBox *lBSrc);
	int TrouveLBNo(TListBox *lB,AnsiString as);
	TTreeNode* TrouveTVNo3(TTreeView *tV,CL_EltRac *eltRac);
	TTreeNode* TrouveTVNo1(TTreeView *tV,AnsiString as0,AnsiString as1);

	void Executer(CL_EltRac *eltRac);

public:// Déclarations de l'utilisateur
	TStringList *SLstRaccourci;
	void LireFichier(void);
	__fastcall TRacDefFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRacDefFrm *RacDefFrm;
//---------------------------------------------------------------------------
#endif
