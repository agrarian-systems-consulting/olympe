//---------------------------------------------------------------------------

#include "CL_Don.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CL_Don::CL_Don(void) {
}
//---------------------------------------------------------------------------
void CL_Don::CreeV(vector<CL_EltProc*> v, CL_Agriculteur *agri) {
	v.clear();
	//             Nature       Famille      categorie   nom
	CreeVAtelier(v, "Production", "Assolement", V_Culture, V_CatCulture, agri);
	CreeVAtelier(v, "Production", "Animaux", V_Animaux, V_CatAnimaux, agri);

	CreeVItem(v, "Produits", "Produits", V_Produit, V_CatProduit, agri);
	CreeVItem(v, "Charges", "Charges", V_Charge, V_CatCharge, agri);

	CreeVItem(v, "Variables", "Variables", V_Variable, V_CatVar, agri);

	CreeVItem(v, "Dépenses", "Charges Structure", V_ChStruct, V_CatChStruct,
			agri);
	CreeVItem(v, "Recettes", "Recettes Diverses", V_RecDiv, V_CatRecDiv, agri);
	CreeVItem(v, "Dépenses", "Dépenses Diverses", V_RecDiv, V_CatRecDiv, agri);

	CreeVItem(v, "Externalités", "Externalités", V_Externalite,
			V_CatExternalite, agri);

	CreeVItem(v, "Recettes", "Recettes Privées", V_RecFam, V_CatRecFam, agri);
	CreeVItem(v, "Dépenses", "Dépenses Privées", V_DepFam, V_CatDepFam, agri);

	//Tendance  Prix
	CreeVTendance(v, "Alea Prix", "Tendance Produits", V_TendPrixProd,
			V_CatProduit, agri);
	CreeVTendance(v, "Alea Prix", "Scénario Produits", V_ScenPrixProd,
			V_CatProduit, agri);

	CreeVTendance(v, "Alea Prix", "Tendance Charges", V_TendPrixCharge,
			V_CatCharge, agri);
	CreeVTendance(v, "Alea Prix", "Scénario Charges", V_ScenPrixCharge,
			V_CatCharge, agri);

	EcrireDonnees(v, "Don.txt");

	TriVector(v);

	//   EcrireDonnees(v,"Don1.txt");
	/*//...test
	 CL_EltProc  *eltP;
	 unsigned int n;
	 for(n=0;n<v.size();n++)
	 eltP=cherche(v,v[n]);
	 */
}
//---------------------------------------------------------------------------
void __fastcall CL_Don::CreeVAtelier(vector<CL_EltProc*> &v,
		AnsiString nomNature,AnsiString nomFamille,
		CL_Vecteur<CL_Atelier> *vecteur,CL_Vecteur<CL_Categorie> *vCat,
		CL_Agriculteur *agri)
{
	int i,j;
	CL_Categorie *cat;
	CL_Atelier *atelier;
	CL_EltProc *eltP;
	if(vecteur->Nbelt==0)return;

	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		for(j=0;j<vecteur->Nbelt;j++)
		{
			atelier=vecteur->Vecteur[j];
			if(atelier->Categorie!=cat) continue;
			eltP=new CL_EltProc(nomNature,nomFamille,
					atelier->Categorie->Nom,
					atelier->Nom);

			v.push_back(eltP);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_Don::CreeVItem(vector<CL_EltProc*> &v,
		AnsiString nomNature,AnsiString nomFamille,
		CL_Vecteur<CL_Item> *vecteur,CL_Vecteur<CL_Categorie> *vCat,
		CL_Agriculteur *agri)
{
	int i,j;
	CL_Categorie *cat;
	CL_Item *item;
	CL_EltProc *eltP;
	if(vecteur->Nbelt==0) return;

	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		for(j=0;j<vecteur->Nbelt;j++)
		{
			item=vecteur->Vecteur[j];
			if(item->Categorie!=cat) continue;

			eltP=new CL_EltProc(nomNature,nomFamille,
					item->Categorie->Nom,
					item->Nom);

			v.push_back(eltP);
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall CL_Don:: CreeVTendance(vector<CL_EltProc*> &v,
		AnsiString nomNature,AnsiString nomFamille,
		CL_Vecteur<CL_Tendance> *vecteur,
		CL_Vecteur<CL_Categorie> *vCat,
		CL_Agriculteur *agri)
{
	int i,j,k;
	CL_Categorie *cat;
//CL_Item      *item;
	CL_Tendance *tend;
	CL_Delta *delta;
	CL_EltProc *eltP;
	if(vecteur->Nbelt==0) return;

	for(i=0;i<vecteur->Nbelt;i++)
	{
		tend=vecteur->Vecteur[i];
		for(j=0;j<vCat->Nbelt;j++)
		{
			cat=vCat->Vecteur[j];
			for(k=0;k<tend->V_Delta->Nbelt;k++)
			{
				delta=tend->V_Delta->Vecteur[k];

				if(delta->Item->Categorie!=cat) continue;

				eltP=new CL_EltProc(nomNature,nomFamille,
						delta->Item->Categorie->Nom,
						delta->Item->Nom);

				v.push_back(eltP);
			}
		}
	}
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall CL_Don::EcrireDonnees(vector<CL_EltProc*> v,AnsiString AsFichier)
{
	unsigned int i;
//int n;
	CL_EltProc *eltP;
	AnsiString nomV;//nom de l'agri + n°Variante
	ofstream outfile(AsFichier.c_str());
	if(v.size()<1)
	{
		ShowMessage("Aucune Donnée !  ");
		return;
	}
	outfile << "Nature" << "\t" << "Famille" << "\t"<< "Categorie" << "\t"<< "Nom" << endl;
	for(i=0;i<v.size();i++)
	{
		eltP=v[i];
		outfile << eltP->NomNature.c_str()<< "\t";
		outfile << eltP->NomFamille.c_str()<< "\t";
		outfile << eltP->NomCategorie.c_str()<< "\t";
		outfile << eltP->Nom.c_str();

		//for(n=0;n<N_X;n++) outfile << eltP->Valeur[n]<< ";";
		outfile << endl;
	}
	outfile.close();
//    fclose(fichier);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall CL_Don::TriVector(vector<CL_EltProc*> &v)
{
	unsigned int i,j,n,min;
	int rep;
	CL_EltProc *eltP;
	n=v.size();
	for(i=0;i<n-1;i++)
	{
		min=i;
		for(j=i+1;j<n;j++)
		{
			rep=Comp(v[min],v[j]);
			if(rep==1) min=j;
		}
		eltP=v[i];v[i]=v[min];v[min]=eltP;
	}
}
//---------------------------------------------------------------------------
// tri dichotomique
//---------------------------------------------------------------------------
CL_EltProc * __fastcall CL_Don::cherche(vector<CL_EltProc*> &v,const CL_EltProc &eltP)
{
	unsigned nMin,nMax,nMil;
	int rep;
//CL_EltProc *eltPMin,*eltPMax,*eltPMil;
	nMin=0;
	nMax=v.size()-1;
	while(1)
	{
		nMil=(nMin+nMax)/2;
		/*
		 eltPMin=v[nMin];
		 eltPMax=v[nMax];
		 eltPMil=v[nMil];
		 */
		rep=Comp(eltP,v[nMil]);
//        rep=Comp(eltP,eltPMil);
		if(rep==1) nMin=nMil+1;//il est après
		else if(rep==0) return v[nMil];
		else nMax=nMil;//il est avant ou dedans
		if(nMin==nMax) return NULL;
	}
}

//---------------------------------------------------------------------------
// comparaison
// retourne   -1  eltP1 avant eltP2
//             1        après
//             0        égal
//---------------------------------------------------------------------------
int __fastcall CL_Don::Comp(const CL_EltProc& eltP1,const CL_EltProc &eltP2)
{
	if(eltP1.NomNature < eltP2.NomNature)
	return -1;
	if(eltP1.NomNature > eltP2.NomNature)
	return 1;

	if(eltP1.NomFamille < eltP2.NomFamille)
	return -1;
	if(eltP1.NomFamille > eltP2.NomFamille)
	return 1;

	if(eltP1.NomCategorie < eltP2.NomCategorie)
	return -1;
	if(eltP1.NomCategorie > eltP2.NomCategorie)
	return 1;

	if(eltP1.Nom < eltP2.Nom)
	return -1;
	if(eltP1.Nom == eltP2.Nom)
	return 0;
	else
	return 1;
}

