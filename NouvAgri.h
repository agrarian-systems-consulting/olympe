//---------------------------------------------------------------------------
#ifndef NouvAgriH
#define NouvAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TNouvAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TStringGrid	*GrilleAgri;
	TPanel *PanelOK;
	TBitBtn *BtBnOk;
	TBitBtn *BtBnPasOk;
	TBitBtn *BtBnNotes;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall GrilleAgriClick(TObject *Sender);
//	void __fastcall LBTypeZoneClick(TObject *Sender);
	void __fastcall BtOKClick(TObject *Sender);
	void __fastcall BtPasOkClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtDonneesClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:// Déclarations de l'utilisateur
	void __fastcall CreeLBTypeZone(int c,int r,CL_Categorie *categorie);
	void __fastcall AffTitreGrille(void);
	void __fastcall ChangerNomVariantes(CL_Agriculteur *agri);//260902
	int __fastcall AffLesVariantes(CL_Agriculteur *agri,int r,int nP);
	bool __fastcall VerifNom(AnsiString nom);
	TList *LstCategorie;
	CL_Vecteur<CL_Agriculteur> *V_AgriDepart;
	void __fastcall copierV_Agriculteur(void);
//    void __fastcall numeroteLesFils(CL_Agriculteur *agri,ST_NoAgri *Ancetre,int nP);
	void __fastcall numeroteLesFils(CL_Agriculteur *agri,int nP);
	CL_Agriculteur* CopierSerie(CL_Agriculteur *agri,AnsiString nom);

public:// Déclarations de l'utilisateur
	__fastcall TNouvAgriFrm(TComponent* Owner);
	int AFaire;
	int Origine;
	bool AStocker;
	CL_Agriculteur *Agri;
	void __fastcall AffAgri(CL_Agriculteur *agri,int r);
	void __fastcall AffVariante(void);
	bool __fastcall SaisirNom(void);

	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtBnNotes;
	AnsiString LC_NouvAgriFrm;

	AnsiString L_Agri;
	AnsiString L_NbVar;
	AnsiString L_NoVar;
	AnsiString L_Existe;
	AnsiString L_Erreur;

	AnsiString L_CopieDe;
	AnsiString L_Modifier;
	AnsiString L_NouvAgri;
	AnsiString L_VarDe;
	AnsiString L_ACopSous;
	AnsiString L_ModNomEn;
	AnsiString L_ModNomVar;
	AnsiString L_VAR;
};
//---------------------------------------------------------------------------
extern PACKAGE TNouvAgriFrm *NouvAgriFrm;
//---------------------------------------------------------------------------
#endif

/*

 L_Agri
 L_NbVar
 L_NoVar
 L_Existe
 L_Erreur


 LC_CopieDe
 LC_Modifier
 LC_NouvAgri
 LC_VarDe
 LC_ACopSous
 LC_ModNomEn
 LC_ModNomVar
 LC_VAR
 */
