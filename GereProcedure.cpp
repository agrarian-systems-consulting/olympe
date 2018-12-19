//---------------------------------------------------------------------------

#include <vcl.h>
#include <dir.h>
#include <sysvari.h>
#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"
#include "Brouillon.h"
#include "Tableur.h"

#include "Main.h"
#include "AgriSaisie.h"
#include "TVDonProcedure.h"
#include "FichierEcrireXml.h"
#include "CL_Procedure.h"
#include "CL_Don.h"
#include "DefProcedure.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereProcedure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereComparaison"
#pragma resource "*.dfm"
TGereProcedureFrm *GereProcedureFrm;
extern CL_ES *ES;
extern CL_Xml *Xml;
extern CL_Don *Don;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereProcedureFrm::TGereProcedureFrm(TComponent* Owner) :
		TGereComparaisonFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::FormActivate(TObject *Sender)
{
	bool rep;
	int repInt;
	FILE *fichier;
	static bool xmlEstLu=false;
	vector<CL_EltProc*> v;
	if(Origine==0)
	{
		//test
		GBAtelier->Caption="Procédures";
//        Don->CreeV(v,NULL);
//        Don->EcrireDonnees(v,"Don.txt");
		if(NomFichierProcedure.Length()==0)
		{
			// creer nom standard procedures.xml
			CreerNomFichProcedure();
			fichier=fopen(NomFichierProcedure.c_str(),"r");
		}
		else fichier=fopen(NomFichierProcedure.c_str(),"r");

		if(fichier==NULL)
		{
			repInt=MessageBox(Handle,NomFichierProcedure.c_str(),"Fichier des Procédures : Nom par Defaut ?",
					MB_YESNO|MB_ICONQUESTION);
			if(repInt==IDYES)
			fichier=fopen(NomFichierProcedure.c_str(),"r");
			else
			{
				ShowMessage("Indiquer le fichier des procédures");
				rep=DemanderNomFichierProcedure();
				if(rep==false) return;
			}
		}

		Origine=1;

		PClasst->Visible=false;
		LabelModifie->Visible=false;
		DefProcedureFrm->LabelModifie->Visible=false;
		OrdreModif=false;
		Categorie=NULL;
		Procedure=NULL;

		V_Categorie=V_CatProcedure;

		if(xmlEstLu==false)
		{
			rep=LireXml();
			if(rep==false)
			{
				NomFichierProcedure="";
				return;
			}
			xmlEstLu=true;
		}
		CalculDonnees();
		CreeTV(); //tv des procédures et tv des données
				   // affiché dans GereProcedureFrm
		DefProcedureFrm->Agri=AgriEnCours;//voir
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::BtBnLesProceduresClick(TObject *Sender)
{
	Origine=0;
	NomFichierProcedure="";
	FormActivate(this);
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TGereProcedureFrm::DemanderNomFichierProcedure(void)
{
	AnsiString as;
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char file[MAXFILE];
	char ext[MAXEXT];
	char *nomFich;
	/** Construction du nom du fichier XML*/
	fnsplit(ES->FEcriture.c_str(),drive,dir,file,ext);

	OpenDProcedure->InitialDir=AnsiString(dir);
	if ( !OpenDProcedure->Execute() )
	return false;

	NomFichierProcedure=OpenDProcedure->FileName;
	nomFich=NomFichierProcedure.c_str();
	fnsplit(nomFich,drive,dir,file,ext);
	if(strcmp(ext,"xml")!=0)
	{
		fnmerge(nomFich,drive,dir,file,".xml");
		NomFichierProcedure=AnsiString(nomFich);
		//fnmerge(NomFichierProcedure,drive,dir,file,"csv");
	}
//    ShowMessage(NomFichierProcedure);
	return true;

}
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------
void TGereProcedureFrm::CreerNomFichProcedure(void) {
	AnsiString as;
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char file[MAXFILE];
	char ext[MAXEXT];
	char nomFich[MAXPATH];
	/** Construction du nom du fichier XML*/
	fnsplit(ES->FEcriture.c_str(), drive, dir, file, ext);
	fnmerge(nomFich, drive, dir, "Procedures", ".xml");
	NomFichierProcedure = AnsiString(nomFich);
}
//---------------------------------------------------------------------------
//cree les TV
//2703

//---------------------------------------------------------------------------
bool __fastcall TGereProcedureFrm::LireXml(void)
{
	int c,cX,p,pX;
	AnsiString s;
	_di_IXMLNode racine,brancheCat,brancheProc,feuille;
	_di_IXMLNodeCollection a;
	FILE *fichier;
	AnsiString nomCat;
	CL_Categorie *cat;

	AnsiString nomProc;
	CL_Procedure *proc;
	int noCat;
	int noProc;

	XMLDoc->FileName=NomFichierProcedure;
	s=XMLDoc->FileName;
	//ShowMessage(s);
	fichier=fopen(s.c_str(),"r");
	if(fichier==NULL)
	{
		ShowMessage("Je cree le fichier :  "+s);
		CreeLesProceduresTxt(s);
		XMLDoc->Active=true;
	}
	else
	fclose(fichier);
	XMLDoc->Active=true;
//    XMLDoc->Refresh();
	racine=XMLDoc->DocumentElement;
	s=racine->NodeName;
	if(s!="OlympeProcedure")
	{
		ShowMessage("ce n'est pas un fichier OlympeProcedure ");
		return false;
	}

	cX=racine->ChildNodes->GetCount();
	V_CatProcedure->vide();
	V_Procedure->vide();

	noCat=0;
	noProc=0;
	for(c=0;c<cX;c++)
	{
		brancheCat=racine->ChildNodes->GetNode(c);
		if(brancheCat->NodeType==ntComment) continue;
		nomCat=brancheCat->Attributes["nom"];
		// cree categorie et la mettre dans V_CatProcedure
		cat=new CL_Categorie();
		cat->Nom=nomCat;
		cat->No=noCat++;
		V_CatProcedure->insSans(cat);
		pX=brancheCat->ChildNodes->GetCount();

		for(p=0;p<pX;p++)
		{
			brancheProc=brancheCat->ChildNodes->GetNode(p);
			if(brancheProc->NodeType==ntComment) continue;

			nomProc=brancheProc->Attributes["nom"];
			proc=new CL_Procedure();
			proc->Nom=nomProc;
			proc->No=noProc++;
			proc->Categorie=cat;
			V_Procedure->insSans(proc);
			proc->LireXml(brancheProc);
		}
	}
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::EcrireXml(void)
{
	int c,cX,p;
	AnsiString s;
	_di_IXMLNode racine,brancheCat,brancheProc,feuille;
	AnsiString nomCat;
	CL_Categorie *cat;

	AnsiString nomProc;
	CL_Procedure *proc;
	racine=XMLDoc->DocumentElement;
	//racine->NodeList->Clear();
	cX=racine->ChildNodes->GetCount();

	for(c=0;c<V_CatProcedure->Nbelt;c++)
	{
		cat=V_CatProcedure->Vecteur[c];
		if(c<cX)
		brancheCat=racine->ChildNodes->GetNode(c);
		else
		brancheCat=racine->AddChild("categorie");

		brancheCat->SetAttribute("nom",cat->Nom);

		for(p=0;p<V_Procedure->Nbelt;p++)
		{
			proc=V_Procedure->Vecteur[p];
			if(proc->Categorie!=cat) continue;
			proc->EcrireXml(brancheCat,p);
		}
	}
	XMLDoc->SaveToFile(XMLDoc->FileName);
}
//---------------------------------------------------------------------------
//provisoire  A SUPPRIMER          ??
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::EcrireXmlTxt(void)
{
	int i,j;
	AnsiString s,date;
	TDateTime time;
	CL_Categorie *cat;
	CL_Procedure *procedure;
	s=XMLDoc->FileName;
	ofstream outfile(s.c_str());

	time=TDateTime::CurrentDateTime();
	date=time.DateTimeString();
	// n'accepte pas é ...
	//    outfile << "<?xml version=\"1.0\" standalone=\"yes\" ?> " <<endl;
	outfile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> " <<endl;

	outfile << "<OlympeProcedure>" <<endl;
	outfile << "<!--" << date.c_str() << "-->" << endl;

	for(i=0;i<V_CatProcedure->Nbelt;i++)
	{
		cat=V_CatProcedure->Vecteur[i];
		Xml->baliseDebut(outfile,"categorie","nom",cat->Nom);
		for(j=0;j<V_Procedure->Nbelt;j++)
		{
			procedure=V_Procedure->Vecteur[j];
			if(procedure->Categorie!=cat) continue;

			procedure->EcrireXmlTxt(outfile);
		}
		Xml->baliseFin(outfile,"categorie");
	}
	outfile << "</OlympeProcedure>" <<endl;
	outfile.close();

}

//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::CreeLesProceduresTxt(AnsiString NomFichierProcedure)
{
	AnsiString s,date;
	TDateTime time;
	ofstream outfile(NomFichierProcedure.c_str());

	time=TDateTime::CurrentDateTime();
	date=time.DateTimeString();
	// n'accepte pas é ...
	//    outfile << "<?xml version=\"1.0\" standalone=\"yes\" ?> " <<endl;
	outfile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> " <<endl;

	outfile << "<OlympeProcedure>" <<endl;
	outfile << "<!--" << date.c_str() << "-->" << endl;
	outfile << "</OlympeProcedure>" <<endl;
	outfile.close();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// creeTV //données à transférer à l'executable
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::CreeTV(void)
{
	Forme0Frm->CreeTVProcedure(TV,V_Categorie,V_Procedure);
	TVDonProcedureFrm->CreeTV();
}
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::TVClick(TObject *Sender)
{
	TVDblClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
	if(CEstBon()==false) return;

	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	if(elt->Level==0 ) //categorie
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
	else //procedure
	{
		Categorie= (CL_Categorie*)elt->Parent->Data;
		BtCatEnabled(true); //??
		// procedure à créer
		if(elt->Text=="[...]")
		{
			BtAtelierCreerClick(this);
		}
		else
		{

			Procedure= (CL_Procedure*)elt->Data;
			Procedure->Flag='E'; //existe
			BtAtelierEnabled(true);//??

			DefProcedureFrm->LabelModifie->Visible=false;
			DefProcedureFrm->PossibleModifier(false);
			DefProcedureFrm->Origine=0;
			DefProcedureFrm->Show();
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//CATEGORIE
//---------------------------------------------------------------------------
//creer
//void __fastcall TGereProcedureFrm::BtBnCreeCatClick(TObject *Sender)
//---------------------------------------------------------------------------
//supprimer
//void __fastcall TGereProcedureFrm::BtCatSupprimerClick(TObject *Sender)
//---------------------------------------------------------------------------
//nettoyer
//  inutile a voir
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::BtCatCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	int n;
	CL_Procedure *procedure;
	CL_Categorie *catOrigine;
	catOrigine=Categorie;

	newNom=catOrigine->Nom;
	rep=ES->EntrerNom("Nouvelle Catégorie copie de","",newNom);
	if(rep==false) return;

	rep=VerifNomCat(newNom,CREER);
	if(rep==false) return;

	for(n=0;n<V_Procedure->Nbelt;n++)
	{
		procedure=V_Procedure->Vecteur[n];
		if(procedure->Categorie!=catOrigine) continue;

		procedure=new CL_Procedure(procedure);
		procedure->Categorie=Categorie;
		//procedure->NoCategorie=Categorie->No; plus de No dorénavant
		procedure->Supprimable=true;

		V_Procedure->ins(procedure);
	}
//    EcrireLesProcedures();     //Provisoire ?? c'est fait dans procedure->ExrireXml
	// ES->ecrireFichier();
	CreeTV();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//modif Nom categorie
//void __fastcall TGereProcedureFrm::BtCatModifNomClick(TObject *Sender)
//---------------------------------------------------------------------------
// verifie nom catégorie et l'insére dans TV
//bool __fastcall TGereAtelierFrm::VerifNomCat(AnsiString newNom,int action)

//---------------------------------------------------------------------------
// PROCEDURE
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::BtAtelierCreerClick(TObject *Sender)
{
	TTreeNode *elt;
	AnsiString titre;
	AnsiString newNom;

	bool rep;

	elt=TV->Selected;
	if(elt)
	{
		if(elt->Level==0 )
		Categorie= (CL_Categorie*)elt->Data;
		else
		Categorie= (CL_Categorie*)elt->Parent->Data;
	}
	if(elt==NULL || Categorie==NULL)
	{
		ShowMessage("Aucune Catégorie sélectionnée");
		return;
	}

	newNom="";

	titre=Categorie->Nom+"  Nouvelle Procédure";
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	rep=VerifNomProcedure(newNom,CREER);
	if(rep==false) return;

	DefProcedureFrm->LabelModifie->Visible=true;
	DefProcedureFrm->Origine=0;
	DefProcedureFrm->PossibleModifier(true);
	DefProcedureFrm->VideLesGrilles();
	DefProcedureFrm->Show();

}
//---------------------------------------------------------------------------
//supprimer Procédure
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::BtAtelierSupprimerClick(TObject *Sender)
{
	int rep;
	//tout atelier sélectionné est visible
	if(Procedure==NULL) return;

	rep=MessageBox(Handle,"Vous voulez vraiment supprimer !",
			Procedure->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Procedure->sup(Procedure);
		Procedure=NULL;
		EcrireXmlTxt();
		Forme0Frm->CreeTVProcedure(TV,V_Categorie,V_Procedure);
	}
}
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::BtAtelierCopierClick(TObject *Sender)
{
	CL_Procedure *procedure= NULL;
	bool rep;
	AnsiString titre;
	AnsiString newNom;
	procedure=DefProcedureFrm->Procedure;

	if(procedure==NULL )
	{
		MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	//définir nom de la copie
	newNom=procedure->Nom;
	titre="Copie de  "+procedure->Nom;
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;

	//verif et insere
	rep=VerifNomProcedure(newNom,COPIER);
	if(rep==false) return;

	DefProcedureFrm->LabelModifie->Visible=true;
	DefProcedureFrm->Origine=0;
	DefProcedureFrm->PossibleModifier(true);
	DefProcedureFrm->VideLesGrilles();
	DefProcedureFrm->Show();

}
//---------------------------------------------------------------------------
// modif nom procedure
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::BtAtelierModifClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Procedure *procedure;
	bool rep;
	AnsiString newNom;

	if(TV->Selected==NULL)
	{
		MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	elt=TV->Selected;
	// categorie ou etat
	//modif nom Categorie
	if(elt->Level==0) return;
	procedure=DefProcedureFrm->Procedure;
	newNom=procedure->Nom;
	rep=ES->EntrerNom("Modification Nom ","",newNom);
	if (rep==true)
	{
		newNom=newNom.Trim();
		if(newNom==procedure->Nom) return;
		VerifNomProcedure(newNom,MODIFIER);
	}
	DefProcedureFrm->LabelModifie->Visible=true;
	DefProcedureFrm->Origine=0;
	DefProcedureFrm->PossibleModifier(true);
	DefProcedureFrm->VideLesGrilles();
	DefProcedureFrm->Show();

}
//---------------------------------------------------------------------------
// verif nom atelier et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereProcedureFrm::VerifNomProcedure(AnsiString newNom,int action)
{
	CL_Procedure *ancProc=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(" Pas de nom");return false;}

	// il n'y a pas d'atelier avec ce nom
	ancProc=V_Procedure->trouve(newNom);
	if(ancProc)
	{
		MessageBox(Handle,"Il existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Procedure->Nom= newNom;
		CreeTV();
		return true;
	}

	//CREER
	else if(action==CREER)
	{
		Procedure=new CL_Procedure();
		Procedure->Nom=newNom;
		Procedure->Categorie=Categorie;
		//Procedure->NoCategorie=Categorie->No;
		Procedure->Flag='N';//nouveau
		if(V_Procedure->Nbelt >0)
		{
			ancProc=V_Procedure->Vecteur[0];
			Procedure->AsExe= ancProc->AsExe;
			Procedure->AsFichier= ancProc->AsFichier;
		}
	}
	else if(action==COPIER)
	{
		Procedure=new CL_Procedure(Procedure);
		Procedure->Nom=newNom;
		Procedure->Flag='N'; //nouveau
	}
	return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Verif Close
//---------------------------------------------------------------------------
bool __fastcall TGereProcedureFrm::CEstBon(void)
{
	if(DefProcedureFrm->Visible==false) return true;

	DefProcedureFrm->Close();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::BtBnFermerClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	bool rep;
	if(TVDonProcedureFrm->Visible==true)
	TVDonProcedureFrm->Close();
	if(DefProcedureFrm->Visible==true)
	DefProcedureFrm->Close();

	if(CEstBon()==false)
	{
		CanClose=false;
		return;
	}

	if(OrdreModif==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),
				"ORDRE MODIFIE",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==true)
		{
			StockerOrdre();
//    EcrireLesProcedures();     //Provisoire ?? c'est fait dans procedure->ExrireXml

//            ES->ecrireFichier();
			LabelModifie->Visible=false;
		}
		OrdreModif=false;
	}

	if(LabelModifie->Visible==true)
	{
		//    EcrireLesProcedures();     //Provisoire ?? c'est fait dans procedure->ExrireXml

//        EcrireLesProcedures();     //Provisoire ??
//        ES->ecrireFichier();
		LabelModifie->Visible=false;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//reclasse Tlist origine dans GereAtelier
// créer une classe mère de GereAtelier
//                            GereProcedure
//                            GereIndic
//---------------------------------------------------------------------------
// clHaut
//void __fastcall TGereProcedureFrm::BtHautClick(TObject *Sender)

//---------------------------------------------------------------------------
//clBas
//void __fastcall TGereProcedureFrm::BtBasClick(TObject *Sender)
//---------------------------------------------------------------------------
void __fastcall TGereProcedureFrm::StockerOrdre(void)
{
	int i,jCat,jPro;
	TTreeNode *elt;
	CL_Categorie *categorie;
	CL_Procedure *Procedure;

	jCat=0;
	jPro=0;
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
			Procedure=(CL_Procedure*)elt->Data;
			V_Procedure->Vecteur[jPro]=Procedure;
			jPro++;
		}
	}
}

//--------------------------------------------
void TGereProcedureFrm::IniCaption(void) {
	GereProcedureFrm->Caption = LC_GereProcedureFrm;
	BtBnLesProcedures->Caption = LC_BtBnLesProcedures;
	GBAtelier->Caption = LC_GBAtelier;

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
void TGereProcedureFrm::TexteCaption(void) {
	LC_GereProcedureFrm = T->TrouveCaption("GereProcedure",
			"LC_GereProcedureFrm");
	LC_BtBnLesProcedures = T->TrouveCaption("GereProcedure",
			"LC_BtBnLesProcedures");
	LC_GBAtelier = T->TrouveCaption("GereProcedure", "LC_GBAtelier");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereProcedureFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

