//---------------------------------------------------------------------------

#ifndef CL_TradH
#define CL_TradH
#include <vcl.h>
#include <stdio.h>

//---------------------------------------------------------------------------
class CL_Trad {
public:
//    CL_Trad(void);

	bool LireTraduction(AnsiString asNature, char langue);
	void CreeTxtDialogue(void);
	void CreeTxtCaption(void);
	AnsiString TrouveTexte(AnsiString nomProg, AnsiString nomVar);

	AnsiString TrouveCaption(AnsiString nomProg, AnsiString nomVar);

	char* TrouveChaine(AnsiString nomProg, AnsiString nomVar);

	bool Erreur;
	FILE *FichierErreur;
private:
	void TexteCaption(void);

	void TexteChaine(void);

	void Francais(void);

	TStringList *SLNomProg, *SLNomVar;
	int TrouveDansSLNomProg(AnsiString asProg);

public:
	AnsiString L_Erreur;
	AnsiString L_DonModifQ;
	AnsiString L_DonModifT;

	AnsiString L_Utilise;
	AnsiString L_Modif;
	AnsiString L_SupQ;
	AnsiString L_SupT;
	AnsiString L_SupInutQ;
	AnsiString L_SupInutT;
	AnsiString L_SupToutQ;
	AnsiString L_SupLiQ;

	AnsiString L_EffaceQ;
	AnsiString L_EffaceT;

	AnsiString L_PasFinComm;
	AnsiString L_CarInco;
	AnsiString L_NbLong;
	AnsiString L_PasDeNom;

	AnsiString L_ParFerm;
	AnsiString L_ParOuv;
	AnsiString L_2Point;
	AnsiString L_Inco;
	AnsiString L_IdentInco;

	AnsiString L_Proc_PasDon;
	AnsiString L_Probleme;
	AnsiString L_Inconnu;

	AnsiString L_Act_Action;
	AnsiString L_Act_DescAction;
	AnsiString L_QuitQ;
	AnsiString L_QuitT;
	AnsiString L_Act_Reg1;
	AnsiString L_Act_Remplacer;
	AnsiString L_Act_Supprimer;
	AnsiString L_Act_Planter;
	AnsiString L_Act_Arracher;
	AnsiString L_Act_Investir;
	AnsiString L_Act_Emprunter;

	AnsiString L_Emp_Lt;
	AnsiString L_Emp_Total;
	AnsiString L_Emp_Ct;
	AnsiString L_Emp_Sub;
	AnsiString L_Emp_Plact;
	AnsiString L_Emp_Immo;

	AnsiString L_Poste;
	AnsiString L_Ceg;
	AnsiString L_Bilan;
	AnsiString L_Immobilisation;
	AnsiString L_Subvention;
	AnsiString L_Tva;
	AnsiString L_Emprunt;
	AnsiString L_Emprunt_LT;
	AnsiString L_Emprunt_CT;
	AnsiString L_Emprunt_Prive;
	AnsiString L_Mvt_Animaux;

	AnsiString L_Nom;
	AnsiString L_Cat;
	AnsiString L_Fam;
	AnsiString L_Nat;

	AnsiString L_Produit;
	AnsiString L_Charge;
	AnsiString L_ChfProd;
	AnsiString L_RecDiv;
	AnsiString L_ChStruct;
	AnsiString L_DepDiv;
	AnsiString L_Culture;
	AnsiString L_Animaux;
	AnsiString L_Perenne;
	AnsiString L_Vivrier;
	AnsiString L_Tendance;
	AnsiString L_Scenario;

	AnsiString L_Exter;

	AnsiString L_Effectifs;
	AnsiString L_Eff_Vendus;
	AnsiString L_Eff_Achetes;
	AnsiString L_Val_Ventes;
	AnsiString L_Val_Achats;
	AnsiString L_Val_Inv;
	AnsiString L_Avt1;

	AnsiString L_TotalM;
	AnsiString L_Total;

	AnsiString L_Agri;
	AnsiString L_Atelier;
	AnsiString L_NonDef;
	AnsiString L_Impo;
	AnsiString L_Marge;
	AnsiString L_MargeHeure;
	AnsiString L_PasUnite;
	//100206
	AnsiString L_CatAElt;

//caption
	AnsiString LC_BtBnAlpha;
	AnsiString LC_LabAchat;
	AnsiString LC_GBAgri;
	AnsiString LC_AleaRdtFrm;
	AnsiString LC_GBAlea;
	AnsiString LC_GBAn;
	AnsiString LC_Assolement;
	AnsiString LC_AtelierFrm;
	AnsiString LC_GBAtelier;
	AnsiString LC_BtIndAucun;
	AnsiString LC_BtAutreAgri;
	AnsiString LC_RG;
	AnsiString LC_RGCat;
	AnsiString LC_LabPCharge;
	AnsiString LC_BtClasser;
	AnsiString LC_LabZone;
	AnsiString LC_GBCode;
	AnsiString LC_Commercialisation1;
	AnsiString LC_GereComparaisonFrm;
	AnsiString LC_GBCondition;
	AnsiString LC_BtBnCopier;
	AnsiString LC_BtBnCopier_A;
	AnsiString LC_BtBnCourbe;
	AnsiString LC_BtBnCreer;
	AnsiString LC_GBDefinition;
	AnsiString LC_ChargesDivers;
	AnsiString LC_BtDico;
	AnsiString LC_BtBnDico;
	AnsiString LC_DIVERS1;
	AnsiString LC_BtDonnees;
	AnsiString LC_Label11;
	AnsiString LC_RBEcran;
	AnsiString LC_BtEffectif;
	AnsiString LC_CreancesDettes1;
	AnsiString LC_BtEnsEnCours;
	AnsiString LC_ChBEnsemble;
	AnsiString LC_GBEnsemble;
	AnsiString LC_ErreurFrm;
	AnsiString LC_DefEtatSortieFrm;
	AnsiString LC_TSExternalite;
	AnsiString LC_BtBnFermer;
	AnsiString LC_TabSheetG;
	AnsiString LC_Immo;
	AnsiString LC_LabIndicateur;
	AnsiString LC_GBAtelier_A;
	AnsiString LC_IntituleP;
	AnsiString LC_LabNom;
	AnsiString LC_LabSais;
	AnsiString LC_GereAgriFrm;
	AnsiString LC_GereEnsembleFrm;
	AnsiString LC_LabelModifie;
	AnsiString LC_BtBnMarge;
	AnsiString LC_BtModifier;
	AnsiString LC_RGModifiable;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtMotCle;
	AnsiString LC_MvtAnneeFrm;
	AnsiString LC_DefBestiauxFrm;
	AnsiString LC_RGNatureG;
	AnsiString LC_BtBnEffacer;
	AnsiString LC_Nom;
	AnsiString LC_NomAgri;
	AnsiString LC_NomAgri_A;
	AnsiString LC_NomPro;
	AnsiString LC_NomUnite;
	AnsiString LC_BtBnNotes;
	AnsiString LC_BtNouveau;
	AnsiString LC_Occc;
	AnsiString LC_PanClassif;
	AnsiString LC_PetitMatriel;
	AnsiString LC_EspeceFrm;
	AnsiString LC_RGPrecision;
	AnsiString LC_GBPrix;
	AnsiString LC_LabProcedure;
	AnsiString LC_PRODUCTIONS;
	AnsiString LC_LabPProduit;
	AnsiString LC_BtBnProduit;
	AnsiString LC_TLabel;
	AnsiString LC_GBQuantite;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_BtBnRafraichir;
	AnsiString LC_Produits1;
	AnsiString LC_Definition;
	AnsiString LC_ChBRepTout;
	AnsiString LC_RESULTATS;
	AnsiString LC_BtBnResultat;
	AnsiString LC_GBSortie;
	AnsiString LC_S1;
	AnsiString LC_Structure1;
	AnsiString LC_BtBnSupBesTrav;
	AnsiString LC_BtSyntDetail;
	AnsiString LC_LBSysUnitFrm;
	AnsiString LC_TauxTva;
	AnsiString LC_TitreEtat;
	AnsiString LC_LabTotal;
	AnsiString LC_LabTotPcent;
	AnsiString LC_BtIndTous;
	AnsiString LC_TSTravail;
	AnsiString LC_Tresorerie;
	AnsiString LC_LBChoixBestiauxFrm;
	AnsiString LC_BtBnTva;
	AnsiString LC_DefZoneFrm;
	AnsiString LC_Unite;
	AnsiString LC_UniteMonnaie;
	AnsiString LC_BtBnUnite;
	AnsiString LC_LabUtilise;
	AnsiString LC_Val0;
	AnsiString LC_Val1;
	AnsiString LC_Val10;
	AnsiString LC_Val11;
	AnsiString LC_Val2;
	AnsiString LC_Val3;
	AnsiString LC_Val4;
	AnsiString LC_Val5;
	AnsiString LC_Val6;
	AnsiString LC_Val7;
	AnsiString LC_Val8;
	AnsiString LC_Val9;
	AnsiString LC_LabVal;
	AnsiString LC_ValeurEn;
	AnsiString LC_BtBnCalcul;
	AnsiString LC_VARIABLES;
	AnsiString LC_BtVariante;
	AnsiString LC_BtBnVenteQ;
// ajout manuel   Atelier
	AnsiString LC_LabTotDep;
	//100206
	AnsiString LC_Visible;
	AnsiString LC_NonVisible;

	AnsiString LC_EP;
	AnsiString LC_Entreprise;
	AnsiString LC_Prive;
	AnsiString LC_Interet;
	//010508
	AnsiString LC_Oui;
	AnsiString LC_Non;
	AnsiString LC_Debut;

};
#endif
