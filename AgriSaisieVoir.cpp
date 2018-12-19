//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"

#include "LesVecteurs.hse"
#include "GereAgri.h"
#include "Erreur.h"

#include "Forme01.h"
#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VoirStockIni(void)
{
	int i;
	int nbElt;
	int an_0;
	CL_StockIni *stock;
	float valStock[N_X+1];
	float valVente[N_X];
	nbElt=Agri->V_StockIni->Nbelt;
	// pour chaque: nom stock valVente
	nbElt=nbElt*3;
	an_0=Agri->DefSim->An_0;

	Forme01Frm->Show();

	Forme01Frm->IniGrilleStandard(L_EvolStock,N_X+1,nbElt,an_0);
	//Forme01Frm->IniGrilleStandard("Evolution des Stocks",N_X+1,nbElt,an_0);

	for(i=0;i<Agri->V_StockIni->Nbelt;i++)
	{
		stock=Agri->V_StockIni->Vecteur[i];
//        stock->Calcul(valStock,valVente);
		Forme01Frm->EcrireTitre (stock->Item->Nom);
		Forme01Frm->EcrireLigne (L_Stocks,valStock);
//Forme01Frm->EcrireLigne    ("Stock",valStock);
		Forme01Frm->EcrireLigneCol2(L_Vente,valVente);
		//Forme01Frm->EcrireLigneCol2("Vente",valVente);
	}
}
//---------------------------------------------------------------------------
/*
 L_EvolStock=           "Evolution des Stocks";
 L_Vente=               "Vente";

 */
