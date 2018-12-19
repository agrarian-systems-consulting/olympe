//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "DefProcedure.h"

#include "TVDonProcedure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVDonProcedureFrm *TVDonProcedureFrm;
//---------------------------------------------------------------------------
__fastcall TTVDonProcedureFrm::TTVDonProcedureFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::FormActivate(TObject *Sender)
{
	RGModifiable=DefProcedureFrm->RGModifiable;
	LaGrille=DefProcedureFrm->LaGrille;
	RGClick(this);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::CreeTV(void)
{
	CreeTVDon(); //données modifiables
	Forme0Frm->CreeTVToutElt(TVRes,AgriEnCours,true);//donnees NON modifiables //Creer TVRes();
}
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::RGClick(TObject *Sender)
{
	// affichie OU données Modifiables OU données NON Modifiables
	if(RG->ItemIndex==0) {GBDon->Visible=true; GBRes->Visible=false;}
	else {GBDon->Visible=false; GBRes->Visible=true;}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------Données A Modifier----------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::TVDonClick(TObject *Sender)
{
	TTreeNode *choix,*pere,*fils,*petitFils;
	static TTreeNode *precedent=NULL;
	int i,j;
	TTreeView *TV=TVDon;
	if(RGModifiable->ItemIndex==0)
	{
		ShowMessage("Procédure Non Modifiable");
		return;
	}

	choix=TV->Selected;
	if(choix->Level==0)return;

	if(choix==precedent)return;
	precedent=choix;

	if(choix->Data==NULL)
	{

		if(choix->Text!="Tout") return;

		pere=choix->GetPrev(); //assolement
		for(i=0;i<pere->Count;i++)
		{
			fils=pere->Item[i];
			if(fils->Data)
			EcrireGrille(fils);
			else
			{
				for(j=0;j<fils->Count;j++)
				{
					petitFils=fils->Item[j];
					if(petitFils->Data)
					EcrireGrille(petitFils);
				}
			}
		}
		choix->Data=NULL;
		return;
	}
	EcrireGrille(choix);
}
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::EcrireGrille(TTreeNode *choix)
{
	CL_Elt *elt;
	int row;
	int rep;
	elt=(CL_Elt*)choix->Data;

	row=LaGrille->Row;

//    if( LaGrille->Objects[0][row]!=NULL) //ne sert pas
	if( LaGrille->Cells[0][row]!="")
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}
	elt->Flag='O'; ////modifiable
//    LaGrille->Objects[0][row]=(TObject*)elt;
	LaGrille->Cells[0][row]=elt->Nom;
	LaGrille->Cells[1][row]=elt->NomCat;
	LaGrille->Cells[2][row]=elt->NomFamille;
	LaGrille->Cells[3][row]=elt->NomNature;
	DefProcedureFrm->LabelModifie->Visible=true;
	LaGrille->Row++;
	LaGrille->RowCount++;
}
//---------------------------------------------------------------------------
//              Données NON modifiables
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::TVResClick(TObject *Sender)
{
	TTreeNode *choix;
	static TTreeNode *precedent=NULL;
	TTreeView *TV=TVRes;
	AnsiString nom;
	AnsiString LesAs[5];
	CL_Elt *elt;
	int row;
	int rep;
//améliorer affichage on connait elt
	if(RGModifiable->ItemIndex==0)
	{
		ShowMessage("Procédure Non Modifiable");
		return;
	}

	choix=TV->Selected;
	if(choix->Level==0) return;

	if(choix==precedent)return;
	precedent=choix;

	row=LaGrille->Row;

//    if( LaGrille->Objects[0][row]!=NULL)
	if( LaGrille->Cells[0][row]!="")
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	elt=(CL_Elt*)choix->Data;
	elt->Flag='N'; //  NON modifiable
	LaGrille->Objects[0][row]=(TObject*)elt;
	LaGrille->Cells[0][row]=elt->Nom;
	if(elt->NomCat) LaGrille->Cells[1][row]=elt->NomCat;
	if(elt->NomFamille) LaGrille->Cells[2][row]=elt->NomFamille;
	if(elt->NomNature) LaGrille->Cells[3][row]=elt->NomNature;

	DefProcedureFrm->LabelModifie->Visible=true;
	LaGrille->Row++;
	LaGrille->RowCount++;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//cree TV pour donnees MODIFIABLES
//pout toutes données PAS seulement données de AgriEnCours;
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::CreeTVDon(void)
{
	TTreeView *tV=TVDon;
	CL_Agriculteur *agri=AgriEnCours;
	TTreeNode *tn0,*tn1;
	//   TV->Visible=false;
	tV->Items->Clear();

	tn0=new TTreeNode(tV->Items);
	//PRODUCTION
	tn1=tV->Items->AddChildObject(tn0,"Production",NULL);
	ArbreAtelier(tV, tn1,"Production","Assolement",CULTURE, V_Culture,V_CatCulture);
	ArbreAtelier(tV, tn1,"Production","Animaux", ANIMAUX, V_Animaux,V_CatAnimaux);

	//PRODUITS
	ArbreItem(tV,tn0,"Produits","Produits",PRODUIT,V_Produit,V_CatProduit);
	//CHARGES
	ArbreItem(tV,tn0,"Charges","Charges",CHARGE,V_Charge,V_CatCharge);

	//VARIABLES
	ArbreItem(tV, tn0,"Variables","Variables", VARIABLE, V_Variable,V_CatVar);

	//CHARGES STRUCTURE
	ArbreItem(tV,tn0,"Dépenses","Charges Structure",CHSTRUCT,V_ChStruct,V_CatChStruct);

	//RECETTES DIVERSES
	ArbreItem(tV,tn0,"Recettes","Recettes Diverses",RECDIV,V_RecDiv,V_CatRecDiv);

	//DEPENSES DIVERSES
	ArbreItem(tV,tn0,"Dépenses","Dépenses Diverses",DEPDIV,V_DepDiv,V_CatDepDiv);

	//EXTERNALITES
	ArbreItem(tV,tn0,"Externalités","Externalités",EXTNEG,V_Externalite,V_CatExternalite);

	//!!!!!!!!!
	//IMMOBILISATION GLOBALES         cf CreerLstNom.cpp
	//rustine 151106
	if(agri!=NULL)
	BrancheGlobal(tV,tn0,"Global","Immobilisation",IMMO,agri->V_InvSom,"Immo");

	//FINANCES GLOBALES
	if(agri!=NULL)
	BrancheGlobal(tV,tn0,"Global","Financement",FINANCE,agri->V_FinSom,"Finance");

	//RECETTES PRIVEES
	ArbreItem(tV,tn0,"Recettes","Recettes Privées",RECFAM,V_RecFam,V_CatRecFam);

	//DEPENSES PRIVEES
	ArbreItem(tV,tn0,"Dépenses","Dépenses Privées",DEPFAM,V_DepFam,V_CatDepFam);

	//Tendance
	ArbreTendance(tV,tn0,"Tendance Produits",PRODUIT,V_TendPrixProd,V_TendQProd);
	ArbreTendance(tV,tn0,"Tendance  Charges",CHARGE,V_TendPrixCharge,V_TendQCharge);

	//ENSEMBLE
	ArbreEnsemble(tV,tn0);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::ArbreAtelier(TTreeView *tV,TTreeNode *tn,
		char* nomNature,char* nomFamille,
		int code,CL_Vecteur<CL_Atelier> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	TTreeNode *tn1;
	if(vecteur->Nbelt)
	{
		tn1=tV->Items->AddChildObject(tn,nomFamille,NULL);
		tV->Items->AddChildObject(tn1,"Tout",NULL);
		BrancheAtelier(tV,tn1,nomNature,nomFamille,code,vecteur,vCat);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::BrancheAtelier(TTreeView *tV,TTreeNode *tn,
		char* nomNature,char* nomFamille,
		int code, CL_Vecteur<CL_Atelier> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	int i,j;
	bool BrancheEstCree;
	CL_Categorie *cat;
	CL_Atelier *atelier;
	CL_Elt *elt;
	TTreeNode *tn1;
	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		BrancheEstCree=false;
		for(j=0;j<vecteur->Nbelt;j++)
		{
			atelier=vecteur->Vecteur[j];
			if(atelier->Categorie!=cat) continue;

			if(BrancheEstCree==false)
			{
				BrancheEstCree=true;
				tn1=tV->Items->AddChildObject(tn,cat->Nom,NULL);
				tV->Items->AddChildObject(tn1,"Tout",NULL);
			}
			elt=new CL_Elt(code,nomNature,nomFamille,
					atelier->Categorie->Nom.c_str(),
					atelier->Categorie->No,
					atelier->Nom.c_str(),
					atelier->No,
					NULL);

			tV->Items->AddChildObject(tn1,atelier->Nom,elt);
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::ArbreItem(TTreeView *tV,TTreeNode *tn,
		char* nomNature,char* nomFamille,
		int code,CL_Vecteur<CL_Item> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	TTreeNode *tn1;
	if(vecteur->Nbelt)
	{
		tn1=tV->Items->AddChildObject(tn,nomFamille,NULL);
		tV->Items->AddChildObject(tn1,"Tout",NULL);
		BrancheItem(tV,tn1,nomNature,nomFamille,code,vecteur,vCat);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::BrancheItem(TTreeView *tV,TTreeNode *tn,
		char* nomNature,char* nomFamille,
		int code, CL_Vecteur<CL_Item> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	int i,j;
	bool BrancheEstCree;
	CL_Categorie *cat;
	CL_Item *item;
	CL_Elt *elt;
	TTreeNode *tn1;
	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		BrancheEstCree=false;
		for(j=0;j<vecteur->Nbelt;j++)
		{
			item=vecteur->Vecteur[j];
			if(item->Categorie!=cat) continue;

			if(BrancheEstCree==false)
			{
				BrancheEstCree=true;
				tn1=tV->Items->AddChildObject(tn,cat->Nom,NULL);
				tV->Items->AddChildObject(tn1,"Tout",NULL);
			}
			elt=new CL_Elt(code,nomNature,nomFamille,
					item->Categorie->Nom.c_str(),
					item->Categorie->No,
					item->Nom.c_str(),
					item->No,
					NULL);

			tV->Items->AddChildObject(tn1,item->Nom,elt);
		}
	}
}
//---------------------------------------------------------------------------
//code PRODUIT ou CHARGE
//---------------------------------------------------------------------------
//                            nomNature        code
//    ArbreTendance(tV,tn0,"Tendance Produits",PRODUIT,V_TendPrixProd,V_TendQProd);

void __fastcall TTVDonProcedureFrm::ArbreTendance(TTreeView *tV,TTreeNode *tn,
		char* nomNature,int code,
		CL_Vecteur<CL_Tendance> *v_Prix,CL_Vecteur<CL_Tendance> *v_Quant)
{
	TTreeNode *tn1,*tn2;
	int codeP,codeQ;
	if (code==PRODUIT) {codeP=PPRODUIT; codeQ=QPRODUIT;}
	else {codeP=PCHARGE; codeQ=QCHARGE;}

	tn1=tV->Items->AddChildObject(tn,nomNature,NULL);
	tn2=tV->Items->AddChildObject(tn1,"Prix",NULL);
	BrancheTendance(tV,tn2,nomNature,"Prix",codeP,v_Prix);

	tn2=tV->Items->AddChildObject(tn1,"Quantités",NULL);
	BrancheTendance(tV,tn2,nomNature,"Quantités",codeQ,v_Quant);
}
// !! delta->Item ou delta->Atelier
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::BrancheTendance(TTreeView *tV,TTreeNode *tn,
		char* nomNature,char* nomFamille,
		int code,CL_Vecteur<CL_Tendance> *v_Tendance)
{
	int i,j;
	TTreeNode *tn1; //,*tn2;
	CL_Tendance *tendance;
	CL_Delta *delta;
	CL_Vecteur<CL_Delta> *vDelta;
	CL_Categorie *cat;
	CL_Elt *elt;
	for(i=0;i<v_Tendance->Nbelt;i++)
	{
		tendance=v_Tendance->Vecteur[i];
		tn1=tV->Items->AddChildObject(tn,tendance->Nom,NULL);
		vDelta=tendance->V_Delta;
		for(j=0;j<vDelta->Nbelt;j++)
		{
			delta=vDelta->Vecteur[j];
			cat=delta->Item->Categorie;
			elt=new CL_Elt(code,nomNature,nomFamille,cat->Nom.c_str(),cat->No,
					delta->Item->Nom.c_str(),delta->Item->No,delta->Pcent); //+++
			tV->Items->AddChildObject(tn1,delta->Item->Nom,elt);
		}
	}
}
//---------------------------------------------------------------------------
// INUTILISE
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::ArbreQuanVal(TTreeView *tV,TTreeNode *tn,
		AnsiString nom,CL_Vecteur<CL_QuanVal> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	TTreeNode *tn1,*tn2;

	if(vecteur->Nbelt)
	{
		tn1=tV->Items->AddChildObject(tn,nom,NULL);
		//Quantités
		tn2=tV->Items->AddChildObject(tn1,"Quantités",NULL);
		BrancheQuanValValeur(tV,tn2,vecteur,vCat);
		//Prix
		tn2=tV->Items->AddChildObject(tn1,"Prix",NULL);
		BrancheQuanValPrix(tV,tn2,vecteur,vCat);
	}
}
//---------------------------------------------------------------------------
// INUTILISE
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::BrancheQuanValValeur(TTreeView *tV,TTreeNode *tn,
		CL_Vecteur<CL_QuanVal> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	int i,j,n;
	bool BrancheEstCree;
	CL_Categorie *cat;
	CL_QuanVal *quanVal;
	float *valeur;
	TTreeNode *tn1;
	valeur=new float[N_X];
	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		BrancheEstCree=false;
		for(j=0;j<vecteur->Nbelt;j++)
		{
			quanVal=vecteur->Vecteur[j];
			if(quanVal->Item->Categorie!=cat) continue;

			//calcul du prix moyen
			//penser à deleter
			for(n=0;n<N_X;n++)
			{
				if(quanVal->Qte[n])
				valeur[n]=quanVal->Val[n]/quanVal->Qte[n];
				else
				valeur [n]=0;
			}
			if(BrancheEstCree==false)
			{
				BrancheEstCree=true;
				tn1=tV->Items->AddChildObject(tn,cat->Nom,NULL);
			}

			tV->Items->AddChildObject(tn1,quanVal->Item->Nom,valeur);
		}
	}
}
//---------------------------------------------------------------------------
// INUTILISE
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::BrancheQuanValPrix(TTreeView *tV,TTreeNode *tn0,
		CL_Vecteur<CL_QuanVal> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	int n;
	CL_QuanVal *quanVal;
	for(n=0;n<vecteur->Nbelt;n++)
	{
		quanVal=vecteur->Vecteur[n];
		//voir comment on peut avoir prix et ou le stocker!!
		tV->Items->AddChildObject(tn0,quanVal->Item->Nom,quanVal->Qte);
	}
}
//---------------------------------------------------------------------------
//Inutilisé
//---------------------------------------------------------------------------
//    ArbreFormule(tV,tn0,"Dépenses","Dépenses Privées",DEPFAM,V_DepFam,V_CatDepFam);
void __fastcall TTVDonProcedureFrm::ArbreFormule(TTreeView *tV,TTreeNode *tn,
		char *nomNature,char *nomFamille,
		int code,CL_Vecteur<CL_Formule> *vecteur,CL_Vecteur<CL_Categorie> *vCat)
{
	int i,j;
	bool BrancheEstCree;
	TTreeNode *tn1,*tn2;
	CL_Formule *formule;
	CL_Categorie *cat;
	CL_Elt *elt;

	if(vecteur->Nbelt==0) return;

	tn1=tV->Items->AddChildObject(tn,nomFamille,NULL);
	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		BrancheEstCree=false;
		for(j=0;j<vecteur->Nbelt;j++)
		{
			formule=vecteur->Vecteur[j];
			if(formule->Item->Categorie!=cat) continue;

			if(BrancheEstCree==false)
			{
				BrancheEstCree=true;
				tn2=tV->Items->AddChildObject(tn1,cat->Nom,NULL);

			}
			elt=new CL_Elt(code,nomNature,nomFamille,cat->Nom.c_str(),cat->No,
					formule->Item->Nom.c_str(),formule->Item->No,formule->Valeur);
			elt->Flag='F'; // F comme formule
			tV->Items->AddChildObject(tn2,formule->Item->Nom,elt);
		}
	}
}
//---------------------------------------------------------------------------
//    BrancheGlobal(tV,tn0,"Financement","Global",FINANCE,agri->V_InvSom,"LstNomInvSom");

void __fastcall TTVDonProcedureFrm::BrancheGlobal(TTreeView *tV,TTreeNode *tn,
		char *nomNature,char *nomFamille,
		int code,CL_Vecteur<CL_FN_Xp1> *vecteur,AnsiString AFaire)
//    int code,CL_Vecteur<CL_FN_Xp1> *vecteur,char *NomDeLaListe)
{
//int n;
	int i;
	TTreeNode *tn1;
	CL_FN_Xp1 *fN_Xp1;
	TStringList *lst;
	CL_Elt *elt;
	lst=new TStringList;
	if(AFaire=="Immo")
	{
		lst->Add("V. Résiduelle");
		lst->Add("Amortissement");
		lst->Add("Achat");
		lst->Add("Revente");
		lst->Add("Plus Value");
		lst->Add("Moins Value");
		lst->Add("Production d'Immo");
	}
	else if(AFaire=="Finance")
	{
		lst->Add("Dette LT");
		lst->Add("Remb Capital LT");
		lst->Add("Interet LT");
		lst->Add("Nouveaux LT");

		lst->Add("Dette CT");
		lst->Add("Remb Capital CT");
		lst->Add("Interet CT");
		lst->Add("Nouveaux CT");
	}
	else
	{
		ShowMessage("TTVDonProcedureFrm::BrancheGlobal OUBLI");
		return;
	}
	/*   bidouille   Montpellier 190405
	 n=LstNom->IndexOf(NomDeLaListe);
	 lst=(TStringList*)LstNom->Objects[n];
	 */
	tn1=tV->Items->AddChildObject(tn,nomFamille,NULL);
	tV->Items->AddChildObject(tn1,"Tout",NULL);
//    for(i=0;i<vecteur->Nbelt;i++)
	for(i=0;i<lst->Count;i++)
	{
		fN_Xp1=vecteur->Vecteur[i];
		elt=new CL_Elt(code,nomNature,nomFamille," ",0,lst->Strings[i].c_str(),i,fN_Xp1->Valeur);

		tV->Items->AddChildObject(tn1,lst->Strings[i],elt);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDonProcedureFrm::ArbreEnsemble(TTreeView *tV,TTreeNode *tn)
{
	int i;
	TTreeNode *tn1;
	CL_Ensemble *ensemble;
	char *nomNature="Effectifs et Assolements";
	char *nomFamille=" ";
	char *nomCat="  ";
	CL_Elt *elt;
	int code=ENSEMBLE; //attention ambiguite possible ENSEMBLE 3 EXTPOS 3
	if(V_Ensemble->Nbelt==0) return;

	tn1=tV->Items->AddChildObject(tn,"Effectifs et assolement",NULL);
	for(i=0;i<V_Ensemble->Nbelt;i++)
	{
		ensemble=V_Ensemble->Vecteur[i];
		//elt=new CL_Elt(code,nomNature,nomFamille,nomCat,noCat,nom,i,NULL);
		elt=new CL_Elt(code,nomNature,nomFamille,nomCat,0,ensemble->Nom.c_str(),ensemble->No,NULL);
		tV->Items->AddChildObject(tn1,ensemble->Nom,elt);
	}
}

