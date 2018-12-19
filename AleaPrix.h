//---------------------------------------------------------------------------

#ifndef AleaPrixH
#define AleaPrixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TAleaPrixFrm: public TForme00Frm {
	friend class TAleaRdtFrm;
	__published: // Composants gérés par l'EDI
TBitBtn	*BtReportDroit;
	TBitBtn *BtReportBas;
	TBitBtn *BtRecopBas;
	TBitBtn *BtSup;
	TButton *BtDonnees;
	TRadioGroup *RGPcentVal;
	TLabel *LabNom;
	TLabel *LabTitre;
	TBitBtn *BtBnVideTout;
	TBitBtn *BtBnNotes;
	TBitBtn *BtBnPcent;
	TRadioGroup *RGPrecision;
	TBitBtn *BtBnVersExcel;
	TBitBtn *BtBnDExcel;
	void __fastcall FormCreate(TObject *Sender);
//    void __fastcall ProduitClick(TObject *Sender);
//    void __fastcall ChargeClick(TObject *Sender);
	void __fastcall BtDonneesClick(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall BtReportBasClick(TObject *Sender);
	void __fastcall BtRecopBasClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BoutAnnulClick(TObject *Sender);
//    void __fastcall ProduitSceClick(TObject *Sender);
//    void __fastcall ChargeSceClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall RGPcentValClick(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall BtBnPcentClick(TObject *Sender);
	void __fastcall RGPrecisionClick(TObject *Sender);
	void __fastcall BtBnVersExcelClick(TObject *Sender);
	void __fastcall BtBnDExcelClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);

protected:
//	virtual bool __fastcall ControleCell(int col,int row);
//	virtual void __fastcall CellDebut(void);
//	virtual void __fastcall SaisirCell(int col,int row);
//	virtual bool __fastcall Stocker(void);
	virtual void __fastcall DesGrilles(void);
	virtual void __fastcall VersGrille(TStringGrid *grille);

	virtual void __fastcall IniGrille0(void);

private:// Déclarations utilisateur
	AnsiString L_Base;
	AnsiString LC_Pcent;
	AnsiString LC_Valeur;

protected:
	int Digits;

public:// Déclarations utilisateur

	int LEcran,HEcran;
	bool EstInitialise;
	int GrilleALire;// ou % ou prix/rdt
	AnsiString TitreColonne2;
	void __fastcall Initialiser(void);
//    void __fastcall BaptiseBouton(void);
//    bool __fastcall demanderNom(int *nature,AnsiString nom);

	__fastcall TAleaPrixFrm(TComponent* Owner);
	void __fastcall Produit(int *nature);
//    void __fastcall SupTendance(void);

	int Nature[4];
	// nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;nature[3]=0 branche NON déployée
	//           QUANTITE       CHARGE            SCENARIO           1 branchz déployée
	//                          EXTER

	int Origine;
	int RepChoix;
	int AFaire;
	CL_Tendance *Tendance;
	int DigitsPrix;//precision d'affichage dans les grilles
	int DigitsRdt;//precision d'affichage dans les grilles
//    CL_Vecteur<CL_Tendance> *V_Tendance; // ou V_TendProd ou V_TendCharge
//    bool __fastcall CEstBon(void);

	//Tendance1
	void __fastcall TailleGrille(void);
	void __fastcall IniGrilleTendance(void);
//    void __fastcall IniGrille(void);

//    void __fastcall ReAffGrilleTendance(void);
	// 2
//	bool __fastcall VerifGrille(void);
//    bool __fastcall VerifGrilleNom(void);
//    void __fastcall DesGrilles(void);
//    void __fastcall DeGrilleTendance(CL_Vecteur<CL_Delta> *vecteur);

	//3
//    void __fastcall SaisirCellTend(int col,int row);
//    void __fastcall RepDroit(void);
//    void __fastcall RepBas(int col,int row);
//    void __fastcall RecopBas(int row);

	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtDonnees;
	AnsiString LC_LabNom;
	AnsiString LC_LabTitre;
	AnsiString LC_AleaPrixFrm;

};
//---------------------------------------------------------------------------
extern PACKAGE TAleaPrixFrm *AleaPrixFrm;
//---------------------------------------------------------------------------
#endif
