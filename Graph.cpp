//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <values.h>
#pragma hdrstop

#include "Olympe.hse"
#include "Olympedec.h"
#include "LesClassesApp.h"

#include "TVChoixElt.h"
#include "Resultat.h"
#include "Format.h"
#include "Forme01.h"

#include "Graph.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGraphiqueFrm *GraphiqueFrm;
//---------------------------------------------------------------------------
__fastcall TGraphiqueFrm::TGraphiqueFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::FormCreate(TObject *Sender)
{
	EstInitialise=false;
	PageControl1->ActivePage=TabSheet1;
	Coul=0;
	LesCouleurs[Coul++]=clRed; //1
	LesCouleurs[Coul++]=clBlue;
	LesCouleurs[Coul++]=clGreen;
	LesCouleurs[Coul++]=clPurple;
	LesCouleurs[Coul++]=clMaroon;//5
	LesCouleurs[Coul++]=clNavy;
	LesCouleurs[Coul++]=clOlive;
	LesCouleurs[Coul++]=clLime;
	LesCouleurs[Coul++]=clFuchsia;
	LesCouleurs[Coul++]=clTeal;//10
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::FormActivate(TObject *Sender)
{
	ListGraph=new TList;
	float vMin,vMax;

//    if(ResultatFrm->BtOuvrir->Tag==0)
	{
		Chart->LeftAxis->Automatic=true;
		Chart->RightAxis->Automatic=true;
		//axe gauche
		vMin=StrToFloat(Chart->MinYValue(Chart->LeftAxis));
		vMax=StrToFloat(Chart->MaxYValue(Chart->LeftAxis));
		// problème d'arrondi bug ? TeeChart
		if(vMin>=vMax)
		{
			vMax=vMax+vMin*0.001;
			vMin=vMin-vMax*0.001;
			EditMaxG->Text=vMax;
			EditMinG->Text=vMin;
		}
		else
		{
			EditMaxG->Text=Chart->MaxYValue(Chart->LeftAxis);
			EditMinG->Text=Chart->MinYValue(Chart->LeftAxis);
		}
		//axe Droit
		vMin=StrToFloat(Chart->MinYValue(Chart->RightAxis));
		vMax=StrToFloat(Chart->MaxYValue(Chart->RightAxis));
		// problème d'arrondi
		if(vMin>=vMax)
		{
			vMax=vMax+vMin*0.001;
			vMin=vMin-vMax*0.001;
			EditMaxD->Text=vMax;
			EditMinD->Text=vMin;
		}
		else
		{
			EditMaxD->Text=Chart->MaxYValue(Chart->RightAxis);
			EditMinD->Text=Chart->MinYValue(Chart->RightAxis);
		}
		ScrollBarMaxG->Position=-StrToFloat(EditMaxG->Text);
		ScrollBarMinG->Position=-StrToFloat(EditMinG->Text);
		ScrollBarMaxD->Position=-StrToFloat(EditMaxD->Text);
		ScrollBarMinD->Position=-StrToFloat(EditMinD->Text);
		Coul=0;
	}
	GraphiqueFrm->Caption = "Graphique";
	Incrementation();
	ButtonApplyClick(this);
}
//---------------------------------------------------------------------------
void TGraphiqueFrm::Demarrer(void) {
	int k, kL, kB;
	int nature;
	TChartSeries *serieVide;

	if (EstInitialise == false) {
		EstInitialise = true;
		CreeSerie();
		LstSerie = new TList;
	}
//    Chart->Text.Add("Toto");

	LstSerie->Clear();
	Effacer();
	k = ResultatFrm->LBGauche->Items->Count;
	kL = 0;
	kB = 0;
	Chart->View3D = true;
	if (ResultatFrm->LBGauche->Items->Count == 0
			|| ResultatFrm->LBDroit->Items->Count == 0)
		Chart->View3D = false;
	else if (ResultatFrm->RGNatureG->ItemIndex
			== ResultatFrm->RGNatureD->ItemIndex)
		Chart->View3D = false;

	Coul = 0;

	//Gauche
	if (ResultatFrm->LBGauche->Items->Count) {
		if (ResultatFrm->RGNatureG->ItemIndex == 0) //Line
				{
			GrapheLine(ResultatFrm->LBGauche, 'G', 0);
			kL = k;
		}
		if (ResultatFrm->RGNatureG->ItemIndex == 1) //Bar
				{
			GrapheBar(ResultatFrm->LBGauche, 'G', 0);
			kB = k;
		}
	}
	//Droit
	if (ResultatFrm->LBDroit->Items->Count) {
		if (ResultatFrm->RGNatureD->ItemIndex == 0) //Line
			GrapheLine(ResultatFrm->LBDroit, 'D', kL);
		if (ResultatFrm->RGNatureD->ItemIndex == 1)
			GrapheBar(ResultatFrm->LBDroit, 'D', kB);
	}

	if (Chart->View3D == false) {
		GraphiqueFrm->Show();
		return;
	}
	Chart->Chart3DPercent = 5;
	Chart->ApplyZOrder = true;

	for (int i = 0; i < 20; i++) {
		if (Chart->Series[i]->Active == false) {
			serieVide = Chart->Series[i];
			break;
		}
	}
	for (int i = 10; i < 20; i++) //mettre les barres en premier
			{
		if (Chart->Series[i]->Active == false)
			break;

		LstSerie->Add(Chart->Series[i]);
		Chart->SeriesList->Items[i] = serieVide;
	}
	for (int i = 0; i < 10; i++) //puis les lignes
			{
		if (Chart->Series[i]->Active == false)
			break;

		LstSerie->Add(Chart->Series[i]);
		Chart->SeriesList->Items[i] = serieVide;
	}
	for (int i = 0; i < LstSerie->Count; i++)
		Chart->SeriesList->Items[i] = LstSerie->Items[i];

	/*
	 Chart->SeriesList->Items[2]=Chart->Series[0];//serie;
	 Chart->SeriesList->Items[1]=Chart->Series[1];//serie;
	 Chart->SeriesList->Items[0]=Chart->Series[10];//Bar;
	 Chart->SeriesList->Items[10]=Chart->Series[4];//serie;
	 */
	GraphiqueFrm->Show();
}
//---------------------------------------------------------------------------
void TGraphiqueFrm::GrapheLine(TListBox *lBCourbe, char axe, int k) {
	int n;
	TColor couleur;
	TLineSeries *occurence;
	if (axe == 'G')
		Chart->LeftAxis->Visible = true;
	else
		Chart->RightAxis->Visible = true;

	for (n = 0; n < lBCourbe->Items->Count; n++, k++) {
		occurence = (TLineSeries*) Series->Objects[k];
		Elt = (CL_Elt*) lBCourbe->Items->Objects[n];
		for (int t = 0; t < N_X; t++) {
			//             abscisse  ordonnée
			occurence->AddXY(t + An_0, Elt->Valeur[t], t + An_0, clTeeColor);
		}
		if (axe == 'G') {
			occurence->VertAxis = aLeftAxis;
			occurence->Title = lBCourbe->Items->Strings[n];
		} else {
			occurence->VertAxis = aRightAxis;
			occurence->Title = "D  " + lBCourbe->Items->Strings[n];
		}
		occurence->SeriesColor = LesCouleurs[Coul++];
		if (Chart->View3D)
			occurence->LinePen->Visible = false;
		occurence->Active = true;
	}
}
//---------------------------------------------------------------------------
//Bar
void TGraphiqueFrm::GrapheBar(TListBox *lBCourbe, char axe, int k) {
	TBarSeries *occurence;
	if (axe == 'G')
		Chart->LeftAxis->Visible = true;
	else
		Chart->RightAxis->Visible = true;

	for (int n = 0; n < lBCourbe->Items->Count; n++, k++) {
		occurence = (TBarSeries*) Series->Objects[k + 10];
		Elt = (CL_Elt*) lBCourbe->Items->Objects[n];
		for (int t = 0; t < N_X; t++)
			occurence->AddXY(t + An_0, Elt->Valeur[t], t + An_0, clTeeColor);

		if (axe == 'G') {
			occurence->VertAxis = aLeftAxis;
			occurence->Title = lBCourbe->Items->Strings[n];
		} else {
			occurence->VertAxis = aRightAxis;
			occurence->Title = "D  " + lBCourbe->Items->Strings[n];
		}
		occurence->SeriesColor = LesCouleurs[Coul++];
		occurence->Active = true;

		occurence->BarWidthPercent = 60;
	}
}
//---------------------------------------------------------------------------
void TGraphiqueFrm::CreeSerie() {
	Series = new TStringList;
	Series->AddObject("Series1", (TObject*) GraphiqueFrm->Series1);
	Series->AddObject("Series2", (TObject*) GraphiqueFrm->Series2);
	Series->AddObject("Series3", (TObject*) GraphiqueFrm->Series3);
	Series->AddObject("Series4", (TObject*) GraphiqueFrm->Series4);
	Series->AddObject("Series5", (TObject*) GraphiqueFrm->Series5);
	Series->AddObject("Series6", (TObject*) GraphiqueFrm->Series6);
	Series->AddObject("Series7", (TObject*) GraphiqueFrm->Series7);
	Series->AddObject("Series8", (TObject*) GraphiqueFrm->Series8);
	Series->AddObject("Series9", (TObject*) GraphiqueFrm->Series9);
	Series->AddObject("Series10", (TObject*) GraphiqueFrm->Series10);

	Series->AddObject("Series11", (TObject*) GraphiqueFrm->Series11);
	Series->AddObject("Series12", (TObject*) GraphiqueFrm->Series12);
	Series->AddObject("Series13", (TObject*) GraphiqueFrm->Series13);
	Series->AddObject("Series14", (TObject*) GraphiqueFrm->Series14);
	Series->AddObject("Series15", (TObject*) GraphiqueFrm->Series15);
	Series->AddObject("Series16", (TObject*) GraphiqueFrm->Series16);
	Series->AddObject("Series17", (TObject*) GraphiqueFrm->Series17);
	Series->AddObject("Series18", (TObject*) GraphiqueFrm->Series18);
	Series->AddObject("Series19", (TObject*) GraphiqueFrm->Series19);
	Series->AddObject("Series20", (TObject*) GraphiqueFrm->Series20);
}
//---------------------------------------------------------------------------
void TGraphiqueFrm::Effacer(void) {
	for (int n = 0; n < 10; n++) {
		TLineSeries *occurence;
		occurence = (TLineSeries*) Series->Objects[n];
		occurence->Clear();
		occurence->LinePen->Width = 2;
		occurence->LinePen->Style = (TPenStyle) 0;
		//occurence->SeriesColor=clTeeColor;
		occurence->Active = false;
	}
	for (int n = 10; n < 20; n++) {
		TBarSeries *occurence;
		occurence = (TBarSeries*) Series->Objects[n];
		//occurence->SeriesColor=clTeeColor;
		occurence->Clear();
		occurence->Active = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::ButtonPrintClick(TObject *Sender)
{
	Chart->Gradient->Visible=false;
	try
	{
		Printer()->Orientation=poLandscape;
		Chart->Gradient->Visible=false;
		Printer()->BeginDoc();
		Chart->PrintPartial(Rect(0,0,Printer()->PageWidth,Printer()->PageHeight));
		Printer()->EndDoc();
		Chart->Gradient->Visible=true;
		ShowMessage ("Graphique imprimé avec succès");
	}
	catch(...)
	{
		ShowMessage("L'imprimante n'est pas prète.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::ButtonFormatClick(TObject *Sender)
{
	FormatFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::ButtonApplyClick(TObject *Sender)
{
	float taille;

	Chart->LeftAxis->Automatic = false;
	taille=(StrToFloat(EditMaxG->Text)-StrToFloat(EditMinG->Text))*0.05;
	Chart->LeftAxis->Maximum = StrToFloat(EditMaxG->Text)+taille;
	Chart->LeftAxis->Minimum = StrToFloat(EditMinG->Text)-taille;

	Chart->RightAxis->Automatic = false;
	taille=(StrToFloat(EditMaxD->Text)-StrToFloat(EditMinD->Text))*0.05;
	Chart->RightAxis->Maximum = StrToFloat(EditMaxD->Text)+taille;
	Chart->RightAxis->Minimum = StrToFloat(EditMinD->Text)-taille;

}
//---------------------------------------------------------------------------
void TGraphiqueFrm::erreur(void) {
	ShowMessage("Valeurs des échelles non respectées.");
}
//---------------------------------------------------------------------------
//Agrandir
void __fastcall TGraphiqueFrm::ButtonZoomClick(TObject *Sender)
{
	GraphiqueFrm->WindowState=wsMaximized;
	Chart->Height=GraphiqueFrm->Height-30;
	Chart->Width=GraphiqueFrm->Width-15;
}
//---------------------------------------------------------------------------
//Reduire
void __fastcall TGraphiqueFrm::ButtonZoom2Click(TObject *Sender)
{
	GraphiqueFrm->WindowState=wsNormal;
	Chart->Height=GraphiqueFrm->Height-30;
	Chart->Width=GraphiqueFrm->Width-118;
}
//---------------------------------------------------------------------------
//Histo/Trait
void __fastcall TGraphiqueFrm::SpeedButtonHistoClick(TObject *Sender)
{
	GrapheBar(ResultatFrm->LBGauche,'G',0); //A VOIR
	FormActivate(this);
//    GrapheLine(ResultatFrm->LBCourbe);
//    GrapheLine(ResultatFrm->LBCourbe,false);
}
//---------------------------------------------------------------------------
//Histo/Trait
void __fastcall TGraphiqueFrm::SpeedButtonTraitClick(TObject *Sender)
{
	GrapheLine(ResultatFrm->LBGauche,'G',0); // A VOIR
//    GrapheLine(ResultatFrm->LBCourbe,true);
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	TVChoixEltFrm->Visible=true;
//    Effacer();
}
//---------------------------------------------------------------------------

//Axe de Gauche
void __fastcall TGraphiqueFrm::ScrollBarMaxGChange(TObject *Sender)
{
	float vMax=-ScrollBarMaxG->Position;
	if(vMax<=Chart->LeftAxis->Minimum) return;
	else
	{
		Chart->LeftAxis->Automatic = false;
		EditMaxG->Text=-ScrollBarMaxG->Position;
		Chart->LeftAxis->Maximum = StrToFloat(EditMaxG->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall TGraphiqueFrm::ScrollBarMinGChange(TObject *Sender)
{
	float vMin=-ScrollBarMinG->Position;
	if(vMin >=Chart->LeftAxis->Maximum) return;
	else
	{
		Chart->LeftAxis->Automatic = false;
		EditMinG->Text=-ScrollBarMinG->Position;
		Chart->LeftAxis->Minimum = StrToFloat(EditMinG->Text);
	}
}
//---------------------------------------------------------------------------
//Axe de Droite
void __fastcall TGraphiqueFrm::ScrollBarMaxDChange(TObject *Sender)
{
	float vMax=-ScrollBarMaxD->Position;
	if(vMax<=Chart->RightAxis->Minimum) return;
	else
	{
		Chart->RightAxis->Automatic = false;
		EditMaxD->Text=-ScrollBarMaxD->Position;
		Chart->RightAxis->Maximum = StrToFloat(EditMaxD->Text);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::ScrollBarMinDChange(TObject *Sender)
{
	float vMin=-ScrollBarMinD->Position;
	if(vMin >=Chart->RightAxis->Maximum) return;
	else
	{
		Chart->RightAxis->Automatic = false;
		EditMinD->Text=-ScrollBarMinD->Position;
		Chart->RightAxis->Minimum = StrToFloat(EditMinD->Text);
	}
}
//---------------------------------------------------------------------------
void TGraphiqueFrm::Incrementation() {
	int valeurG, valeurD, i, j;
	float vMax, vMin;

	i = 0;
	j = 0;
	vMax = EditMaxG->Text.ToDouble();
	vMin = EditMinG->Text.ToDouble();
	valeurG = (vMax - vMin) * 0.05;
	//...
	if (valeurG == 0)
		valeurG = 10;

	vMax = EditMaxD->Text.ToDouble();
	vMin = EditMinD->Text.ToDouble();
	valeurD = (vMax - vMin) * 0.05;
//    valeurG=(EditMaxG->Text-EditMinG->Text)*0.05;
//    valeurD=(EditMaxD->Text-EditMinD->Text)*0.05;

	while (valeurG > 10) {
		valeurG = valeurG / 10;
		i++;
	}
	while (valeurD > 10) {
		valeurD = valeurD / 10;
		j++;
	}
	for (int t = 0; t < i; t++)
		valeurG = valeurG * 10;
	for (int t = 0; t < j; t++)
		valeurD = valeurD * 10;

	EditIncG->Text = valeurG;
	Chart->LeftAxis->Increment = valeurG;
	EditIncD->Text = valeurD;
	Chart->RightAxis->Increment = valeurD;

	if (valeurD == 0)
		TabSheet2->TabVisible = false;
	else
		TabSheet2->TabVisible = true;
	EditIncDChange(this);
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::EditIncDChange(TObject *Sender)
{
	if(EditIncG->Text!="")
	{
		ScrollBarMaxG->SmallChange=StrToFloat(EditIncG->Text);
		ScrollBarMinG->SmallChange=StrToFloat(EditIncG->Text);
	}
	else
	EditIncG->Text=0;

	if(EditIncD->Text!="")
	{
		ScrollBarMaxD->SmallChange=StrToFloat(EditIncD->Text);
		ScrollBarMinD->SmallChange=StrToFloat(EditIncD->Text);
	}
	else
	EditIncD->Text=0;
}
//---------------------------------------------------------------------------

void __fastcall TGraphiqueFrm::CheckBoxSupClick(TObject *Sender)
{
	/* TChartShape *ligneHaut;

	 ligneHaut->Style=chasHorizLine;
	 ligneHaut->Y0=Chart->LeftAxis->CalcYPosValue(Edit->Text.ToDouble()));
	 ligneHaut->Y1=Chart->LeftAxis->CalcYPosValue(Edit->Text.ToDouble()));

	 */

	if (CheckBoxSup->Checked==true && EditSup->Text!="")
	{
		for(int an=0;an<N_X;an++)
		{
			Series21->Add(StrToFloat(EditSup->Text),an,clRed);
			Series21->Active=true;
		}
	}
	else
	{
		Series21->Clear();
		Series21->Active=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::CheckBoxInfClick(TObject *Sender)
{
	if (CheckBoxInf->Checked==true && EditInf->Text!="")
	{
		for(int an=0;an<N_X;an++)
		{
			Series22->Add(StrToFloat(EditInf->Text),an,clRed);
			Series22->Active=true;
		}
	}
	else
	{
		Series22->Clear();
		Series22->Active=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::ButtonSaveClick(TObject *Sender)
{
	CL_Graphique *graph;
	CL_Courbe *courbe;
	FILE *ficGraph;
	graph=new CL_Graphique;
	TLineSeries *occurence;

	graph->NbAn=N_X;
	graph->NbrSeries=ResultatFrm->LBGauche->Items->Count;

	for(int t=0;t<graph->NbrSeries;t++)
	{
		courbe=new CL_Courbe;
		occurence=(TLineSeries*)Series->Objects[t];
		courbe->Couleur=occurence->SeriesColor;
		courbe->Epaisseur=occurence->LinePen->Width;
		courbe->Trait=occurence->LinePen->Style;
//        courbe->AxeD=ResultatFrm->LBGauche->Checked[t];
		ListGraph->Add(courbe);
	}

	graph->MaxG= StrToFloat(EditMaxG->Text);
	graph->MinG= StrToFloat(EditMinG->Text);
	graph->MaxD= StrToFloat(EditMaxD->Text);
	graph->MinD= StrToFloat(EditMinD->Text);
	graph->TitreAbs= Chart->BottomAxis->Title->Caption;
	graph->TitreOrd= Chart->LeftAxis->Title->Caption;
	graph->TitreGraph= Chart->Title->Text->Text;
	graph->ClFond= Chart->Gradient->EndColor;

	//si courbe TypeGraph=true; si bar TypeGraph=false
	if (Series1->Active) graph->TypeGraph=true;
	else graph->TypeGraph=false;

	if(CheckBoxSup->Checked) graph->BornSup=StrToFloat(EditSup->Text);
	else graph->BornSup=MAXFLOAT;
	if(CheckBoxInf->Checked) graph->BornInf=StrToFloat(EditInf->Text);
	else graph->BornInf=MAXFLOAT;

	if (FormatFrm->CheckBox3D->Checked) graph->TD=true;
	else graph->TD=false;

	if(SaveDialog->Execute())
	{
		ficGraph=fopen(SaveDialog->FileName.c_str(),"wb");

		fwrite(&graph->NbrSeries, sizeof(int),1,ficGraph);
		fwrite(&graph->NbAn, sizeof(int),1,ficGraph);
		fwrite(&graph->MaxG, sizeof(int),1,ficGraph);
		fwrite(&graph->MaxD, sizeof(int),1,ficGraph);
		fwrite(&graph->MinG, sizeof(int),1,ficGraph);
		fwrite(&graph->MinD, sizeof(int),1,ficGraph);
		fwrite(&graph->TypeGraph, sizeof(bool),1,ficGraph);
		fwrite(&graph->BornSup, sizeof(int),1,ficGraph);
		fwrite(&graph->BornInf, sizeof(int),1,ficGraph);
		fwrite(&graph->ClFond, sizeof(int),1,ficGraph);
		fwrite(&graph->TD, sizeof(bool),1,ficGraph);

		//les titres : général abscisse ordonnées
		int l=graph->TitreGraph.Length();
		fwrite(&l,sizeof(int),1,ficGraph);
		fwrite(graph->TitreGraph.c_str(),sizeof(char)*(l+1),1,ficGraph);

		l=graph->TitreAbs.Length();
		fwrite(&l,sizeof(int),1,ficGraph);
		fwrite(graph->TitreAbs.c_str(),sizeof(char)*(l+1),1,ficGraph);

		l=graph->TitreOrd.Length();
		fwrite(&l,sizeof(int),1,ficGraph);
		fwrite(graph->TitreOrd.c_str(),sizeof(char),(l+1),ficGraph);

		CL_Elt *elt;

		for(int t=0;t<graph->NbrSeries;t++)
		{
			Elt=(CL_Elt*)ResultatFrm->LBGauche->Items->Objects[t];
			courbe=(CL_Courbe*)ListGraph->Items[t];
			fwrite(&Elt->NoFamille, sizeof(int),1,ficGraph);
			fwrite(&Elt->NoCategorie, sizeof(int),1,ficGraph);
			fwrite(&Elt->NoItem, sizeof(int),1,ficGraph);
			fwrite(&courbe->Couleur, sizeof(int),1,ficGraph);
			fwrite(&courbe->Epaisseur, sizeof(int),1,ficGraph);
			fwrite(&courbe->Trait, sizeof(int),1,ficGraph);
			fwrite(&courbe->AxeD, sizeof(bool),1,ficGraph);
		}
		fclose(ficGraph);
		ShowMessage("Fichier enregistré avec succès.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGraphiqueFrm::EdKeyPress(TObject *Sender, char &Key)
{
	if (Key >='0' && Key <='9') return;
	else if(Key==VK_BACK) return;
	Key=0;

}
//---------------------------------------------------------------------------

void __fastcall TGraphiqueFrm::BtTableauClick(TObject *Sender)
{
	int i,nbElt;
	AnsiString titre;
	AnsiString as;
	CL_Elt *elt;
	nbElt=ResultatFrm->LBGauche->Items->Count
	+ResultatFrm->LBDroit->Items->Count;
	titre=Chart->Title->Text->Text;

	Forme01Frm->Origine=0;
	Forme01Frm->UtilisePar="Graph";
	Forme01Frm->Show();
	// An_0 à voir
	Forme01Frm->IniGrilleStandard(titre,N_X,nbElt,An_0);
	for(i=0;i<ResultatFrm->LBGauche->Items->Count;i++)
	{
		elt=(CL_Elt*)ResultatFrm->LBGauche->Items->Objects[i];
		as= ResultatFrm->LBGauche->Items->Strings[i];
		Forme01Frm->EcrireLigne(as,elt->Valeur);
	}
	for(i=0;i<ResultatFrm->LBDroit->Items->Count;i++)
	{
		elt=(CL_Elt*)ResultatFrm->LBDroit->Items->Objects[i];
		as= ResultatFrm->LBDroit->Items->Strings[i];
		Forme01Frm->EcrireLigne(as,elt->Valeur);
	}
}
//---------------------------------------------------------------------------

