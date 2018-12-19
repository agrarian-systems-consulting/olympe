//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "LesClassesApp.h"
#include "LesVecteurs.h"
#include "LireXml.h"

#include "DebutXml.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDebutXmlFrm *DebutXmlFrm;
//---------------------------------------------------------------------------
__fastcall TDebutXmlFrm::TDebutXmlFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TDebutXmlFrm::FormCreate(TObject *Sender)
{
	CL_Categorie *cat;

	DecimalSeparator='.';
	ThousandSeparator=' ';

	V_SystemeUnite= new CL_Vecteur<CL_SystemeUnite>();
	V_Tva = new CL_Vecteur<CL_Tva>();

	V_CatProduit= new CL_Vecteur<CL_Categorie>();
	V_CatCharge= new CL_Vecteur<CL_Categorie>();
	V_CatBestiaux= new CL_Vecteur<CL_Categorie>();
	V_CatExternalite= new CL_Vecteur<CL_Categorie>();
	/*
	 cat= new CL_Categorie("Négative",EXTNEG);
	 //                cat= new CL_Categorie("Négative",0);
	 V_CatExternalite->insSans(cat);

	 cat= new CL_Categorie("Positive",EXTPOS);
	 //                cat= new CL_Categorie("Positive",1);
	 V_CatExternalite->insSans(cat);
	 */
	V_CatCulture= new CL_Vecteur<CL_Categorie>();
	V_CatAnimaux= new CL_Vecteur<CL_Categorie>();
	V_CatVivrier= new CL_Vecteur<CL_Categorie>();

	V_CatChStruct= new CL_Vecteur<CL_Categorie>();
	V_CatDepDiv= new CL_Vecteur<CL_Categorie>();
	V_CatRecDiv= new CL_Vecteur<CL_Categorie>();
	V_CatRecFam= new CL_Vecteur<CL_Categorie>();
	V_CatDepFam= new CL_Vecteur<CL_Categorie>();

	V_CatTypeZone= new CL_Vecteur<CL_Categorie>();

	V_CatIndic= new CL_Vecteur<CL_Categorie>();
	V_CatEtatSortie= new CL_Vecteur<CL_Categorie>();
	V_CatSerieComp= new CL_Vecteur<CL_Categorie>();

	V_Produit= new CL_Vecteur<CL_Item>();
	V_Charge = new CL_Vecteur<CL_Item>();
	V_Bestiaux= new CL_Vecteur<CL_Bestiaux>();
	V_Externalite= new CL_Vecteur<CL_Item>();

	V_Culture= new CL_Vecteur<CL_Atelier>();
	V_Animaux= new CL_Vecteur<CL_Atelier>();
	V_Vivrier= new CL_Vecteur<CL_Atelier>();

	V_Espece = new CL_Vecteur<CL_Espece>();
	V_Perenne= new CL_Vecteur<CL_Atelier>();

	V_ChStruct= new CL_Vecteur<CL_Item>();
	V_RecDiv= new CL_Vecteur<CL_Item>();
	V_DepDiv= new CL_Vecteur<CL_Item>();

	V_RecFam= new CL_Vecteur<CL_Item>();
	V_DepFam= new CL_Vecteur<CL_Item>();

	V_TypeZone= new CL_Vecteur<CL_Item>();

	V_CatVar= new CL_Vecteur<CL_Categorie>();
	V_Variable= new CL_Vecteur<CL_Item>();

	V_Calendrier= new CL_Vecteur<CL_Calendrier>();

	V_Agriculteur= new CL_Vecteur<CL_Agriculteur>();

	V_Ensemble= new CL_Vecteur<CL_Ensemble>();

	V_CatRepart= new CL_Vecteur<CL_Categorie>();
	V_Repart= new CL_Vecteur<CL_Repart>; //240203

	V_EtatSortie= new CL_Vecteur<CL_EtatSortie>();
	V_SerieComp= new CL_Vecteur<CL_EtatSortie>();
	V_Indicateur= new CL_Vecteur<CL_Indicateur>();

	V_Poste= new CL_Vecteur<CL_Poste>();
	V_Elt= new CL_Vecteur<CL_Elt>();

	V_CatDico= new CL_Vecteur<CL_Categorie>();
	V_Dico= new CL_Vecteur<CL_Item>();

	// tendance produits charges
	V_TendPrixProd= new CL_Vecteur<CL_Tendance>();
	V_TendPrixCharge= new CL_Vecteur<CL_Tendance>();
	V_ScenPrixProd= new CL_Vecteur<CL_Tendance>();
	V_ScenPrixCharge= new CL_Vecteur<CL_Tendance>();

	// production et consommation de charges
	V_TendQProd= new CL_Vecteur<CL_Tendance>();
	V_TendQCharge= new CL_Vecteur<CL_Tendance>();
	V_ScenQProd= new CL_Vecteur<CL_Tendance>();
	V_ScenQCharge= new CL_Vecteur<CL_Tendance>();
	V_TendQExt= new CL_Vecteur<CL_Tendance>();
	V_ScenQExt= new CL_Vecteur<CL_Tendance>();

	V_DefSim= new CL_Vecteur<CL_AgriDefSim>();

	V_Conversion= new CL_Vecteur<CL_Conversion>();

}
//---------------------------------------------------------------------------
void __fastcall TDebutXmlFrm::FormActivate(TObject *Sender)
{

//    if (!OpenDialog->Execute()) return;
//    LireXmlFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TDebutXmlFrm::BitBtn1Click(TObject *Sender)
{
	AnimateWindow(Handle,5000, AW_HIDE |AW_SLIDE | AW_VER_POSITIVE);
	AnimateWindow(Handle,5000, AW_ACTIVATE |AW_SLIDE | AW_HOR_POSITIVE);
}
//---------------------------------------------------------------------------

void __fastcall TDebutXmlFrm::BitBtn2Click(TObject *Sender)
{
	TDateTime t1,t2,delta;
	Word h,m,s,ms;
	AnsiString as;
//int n;
	EdDuree->Text="";
	if (!OpenDialog->Execute()) return;

	t1 = Now();
//    as1 = DateTimeToStr(t1);
//    DecodeTime(t1,h,m,s,ms);

	LireXmlFrm->Show();

	t2 = Now();
//    as2 = DateTimeToStr(t2);
//    DecodeTime(t2,h,m,s,ms);
	delta=t2-t1;

	DecodeTime(delta,h,m,s,ms);
	EdDuree->Text== IntToStr(s) +"  secondes  " +IntToStr(ms)+"  milliSecondes";

}
//---------------------------------------------------------------------------
/*


 Word Year, Month, Day, Hour, Min, Sec, MSec;
 TDateTime dtPresent = Now();
 DecodeDate(dtPresent, Year, Month, Day);
 Label1->Caption = AnsiString("Nous sommes aujourd'hui le ") + IntToStr(Day) + IntToStr(Month) + AnsiString(" de l'année ") + IntToStr(Year);
 DecodeTime(dtPresent, Hour, Min, Sec, MSec);
 Label2->Caption = AnsiString("Il est ") + IntToStr(Hour) + AnsiString(" heures et ")+ IntToStr(Min) + AnsiString(" minutes.");

 }
 */
