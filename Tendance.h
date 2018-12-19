//---------------------------------------------------------------------------

#ifndef TendanceH
#define TendanceH
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
class TTendanceFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtReportDroit;
	TBitBtn *BtReportBas;
	TBitBtn *BtRecopBas;
	TBitBtn *BtSup;
	TButton *BtDonnees;
	TEdit *EdNom;
	TLabel *LabTitre;
	TRadioGroup *RGPcentVal;
	void __fastcall FormCreate(TObject *Sender);
//    void __fastcall ProduitClick(TObject *Sender);
//    void __fastcall ChargeClick(TObject *Sender);
	void __fastcall BtDonneesClick(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall BtReportBasClick(TObject *Sender);
	void __fastcall BtRecopBasClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
//    void __fastcall BtValPcentClick(TObject *Sender);
	void __fastcall BoutFermerClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BoutAnnulClick(TObject *Sender);
//    void __fastcall ProduitSceClick(TObject *Sender);
//    void __fastcall ChargeSceClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall RGPcentValClick(TObject *Sender);

protected:
//	virtual bool __fastcall ControleCell(int col,int row);
	virtual void __fastcall CellDebut(void);
	virtual void __fastcall SaisirCell(int col,int row);
	virtual bool __fastcall Stocker(void);
	virtual void __fastcall DesGrilles(void);
	virtual void __fastcall VersGrille(TStringGrid *grille);

	virtual void __fastcall IniGrille0(void);

private:// Déclarations utilisateur
public:// Déclarations utilisateur
	int LEcran,HEcran;
	bool EstInitialise;
	void __fastcall Initialiser(void);
	void __fastcall PrepareEcran(void);
	bool __fastcall demanderNom(int nature,AnsiString nom);

	__fastcall TTendanceFrm(TComponent* Owner);
	void __fastcall Produit(int *nature);
	void __fastcall SupTendance(void);

	int Origine;
	int Type;//PRIX QUANTITE
	int RepChoix;
	int AFaire;
	CL_Tendance *Tendance;
	int Digits;//precision d'affichage dans les grilles
	CL_Vecteur<CL_Tendance> *V_Tendance;// ou V_TendProd ou V_TendCharge
	bool __fastcall CEstBon(void);

	//Tendance1
	void __fastcall TailleGrille(void);
	void __fastcall IniGrilleTendance(void);
//    void __fastcall IniGrille(void);

	void __fastcall VersGrilleTendance(CL_Vecteur<CL_Delta> *vecteur);
	void __fastcall ReAffGrilleTendance(void);
	// 2
	bool __fastcall VerifGrille(void);
	bool __fastcall VerifGrilleNom(void);
//    void __fastcall DesGrilles(void);
	void __fastcall DeGrilleTendance(CL_Vecteur<CL_Delta> *vecteur);

	//3
	void __fastcall SaisirCellTend(int col,int row);
	void __fastcall RepDroit(void);
	void __fastcall RepBas(int col,int row);
	void __fastcall RecopBas(int row);

};
//---------------------------------------------------------------------------
extern PACKAGE TTendanceFrm *TendanceFrm;
//---------------------------------------------------------------------------
#endif
