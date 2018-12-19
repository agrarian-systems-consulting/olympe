//---------------------------------------------------------------------------

#ifndef AgriDataH
#define AgriDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//---------------------------------------------------------------------------
class TAgriDataFrm: public TForm {
	__published: // Composants gérés par l'EDI
TOpenDialog	*OpenDialogFicCsv;
	TGroupBox *GBLangue;
	TComboBox *CBLangue;
	TRadioGroup *RGSeparateurCsv;
	TRadioGroup *RGSeparateurDecimal;
	TGroupBox *GBFicOlympe;
	TEdit *EdFicOlympe;
	TGroupBox *GBFicCSV;
	TEdit *EdFicCsv;
	TBitBtn *BtBnOK;
	TBitBtn *BtBnPasOk;
	TImage *ImFlecheBas;
	TGroupBox *GBFicResultat;
	TEdit *EdFicResultat;
	TOpenDialog *OpenDialogFicOlympe;
	TSaveDialog *SaveDialogFicResultat;
	TBitBtn *BtBnAide;
	void __fastcall EdFicCsvClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall BtBnPasOkClick(TObject *Sender);
	void __fastcall EdFicResultatClick(TObject *Sender);
	void __fastcall EdFicOlympeClick(TObject *Sender);
	void __fastcall BtBnAideClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private: // Déclarations de l'utilisateur
	TStringList *SLstErreur;
	int NoLi;
	bool IlYaErreur;

	AnsiString AsNature,AsType;

	char Delimiter,DecSep;
	void LireData(char *nomFichData);
	void LireNomAgri(CL_Agriculteur *agri,char *chaine);
	void CreerNomFicAStocker(char *nomFichData,char *stockerSous);

	void LireDelta(FILE *fichier,CL_Agriculteur *agri,char *chaine);
	bool LireDeltaPrix(FILE *fichier,AnsiString nom,CL_Vecteur<CL_Tendance>*vTendance,
			CL_Vecteur<CL_Item> *vItem);
	CL_Delta* TrouverDelta(CL_Tendance *tendance,AnsiString nom,AnsiString nomCat,
			CL_Vecteur<CL_Item> *vItem);

	bool LireDeltaQuantite(FILE *fichier,AnsiString nom,
			CL_Vecteur<CL_Tendance>*vTendance,int type);
	CL_Delta* TrouverDeltaQuantite(CL_Tendance *tendance,AnsiString nom,
			AnsiString nomAtelier,int type);
	CL_Atelier* TrouverAtelierQ(AnsiString nomAtelier,CL_Vecteur<CL_Atelier> *vAtelier);

	void LireAssolement(FILE *fichier,int nature,CL_Agriculteur *agri,
			CL_Vecteur<CL_Atelier> *vecteur,CL_Vecteur<CL_Categorie> *vCategorie);

	CL_Atelier* TrouveAtelier(AnsiString asNom,AnsiString asCat,
			CL_Vecteur<CL_Atelier> *vAtelier,CL_Vecteur<CL_Categorie> *vCategorie);
	void LireValeur(float *valeur,char *chaine,int nMax);

	void LirePerenne(FILE *fichier,CL_Agriculteur *agri);
	CL_Atelier* TrouvePerenne(AnsiString asNom,AnsiString asEspece);
	CL_Espece* TrouveEspece(AnsiString asEspece);

	void LireVariable(FILE *fichier,CL_Agriculteur *agri);
	CL_Item* TrouveItem(AnsiString asNom,AnsiString asCat,CL_Vecteur<CL_Item> *vItem);

	void LireFormule(FILE *fichier,CL_Agriculteur *agri,int nature);
	CL_Formule* TrouveFormule(AnsiString asNom,AnsiString asCat,CL_Vecteur<CL_Formule> *vFormule);
	void CreerFormuleProg(CL_Formule *formule);

	void LireImmoGlobal(FILE *fichier,CL_Agriculteur *agri);
	void LireMateriel(FILE *fichier,CL_Agriculteur *agri);
	void LirePetitMateriel(FILE *fichier,CL_Agriculteur *agri);
	void LireFinGlobal (FILE *fichier,CL_Agriculteur *agri);
	void LireFN_Xp1(CL_Vecteur<CL_FN_Xp1>*vecteur,int no,int nbVal,char *chaine);

	AnsiString Trouve(AnsiString as,TStringList *sLAsIdent,TStringList *sLAsTrad);

	void LireResultats(void);
	void AffResultats(void);
	void Erreur(AnsiString message);

public:// Déclarations de l'utilisateur
	void LireLigneCommande(void);
	void LireIdent(int noLangue);

	void ImportDelta(void);

	AnsiString L_Agriculteur;
	AnsiString L_Assolement;
	AnsiString L_Animaux;
	AnsiString L_Perenne;
	AnsiString L_Variable;
	AnsiString L_Nom;

	AnsiString L_Delta;
	AnsiString L_Prix;
	AnsiString L_Quantite;
	AnsiString L_Produit;
	AnsiString L_Charge;

	AnsiString L_ChStruct;//110607
	AnsiString L_DepDiv;
	AnsiString L_DepPriv;
	AnsiString L_RecDiv;
	AnsiString L_RecPriv;

	AnsiString L_Tendance;
	AnsiString L_Scenario;

	AnsiString L_Immo;
	AnsiString L_Materiel;
	AnsiString L_Finance;

	AnsiString L_ValResid;
	AnsiString L_Amor;
	AnsiString L_Achat;

	AnsiString L_Dette;
	AnsiString L_RembCap;
	AnsiString L_Interet;
	AnsiString L_PetitMateriel;

	AnsiString L_Resultat;
	AnsiString L_Standard;
	AnsiString L_Comparaison;

	AnsiString L_Synthese;
	AnsiString L_RecDepense;
	AnsiString L_RecDepGP;
//    AnsiString L_Quantite;
	AnsiString L_CEG;
	AnsiString L_Bilan;

	__fastcall TAgriDataFrm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAgriDataFrm *AgriDataFrm;
//---------------------------------------------------------------------------
#endif
