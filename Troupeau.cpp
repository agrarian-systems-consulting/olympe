//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"
#include "Aide.h"

//extern CL_Trad *T;
#include "Troupeau.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
extern CL_ES *ES;
extern CL_Trad *T;

TTroupeauFrm *TroupeauFrm;

//---------------------------------------------------------------------------
__fastcall TTroupeauFrm::TTroupeauFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
// voir méthodes dans Troupeau1
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::FormActivate(TObject *Sender)
{
	bool rep;
	static bool debut=true;
	if(debut==true)
	{
		debut=false;
		IniLesTreeView();
	}
	if(Origine==1) return;
	/*
	 TTreeNodes *tn;
	 tn=TVResultat->Items[0];
	 ShowMessage(tn->Text);
	 */
	//ES->AffLstMvtAniCount();
	Origine=1;
	AStocker=false;
	ASimuler=false;

	Col0=3;
	Agri= AgriSaisieFrm->Agri;
	An_0=Agri->DefSim->An_0;
	TroupeauEnCours=Agri->TroupeauEnCours;
	LabelModifie->Visible=false;
	DefinirLesGrilles();
	if(Agri->LstTroupeaux->Count==1)
	TroupeauEnCours=(CL_Troupeau*)Agri->LstTroupeaux->Items[0];
	else
//	if(TroupeauEnCours==NULL)
	{
		IniTSNature();
		PC->ActivePage=TSNature;
		PCChange(this);
		return;
	}
//	if(TroupeauEnCours==NULL)return;

	Debuter();
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::Debuter(void)
{
	int g;

	IniTSNature();
	IniTSResultats();
	LabNomTroupeau->Caption=TroupeauEnCours->CatBestiaux->Nom;

	LstMvtAni=TroupeauEnCours->LstMvtAni;
	EtablitAchatPrixAchat();

	for(g=0;g<GrilleX;g++)
	IniGrille(LesGrilles[g]);
	for(g=0;g<GrilleX;g++)
	VersGrille(LesGrilles[g]);

	PC->ActivePage=TSMouvement;
	PCChange(this);
}
//---------------------------------------------------------------------------
//les utilisateurs ont demandé de pouvoir définir des achats-> 2 grilles de saisie
// pour nombre et valeur (l'intro des achats comme j'ai prévu dans mvtAni semble trop compliqué)
//ils vont dans invAni->AAcheter et invAni->PrixAchat
//mais je n'avais pas prévu le stockage sur fichier  de ces 2 vecteurs
// et je ne veux pas modifier la structure du fichier
//dans invAni il y a un vecteur pour achat
//( les achats décidés dans mvtAni + les achats définis)
//Mais  cette information est stockée dans mvtAni de LstMvtAni
// ils sont identifiables mvtAni->Type==AACHETER
//
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::EtablitAchatPrixAchat(void)
{
	int i,n,l;
	CL_MvtAni *mvtAni;
	CL_InvAni *invAni;
	for(i=0;i<LstMvtAni->Count;i++)
	{
		mvtAni=(CL_MvtAni *)LstMvtAni->Items[i];
		if(mvtAni->Type==AACHETER)
		{
			l=mvtAni->Ligne;
			n=mvtAni->Date;
			invAni=TroupeauEnCours->V_InvAni->Vecteur[l-1];
			invAni->AAcheter[n]=mvtAni->Eff;
			invAni->PrixAchat[n]=mvtAni->Info;
		}
	}
}
//---------------------------------------------------------------------------
CL_InvAni* __fastcall TTroupeauFrm::TrouverAnimalNo(int no)
{
	int i;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;

	vecteur=TroupeauEnCours->V_InvAni;

	for(i=0;i<vecteur->Nbelt;i++)
	{
		invAni=vecteur->Vecteur[i];
		if(invAni->NoAnimal==no)
		return invAni;
	}
	return NULL;
}
//---------------------------------------------------------------------------
bool __fastcall TTroupeauFrm::VerifTroupeauEnCours(void)
{
	int i;
	int no;
	int noCat;
	int nbElt;
	int repMB;
	CL_Bestiaux *animal;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *v_InvAni;

	noCat=TroupeauEnCours->NoCatBestiaux;
	nbElt=0;
	for(i=0;i<V_Bestiaux->Nbelt;i++)
	{
		animal=V_Bestiaux->Vecteur[i];
		if(animal->NoCategorie==noCat)
		nbElt++;
	}

	if(nbElt==TroupeauEnCours->V_InvAni->Nbelt) return true;
	repMB=MessageBox(Handle,"Il faut simuler","Vous avez modifié les mouvements de troupeau",
			MB_ICONEXCLAMATION);

	if(repMB==IDNO) return false;

	//recreer V_InvAni
	v_InvAni =new CL_Vecteur<CL_InvAni>( );
	no=0;
	for(i=0;i<V_Bestiaux->Nbelt;i++)
	{
		animal=V_Bestiaux->Vecteur[i];
		if(animal->NoCategorie==noCat)
		{
			invAni=TrouveInvAni(no,animal,TroupeauEnCours->V_InvAni);
			v_InvAni->insSans(invAni);
			no++;
		}
	}
	delete TroupeauEnCours->V_InvAni;
	TroupeauEnCours->V_InvAni=v_InvAni;
	return true;
}
//---------------------------------------------------------------------------
CL_InvAni* __fastcall TTroupeauFrm::TrouveInvAni(int no,CL_Bestiaux *animal,CL_Vecteur<CL_InvAni>*vInvAni)
{
	int i;
	CL_InvAni *invAni;
	for(i=0;i<TroupeauEnCours->V_InvAni->Nbelt;i++)
	{
		invAni=TroupeauEnCours->V_InvAni->Vecteur[i];
		if(invAni->NoAnimal==animal->No) return invAni;
	}
	invAni=new CL_InvAni();
	invAni->No=no;
	invAni->Animal=animal;
	invAni->NoAnimal=animal->No;
	return invAni;
}
//****************************************************************************
//CHGT Page changt de page et verif de page précédente produits charges etc...
//
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::PCChanging(TObject *Sender,
		bool &AllowChange)
{
	if(LabelModifie->Visible==false) return;

	if(DernierePage==TSMouvement) return;

	//lire la grille modifiée
	BtBnStockerClick(this);
	if(ASimuler==true)
	{
		if(RGCouS->ItemIndex==0)
		{
			Simuler();
			AffEffectifs();
			ASimuler=false;
		}
		else
		EffConstant();

	}
	AStocker=true;
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::PCChange(TObject *Sender)
{
	int g;
	BtReportDroit->Visible=true;
	BtReportBas->Visible=true;
	ChBRepTout->Visible=true;
	BtBnSansBorne->Visible=false;
	//passage à l'autre page
	if (PC->ActivePage==TSNature)
	{
		BtReportDroit->Visible=false;
		BtReportBas->Visible=false;
		ChBRepTout->Visible=false;
	}
	else if(PC->ActivePage==TSMaxi)
	{
		BtBnSansBorne->Visible=true;
		// T alpha N numérique 0 non modifiable
		strcpy(TypeCol, "00NNNNNNNNNNNNNNNNN");
		LaGrille=GrilleMaxi;
	}
	else if(PC->ActivePage==TSPrix)
	{
		strcpy(TypeCol, "00NNNNNNNNNNNNNNNNN");
		LaGrille=GrillePrix;
	}
	else if(PC->ActivePage==TSValInv)
	{
		strcpy(TypeCol, "00NNNNNNNNNNNNNNNNN");
		LaGrille=GrilleValInv;
	}
	else if(PC->ActivePage==TSAchat)
	{
		strcpy(TypeCol, "00NNNNNNNNNNNNNNNNN");
		LaGrille=GrilleAchat;
	}
	else if(PC->ActivePage==TSPrixAchat)
	{
		strcpy(TypeCol, "00NNNNNNNNNNNNNNNNN");
		LaGrille=GrillePrixAchat;
	}
	else if(PC->ActivePage==TSMouvement)
	{
		BtReportDroit->Visible=false;
		BtReportBas->Visible=false;
		strcpy(TypeCol, "00N000000000000000000");
		LaGrille=GrilleMvt;
	}
	else if(PC->ActivePage==TSProCha)
	{
		strcpy(TypeCol, "00000000000000000000");
		LaGrille=GrilleProCha;
	}
	DernierePage=PC->ActivePage;
	if(DernierePage==TSNature) return;

	g=LaGrille->Tag;
	g=g; //aew
//	ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{

	LBChoixBestiauxFrm->Close();
	if(LabelModifie->Visible==true)
	{
		//lit la grille modifiée
		BtBnStockerClick(this);
		if(ASimuler==true)
		BtBnSimulerClick(this);
		AStocker=true;
	}
	if(AStocker==false) return;

	//supprimer LstAchat inutile et fonctions annexes
	CreeLstMvtAni();
	TroupeauEnCours->LstMvtAni=LstMvtAni;//220305
	ES->ecrireFichier();
}
//-------------------------------------------------------------------

//--------------------------------------------
void TTroupeauFrm::IniCaption(void) {
	LabPrix->Caption = LC_LabPrix;
	LabAchat->Caption = LC_LabAchat;
	TSAchat->Caption = T->LC_LabAchat;
	RBEcran->Caption = T->LC_RBEcran;
	LabEffMax->Caption = LC_LabEffMax;
	RGCouS->Caption = T->LC_BtEffectif;
//    GroupBox1->Caption=LC_GroupBox1;
	GBTroupeau->Caption = LC_GroupBox1;
	TSMaxi->Caption = LC_TSMaxi;
	TSMouvement->Caption = T->LC_MvtAnneeFrm;
	LabMvt->Caption = T->LC_DefBestiauxFrm;
	TSNature->Caption = T->LC_RGNatureG;
	LabNomTroupeau->Caption = LC_LabNomTroupeau;
	TSPrixAchat->Caption = LC_TSPrixAchat;
	LabPrixAchat->Caption = LC_LabPrixAchat;
	TSPrix->Caption = LC_TSPrix;
	GBResultat->Caption = T->LC_BtBnResultat;
	RSResultat->Caption = T->LC_BtBnResultat;
	GBResultats->Caption = T->LC_BtBnResultat;
	LabResTroup->Caption = LC_LabResTroup;
	LabResTroup->Caption = LC_LabResTroup;
	BtBnRien->Caption = LC_BtBnRien;
	BtBnSansBorne->Caption = LC_BtBnSansBorne;
	BtBnSimuler->Caption = LC_BtBnSimuler;
	GBSortie->Caption = T->LC_GBSortie;
	BtBnSup->Caption = T->LC_BtBnSupBesTrav;
	BtBnSup->Caption = T->LC_BtBnSupBesTrav;
	TroupeauFrm->Caption = T->LC_LBChoixBestiauxFrm;
	GBTrARetenir->Caption = LC_GBTrARetenir;
	LabNature->Caption = LC_LabNature;
	TSValInv->Caption = LC_TSValInv;
	LabValInv->Caption = LC_LabValInv;
	BtBnMazVenteAchat->Caption = LC_MazVenteAchat;
	BtBnMazMvt->Caption = LC_MazMvt;

	TSPrixAchat->Caption = LC_PrixAchat; //090206
	TSProCha->Caption = LC_ProCha;
	LabProCha->Caption = LC_ProChaT;

	ChBRepTout->Caption = T->LC_ChBRepTout;
	RGCouS->Items->Strings[0] = LC_AvecMvt;
	RGCouS->Items->Strings[1] = LC_Constant;

	//180507
	BtBnProcha->Caption = LC_ProCha;
	LabFinAnnee->Caption = LC_LabFinAnnee;

	IniLesTreeView();

	/*
	 TTreeNode *tn;
	 AnsiString as;
	 as=TVResultat->Items->Item[1]->Text;
	 TVResultat->Items->Item[1]->Text="AAAAAA";
	 as=TVResultat->Items->Item[1]->Text;
	 */
}
//--------------------------------------------
void TTroupeauFrm::TexteChaine(void) {
	L_Recommencer = T->TrouveTexte("TroupeauFrm", "L_Recommencer");
}
//--------------------------------------------
void TTroupeauFrm::TexteCaption(void) {
	LC_LabPrix = T->TrouveCaption("Troupeau", "LC_LabPrix");
	LC_LabAchat = T->TrouveCaption("Troupeau", "LC_LabAchat");
	LC_LabAchat = T->TrouveCaption("CL_Trad", "LC_LabAchat");
	LC_RBEcran = T->TrouveCaption("CL_Trad", "LC_RBEcran");
	LC_LabEffMax = T->TrouveCaption("Troupeau", "LC_LabEffMax");
	LC_BtEffectif = T->TrouveCaption("CL_Trad", "LC_BtEffectif");
	LC_GroupBox1 = T->TrouveCaption("Troupeau", "LC_GroupBox1");
	LC_TSMaxi = T->TrouveCaption("Troupeau", "LC_TSMaxi");
	LC_MvtAnneeFrm = T->TrouveCaption("CL_Trad", "LC_MvtAnneeFrm");
	LC_DefBestiauxFrm = T->TrouveCaption("CL_Trad", "LC_DefBestiauxFrm");
	LC_RGNatureG = T->TrouveCaption("CL_Trad", "LC_RGNatureG");
	LC_LabNomTroupeau = T->TrouveCaption("Troupeau", "LC_LabNomTroupeau");
	LC_TSPrixAchat = T->TrouveCaption("Troupeau", "LC_TSPrixAchat");
	LC_LabPrixAchat = T->TrouveCaption("Troupeau", "LC_LabPrixAchat");
	LC_TSPrix = T->TrouveCaption("Troupeau", "LC_TSPrix");
//       LC_[0]TLabel =T->TrouveCaption("CL_Trad" ,"LC_[0]TLabel");
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_LabResTroup = T->TrouveCaption("Troupeau", "LC_LabResTroupeau");
	LC_BtBnRien = T->TrouveCaption("Troupeau", "LC_BtBnRien");
	LC_BtBnSansBorne = T->TrouveCaption("Troupeau", "LC_BtBnSansBorne");
	LC_BtBnSimuler = T->TrouveCaption("Troupeau", "LC_BtBnSimuler");
	LC_GBSortie = T->TrouveCaption("CL_Trad", "LC_GBSortie");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");
	LC_LBChoixBestiauxFrm = T->TrouveCaption("CL_Trad",
			"LC_LBChoixBestiauxFrm");
	LC_GBTrARetenir = T->TrouveCaption("Troupeau", "LC_GBTrARetenir");
	LC_LabNature = T->TrouveCaption("Troupeau", "LC_LabNature");
	LC_TSValInv = T->TrouveCaption("Troupeau", "LC_TSValInv");
	LC_LabValInv = T->TrouveCaption("Troupeau", "LC_LabValInv");

	LC_PrixAchat = T->TrouveCaption("Troupeau", "LC_PrixAchat");
	LC_ProCha = T->TrouveCaption("Troupeau", "LC_ProCha");

	LC_ProChaT = T->TrouveCaption("Troupeau", "LC_ProChaT");
	LC_AvecMvt = T->TrouveCaption("Troupeau", "LC_AvecMvt");
	LC_Constant = T->TrouveCaption("Troupeau", "LC_Constant");
	LC_Procha = T->TrouveCaption("Troupeau", "LC_ProCha");

	//180507
	LC_Effectif = T->TrouveCaption("Troupeau", "LC_Effectif");
	LC_Achat = T->TrouveCaption("Troupeau", "LC_Achat");
	LC_Vente = T->TrouveCaption("Troupeau", "LC_Vente");
	LC_Valeur = T->TrouveCaption("Troupeau", "LC_Valeur");
	LC_Inventaire = T->TrouveCaption("Troupeau", "LC_Inventaire");
	LC_ProdCha = T->TrouveCaption("Troupeau", "LC_ProdCha");
	LC_Quantite = T->TrouveCaption("Troupeau", "LC_Quantite");
	LC_LabFinAnnee = T->TrouveCaption("Troupeau", "LC_LabFinAnnee");

	LC_EffVente = T->TrouveCaption("Troupeau", "LC_EffVente");
	LC_EffAchat = T->TrouveCaption("Troupeau", "LC_EffAchat");
	LC_ValVente = T->TrouveCaption("Troupeau", "LC_ValVente");
	LC_ValAchat = T->TrouveCaption("Troupeau", "LC_ValAchat");
	LC_ValInv = T->TrouveCaption("Troupeau", "LC_ValInv");

	LC_MazVenteAchat = T->TrouveCaption("Troupeau", "LC_MazVenteAchat");
	LC_MazMvt = T->TrouveCaption("Troupeau", "LC_MazMvt");

	IniCaption();

}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void __fastcall TTroupeauFrm::GrilleMaxiMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int c,r;
	MouseActive=true;
	LaGrille->MouseToCell(X,Y,c,r);
	CDebSel=c;
	RDebSel=r;

	CFinSel=c;
	RFinSel=r;
//    ShowMessage(AnsiString(CDebSel)+"  "+RDebSel);

}
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::GrilleMaxiMouseMove(TObject *Sender,
		TShiftState Shift, int X, int Y)
{
	int c,r;
	if(MouseActive==false) return;

	LaGrille->MouseToCell(X,Y,c,r);
	CFinSel=c;
	RFinSel=r;
	//ShowMessage(AnsiString(CFinSel)+"  "+RFinSel);
	if ((CDebSel!=CFinSel) ||(RDebSel!=RFinSel))
	{
		PlageCellules.Left = CDebSel;
		PlageCellules.Top = RDebSel;

		PlageCellules.Right = c; //CFinSel+1;
		PlageCellules.Bottom = r;//RFinSel;

		//LaGrille->EditorMode = false;

		LaGrille->Selection = PlageCellules;
	}

}
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::GrilleMaxiMouseUp(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int c,r;
	MouseActive=false;

	LaGrille->MouseToCell(X,Y,c,r);
	CFinSel=c;
	RFinSel=r;
	//ShowMessage(AnsiString(CFinSel)+"  "+RFinSel);
	if ((CDebSel!=CFinSel) ||(RDebSel!=RFinSel))
	{
		PlageCellules.Left = CDebSel;
		PlageCellules.Top = RDebSel;

		PlageCellules.Right = CFinSel; //+1;
		PlageCellules.Bottom = RFinSel;

		LaGrille->Selection = PlageCellules;
	}
	//ShowMessage("GrilleMaxiMouseUp");

}
//---------------------------------------------------------------------------

void TTroupeauFrm::IniLesTreeView(void) {
	TTreeNode *tn1, *tn11, *tn12, *tn13;
	TVResultat->Items->Clear();
	tn1 = new TTreeNode(TVResultat->Items);
	tn11 = TVResultat->Items->AddFirst(tn1, LC_Effectif);
	TVResultat->Items->AddChild(tn11, LC_Achat);
	TVResultat->Items->AddChild(tn11, LC_Vente);
	tn12 = TVResultat->Items->AddChild(tn1, LC_Valeur);
	TVResultat->Items->AddChild(tn12, LC_Achat);
	TVResultat->Items->AddChild(tn12, LC_Vente);
	TVResultat->Items->AddChild(tn12, LC_Inventaire);
	tn13 = TVResultat->Items->AddChild(tn1, LC_ProdCha);
	TVResultat->Items->AddChild(tn13, LC_Quantite);
	TVResultat->Items->AddChild(tn13, LC_Valeur);

	TVMvtEffectif->Items->Clear();
	tn1 = new TTreeNode(TVMvtEffectif->Items);
	tn11 = TVMvtEffectif->Items->AddFirst(tn1, LC_Effectif);
	TVMvtEffectif->Items->AddChild(tn11, LC_Achat);
	TVMvtEffectif->Items->AddChild(tn11, LC_Vente);

	TVMvtValeur->Items->Clear();
	tn1 = new TTreeNode(TVMvtValeur->Items);
	tn11 = TVMvtValeur->Items->AddFirst(tn1, LC_Valeur);
	TVMvtValeur->Items->AddChild(tn11, LC_Achat);
	TVMvtValeur->Items->AddChild(tn11, LC_Vente);
	TVMvtValeur->Items->AddChild(tn11, LC_Inventaire);

}
//---------------------------------------------------------------------------

bool __fastcall TTroupeauFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=750;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=750;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                BOUTONS
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::RGCouSClick(TObject *Sender)
{
	switch(RGCouS->ItemIndex)
	{
		case 0:
		RemplitLesMvtAnnee();
		Simuler();
		AffEffectifs();
		break;
		case 1:
		EffConstant();
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnSimulerClick(TObject *Sender)
{
	bool rep;
	AnsiString as;
	as=L_Recommencer.UpperCase();

	if(RGCouS->ItemIndex==0)
	{
		//rep=MessageBox(Handle,"recommence simulation\n Ignore Ventes Achats Mouvements décidés","RECOMMENCER", MB_YESNO|MB_ICONQUESTION);
		rep=MessageBox(Handle,L_Recommencer.c_str(),as.c_str(), MB_YESNO|MB_ICONQUESTION);
		if(rep==false)
		return;
		MazTout();//120108
		Simuler();
		AffEffectifs();
	}
	else
	EffConstant();

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::MazTout(void)
{
	int col;
	AnsiString value,s;
	CL_MvtAnnee *mvtAnnee;

	LabelModifie->Visible=true;
	Erreur=false;
	for(int r=1;r<GrilleMvt->RowCount;r++)
	for(int c=Col0;c<GrilleMvt->ColCount;c++)
	GrilleMvt->Cells[c][r]="";

	for(int r=1;r<GrilleMvt->RowCount;r++)
	{
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
			if(mvtAnnee==NULL) continue;

			mvtAnnee->Maz();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnMazClick(TObject *Sender)
{
	int col;
	AnsiString value,s;
	CL_MvtAnnee *mvtAnnee;

	LabelModifie->Visible=true;
	Erreur=false;
	for(int r=1;r<GrilleMvt->RowCount;r++)
	for(int c=Col0;c<GrilleMvt->ColCount;c++)
	GrilleMvt->Cells[c][r]="";

	for(int r=1;r<GrilleMvt->RowCount;r++)
	{
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
			if(mvtAnnee==NULL) continue;

			mvtAnnee->Maz();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnMazVenteAchatClick(TObject *Sender)
{
	CL_MvtAnnee *mvt;
	int r,c;
	bool rep;
	AnsiString as;
	as=L_Recommencer.UpperCase();
	rep=MessageBox(Handle,L_Recommencer.c_str(),as.c_str(), MB_YESNO|MB_ICONQUESTION);
//	rep=MessageBox(Handle,"recommence simulation\n Ignore Ventes Achats ","RECOMMENCER", MB_YESNO|MB_ICONQUESTION);
	if(rep==false)
	return;
	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;
			// mouvement d'une catégorie à une autre
			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			mvt->iAchat=0;
			mvt->iVente=0;
			memset(mvt->Sortie,0,sizeof(mvt->Sortie));
			memset(mvt->Achat,0,sizeof(mvt->Achat));
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::BtBnMazMvtClick(TObject *Sender)
{
	CL_MvtAnnee *mvt;
	int r,c;
	bool rep;
	AnsiString as;
	as=L_Recommencer.UpperCase();

	rep=MessageBox(Handle,L_Recommencer.c_str(),as.c_str(), MB_YESNO|MB_ICONQUESTION);
//	rep=MessageBox(Handle,"recommence simulation\n Ignore Mouvements Décidés ","RECOMMENCER", MB_YESNO|MB_ICONQUESTION);
	if(rep==false)
	return;

	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;

			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			mvt->iOr=0;
			mvt->iDest=0;
			memset(mvt->Entree, 0,sizeof(mvt->Entree));
			memset(mvt->Origine, 0,sizeof(mvt->Origine));
			memset(mvt->Sortie, 0,sizeof(mvt->Sortie));
			memset(mvt->Destin, 0,sizeof(mvt->Destin));

		}
	}
}
//---------------------------------------------------------------------------

