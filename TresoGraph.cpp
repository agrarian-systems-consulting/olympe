//---------------------------------------------------------------------------

#include <vcl.h>
#include <values.h>
#include <Printers.hpp>

#pragma hdrstop
#include "CL_TresoMens.h"
#include "Forme01.h"

#include "AgriSaisie.h"
#include "Treso.h"

#include "TresoRes.h"
#include "TresoEnum.h"
#include "TresoRepart.h"
#include "CL_Trad.h"

#include "TresoGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ResGraph"
#pragma resource "*.dfm"
TTresoGraphFrm *TresoGraphFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTresoGraphFrm::TTresoGraphFrm(TComponent* Owner) :
		TResGraphFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::FormActivate(TObject *Sender)
{
	int n;
//int an;
//int j;
	int a,m;
	bool static debut=true;
//j=CBAn->ItemIndex;
	if(debut==true)
	{
		debut=false;
		//TypeCourbeG=HISTO;
		TypeCourbeG=COURBE;
		//131206
		for(n=0;n<12;n++)CBMois->Items->Strings[n]=LongMonthNames[n];
		CBMois->ItemIndex=0;

	}
	if(Origine==0)
	{
		Caption=AgriEnCours->NomVC();
		LeCanvas=Canvas;

		SG=TresoResFrm->SG;
		LstTresoMensG=new TList();
		LstTresoMensD=new TList();
//        an=AgriEnCours->DefSim->An_0;
		//TrouveMinMax(); cf FormResize
		Origine=1;

	}
	if(NbAnnee==1)
	{
		a=CBAn->ItemIndex; //141206
		m=CBMois->ItemIndex;
		Nmin=a*12+m;
		//Nmin=Annee*12+MDeb;
		Nmax=Nmin+12;
	}
	else
	{
		Nmin=0;Nmax=N_X*12;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::FormResize(TObject *Sender)
{
//	Beep();
//    ShowMessage("FormResize Treso");
	PCGaucheDroit->Left= TresoGraphFrm->Width-PCGaucheDroit->Width-10;
	GBBas->Left= TresoGraphFrm->Width-GBBas->Width-10;
	GBAff->Left= TresoGraphFrm->Width-GBBas->Width-10;
	LaWidth=Width-PCGaucheDroit->Width-10;
	LaHeight=Height;
	TrouveMinMax();

	Dessiner();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::TrouveMinMax(void)
{
	int nbUnite;
	int digits=0;

	EditMaxG->Text=" ";
	EditMinG->Text=" ";

	EditMaxD->Text=" ";
	EditMinD->Text=" ";
	// seulement à gauche Compléter!!!!!!
	TrouveVMinMax(LstTresoMensG,VMinG,VMaxG);

	// toujours 0 en bas
	if(VMinG>0) VMinG=0;

	digits=0;if(VMaxG<100) digits=2;
	//EditMaxG->Text=FloatToStrF((double)VMaxG,ffNumber,7,digits);
	digits=0;if(VMinG<100) digits=2;
	//EditMinG->Text=FloatToStrF((double)VMinG,ffNumber,7,digits);

	// prendre des nombres ronds
	UniteG=TrouveUnite('G');

	nbUnite=VMaxG/UniteG;
	VMaxG=(nbUnite+1) *UniteG;

	nbUnite=VMinG/UniteG;
	VMinG=(nbUnite) *UniteG;

	EditMaxG->Text=FloatToStrF((double)VMaxG,ffNumber,7,digits);
	EditMinG->Text=FloatToStrF((double)VMinG,ffNumber,7,digits);
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::TrouveVMinMax(TList *lstTresoMens,float &vMin,float &vMax)
{
	int r;
	CL_TresoMens *tresoMens;
	float tMin,tMax;
	bool uniteEstTrouvee=false;
	vMin=MAXFLOAT;
	vMax=MINFLOAT;

	lstTresoMens->Clear();
	for(r=0;r<SG->RowCount;r++)
	{
		tresoMens=(CL_TresoMens*)SG->Objects[0][r];
		if(tresoMens==NULL) continue;
		if(tresoMens->Contient==TITRECAT) continue;
		if(tresoMens->Contient==TITREFAM) continue;
		if(tresoMens->AAfficher==' ') continue;
		//unite pour quantité la première
//        if(uniteEstTrouvee==false && tresoMens->QuanVal)   //100108

		if(uniteEstTrouvee==false && tresoMens->QuanVal !=NULL)//090112
		{
			AsUniteQuantite=tresoMens->QuanVal->Item->SysUnite->UTrans;
			uniteEstTrouvee=true;
		}

		lstTresoMens->Add(tresoMens);
		tresoMens->TrouveMinMax(tMin,tMax,Nmin,Nmax);
		if(tMin<vMin) vMin=tMin;
		if(tMax>vMax) vMax=tMax;
	}
	/*
	 if(vMin>=vMax)
	 {
	 vMax+=vMin*0.001;
	 vMin-=vMax*0.001;
	 }
	 */
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::Dessiner(void)
{
	int epaisseur;
	//coordonnes de l'ecran d'affichage
	// l'ecran fait 400*276
	// cf papier quadrille

	LEcran=400;
	HEcran=276;

	XGauche=40;
//    XDroit= 370;
	XDroit= 340;

	YBas= 30;
	YHaut= 230;
	Intervalle=(XDroit-XGauche)/(Nmax-Nmin);//(N_X*12);

	LarHisto=(XDroit-XGauche)/(Nmax-Nmin+1);
	LarHisto*=0.9;
	// tout l'ecran clInfoBk
	LeCanvas->Pen->Style=psClear;
	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Brush->Style=bsSolid;
	LeCanvas->Rectangle(0,0,LaWidth,LaHeight);
	//Axe Horizontal
	LeCanvas->Brush->Color=clBlack;

	TraitHor(YBas,XGauche,XDroit,2);
	TraitHor(YHaut,XGauche,XDroit,1);

	//Axes Verticaux  Gauche
	epaisseur=1;if(LstTresoMensG->Count>0) epaisseur=2;
	TraitVer(XGauche,YBas,YHaut,epaisseur);
	//                Droite
	epaisseur=1;if(LstTresoMensD->Count>0) epaisseur=2;
	TraitVer(XDroit ,YBas,YHaut,epaisseur);//1 ou 2

	EchelleVer();
	if(NbAnnee!=1)
	AffAnnees(AgriEnCours->DefSim->An_0);
	else
	AffMois(AgriEnCours->DefSim->An_0);
	// switch etc on peut avoir courbe histo histo empilé
	// à drote à gauche

	//LesCourbes ou Histo
	Coul=0;
	Motif=0;
	if(LstTresoMensG->Count>0)
	{
		switch(TypeCourbeG)
		{
			case COURBE:
			AffLesCourbes(LstTresoMensG,VMinG,VMaxG);break;
			case HISTO:
			AffLesHisto(LstTresoMensG,VMinG,VMaxG);break;
		}
	}
	if(LstTresoMensD->Count>0)
	{
		switch(TypeCourbeD)
		{
			case COURBE:
			AffLesCourbes(LstTresoMensD,VMinD,VMaxD);break;
			case HISTO:
			AffLesHisto(LstTresoMensG,VMinD,VMaxD);break;
		}
	}

	//Légende
	Coul=0;
	LeCanvas->Brush->Color=clInfoBk;
	LegendeTreso(LstTresoMensG,XGauche);
	LegendeTreso(LstTresoMensD,LEcran/2+XGauche);
}
// attention pour la légende
// y est en coordonnees de l'ecran 0 en haut

//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::LegendeTreso(TList *lstTresoMens,float xGauche)
{
	int n;
	float y;
	float deltaY=12; //15;
	float xTrait;
	float lonTrait=40;
	AnsiString asNom;
	CL_TresoMens *tresoMens;

//float z;
	if(lstTresoMens->Count==0) return;

	LeCanvas->Font->Color=clBlack;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=7;//8;

	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =2;
	xTrait=xGauche+90;
	y=1;
	for(n=0;n<lstTresoMens->Count;n++)
	{
		LeCanvas->Pen->Color=(TColor)LesCouleurs[Coul++];
		tresoMens=(CL_TresoMens*)lstTresoMens->Items[n];
		//trait de la couleur de l'élément
		LeCanvas->MoveTo(Xde(xTrait),y+deltaY/2);
		LeCanvas->LineTo(Xde(xTrait+lonTrait),y+deltaY/2);
		asNom=AnsiString(tresoMens->Nom);
		/*
		 //nom de l'élément
		 switch(Nature)
		 {
		 case AGRI:        asNom=elt->Donne_Nom();break;
		 case COMPARAISON: asNom=lb->Items->Strings[n];break;

		 }
		 */
		LeCanvas->TextOut(Xde(xGauche),y,asNom.Trim());
		y+=deltaY;
	}

	LeCanvas->Pen->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::AffAnnees(int an0)
{
	int n;
	float x;
	float hBar=3;
	int an;
	AnsiString nomPolice;
	SetTextAlign(LeCanvas->Handle,TA_CENTER);

	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=8; //7;

	x=XGauche+(Intervalle*12)/2;
	an=an0;
	for(n=0;n<N_X;n++)
	{
		TraitVer(x,YBas,YBas-hBar,2);
		LeCanvas->TextOut(Xde(x),Yde(YBas-1),an );
		x+=Intervalle*12;
		an++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::AffMois(int an0)
{
	int n;
	float x;
	float hBar=3;
	int m;
	AnsiString nomPolice;
	SetTextAlign(LeCanvas->Handle,TA_CENTER);

	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=8; //7;

	x=XGauche-(Intervalle)/2;
	LeCanvas->TextOut(Xde(x),Yde(YBas-1),an0+CBAn->ItemIndex );

	x=XGauche+(Intervalle)/2;
	m=CBMois->ItemIndex+1;//131206
//    m=MDeb+1;
	for(n=0;n<12;n++)
	{
		TraitVer(x,YBas,YBas-hBar,2);
		LeCanvas->TextOut(Xde(x),Yde(YBas-1),m );
		x+=Intervalle;
		m++;
		if(m>12) m=1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::EchelleVer(void)
{
	AnsiString svaleur;
	AnsiString nomPolice;
	AnsiString unite;
	SetTextAlign(LeCanvas->Handle,TA_RIGHT);

	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=8; //7;
	LeCanvas->Font->Color=clBlack;

	if(LstTresoMensG->Count>0)
	{
		//Unité
		SetTextAlign(LeCanvas->Handle,TA_CENTER);
		if(TresoRepartFrm->CalculEn==QUANTITE)
		unite=AsUniteQuantite;
		else
		unite=SysMonnaie->UTrans;
		LeCanvas->Font->Size=10;
		LeCanvas->TextOut(Xde(XGauche),Yde(YHaut+10),unite);

		AxeOrdonnee('G');
	}
	if(LstTresoMensD->Count>0)
	{
		//Unite
		SetTextAlign(LeCanvas->Handle,TA_CENTER);
		//elt=(CL_Elt*)ResultatFrm->LBDroit->Items->Objects[0];
		//unite=elt->Donne_Unite();
		unite=SysMonnaie->UTrans;
		LeCanvas->Font->Size=10;
		LeCanvas->TextOut(Xde(XDroit),Yde(YHaut+10),unite);

		AxeOrdonnee('D');
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::AffLesCourbes(TList *lstTresoMens,float vMin,float vMax)
{
	int i;
	float flux[N_X*12];
	CL_TresoMens *tresoMens;
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =1.75; //2;
	Coul=0;
	for(i=0;i<lstTresoMens->Count;i++)
	{
		LeCanvas->Pen->Color=(TColor)LesCouleurs[Coul];
		LeCanvas->Brush->Color=(TColor)LesCouleurs[Coul];
		Coul++;
		if(Coul==CoulMax)Coul=0;
		tresoMens=(CL_TresoMens*)lstTresoMens->Items[i];
		tresoMens->EtablitFlux(flux);
		Courbe(flux,vMin,vMax);
	}
	LeCanvas->Pen->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::Courbe(float *valeur,float vMin,float vMax)
{
	float x,y;
	int n,p;
//float delta=1.5;
	TPoint points[N_X*12];
	x=XGauche+Intervalle/2;
	y=(valeur[Nmin]-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;
	p=0;
	points[p].x=Xde(x);
	points[p].y=Yde(y);
	p++;
	//LeCanvas->Ellipse(Xde(x-delta),Yde(y+delta),Xde(x+delta),Yde(y-delta));
	//j'ai déjà affiché le premier
	for(n=Nmin+1;n<Nmax;n++,p++)//141206
	{
		x+= Intervalle;
		y=(valeur[n]-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;

		points[p].x=Xde(x);
		points[p].y=Yde(y);
		//LeCanvas->Ellipse(Xde(x-delta),Yde(y+delta),Xde(x+delta),Yde(y-delta));
	}
	LeCanvas->Polyline(points,Nmax-Nmin-1);
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::AffLesHisto(TList *lstTresoMens,float vMin,float vMax)
{
	int i;
	float flux[N_X*12];
	CL_TresoMens *tresoMens;
	float larHisto;
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =2;
	larHisto=LarHisto/lstTresoMens->Count;
	Coul=0;
	for(i=0;i<lstTresoMens->Count;i++)
	{
		LeCanvas->Pen->Color=clBlack;
		LeCanvas->Pen->Color=(TColor)LesCouleurs[Coul];
		LeCanvas->Brush->Color=(TColor)LesCouleurs[Coul++];
		if(Coul==CoulMax) {Coul=0;Motif++;}
		LeCanvas->Brush->Style=(TBrushStyle)LesMotifs[Motif];
		if(Motif==MotifMax) Motif=0;
		tresoMens=(CL_TresoMens*)lstTresoMens->Items[i];
		tresoMens->EtablitFlux(flux);
		Histo(flux,vMin,vMax,i,larHisto);
	}
	LeCanvas->Pen->Color=clBlack;

}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::Histo(float *valeur,float vMin,float vMax,int i,float larHisto)
{
	float x,yH,yB;
	int n;
	float ecart=((XDroit-XGauche)/(N_X*12+1))*0.1;

	x=XGauche+ecart+i*larHisto;

	for(n=Nmin;n<Nmax;n++)
	{
		if(valeur[n]==0)
		{
			x+=Intervalle; //081206
			continue;
		}
		yH=(valeur[n]-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;
		yB=(0-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;
		LeCanvas->Rectangle(Xde(x),Yde(yH),Xde(x+larHisto),Yde(yB));
//	    LeCanvas->Rectangle(Xde(x),Yde(y),Xde(x+larHisto),Yde(YBas));
		x+=Intervalle;//081206
	}

}

//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	delete LstTresoMensG;
	delete LstTresoMensD;
}
//---------------------------------------------------------------------------
// Courbe ou Histo
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::SpBtCourbeGClick(TObject *Sender)
{
	TypeCourbeG=COURBE;
	Dessiner();
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::SpBtHistoGClick(TObject *Sender)
{
	TypeCourbeG=HISTO;
	Dessiner();
}
//---------------------------------------------------------------------------

void __fastcall TTresoGraphFrm::BtImpClick(TObject *Sender)
{
	float w,h;
	LeCanvas=Printer()->Canvas;
	Printer()->Orientation=poLandscape;
	Printer()->BeginDoc();
	w=LaWidth;
	h=LaHeight;
	LaWidth=Printer()->PageWidth;
	LaHeight=Printer()->PageHeight;
	Dessiner();

	//  Printer()->Canvas->TextRect(r, 200, 200, Memo1->Lines->Text);
	Printer()->EndDoc();
	// je restaure
	LaWidth=w;
	LaHeight=h;
	LeCanvas=Canvas;

}
//---------------------------------------------------------------------------
//  1 annee ou toutes=10
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::RGNbAnneeClick(TObject *Sender)
{
	//NbAnnee=1 ou 10  CF RGNbAnneeClick
	if(RGNbAnnee->ItemIndex==0)//une année
	{
		NbAnnee=1;
		CBAn->Enabled=true;
		CBMois->Enabled=true;
	}
	else //10 ans
	{
		NbAnnee=10;
		CBAn->Enabled=false;
		CBMois->Enabled=false;
	}
}
// choix année
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::CBAnClick(TObject *Sender)
{
	Annee=CBAn->ItemIndex;
}
//choix du mois
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::CBMoisClick(TObject *Sender)
{
	MDeb=CBMois->ItemIndex+1;
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::BtBnOKClick(TObject *Sender)
{
	int a,m;
	if(NbAnnee!=1) //resultats sur 120 mois
	{
		Nmin=0;Nmax=N_X*12;
	}
	else //sur 12 mois
	{
		a=CBAn->ItemIndex;
		m=CBMois->ItemIndex;
		Nmin=a*12+m;
		//Nmin=NbAnnee*12+MDeb-1;
		Nmax=Nmin+12;
	}

	FormResize(this);
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::SpBtCourbeDClick(TObject *Sender)
{
	TypeCourbeG=COURBE;
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::SpBtHistoDClick(TObject *Sender)
{
	TypeCourbeG=HISTO;
}
//---------------------------------------------------------------------------
void __fastcall TTresoGraphFrm::BtTableauClick(TObject *Sender)
{
//180512
	AnDeb=AgriEnCours->DefSim->An_0+CBAn->ItemIndex;
	AffTableau(AnDeb);
}
//---------------------------------------------------------------------------
void TTresoGraphFrm::AffTableau(int an0) //180512
		{
	int i, j;
	int mois0, mDeb;
	CL_TresoMens *tresoMens;
	float flux[N_X * 12], fluxTot[N_X * 12];
	AnsiString titre;
	AnsiString as;
	AnsiString unite;
	mois0 = CBMois->ItemIndex + 1;
	mDeb = (an0 - AgriEnCours->DefSim->An_0) * 12 + CBMois->ItemIndex;
	memset(fluxTot, 0, sizeof(fluxTot));
	Forme01Frm->Origine = 0;
	Forme01Frm->UtilisePar = "TresoGraph";
	Forme01Frm->Show();
	Forme01Frm->IniGrilleTreso("aaaa", TresoRepartFrm->CalculEn,
			LstTresoMensG->Count, an0, mois0);

	for (i = 0; i < LstTresoMensG->Count; i++) {
		tresoMens = (CL_TresoMens*) LstTresoMensG->Items[i];
		tresoMens->EtablitFlux(flux);
		if (TresoRepartFrm->CalculEn == VALEUR)
			Forme01Frm->EcrireLigneTresoValeur(tresoMens->Nom, flux, mDeb);
		else {
			if (tresoMens->Contient == UnITEM)
				unite = tresoMens->QuanVal->Item->SysUnite->UTrans;
			else
				unite = "  ";
			Forme01Frm->EcrireLigneTresoQuantite(tresoMens->Nom, unite, flux,
					mDeb);
		}
		for (j = 0; j < N_X * 12; j++)
			fluxTot[j] += flux[j];
	}
	if (TresoRepartFrm->CalculEn == VALEUR)
		Forme01Frm->EcrireLigneTresoValeur("Total", fluxTot, mDeb);
	else
		Forme01Frm->EcrireLigneTresoQuantite("Total", "", fluxTot, mDeb);

}
//---------------------------------------------------------------------------
void TTresoGraphFrm::AffTableauPlus12(void) //170512
		{
	int anMax = AgriEnCours->DefSim->An_0 + N_X;

	AnDeb++;
	if (AnDeb > anMax)
		AnDeb = anMax;
	AffTableau(AnDeb);
}
//---------------------------------------------------------------------------
void TTresoGraphFrm::AffTableauMoins12(void) {
	int anMin = AgriEnCours->DefSim->An_0;
	AnDeb--;
	if (AnDeb < anMin)
		AnDeb = anMin;
	AffTableau(AnDeb);
}
//---------------------------------------------------------------------------

//...........
//ScrollBar Axe de Gauche
//---------------------------------------------------------------------------

void __fastcall TTresoGraphFrm::ScrollBarMaxGScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos)
{
	if(ScrollCode==scLineUp) VMaxG+=UniteG;
	if(ScrollCode==scLineDown)
	{
		if(VMaxG-UniteG<=VMinG)return;
		VMaxG-=UniteG;
	}
	EditMaxG->Text=VMaxG;
	Dessiner();

}
//---------------------------------------------------------------------------

void __fastcall TTresoGraphFrm::ScrollBarMinGScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos)
{
	if(ScrollCode==scLineUp)
	{
		if( VMinG+UniteG>=VMaxG) return;
		VMinG+=UniteG;
	}
	if(ScrollCode==scLineDown) VMinG-=UniteG;

	EditMinG->Text=VMinG;
	Dessiner();

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTresoGraphFrm::IniCaption(void) {
	GBAff->Caption = LC_GBAff;
	LabAn->Caption = T->LC_GBAn;
	LabMois->Caption = LC_LabMois;
	RGNbAnnee->Caption = LC_RGNbAnnee;
	TresoGraphFrm->Caption = LC_TresoGraphFrm;
}
//--------------------------------------------
void TTresoGraphFrm::TexteCaption(void) {
	LC_GBAff = T->TrouveCaption("TresoGraph", "LC_GBAff");
	LC_GBAn = T->TrouveCaption("CL_Trad", "LC_GBAn");
	LC_LabMois = T->TrouveCaption("TresoGraph", "LC_LabMois");
	LC_RGNbAnnee = T->TrouveCaption("TresoGraph", "LC_RGNbAnnee");
	LC_TresoGraphFrm = T->TrouveCaption("TresoGraph", "LC_TresoGraphFrm");

	IniCaption();

}
//--------------------------------------------

