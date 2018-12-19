//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <stdio.h>
#include <vcl\printers.hpp>
#include <systdate.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Tableur.h"
#include "QuelExcelCSV.h"

#include "Brouillon.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFBrouillon *FBrouillon;
extern CL_Excel *EX;
//---------------------------------------------------------------------------
__fastcall TFBrouillon::TFBrouillon(TComponent* Owner) :
		TForm(Owner) {
}
//----------------------------------------------------------------------------
void __fastcall TFBrouillon::FormCreate(TObject *Sender)
{
	CurrencyString= " ";
	CurrencyFormat= 1;
	ThousandSeparator=' ';
	DecimalSeparator ='.';
	Marge1="";
	Marge2="    "; // ??
	Marge3="        ";
	posNom=7;
	posUnite=29;
	posVal=44;
	delta=10;
	//base
	size0=12;
	size1=10;
	size2=8;

//    TypeImp("Courier",size1,clBlack,'G');
//    Memo1->DefAttributes->Name= "Courier";
	Memo1->DefAttributes->Name= "FixedSys";
	Memo1->DefAttributes->Size= size1;
	Memo1->DefAttributes->Color= clBlack;

}
//---------------------------------------------------------------------------
void __fastcall TFBrouillon::FormActivate(TObject *Sender)
{
	Debut=true; //sert seulement dans Resize
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// envoi dans Memo
//--------------------------------------------------------------------------
void TFBrouillon::Demarre(void) {
	Caption = "";
	if (Global == false) {
		if (AgriEnCours != NULL)
			Caption = "Agriculteur: " + TexteCaption(AgriEnCours);
	} else {
		if (EnsembleEnCours != NULL)
			Caption = "Ensemble: " + EnsembleEnCours->Nom;
	}
	AsBlanc = "                            ";
	Memo1->Clear();
	EnTeteDate();

}

//copie de AgriSaisie
//---------------------------------------------------------------------------
AnsiString __fastcall TFBrouillon::TexteCaption(CL_Agriculteur *agri) {
	CL_Item *critere;
//static AnsiString caption;
	AnsiString caption;
	caption = agri->Nom + "  " + AnsiString(agri->NoVariante);
	for (int i = 0; i < agri->LstCritere->Count; i++) {
		critere = (CL_Item*) agri->LstCritere->Items[i];
		caption = caption + "  ";
		caption = caption + critere->Nom;
	}
	caption += "  ";
	if (agri->DefSim->PrixProd)
		caption += agri->DefSim->PrixProd->Nom + "  ";
	if (agri->DefSim->PrixCharge)
		caption += agri->DefSim->PrixCharge->Nom + "  ";
	if (agri->DefSim->QProd)
		caption += agri->DefSim->QProd->Nom + "  ";
	if (agri->DefSim->QCharge)
		caption += agri->DefSim->QCharge->Nom + "  ";
	if (agri->DefSim->QExt)
		caption += agri->DefSim->QExt->Nom;

	return caption;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
void TFBrouillon::TypeImp(char *police, int size, TColor couleur, char style) {
//return;

	Memo1->SelAttributes->Name = police;
	Memo1->SelAttributes->Size = size; //14;
	Memo1->SelAttributes->Color = couleur;
	Memo1->SelAttributes->Pitch = fpFixed;
	if (style == 'g' || style == 'G')
		Memo1->SelAttributes->Style = TFontStyles() << fsBold;
	else
		Memo1->SelAttributes->Style = TFontStyles() >> fsBold;

}
//--------------------------------------------------------------------------
void TFBrouillon::Titre1(char *titre, TColor couleur) {
//size1=14
	TypeImp("Times New Roman", size0, couleur, 'G');
//    TypeImp("Courier",size0,couleur,'G');
	AsLambda = Marge1 + titre;
	Memo1->Lines->Add(AsLambda.TrimRight());

	Memo1->SelAttributes->Style = TFontStyles() >> fsBold;
}
//--------------------------------------------------------------------------
void TFBrouillon::Titre2(char *titre, TColor couleur) {
//    TypeImp("Courier",size1,couleur,'G');
	TypeImp("Times New Roman", size1, couleur, 'G');
	AsLambda = Marge2 + titre;
	Memo1->Lines->Add(AsLambda.TrimRight());

	Memo1->SelAttributes->Style = TFontStyles() >> fsBold;
}
//--------------------------------------------------------------------------
void TFBrouillon::Titre3(char *titre, TColor couleur) {
//size1=12;
//    TypeImp("Courier",size1,couleur,'G');
	TypeImp("Times New Roman", size1, couleur, 'G');

	AsLambda = Marge3 + titre;
	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TFBrouillon::Nom(char *titre, TColor couleur) {
	AnsiString s;
	TypeImp("Courier", size2, couleur, 'G');

//    TypeImp("Times New Roman",size2,couleur,'M');
	AsLambda = Marge2 + titre;
	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TFBrouillon::An(int an0, TColor couleur) {
	int i, an, pos;
	AnsiString s;
	int posVal = 44; //42
	int delta = 10;
	TypeImp("Courier", size2, couleur, 'M');

	AsLambda =
			"                                                               ";
	for (i = 0, pos = posVal, an = an0; i < N_X; i++, an++, pos += delta) {
		s = an;
		AsLambda.Insert(AnsiString(an), pos - s.Length());
		AsLambda += AsBlanc;
	}
	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TFBrouillon::AnPluUn(int an0, TColor couleur) {
	int i, an, pos;
	AnsiString s;
	int posVal = 44;
	int delta = 10;
	TypeImp("Courier", size2, couleur, 'M');

// au moins 42 +10 de long
	AsLambda =
			"                                                               ";
	for (i = 0, pos = posVal, an = an0 - 1; i < N_X + 1;
			i++, an++, pos += delta) {
		s = an;
		AsLambda.Insert(AnsiString(an), pos - s.Length());
		AsLambda += AsBlanc;
	}
	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TFBrouillon::EnTeteDate(void) {
	AnsiString date;
	TDateTime time;
//size2=10
	TypeImp("Courier", size2, clBlack, 'M');
//    TypeImp("Times New Roman",size2,clBlack,'M');
	time = TDateTime::CurrentDateTime();
	date = time.DateTimeString();
	Memo1->Lines->Add(date);
}
//--------------------------------------------------------------------------
void TFBrouillon::Blanc(int nli, TColor couleur) {
	TypeImp("Courier", size2, couleur, 'M');
	for (int n = 0; n < nli; n++)
		Memo1->Lines->Add("");
}
//--------------------------------------------------------------------------
void TFBrouillon::Trait(void) {
	char chaine[256];
	memset(chaine, '_', LarTrait + 1);
	chaine[LarTrait] = '\0';
	Memo1->Lines->Add(chaine);
}
//--------------------------------------------------------------------------
void TFBrouillon::Trait(int larTrait) {
	char chaine[256];
	memset(chaine, '_', larTrait + 1);
	chaine[larTrait] = '\0';
	Memo1->Lines->Add(chaine);
}
//--------------------------------------------------------------------------
//
//
//
//Utilitaires
//
//
//
//--------------------------------------------------------------------------
void TFBrouillon::videAsLambda(void) {
	char blanc[200];
	int n;
	memset(blanc, ' ', sizeof(char) * 200);
	blanc[199] = 0;
	AsLambda = AnsiString(blanc);
}
//--------------------------------------------------------------------------
void TFBrouillon::placer(AnsiString ss, int pos) {
	AsLambda.Insert(ss.Trim(), pos);
}
//--------------------------------------------------------------------------
void TFBrouillon::placer(float val, int pos, int apresVirgule) {
	int lg;
	AnsiString s;
//    s=FloatToStrF((double)val,AnsiString::sffNumber,7,apresVirgule);
	s = FloatToStrF((double) val, ffNumber, 7, apresVirgule);
	lg = s.Length();

	AsLambda.Insert(s, pos - lg);
}
//-------------------------------------------------------------------
void __fastcall TFBrouillon::BtBnImprimerClick(TObject *Sender)
{
	TPrinter *imprimante=Printer();
	int i,x;
	String s;
	switch(RGOrientation->ItemIndex)
	{
		case 0:Printer()->Orientation = poPortrait; break;
		case 1:Printer()->Orientation = poLandscape;break;
	}
	s="Bonjour";
	imprimante->BeginDoc();
//    imprimante->Canvas->Font->Name="Times New Roman";
	imprimante->Canvas->Font->Name="Courier";
	imprimante->Canvas->Font->Size=8;
	imprimante->Canvas->Font->Pitch=fpFixed;
	imprimante->Canvas->Font->PixelsPerInch=550;//600;//500;
	x=imprimante->Canvas->TextHeight(s);
	for(i=0;i<Memo1->Lines->Count;i++)
	{
		s=Memo1->Lines->Strings[i];
		imprimante->Canvas->TextOut(1,i*x+1,s);
	}
	imprimante->EndDoc();
//    Memo1->Print("Olympe");
}
//---------------------------------------------------------------------------
void __fastcall TFBrouillon::BtBnEffacerClick(TObject *Sender)
{
	Memo1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFBrouillon::BtBnExcelClick(TObject *Sender)
{
	bool rep;
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;

	switch(EnCours)
	{
		case VALEUR: //Valeurs
		EX->Valeur(Agri);
		break;

		case QUANTITE://Quantités
		EX->Quantite(Agri);
		break;

		case EXTER://Externalites
		EX->Externalite(Agri);
		break;

		case ETAT://Etat sortie
		EX->Etat(Agri,EtatSortie);
		break;

		case SERIECOMP://Serie de comparaison
		EX->Comparaison(EtatSortie,LstElt,An_0);
		break;

		case FINANCE://Finances
		EX->Finance(Agri);
		break;

		case IMMO://Immo
		EX->Immo(Agri);
		break;

		case TVA://Tva
		EX->Tva(Agri);
		break;

		case CEG://Ceg
		EX->Ceg(Agri);
		break;

		case BILAN://Bilan
		EX->Bilan(Agri);
		break;

		case FAMILLE://Famille
		EX->Famille(Agri);
		break;

		default:
		ShowMessage("A faire");
		break;
	}

}
//---------------------------------------------------------------------------

