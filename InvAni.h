//---------------------------------------------------------------------------

#ifndef InvAniH
#define InvAniH
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

//---------------------------------------------------------------------------
class CL_MvtAnnee;

class TInvAniFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabEffectif;
	TBitBtn *BtBnEAchat;
	TBitBtn *BtBnEVente;
	TLabel *LabValeur;
	TBitBtn *BtBnVAchat;
	TBitBtn *BtBnVVente;
	TBitBtn *BtBnInventaire;
	TRadioGroup *RGCouS;
	TBitBtn *BtBnDemarrer;
	TComboBox *CBCatAnimaux;
	TLabel *LabCatAnimaux;
	TBitBtn *BtBnRecommencer;
	TLabel *LabEffFin;
	TBitBtn *BtBnMax;
	TBitBtn *BtBnProCha;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnEAchatClick(TObject *Sender);
	void __fastcall BtBnEVenteClick(TObject *Sender);
	void __fastcall BtBnVAchatClick(TObject *Sender);
	void __fastcall BtBnVVenteClick(TObject *Sender);
	void __fastcall BtBnInventaireClick(TObject *Sender);
	void __fastcall RGCouSClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnDemarrerClick(TObject *Sender);
	void __fastcall CBCatAnimauxClick(TObject *Sender);
	void __fastcall BtBnRecommencerClick(TObject *Sender);
	void __fastcall BtBnMaxClick(TObject *Sender);
	void __fastcall BtBnProChaClick(TObject *Sender);
//    void __fastcall BtBnQuitterClick(TObject *Sender);
private:// Déclarations utilisateur
//    TStringGrid  *GrilleInv;
	CL_Agriculteur *Agri;
	CL_InvAni *InvAni;
	CL_MvtAnnee *MvtAnnee;

	void __fastcall Personnaliser(void);
	void __fastcall Demarrer(void);
	void __fastcall DefinirLesGrilles(void);
	void __fastcall IniGrille(TStringGrid *grille);
	void __fastcall SaisirCell(int col,int row);
	bool __fastcall ControleCell(int col,int row);

	void __fastcall VersGrilleInvAni(CL_Vecteur<CL_InvAni> *vecteur);
	void __fastcall Filiation(void);
	void __fastcall RemplitLesMvtAnnee(void);
//    void __fastcall MvtInitial(void);

	void __fastcall EffConstant(void);
	void __fastcall Simuler(void);
	void __fastcall SansSimuler(void);
	int __fastcall TrouverLigne(int noAnimal);
	int __fastcall TrouverNoAnimal(int r);
	CL_MvtAnnee* __fastcall TrouverMvt(int noAnimal,int c);
	void __fastcall MarquerCell(TStringGrid *grille,int col,int row);

	void __fastcall Quitter(void);
	void __fastcall CreeLstMvtAni(void);
	void __fastcall VideLstMvtAni(void);

	void __fastcall CalculValeur(void);
	bool Erreur;

	friend class TMvtAniFrm;

public:// Déclarations utilisateur
	int An_0;
	int Origine;
	TStringGrid *GrilleInv;
	void __fastcall AffEffectifs(void);

	__fastcall TInvAniFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInvAniFrm *InvAniFrm;
//---------------------------------------------------------------------------
#endif
