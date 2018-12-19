//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "CL_Trad.h"

#include "Forme0.h"
#include "CopierDans.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCopierDansFrm *CopierDansFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TCopierDansFrm::TCopierDansFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TCopierDansFrm::EntrerNom(CL_Atelier *atelier)
{
	Retour=false;
	Atelier=atelier;
	Caption=AnsiString(" Copier  ")+atelier->Nom;
	EdNom->Text=atelier->Nom;
	Forme0Frm->CreeCLBCat(ChLB,V_Categorie);
	RGCat->ItemIndex=0;
	ChLB->Visible=false;
	ShowModal();
//    Show();
}
//---------------------------------------------------------------------------
void __fastcall TCopierDansFrm::BtAnnulerClick(TObject *Sender)
{
	Close();
	Retour=false;
	return;
}
//---------------------------------------------------------------------------
void __fastcall TCopierDansFrm::BtOkClick(TObject *Sender)
{
	Close();
	Retour=true;
	return;
}
//---------------------------------------------------------------------------
void __fastcall TCopierDansFrm::RGCatClick(TObject *Sender)
{
	if(RGCat->ItemIndex==0)ChLB->Visible=false;
	else if(RGCat->ItemIndex==1)ChLB->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TCopierDansFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int i;
	CL_Atelier *atelier;
	CL_Categorie *cat;
	if(Retour==true) //on a dit ok je verifie donc
	{
		if(VerifNom()==false) CanClose=false;
		// si c'est bon je copie
		// copie dans la catégorie
		if(RGCat->ItemIndex==0)
		{
			atelier=new CL_Atelier(Atelier);
			atelier->Nom=NewNom;
			atelier->Categorie=Atelier->Categorie; //inutile cf constructeur
			V_Atelier->ins(atelier);
		}
		//copie dans d'autres catégories
		else
		{
			for(i=0;i<ChLB->Items->Count;i++)
			{
				if(ChLB->Checked[i]==false) continue;
				cat=(CL_Categorie*)ChLB->Items->Objects[i];
				atelier=new CL_Atelier(Atelier);
				atelier->Nom=NewNom;
				atelier->Categorie=cat;
				atelier->NoCategorie=cat->No;
				V_Atelier->ins(atelier);

			}
		}
	}
	return;
}
//---------------------------------------------------------------------------
bool __fastcall TCopierDansFrm::VerifNom(void)
{
	int i;
	char buf[100];
	CL_Categorie *cat;
	NewNom=EdNom->Text.Trim();

	// le new nom existe et contient seult des caractères corrects

	if(NewNom.Length()==0 )
	{
		MessageBox(Application->Handle,NewNom.c_str(),"Le nom est vide",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(isalpha(NewNom[1])==false)
	{
		MessageBox(Application->Handle,NewNom.c_str(),"Doit commencer par caractère alpha",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	for(int n=1;n<NewNom.Length();n++)
	{
		if(ES->isalnumA(NewNom[n])>0)continue;
		if(NewNom[n]==' ') continue;

		sprintf(buf,"  %c Est un Caractère Invalide",NewNom[n]);
		MessageBox(Application->Handle,NewNom.c_str(),buf,MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	//ce nom n'est pas déjà utilisé
	if(RGCat->ItemIndex==0)
	return SansDouble(NewNom,Atelier->Categorie);
	else
	{
		for(i=0;i<ChLB->Items->Count;i++)
		{
			if(ChLB->Checked[i]==false) continue;
			cat=(CL_Categorie*)ChLB->Items->Objects[i];
			if(SansDouble(NewNom,cat)==false)
			return false;
		}
		return true;
	}
}
//---------------------------------------------------------------------------
// il n'y a pas d'atelier avec ce nom  dans la categorie
//---------------------------------------------------------------------------
bool __fastcall TCopierDansFrm::SansDouble(AnsiString newNom,CL_Categorie *cat)
{
	int n;
	AnsiString as=AnsiString("Il existe déjà  dans catégorie  ");
	CL_Atelier *atelier;

	for(n=0;n<V_Atelier->Nbelt;n++)
	{
		atelier=V_Atelier->Vecteur[n];
		if(atelier->Nom==NewNom && atelier->Categorie==cat)
		{
			as+=Atelier->Categorie->Nom;
			MessageBox(Handle,as.c_str(),
					"ERREUR",MB_OK|MB_ICONEXCLAMATION);
			return false;
		}
	}
	return true;
}
//--------------------------------------------
void TCopierDansFrm::IniCaption(void) {
	LabAncNom->Caption = LC_LabAncNom;
	RGCat->Caption = T->LC_RGCat;
	CopierDansFrm->Caption = T->LC_BtBnCopier_A;
	LabCategorie->Caption = LC_LabCategorie;
}
//--------------------------------------------
void TCopierDansFrm::TexteCaption(void) {
	LC_LabAncNom = T->TrouveCaption("CopierDans", "LC_LabAncNom");
	LC_RGCat = T->TrouveCaption("CL_Trad", "LC_RGCat");
	LC_BtBnCopier_A = T->TrouveCaption("CL_Trad", "LC_BtBnCopier_A");
	LC_LabCategorie = T->TrouveCaption("CopierDans", "LC_LabCategorie");

	IniCaption();

}

