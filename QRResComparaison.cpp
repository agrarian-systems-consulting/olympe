#include <vcl.h>
#pragma hdrstop

//#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "QRSortieQuant.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::Comparaison(CL_EtatSortie *serieComp,TList *lstElt,CL_Agriculteur *agri)
{
	CL_Elt *elt;
	char *unite;
//CL_Agriculteur *agr;
	Agri=agri;//ne pas effacer cfTQRSortieValFrm::Initialise(
	// !!!
	//QRSortieValFrm->NomAgri->Caption=agri->Nom.c_str();
	QRSortieValFrm->NomAgri->Caption=serieComp->Nom.c_str();
	QRSortieValFrm->UniteMonnaie->Caption="";

	// nb Colonne 10 CEG Treso  11 Bilan
	QR->Tag=10;
	LstDonnees=new TList;
	TitreEtat->Caption=serieComp->Nom.c_str();

	for(int n=0;n<lstElt->Count;n++)
	{
		elt=(CL_Elt*)lstElt->Items[n];

		if(elt->NoFamille==FORME)
		{
			if (elt->NoItem==TRAIT) entreTrait();
			else if(elt->NoItem==BLANC) entreBlanc();
			else if(elt->NoItem==TITRE) entreDonnees(QRTITRE,elt->Nom,NULL);
		}
		else
		{
			unite=elt->Donne_Unite();
//			entreDonnees(QRDON,elt->Nom,unite,elt->Valeur,clNavy);
			if(elt->Digits >2)
			elt->Digits=0;//160808
			entreDonnees(QRDON,elt->Nom,unite,elt->Valeur,elt->Digits,clNavy);//160808

		}
	}

	//....
	Initialise();
	NomAgri->Caption="Comparaison";
	QR->Preview();
	DelDonnees();//!!!!!!!!!
}

