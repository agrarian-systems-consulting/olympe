//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"
#include "Brouillon.h"
#include "Tableur.h"
#include "QRCatNom.h"
#include "QuelExcelCSV.h"

#include "Main.h"
#include "Atelier.h"
//#include "Espece.h"
//#include "GereCat.h"
#include "CopierDans.h"
#include "CL_Trad.h"

#include "GereCatItem.h"    //160206
#include "GereCatItem.h"
#include "GereAleaPrix.h"

#include "Aide.h"

#include "GereAtelier.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGereAtelierFrm *GereAtelierFrm;
extern CL_ES *ES;
extern CL_Excel *EX;

extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereAtelierFrm::TGereAtelierFrm(TComponent* Owner) :
		TForm(Owner) {
	if (ES->Verrou == MEDTER) //040205
	{
		BtCatCreer->Enabled = false;
		BtCatSupprimer->Enabled = false;
		BtCatNettoyer->Enabled = false;
		BtCatCopier->Enabled = false;
		BtCatModifNom->Enabled = false;

		BtAtelierSupprimer->Enabled = false;
		BtAtelierCreer->Enabled = false;
		BtAtelierCopier->Enabled = false;
		BtAtelierModifNom->Enabled = false;
	}

}
//---------------------------------------------------------------------------
//perso
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		PClasst->Visible=false;
		LabelModifie->Visible=false;
		OrdreModif=false; //151203
		Personnaliser();
		Categorie=NULL;
		Atelier=NULL;
		BtCatEnabled(false);
		BtAtelierEnabled(false);
		Origine=1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::Personnaliser(void)
{
	switch(Nature)
	{
		case CULTURE:
		//Caption=                   "Cultures";
		V_Atelier= V_Culture;
		V_Categorie= V_CatCulture;
		break;
		case ANIMAUX:
		//Caption=                  "Animaux";
		V_Atelier= V_Animaux;
		V_Categorie= V_CatAnimaux;
		break;
		case VIVRIER:
		//Caption=                  "Pluriannuelles";
		V_Atelier= V_Vivrier;
		V_Categorie= V_CatVivrier;
		break;
		default:
		ShowMessage("GereAtelier Personnaliser Oubli");
	}
	AtelierFrm->Nature=Nature;
	CreeTV();

}
//---------------------------------------------------------------------------
// utilisé par GereEspece
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::CreeTV(void)
{
	switch(Nature)
	{
		case PERENNE:Forme0Frm->CreeTVPerenne(TV, V_Espece,V_Perenne);break;
		case CULTURE:Forme0Frm->CreeTVAtelier(TV, V_CatCulture,V_Culture);break;
		case ANIMAUX:Forme0Frm->CreeTVAtelier(TV, V_CatAnimaux,V_Animaux);break;
		case VIVRIER:Forme0Frm->CreeTVAtelier(TV, V_CatVivrier,V_Vivrier);break;
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtCatEnabled(bool aff)
{
	/*
	 BtCatCreer->Enabled=true;
	 BtCatSupprimer->Enabled=aff;
	 BtCatNettoyer->Enabled=aff;
	 BtCatCopier->Enabled=aff;
	 BtCatModifNom->Enabled=aff;
	 */
}
//----------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtAtelierEnabled(bool aff)
{
	/*
	 BtAtelierCreer->Enabled=aff;
	 BtAtelierSupprimer->Enabled=aff;
	 BtAtelierCopier->Enabled=aff;
	 BtAtelierModifNom->Enabled=aff;
	 */
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::TVClick(TObject *Sender)
{
	TVDblClick(Sender);
}
//----------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
	if(CEstBon()==false) return;

	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	//ShowMessage(elt->Count);
	if(elt->Level==0 )//categorie
	{
		// catégorie à créer
		if(elt->Text=="[...]")
		{
			BtCatCreerClick(this);
			return;
		}
		else
		{
			// catégorie existe  qu'est ce qu'on va en faire ?
			Categorie= (CL_Categorie*)elt->Data;
			BtCatEnabled(true);
		}
	}
	else //atelier
	{
		Categorie= (CL_Categorie*)elt->Parent->Data;
		BtCatEnabled(true);
		// atelier à créer
		if(elt->Text=="[...]")
		{
			BtAtelierCreerClick(this);
			return;
		}
		else
		{
			Atelier= (CL_Atelier*)elt->Data;
			BtAtelierEnabled(true);
			AffAtelier();
//pourquoi            TV->Selected=NULL;  //310305
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::AffAtelier(void)
{

	if(PClasst->Visible==true)return;

	// si pas d'atelier voulez vous créer
	if(Atelier==NULL)
	{
		BtAtelierCreerClick(this);
		return;
	}

	//indique si atelier supprimable
	if(Atelier->Supprimable==false)
	AtelierFrm->LabUtilise->Visible=true;
	else
	AtelierFrm->LabUtilise->Visible=false;

	AtelierFrm->Atelier=Atelier;
	AtelierFrm->Origine=0;
	AtelierFrm->Show();
	AtelierFrm->AffAtelier();
	AtelierFrm->Caption=Categorie->Nom;//151203
	AtelierFrm->Nature=Nature;//151203

}
//---------------------------------------------------------------------------
// CATEGORIE
//---------------------------------------------------------------------------
// créer
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtCatCreerClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
//	if(CestBon()==false) return;

	newNom="";
	rep=ES->EntrerNom(GereCatItemFrm->L_NouvCat,"",newNom);//160206
	//rep=ES->EntrerNom("Nouvelle Catégorie","",newNom);
	if(rep==false) return;

	VerifNomCat(newNom,CREER);
}
//---------------------------------------------------------------------------
//  supprimer
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtCatSupprimerClick(TObject *Sender)
{
	int rep;

	if(Categorie==NULL )return;
	// si a des éléments tous doivent etre supprimables
	if(Categorie->Supprimable==false)
	{
		MessageBox(Handle,T->L_CatAElt.c_str(),Categorie->Nom.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,"a des éléments !",Categorie->Nom.c_str(),MB_OK|MB_ICONSTOP);
		return;
	}

	//rep=MessageBox(Handle,"Vous voulez vraiment supprimer !",     //160206
	rep=MessageBox(Handle,GereCatItemFrm->L_JSup.c_str(),
			Categorie->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		V_Categorie->sup(Categorie);
		ES->ecrireFichier();
		CreeTV();
		Categorie=NULL;
		BtCatEnabled(false);
		BtAtelierEnabled(false);
	}
}
//---------------------------------------------------------------------------
// Nettoie: retire tous les ateliers inutilisés
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtCatNettoyerClick(TObject *Sender)
{
//
	int n;
	bool jAiSupprime;
	CL_Atelier *atelier;
	jAiSupprime=false;
	for(n=0;n<V_Atelier->Nbelt;n++)
	{
		atelier=V_Atelier->Vecteur[n];
		if(atelier->Categorie!=Categorie) continue;

		if(atelier->Supprimable==false) continue;

		V_Atelier->sup(atelier);
		n--;
		jAiSupprime=true;
	}
	if(jAiSupprime==false) return;

	ES->ecrireFichier();
	CreeTV();

}
//---------------------------------------------------------------------------
//  copier
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtCatCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	int n;
	CL_Atelier *atelier;
	CL_Categorie *catOrigine;
	catOrigine=Categorie;

	newNom=catOrigine->Nom;
	//rep=ES->EntrerNom("Nouvelle Catégorie copie de","",newNom);1600306
	rep=ES->EntrerNom(L_NouvCatCopDe,"",newNom);
	if(rep==false) return;

	rep=VerifNomCat(newNom,CREER);
	if(rep==false) return;

	for(n=0;n<V_Atelier->Nbelt;n++)
	{
		atelier=V_Atelier->Vecteur[n];
		if(atelier->Categorie!=catOrigine) continue;

		atelier=new CL_Atelier(atelier);

		atelier->Categorie=Categorie; //210203
		atelier->NoCategorie=Categorie->No;
		atelier->Supprimable=true;

		V_Atelier->ins(atelier);
	}

	ES->ecrireFichier();
	CreeTV();
}
//---------------------------------------------------------------------------
// modifier nom
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtCatModifNomClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Categorie *categorie;
	bool rep;
	AnsiString newNom;
	if(TV->Selected==NULL)
	{
		//MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		MessageBox(Handle,GereCatItemFrm->L_PasSel.c_str(),GereCatItemFrm->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		return;
	}

	elt=TV->Selected;
	// categorie ou atelier
	//modif nom Categorie
	if(elt->Level==0)
	categorie=(CL_Categorie*)elt->Data;
	else
	categorie= (CL_Categorie*)elt->Parent->Data;

	newNom=categorie->Nom;
	//rep=ES->EntrerNom("Modification Nom Categorie","",newNom);
	rep=ES->EntrerNom(L_ModifNomCat,"",newNom);
	if (rep==true)
	{
		newNom=newNom.Trim();
		if(newNom==categorie->Nom) return;
		VerifNomCat(newNom,MODIFIER);
	}
}
//---------------------------------------------------------------------------
// verifie nom catégorie et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereAtelierFrm::VerifNomCat(AnsiString newNom,int action)
{
	CL_Categorie *ancCat=NULL;

	// le nom existe
	newNom=newNom.Trim();
	//if (newNom.IsEmpty()==true){ ShowMessage(" Pas de nom");return false; }
	if (newNom.IsEmpty()==true) {ShowMessage(GereCatItemFrm->L_PasNom);return false;}

	// il n'y a pas de categorie
	ancCat=V_Categorie->trouve(newNom);
	if(ancCat)
	{
		//MessageBox(Handle,"Il existe déjà","ERREUR",
		MessageBox(Handle,GereCatItemFrm->L_Existe.c_str(),GereCatItemFrm->L_Erreur.c_str(),
				MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	Categorie->Nom= newNom;

	//CREER
	else if(action==CREER)
	{
		Categorie=new CL_Categorie();
		Categorie->Nom=newNom;
		V_Categorie->ins(Categorie);
	}

	ES->ecrireFichier();
	CreeTV();
	return true;
}
//---------------------------------------------------------------------------
// ATELIER
//---------------------------------------------------------------------------
//créer
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtAtelierCreerClick(TObject *Sender)
{
	TTreeNode *elt;
	AnsiString titre;
	AnsiString newNom;

	bool rep;
	if(CEstBon()==false) return;

	elt=TV->Selected;
	if(elt==NULL)
	{
		ShowMessage("Quelle Categorie ?");
		return;
	}
	if(elt->Level==0 )
	Categorie= (CL_Categorie*)elt->Data;
	else
	Categorie= (CL_Categorie*)elt->Parent->Data;

	if(Categorie==NULL)
	{
		ShowMessage(L_PasCatSel); //"Aucune Catégorie sélectionnée");
		return;
	}

	newNom="";
	titre=Categorie->Nom+L_NouvAtelier; //"  Nouvel Atelier";
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	VerifNomAtelier(newNom,CREER);

}
//---------------------------------------------------------------------------
//supprimer
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtAtelierSupprimerClick(TObject *Sender)
{
	int rep;
	//tout atelier sélectionné est visible
	if(Atelier==NULL) return;

	//sinon j'essaie de supprimer l'atelier
	if(Atelier->Supprimable==false)
	{
		//MessageBox(Handle," Atelier utilisé !","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		MessageBox(Handle,L_AtUtil.c_str(),GereCatItemFrm->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		return;
	}

	//rep=MessageBox(Handle,"Vous voulez vraiment supprimer !",
	rep=MessageBox(Handle,GereAleaPrixFrm->L_Sup.c_str(),

			Atelier->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Atelier->sup(Atelier);
		Atelier=NULL;

		ES->ecrireFichier();
		CreeTV();
		//pb possible si atelier a erreurs
		// on ne peut supprimer que atelier correct:idiot!!
		//AtelierFrm->Close();
	}
}
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtAtelierCopierClick(TObject *Sender)
{
	CL_Atelier *atelier= NULL;
	bool rep;
	AnsiString titre;
	AnsiString newNom;
	atelier=AtelierFrm->Atelier;

	if(atelier==NULL )
	{
		//MessageBox(Handle,"Rien à copier","PROBLEME",
		MessageBox(Handle,GereCatItemFrm->L_RienACop.c_str(),GereCatItemFrm->L_Prob.c_str(),
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(CEstBon()==false) return;

	newNom="";
	CopierDansFrm->EntrerNom(atelier);
	rep=CopierDansFrm->Retour;
	if(rep==false )return;
//    newNom=CopierDansFrm->NewNom;
//..............

	/*
	 //...........
	 //définir nom de la copie
	 newNom=atelier->Nom;
	 titre="Copie de  "+atelier->Nom;
	 //    rep=ES->EntrerNom(titre,"",newNom);
	 //    CopierDansFrm->ShowModal();
	 CopierDansFrm->EntrerNom(atelier,newNom);
	 rep=CopierDansFrm->Retour;
	 if(rep==false )return;
	 //..............
	 */
	//verif et insere
	//c'est fait dans CopierDans
	//VerifNomAtelier(newNom,COPIER);
	ES->ecrireFichier();
	CreeTV();
	AffAtelier();

}
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtBnCopierDansClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//modifier nom
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtAtelierModifClick(TObject *Sender)
{
//TTreeNode *elt;
	bool rep;
	AnsiString newNom;

	//if(Atelier==NULL){ ShowMessage("Aucun Choix");return;}
	if(Atelier==NULL) {ShowMessage(GereCatItemFrm->L_PasSel);return;}
	newNom=Atelier->Nom;
	//rep=ES->EntrerNom("Modification Nom Atelier","",newNom);

	rep=ES->EntrerNom(L_ModifNomAt,"",newNom);
	if (rep==true)
	{
		newNom=newNom.Trim();
		if(newNom==Atelier->Nom) return;
		VerifNomAtelier(newNom,MODIFIER);
	}
}
/*
 //---------------------------------------------------------------------------
 //modifier nom
 //---------------------------------------------------------------------------
 void __fastcall TGereAtelierFrm::BtAtelierModifClick(TObject *Sender)
 {
 TTreeNode *elt;
 CL_Atelier    *atelier;
 bool rep;
 AnsiString newNom;
 if(TV->Selected==NULL)
 {
 MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
 return;
 }

 elt=TV->Selected;
 // categorie ou atelier
 //modif nom Categorie
 if(elt->Level==0)  return;
 atelier=AtelierFrm->Atelier;
 newNom=atelier->Nom;
 rep=ES->EntrerNom("Modification Nom Atelier","",newNom);
 if (rep==true)
 {
 newNom=newNom.Trim();
 if(newNom==atelier->Nom) return;
 VerifNomAtelier(newNom,MODIFIER);
 }
 }
 */
//---------------------------------------------------------------------------
// verif nom atelier et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereAtelierFrm::VerifNomAtelier(AnsiString newNom,int action)
{
	CL_Atelier *ancAtelier=NULL;

	// le nom existe
	newNom=newNom.Trim();
	//if (newNom.IsEmpty()==true){ ShowMessage(" Pas de nom");return false; }
	if (newNom.IsEmpty()==true) {ShowMessage(GereCatItemFrm->L_PasNom);return false;}

	// il n'y a pas d'atelier avec ce nom
	ancAtelier=V_Atelier->trouve(newNom);
	if(ancAtelier)
	{
		///MessageBox(Handle,"Il existe déjà","ERREUR",
		//MB_OK|MB_ICONEXCLAMATION);
		MessageBox(Handle,GereCatItemFrm->L_Existe.c_str(),
				GereCatItemFrm->L_Erreur.c_str(),MB_OK|MB_ICONEXCLAMATION);

		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Atelier->Nom= newNom;
		CreeTV();
		return true;
	}

	//CREER
	else if(action==CREER)
	{
		Atelier=new CL_Atelier();
		Atelier->Nom=newNom;
		Atelier->Categorie=Categorie;
		Atelier->NoCategorie=Categorie->No;
		Atelier->Nature=Nature; //030604

		switch(Nature)
		{
			case CULTURE:
			case ANIMAUX:Atelier->NbPhase=3;break;
			case VIVRIER:Atelier->NbPhase=5;break;
			//case PERENNE:Atelier->NbPhase=AtelierFrm->Espece->NbPhase;break;
		}
		V_Atelier->ins(Atelier); //310105
	}
	else if(action==COPIER)
	{
		//Atelier=new CL_Atelier(Atelier);
		//Atelier->Nom=newNom;
	}
	//V_Atelier->ins(Atelier);

	ES->ecrireFichier();
	CreeTV();
	AffAtelier();
	return true;
}
//---------------------------------------------------------------------------
// Fermeture brutale
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtBnFermerClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
//	rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;
}
//---------------------------------------------------------------------------
// Verif Close
//---------------------------------------------------------------------------
bool __fastcall TGereAtelierFrm::CEstBon(void)
{
//int rep;
	if(AtelierFrm->Visible==false) return true;

	AtelierFrm->Close();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(CEstBon()==false)
	{
		CanClose=false;
		return;
	}
	if(OrdreModif==true)
	{
		StockerOrdre();
		ES->ecrireFichier();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::StockerOrdre(void)
{
	int i,jCat,jAt;
	TTreeNode *elt;
	CL_Categorie *categorie;
	CL_Atelier *atelier;

	jCat=0;
	jAt=0;
	for(i=0;i<TV->Items->Count-1;i++) //ne pas voir le dernier [...]
	{
		elt=TV->Items->Item[i];
		if(elt->Text=="[...]")continue;

		if(elt->Level==0)
		{
			categorie=(CL_Categorie *)elt->Data;
			V_Categorie->Vecteur[jCat]=categorie;
			jCat++;
		}
		else
		{
			atelier=(CL_Atelier*)elt->Data;
			V_Atelier->Vecteur[jAt]=atelier;
			jAt++;
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;

}
//---------------------------------------------------------------------------
// Pour TOUS LES HERITIERS
//reclasse Tlist origine dans GereAtelier
// créer une classe mère de GereAtelier
//                            GereEtat
//                            GereIndic
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtClHautClick(TObject *Sender)
{
	TTreeNode *elt,*precedent;
	int j;
	AnsiString texte;
	bool expansion;
	if(TV->Selected==NULL) return;

	elt = TV->Selected;
	j=elt->AbsoluteIndex;
	texte=elt->Text;
	expansion=elt->Expanded;
	if (j<1 || texte=="[...]" || TV->Items->Item[j-1]->Level<elt->Level)
	return;

	TV->Items->BeginUpdate();
	if (TV->Items->Item[j-1]->Level==elt->Level)
	{
		TV->Selected=TV->Items->InsertObject(TV->Items->Item[j-1],texte,elt->Data);
		elt->Delete();
	}
	else
	{
		precedent=elt->getPrevSibling();
		precedent=TV->Items->InsertObject(precedent,texte,elt->Data);
		j=elt->AbsoluteIndex;
		if (elt->GetLastChild()!=NULL)
		{
			for(int i=j+1;i<=elt->GetLastChild()->AbsoluteIndex;i+=2)
			{
				TV->Items->AddChildObject(precedent,TV->Items->Item[i]->Text,TV->Items->Item[i]->Data);
			}
		}
		elt->DeleteChildren();
		elt->Delete();
		TV->Selected=precedent;
	}
	TV->Selected->Expanded=expansion;
	TV->Items->EndUpdate();

	OrdreModif=true;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtClBasClick(TObject *Sender)
{
	TTreeNode *elt,*suivant;
	int j,indexEnfant=0;
	AnsiString texte;
	bool expansion;

	if(TV->Selected==NULL) return;

	elt = TV->Selected;
	j=elt->AbsoluteIndex;
	texte=elt->Text;
	expansion=elt->Expanded;

	if (elt->GetLastChild()!=NULL)
	indexEnfant=elt->GetLastChild()->AbsoluteIndex;

	if ( (max(j,indexEnfant)+2)>=TV->Items->Count
			|| TV->Items->Item[j+2]->Level<elt->Level)
	return;

	TV->Items->BeginUpdate();

	if (TV->Items->Item[j+2]->Level==elt->Level)
	{
		TV->Selected=
		TV->Items->InsertObject(TV->Items->Item[j+2],texte,elt->Data);
		elt->Delete();
	}
	else
	{
		suivant=elt->getNextSibling();
		suivant=suivant->getNextSibling();
		suivant=TV->Items->InsertObject(suivant,texte,elt->Data);
		for(int i=j+1;i<=elt->GetLastChild()->AbsoluteIndex;i++)
		{
			TV->Items->AddChildObject(suivant, TV->Items->Item[i]->Text,
					TV->Items->Item[i]->Data);
		}
		elt->DeleteChildren();
		elt->Delete();
		TV->Selected=suivant;
	}

	TV->Selected->Expanded=expansion;
	TV->Items->EndUpdate();
	OrdreModif=true;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TGereAtelierFrm::BtBnFermClasstClick(TObject *Sender)
{
	PClasst->Visible=false; //290302
	/*
	 BtCopier->Enabled=true;
	 Btsupprimer->Enabled=true;
	 BtChgtNom->Enabled=true;
	 BtBnCreeCat->Enabled=true;
	 BtBnCreeAtelier->Enabled=true;
	 */
}
//---------------------------------------------------------------------------
/*
 void __fastcall TGereAtelierFrm::BtClasser1Click(TObject *Sender)
 PClasst->Visible=true;               //290302

 BtCopier->Enabled=false;
 Btsupprimer->Enabled=false;
 BtChgtNom->Enabled=false;
 BtBnCreeCat->Enabled=false;
 BtBnCreeAtelier->Enabled=false;
 */

void __fastcall TGereAtelierFrm::BtClasserClick(TObject *Sender)
{
//TV->AlphaSort(true);
//TV->CustomSort(NULL,true);

	PClasst->Visible=true;
}
//------------------------------------------------------------------------------

void __fastcall TGereAtelierFrm::TVCompare(TObject *Sender,
		TTreeNode *Node1, TTreeNode *Node2, int Data, int &Compare)
{
	if(Node1->Text=="[...]") Compare=1;
	else if(Node2->Text=="[...]") Compare=-1;
	else Compare=AnsiStrIComp(Node1->Text.c_str(),Node2->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TGereAtelierFrm::BtBnAlphaClick(TObject *Sender)
{
	TV->AlphaSort();
}
//---------------------------------------------------------------------------
void TGereAtelierFrm::TexteChaine(void) {
	L_NouvCatCopDe = T->TrouveTexte("GereAtelierFrm", "L_NouvCatCopDe");
	L_ModifNomCat = T->TrouveTexte("GereAtelierFrm", "L_ModifNomCat");
	L_PasCatSel = T->TrouveTexte("GereAtelierFrm", "L_PasCatSel");
	L_NouvAtelier = T->TrouveTexte("GereAtelierFrm", "L_NouvAtelier");
	L_AtUtil = T->TrouveTexte("GereAtelierFrm", "L_AtUtil");
	L_ModifNomAt = T->TrouveTexte("GereAtelierFrm", "L_ModifNomAt");
}
//--------------------------------------------

void TGereAtelierFrm::IniCaption(void) {
	BtBnAlpha->Caption = T->LC_BtBnAlpha;
	GBAtelier->Caption = T->LC_AtelierFrm;
	GBCategorie->Caption = T->LC_RGCat;
	GereAtelierFrm->Caption = LC_GereAtelierFrm;
	BtClasser->Caption = T->LC_BtClasser;
	BtCatCopier->Caption = T->LC_BtBnCopier;
	BtAtelierCopier->Caption = T->LC_BtBnCopier;
	BtCatCreer->Caption = T->LC_BtBnCreer;
	BtAtelierCreer->Caption = T->LC_BtBnCreer;
	BtCatModifNom->Caption = T->LC_BtModifier;
	BtAtelierModifNom->Caption = T->LC_BtModifier;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtCatNettoyer->Caption = T->LC_BtBnEffacer;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;

	BtCatSupprimer->Caption = T->LC_BtBnSupBesTrav;
	BtAtelierSupprimer->Caption = T->LC_BtBnSupBesTrav;
}
//--------------------------------------------
void TGereAtelierFrm::TexteCaption(void) {
	LC_BtBnAlpha = T->TrouveCaption("CL_Trad", "LC_BtBnAlpha");
	LC_AtelierFrm = T->TrouveCaption("CL_Trad", "LC_AtelierFrm");
	LC_RGCat = T->TrouveCaption("CL_Trad", "LC_RGCat");
	LC_GereAtelierFrm = T->TrouveCaption("GereAtelier", "LC_GereAtelierFrm");
	LC_BtClasser = T->TrouveCaption("CL_Trad", "LC_BtClasser");
	LC_BtBnCopier = T->TrouveCaption("CL_Trad", "LC_BtBnCopier");
	LC_BtBnCreer = T->TrouveCaption("CL_Trad", "LC_BtBnCreer");
	LC_BtModifier = T->TrouveCaption("CL_Trad", "LC_BtModifier");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_BtBnEffacer = T->TrouveCaption("CL_Trad", "LC_BtBnEffacer");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereAtelierFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=545;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TGereAtelierFrm::BtBnImpClick(TObject *Sender)
{
	AnsiString as;
	switch(Nature)
	{
		case CULTURE:
		as=T->L_Atelier+"  "+T->L_Culture;
		QRCatNomFrm->PrepareAtelier(AgriEnCours,as.c_str(),V_CatCulture,V_Culture);
		break;
		case ANIMAUX:
		as=T->L_Atelier+"  "+T->L_Animaux;
		QRCatNomFrm->PrepareAtelier(AgriEnCours,as.c_str(),V_CatAnimaux,V_Animaux);
		break;
		case VIVRIER:
		as=T->L_Atelier+"  "+T->L_Vivrier;
		QRCatNomFrm->PrepareAtelier(AgriEnCours,as.c_str(),V_CatVivrier,V_Vivrier);
		break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TGereAtelierFrm::BtBnExcelClick(TObject *Sender)
{
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;
	switch(Nature)
	{
		case CULTURE:
		EX->CatCulture(V_CatCulture,V_Culture);
		break;
		case ANIMAUX:
		EX->CatCulture(V_CatAnimaux,V_Animaux);
		break;
		case VIVRIER:
		EX->CatCulture(V_CatVivrier,V_Vivrier);
		break;
	}
	EX->FermerFichier();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

