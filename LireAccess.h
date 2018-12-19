//---------------------------------------------------------------------------

#ifndef LireAccessH
#define LireAccessH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
/*
 #define CULTURE 1
 #define ANIMAUX 2
 #define PERENNE 3
 #define VIVRIER 4
 */
//---------------------------------------------------------------------------
class TLireAccessFrm: public TForm {
	__published: // Composants gérés par l'EDI
TOpenDialog	*OpenDialog;
	TProgressBar *ProgressBar;
	TProgressBar *ProgressBar1;
private: // Déclarations de l'utilisateur
	void ImpElt(void);
	void MajTable(TADOTable *adoTable,AnsiString nomTable);
	void EcrireRapport(AnsiString info);
	void LireSystemeUnite(TADOQuery *adoQuery,CL_Vecteur<CL_SystemeUnite> *vecteur);
	void LireTva(TADOQuery *adoQuery,CL_Vecteur<CL_Tva> *vecteur);
	void LireR_Def_Categ(TADOQuery *adoQuery,AnsiString nomTable,CL_Vecteur<CL_Categorie> *vCategorie);
	//	void LireR_DefCalendrier(TADOTable *adoTable,AnsiString nomTable);      //260509
//	void LireR_DefPeriode(TADOTable *adoTable,AnsiString nomTable);

	void LireR_Def_ProCha(TADOQuery *adoQuery,AnsiString nomTable,
			CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Item> *vItem);
	void LireR_Def_ExtVar(TADOQuery *adoQuery,AnsiString nomTable,
			CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Item> *vItem);

	void LireR_Def_ChStructRecDep(TADOQuery *adoQuery,AnsiString nomTable,
			CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Item> *vItem);

	void LireR_Def_Critere(TADOQuery *adoQuery,
			CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Item> *vItem);

	void LireR_Ate_CatAtelier(TADOQuery *adoQuery,AnsiString nomTable,CL_Vecteur<CL_Categorie> *vCategorie);
	void LireR_Ate_CatPerenne(TADOQuery *adoQuery);
	void LireR_DefBestiaux(TADOQuery *adoQuery);

	void LireR_Ate_Atelier(TADOQuery *adoQuery,AnsiString nomTable,int nature,
			CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Atelier> *vAtelier);
	void LireR_Ate_Atelier(TADOQuery *adoQuery);
	void LireQtePhase(TADOQuery *adoQuery,int nbPhase,float *qtePhase);
	void AdresseChFVol(CL_Vecteur<CL_Atelier> *vAtelier);
	void LireR_Ate_Item(TADOQuery *adoQuery,AnsiString nomTable,
			CL_Vecteur<CL_Atelier> *vAtelier);
	void LireR_Ate_PiedHa(TADOQuery *adoQuery,AnsiString nomTable,
			CL_Vecteur<CL_Atelier> *vAtelier);
	void LireR_Ate_Avance(TADOQuery *adoQuery);
	void LireR_Ate_Immo(TADOQuery *adoQuery);
	void LireR_Ate_BesTrav(TADOQuery *adoQuery);
	/*void LireR_Ate_BesTrav_Item(TADOQuery *adoQuery, int _idAteliers, int _idAteSousCateg,
	 int _idDefCateg, int _nbPeriodeCal, CL_Matrice *besoins);
	 */
	void LireR_Agri(TADOQuery *adoQuery);
	void LireR_Agri_DefSim(TADOQuery *adoQuery);
	void LireR_Agri_Critere(TADOQuery *adoQuery);

	void LireR_AgriAssol(TADOQuery *adoQuery,AnsiString nomTable,int nature);
	void LireR_AgriPerenne(TADOQuery *adoQuery,AnsiString nomTable,int nature);

	void LireValeur(TADOQuery *adoQuery,float *valeur,int nbVal=10);
	void LireR_AgriFormule(TADOQuery *adoQuery,TADOQuery *adoQuery1 ,AnsiString nomTable,int nature);
	void LireR_AgriVariable(TADOQuery *adoQuery);

	void LireR_AgriImmo(TADOQuery *adoQuery);
	void LireR_AgriXXXGlobal(TADOQuery *adoQuery,AnsiString nomTable,int nature);
	void LireR_AgriEmpCT(TADOQuery *adoQuery);
	void LireR_AgriEmpLT(TADOQuery *adoQuery);
	void LireR_AgriSub(TADOQuery *adoQuery);
	void LireR_AgriOccc(TADOQuery *adoQuery);
	void LireR_AgriPetit(TADOQuery *adoQuery);
	void LireR_AgriPlact(TADOQuery *adoQuery);
	void LireR_AgriEnCoursDette (TADOQuery *adoQuery);
	void LireR_AgriEnCoursCreance (TADOQuery *adoQuery);
	void LireR_Ensemble(TADOQuery *adoQuery);
	void LireR_EnsEff(TADOQuery *adoQuery);
	void LireR_AgriStockIni(TADOQuery *adoQuery);
	void LireR_AgriPolStock(TADOQuery *adoQuery);
	//--TP2012
	void LireR_Repart(TADOQuery *adoQuery, TADOQuery *adoQuery1);
	void LireR_AgriTroupeau(TADOQuery *adoQuery, TADOQuery *adoQuery1, TADOQuery *adoQuery2);
	void LireR_AgriTroupeauMVT(TADOQuery *adoQuery);
	//
	void LireR_DefCatCalendrier(TADOQuery *adoQuery);
	void LireR_DefCalendrier(TADOQuery *adoQuery);
	void LireR_AleaCateg(TADOQuery *adoQuery);
	void LireR_AleaItem(TADOQuery *adoQuery);
	void LireR_DefEtatSortie(TADOQuery *adoQuery, TADOQuery *adoQuery1);
	void LireR_DefSerieComp(TADOQuery *adoQuery, TADOQuery *adoQuery1);
	void LireR_DefConversion(TADOQuery *adoQuery);
	void LireR_Indicateur(TADOQuery *adoQuery);
	void LireR_AgriRepartItem(TADOQuery *adoQuery);
	CL_Arbre* lireArbre(TADOQuery *adoQuery, CL_Vecteur<CL_Indicateur> *vIndic);
	CL_Reseau* lireReseau(TADOQuery *adoQuery, CL_Vecteur<CL_Indicateur> *vIndic);

	heritage(CL_Agriculteur *agri);

	void LesAdresses(void);
	void __fastcall IniV_Elt(void);
	void TrouveTendScen(CL_AgriDefSim *defSim);

public:// Déclarations de l'utilisateur
	void LireFichier(void);
	AnsiString LC_Ouvrir;
	AnsiString L_Termine;
	void TexteChaine (void);
	void TexteCaption (void);

	__fastcall TLireAccessFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLireAccessFrm *LireAccessFrm;
//---------------------------------------------------------------------------
#endif
