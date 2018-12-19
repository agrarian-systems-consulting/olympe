//---------------------------------------------------------------------------

#ifndef AtelierMDetailH
#define AtelierMDetailH
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
class TAtelierMDetailFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnSynthese;
	TLabel *LabTotal;
	TLabel *LabSais;
	TBitBtn *BtBnVersExcel;
	void __fastcall BtBnSyntheseClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnVersExcelClick(TObject *Sender);

private: // Déclarations utilisateur
	void __fastcall VersGrilleItem (int &row,int nature,
			TList *lstItem,TList *lstQuant);
//            CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall VersGrilleVolume(int &row,
			CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall AffTotal(int &row,int nbPhase,float *total,char *titre);

protected:
	//Atelier
	//Atelier1

	char *Titre;//seult pour object
	char *Total;
	char *Marge;
	//AnsiString Titre;//seult pour object
	//AnsiString Total;
	//AnsiString Marge;
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
	void __fastcall AffTrav(int row,CL_Atelier *atelier,
			CL_BesTrav *besTrav, float *marge,float margeTot);
	void TotaliserProdCha(int nbPhase,
			CL_Vecteur<CL_ItemParAtelier>*vItemPA,
			float* piedHa,
			CL_Vecteur<CL_ItemParAtelier>*vQParPied,
			TList *lstItem,TList *lstValeur);
	void Libere(TList *lstItemProd,TList *lstQuantProd,TList *lstItemCha,TList *lstQuantCha);

	AnsiString L_TitreGrille;
	AnsiString L_AvtQuant;
	AnsiString L_Quant;
	AnsiString L_QuantV;
	AnsiString L_QuantEt;
	AnsiString L_Valeur;
	AnsiString L_MargeDet;
	AnsiString L_Titre;
//    AnsiString L_Total;
//  AnsiString L_Marge;
	AnsiString L_MargeUnit;
//    AnsiString L_Produit;
//    AnsiString L_Charge;
	AnsiString L_SousTot;
	AnsiString L_TotProd;
	AnsiString L_TotCharge;
	//AnsiString L_ChfProd;
	AnsiString L_TotChvol;
	AnsiString L_Travail;
	AnsiString L_Besoins;
	AnsiString L_Heure;
//    AnsiString L_MargeHeure;
	AnsiString L_MargeDe;

public:// Déclarations utilisateur
	CL_Atelier *Atelier;
	float TotHeureAn[N_PHASE];
	float TotHeure;
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LabSais;
	AnsiString LC_AtelierMDetailFrm;
	AnsiString LC_BtSyntDetail;
	AnsiString LC_LabTotal;

	__fastcall TAtelierMDetailFrm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAtelierMDetailFrm *AtelierMDetailFrm;
//---------------------------------------------------------------------------
#endif
