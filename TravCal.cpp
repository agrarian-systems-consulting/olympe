//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "Forme0.h"
#include "Forme01.h"

#include "SortieEcran.h"
#include "ChoixMotif.h"

#include "TravCal.h"
//#include "Graph.h"   //???
#include "CL_SousPeriode.h"
#include "CL_Matrice.h"
#include "CL_BesTravAtelier.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "TravGraph.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern CL_Trad *T;

TTravCalFrm *TravCalFrm;
//
//        Calendrier de travail
//
//---------------------------------------------------------------------------
//----------------Modifier le 17/08/2010-------------------------------------
//---------------------------------------------------------------------------
//           LES CONSTRUCTEURS DES CLASSES SPECIFIQUES
int CmpBornes(const void *a, const void *b) {
	int borne1, borne2;
	borne1 = *(int*) a;
	borne2 = *(int*) b;
	return (borne1 - borne2);
}

//---------------------------------------------------------------------------
CL_Legende::CL_Legende(int no, AnsiString nom, int couleur, int style) {
	int height = 20;
	int width = 40;
//---------------------------------------------
	Texte = new TStaticText(TravCalFrm->GB);
	Texte->Font->Size = 8;
	Texte->Caption = nom;

	Couleur = new TShape(TravCalFrm->GB);
	Couleur->Brush->Style = bsSolid; //(TBrushStyle)style;
	Couleur->Brush->Color = (TColor) couleur;
	Couleur->OnMouseDown = TravCalFrm->RecCouleurMouseDown;

	Motif = new TShape(TravCalFrm->GB);
	Motif->Pen->Color = clBlack;
	Motif->Brush->Color = clBlack;
	if (style == bsSolid)
		style = bsClear;
	Motif->Brush->Style = (TBrushStyle) style;
//    Motif->Brush->Style=bsCross;
	Motif->OnMouseDown = TravCalFrm->RecMotifMouseDown;

	Ensemble = new TShape(TravCalFrm->GB);
	Ensemble->Pen->Color = clBlack;
	Ensemble->Brush->Color = Couleur->Brush->Color;
	Ensemble->Brush->Style = Motif->Brush->Style;
	if (Motif->Brush->Style == bsClear)
		Ensemble->Brush->Color = Couleur->Brush->Color;

	Texte->Height = height;
	Couleur->Height = height;
	Motif->Height = height;
	Ensemble->Height = height;

	Texte->Width = width * 6;
	Couleur->Width = width;
	Motif->Width = width;
	Ensemble->Width = width;

	/*  Texte->Left=   10;
	 Couleur->Left= Texte->Left+Texte->Width;
	 Motif->Left=   Couleur->Left+Couleur->Width;
	 Ensemble->Left=Motif->Left+Motif->Width;
	 */
	Couleur->Left = 10;
	Motif->Left = Couleur->Left + Couleur->Width;
	Ensemble->Left = Motif->Left + Motif->Width;
	Texte->Left = Ensemble->Left + Ensemble->Width + 10;
//    Texte->Top=   TravCalFrm->GB->Top+10+no*Couleur->Height;
	Texte->Top = TravCalFrm->GB->Top + 30 + no * Couleur->Height;
	Couleur->Top = Texte->Top;
	Motif->Top = Texte->Top;
	Ensemble->Top = Texte->Top;
	if (!Couleur->Parent) {
		TravCalFrm->GB->InsertControl(Texte);
		TravCalFrm->GB->InsertControl(Couleur);
		TravCalFrm->GB->InsertControl(Motif);
		TravCalFrm->GB->InsertControl(Ensemble);

	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//               CALTRAV
__fastcall TTravCalFrm::TTravCalFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::FormCreate(TObject *Sender)
{
	EstInitialise=false;
	LBCalendrierItemIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::FormActivate(TObject *Sender)
{
	int an;
	int n;
	static bool utilisable;
	if(Origine!=0) return;

	if(V_Calendrier->Nbelt==0)
	{
		ShowMessage(L_PasCal); //"Aucun calendrier");
		return;
	}

	utilisable=false;
	for(n=0;n<V_Calendrier->Nbelt;n++)
	{
		Calendrier=V_Calendrier->Vecteur[n];
		if(Calendrier->V_Periode->Nbelt==0)
		Calendrier->Flag='N';
		else
		{
			Calendrier->Flag='O';
			utilisable=true;
		}
	}
	if(utilisable==false )
	{
		ShowMessage(L_PasPeriode); //"Aucun calendrier ne contient des périodes");
		return;
	}

	DefinirCoulMotif();

	Forme0Frm->CreeLBCalendrier(LBCalendrier,V_Calendrier);
	LBCalendrier->ItemIndex=LBCalendrierItemIndex;
	Calendrier=(CL_Calendrier*)LBCalendrier->Items->Objects[LBCalendrierItemIndex];
	LabCal->Caption=Calendrier->Nom;

	Agri=AgriEnCours;

	// années
	CBAn->Clear();
	an=Agri->DefSim->An_0;
	AnSim=an;
	for(int i=0;i<10;i++,an++)CBAn->Items->Add(an);
	CBAn->ItemIndex=CBAnItemIndex;

	Origine=1;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtBnCalculerClick(TObject *Sender)
{
	bool rep;
	rep=VerifCompletude(); //besoins sont définis 101005
	if(rep==false) return;

	EtablirBornes();
	CalculBesPeriode(CBAn->ItemIndex);//090306
	BtBnLegendeClick(this);//Visible
	LegendeAtelier();//a quoi ça sert

	OrdreAffichage();

}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	CL_SousPeriode* sPeriode;
//float *besSousPer;
	CL_BesTravAtelier *besTravAtelier;

	if(LesBornes==NULL) return;

	delete []LesBornes; LesBornes=NULL;
	for(int i=0;i<LstSousPeriodes->Count;i++)
	{
		sPeriode=(CL_SousPeriode*)LstSousPeriodes->Items[i];
		delete sPeriode;
	}
	delete LstSousPeriodes; LstSousPeriodes=NULL;

	for(int n=0;n<LstBesAtelier->Count;n++)
	{
		besTravAtelier=(CL_BesTravAtelier*)LstBesAtelier->Items[n];
		delete besTravAtelier;
	}
	delete LstBesAtelier; LstBesAtelier=NULL;

	delete []TotBesSousPer; TotBesSousPer=NULL;
	if(LstLegende) {delete LstLegende; LstLegende=NULL;}

	ChoixMotifFrm->Close();

}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitQ.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);

	if(rep==IDYES) Application->Terminate();

	else return;
}

//---------------------------------------------------------------------------
//LB des calendriers->choix
void __fastcall TTravCalFrm::LBCalendrierClick(TObject *Sender)
{
	int n;
	n=LBCalendrier->ItemIndex;
	LBCalendrierItemIndex=n;
	//verif et stockage que si définitions d'élements de la catégorie
	//if(CEstBon()==false) return;
	if(LBCalendrier->Items->Strings[n]=="[...]")
	{
		ShowMessage("A Faire");
		return;
	}
	else
	{
		Calendrier=(CL_Calendrier*)LBCalendrier->Items->Objects[n];
		LabCal->Caption=Calendrier->Nom;
		if(Calendrier->Flag=='N')
		{
			ShowMessage(L_CalNonDef); //"le calendrier n'est pas complètement défini");
			return;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::CBAnClick(TObject *Sender)
{
	AnSim=AgriEnCours->DefSim->An_0+CBAn->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::ClasseLstTravail(void)
{
	int i,j;
	CL_BesTravAtelier *besI,*besJ;
	for(i=0;i<LstBesAtelier->Count;i++)
	besI=(CL_BesTravAtelier*)LstBesAtelier->Items[i];

	for(i=0;i<LstBesAtelier->Count-1;i++)
	{
		besI=(CL_BesTravAtelier*)LstBesAtelier->Items[i];
		for(j=i+1;j<LstBesAtelier->Count;j++)
		{
			besJ=(CL_BesTravAtelier*)LstBesAtelier->Items[j];
			if(besJ->Atelier->Ordre < besI->Atelier->Ordre)
			{
				LstBesAtelier->Items[j]=besI;
				LstBesAtelier->Items[i]=besJ;
				besI=besJ;
			}
		}
	}
	for(i=0;i<LstBesAtelier->Count;i++)
	besI=(CL_BesTravAtelier*)LstBesAtelier->Items[i];

}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtBnGrapheClick(TObject *Sender)
{
	bool rep;
	rep=VerifCompletude(); // besoins sont définis 101005
	if(rep==false) return;

	EtablirBornes();//decoupe annee en sous periodes
	CalculBesPeriode(CBAn->ItemIndex);//LstBesatelier pour l'année
	BtBnLegendeClick(this);//Visible
	LegendeAtelier();// ?,

	OrdreAffichage();

//    if(LstBesAtelier==NULL)        //101005
//        BtBnCalculerClick(this);
	ClasseLstTravail();
	TravGraphFrm->Show();
	TravGraphFrm->Dessiner();
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtBnCalculClick(TObject *Sender)
{
	int an;
//    if(LstBesAtelier==NULL)
	BtBnCalculerClick(this);
	an=Agri->DefSim->An_0+CBAn->ItemIndex;

	Forme01Frm->Show();
	Forme01Frm->IniGrilleTravail(LstBesAtelier,LstSousPeriodes,
			TotBesSousPer,DispoSousPer,TravNec,NbTrav,an,DtDebut);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::DefinirCoulMotif(void)
{
	int n;
	n=0;
	LesCouleurs[n++]=clRed; //1
	LesCouleurs[n++]=clBlue;
	LesCouleurs[n++]=clGreen;
	LesCouleurs[n++]=clPurple;
	LesCouleurs[n++]=clMaroon;//5
	LesCouleurs[n++]=clNavy;
	LesCouleurs[n++]=clOlive;
	LesCouleurs[n++]=clLime;
	LesCouleurs[n++]=clFuchsia;
	LesCouleurs[n++]=clTeal;//10
	CoulX=n;

	n=0;
	LesMotifs[n++]=bsSolid;
	LesMotifs[n++]=bsHorizontal;
	LesMotifs[n++]=bsVertical;
	LesMotifs[n++]=bsCross;
	LesMotifs[n++]=bsDiagCross;
	LesMotifs[n++]=bsBDiagonal;
	LesMotifs[n++]=bsFDiagonal;
	MotifX=n;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::EdNbOuvKeyPress(TObject *Sender, char &Key)
{
	if(Key>='0' && Key<='9')return;
	if(Key==VK_BACK) return;
	Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TTravCalFrm::EdNbOuvExit(TObject *Sender)
{
	NbTrav=EdNbOuv->Text.ToInt();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Ordre affichage
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::OrdreAffichage(void)
{
	CL_Atelier *atelier;
	CL_BesTravAtelier *besTravAtelier;
	int i;
	LBAtelier->Clear();
	for(i=0;i<LstBesAtelier->Count;i++)
	{
		besTravAtelier=(CL_BesTravAtelier*)LstBesAtelier->Items[i];
		atelier=besTravAtelier->Atelier;
		LBAtelier->Items->AddObject(atelier->Nom,(TObject*)besTravAtelier);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtBnOrdreClick(TObject *Sender)
{
	GBOrdre->Visible=!GBOrdre->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::LBAtelierClick(TObject *Sender)
{
	NAtelier=LBAtelier->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtClBasClick(TObject *Sender)
{
	int n=LBAtelier->ItemIndex;
	TObject *ob0,*ob1;
	AnsiString as0,as1;
	CL_BesTravAtelier *bes;
	if(n==LBAtelier->Count-1) return;

	ob0=LBAtelier->Items->Objects[n];
	ob1=LBAtelier->Items->Objects[n+1];

	LBAtelier->Items->Objects[n]=ob1;
	LBAtelier->Items->Objects[n+1]=ob0;

	as0=LBAtelier->Items->Strings[n];
	as1=LBAtelier->Items->Strings[n+1];

	LBAtelier->Items->Strings[n]=as1;
	LBAtelier->Items->Strings[n+1]=as0;

	LBAtelier->ItemIndex++;
	LBAtelier->Refresh();

	for(n=0;n<LstBesAtelier->Count;n++)
	{
		LstBesAtelier->Items[n]=LBAtelier->Items->Objects[n];
		bes=(CL_BesTravAtelier*)LstBesAtelier->Items[n];
		bes->Atelier->Ordre=n;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtClHautClick(TObject *Sender)
{
	int n;
	TObject *ob0,*ob1;
	AnsiString as0,as1;
	CL_BesTravAtelier *bes;

	n=LBAtelier->ItemIndex;
	if(n<1) return;

	ob0=LBAtelier->Items->Objects[n];
	ob1=LBAtelier->Items->Objects[n-1];

	LBAtelier->Items->Objects[n]=ob1;
	LBAtelier->Items->Objects[n-1]=ob0;

	as0=LBAtelier->Items->Strings[n];
	as1=LBAtelier->Items->Strings[n-1];

	LBAtelier->Items->Strings[n]=as1;
	LBAtelier->Items->Strings[n-1]=as0;

	LBAtelier->ItemIndex--;
	LBAtelier->Refresh();

	for(n=0;n<LstBesAtelier->Count;n++)
	{
		LstBesAtelier->Items[n]=LBAtelier->Items->Objects[n];
		bes=(CL_BesTravAtelier*)LstBesAtelier->Items[n];
		bes->Atelier->Ordre=n;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTravCalFrm::BtBnFermClasstClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TTravCalFrm::BtBnOrdreFinClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TTravCalFrm::LegendeAtelier(void)
{
	int i;
	TRect rect;
	int x1,x2,y1,y2;
	int X0,Y0;
	int Hauteur,Largeur;

	Canvas->Pen->Width=1;
	Canvas->Pen->Color=clBlack;
	Canvas->Brush->Color=clBlack;
	X0=600;Y0=20;
	Largeur=50;Hauteur=20;
//	X0=10+GB->Left;Y0=20+GB->Top;
	for(i=0;i<LstBesAtelier->Count;i++)
	{
		x1=X0;x2=x1+Largeur;
		y1=Y0+i*Hauteur;
		y2=y1+Hauteur;

//		rect=Rect(x1,y1,x2,y2);
		Canvas->Rectangle(x1,y1,x2,y2);
	}

}

//---------------------------------------------------------------------------
// total des besoins                          //030306
void __fastcall TTravCalFrm::BtBnTotalBesoinsClick(TObject *Sender)
{
	int n,r;
	if(V_Calendrier->Nbelt==0)
	{
		ShowMessage(L_PasCal); //"Aucun calendrier");
		return;
	}
	CalculTotBesoins();

	Forme01Frm->Show();
	Forme01Frm->IniGrilleStandard(L_TotBesoinsTrav, //"Total des Besoins en travail",
			N_X,V_Calendrier->Nbelt,Agri->DefSim->An_0);
	for(n=0,r=1;n<V_Calendrier->Nbelt;n++,r++)
	{
		Calendrier=V_Calendrier->Vecteur[n];
		if(Calendrier->Flag=='N') continue;
		Forme01Frm->EcrireLigne(Calendrier->Nom,Calendrier->TotBesoins);
	}

	//remetttre en ordre
	Calendrier=(CL_Calendrier*)LBCalendrier->Items->Objects[LBCalendrierItemIndex];
	LabCal->Caption=Calendrier->Nom;
//    delete LstBesAtelier;   LstBesAtelier=NULL;
}
//---------------------------------------------------------------------------
void TTravCalFrm::CalculTotBesoins(void) {
	int n, noAn, nSousPer;
	int r, c;
	CL_BesTravAtelier *besTravAtelier;
	int CBAnItemIndex;
//    CBAnItemIndex=CBAn->ItemIndex;
	for (n = 0; n < V_Calendrier->Nbelt; n++) {
		Calendrier = V_Calendrier->Vecteur[n];
		Calendrier->Flag = 'N';
		memset(Calendrier->TotBesoins, 0, sizeof(Calendrier->TotBesoins));

		if (Calendrier->V_Periode->Nbelt == 0)
			continue;

		EtablirBornes(); //decoupe année en sous periode B

		for (noAn = 0; noAn < N_X; noAn++) {
			//CBAn->ItemIndex=noAn;
			CalculBesPeriode(noAn); //LstBesAtelier pour l'année  090306
			nSousPer = LstSousPeriodes->Count;
			if (nSousPer == 0)
				continue; //??

			Calendrier->Flag = 'O';

			for (r = 0; r < LstBesAtelier->Count; r++) {
				besTravAtelier = (CL_BesTravAtelier*) LstBesAtelier->Items[r];
				for (c = 0; c < LstSousPeriodes->Count; c++)
					Calendrier->TotBesoins[noAn] +=
							besTravAtelier->besSousPeriode[c]; //!!
			}
		}
	}
	CBAn->ItemIndex = CBAnItemIndex;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TTravCalFrm::TexteChaine(void) {

	L_PasCal = T->TrouveTexte("TravCalFrm", "L_PasCal");
	L_PasPeriode = T->TrouveTexte("TravCalFrm", "L_PasPeriode");
	L_CalNonDef = T->TrouveTexte("TravCalFrm", "L_CalNonDef");
	L_TotBesoinsTrav = T->TrouveTexte("TravCalFrm", "L_TotBesoinsTrav");
	L_A_Executer = T->TrouveTexte("TravCalFrm", "L_A_Executer");
}

//---------------------------------------------------------------------------
//--------------------------------------------
void TTravCalFrm::IniCaption(void) {
	LabAn->Caption = T->LC_GBAn;
	BtBnCalculer->Caption = T->LC_RG;
	LabCalendrier->Caption = LC_LabCalendrier;
	LabCoulMotif->Caption = LC_LabCoulMotif;
	GB->Caption = LC_GB;
	BtBnGraphe->Caption = LC_BtBnGraphe;
	BtBnLegende->Caption = LC_BtBnLegende;
	GBPresentation->Caption = LC_GBPresentation;
	LabNbOuv->Caption = LC_LabNbOuv;
	BtBnOrdre->Caption = LC_BtBnOrdre;
	GBOrdre->Caption = LC_GBOrdre;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	GBResultat->Caption = T->LC_BtBnResultat;
	TravCalFrm->Caption = LC_TravCalFrm;
	BtBnCalcul->Caption = T->LC_BtBnCalcul;
	BtBnTotalBesoins->Caption = LC_TotBesoins;
}
//--------------------------------------------
void TTravCalFrm::TexteCaption(void) {
	LC_GBAn = T->TrouveCaption("CL_Trad", "LC_GBAn");
	LC_RG = T->TrouveCaption("CL_Trad", "LC_RG");
	LC_LabCalendrier = T->TrouveCaption("TravCal", "LC_LabCalendrier");
	LC_LabCoulMotif = T->TrouveCaption("TravCal", "LC_LabCoulMotif");
	LC_GB = T->TrouveCaption("TravCal", "LC_GB");
	LC_BtBnGraphe = T->TrouveCaption("TravCal", "LC_BtBnGraphe");
	LC_BtBnLegende = T->TrouveCaption("TravCal", "LC_BtBnLegende");
	LC_GBPresentation = T->TrouveCaption("TravCal", "LC_GBPresentation");
	LC_LabNbOuv = T->TrouveCaption("TravCal", "LC_LabNbOuv");
	LC_BtBnOrdre = T->TrouveCaption("TravCal", "LC_BtBnOrdre");
	LC_GBOrdre = T->TrouveCaption("TravCal", "LC_GBOrdre");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_TravCalFrm = T->TrouveCaption("TravCal", "LC_TravCalFrm");
	LC_BtBnCalcul = T->TrouveCaption("CL_Trad", "LC_BtBnCalcul");
	LC_TotBesoins = T->TrouveCaption("TravCal", "LC_TotBesoins");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TTravCalFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1480;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TTravCalFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=1480;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

