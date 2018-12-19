//---------------------------------------------------------------------------
#ifndef BrouillonH
#define BrouillonH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <stdio.h>
#include <vcl\printers.hpp>
#include <Menus.hpp>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
//--------------

#include "Olympedec.h"
#include "LesClassesApp.h"

#define  MAIGRE 0
#define  GRAS   1

#define  COURIER    0
#define  NEWROMAN   1

class TFBrouillon: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panel1;
	TBitBtn *BtBnQuitter;
	TBitBtn *BtBnImprimer;
	TBitBtn *BtBnEffacer;
	TRadioGroup *RGOrientation;
	TRichEdit *Memo1;
	TBitBtn *BtBnExcel;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtBnImprimerClick(TObject *Sender);

	void __fastcall BtBnEffacerClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnExcelClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	AnsiString AsLambda;
	AnsiString AsBlanc;
	void placer(AnsiString ss,int pos);
	void placer(float val,int pos, int apresVirgule);
	AnsiString Marge1,Marge2,Marge3;
	int posNom,posUnite,posVal,delta;
	void videAsLambda(void);
	int size0;
	int size1;
	int size2;
	int LarTrait;
public:// Déclarations de l'utilisateur
	__fastcall TFBrouillon(TComponent* Owner);
	int EnCours;
	CL_Agriculteur *Agri;
	void Demarre(void);
	AnsiString __fastcall TexteCaption(CL_Agriculteur *agri);

	void TypeImp(char *police,int size,TColor couleur,char style);

	void Titre1(char *titre, TColor=clBlack);
	void Titre2(char *titre, TColor=clBlack);
	void Titre3(char *titre, TColor=clBlack);
	void Nom(char *nom, TColor=clBlack);
	void An(int an0, TColor=clBlack);
	void Trait(void);
	void Trait(int larTrait);
	void Blanc(int nli=1, TColor=clBlack);
	void EnTeteDate(void);

	//BrouResultat
	void ResultatAgriValeur(CL_Agriculteur *agri);
	void ResultatAgriQuantite(CL_Agriculteur *agri);
	void ResultatAgriExternalite(CL_Agriculteur *agri);
	void ResultatAgriTva(CL_Agriculteur *agri);

	void Quantite(CL_Agriculteur *agri);
	void CategorieQ(
			char *titre,
			CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vQuanVal);
	void Valeur(CL_Agriculteur *agri);
	void CategorieV(
			char *titre,
			CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vProduit,
			float *total,
			CL_Vecteur<CL_QuanVal> *vCatTot);
	void __fastcall trouveDelta(CL_Item *item,CL_Tendance *tendance,float *pcent);
	void Tva(CL_Agriculteur *agri);

	//BrouFinance
	void Externalite(CL_Agriculteur *agri);
	void Finance(CL_Agriculteur *agri);
	void ImpFinance(CL_TotEmp *totEmp,char *titre);
	void ImpPlacement(CL_TotEmp *totEmp,char *titre);
	void ImpSubvention(CL_Agriculteur *agri);
	void AnPluUn(int an0, TColor=clBlack);
	void ResultatBilan(AnsiString nom, float *valeur,int nX, TColor=clBlack);
	//BrouImmo
	void Immo(CL_Agriculteur *agri);
	void ImpImmobilisation(CL_AgriRes *resultat,char *titre);
	void ImpImmo(CL_TotImmo *totImmo,char *titre);
	void ImpPetit(CL_TotImmo *totImmo,char *titre);
	void ImpImmoTotal(CL_AgriRes *resultat,char *titre);

	//BrouEtat
	void Etat(CL_Agriculteur *agri,CL_EtatSortie *etat);
	CL_EtatSortie *EtatSortie;
	//Comparaison
	void Comparaison(CL_EtatSortie *serieComp,TList *lstElt,int an_0);
	TList *LstElt;
	int An_0;
	//BrouDiv
	void ImprimerLesDonnees(void);

	void SysUnite(CL_SystemeUnite *sysUnite, TColor=clBlack);
	void EnTeteSysUnite( TColor=clBlack);
	void Tva(CL_Tva *tva, TColor=clBlack);
	void EnTeteTva( TColor=clBlack);

	void ItemProCha(CL_Item *item, TColor=clBlack);
	void EnTeteProCharge( TColor=clBlack);
	void ItemNomTva(CL_Item *item, TColor=clBlack);
	void EnTeteNomTva( TColor=clBlack);
	void ItemNomUnite(CL_Item *item, TColor=clBlack);
	void EnTeteNomUnite( TColor=clBlack);
	void ItemNom(CL_Item *item, TColor=clBlack);
	void EnTeteNom( TColor=clBlack);
	void ItemNomAnimaux(CL_Item *item, TColor=clBlack);
	void EnTeteNomAnimaux(TColor couleur);
	bool EstVide(int *vecteur);
	bool EstVide(float *vecteur);

	void Resultat(AnsiString nom,AnsiString unite, float *valeur, TColor=clBlack);
	void Resultat(AnsiString nom, float *valeur, TColor=clBlack);
	void Resultat(AnsiString nom, int *valeur, TColor=clBlack);

	void Total(AnsiString nom, float *valeur, TColor=clBlack);

	void Espece(CL_Espece *espece, TColor couleur);
	void EnTeteEspece(TColor couleur);

	//BrouPerenne
	void ComptaPerenne(CL_Agriculteur *agri);
	//BrouCompta
	void Ceg(CL_Agriculteur *agri);
	void Bilan(CL_Agriculteur *agri);
	void Famille(CL_Agriculteur *agri);

private:
	bool Debut;

};
//---------------------------------------------------------------------------
extern TFBrouillon *FBrouillon;
//---------------------------------------------------------------------------
#endif
