#include <vcl.h>
#pragma hdrstop

//#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
//#include "QRSortieEnum.h"
#include "QRSortieQuant.h"
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::Prepare(int TypeSortie,CL_Agriculteur *agri)
{
	QRSortieQuantFrm->Agri=agri;
	QRSortieQuantFrm->NomAgri->Caption=agri->Nom.c_str();
	// nb Colonne 10 CEG Treso  11 Bilan
	QRSortieQuantFrm->QR->Tag=10;
	LstDonnees=new TList;
	switch(TypeSortie)
	{
		case QUANTITE:
		QRSortieQuantFrm->TitreEtat->Caption=L_1; //"Quantites Physiques";
		IniDonneesQuantite(agri);
		break;
		case EXTER:
		QRSortieQuantFrm->TitreEtat->Caption=L_2;//"Externalités";
		IniDonneesExter(agri);
		break;
	}
	Initialise();
	QR->Preview();
	DelDonnees();
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::IniDonneesQuantite(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	resultat=agri->Resultat;

	IniDQuantCategorie(L_3.c_str(),V_CatProduit,resultat->V_Produit); //Produits
// Montpellier 100203
//    IniDTresoAnimaux(agri);
//    if(Agri->V_InvAni->Nbelt)
	IniDQuantAnimaux(agri);
	IniDQuantCategorie(L_4.c_str(),V_CatCharge ,resultat->V_Charge);//"Charges"

}
//240406
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::IniDQuantCategorie(
		char *nom,
		CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vQuanVal)
{
	int i,j;
	int n;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_QuanVal *quanVal;
	char *unite;
	float quantite[N_X];
	if(vQuanVal->Nbelt==0) return;

	entreTitre(nom);

//    Trait();

	for(i=0;i<vCategorie->Nbelt;i++)
	{
		categorie=vCategorie->Vecteur[i];
		if(categorie->Flag=='N') continue;

		entreDonnees(QRTITRE1,categorie->Nom.c_str(),NULL,clNavy);

		for(j=0;j<vQuanVal->Nbelt;j++)
		{
			quanVal=vQuanVal->Vecteur[j];
			item=quanVal->Item;
			if(item->Categorie!=categorie ) continue;

			if(Global==AGRI||Global==MOYENNE)
			{
				unite=item->SysUnite->UTrans.c_str();
				entreDonnees(QRDON,item->Nom.c_str(),unite,quanVal->Qte,clNavy);
			}
			else
			{
				unite=item->SysUnite->UGlobal.c_str(); //171006 calcul fait
				for(n=0;n<N_X;n++)quantite[n]=quanVal->Qte[n];///item->SysUnite->RatioG;
				entreDonnees(QRDON,item->Nom.c_str(),unite,quantite,clNavy);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::IniDQuantAnimaux(CL_Agriculteur *agri)

{
	int i,j;
	CL_InvAni *invAni;
	CL_Troupeau *troupeau;
	bool titreAffiche;

	if(agri->LstTroupeaux->Count==0) return;
	titreAffiche=false;
	for(i=0;i<agri->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[i];
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			if(EstVide(invAni->Vente)==false)
			{
				if(titreAffiche==false)
				{
					entreDonnees(QRTITRE1,L_5.c_str(),NULL,clNavy); //"Animaux Vendus"
					titreAffiche=true;
				}
				entreDonnees(QRDON,invAni->Animal->Nom.c_str(),L_6.c_str(),invAni->Vente,clNavy); //"tête"
			}
		}
	}
	titreAffiche=false;
	for(i=0;i<agri->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[i];
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			if(EstVide(invAni->Achat)==false)
			{
				if(titreAffiche==false)
				{
					entreDonnees(QRTITRE1,L_7.c_str(),NULL,clNavy); //"Animaux Achetés"
					titreAffiche=true;
				}
				entreDonnees(QRDON,invAni->Animal->Nom.c_str(),L_6.c_str(),invAni->Achat,clNavy); //"tête"
			}
		}
	}
}

//---------------------------------------------------------------------------
//240406
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::IniDonneesExter(CL_Agriculteur *agri)
{
	int i,n;
	CL_AgriRes *resultat;
	CL_QuanVal *quanVal;
	CL_Item *item;
	char *unite;
	float quantite[N_X];
	CL_Vecteur<CL_QuanVal> *vQuanVal;
	resultat=agri->Resultat;

	if(resultat->V_ExtNeg->Nbelt>0)
	{
		vQuanVal=resultat->V_ExtNeg;
		entreTitre(L_8.c_str()); //"Négatives");
		for(i=0;i<vQuanVal->Nbelt;i++)
		{
			quanVal=vQuanVal->Vecteur[i];
			item=quanVal->Item;
			if(Global==AGRI||Global==MOYENNE)
			{
				unite=item->SysUnite->UTrans.c_str();
				entreDonnees(QRDON,item->Nom.c_str(),unite,quanVal->Qte,clNavy);
			}
			else
			{
				unite=item->SysUnite->UGlobal.c_str();
				for(n=0;n<N_X;n++)quantite[n]=quanVal->Qte[n]/item->SysUnite->RatioG;
				entreDonnees(QRDON,item->Nom.c_str(),unite,quantite,clNavy);
			}

		}
	}

	if(resultat->V_ExtPos->Nbelt>0)
	{
		vQuanVal=resultat->V_ExtPos;
		entreTitre(L_9.c_str()); //"Positives");
		for(i=0;i<vQuanVal->Nbelt;i++)
		{
			quanVal=vQuanVal->Vecteur[i];
			item=quanVal->Item;
			if(Global==AGRI||Global==MOYENNE)
			{
				unite=item->SysUnite->UTrans.c_str();
				entreDonnees(QRDON,item->Nom.c_str(),unite,quanVal->Qte,clNavy);
			}
			else
			{
				unite=item->SysUnite->UGlobal.c_str();
				for(n=0;n<N_X;n++)quantite[n]=quanVal->Qte[n]/item->SysUnite->RatioG;
				entreDonnees(QRDON,item->Nom.c_str(),unite,quantite,clNavy);
			}

		}
	}
}

