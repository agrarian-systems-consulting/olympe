//---------------------------------------------------------------------------

#ifndef LesClassesH
#define LesClassesH
#include <vcl.h>
#include <iostream>
#include <fstream>
#include<string>
#include <stdio.h>
#define N_PHASE   100
#define N_X 10
//-----------------------------------------------------------
//-----------------------------------------------------------
//Classe de base
class CL_0 {
public:
	int No;
	AnsiString Nom;
	bool Supprimable;
	char Flag;
///        void EcrireXml(ofstream &fichier,char *nomE);
};
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

//-----------------------------------------------------------
//Categorie
class CL_Categorie: public CL_0 {
public:
	CL_Categorie() {
		Supprimable = true;
		No = 0;
		Nom = "";
		Flag = ' ';
	}
	;
	CL_Categorie(AnsiString nom, int no);
	int Cmp(CL_Categorie *cat);
	AnsiString Notes;
//        void EcrireXml(ofstream &fichier,char *nomE,int nb);
};
//-----------------------------------------------------------
//syteme d'unites
class CL_SystemeUnite: public CL_0 {
public:
	CL_SystemeUnite() {
		Ratio = 0;
		RatioG = 0;
		Supprimable = true;
		No = 0;
		Nom = "";
		Flag = ' ';
	}
	;
	CL_SystemeUnite(char *uUt, char *uTrans, char *uGlobal, float ratio,
			float ratioG);
	float Ratio; //Utrans/UUt
	float RatioG; //Uglobal/UUt
	AnsiString UUt; //unite de rdt ou d'utilisation UTILISATION
	AnsiString UTrans; //unite de vente ou d'achat     TRANSACTION
	AnsiString UGlobal; //unite pour résultat d'ensemble
	char Monnaie; // blanc ou qqchose signale que c'est une monnaie	bool   Supprimable;
	int Cmp(CL_SystemeUnite *ptr);
//        void EcrireXml(ofstream &fichier,char *nomE,int nb);
};
//----------------------------------------------------------------
//Tva
class CL_Tva: public CL_0 {
public:
	CL_Tva() {
		Supprimable = true;
		No = 0;
		Nom = "";
		Flag = ' ';
		Taux = 0;
		Defaut = 0;
	}
	;
	float Taux;
	int Defaut; //tva par defaut 1   tva immo =2
	int Cmp(CL_Tva *tva) {
		return true;
	}
	;
//    void EcrireXml(ofstream &fichier,char *nomE,int nb);

};
//----------------------------------------------------------------
// pour charge produit irrigation contient prix systeme unité
class CL_Item: public CL_0 {
public:
	CL_Item();
	CL_Item(CL_Item *anc);
	float Prix;
	int NoCategorie;
	CL_Categorie *Categorie;
	int NoSysteme;
	CL_SystemeUnite *SysUnite;
	int NoTva;
	CL_Tva *Tva;
	int Cmp(CL_Item *ptr);
//        void EcrireXml(ofstream &fichier,char *nomE,int nb);
};

//----------------------------------------------------------------
//-----------------------------------------------------------------
class CL_Espece: public CL_0 {
private:
public:
	CL_Espece();
	CL_Espece(CL_Espece *source);
	int Phase[N_PHASE];
	int DebAmor;
	int DurAmor;
	int NbPhase;
	int Cmp(CL_Espece *ptr) {
		return 0;
	}
	;
	//non utilisé
//??        void EcrireXml(ofstream &fichier,char *nomE,int nb);
};

//----------------------------------------------------------------
class CL_Atelier: public CL_0 {
public:
	CL_Atelier();
	CL_Atelier(const CL_Atelier *atelier);
	~CL_Atelier(void);
//??		void Deletevecteur(CL_Vecteur<CL_ItemParAtelier> *vecteur);
//??		void RecopieQuantite(CL_Vecteur<CL_ItemParAtelier> *vecteur,
//??			CL_Vecteur<CL_ItemParAtelier> *vecteurOr);
	int Nature;
	int NoEspece;
	CL_Espece *Espece;
	int NbPhase; //NbPhase=Espece->NbPhase+1
	int NoCategorie;
	int DebAmor; //031201
	int DurAmor; //031201
	bool Derobe; //240901
	// indique si on a définit des productions d'immo entreprise famille
	bool PImmoExiste; //011201
	bool PImmoFamExiste; //011201
	int Couleur, Motif, Ordre; //pour affichage travail

	AnsiString Notes; //281101
	CL_Categorie *Categorie;
	/*??
	 CL_Vecteur<CL_ItemParAtelier> *V_Charge;
	 CL_Vecteur<CL_ItemParAtelier> *V_ChargeVolume;
	 CL_Vecteur<CL_ItemParAtelier> *V_Produit;
	 CL_Vecteur<CL_ItemParAtelier> *V_Externalite;
	 CL_Vecteur<CL_EEF>            *V_Avance;     //301101
	 CL_Vecteur<CL_BesTrav>        *V_BesTrav;    //270802
	 //version >=131   280307
	 CL_Vecteur<CL_ItemParAtelier> *V_ProdPied;
	 CL_Vecteur<CL_ItemParAtelier> *V_ChPied;
	 */
	float PiedHa[N_PHASE];
	//CL_Vecteur<CL_EEF>            *V_Stock;      //190802
	// production d'immobilisation par l'entreprise par la famille
	float *ProdImmo; //301101
	float *ProdImmoFam; //301101
	float Surface[N_X];
	float ValInvRepro, ValInvAutre;
	int Cmp(CL_Atelier *ptr) {
		return 0;
	}
	; //non utilisé
	void SupMaFalse(void);
//??        void EcrireXml(ofstream &fichier,char *nomE,int nb);
};
//----------------------------------------------------------------
class CL_ItemParAtelier: public CL_0 {
public:
	CL_ItemParAtelier();
	CL_ItemParAtelier(const CL_ItemParAtelier *ptr);
	~CL_ItemParAtelier(void);
	CL_Item *Item;
	CL_ItemParAtelier *ItemPA; //pour les charges proportionnelles au volume   no_produit!=-1
	CL_Item *Charge;
	int NoItem;
	int NoCharge;
	int NoItemPA; //pour les charges proportionnelles au volume
	float Qte;
	float *QtePhase; //quantite par phase pour perennes
	int Cmp(CL_ItemParAtelier *ptr) {
		return 0;
	}
	;
	//non utilisé
//??        void EcrireXml(ofstream &fichier,char *nomE,int nb);
};

//---------------------------------------------------------------------------
#endif
