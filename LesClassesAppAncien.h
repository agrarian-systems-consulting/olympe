//---------------------------------------------------------------------------
#ifndef LesClassesAppH
#define LesClassesAppH

#include <Grids.hpp>
#include <stdio.h>
#include "CL_BesTrav.h"
#include "CL_Passe.h"
#include "CL_PossibOcPlact.h"

//---------------------------------------------------------------------------

// #include "Brouillon.h"
//atto 110498 destructeur pour CL_ItemParAtelier
//            destructeur pour CL_Agriculteur
//atto 200898
//-------------------------------------- ----------------------------------------
template<class T> class CL_Vecteur {
private:
//		int NoX;
public:
//    	CL_Vecteur(bool classe=false, int nbmax=20, int delta=20);
	CL_Vecteur();
	CL_Vecteur(CL_Vecteur *vecteur);
	~CL_Vecteur(void);
	int Nbmax;
	int Nbelt;
	int Delta;
	int NoX;
	int Flag;
	bool Classe; //Classé true/false
	T** Vecteur;
	void ins(T *ptr);
	void insSans(T *ptr);
	T* trouve(int no);
	T* trouve(AnsiString nom);
	void sup(T* ptr);
	void sup(int no);
	void remplace(T* ancien, T* nouveau);
	void purge(void);
	void nettoie(void);
	void vide(void);
	void SupMazTrue(void);
	void FlagMisA(char car);
	void FlagMisA(bool vraiFaux);
};

template<class T>
//CL_Vecteur<T>::CL_Vecteur(bool classe,int nbmax, int delta)
CL_Vecteur<T>::CL_Vecteur() {
	Nbmax = 5; //120; //nbmax
	Nbelt = 0;
	Delta = 5; //20; //delta
	NoX = 0;
	Classe = false; //classe;
	Flag = 0;
	Vecteur = new T*[Nbmax];
}
//-----------------------------------------------------------
//constructeur par recopie
template<class T>
CL_Vecteur<T>::CL_Vecteur(CL_Vecteur *vecteur) {
	T* t;
	Nbmax = vecteur->Nbmax;
	Nbelt = vecteur->Nbelt;
	Delta = vecteur->Delta;
	NoX = vecteur->NoX;
	Vecteur = new T*[Nbmax];
	for (int i = 0; i < Nbelt; i++) {
//        t=new T(vecteur->Vecteur[i]);
		t = new T;
		memcpy(t, vecteur->Vecteur[i], sizeof(T));
		Vecteur[i] = t;
	}
}
//destructeur
//-----------------------------------------------------------
template<class T>
CL_Vecteur<T>::~CL_Vecteur(void) {
	delete[] Vecteur;
	Vecteur = NULL;
}
//-----------------------------------------------------------
template<class T>
void CL_Vecteur<T>::ins(T *ptr) {
	T** vecteurBis;
	int i;
	int sens, l, ldeb, lfin;
	int pos;
	if (Nbelt >= Nbmax) {
		Nbmax += Delta;
		vecteurBis = new T*[Nbmax];
		for (i = 0; i < Nbelt; i++)
			vecteurBis[i] = Vecteur[i];
		delete[] Vecteur;
		Vecteur = vecteurBis;
	}

	ptr->No = NoX;
	NoX++;

	if (Classe == false) {
		Vecteur[Nbelt] = ptr;
	} else {
		sens = 0;
		l = 0;
		ldeb = 0;
		lfin = Nbelt - 1;
		while (lfin >= ldeb) {
			l = (lfin + ldeb) / 2;
			sens = ptr->Cmp(Vecteur[l]);
			if (sens < 0)
				lfin = l - 1; // il est au début
			else if (sens > 0)
				ldeb = l + 1; //il est à la fin
			else if (sens == 0)
				break;
		}
		if (sens > 0)
			pos = l + 1;
		else
			pos = l;
		if (pos < Nbelt) {
			for (int n = Nbelt; n > pos; n--)
				Vecteur[n] = Vecteur[n - 1];
		}
		Vecteur[pos] = ptr;
	}
	Nbelt++;
}
//-----------------------------------------------------------
template<class T>
void CL_Vecteur<T>::insSans(T *ptr) //sans donner numero
		{
	T** vecteurBis;
	int i;
	if (Nbelt >= Nbmax) {
		Nbmax += Delta;
		vecteurBis = new T*[Nbmax];
		for (i = 0; i < Nbelt; i++)
			vecteurBis[i] = Vecteur[i];
		delete[] Vecteur;
		Vecteur = vecteurBis;
	}
	Vecteur[Nbelt] = ptr;
	Nbelt++;
}
//-----------------------------------------------------------

template<class T>
void CL_Vecteur<T>::remplace(T* ancien, T* nouveau) {
	for (int i = 0; i < Nbelt; i++) {
		if (Vecteur[i]->No == ancien->No) {
			//       	delete Vecteur[i];
			Vecteur[i] = nouveau;
			break;
		}
	}
}

//-----------------------------------------------------------
template<class T>
T* CL_Vecteur<T>::trouve(int no) {
	int i;
	for (i = 0; i < Nbelt; i++) {
		if (Vecteur[i]->No == no)
			return Vecteur[i];
	}
	return NULL;
}
//-----------------------------------------------------------
template<class T>
T* CL_Vecteur<T>::trouve(AnsiString nom) {
	int i;
	for (i = 0; i < Nbelt; i++) {
		if (Vecteur[i]->Nom == nom)
			return Vecteur[i];
	}
	return NULL;
}
//-----------------------------------------------------------

template<class T>
void CL_Vecteur<T>::sup(int no) {
	int i;
	T* ptr;
	for (i = 0; i < Nbelt; i++) {
		if (Vecteur[i]->No == no) {
			ptr = Vecteur[i];
			delete ptr;
			for (int j = i; j < Nbelt - 1; j++)
				Vecteur[j] = Vecteur[j + 1];
			Nbelt--;
			return;
		}
	}
	return;
}

//-----------------------------------------------------------

template<class T>
void CL_Vecteur<T>::sup(T* ptr) {
	int i;
	for (i = 0; i < Nbelt; i++) {
		if (Vecteur[i] == ptr) {
			delete ptr;
			for (int j = i; j < Nbelt - 1; j++)
				Vecteur[j] = Vecteur[j + 1];
			Nbelt--;
			return;
		}
	}
	return;
}
//-----------------------------------------------------------
template<class T>
void CL_Vecteur<T>::purge(void) {
// utilisé en lecture de fichier pour ne pas entrer par erreur n fois les
// memes données
	for (int i = 0; i < Nbelt; i++)
		if (Vecteur[i])
			delete Vecteur[i];
	Nbelt = 0;
	NoX = 0;

}
//-----------------------------------------------------------
template<class T>
void CL_Vecteur<T>::vide(void) {
	Nbelt = 0;
	NoX = 0;

}
//-----------------------------------------------------------
template<class T>
void CL_Vecteur<T>::nettoie(void) {
	T* ptr;
// retire tous les éléments où Supprimable=true
	for (int i = 0; i < Nbelt; i++) {
		ptr = Vecteur[i];
		if (ptr->Supprimable == true) {
			delete ptr;
			ptr = NULL;
			for (int j = i; j < Nbelt - 1; j++)
				Vecteur[j] = Vecteur[j + 1];
			Nbelt--;
			i--;
		}
	}

}
//-----------------------------------------------------------

template<class T>
void CL_Vecteur<T>::SupMazTrue(void) {
	for (int i = 0; i < Nbelt; i++)
		Vecteur[i]->Supprimable = true;
}
//-----------------------------------------------------------

template<class T>
void CL_Vecteur<T>::FlagMisA(char car) {
	for (int i = 0; i < Nbelt; i++)
		Vecteur[i]->Flag = car;
}
//-----------------------------------------------------------

template<class T>
void CL_Vecteur<T>::FlagMisA(bool vraiFaux) {
	for (int i = 0; i < Nbelt; i++)
		Vecteur[i]->Flag = vraiFaux;
}
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//-----------------------------------------------------------
//-----------------------------------------------------------
//Categorie
class CL_Categorie {
public:
	CL_Categorie() {
		Supprimable = true;
	}
	;
	CL_Categorie(AnsiString nom, int no);
	int No;
	AnsiString Nom;
	bool Supprimable;
	int Cmp(CL_Categorie *cat);
	AnsiString Notes;
	char Flag;
};
//-----------------------------------------------------------
//syteme d'unites
class CL_SystemeUnite {
public:
	CL_SystemeUnite() {
		Ratio = 0;
		RatioG = 0;
		Supprimable = true;
	}
	;
	CL_SystemeUnite(char *uUt, char *uTrans, char *uGlobal, float ratio,
			float ratioG);
	int No;
	float Ratio; //Utrans/UUt
	float RatioG; //Uglobal/UUt
	AnsiString Nom;
	AnsiString UUt; //unite de rdt ou d'utilisation UTILISATION
	AnsiString UTrans; //unite de vente ou d'achat     TRANSACTION
	AnsiString UGlobal; //unite pour résultat d'ensemble
	char Monnaie; // blanc ou qqchose signale que c'est une monnaie	bool   Supprimable;
	bool Supprimable;
	int Cmp(CL_SystemeUnite *ptr);
	char Flag;
};
//----------------------------------------------------------------
//Tva
class CL_Tva {
public:
	CL_Tva() {
	}
	;
	int No;
	AnsiString Nom;
	float Taux;
	int Defaut; //tva par defaut 1   tva immo =2
	bool Supprimable;
	int Cmp(CL_Tva *tva) {
		return true;
	}
	;
	char Flag;
};
//----------------------------------------------------------------
//Tva Entreprise   à mettre CL_AgriRes
class CL_TvaEnt {
public:
	CL_TvaEnt();
	CL_TvaEnt(CL_TvaEnt *source);
	void MaZ(void);
	float Recu[N_X];
	float Verse[N_X];
	float AcompteAout[N_X];
	float AcompteNov[N_X];
	float AcompteFev[N_X];
	float AcompteMai[N_X];
	float RembTva[N_X];
	float Regul[N_X];
	float Solde[N_X];
};
//----------------------------------------------------------------
//Tva Entreprise Initiale à mettre CL_Agriculteur
class CL_TvaEntIni {
public:
	CL_TvaEntIni();
	CL_TvaEntIni(CL_TvaEntIni *ptr);
	float Recu;
	float Verse;
	float AcompteAout;
	float AcompteNov;
	float AcompteFev;
	float AcompteMai;
	float Regul;

};
//----------------------------------------------------------------
// pour charge produit irrigation contient prix systeme unité
class CL_Item {
public:
	CL_Item();
	CL_Item(CL_Item *anc);
	int No;
	float Prix;
	AnsiString Nom;
	int NoCategorie;
	CL_Categorie *Categorie;
	int NoSysteme;
	CL_SystemeUnite *SysUnite;
	int NoTva;
	CL_Tva *Tva;
	int NoOrigine; //seult utilisé pour NomAnimaux
	int DonneNo[4]; //       "            060103
	float DonnePcent[4]; //       "
	float ValInv; //       "  300903
	bool Supprimable;
	int Cmp(CL_Item *ptr);
	char Flag;
};
/*
 // utilise par CL_Agriculteur pour stocker NoZone *Zone dans une TList
 //----------------------------------------------------------------
 struct ST_NoItem
 {
 int No;
 CL_Item* Item;
 };
 */
//---------------------------------------------------------------------------
class CL_IntFloat {
public:
	CL_IntFloat();
	CL_IntFloat(CL_IntFloat *source);
	CL_IntFloat(int n, float v);
	int i;
	float Val;
	void FichierEcrire(FILE *fichier);
	void FichierLire(FILE *fichier);

};
//---------------------------------------------------------------------------
class CL_Repart {
public:
	CL_Repart();
	CL_Repart(CL_Repart *source);
	~CL_Repart();
	AnsiString Nom;
	int No;
	int NoCategorie;
	CL_Categorie *Categorie;
	bool Supprimable;
	int Cmp(CL_Repart *source);
	TList *LstPcent; //liste de CL_IntFloat mois 0 à 36 et pcent
//    float Pcent[36];
	float Total(void);
	float LireTotal(TStringGrid *SG);

	void FichierEcrire(FILE *fichier);
	void FichierLire(FILE *fichier);
	void GrilleEcrire(TStringGrid* sg, float valTot);
	void GrilleLire(TStringGrid* SG);
	float LireCell(TStringGrid* SG, int col, int row);
	// il faut creer une classe ES cf Mangalere
	AnsiString Aff(float x);
	AnsiString Aff(float x, int digits);
	//CL_Outil
	float as2float(AnsiString as);
};

//----------------------------------------------------------------
class CL_ItemRepart {
public:
	CL_ItemRepart();
	CL_ItemRepart(int noItem, int nature);
	CL_ItemRepart(CL_ItemRepart *source);
	int No;
	int NoItem; //le n° de l'item
	int Famille; //PRODUIR CHARGE CHSTRUCT RECDIV...
	CL_Item *Item;
	char Flag;
	int Cmp(CL_ItemRepart *itemRepart) {
		return 0;
	}
	;
	int LesNoRepartQ[N_X];
	CL_Repart *LesRepartQ[N_X];
	int LesNoRepartV[N_X];
	CL_Repart *LesRepartV[N_X];
	void EcrireFichier(FILE *fichier);
	void LireFichier(FILE *fichier);

};

//----------------------------------------------------------------
// pour charge produit sous categorie  pour mettre quantite ou valeur
class CL_QuanVal {
public:
	CL_QuanVal();
	CL_QuanVal(int nature);
	CL_QuanVal(CL_QuanVal *source);
	int No; //le n° de l'item
	CL_Item *Item;
	CL_Categorie *Categorie; //100401
	float Qte[N_X];
	float Val[N_X];
	float Stock[N_X + 1];
	char Flag;
	int Cmp(CL_QuanVal *quanVal) {
		return 0;
	}
	;
	CL_ItemRepart *ItemRepart;
};
//----------------------------------------------------------------
class CL_ItemParAtelier {
public:
	CL_ItemParAtelier();
	~CL_ItemParAtelier(void);
	CL_Item *Item;
	CL_ItemParAtelier *ItemPA; //pour les charges proportionnelles au volume   no_produit!=-1
	CL_Item *Charge;
	int No;
	int NoItem;
	int NoCharge;
	int NoItemPA; //pour les charges proportionnelles au volume
	float Qte;
	float *QtePhase; //quantite par phase pour perennes
	int Cmp(CL_ItemParAtelier *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;
};
//-----------------------------------------------------------------
class CL_Espece {
private:
public:
	CL_Espece();
	CL_Espece(CL_Espece *source);
	int No;
	AnsiString Nom;
	bool Supprimable;
	int Phase[N_PHASE];
	int DebAmor;
	int DurAmor;
	int NbPhase;
	char Flag;
	int Cmp(CL_Espece *ptr) {
		return 0;
	}
	;
	//non utilisé
};
// entier entier flottant
//----------------------------------------------------------------
class CL_EEF {
public:
	CL_EEF();
	CL_EEF(CL_EEF *eef);
	CL_EEF(int col, int r0, int r1, float val);
	void Coordonnee(int &col, int &r0, int &r1);

	int No; // à mettre dans CL_Base
	AnsiString Nom;
	int Cmp(CL_EEF *ptr) {
		return 0;
	}
	; //non utilisé

	int Deb, Fin;
	float Val;
};
//----------------------------------------------------------------
class CL_Atelier {
public:
	CL_Atelier();
	CL_Atelier(const CL_Atelier *atelier);
	~CL_Atelier(void);
	void Deletevecteur(CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void RecopieQuantite(CL_Vecteur<CL_ItemParAtelier> *vecteur,
			CL_Vecteur<CL_ItemParAtelier> *vecteurOr);
	int No;
	AnsiString Nom;
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
	CL_Vecteur<CL_ItemParAtelier> *V_Charge;
	CL_Vecteur<CL_ItemParAtelier> *V_ChargeVolume;
	CL_Vecteur<CL_ItemParAtelier> *V_Produit;
	CL_Vecteur<CL_ItemParAtelier> *V_Externalite;
	CL_Vecteur<CL_EEF> *V_Avance; //301101
	CL_Vecteur<CL_BesTrav> *V_BesTrav; //270802

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
	char Flag;
	bool Supprimable;
	void SupMaFalse(void);
};
//-----------------------------------------------------------------
class CL_Verger {
public:
	int No;
	CL_Verger() {
		Supprimable = true;
	}
	;
	CL_Verger(const CL_Verger *verger);
	//CL_Verger(CL_Verger *ptrVerger);
	//void  Add(CL_Verger *ptrVerger,int *effectif);
	bool Supprimable;
	float Surface;
	float SurfaceAn[N_X];
	int AnPlant;
	int AnArr;
	int NoAtelier;
	int NoEspece;
	int Phase[N_X]; // ds quelle phase est le verger l'année n de la simulation
	CL_Atelier *Atelier;
	CL_Espece *Espece;
	int Cmp(CL_Verger *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;
};

//-----------------------------------------------------------
class CL_Valeur {
// Atelier Ou Item
private:
public:
	CL_Valeur() {
	}
	;
	CL_Valeur(const CL_Valeur *valeur);
	char Type;
	bool Supprimable; //pour les variables  ???
	int No;
	int NoAtelier;
	int NoItem;
	CL_Atelier *Atelier;
	CL_Item *Item;
	float Valeur[N_X];
	int Cmp(CL_Valeur *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;
};

//-----------------------------------------------------------
class CL_InvAni {
private:
public:
	CL_InvAni();
	CL_InvAni(const CL_InvAni *invAni);
	int Cmp(CL_InvAni *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;
	int No;
	int NoAnimal;
	CL_Item *Animal;
	char Reproducteur; //O/N       //260903
//        float ValInv;           //260903 A supprimer
	float Effectif[N_X + 1]; //091002
	float Valeur[N_X + 1]; //valeur d'inventaire

	float Vente[N_X]; //091002    effectifs
	float Achat[N_X]; //091002
	float ValVente[N_X]; //valeurs totales
	float ValAchat[N_X];
	// pour calcul des ventes automatiques
	float EffMax[N_X];
//        float ValVenteDefaut;            // A supprimer

	float PrixVenteMoy[N_X]; //300903  Non Stocké
	float ValInvMoy[N_X + 1]; //300903  Non Stocké

	float AAcheter[N_X]; //14 10 04 non stocké
	float PrixAchat[N_X]; //14 10 04 non stocké
						  //bricolé pour compatibilité de fichier
						  // je les trouve dans danslstMvtAni
	CL_Atelier *Atelier[N_X];
	int NoAtelier[N_X];
};
//-----------------------------------------------------------
class CL_Troupeau {
private:
public:
	CL_Troupeau();
	CL_Troupeau(CL_Categorie *catBestiaux);
	CL_Troupeau(CL_Troupeau *troupeau);
	~CL_Troupeau();
	char Flag;
	CL_Categorie *CatBestiaux;
	int NoCatBestiaux;
	CL_Vecteur<CL_InvAni> *V_InvAni;
	void VideLstMvtAni(void);
	TList *LstMvtAni;
};
//-----------------------------------------------------------
class CL_EmpLT {
private:
public:
	CL_EmpLT();
	~CL_EmpLT();
	int No;
	char Flag;
	int Cmp(CL_EmpLT *ptr) {
		return 0;
	}
	; //non utilisé
	AnsiString Nom;
	float Montant;
	int Duree, Duree2;
	float Taux, Taux2;
	AnsiString Type; //ca s t m va...
	int AReal, MReal, ARemb, MRemb;
	int ExReal;
//        float      Dette[N_X+1];
//        float      CapRemb[N_X];
//        float      Interet[N_X];
	float TotInt;
	char Pour; //E ou Prive
	void Calcul(int an_0, float *capital, float *remb, float *interet,
			float *dette);
	//private
	void RembConstant(float *capital, float *remb, float *interet,
			float *dette);
	void RembVariable(float *capital, float *remb, float *interet,
			float *dette);
	float VerstConst(float valeur, float taux, int duree);
	void TauxDuree(float &taux1, float &taux2, int &duree1, int &duree2,
			int &duree, int &deltaT);
	void Aff(int an_0);
	void RembConstantTreso(float *recu, float *verse);
	void RembVariableTreso(float *recu, float *verse);
};
//-----------------------------------------------------------
class CL_EmpCT {
private:
public:
	CL_EmpCT();
	int No;
	char Flag;
	int Cmp(CL_EmpCT *ptr) {
		return 0;
	}
	; //non utilisé
	AnsiString Nom;
	float Montant;
	float Taux;
	AnsiString Type; //interet Normal Precompte N/P
	int AReal, MReal, ARemb, MRemb;
	char Pour; //E ou Prive

	void Calcul(int an_0, float *capital, float *remb, float *interet,
			float *dette);
	void CalculTreso(float *recu, float *verse);
	void Aff(int an_0);
};
//-----------------------------------------------------------
class CL_Sub {
private:
public:
	CL_Sub();
	CL_Sub(CL_Sub *source);
	int No;
	char Flag;
	int Cmp(CL_Sub *ptr) {
		return 0;
	}
	; //non utilisé
	AnsiString Nom;
	float Montant;
	int AReal, MReal;
	int ExReal;
	int Duree;
	void Calcul(int an_0, float *amor, float *vResid);
	void CalculTreso(float *recu, float *verse);
	void Aff(int an_0);
};
//-----------------------------------------------------------
class CL_Plact {
private:
public:
	CL_Plact();
	int No;
	char Flag;
	int Cmp(CL_Plact *ptr) {
		return 0;
	}
	; //non utilisé
	AnsiString Nom;
	float Montant;
	float Taux;
	char Type; //interet versé Annuellement ou à la Fin
	int AReal, MReal, ATerme, MTerme;
	char Pour; //E ou Privé
	void Calcul(int an_0, int mois_0, float *capital, float *verst,
			float *interet, float *creance);
	void CalculTreso(float *recu, float *verse);
	void Aff(int an_0, int mois_0);
};
//-----------------------------------------------------------
class CL_Occc {
private:
public:
	CL_Occc();
	int No;
	char Flag;
	int Cmp(CL_Occc *ptr) {
		return 0;
	}
	; //non utilisé
	int Ex; //Exercice
	float Montant;
	float Taux;
	float Pcent;
	float Frais;
};
// vecteur de float dimension:N_X plus 1
//-----------------------------------------------------------
class CL_FN_Xp1 {
private:
public:
	CL_FN_Xp1();
	int No;
	char Flag;
	int Cmp(CL_FN_Xp1 *ptr) {
		return 0;
	}
	; //non utilisé
	float Valeur[N_X + 1];
};
//-----------------------------------------------------------
class CL_Immo {
private:
public:
	CL_Immo();
	int No;
	char Flag;
	int Cmp(CL_Immo *ptr) {
		return 0;
	}
	; //non utilisé
	AnsiString Nom;
	float ValAchat;
	int AAchat, MAchat, AVente, MVente;
	char TypeAmor;
	int Duree;
//        bool       Present;  //O/N
//?        float      Amor[N_X],VResid[N_X+1];
//        int        Groupe; //pour ensemble remplacé
	float ValVente; //valeur Vente
	float ValComptable; //valeur Vente
	int NoTva;
	CL_Tva *Tva;
	void Calcul(int an_0, float *amor, float *vResid, int &exAchat,
			int &exVente);
	void CalculTreso(int &mVente, float &valVente, float &tvaRecu, int &mAchat,
			float &valAchat, float &tvaVerse);
//        void       CalculTreso(float *recu,float *verse);
	void Aff(int an_0);
};
//-----------------------------------------------------------
//A
class CL_Petit //petit matériel amorti dans l'année
{
private:
public:
	CL_Petit();
	int No;
	char Flag;
	int Cmp(CL_Petit *ptr) {
		return 0;
	}
	; //non utilisé
	float ValAchat;
	int NoTva;
	CL_Tva *Tva;
	int NoRepart; //210604
	CL_Repart *Repart;
};
//-----------------------------------------------------------
class CL_TotEmp {
public:
	CL_TotEmp();
	CL_TotEmp(CL_TotEmp *totEmp);
	float Capital[N_X];
	float Remb[N_X];
	float Interet[N_X];
	float Dette[N_X + 1];
	float Annuite[N_X];
	bool EstVide;
	void Ajoute(float *capital, float *remb, float *interet, float *dette);
	void Maz(void);
};
//-----------------------------------------------------------
class CL_TotImmo {
public:
	CL_TotImmo();
	CL_TotImmo(CL_TotImmo *totImmo);
	float Achat[N_X];
	float Vente[N_X];
	float Amor[N_X];
	float Resid[N_X + 1];
	float ValBrut[N_X];
	float TvaVersee[N_X];
	float TvaRecue[N_X];
	float ValCompta[N_X]; //070202
//    float PlusVal   [N_X];
//    float MoinsVal  [N_X];
	float ProdImmo[N_X];
	bool EstVide;
	void Maz(void);
};
//-----------------------------------------------------------
class CL_TotSub {
public:
	CL_TotSub();
	CL_TotSub(CL_TotSub *source);
	float Valeur[N_X];
	float Amor[N_X];
	float Resid[N_X + 1];
	void Maz(void);
};
//-----------------------------------------------------------
class CL_TotEnCours {
public:
	CL_TotEnCours();
	CL_TotEnCours(CL_TotEnCours *totEnCours);
	float Flux[N_X];
	float Stock[N_X + 1];
	float CrDette[N_X + 1];
	float Tva[N_X];
	bool EstVide;
	void Maz(void);
};
//-----------------------------------------------------------
class CL_EnCours //creance dette
{
private:
public:
	CL_EnCours();
	CL_EnCours(CL_EnCours *source);
	int No;
	char Flag;
	int Cmp(CL_EnCours *ptr) {
		return 0;
	}
	; //non utilisé
	int NoFamille;
	int NoItem;
	CL_Item *Item;
	char EnStock; //O/N
	float Valeur;
	int APaie, MPaie;
};
//-----------------------------------------------------------
class CL_StockIni //stock et commercialisation
{
private:
public:
	CL_StockIni();
	CL_StockIni(CL_StockIni *source);
	int No;
	char Flag;
	int Cmp(CL_StockIni *ptr) {
		return 0;
	}
	; //non utilisé
	AnsiString Nom;
	int NoItem;
	CL_Item *Item;
	float Quantite[N_X];
	float PrixRevient[N_X];
};
//----------------------------------------------------------------------------
struct ST_Branche {
	int code;
	int arg[3];
	float valeur;
	int type;
	int date;
};
//----------------------------------------------------------------------------
struct ST_Maille {
	int code;
	int branche;
	int apG, apD;
};
//-----------------------------------------------------------
class CL_Arbre {
public:
	CL_Arbre(int BrancheMax = 50, int Delta = 50);
	CL_Arbre(CL_Arbre *Ancien);
	~CL_Arbre();
	ST_Branche *LesBranches;
	int BrancheX;
	int BrancheMax;
	int Delta;
	bool EstIdentique(CL_Arbre *autre);
	bool EstNumerique(void);
	bool ContientIndic(void);
	void MetIndicNonSupprimable(void);

};
//-----------------------------------------------------------
class CL_Reseau {
public:
	CL_Reseau(int MailleMax = 50, int Delta = 50);
	CL_Reseau(CL_Reseau *Reseau);
	~CL_Reseau();
	ST_Maille *LesMailles;
	int MailleX;
	int MailleMax;
	int Delta;
	bool EstIdentique(CL_Reseau *autre);
};
//-----------------------------------------------------------
class CL_Prog {
public:
	CL_Prog();
	CL_Prog(CL_Prog *prog);
	~CL_Prog(); //311201
	AnsiString Source;
	CL_Arbre *Arbre;
	CL_Reseau *Reseau;
	bool EstIdentique(CL_Prog *autre);
	bool EstNumerique(void);
};
//-----------------------------------------------------------
class CL_Formule {
// Atelier Ou Item
private:
public:
	CL_Formule();
	CL_Formule(CL_Formule *source);
	~CL_Formule();
	int No; //c'est le no de l'item on ne peut pas en avoir 2
//        AnsiString  Nom;
	int NoFamille; //PRODUIT CHARGE .. cf Olympedec.h
//        int         NoItem;
	CL_Item *Item;
	float Valeur[N_X];
//        float       Recette[N_X];
//        float       Stock[N_X];
	CL_Prog *LesProg[N_X];
	int Cmp(CL_Formule *ptr) {
		return 0;
	}
	; //non utilisé
	bool Supprimable;
	char Origine; // C pour etabli par calcul
	bool Existe;
	bool EstCalcule;
	char Flag;
};

//------------------ ------------------------------------------------------------
class CL_Periode {
public:
	CL_Periode();
	CL_Periode(CL_Periode *ptr);
	char Flag;
	bool Supprimable;
	int Cmp(CL_Periode *ptr) {
		return 0;
	}
	; //non utilisé
	int No;
	AnsiString Nom;
	int JDeb, MDeb, ADeb;
	int JFin, MFin, AFin;
	int Duree;
	int JD, JF; //par rapport au début premiere période
	int PcentDispo;
	float HpJ; //heurs par jour
	float JDispo;
	float HDispo;
	float Valeur[N_X];
	bool CalculDuree(void);
	void CalculDispo(void); //->JDispo HDispo
};
//------------------ ------------------------------------------------------------
class CL_Calendrier {
public:
	CL_Calendrier();
	CL_Calendrier(CL_Calendrier*ptr);
	int No;
	AnsiString Nom;
	AnsiString Notes;
	char Flag;
	bool Supprimable;
	int Cmp(CL_Calendrier *ptr) {
		return 0;
	}
	; //non utilisé
	CL_Vecteur<CL_Periode> *V_Periode;

};

struct ST_NoAgri;
class CL_Tendance;
//------------------ ------------------------------------------------------------
class CL_AgriDefSim {
public:
	CL_AgriDefSim();
	CL_AgriDefSim(CL_AgriDefSim* autre);
	// pour pouvoir se mettre dans un Vecteur
	int No;
	int Cmp(CL_AgriDefSim *ptr) {
		return 0;
	}
	; //non utilisé
	void SupMaFalse(void);
	bool Supprimable;
	int An_0; //début simulation
	int NbAnSim; //nb année simulation
	int MDeb; //mois
	int AnCalage;
	int TypeAlea; //SANS TENDANCE ENCHDEF ENCHALEA MCARLO

	char Enchainement[N_X + 1];
	// Tendance ou Scenario 0 aucun 1 tendance 2 scénario
	int TouSPrixProd;
	int TouSPrixCharge;
	int TouSQProd;
	int TouSQCharge;
	int TouSQExt;

	int NoPrixProd;
	int NoPrixCharge;
	int NoQProd;
	int NoQCharge;
	int NoQExt;
	// tel que definies avec 100
	CL_Tendance *PrixProd;
	CL_Tendance *PrixCharge;
	CL_Tendance *QProd;
	CL_Tendance *QCharge;
	CL_Tendance *QExt;
	// tel que utilisées avec prise en compte scénario
	// avec division par 100
	CL_Tendance *TPProd;
	CL_Tendance *TPCharge;
	CL_Tendance *TQProd;
	CL_Tendance *TQCharge;
	CL_Tendance *TQExt;
};
//--------------------------------------------------------------------
class CL_QuantPrix {
public:
	CL_QuantPrix();
	CL_QuantPrix(CL_Item *item, int anProd, int anComm, float quant,
			float prix);
	CL_QuantPrix(CL_QuantPrix *source);

	int NoItem;
	CL_Item *Item;
	int AnProd;
	int AnComm;
	float Quant;
	float Prix;
	void EcrireFichier(FILE *fichier);
	void LireFichier(FILE *fichier);
};
//--------------------------------------------------------------------
class CL_PolStock {
public:
	CL_PolStock();
	CL_PolStock(CL_Item *item);
	CL_PolStock(CL_PolStock *source);

	void MaZ(void);
	int No; //c'est le n° de l'item
	CL_Item *Item;
	float PcentStock;
	float Maxi;
	float PcentDeltaPrix;
	float PcentDecote;

	void AffRow(TStringGrid *grille, int r);
	void LitRow(TStringGrid *grille, int r);
	bool EstCorrect(TStringGrid *grille, int r);
	void EcrireFichier(FILE *fichier);
	void LireFichier(FILE *fichier);

};

// resultats calculés NON stockés
//--------------------------------------------------------------------
class CL_AgriRes {
private:
public:
	CL_AgriRes();
	CL_AgriRes(CL_AgriRes *source);
	~CL_AgriRes(void);
	void Maz(void);
	void SupMaFalse(void);
	int No;
	AnsiString Nom;
	int NoZone;
	int NoType;
	CL_Item *Zone;
	CL_Item *Type;
	int Cmp(CL_AgriRes *ptr) {
		return 0;
	}
	; //non utilisé

	bool Supprimable;

	//Resultats
	CL_Vecteur<CL_QuanVal> *V_Produit;
	CL_Vecteur<CL_QuanVal> *V_Charge;

	CL_Vecteur<CL_QuanVal> *V_Externalite;
	CL_Vecteur<CL_QuanVal> *V_ExtNeg;
	CL_Vecteur<CL_QuanVal> *V_ExtPos;

	CL_Vecteur<CL_QuanVal> *V_ChStruct;
	CL_Vecteur<CL_QuanVal> *V_RecDiv;
	CL_Vecteur<CL_QuanVal> *V_DepDiv;
	CL_Vecteur<CL_QuanVal> *V_RecFam;
	CL_Vecteur<CL_QuanVal> *V_DepFam;

	// total valeur par categorie
	CL_Vecteur<CL_QuanVal> *V_CatProduitTot;
	CL_Vecteur<CL_QuanVal> *V_CatChargeTot;

	CL_Vecteur<CL_QuanVal> *V_CatExtNegTot;
	CL_Vecteur<CL_QuanVal> *V_CatExtPosTot;

	CL_Vecteur<CL_QuanVal> *V_CatChStructTot;

	CL_Vecteur<CL_QuanVal> *V_CatRecDivTot;
	CL_Vecteur<CL_QuanVal> *V_CatDepDivTot;

	CL_Vecteur<CL_QuanVal> *V_CatRecFamTot;
	CL_Vecteur<CL_QuanVal> *V_CatDepFamTot;

	//totaux          Rec Recette  Dep Depense
	float Produit[N_X];
	float Charge[N_X];

	float VenteAni[N_X]; //181201
	float AchatAni[N_X]; //181201
	float InvAniRepro[N_X + 1]; //260903
	float InvAniAutre[N_X + 1]; //260903

	float RecDiv[N_X];
	float DepDiv[N_X];

	float ChStruct[N_X];

	float RecFam[N_X];
	float DepFam[N_X];

	float Stock[N_X + 1]; //031201
	float StockIni[N_X + 1]; //031201
	float Avance[N_X + 1]; //031201
	float ProdImmo[N_X]; //031201
	float ProdImmoFam[N_X]; //051201
	float AmorPlant[N_X]; //051201
	float ValPlant[N_X + 1]; //051201
	float PertePlant[N_X];

	CL_TotEmp *EmpLTE; //entreprise
	CL_TotEmp *EmpCTE;
	CL_TotEmp *EmpLTP; //privé
	CL_TotEmp *EmpCTP;

	CL_TotEmp *EmpSomLT;
	CL_TotEmp *EmpSomCT;

	CL_TotEmp *EmpTotal;

	CL_TotEmp *PlactE; //entreprise
	CL_TotEmp *PlactP;

	CL_TotImmo *Immo;
	CL_TotImmo *ImmoPetit;
	CL_TotImmo *ImmoSom;
	CL_TotImmo *ImmoTotal;

	CL_TotSub *TotSub;
	CL_TotEnCours *Creance;
	CL_TotEnCours *Dette;

	float FraisOccc[N_X];
	float Marge[N_X];
	float AutreDepense[N_X];
	float AutreRecette[N_X];
	float Solde[N_X];
	float SoldeCumul[N_X];

	CL_TvaEnt *Tva;

	//systeme de production
	CL_Vecteur<CL_Valeur> *V_SurCulture;
	CL_Vecteur<CL_Valeur> *V_SurVerger;
	CL_Vecteur<CL_Valeur> *V_EffAnimaux;

	float SurCulture[N_X];
	float SurVerger[N_X];
	float EffAnimaux[N_X];

	float TresoIni;

	//pour Comptabilite
	//privé
	float soldePrive[N_X]; //aussi dans Prive
	//ceg
	float deltaStock[N_X];
	float deltaAvance[N_X];
	float deltaValPlant[N_X];
	float deltaVarInvAniRepro[N_X]; //260903
	float deltaVarInvAniAutre[N_X]; //260903
	float totProduit[N_X];
	float totDepense[N_X];
	float totChStruct[N_X];
	float totCharge[N_X];
	float resExercice[N_X];
	//bilan
	float totImmo[N_X + 1];
	float tresorerie[N_X + 1];
	float perte[N_X];
	float benefice[N_X];
	float totActif[N_X + 1];
	float totPassif[N_X + 1];
	float capital[N_X + 1];
	float creanceTva[N_X + 1];
	float detteTva[N_X + 1];
	//
	float Ebe[N_X], Caf[N_X], Msa[N_X];

	char Flag;

	void creeVCat_Tot(CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vecteur);
	void MaZCat_Tot(CL_Vecteur<CL_QuanVal> *vecteur);
};
//--------------------------------------------------------------------
class CL_Agriculteur {
private:
public:
	CL_Agriculteur();
	CL_Agriculteur(const CL_Agriculteur *agri);
	~CL_Agriculteur(void);
	CL_AgriDefSim *DefSim;
	CL_AgriRes *Resultat;
	void Maz(void);
	void SupMaFalse(void);
	void FormuleSupMaFalse(CL_Vecteur<CL_Formule>*vecteur);
	void RecopierFormule(CL_Vecteur<CL_Formule> *vecteur,
			const CL_Vecteur<CL_Formule> *source);
	int No;
	AnsiString Nom;
	//à mettre dans AgriDefSim

	AnsiString Notes;
	TList *LstCritere;
	int NoVariante;
	int NbVariante;
	bool EstVariante;
	void IniGlobal(void);
	CL_Agriculteur *Pere; //020202

	int TypeAgreg; //SANS TOTAL MOYENNE  //130302  021002
				   // 260902
	AnsiString NomV(void); //fournit  Nom et n°variante
	AnsiString NomVC(void); //id° + criteres

	//...
	bool Supprimable;
	//Données
	CL_Vecteur<CL_Valeur> *V_Culture;
	CL_Vecteur<CL_Valeur> *V_Animaux;
	CL_Vecteur<CL_Verger> *V_Verger;
	CL_Vecteur<CL_Verger> *V_Vivrier;

	CL_Vecteur<CL_Formule> *V_Produits;
	CL_Vecteur<CL_Formule> *V_Charges;
	CL_Vecteur<CL_Formule> *V_ChStruct;

	CL_Vecteur<CL_Formule> *V_RecDiv;
	CL_Vecteur<CL_Formule> *V_DepDiv;
	CL_Vecteur<CL_Formule> *V_RecFam;
	CL_Vecteur<CL_Formule> *V_DepFam;

	CL_Vecteur<CL_Formule> *V_ExtPos;
	CL_Vecteur<CL_Formule> *V_ExtNeg;

	CL_Vecteur<CL_Valeur> *V_Variable;

	CL_Vecteur<CL_Immo> *V_Immo;
	CL_Vecteur<CL_Petit> *V_Petit; //A
	CL_Vecteur<CL_FN_Xp1> *V_InvSom;

	CL_Vecteur<CL_EmpLT> *V_EmpLT;
	CL_Vecteur<CL_EmpCT> *V_EmpCT;
	CL_Vecteur<CL_Sub> *V_Sub;
	CL_Vecteur<CL_Occc> *V_Occc;
	CL_Vecteur<CL_Plact> *V_Plact;
	CL_Vecteur<CL_FN_Xp1> *V_FinSom;

	CL_Vecteur<CL_EnCours> *V_Creance;
	CL_Vecteur<CL_EnCours> *V_Dette;
	CL_Vecteur<CL_StockIni> *V_StockIni; //111201

	CL_Vecteur<CL_FN_Xp1> *V_PrixRevient; //150302
	CL_Vecteur<CL_PolStock> *V_PolStock; //300302 Politique Stockage

	CL_Vecteur<CL_ItemRepart> *V_ItemRepart; //180903 tresorerie repartition
	TList *LstTroupeaux; //061003
	CL_Troupeau *TroupeauEnCours;

	TList* LstQuantPrix; //130302
	TList* LstVariante;
	TList* LstPasse; //191103
	CL_TvaEntIni *TvaEntIni;
	CL_PossibOcPlact *PossibOcPlact; //150604
	CL_QuanVal *QuanValPetit; //210604
	float TresoIni; //13 08 01
	int Cmp(CL_Agriculteur *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;

	int TypeAlea;

};
// utilise par CL_Agriculteur pour stocker les variantes dans une TList
// a revoir
// impossible de supprimer
//----------------------------------------------------------------
struct ST_NoAgri {
	int No;
	CL_Agriculteur* Agri;
};
//---------------------------------------------------------------------------

class CL_AgriEff {
public:
	CL_AgriEff() {
	}
	;
	CL_AgriEff(CL_Agriculteur *agri);
	CL_AgriEff(CL_AgriEff *agriEff);
	~CL_AgriEff() {
	}
	;
	int No;
	AnsiString Nom;
	char Flag;
	int Cmp(CL_AgriEff *ptr) {
		return 0;
	}
	; //non utilisé

	CL_Agriculteur *Agri;
	int NoAgri;
	int Effectif[N_X];
	AnsiString Notes;

};
struct ST_NoEnsemble;
//---------------------------------------------------------------------------
class CL_Ensemble {
public:
	CL_Ensemble();
	CL_Ensemble(const CL_Ensemble *ens);

	~CL_Ensemble() {
		delete V_AgriEff;
	}
	;

	int No;
	AnsiString Nom;
	int NoVariante;
	bool EstVariante;
	char Flag;
	int Cmp(CL_Ensemble *ptr) {
		return 0;
	}
	; //non utilisé

	CL_Vecteur<CL_AgriEff> *V_AgriEff;
	CL_Agriculteur *Total;
	AnsiString Notes;
	TList *LstVariante;
	ST_NoEnsemble *Ancetre;

};
// utilise par CL_Ensemble pour stocker les variantes dans une TList
//----------------------------------------------------------------
struct ST_NoEnsemble {
	int No;
	CL_Ensemble* Ensemble;
};

//---------------------------------------------------------------------------
class CL_Poste {
public:

	CL_Poste(AnsiString nom, int noPoste) {
		Nom = nom;
		No = noPoste;
	}
	;
	int No;
	AnsiString Nom;
	int Cmp(CL_Poste *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;
	void imp() {
	}
	;
};
//----------------------------------------------------------------------------
class CL_Indicateur {
public:
	CL_Indicateur(void);
	CL_Indicateur(CL_Indicateur *indicateur);
	~CL_Indicateur(void);

	AnsiString Nom;
	int No;
	int NoCategorie;
	CL_Categorie *Categorie;
	int NoSysteme; //101003
	CL_SystemeUnite *SysUnite;
	int Cmp(CL_Indicateur *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;
	int type;
//    AnsiString Text;
	bool Supprimable;
//    bool Libre;    //false si utilisé par un autre indic
	float Valeur[N_X];
	CL_Prog *Prog; //nouveau 71200
//	CL_Arbre    *Arbre;      // a supprimer est dans Prog
//	CL_Reseau   *Reseau;     // a supprimer

	bool Compile;
	bool Calcule;
	long pos;
};
class CL_EtatSortie;

//---------------------------------------------------------------------------
class CL_Elt {
	friend bool operator<(const CL_Elt&, const CL_Elt&);
public:
	CL_Elt();
	CL_Elt(CL_Elt *elt);
	CL_Elt(CL_Poste *poste);
	CL_Elt(CL_Poste *poste, CL_Categorie *categorie, CL_Item *item);
	CL_Elt(CL_Poste *poste, int noType, CL_Categorie *categorie, CL_Item *item);
	CL_Elt(CL_Poste *poste, CL_Categorie *categorie, CL_Indicateur *indic);
	CL_Elt(CL_Poste *poste, CL_Categorie *categorie, CL_Atelier *atelier);
	CL_Elt(CL_Poste *poste, CL_Espece *espece, CL_Atelier *atelier);
	CL_Elt(CL_Poste *poste, char *nom, int no);

	CL_Elt(CL_Poste *poste, CL_Item *item);
	CL_Elt(CL_Poste *poste, CL_Categorie *categorie);

	CL_Elt(char *nomFamille);
	CL_Elt(int type); //pour mise en forme :trait blanc
	~CL_Elt(void);
	AnsiString Donne_Nom();
//    AnsiString Donne_Unite();
	char* Donne_Unite();
	AnsiString NomTypeMvtAni(int noType);
//....
	int No;
	int Cmp(CL_Elt *ptr) {
		return 0;
	}
	; //non utilisé
	char Flag;
	int NoFamille; //PRODUIT CHARGE RECDIV...INDIC  cf olympedec.h
	int NoCategorie; //seult pour produit charge
	int NoType; //seult pour animaux EFF EFFV EFFA VALV VALA VALINV
	int NoItem;
	int NoEspece;
	int NoEtat;
	CL_Poste *Poste;
	CL_Item *Item;
	CL_EtatSortie *Etat;
	CL_Categorie *Categorie;
	CL_Espece *Espece;
	char *Nom;
	char *NomCat;
	char *NomFamille;
	char *Unite;
	float *Valeur;
	float *Pcent;
	float VMin, VMax;
	float *Passe;
};
bool operator<(const CL_Elt& elt1, const CL_Elt& elt2) {
	return (elt1.No < elt2.No);
}
//----------------------------------------------------------------------------
class CL_EtatSortie {
public:
	CL_EtatSortie(void);
	CL_EtatSortie(CL_EtatSortie *etat);
	~CL_EtatSortie(void);
	AnsiString Nom;
	int No;
	int NoCategorie;
	CL_Categorie *Categorie;
	char Flag;
	int Cmp(CL_EtatSortie *ptr) {
		return 0;
	}
	; //non utilisé
	bool Supprimable;
	CL_Vecteur<CL_Elt> *V_Elt;

private:
};
//------------------------------------------------------------------------------
class CL_Delta {
public:
	CL_Delta();
	int No;
	char Flag;
	int Cmp(CL_Delta *ptr) {
		return 0;
	}
	; //non utilisé

	int NoItem;
	CL_Item *Item;

	int NoAtelier;
	CL_Atelier *Atelier;
	int Nature; //ANIMAUX CULTURE PERENNE VIVRIER

	float Rdt;

	float Pcent[N_X];

};
//------------------------------------------------------------------------------
class CL_Tendance {
public:
	CL_Tendance();
	CL_Tendance(CL_Tendance *tend);
	~CL_Tendance();
	int No;
	char Flag;
	bool Supprimable;
	int Cmp(CL_Tendance *ptr) {
		return 0;
	}
	; //non utilisé

	AnsiString Nom;
	CL_Vecteur<CL_Delta> *V_Delta;
};
//------------------------------------------------------------------------------
class CL_MvtAni {
public:
	CL_MvtAni(int noAnimal, int date, int type, int eff, float info);
	CL_MvtAni(CL_MvtAni* mvtAni);
	int Ligne;
	int Type;
	int Date;
	int Eff;
	float Info;
};
//------------------------------------------------------------------------------
class CL_Conversion {
public:
	CL_Conversion();
	CL_Conversion(CL_SystemeUnite *Base, CL_SystemeUnite *Sortie);

	AnsiString Nom;
	int No;
	bool Supprimable;
	int Cmp(CL_Conversion *ptr) {
		return true;
	}
	;
	char Flag;

	int NoBase;
	int NoSortie;
	int APartirDe; // 0 franc    1 euro
	CL_SystemeUnite *Base;
	CL_SystemeUnite *Sortie;
	float TauxConvFrancVersEuro[N_X + 1];
	float TauxConvEuroVersFranc[N_X + 1];
};
#endif

