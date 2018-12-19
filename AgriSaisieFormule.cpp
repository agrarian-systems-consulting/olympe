//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "Compilateur.h"
#include "Erreur.h"
#include "AgriSaisieEnum.h"

#include "AgriSaisie.h"

extern CL_Compil *Compil;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//3

//EstCalcule A supprimer ???
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AffFormule(CL_Vecteur<CL_Formule>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)
{
// formules ont été recalculées dans CEstBon()

	Memo->Visible=true;
	ErreurFrm->Edit->Clear();

//	IniGrilleAssol();
	Memo->Width=LaGrille->Width;
	VersGrilleFormule(vecteur,vCat);
	CellDebut();
	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
/*
 tous les produits et charges ont été recalculés si nécessaire dans agrisaisie4
 CEstBon a vu une modif et a déclenché le calcul
 pour tous les produits et charges
 SI une formule existe pour ce produit
 regénérer le ou les textes (des noms ont pu changer !)
 à partir de l'arbre ou du reseau du programme
 la classe formule contient un ensemble de N_X programmes formule->LesProg
 ces programmes peuvent être les mêmes
 mais les textes donc LesProg[n]ont pu être modifiées par l'utilisateur
 pour une ou des années
 recalculer les résultats pour toutes les années
 SINON
 écrire le texte de la formule
 de la forme q:categorie:nom * p:categorie:nom
 ou seult    q:categorie:nom  pour les externalités
 génerer prog
 compiler le texte ce ne peut fournir qu'un arbre
 accrocher à cet arbre le texte
 recopier le prog pour toutes les années

 Mais ceci ne tient pas compte des formules uniquemen définies avec des variables
 d'où appel à CompleteFormule2 qui traite ce cas par AgriSaisiecalcul
 */
//retirer AgriRes V_RecDiv etc...
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CompleteFormule(void)
{
	CL_QuanVal *quanVal;
	CL_Formule *formule;
	CL_Prog *prog,*prog0;
	CL_Item *item;
	CL_Vecteur<CL_QuanVal> *vQuanVal;
	CL_Vecteur<CL_Formule> *vFormule;
	AnsiString as,asQ,asP;
	int noFamille;
	bool correct,erreur;
	switch(LaGrille->Tag)
	{
		case GProduit:
		vQuanVal=Agri->Resultat->V_Produit;
		vFormule=Agri->V_Produits;
		noFamille=PRODUIT;
		break;
		case GCharge:
		vQuanVal=Agri->Resultat->V_Charge;
		vFormule=Agri->V_Charges;
		noFamille=CHARGE;
		break;
		case GChStruct:
		vFormule=Agri->V_ChStruct;
		noFamille=CHSTRUCT;
		break;

		case GExtNeg:
		vQuanVal=Agri->Resultat->V_ExtNeg;
		vFormule=Agri->V_ExtNeg;
		noFamille=EXTNEG;
		break;
		case GExtPos:
		vQuanVal=Agri->Resultat->V_ExtPos;
		vFormule=Agri->V_ExtPos;
		noFamille=EXTPOS;
		break;
		default:ShowMessage("CompleteFormule A Faire");
	}
	for(int i=0;i<vFormule->Nbelt;i++)
	{
		formule=vFormule->Vecteur[i];
		formule->Existe=false;
	}
	for(int i=0;i<vQuanVal->Nbelt;i++)
	{
		quanVal=vQuanVal->Vecteur[i];
		item=quanVal->Item;
		formule=vFormule->trouve(item->No);
		if(formule!=NULL)
		formule->Origine='C'; //090709
		if(formule && formule->Origine!='C')//030908 c'est une formule contenant
		//des valeurs fournies
		formule=NULL;
		if(formule)
		{
			// correction palliative pb legrusse 310103
			// faut il garder ??
			prog=formule->LesProg[0];
			if(prog==NULL ||prog->Arbre==NULL)
			{
				vFormule->sup(formule->No);
				formule=NULL;
			}
		}
		// si la formule a déjà eté crée réecrire le texte  des noms ont pu changer
		// sinon la créer CreeProgramme
		//          soit du type quant*prix    produits charges
		//                       quant         externalités
		if(formule)
		{
			formule->Existe=true;
			erreur=false;
			prog0=NULL;
			for(int n=0;n<N_X;n++)
			{
				prog=formule->LesProg[n];
				if(prog==NULL) continue; //si on a prog NULL plante
				if(prog!=prog0)
				{
					// des noms ont pu changer
					Compil->ReEcritFormule(prog);
					prog0=prog;
				}
				Compil->JeTraite=formule->Nom;
				correct=Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
				if(correct==false) erreur =true;
			}
			if(erreur==false)
			formule->EstCalcule=true;
		}
		else
		{
			formule=new CL_Formule();

			GrilleModif[LaGrille->Tag]=true;

			formule->Flag='N';
			formule->Item=item;
			formule->No=item->No;
			formule->NoFamille=noFamille;
			formule->Supprimable=false;
			formule->Origine='C'; //calculé depuis l'assolement...
			formule->Existe=true;
			prog=Compil->CreeProg(noFamille,item);
			Compil->ReEcritFormule(prog);
			//par défaut c'est le meme arbre pour toutes les années
			for(int n=0;n<N_X;n++)
			{
				formule->LesProg[n]=prog;
				Compil->JeTraite=formule->Nom;
				correct=Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
			}
			vFormule->insSans(formule);
		}
	}
	//retirer les formules correspondant à des produits qui n'existent plus
	for(int i=0;i<vFormule->Nbelt;i++)
	{
		formule=vFormule->Vecteur[i];
		if(formule->Origine=='C'&& formule->Existe==false)
		{
			vFormule->sup(formule);
			i--;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::iniElt(CL_Elt *elt,int noFamille)
{
	CL_Poste *poste;
	elt->NoFamille=noFamille;
	poste=V_Poste->trouve(elt->NoFamille);
	elt->NomFamille=poste->Nom.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::completeElt(CL_Elt *eltG,CL_Elt *eltD,CL_Item *item)
{
	eltG->NoItem=item->No;
	eltG->Nom=item->Nom.c_str();
	eltG->Categorie=item->Categorie;
	eltG->NomCat=item->Categorie->Nom.c_str();

	eltD->NoItem=item->No;
	eltD->Nom=item->Nom.c_str();
	eltD->Categorie=item->Categorie;
	eltD->NomCat=item->Categorie->Nom.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CompleteFormule2(CL_Vecteur<CL_Formule>*vFormule)
{
	int n;
	CL_Formule *formule;
	CL_Prog *prog,*prog0;
	AnsiString as,asQ,asP;
	for(int i=0;i<vFormule->Nbelt;i++)
	{
		formule=vFormule->Vecteur[i];
		if(formule->Origine=='C') continue; //calculé depuis l'assolement...

		formule->EstCalcule=false;
		formule->Existe=true;
		//erreur=false;
		prog0=NULL;
		for(n=0;n<N_X;n++)
		{
			prog=formule->LesProg[n];
			if(prog==NULL) continue;
//                pour test
//                Compil->Arbre=prog->Arbre;
//                Compil->ecrireArbre();
			if(prog!=prog0)
			{
				Compil->ReEcritFormule(prog);
				prog0=prog;
			}
		}
	}
}
// tient compte des aleas prix cf CompCalcul
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalcFormule(CL_Vecteur<CL_Formule>*vecteur,int an)
{
	int i;
	AnsiString as,asQ,asP;
	CL_Prog *prog;
	CL_Formule *formule;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		formule=vecteur->Vecteur[i];
		prog=formule->LesProg[an];
		if(prog==NULL)
		{
			formule->Valeur[an]=0;
			continue;
		}
		Compil->JeTraite=formule->Nom;
		Compil->Calculer(prog->Reseau,prog->Arbre,an,an+1,formule->Valeur);
	}
}
/*
 //---------------------------------------------------------------------------
 void __fastcall TAgriSaisieFrm::CalcFormule(CL_Vecteur<CL_Formule>*vecteur)
 {
 int i,n;
 AnsiString as,asQ,asP;
 CL_Prog     *prog;
 CL_Formule  *formule;
 for(i=0;i<vecteur->Nbelt;i++)
 {
 formule=vecteur->Vecteur[i];
 for(n=0;n<N_X;n++)
 {
 prog=formule->LesProg[n];
 if(prog==NULL) continue;
 Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
 }
 //dans tous les cas on part de formule->Valeur
 // formule->Recette va etre supprimé il ne sert à rien
 //compte tenu de l'introduction de  la commercialisation
 //if(formule->Origine=='C')continue;             //210902
 //    for(n=0;n<N_X;n++)formule->Recette[n]= formule->Valeur[n];

 }
 }
 */
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellFormule(int col,int row)
{
	CL_Formule *formule;
	int rep;
	int n;
	//avant de passer à la cellule suivante
	if(col<=2) return true;

	if(RowVide(row)==true) return true;

	formule=(CL_Formule*)LaGrille->Objects[0][row];//300902
// test pour saisir dans cellule ne marxhe pas
//voir aussi AgriSaisieFrm IniGrille SaisirCellformule 
//    if(LaGrille->Cells[ColEC][RowEC]!=ValueAvant)
//        Memo->Text=LaGrille->Cells[ColEC][RowEC];
//    else
//    {
	n=col-4;
	Memo->Text=Memo->Text.Trim();
//    }
	if(Memo->Text.IsEmpty()==true) {formule->LesProg[n]=NULL; return true;} //300902
//               compiler va donner Arbre->BrancheX=0
	rep=CreeProg(formule,n);
	if(rep==false) return false;

	LaGrille->Cells[col][row]=Aff(formule->Valeur[n],0);
	return true;
}
//-----------------------------------------------------------------------------
/*
 on a modifié le texte
 compiler le texte
 creér prog
 accrocher arbre
 VERIFIER SI RESEAU
 */
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::CreeProg(CL_Formule *formule,int n)
{
	CL_Prog *prog;
	ErreurFrm->Edit->Clear();
	Compil->Erreur=false;
	Compil->Compiler(Memo->Text.c_str());
	if(Compil->Erreur==true)return false; //il y a erreur et c'est affiché

	Memo->Modified=false;
	prog=new CL_Prog();
	formule->LesProg[n]=prog;
//                                        pb si reseau
	prog->Arbre=new CL_Arbre(Compil->Arbre);
	prog->Source=Memo->Text;
	if(Compil->Reseau->MailleX)
	prog->Reseau=new CL_Reseau(Compil->Reseau);
	Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
	return true;
}
