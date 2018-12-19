//---------------------------------------------------------------------------

#ifndef Forme01H
#define Forme01H
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
class TForme01Frm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGPrecision;
	TBitBtn *BtBnMoin12;
	TBitBtn *BtBnPlus12;
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall RGPrecisionClick(TObject *Sender);
	void __fastcall Grille0DrawCell(TObject *Sender, int ACol, int ARow,
			TRect &Rect, TGridDrawState State);
	void __fastcall BtBnMoin12Click(TObject *Sender);
	void __fastcall BtBnPlus12Click(TObject *Sender);
private: // Déclarations utilisateur

public:// Déclarations utilisateur
	int Digits;
	AnsiString UtilisePar;
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);

	void __fastcall IniGrilleStandard(AnsiString titre,int nbCol,
			int nbRow,int an_0);
	void __fastcall IniGrilleTreso(AnsiString titre,int QouV,
			int nbRow,int an_0,int mois_0);
	void __fastcall IniGrilleEmprunt(AnsiString nature,AnsiString titre);
	void __fastcall IniGrilleTravail(TList *LstAtelier,TList *LstSousPeriodes,
//                                      TList *LstBesSousPer,
			float *TotBesSousPer,
			float *DispoSousPer,
			float *TravNec,
			int NbTrav,
			int an,
			TDateTime DtDebut);

	void __fastcall EcrireTitre(AnsiString titre);
	void __fastcall EcrireLigne(AnsiString titre,float *vecteur);
	void __fastcall EcrireLigneCol2(AnsiString titre,float *vecteur);

	void __fastcall EcrireLigne(AnsiString titre,int *vecteur);
	void __fastcall EcrireLigne(float *vecteur);
	void __fastcall EcrireLigneTresoValeur(AnsiString nom,float *flux,int mDeb);
	void __fastcall EcrireLigneTresoQuantite(AnsiString nom,AnsiString unite,float *flux,int mDeb);

	void IniGrilleImmo(CL_Agriculteur *agri,int nature);//300406

	AnsiString NatureGEmprunt;
//    AnsiString Titre;
	float *vecteur;
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString L_BesTrav;
	AnsiString L_DispoT;
	AnsiString L_TravNec;
	AnsiString L_TravDispo;
	AnsiString L_HDispo;
	AnsiString L_HManq;
	AnsiString L_HExces;

	AnsiString LC_RGPrecision;
	AnsiString LC_Forme01Frm;
	__fastcall TForme01Frm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForme01Frm *Forme01Frm;
//---------------------------------------------------------------------------
#endif
