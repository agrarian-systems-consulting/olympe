//---------------------------------------------------------------------------

#ifndef AtelierMDetailPerenneH
#define AtelierMDetailPerenneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AtelierMDetail.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAtelierMDetailPerenneFrm: public TAtelierMDetailFrm {
	__published: // Composants gérés par l'EDI
//	virtual void  __fastcall Personnaliser(void);
//	virtual void __fastcall  DefinirLesGrilles(void);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
protected:
	virtual void __fastcall IniGrille(TStringGrid *grille);virtual void __fastcall VersGrille(TStringGrid *grille);

private:
	// Déclarations utilisateur
//    char *Titre;//seult pour object
//    char *Total;
//    char *Marge;
	void __fastcall VersGrilleItem (int &row,int nature,
			TList *lstItem,TList *lstValeur, float &moyTotal);

//    void __fastcall  VersGrilleItem (int &row,int nature,
//    		CL_Vecteur<CL_ItemParAtelier> *vecteur,float &moyTotal);
	void __fastcall VersGrilleVolume(int &row,
			CL_Vecteur<CL_ItemParAtelier> *vecteur,TList *lstQuantProd,
			TList *lstItemProd,float &moyTotal);void __fastcall AffTotal(int &row,int nbPhase,float *total,char *titre);
	/*
	 void TotaliserProdCha(int nbPhase,
	 CL_Vecteur<CL_ItemParAtelier>*vItemPA,
	 float* piedHa,
	 CL_Vecteur<CL_ItemParAtelier>*vQParPied,
	 TList *lstItem,TList *lstValeur);
	 */
public:
	// Déclarations utilisateur
	CL_Atelier *Atelier;
	int DureePhase[N_PHASE + 1];
	float TotalHeure(CL_Espece *espece, float *TotHeureAn);

	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_AtelierMDetailPerenneFrm;
	AnsiString LC_LabTotal;

	__fastcall TAtelierMDetailPerenneFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAtelierMDetailPerenneFrm *AtelierMDetailPerenneFrm;
//---------------------------------------------------------------------------
#endif
