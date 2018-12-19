//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vcl.h>
#pragma hdrstop
using namespace std;
#include "Matrice.h"

#include "InvAni.h"

#include "MvtAni.h"

#include "CL_MvtAnnee.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//-----------------------------------------------------------------------------
//CL_MvtAnnee()  à mettre dans LesClassesApp
//-----------------------------------------------------------------------------
CL_MvtAnnee::CL_MvtAnnee() {
	Debut = 0;
	Fin = 0;
	Ne = 0;
	Mort = 0;
	iVente = 0;
	iAchat = 0;
	iOr = 0;
	iDest = 0;
	iRegul = -1;
	iAchatAuto = -1;
	memset(Vente, 0, sizeof(int) * 3);
	memset(PrixVente, 0, sizeof(float) * 3);
	memset(Achat, 0, sizeof(int) * 3);
	memset(PrixAchat, 0, sizeof(float) * 3);
	memset(Entree, 0, sizeof(int) * 3);
	memset(Origine, 0, sizeof(int) * 3);
	memset(Sortie, 0, sizeof(int) * 3);
	memset(Destin, 0, sizeof(int) * 3);
	memset(EntreeTout, false, sizeof(bool) * 3);
	memset(SortieTout, false, sizeof(bool) * 3);
	ValVente = 0;
	ValAchat = 0;
	TotVente = 0;
	TotAchat = 0;
	ADescendance = false;
	for (int i = 0; i < 4; i++) {
		DonneNo[i] = 0;
		DonnePcent[i] = 0.;
	}
}
//-----------------------------------------------------------------------------
void CL_MvtAnnee::Maz(void) {
	Debut = 0;
	Fin = 0;
	Ne = 0;
	Mort = 0;
	iVente = 0;
	iAchat = 0;
	iOr = 0;
	iDest = 0;
	iRegul = -1;
	iAchatAuto = -1;
	memset(Vente, 0, sizeof(int) * 3);
	memset(PrixVente, 0, sizeof(float) * 3);
	memset(Achat, 0, sizeof(int) * 3);
	memset(PrixAchat, 0, sizeof(float) * 3);
	memset(Entree, 0, sizeof(int) * 3);
	memset(Origine, 0, sizeof(int) * 3);
	memset(Sortie, 0, sizeof(int) * 3);
	memset(Destin, 0, sizeof(int) * 3);
	memset(EntreeTout, false, sizeof(bool) * 3);
	memset(SortieTout, false, sizeof(bool) * 3);
	ValVente = 0;
	ValAchat = 0;
	TotVente = 0;
	TotAchat = 0;
	/*
	 ADescendance=false;
	 for(int i=0;i<4;i++)
	 {
	 DonneNo[i]   =0;
	 DonnePcent[i]=0.;
	 }
	 */
}
/*
 //-----------------------------------------------------------------------------
 void CL_MvtAnnee::Maz(void)
 {
 int i;
 //maz Mais conserve la filiation
 //Debut=0;
 Fin=0;
 Ne=0;Mort=0;
 //    iVente=0;
 //    iAchat=0;

 iDest=0;
 if(iRegul!=-1)  //consever Achat et Vente introduite à la main
 {
 Vente[iRegul]=0;
 PrixVente[iRegul]=0;
 }
 //    memset(Vente,      0,sizeof(int)*3);
 //    memset(PrixVente,  0,sizeof(float)*3);
 //    memset(Achat,      0,sizeof(int)*3);
 //    memset(PrixAchat,  0,sizeof(float)*3);

 memset(Entree,      0,sizeof(int)*3);

 iOr=0;
 for(i=0;i<3;i++)
 {
 Entree[i]=0;
 if(EntreeTout[i]==false) Origine[i]=0;
 else iOr++;
 }

 iDest=0;
 for(i=0;i<3;i++)
 {
 Sortie[i]=0;
 if(SortieTout[i]==false) Destin[i]=0;
 else
 {
 iDest++;
 if(iDest>3)
 ShowMessage("iDest>3");
 }
 }
 ValVente=0;
 ValAchat=0;
 TotVente=0;
 TotAchat=0;
 }
 */
//-----------------------------------------------------------------------------
void CL_MvtAnnee::CopieVers(CL_MvtAnnee* vers) {
	int i;
	vers->Ne = Ne;
	vers->Mort = Mort;

	vers->iVente = iVente;
	for (i = 0; i < iVente; i++) {
		vers->Vente[i] = Vente[i];
		vers->PrixVente[i] = PrixVente[i];
	}
	vers->iAchat = iAchat;
	for (i = 0; i < iAchat; i++) {
		vers->Achat[i] = Achat[i];
		vers->PrixAchat[i] = PrixAchat[i];
	}
	vers->iOr = iOr;
	for (i = 0; i < iOr; i++) {
		vers->Entree[i] = Entree[i];
		vers->Origine[i] = Origine[i];
	}

	vers->iDest = iDest;
	for (i = 0; i < iDest; i++) {
		vers->Sortie[i] = Sortie[i];
		vers->Destin[i] = Destin[i];
	}

}
//-----------------------------------------------------------------------------
/// calcule le nombre d'animaux compte tenu des mouvements
void CL_MvtAnnee::Solde(void) {
	int i;
	int entree, sortie;
	entree = 0;
	sortie = 0;
	ValVente = 0.;
	ValAchat = 0.;
	TotVente = 0.;
	TotAchat = 0.;

	for (i = 0; i < iVente; i++) {
		TotVente += Vente[i];
		ValVente += Vente[i] * PrixVente[i];
	}
	for (i = 0; i < iAchat; i++) {
		TotAchat += Achat[i];
		ValAchat += Achat[i] * PrixAchat[i];
	}

	for (i = 0; i < iOr; i++)
		entree += Entree[i];
	for (i = 0; i < iDest; i++)
		sortie += Sortie[i];

	Fin = Debut - TotVente + TotAchat + entree + Ne - sortie - Mort;
	/*
	 if(Ne>0)
	 Fin=Ne   -TotVente+TotAchat-Mort;
	 else
	 Fin=Debut-TotVente+TotAchat+entree-sortie-Mort;
	 */

}
//-----------------------------------------------------------------------------
// l'utilisateur a défini la filiation des animaux
// ex  Vl <- Vl1 <Gpav <-G1224 <-G 0 12
// mais il peut décider autrement
// ce qui reste suit le cours habituel
//int CL_MvtAnnee::Dispo(int noDest)
//  va dans categorie suivante
//	Debut-mort-toutes les ventes -sorties fixées par l'utilisateur
int CL_MvtAnnee::Dispo(int noDest) {
	int dispo;
	int i;
	int totVente = 0;
	int totAchat = 0;
	int totEntree = 0;

	for (i = 0; i < iVente; i++)
		totVente += Vente[i];
	for (i = 0; i < iAchat; i++)
		totAchat += Achat[i];

	dispo = Debut - Mort - totVente + totAchat + totEntree;
	for (i = 0; i < iDest; i++)
		dispo -= Sortie[i];
	return dispo;
}
/*
 for(i=0;i<3;i++)
 {
 if(SortieTout[i]==true)break;// continue;
 decide=true;
 sorDecision+=Sortie[i];
 if(Destin[i]==noDest)
 dispoPour+=Sortie[i];
 }
 if(decide==true) return dispoPour;


 if(Ne>0)
 dispo=Debut;//Ne-Mort;
 else
 dispo=Debut-Mort-totVente-sorDecision;
 for(i=0;i<3;i++)
 {
 if(SortieTout[i]==true)
 {
 Sortie[i]=dispo;
 //            MvtAniFrm->SGSortie->Cells[0][0]=dispo;
 break;
 }
 }
 return dispo;
 }
 */
//-----------------------------------------------------------------------------
/// si aucune information true
bool CL_MvtAnnee::EstVide(void) {
	if (Ne > 0)
		return false;
	if (Mort > 0)
		return false;
	if (iVente > 0)
		return false;
	if (iAchat > 0)
		return false;
	if (iOr > 0)
		return false;
	if (iDest > 0)
		return false;
	if (iVente > 0)
		return false;

	return true;
}
//-----------------------------------------------------------------------------
int CL_MvtAnnee::DonneiRegul(void) {
	int i;
	if (iRegul != -1)
		return iRegul;

	i = iVente++;
	if (iVente > 3)
		ShowMessage("iVente>3");
	if (i > 2) {
		iVente--;
		i = 0;
	} // impossible!!!???
	iRegul = i;
	return i;
}
//-----------------------------------------------------------------------------
int CL_MvtAnnee::DonneiAchatAuto(void) {
	int i;
	if (iAchatAuto != -1)
		return iAchatAuto;

	i = iAchat++;
	if (iAchat > 3)
		ShowMessage("iAchat>3");
	if (i > 2) {
		iAchat--;
		i = 0;
	} // impossible!!!???
	iAchatAuto = i;
	return i;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CL_MvtAnnee::Lister(ofstream &outfile) {
	int i;
	outfile << "Début " << Debut << "Fin" << Fin << endl;
	if (Ne > 0)
		outfile << "Né  " << Ne << endl;
	if (Mort < 0)
		outfile << "Mort" << Mort << endl;
	if (iVente > 0) {
		outfile << "iVente = " << iVente << endl;
		for (i = 0; i < iVente; i++) {
			outfile << i << " " << Vente[i] << "Vendues à " << PrixVente[i]
					<< endl;
		}
	}
	if (iAchat > 0) {
		outfile << "iAchat = " << iAchat << endl;
		for (i = 0; i < iAchat; i++) {
			outfile << i << " " << Achat[i] << " Achetées à " << PrixAchat[i]
					<< endl;
		}
	}
	if (iOr > 0) {
		outfile << "iOr = " << iOr << endl;
		for (i = 0; i < iOr; i++) {
			outfile << i << " " << Entree[i] << " Viennent de " << Origine[i]
					<< endl;
		}
	}
	if (iDest > 0) {
		outfile << "iDest" << iDest << endl;
		for (i = 0; i < iDest; i++) {
			outfile << i << " " << Sortie[i] << "Vont en " << Destin[i] << endl;
		}
	}
	outfile << endl;

}
//-----------------------------------------------------------------------------
void CL_MvtAnnee::Nettoyer(AnsiString aFaire) {
	int effectif[3];
	int noAnimal[3];
	int i;
	if (aFaire == "Dest") {
		for (i = 0; i < 3; i++) {
			effectif[i] = Entree[i];
			noAnimal[i] = Origine[i];
			Entree[i] = 0;
			Origine[i] = 0;
		}
		iOr = 0;
		for (i = 0; i < 3; i++) {
			if (effectif[i] <= 0)
				continue;
			if (noAnimal[i] <= 0)
				continue;
			Entree[iOr] = effectif[i];
			Origine[iOr] = noAnimal[i];
			iOr++;
		}
	}
	if (aFaire == "Origine") {
		for (i = 0; i < 3; i++) {
			effectif[i] = Sortie[i];
			noAnimal[i] = Destin[i];
			Sortie[i] = 0;
			Destin[i] = 0;
		}
		iDest = 0;
		for (i = 0; i < 3; i++) {
			if (effectif[i] <= 0)
				continue;
			if (noAnimal[i] <= 0)
				continue;
			Sortie[iDest] = effectif[i];
			Destin[iDest] = noAnimal[i];
			iDest++;
		}
	}
	if (aFaire == "Vente") {
		for (i = 0; i < 3; i++) {
			effectif[i] = Vente[i];
			Vente[i] = 0;
		}
		iVente = 0;
		for (i = 0; i < 3; i++) {
			if (effectif[i] <= 0)
				continue;
			Vente[iVente] = effectif[i];
			iVente++;
		}

	}
}

//Fin MvtAnnee
