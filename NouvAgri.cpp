//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "Forme0.h"
#include "Forme00.h"
//#include "ChoixCritere.h"           //120109
#include "AgriClasst.h"

#include "GereAgri.h"
#include "AgriSaisie.h"
#include "Variante.h"
#include "NoteAgri.h"
#include "TVVarianteAgri.h"
#include "LBTypeZone.h"
#include "AgriDefSerie.h"

#include "CL_Trad.h"
#include "Aide.h"

#include "NouvAgri.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNouvAgriFrm *NouvAgriFrm;

extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TNouvAgriFrm::TNouvAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::FormActivate(TObject *Sender)
{
	AnsiString newNom;
	if(Origine==1) return;
	AStocker=false;
	switch(AFaire)
	{
		case COPIER:
		//Caption="Copie de  "+Agri->Nom;
		Caption=L_CopieDe+Agri->Nom;
		break;
		case MODIFIER:
		//Caption="Modifier "+Agri->Nom;
		Caption=L_Modifier+Agri->Nom;
		break;
		case CREER:
		Caption=LC_NouvAgriFrm;//"Nouvel agriculteur";
		break;
		case VARIANTE:
		//Caption="Variante de "+Agri->Nom;
		Caption=L_VarDe+Agri->Nom;
		//copierV_Agriculteur(); test suppression
		// aprés la définition faire appel ES->LesFilsDAgri ???
		break;
	}

	Origine=1;
	Forme00Frm->VideGrille(GrilleAgri);
	GrilleAgri->EditorMode=true;
//	Forme00Frm->VideGrille(GrilleAgri);
	LBTypeZoneFrm->Visible=false;
	switch(AFaire)
	{
		case COPIER:
		case MODIFIER:
		AffTitreGrille();
		AffAgri(Agri,1);
		GrilleAgri->RowCount=2;
		break;
		case CREER:
		AffTitreGrille();
		GrilleAgri->RowCount=2;
		break;
		case VARIANTE:
//			for(int i=0;i<V_Agriculteur->Nbelt;i++)
//		        agri=V_Agriculteur->Vecteur[i];
//    NouvAgriFrm->Height=400;
		AffTitreGrille();
		AffVariante();
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::copierV_Agriculteur(void)
{
	CL_Agriculteur *agri;
	ST_NoAgri *variante;
	// a quoi ça sert ?????
	for(int i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->LstVariante->Count==0) continue;
		for(int j=0;j<agri->LstVariante->Count;j++)
		{
			variante=(ST_NoAgri*)agri->LstVariante->Items[j];
			variante->Agri=V_Agriculteur->trouve(variante->No);
		}
	}
	for(int i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->EstVariante==true) continue;
		agri->Pere=agri;
		agri->Pere->No =agri->No;
		numeroteLesFils(agri,1);
	}

}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::numeroteLesFils(CL_Agriculteur *agri,int nP)
{
	ST_NoAgri *variante;
	agri->NoVariante=nP;
	if(agri->LstVariante->Count==0) return;

	nP=nP*10;
	for(int i=0;i<agri->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)agri->LstVariante->Items[i]; // Agri ou agri
		variante->Agri->EstVariante=true;
		variante->Agri->Pere=agri;
		nP++;
		numeroteLesFils(variante->Agri,nP);
	}
	return;

}
//---------------------------------------------------------------------------
bool __fastcall TNouvAgriFrm::SaisirNom(void)
{
	AnsiString newNom;
	AnsiString ancNom;
	CL_Agriculteur *agri;
	bool rep;
	int aModif;
	char nom[200],*ptr; //100907
	int n;
	switch(AFaire)
	{
		case CREER:
		newNom="";
		ancNom="";
		//rep=ES->EntrerNom("Nouvel Agriculteur",newNom,newNom);
		rep=ES->EntrerNom(Caption,newNom,newNom);
		break;
		case COPIER:
		strcpy(nom,Agri->Nom.c_str());
		ptr=strchr(nom,'-');// copie d'un cas sur + de 10 ans
							//  nomCas 2007-2037
							//retirer  2007-2037
		if(ptr)
		{
			n=strlen(nom);
			nom[n-9]=0;
			newNom=nom;
		}
		ancNom=Agri->Nom;
		//rep=ES->EntrerNom("A copier sous",newNom,newNom);
		rep=ES->EntrerNom(L_ACopSous,newNom,newNom);
		break;
		case MODIFIER:
		newNom=Agri->Nom;
		ancNom=Agri->Nom;
		//rep=ES->EntrerNom("Modifier le Nom en",newNom,newNom);
		rep=ES->EntrerNom(L_ModNomEn,newNom,newNom);
		break;
	}
	if(rep==true)
	{
		if(newNom==ancNom) return false;
		agri=V_Agriculteur->trouve(newNom);
		if(agri)
		{
			//MessageBox(Handle,"Il existe déjà","ERREUR",MB_OK|MB_ICONEXCLAMATION);
			MessageBox(Handle,L_Existe.c_str(),L_Erreur.c_str(),MB_OK|MB_ICONEXCLAMATION);
			return false;
		}
		AStocker=true;
		GrilleAgri->Cells[0][1]=newNom;
		if(AFaire==MODIFIER && Agri->LstVariante->Count>0)
		{
			Agri->Nom=newNom;
			//aModif=MessageBox(Handle,"Modifier le nom des variantes ","VARIANTES",MB_YESNO|MB_ICONQUESTION);
			aModif=MessageBox(Handle,L_ModNomVar.c_str(),L_VAR.c_str(),MB_YESNO|MB_ICONQUESTION);
			if(aModif==IDYES)
			ChangerNomVariantes(Agri);
		}
		return true;
	}
	else //rep=false
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::ChangerNomVariantes(CL_Agriculteur *agri)
{
	ST_NoAgri* variante;
	if(agri->LstVariante->Count==0) return;

	for(int i=0;i<agri->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)agri->LstVariante->Items[i]; // Agri ou agri
		variante->Agri->Nom=agri->Nom;
		ChangerNomVariantes(variante->Agri);
	}

}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::AffTitreGrille(void)
{
	int n,c;
	TListBox *lB;
	CL_Categorie *categorie;
	LstCategorie=new TList;
	// Nb colonne de la Grille

	//critéres
	for(n=0;n<AgriClasstFrm->ChLBCatTypeZone->Items->Count;n++)
	{
		categorie=(CL_Categorie*)AgriClasstFrm->ChLBCatTypeZone->Items->Objects[n];
		LstCategorie->Add((void*)categorie);
	}
	/*    //.......................
	 //120109
	 lB=ChoixCritereFrm->LBCritere;  //critere Retenu
	 for(int n=0;n<lB->Items->Count;n++)
	 {
	 categorie=(CL_Categorie*)lB->Items->Objects[n];
	 LstCategorie->Add((void*)categorie);
	 }
	 lB=ChoixCritereFrm->LBCritereNR;//critere Non Retenu
	 for(int n=0;n<lB->Items->Count;n++)
	 {
	 categorie=(CL_Categorie*)lB->Items->Objects[n];
	 LstCategorie->Add((void*)categorie);
	 }
	 */
	//............................
	GrilleAgri->ColCount=V_CatTypeZone->Nbelt+3;//LstCategorie->Count+3;
	Forme00Frm->VideGrille(GrilleAgri);

	c=0;
	GrilleAgri->ColWidths[c]=240;
	GrilleAgri->Cells[c][0]=L_Agri;//"Agriculteur";

	c=1;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][0]=L_NbVar;//"Nb Variante";

	c=2;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][0]=L_NoVar;//"N° Variante";

	c=3;
	/* sup le 120109
	 for(int n=0;n<LstCategorie->Count;n++)
	 {
	 GrilleAgri->ColWidths[c]=90;
	 categorie=(CL_Categorie*)LstCategorie->Items[n];
	 GrilleAgri->Cells[c][0]=categorie->Nom;
	 GrilleAgri->Objects[c][0]=(TObject*)categorie;
	 c++;
	 }
	 */
	for(int n=0;n<V_CatTypeZone->Nbelt;n++)
	{
		GrilleAgri->ColWidths[c]=90;
		categorie=V_CatTypeZone->Vecteur[n];
		GrilleAgri->Cells[c][0]=categorie->Nom;
		GrilleAgri->Objects[c][0]=(TObject*)categorie;
		c++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::AffAgri(CL_Agriculteur *agri,int r)
{
	int c,k,n;
	CL_Categorie *categorie;
	TList *lstCritere;
	CL_Item *critere;
	bool trouve;
	lstCritere=agri->LstCritere;

	GrilleAgri->Objects[0][r]=(TObject*)agri;
	GrilleAgri->Cells[0][r]=agri->Nom;

	GrilleAgri->Cells[1][r]=AnsiString(agri->NbVariante);
	GrilleAgri->Cells[2][r]=AnsiString(agri->NoVariante);

	c=3;
	for (k=0;k<agri->LstCritere->Count;k++)
	{
		critere=(CL_Item*)lstCritere->Items[k];
		trouve=false;

		for(n=0;n<V_CatTypeZone->Nbelt;n++)
		{
			categorie=V_CatTypeZone->Vecteur[n];
			if(critere->Categorie==categorie)
			{
				GrilleAgri->Cells[c][r]=critere->Nom;
				GrilleAgri->Objects[c][r]=(TObject*)critere;
				trouve=true;
				break;
			}
		}
		if(trouve==false) GrilleAgri->Cells[c][r]="???";
		c++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::AffVariante(void)
{

	int r;
	GrilleAgri->RowCount=1+Agri->NbVariante+1;
	NouvAgriFrm->Height=GrilleAgri->RowCount*GrilleAgri->DefaultRowHeight
	+50+PanelOK->Height;
	GrilleAgri->Height=GrilleAgri->RowCount*GrilleAgri->DefaultRowHeight;
	r=1;
	AffLesVariantes(Agri,r,Agri->NoVariante);
}
//---------------------------------------------------------------------------
int __fastcall TNouvAgriFrm::AffLesVariantes(CL_Agriculteur *agri,int r,int nP)
{
	ST_NoAgri *variante;
	AffAgri(agri,r);
//	GrilleAgri->Cells[1][r]=AnsiString(nP);
	if(agri->LstVariante->Count==0) return r;

	nP=nP*10;
	for(int i=0;i<agri->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)agri->LstVariante->Items[i]; // Agri ou agri
		r++;
		nP++;
		r=AffLesVariantes(variante->Agri,r,nP);
	}
	return r;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::GrilleAgriClick(TObject *Sender)
{
	CL_Categorie *categorie;
	int c=GrilleAgri->Col;
	int r=GrilleAgri->Row;
	if(c==0)
	{
		LBTypeZoneFrm->Visible=false;
		SaisirNom();

		//NoteAgriFrm->Agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
		//if(NoteAgriFrm->Agri==NULL)return;  //on démarre aucun agri n'a été défini
		//NoteAgriFrm->Show();
	}

	if(c>2)
	{
		categorie=(CL_Categorie *)GrilleAgri->Objects[c][0];
		CreeLBTypeZone(c,r,categorie);
	}
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::BtBnNotesClick(TObject *Sender)
{
	int r=GrilleAgri->Row;
	NoteAgriFrm->Agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	if(NoteAgriFrm->Agri==NULL)return; //on démarre aucun agri n'a été défini
	NoteAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::CreeLBTypeZone(int c,int r,CL_Categorie *categorie)
{
	int posG,posH;
	TRect rect;
	rect=GrilleAgri->CellRect(c, r);
	posG=Left+rect.Left;
	posH=Top+rect.Bottom+20; //20 ??
	LBTypeZoneFrm->Origine="NouvAgri";
	//cree LB l'affiche et donne la main à LBTypeZone
	LBTypeZoneFrm->CreeLB(posG,posH,r,categorie);
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::BtDonneesClick(TObject *Sender)
{
	BtOKClick(this);
	AgriSaisieFrm->Origine=0;
	AgriSaisieFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TNouvAgriFrm::BtOKClick(TObject *Sender)
{
	int c;
	AnsiString nom,text;
	CL_Agriculteur *agri;
	CL_Item *critere;
	ST_NoAgri *noAgri;
	nom=GrilleAgri->Cells[0][1].Trim();
	if(AStocker==false)
	{
		NoteAgriFrm->Close();
		TVVarianteAgriFrm->Close();
		Close();
		return;
	}

	switch(AFaire)
	{
		case CREER:
		agri=new CL_Agriculteur();
		agri->Nom=nom;
		agri->Flag=NOUVEAU;
		V_Agriculteur->ins(agri);
		break;
		case COPIER:
		if(Agri->LstSerie!=NULL) // simulation sur + de 10 ans
		{
			agri=CopierSerie(Agri,nom);
			break;
		}
		agri=new CL_Agriculteur(Agri);
		agri->LstVariante->Clear();
		agri->Nom=nom;
		agri->Flag=NOUVEAU;
		agri->NoVariante=0;
		agri->NbVariante=0;
		V_Agriculteur->ins(agri);
		break;
		case MODIFIER:
		Agri->Nom=nom;
		if(Agri->LstSerie) //modifier aussi nom des series 071008
		{
			for(int i=1;i<Agri->LstSerie->Count;i++)
			{
				noAgri=(ST_NoAgri*)Agri->LstSerie->Items[i];
				if(noAgri->Agri)
				noAgri->Agri->Nom=nom;
			}
		}
		agri=Agri;
		break;
		case VARIANTE:
//            V_AgriDepart->purge();  à remettre
// verifier constructeur par copie de CL_Agri
//            delete V_AgriDepart;
		Forme0Frm->CreeTVVarianteAgri(TVVarianteAgriFrm->TV,Agri);
		agri=Agri;
		break;
		default:
		ShowMessage("NouvAgri BtOk oubli");
	}
	//les criteres
	agri->LstCritere->Clear();
	for(c=3;c<GrilleAgri->ColCount;c++)
	{
		if(GrilleAgri->Objects[c][1]==NULL) continue;

		critere=(CL_Item*)GrilleAgri->Objects[c][1];
		agri->LstCritere->Add(critere);
	}

	GereAgriFrm->NouvAgri=agri;
	GereAgriFrm->CreeGrilleAgri();

	AgriSaisieFrm->Caption=agri->NomVC();
	ES->ecrireFichier();
	AgriSaisieFrm->Agri=agri;
	AgriEnCours=agri;

	AStocker=false;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::BtPasOkClick(TObject *Sender)
{
	AStocker=false;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TNouvAgriFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	int rep;
	if(AStocker==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),"MODIFICATION",
				//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		switch(rep)
		{
			case ID_YES:
			BtOKClick(this);
			break;
			case ID_CANCEL:
			return;
			case ID_NO:
			break;
		}
	}
	NoteAgriFrm->Close();
	TVVarianteAgriFrm->Close();
	LBTypeZoneFrm->Close();
	if(LstCategorie)
	{
		delete LstCategorie;
		LstCategorie=NULL;
	}
//    delete LstCategorie;                  à remettre mais ça plante
}
//---------------------------------------------------------------------------
void TNouvAgriFrm::TexteChaine(void) {

	L_Agri = T->TrouveTexte("NouvAgriFrm", "L_Agri");
	L_NbVar = T->TrouveTexte("NouvAgriFrm", "L_NbVar");
	L_NoVar = T->TrouveTexte("NouvAgriFrm", "L_NoVar");
	L_Existe = T->TrouveTexte("NouvAgriFrm", "L_Existe");
	L_Erreur = T->TrouveTexte("NouvAgriFrm", "L_Erreur");

	L_CopieDe = T->TrouveTexte("NouvAgriFrm", "L_CopieDe");
	L_Modifier = T->TrouveTexte("NouvAgriFrm", "L_Modifier");
	L_NouvAgri = T->TrouveTexte("NouvAgriFrm", "L_NouvAgri");
	L_VarDe = T->TrouveTexte("NouvAgriFrm", "L_VarDe");
	L_ACopSous = T->TrouveTexte("NouvAgriFrm", "L_ACopSous");
	L_ModNomEn = T->TrouveTexte("NouvAgriFrm", "L_ModNomEn");
	L_ModNomVar = T->TrouveTexte("NouvAgriFrm", "L_ModNomVar");
	L_VAR = T->TrouveTexte("NouvAgriFrm", "L_VAR");
}
//---------------------------------------------------------------------------
void TNouvAgriFrm::IniCaption(void) {
	BtBnNotes->Caption = T->LC_BtBnNotes;
	NouvAgriFrm->Caption = LC_NouvAgriFrm;
}
//--------------------------------------------
void TNouvAgriFrm::TexteCaption(void) {
	LC_BtBnNotes = T->TrouveCaption("CL_Trad", "LC_BtBnNotes");
	LC_NouvAgriFrm = T->TrouveCaption("NouvAgri", "LC_NouvAgriFrm");

	IniCaption();

}
//--------------------------------------------
CL_Agriculteur* TNouvAgriFrm::CopierSerie(CL_Agriculteur *agri0,
		AnsiString nom) {
	int n, i, j;
	int an0;
	ST_NoAgri *noAgri, *noAgriOr;
	CL_Agriculteur *agri, *copie, *agriAvant;
	TList *lstAgri, *lstNoAgri;
	AnsiString nomAgri, asDate;
	/*
	 char *chaineDebut,*chaineFin;

	 chaineDebut=nom.c_str();
	 chaineFin=strpbrk(chaineDebut,"-");
	 if(chaineFin)
	 {
	 n=chaineFin-chaineDebut-5;
	 chaineDebut[n]=0;
	 chaineFin+=5;
	 }
	 //100907
	 asDate=AnsiString("  ")+AnsiString(agri0->DefSim->An_0)+"-"+AnsiString(agri0->DefSim->An_0+9);

	 nomAgri=AnsiString(chaineDebut)+asDate+AnsiString(chaineFin);
	 */

	lstAgri = new TList;
	lstNoAgri = new TList;
	agriAvant = agri0;
	for (n = 0; n < agri0->LstSerie->Count; n++) {
		noAgri = (ST_NoAgri*) agri0->LstSerie->Items[n];
		agri = noAgri->Agri;
		//230908
		if (agri == NULL) {
			AgriDefSerieFrm->DefAgriApres(agriAvant, noAgri);
			agri = noAgri->Agri;

		}
		agriAvant = agri;
		copie = new CL_Agriculteur(agri);
		copie->LstVariante->Clear();
		copie->Nom = nom;
		copie->Flag = NOUVEAU;
		copie->NoVariante = 0;
		copie->NbVariante = 0;
		/*
		 //nom de la copie
		 an0=copie->DefSim->An_0;
		 asDate=AnsiString("  ")+AnsiString(an0)+"-"+AnsiString(an0+9);
		 nomAgri=AnsiString(chaineDebut)+asDate+AnsiString(chaineFin);
		 copie->Nom=nomAgri;
		 */
		V_Agriculteur->ins(copie);
		noAgriOr = new ST_NoAgri;
		noAgriOr->No = copie->No;
		noAgriOr->Agri = copie;

		lstAgri->Add(copie);
		lstNoAgri->Add(noAgriOr);
	}
	for (i = 0; i < lstAgri->Count; i++) {
		copie = (CL_Agriculteur*) lstAgri->Items[i];
		copie->LstSerie = new TList;
		for (j = 0; j < lstNoAgri->Count; j++) {
			noAgriOr = (ST_NoAgri*) lstNoAgri->Items[j];
			copie->LstSerie->Add(noAgriOr);
		}
	}
	copie = (CL_Agriculteur*) lstAgri->Items[0];
	delete lstAgri;
	delete lstNoAgri;
	noAgri = (ST_NoAgri*) copie->LstSerie->Items[0];
	agri = noAgri->Agri;
	an0 = agri->DefSim->An_0;
	nomAgri = agri->Nom;
	n = 1;
//    while(nom[n]!='-')n++;
	return copie;
}
//------------------------------------------------------------------------------
bool __fastcall TNouvAgriFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

