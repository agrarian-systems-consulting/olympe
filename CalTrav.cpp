//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "Forme0.h"
#include "SortieEcran.h"
#include "LBMotif.h"

#include "CalTrav.h"
#include "Graph.h"
#include "GraphTrav.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TCalTravFrm *CalTravFrm;
//
//        Calendrier de travail
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//           LES CONSTRUCTEURS DES CLASSES SPECIFIQUES
int CmpBornes(const void *a, const void *b) {
	int borne1, borne2;
	borne1 = *(int*) a;
	borne2 = *(int*) b;
	return (borne1 - borne2);
}
CL_SousPeriode::CL_SousPeriode(int borneD, int borneF,
		CL_Calendrier *calendrier) {
	int n;
	CL_Periode *periode;
	n = calendrier->V_Periode->Nbelt;
	JD = borneD;
	JF = borneF;
	LesPeriodes = new CL_Periode*[n];
	LesPcent = new float[n];
	for (int i = 0; i < n; i++)
		LesPeriodes[i] = NULL;
	NPeriode = 0;
}
CL_SousPeriode::~CL_SousPeriode() {
	delete[] LesPeriodes;
	delete[] LesPcent;
}

CL_Legende::CL_Legende(int no, char *nom, TColor couleur, int style) {
	int height = 20;
	int width = 40;
	Texte = new TStaticText(CalTravFrm->GB);
	Texte->Font->Size = 10;
	Texte->Caption = nom;

	Couleur = new TShape(CalTravFrm->GB);
	Couleur->Brush->Style = (TBrushStyle) 0;
	Couleur->Brush->Color = couleur;
	Couleur->OnMouseDown = CalTravFrm->RecCouleurMouseDown;

	Motif = new TShape(CalTravFrm->GB);
	Motif->Brush->Style = (TBrushStyle) style;
	if (style == 1)
		Motif->Brush->Color = clInfoBk;
	else
		Motif->Brush->Color = clBlack;
//    Motif->Brush->Color=clWhite;
	Motif->OnMouseDown = CalTravFrm->RecMotifMouseDown;

	Ensemble = new TShape(CalTravFrm->GB);
	Ensemble->Brush->Style = (TBrushStyle) style;
	Ensemble->Brush->Color = couleur;

	Texte->Height = height;
	Couleur->Height = height;
	Motif->Height = height;
	Ensemble->Height = height;

	Texte->Width = width * 3;
	Couleur->Width = width;
	Motif->Width = width;
	Ensemble->Width = width;

	Texte->Left = 10;
	Couleur->Left = Texte->Left + Texte->Width;
	Motif->Left = Couleur->Left + Couleur->Width;
	Ensemble->Left = Motif->Left + Motif->Width;

	Texte->Top = CalTravFrm->GB->Top + 10 + no * Couleur->Height;
	Couleur->Top = Texte->Top;
	Motif->Top = Texte->Top;
	Ensemble->Top = Texte->Top;
	if (!Couleur->Parent) {
		CalTravFrm->GB->InsertControl(Texte);
		CalTravFrm->GB->InsertControl(Couleur);
		CalTravFrm->GB->InsertControl(Motif);
		CalTravFrm->GB->InsertControl(Ensemble);

	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//               CALTRAV
__fastcall TCalTravFrm::TCalTravFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TCalTravFrm::FormActivate(TObject *Sender)
{
	int coul;
	if(EstInitialise==false)
	{
		EstInitialise=true;
		//on peut avoir créé des nouveaux calendriers
		//Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);

		coul=0;
		LesCouleurs[coul++]=clRed;//1
		LesCouleurs[coul++]=clBlue;
		LesCouleurs[coul++]=clGreen;
		LesCouleurs[coul++]=clPurple;
		LesCouleurs[coul++]=clMaroon;//5
		LesCouleurs[coul++]=clNavy;
		LesCouleurs[coul++]=clOlive;
		LesCouleurs[coul++]=clLime;
		LesCouleurs[coul++]=clFuchsia;
		LesCouleurs[coul++]=clTeal;//10
		CoulX=coul;

		Calendrier=NULL;
	}
	Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);
	return;
}
//---------------------------------------------------------------------------
void __fastcall TCalTravFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	CL_SousPeriode* sPeriode;

	if(LesBornes==NULL) return;

	delete []LesBornes;
	for(int i=0;i<LstSousPeriodes->Count;i++)
	{
		sPeriode=(CL_SousPeriode*)LstSousPeriodes->Items[i];
		delete sPeriode;
	}
	delete LstSousPeriodes;
}
//---------------------------------------------------------------------------
//LB des calendriers->choix
void __fastcall TCalTravFrm::LBClick(TObject *Sender)
{
	int n;
	n=LB->ItemIndex;
	//verif et stockage que si définitions d'élements de la catégorie
	//if(CEstBon()==false) return;
	if(LB->Items->Strings[n]=="[...]")
	{
		ShowMessage("A Faire");
		return;
	}
	else
	{
		Calendrier=(CL_Calendrier*)LB->Items->Objects[n];
		EtablirBornes();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//   decouper les périodes en sous périodes
void __fastcall TCalTravFrm::EtablirBornes(void)
{
	int n;
	CL_Vecteur<CL_Periode> *v_Periode;
	CL_Periode *periode;
	v_Periode=Calendrier->V_Periode;
	BorneX=v_Periode->Nbelt*2;
	LesBornes=new int[BorneX];

	// calcule la durée des péeiodes
	//etablit periode->J0  debut de la période par rapport au début de la période initiale
	DatePeriode(Calendrier->V_Periode);

	NBorne=0;
	for(n=0;n<v_Periode->Nbelt;n++)
	{
		periode=v_Periode->Vecteur[n];
		LesBornes[NBorne++]=periode->JD;
		LesBornes[NBorne++]=periode->JF;
	}
	// classer les bornes et retirer les doublons
	// bornes classées selon date croissante

	qsort((void *)LesBornes, NBorne, sizeof(int), CmpBornes);

//    LstBornes->Sort(CmpBornes);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	RetirerDoublon();

	// creer les sous périodes
	CreerSousPeriodes();
	//
	CorrespondancePeriodeSousPeriode();

	Imprimer();
}
//---------------------------------------------------------------------------
bool __fastcall TCalTravFrm::DatePeriode(CL_Vecteur<CL_Periode> *v_Periode)
{
	int n;
	int duree,ecart;
	Word an;
	char chaine[100];
	CL_Periode *periode,*periodeDebut;
	TDateTime dtDeb,dtFin; //,dtDebut;
	an=2001;
	for(n=0;n<v_Periode->Nbelt;n++)
	{
		periode=v_Periode->Vecteur[n];
		periode->ADeb=periode->AFin=an;
		dtDeb = EncodeDate((Word) periode->ADeb, (Word) periode->MDeb,
				(Word)periode->JDeb);
		dtFin = EncodeDate((Word) periode->AFin, (Word) periode->MFin,
				(Word)periode->JFin);
		duree=dtFin-dtDeb;
		if(duree==0)
		{
			sprintf(chaine," La période n° %d a une duree nulle",n);
			ShowMessage(chaine);
			return false;
		}

		if(duree<0)
		{
			duree+=365;
			periode->AFin++;
			periode->Duree=duree;
		}

		if(n==0)
		{
			periodeDebut=periode;
			periodeDebut->JD=0;
			DtDebut=dtDeb; //debut du calendrier
		}
		else
		{
			dtDeb = EncodeDate((Word) periode->ADeb, (Word) periode->MDeb,
					(Word)periode->JDeb);
			ecart=dtDeb-DtDebut;
			if(ecart<0)
			{
				periode->ADeb++;
				periode->AFin++;
				ecart+=365;
			}
			if(ecart >365)
			{
				sprintf(chaine," La période n° %d fait dépasser 365 jours",n);
				ShowMessage(chaine);
				return false;
			}
			periode->JD=ecart;
		}
		periode->JF=periode->JD+duree;
	}
	return true;
}
//--------------------------------------------------------------------------
void __fastcall TCalTravFrm::RetirerDoublon(void)
{
	int i,j;
	int borne,borneApres;
//CL_Borne *borne,*borneAvant;
	for(i=0;i<NBorne;i++)
	{
		borne= LesBornes[i];
		borneApres= LesBornes[i+1];
		if(borne==borneApres)
		{
			for(j=i+1;j<NBorne;j++)
			LesBornes[j]=LesBornes[j+1];
			NBorne--;
		}
	}
}
//--------------------------------------------------------------------------
void __fastcall TCalTravFrm::CreerSousPeriodes(void)
{
	int n;
	CL_SousPeriode *sPeriode;
	int borne1,borne2;
	LstSousPeriodes=new TList;
	for(n=0;n<NBorne-1;n++)
	{
		borne1=LesBornes[n];
		borne2=LesBornes[n+1];
		sPeriode=new CL_SousPeriode(borne1,borne2,Calendrier);
		LstSousPeriodes->Add(sPeriode);
	}
}
//--------------------------------------------------------------------------
void __fastcall TCalTravFrm::CorrespondancePeriodeSousPeriode(void)
{
	int i,j;
	int n;
	int jD,jF;
	int dureePeriode;
	float pcent;
	CL_Periode *periode;
	CL_SousPeriode *sPeriode;
	CL_Vecteur<CL_Periode> *v_Periode;

	v_Periode=Calendrier->V_Periode;
	for(i=0;i<v_Periode->Nbelt;i++)
	{
		periode=v_Periode->Vecteur[i];
		dureePeriode= periode->JF-periode->JD;
		jD=periode->JD;
		jF=periode->JF;
		for(j=0;j<LstSousPeriodes->Count;j++)
		{
			sPeriode=(CL_SousPeriode*)LstSousPeriodes->Items[j];
			if(sPeriode->JD >=jD && sPeriode->JF <=jF)
			{
				n=sPeriode->NPeriode;
				sPeriode->LesPeriodes[n]=periode;
				pcent=(float)(sPeriode->JF-sPeriode->JD)/(float)dureePeriode;
				sPeriode->LesPcent[n]=pcent;
				sPeriode->NPeriode++;
			}
		}
	}

}

//--------------------------------------------------------------------------
//Pour Test à court circuiter une fois mis au point
void __fastcall TCalTravFrm::Imprimer(void)
{
	int n;
	CL_Periode *periode;
	CL_Vecteur<CL_Periode> *v_Periode;
	int borne;
	CL_SousPeriode *sPeriode;
	char chaine[100];
	float pcent;
	Word Year,jDeb,mDeb,jFin,mFin;

	v_Periode=Calendrier->V_Periode;
	SortieEcranFrm->Memo1->Clear();
	SortieEcranFrm->Memo1->Lines->Add("Périodes");
	for(n=0;n<v_Periode->Nbelt;n++)
	{
		periode=v_Periode->Vecteur[n];
		sprintf(chaine,"%3d %3d   %3d %3d %4d    %3d %3d %4d   %3d %3d %3d",
				n,periode->No,
				periode->JDeb,periode->MDeb,periode->ADeb,
				periode->JFin,periode->MFin,periode->AFin,
				periode->JD,periode->JF,
				periode->Duree);
		SortieEcranFrm->Memo1->Lines->Add(chaine);
	}
	SortieEcranFrm->Memo1->Lines->Add("");

	SortieEcranFrm->Memo1->Lines->Add("Bornes");
	for(n=0;n<NBorne;n++)
	{
		borne=LesBornes[n];
		sprintf(chaine,"%3d    %3d    ",n,borne);
		SortieEcranFrm->Memo1->Lines->Add(chaine);
	}
	SortieEcranFrm->Memo1->Lines->Add("");

	SortieEcranFrm->Memo1->Lines->Add("Sous Périodes");
	for(n=0;n<LstSousPeriodes->Count;n++)
	{
		sPeriode=(CL_SousPeriode *)LstSousPeriodes->Items[n];
		DecodeDate(DtDebut+(Word)sPeriode->JD, Year, mDeb, jDeb);
		DecodeDate(DtDebut+(Word)sPeriode->JF, Year, mFin, jFin);
		sprintf(chaine,"%3d    %3d   %3d   %3d %3d  %3d %3d",
				n,sPeriode->JD,sPeriode->JF,jDeb,mDeb,jFin,mFin);
		SortieEcranFrm->Memo1->Lines->Add(chaine);
		for(int i=0;i<sPeriode->NPeriode;i++)
		{

			periode=sPeriode->LesPeriodes[i];
			pcent= sPeriode->LesPcent[i];

			sprintf(chaine, "     %3d    %3d  %6.5f",
					i,periode->No,pcent);
			SortieEcranFrm->Memo1->Lines->Add(chaine);
		}
	}
	SortieEcranFrm->Memo1->Lines->Add("");

	SortieEcranFrm->Show();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// pour test
void __fastcall TCalTravFrm::BtBnLegendeClick(TObject *Sender)
{
	int n;
	int NAtelier,AtelierX;
	CL_Legende *legende;
	LstLegende=new TList;
	LstLegende->Clear();

//    legende=new CL_Legende(1,"Blé",clRed,1);
	legende=new CL_Legende(1,"Blé",LesCouleurs[0],1);
	LstLegende->Add(legende);
	legende=new CL_Legende(2,"Orge",LesCouleurs[1],2);
	LstLegende->Add(legende);
	legende=new CL_Legende(3,"Mais",LesCouleurs[2],3);
	LstLegende->Add(legende);
}
//---------------------------------------------------------------------------

void __fastcall TCalTravFrm::RecCouleurMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int n;
	bool trouve;
	POINT p,q;
	CL_Legende *legende;
	TShape *couleur,*ensemble;
	trouve=false;
	for(n=0;n<LstLegende->Count;n++)
	{
		legende=(CL_Legende*)LstLegende->Items[n];
		if(Sender==legende->Couleur)
		{
			trouve=true;
			break;
		}
	}
	if(trouve==false) return;
	if(ColorDialog->Execute())
	{
		legende->Couleur->Brush->Color = ColorDialog->Color;
//        legende->Motif->Brush->Color = ColorDialog->Color;
		legende->Ensemble->Brush->Color = ColorDialog->Color;
	}
}

//---------------------------------------------------------------------------
void __fastcall TCalTravFrm::RecMotifMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int n;
	bool trouve;
	POINT p,q;
	TShape *couleur,*ensemble;
	trouve=false;
	for(n=0;n<LstLegende->Count;n++)
	{
		Legende=(CL_Legende*)LstLegende->Items[n];
		if(Sender==Legende->Motif)
		{
			trouve=true;
			break;
		}
	}
	if(trouve==false) return;
	LBMotifFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TCalTravFrm::DessineMotif(int n)
{
	if(n>0)n++;
	Legende->Motif->Brush->Style= (TBrushStyle)(n);
	Legende->Ensemble->Brush->Style= (TBrushStyle)(n);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TCalTravFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER",
			MB_YESNO|MB_ICONEXCLAMATION);

	if(rep==IDYES) Application->Terminate();

	else return;
}
//         APPEL au GRAPHIQUE
//---------------------------------------------------------------------------

void __fastcall TCalTravFrm::BtBnGrapheClick(TObject *Sender)
{
	if(Calendrier==NULL)
	{
		ShowMessage("Vous n'avez pas choisi de Calendrier");
		return;
	}
	GraphTravFrm->Show();
	GraphTravFrm->Dessiner();
}
//---------------------------------------------------------------------------

