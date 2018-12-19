//---------------------------------------------------------------------------

#ifndef EcrireAccessH
#define EcrireAccessH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TEcrireAccessFrm: public TForm {
	__published: // Composants gérés par l'EDI
TSaveDialog	*SaveDialog;
	TProgressBar *ProgressBar;
	TProgressBar *ProgressBar1;
	//void __fastcall FormActivate(TObject *Sender);
private:// Déclarations de l'utilisateur
	int cpt;

	void EcrireFichierAccess(void);
	bool Dialogue_EcrireAccess(AnsiString *as, char file[]);
	void CreationRapport_EcrireAccess();
	void CreationTables_EcrireAccess(TADOQuery *adoQuery);
	void CreationClePrimaire_EcrireAccess(TADOQuery *adoQuery);
	void CreationCleEtrangere_EcrireAccess(TADOQuery *adoQuery);
	void InsertDonneesDefCat_EcrireAccess(TADOQuery *adoQuery,TADOTable *adoTable,TADOTable *adoTable1);
	void InsertDonneesAutres_EcrireAccess(TADOQuery *adoQuery,TADOTable *adoTable,TADOTable *adoTable1);

	void MajTable(TADOTable *adoTable,AnsiString nomTable);
	void EcrireRapport(AnsiString info);
	void EcrireAte_PiedHaPer(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Atelier> *vAtelier, int nature,int ate);
	void EcrireAte_PiedHa(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Atelier> *vAtelier, int nature,int ate);
	void EcrireRepart(TADOTable *adoTable,AnsiString nomTable,TADOTable *adoTable1,AnsiString nomTable1,CL_Vecteur<CL_Repart> *vRepart);
	void EcrireDefinitions(TADOTable *adoTable,AnsiString nomTable);
	void EcrireAleas(TADOTable *adoTable,AnsiString nomTable);
	void EcrireAteliers(TADOTable *adoTable,AnsiString nomTable);
	void EcrireAteListItem(TADOTable *adoTable,AnsiString nomTable);
	void EcrireAgriValeur(TADOTable *adoTable,AnsiString nomTable);

	void EcrireSystemeUnite(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_SystemeUnite> *vecteur);
	void EcrireTva(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Tva> *vecteur);

	void EcrireCategorie(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Categorie> *vCategorie,int nature);
	void EcrireCatCalendrier(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Calendrier> *vCalendrier,int nature);
	void EcrireDef_ProCha(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Item> *vItem,int nature);
	void EcrireDef_ExtVar(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Item> *vItem,int nature);
	void EcrireDef_ChStructRecDep(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Item> *vItem,int nature);
	void EcrireDef_Critere(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Item> *vItem);
	void EcrireDef_Dico(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Item> *vItem);
	void EcrireDef_EtatSortie(TADOQuery *adoQuery, TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_EtatSortie> *vEtat, TADOTable *adoTable1);
	void EcrireDef_Calendrier(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Calendrier> *vCalendrier);
	//void EcrireDef_Periode(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Calendrier> *vCalendrier);
	void EcrireDef_Periode(TADOQuery *adoQuery,AnsiString nomTable,CL_Vecteur<CL_Calendrier> *vCalendrier);
	void EcrireDef_Bestiaux(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Bestiaux> *vBestiaux);

	void EcrireAleaCateg(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Tendance> *vTendance,int nature);
	void EcrireTendance(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Tendance> *vTendance,int nature,TADOQuery *adoQuery,int t, int natureDefinition);

	void EcrireAte_CatAtelier(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Categorie> *vCategorie,int nature);
	void EcrireAte_CatPerenne(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Espece> *vEspece,TADOQuery *adoQuery,int nature);

	void EcrireAte_Atelier(TADOTable *adoTable,AnsiString nomTable,int nature,CL_Vecteur<CL_Atelier> *vAtelier,int ate);
	void EcrireAte_Atelier(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Atelier> *vAtelier);

	void EcrireAte_Item(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Atelier> *vAtelier, int nature,int ate);
	void EcrireAte_ItemPer(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Atelier> *vAtelier, int nature,TADOQuery *adoQuery,int ate);

	void EcrireAte_BesTrav(TADOQuery *adoQuery,TADOTable *adoTable, TADOTable *adoTable1 ,AnsiString nomTable, AnsiString nomTable1,CL_Vecteur<CL_Atelier> *vAtelier, int ate);
	void EcrireAte_BesTrav_Item(TADOQuery *adoQuery, TADOTable *adoTable,AnsiString nomTable,CL_Matrice *besoin, int ate, int numAte, int numCal);
	void EcrireAte_Avance(TADOTable *adoTable, AnsiString nomTable,CL_Vecteur<CL_Atelier> *vAtelier, int ate);
	void EcrireAte_Immo(TADOTable *adoTable, AnsiString nomTable,CL_Vecteur<CL_Atelier> *vAtelier, int ate);
	void EcrirePhase(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Espece> *vEspece);
	void AdresseChFVol(CL_Vecteur<CL_Atelier> *vAtelier);

	void EcrireAgri(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);

	void EcrireAgri_DefSim(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgri_Critere(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriVariante(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriSerie(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);

	void EcrireAgriAssol(TADOTable *adoTable,AnsiString nomTable,int nature,CL_Vecteur<CL_Agriculteur> *vAgri,TADOQuery *adoQuery);
	void EcrireAgriPerenne(TADOTable *adoTable,AnsiString nomTable,int nature,CL_Vecteur<CL_Agriculteur> *vAgri);

	void EcrireValeur(TADOTable *adoTable,float *valeur,int nbVal);

	void EcrireAgriFormule(TADOTable *adoTable, TADOTable *adoTable1,AnsiString nomTable,int nature,CL_Vecteur<CL_Agriculteur> *vAgri,TADOQuery *adoQuery);
	void EcrireAgriFormuleArbre(TADOQuery *adoQuery, TADOTable *adoTable, int noAgri, int idDef, int ident, int noItem, int idList, int noAn, CL_Arbre *Arbre);
	void EcrireAgriFormuleReseau(TADOTable *adoTable, int noAgri, int ident, int idDef, int idList, int noAn, CL_Reseau *Reseau);
	void EcrireAgriVariable(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri,TADOQuery *adoQuery);
	void EcrireAgriImmo(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriXXXGlobal(TADOTable *adoTable,AnsiString nomTable, int nature,CL_Vecteur<CL_Agriculteur> *vAgri,TADOQuery *adoQuery);
	void EcrireAgriEmpCT(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriEmpLT(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriSub(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriPlact(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriOccc(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriPetit(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriEnCours(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri,int nature);
	void EcrireAgriStockIni(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri,TADOQuery *adoQuery);
	void EcrireAgriPolStock(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeau(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauEff(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauVal(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauVente(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauAchat(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauValVente(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauValAchat(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauEffMax(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauNoAtelier(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauPVM(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauVIM(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgriTroupeauMvt(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	void EcrireAgri_RepartItem(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Agriculteur> *vAgri);
	//    void EcrireConversion(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Conversion> *vConversion);
	void EcrireEnsemble(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Ensemble> *vEnsemble);
	void EcrireEns_Eff(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Ensemble> *vEnsemble);
	void EcrireConversion(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_Conversion> *vConversion);
	void RequeteTable(TADOQuery *adoQuery,AnsiString nomTable,AnsiString asPhase);
	void EcrireProjet(TADOTable *adoTable,AnsiString nomTable,char file[MAXFILE]);
	void EcrireIndicateur(TADOTable *adoTable,TADOQuery *adoQuery,AnsiString nomTable,CL_Vecteur<CL_Indicateur> *vIndic);
	void EcrireArbre(TADOTable *adoTable,TADOQuery *adoQuery, CL_Vecteur<CL_Indicateur> *vIndic, int brancheMax);
	void EcrireReseau(TADOTable *adoTable,TADOQuery *adoQuery, CL_Vecteur<CL_Indicateur> *vIndic, int MailleMax);
	//void EcrireEtatSortie(TADOTable *adoTable,AnsiString nomTable,CL_Vecteur<CL_EtatSortie> *vEtat);
	//AnsiString RenommerFichier(AnsiString as,AnsiString asNom,AnsiString asExt);
	int TrouveLigne(int no,int **pereVS,int iMax);

public:// Déclarations de l'utilisateur
	void EcrireFichier(void);
	AnsiString L_Remplace;
	AnsiString L_RemplaceAll;
	AnsiString LC_Encours;
	AnsiString LC_Enregistrer;
	void TexteChaine (void);
	void TexteCaption (void);

	__fastcall TEcrireAccessFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEcrireAccessFrm *EcrireAccessFrm;
//---------------------------------------------------------------------------
#endif
