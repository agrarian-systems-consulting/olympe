//---------------------------------------------------------------------------
#include <vcl.h>
#include <grids.hpp>
#pragma hdrstop
#include "AgriSaisie.h"
#include "Main.h"
#include "Forme0.h"
#include "AgriSaisieEnum.h"
#include "CL_MvtAnnee.h"       //010702
#include "CL_Trad.h"

#include "MvtAni.h"

#include "TVChoix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVChoixFrm *TVChoixFrm;
extern CL_Trad *T;

/*
 TVChoix
 TVChoixDico
 TVChoixElt
 LBChoix
 LBChoixMC
 LBChoixMCInd
 */
// pour remplir colonne de gauche
//---------------------------------------------------------------------------
__fastcall TTVChoixFrm::TTVChoixFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::FormActivate(TObject *Sender)
{
	Left= AgriSaisieFrm->Left+AgriSaisieFrm->Width-Width;
	Top= AgriSaisieFrm->Top+20;

	LaGrille= AgriSaisieFrm->LaGrille;
	Memo= AgriSaisieFrm->Memo;
//    Top=      LaGrille->Top+110;
	RGModifiable=AgriSaisieFrm->RGModifiable;

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClick(TObject *Sender)
{
//	if(AgriSaisieFrm->RGModifiable->ItemIndex==0)return;
	if(RGModifiable->ItemIndex==0)return;

	switch(LaGrille->Tag)
	{
		case GAssol:
		case GAni: TVDblClickAssol(); break; //animaux

		case GPerenne: TVDblClickVerger(); break;//verger
		case GVivrier: TVDblClickVivrier();break;//verger vivrier
		//       case  GBestiaux:  TVDblClickBestiaux(); break;//animaux
		case GVariable: TVDblClickVariable(); break;//animaux

		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam: TVDblClickFormule();
		Memo->Clear();//110203
		break;//variable pour formule

		case GCreance:
		case GDette:
		TVDblClickCreanceDette();break;
		case GStock:
		TVDblClickStockIni();break;
		case GPolStock:
		TVDblClickPolStock();break;
		default:ShowMessage("TVDblClick Oubli");break;
	}

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickAssol(void)
{
	CL_Valeur *valeur;
	TTreeNode *elt;
	CL_Atelier *atelier;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int rep;
	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		TVChoixFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		if(LaGrille->Tag== GAssol) MainForm->NouvelleDefinition(CULTURE);
		else MainForm->NouvelleDefinition(ANIMAUX);
		return;
	}

//	if(elt->Level==0)	return;
	if(elt->Count!=0) return;//160103

	atelier=(CL_Atelier*)elt->Data;
	if(atelier==NULL) return;

	valeur=(CL_Valeur*)LaGrille->Objects[0][r];

	if(valeur==NULL)
	{
		valeur=new CL_Valeur();
		valeur->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)valeur;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(valeur->Flag!='N')valeur->Flag='M';

	valeur->NoAtelier=atelier->No;
	valeur->Atelier =atelier;
	LaGrille->Cells[2][r]=atelier->Nom;
	LaGrille->Cells[3][r]=atelier->Categorie->Nom;

	Forme00Frm->AjouterRow();

	LaGrille->Row++;
	LaGrille->Col=2;

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickVariable(void)
{
	CL_Valeur *valeur;
	TTreeNode *elt;
	CL_Item *variable;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int rep;
	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		TVChoixFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		if(LaGrille->Tag== GAssol) MainForm->NouvelleDefinition(CULTURE);
		else MainForm->NouvelleDefinition(ANIMAUX);
		return;
	}

	if(elt->Count!=0) return; //160103

	variable=(CL_Item*)elt->Data;
	if(variable==NULL) return;

	valeur=(CL_Valeur*)LaGrille->Objects[0][r];

	if(valeur==NULL)
	{
		valeur=new CL_Valeur();
		valeur->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)valeur;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(valeur->Flag!='N')valeur->Flag='M';

	valeur->NoItem=variable->No;
	valeur->Item =variable;
	LaGrille->Cells[2][r]=variable->Nom;
	LaGrille->Cells[3][r]=variable->Categorie->Nom;

	Forme00Frm->AjouterRow();

	LaGrille->Row++;
	LaGrille->Col=2;

}

//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickVerger(void)
{
	int rep;
	CL_Verger *verger;
	TTreeNode *elt;
	CL_Atelier *atelier;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;
	if(elt->Text=="[...]")
	{
		TVChoixFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		MainForm->NouvelleDefinition(PERENNE);
		return;
	}

	if(elt->Count!=0) return; //160103

	atelier=(CL_Atelier*)elt->Data;
	if(atelier==NULL) return;

	verger=(CL_Verger*)LaGrille->Objects[0][r];

	if(verger==NULL)
	{
		verger=new CL_Verger();
		verger->Flag='N';
		verger->Espece=atelier->Espece;
		verger->NoEspece=atelier->NoEspece;

		LaGrille->Objects[0][r]=(TObject*)verger;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(verger->Flag!='N')verger->Flag='M';

	verger->NoAtelier=atelier->No;
	verger->Atelier =atelier;
	LaGrille->Cells[2][r]=atelier->Nom;
	LaGrille->Cells[3][r]=atelier->Espece->Nom;

	Forme00Frm->AjouterRow();
	LaGrille->Row++;
	LaGrille->Col=2;
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickVivrier(void)
{
	int rep;
	CL_Verger *verger;
	TTreeNode *elt;
	CL_Atelier *atelier;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;
	if(elt->Text=="[...]")
	{
		TVChoixFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		MainForm->NouvelleDefinition(VIVRIER);
		return;
	}

	if(elt->Count!=0) return; //160103

	atelier=(CL_Atelier*)elt->Data;
	if(atelier==NULL) return;

	verger=(CL_Verger*)LaGrille->Objects[0][r];

	if(verger==NULL)
	{
		verger=new CL_Verger();
		verger->Flag='N';

		LaGrille->Objects[0][r]=(TObject*)verger;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(verger->Flag!='N')verger->Flag='M';

	verger->NoAtelier=atelier->No;
	verger->Atelier =atelier;
	LaGrille->Cells[2][r]=atelier->Nom;
	LaGrille->Cells[3][r]=atelier->Categorie->Nom;

	Forme00Frm->AjouterRow();
	LaGrille->Row++;
	LaGrille->Col=2;

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickFormule(void)
{
	TTreeNode *elt;
	CL_Item *item;
	CL_Formule *formule;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int rep;

	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		TVChoixFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		switch(LaGrille->Tag)
		{
			case GProduit: MainForm->NouvelleDefinition( PRODUIT ); break;
			case GCharge: MainForm->NouvelleDefinition( CHARGE ); break;
			case GChStruct: MainForm->NouvelleDefinition( CHSTRUCT ); break;
			case GRecDiv: MainForm->NouvelleDefinition( RECDIV ); break;
			case GDepDiv: MainForm->NouvelleDefinition( DEPDIV ); break;
			case GRecFam: MainForm->NouvelleDefinition( RECFAM ); break;
			case GDepFam: MainForm->NouvelleDefinition( DEPFAM ); break;

			default: ShowMessage("Oubli TVDblClickFormule");
		}
		return;
	}

	if(elt->Count!=0) return; //160103

	item=(CL_Item*)elt->Data;
	if(item==NULL) return;

	formule=(CL_Formule*)LaGrille->Objects[0][r];

	if(formule==NULL)
	{
		formule=new CL_Formule();
		formule->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)formule;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		if(formule->Origine=='C')
		MessageBox(Handle,"Calculé"," NON MODIFIABLE",MB_OK|MB_ICONSTOP);
		else
		{
			rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
			if(rep==ID_NO) return;
		}
	}

	if(formule->Flag!='N')formule->Flag='M';

	formule->No =item->No;
	formule->Item =item;

	switch(LaGrille->Tag)
	{
		//case GExtNeg:
		//case GExtPos:MainForm->ExternaliteClick(this);break;
		case GProduit: formule->NoFamille=PRODUIT; break;
		case GCharge: formule->NoFamille=CHARGE; break;
		case GChStruct:formule->NoFamille=CHSTRUCT;break;
		case GDepDiv: formule->NoFamille=DEPDIV; break;
		case GRecDiv: formule->NoFamille=RECDIV; break;
		case GDepFam: formule->NoFamille=DEPFAM; break;
		case GRecFam: formule->NoFamille=RECFAM; break;
		default: ShowMessage("Oubli TVDblClickFormule");
	}

	LaGrille->Cells[2][r]=formule->Item->Nom;
	LaGrille->Cells[3][r]=formule->Item->Categorie->Nom;

	Forme00Frm->AjouterRow();
	LaGrille->Row++;
	LaGrille->Col=2;
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickCreanceDette(void)
{
	CL_EnCours *enCours;
	TTreeNode *elt;
	CL_Item *item;
	AnsiString as;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int rep;
	if(c!=2) return;

	elt=TV->Selected;

	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		//oblige a clicker et donc à mettre à jour la TV
		TVChoixFrm->Visible=false;
		as=(char*)elt->Data;
		if (as=="Produits") MainForm->NouvelleDefinition(PRODUIT);
		else if(as=="RecDiv") MainForm->NouvelleDefinition(RECDIV);

		else if(as=="Charges") MainForm->NouvelleDefinition(CHARGE);
		else if(as=="ChStruct") MainForm->NouvelleDefinition(CHSTRUCT);
		else if(as=="DepDiv") MainForm->NouvelleDefinition(DEPDIV);

		else ShowMessage("TVDblClickStock Oubli");

		return;
	}

	if(elt->Level!=2)return; //020604
	//	if(elt->Level==0)	return;
	if(elt->Count!=0) return;//160103
	item=(CL_Item*)elt->Data;
	if(item==NULL) return;

	enCours=(CL_EnCours*)LaGrille->Objects[0][r];

	if(enCours==NULL)
	{
		enCours=new CL_EnCours();
		enCours->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)enCours;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(enCours->Flag!='N')enCours->Flag='M';

	enCours->Item=item;
	enCours->NoItem=item->No;
	enCours->NoFamille=trouveFamille(item);
	LaGrille->Cells[2][r]=item->Nom;
	Forme00Frm->AjouterRow();
	LaGrille->Row++;
	LaGrille->Col=2;

}
//---------------------------------------------------------------------------
int __fastcall TTVChoixFrm:: trouveFamille(CL_Item *item)
{
	int n;
	CL_Vecteur<CL_Categorie> *vCat;
	CL_Categorie *cat;
	//A Ameliorer
	vCat=V_CatProduit;
	for(n=0;n<vCat->Nbelt;n++)
	{
		cat=vCat->Vecteur[n];
		if(item->Categorie==cat) return PRODUIT;
	}

	vCat=V_CatCharge;
	for(n=0;n<vCat->Nbelt;n++)
	{
		cat=vCat->Vecteur[n];
		if(item->Categorie==cat) return CHARGE;
	}

	vCat=V_CatChStruct;
	for(n=0;n<vCat->Nbelt;n++)
	{
		cat=vCat->Vecteur[n];
		if(item->Categorie==cat) return CHSTRUCT;
	}

	vCat=V_CatDepDiv;
	for(n=0;n<vCat->Nbelt;n++)
	{
		cat=vCat->Vecteur[n];
		if(item->Categorie==cat) return DEPDIV;
	}

	vCat=V_CatRecDiv;
	for(n=0;n<vCat->Nbelt;n++)
	{
		cat=vCat->Vecteur[n];
		if(item->Categorie==cat) return RECDIV;
	}
	ShowMessage("Pb possible dans TTVChoixFrm:: trouveFamille");
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickStockIni(void)
{
	CL_StockIni *stock;
	TTreeNode *elt;
	CL_Item *item;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int rep;
	int ligneProduit;
	if(c!=2) return;
	ligneProduit=r%2;
	if(ligneProduit==0)
	{
		ShowMessage("Ligne de Prix de Revient !!!");
		return;
	}
	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		//oblige a clicker et donc à mettre à jour la TV
		TVChoixFrm->Visible=false;
		MainForm->NouvelleDefinition(PRODUIT);
		return;
	}

	if(elt->Count!=0) return; //160103

	item=(CL_Item*)elt->Data;
	if(item==NULL) return;

	stock=(CL_StockIni*)LaGrille->Objects[0][r];

	if(stock==NULL)
	{
		stock=new CL_StockIni();
		stock->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)stock;
		LaGrille->Cells[0][r]=(r+1)/2;
		LaGrille->RowCount+=2;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(stock->Flag!='N')stock->Flag='M';
	stock->Item=item;
	stock->NoItem=item->No;
	LaGrille->Cells[2][r]=item->Nom;
	LaGrille->Cells[2][r+1]="Prix revient";
//    LaGrille->RowCount+=2;
//    Forme00Frm->AjouterRow();

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixFrm::TVDblClickPolStock(void)
{
	CL_PolStock *polStock;
	TTreeNode *elt;
	CL_Item *item;
	int r=LaGrille->Row;
//int c=LaGrille->Col;
	int rep;
	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		//oblige a clicker et donc à mettre à jour la TV
		TVChoixFrm->Visible=false;
		MainForm->NouvelleDefinition(PRODUIT);
		return;
	}

//	if(elt->Level==0)	return;
	if(elt->Count!=0) return;//160103

	item=(CL_Item*)elt->Data;
	if(item==NULL) return;

	polStock=(CL_PolStock*)LaGrille->Objects[0][r];

	if(polStock==NULL)
	{
		polStock=new CL_PolStock();
//        polStock->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)polStock;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

//    if(polStock->Flag!='N')polStock->Flag='M';
	polStock->MaZ();
	polStock->Item=item;
	polStock->No=item->No;
	polStock->AffRow(LaGrille,r);
	AgriSaisieFrm->LabelModifie->Visible=true;
	Forme00Frm->AjouterRow();

}
//--------------------------------------------
void TTVChoixFrm::IniCaption(void) {
	TVChoixFrm->Caption = LC_TVChoixFrm;
}
//--------------------------------------------
void TTVChoixFrm::TexteCaption(void) {
	LC_TVChoixFrm = T->TrouveCaption("TVChoix", "LC_TVChoixFrm");

	IniCaption();

}
//--------------------------------------------

