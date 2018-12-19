//---------------------------------------------------------------------------
#ifndef ReClasseH
#define ReClasseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TReClasseFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panel1;
	TListBox *LB;
	TButton *BtOK;
	TButton *BtAnnule;
	TLabel *LabelModifie;
	TRadioGroup *RG;
	TBitBtn *BtHaut;
	TBitBtn *BtBas;
	void __fastcall BtHautClick(TObject *Sender);
	void __fastcall BtBasClick(TObject *Sender);
	void __fastcall LBClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtOKClick(TObject *Sender);
	void __fastcall BtAnnuleClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

	void __fastcall RGClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	int No;
	void __fastcall Remplacer(void);
	bool Fermer;
public:// Déclarations de l'utilisateur
	int Nature;
	int NoCat;
	CL_Vecteur<CL_Categorie> *VCat;
	CL_Vecteur<CL_SystemeUnite> *VSys;
	CL_Vecteur<CL_Tva> *VTva;
	CL_Vecteur<CL_Elt> *VElt;
	CL_Vecteur<CL_Item> *VItem;
	CL_Vecteur<CL_Valeur> *VValeur;
	CL_Vecteur<CL_Verger> *VVerger;
	void __fastcall ReClasser(void);

	__fastcall TReClasseFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReClasseFrm *ReClasseFrm;
//---------------------------------------------------------------------------
#endif
