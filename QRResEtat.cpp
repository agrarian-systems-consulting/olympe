#include <vcl.h>
#pragma hdrstop

//#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "TVChoixEtat.h"

//#include "QRSortieEnum.h"
#include "QRSortieQuant.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::Etat(CL_EtatSortie *etat,CL_Agriculteur *agri)
{
	CL_Elt *elt;
	AnsiString unite; //021102

	Agri=agri;
	QRSortieValFrm->NomAgri->Caption=agri->NomV();
	// nb Colonne 10 CEG Treso  11 Bilan
	QR->Tag=10;
	if(LstDonnees) DelDonnees();//211204
	LstDonnees=new TList;
	TVChoixEtatFrm->Close();
	NomAgri->Caption=agri->NomV();//??
	TitreEtat->Caption=etat->Nom.c_str();

	for(int n=0;n<etat->V_Elt->Nbelt;n++)
	{
		elt=etat->V_Elt->Vecteur[n];

		if(elt->NoFamille==FORME)
		{
			if (elt->NoItem==TRAIT) entreTrait();
			else if(elt->NoItem==BLANC) entreBlanc();
			else if(elt->NoItem==TITRE) entreDonnees(QRTITRE,elt->Nom,NULL);
		}
		else
		{
			Forme0Frm->CompleteElt(elt,agri);
			entreDonnees(QRDON,elt,clNavy);
		}
	}

	Initialise();
	QR->Preview();
	DelDonnees();
}

