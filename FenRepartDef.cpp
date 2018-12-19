//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TVChoixRepart.h"
#include "FenRepartDef.h"
#include "CL_Trad.h"
#include "Aide.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TFenRepartDefFrm *FenRepartDefFrm;
extern CL_Trad *T;

/*
 création des répartitions
 */
//---------------------------------------------------------------------------
__fastcall TFenRepartDefFrm::TFenRepartDefFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::FormActivate(TObject *Sender)
{
	static bool debut=true;
	if(debut==true)
	{
		debut=false;
		Demarre();
	}
//	LabelModifie->Visible=false; fait dans Affiche
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::Demarre(void)
{
	int c;
	Repart=NULL;
	LaGrille->ColWidths[0]=60;
	for(int i=1;i<4;i++)LaGrille->ColWidths[i]=30;

	for(c=1;c<13;c++)
	LaGrille->Cells[0][c]=NomMois(c);

	LaGrille->Cells[1][0]=T->L_Avt1; //"Avt 1";
	LaGrille->Cells[2][0]="   1";
	LaGrille->Cells[3][0]="   2";

}
/*
 //---------------------------------------------------------------------------
 void __fastcall TFenRepartDefFrm::EffaceGrille(void)
 {
 int r,c;
 for(r=1;r<LaGrille->RowCount;r++)
 for(c=1;c<LaGrille->ColCount;c++)
 LaGrille->Cells[c][r]="";
 }
 */
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::Affiche(void)
{
	float totalPcent;
	LabelModifie->Visible=false;
//	EffaceGrille();
	EdCategorie->Text=Categorie->Nom;
	if(Repart0==NULL)
	{
		Traitement=CREER;
		Repart=new CL_Repart();
		EdCode->Text="";
	}
	else
	{
		Traitement=MODIFIER;
		Repart=new CL_Repart(Repart0); //garde ce qu'il y avait au debut
		EdCode->Text=Repart->Nom;
	}

	Repart->GrilleEcrire(LaGrille,0);
	totalPcent=Repart->LireTotal(LaGrille);
	EdTotPcent->Text=FloatToStrF((double)totalPcent,ffNumber,7,0);
	LaGrille->Col=1;LaGrille->Row=1;

}
// Traitement  0 nouveau  1 nouveau avec place pour Valeur
//             2  sans Valeur
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::LaGrilleKeyPress(TObject *Sender,
		char &Key)
{

	if(Key >='0' && Key <='9') {LabelModifie->Visible=true; return;}
	else if(Key=='-') {LabelModifie->Visible=true; return;}
	else if(Key=='.') {LabelModifie->Visible=true; return;}
	else if(Key==VK_BACK) {LabelModifie->Visible=true; return;}
	Key=0;

}
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::AffTotal(void)
{
	float tot;
	tot=Repart->LireTotal(LaGrille);

	EdTotPcent->Text=FloatToStrF((double)tot,ffNumber,7,0);
}
//---------------------------------------------------------------------------
// si creation   Repart= new CL_Repart();
//sinon          Repart=new CL_Repart(Repart0);
// on travaille sur Repart
// au Close
//  si on ne veut pas conserver-> delete Repart
// sinon
//       si creation stocker Repart
//       sinon lire la grille et la mettre dans Repart0 puis delete Repart
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	if(TVChoixRepartFrm->AFaire==AnsiString("Copier"))
	TVChoixRepartFrm->AFaire=AnsiString("Definir");
	if(Repart0==NULL) LabelModifie->Visible=true;
	if(LabelModifie->Visible==false) return;
	rep=MessageBox(Handle,T->L_DonModifQ.c_str(),"MODIFICATION",
			//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
			MB_YESNOCANCEL|MB_ICONEXCLAMATION);
	if(rep==ID_NO)
	{
		delete Repart;
		return;
	}

	if(VerifTotal()==IDYES) {CanClose=false;return;} //total!=100 et on veut modifier
	if(VerifCode()==IDYES) {CanClose=false;return;} //code déjà donné

	// on a seulement changé les %
	if(Traitement==MODIFIER)
	{
		Repart0->GrilleLire(LaGrille);
		//on a modifié le nom
		if(Repart0->Nom!=Repart->Nom &&Repart0->NoCategorie==Categorie->No)
		{
			Repart0->Nom=Repart->Nom;
			MajTV();
		}
		delete Repart;
	}
	else //CREER
	{
		Repart->Categorie=Categorie;
		Repart->NoCategorie=Categorie->No;
		Repart->GrilleLire(LaGrille);
		V_Repart->ins(Repart);
		MajTV();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::BtBnCopieRepartClick(TObject *Sender)
{
	TVChoixRepartFrm->AFaire=AnsiString("Copier");
//    TVChoixRepartFrm->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//retourne IDYES correction à faire
//         IDNO pas de correction
//---------------------------------------------------------------------------
int __fastcall TFenRepartDefFrm::VerifTotal(void)
{
	int rep;
	float total;
	AnsiString buf;
//	LireDerniereCell();
	total=Repart->LireTotal(LaGrille);
	if(total<100-5 ||total >100+5)
	{
		buf=AnsiString("Total  =")+ total;
		rep=MessageBox(Handle,"Vous corrigez ?",buf.c_str(),
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		return rep;
	}
	return IDNO;
}
//---------------------------------------------------------------------------
//retourne IDYES correction à faire
//         IDNO pas de correction

//---------------------------------------------------------------------------
int __fastcall TFenRepartDefFrm::VerifCode(void)
{
	Repart->Nom=EdCode->Text;
	if(Repart->Nom=="")
	{
		ShowMessage("Pas de Code");
		return IDYES;
	}

	if(CodeExiste()==IDYES)
	{
		if(Traitement==CREER)
		{
			ShowMessage("Code déjà donné");
			return IDYES;
		}
		else //MODIFIER
		{
			// on a seulement changé les %
			if(Repart0->Nom==Repart->Nom
					&&Repart0->NoCategorie==Repart->NoCategorie)
			return IDNO;
			else//on a changé le nom et il existe déjà
			return IDYES;
		}
	}
	else
	return IDNO;
}
//---------------------------------------------------------------------------
int __fastcall TFenRepartDefFrm::CodeExiste(void)
{
	int i;
	CL_Repart *repart;
	for(i=0;i<V_Repart->Nbelt;i++)
	{
		repart=V_Repart->Vecteur[i];
		if(repart->Nom==Repart->Nom
				&& repart->NoCategorie==Categorie->No)
		{
			return IDYES;
		}
	}
	return IDNO;
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::MajTV(void)
{
	TVChoixRepartFrm->TV->Items->Clear();
	Forme0Frm->CreeTVRepart(TVChoixRepartFrm->TV);
	TVChoixRepartFrm->TV->FullExpand();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//100/12
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::BtBnEgalClick(TObject *Sender)
{
	int i;
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	float taux;
	if(c>=4)return;
	taux=8.34;
	for(i=0;i<12;i++)
	{
		if(i==4) taux=8.33;
		LaGrille->Cells[c][r]=FloatToStrF((double)taux,ffNumber,7,2);
		if(r<12) r++;
		else
		{
			c++;r=1;
			if(c==4) break;
		}
	}
	AffTotal();
	LabelModifie->Visible=true;
}
//100
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::BtBn100Click(TObject *Sender)
{
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	if(c>=4)return;

	LaGrille->Cells[c][r]=100;

	LabelModifie->Visible=true;
	AffTotal();

}
//0
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::BtBn0Click(TObject *Sender)
{
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	if(c>=4)return;

	LaGrille->Cells[c][r]="";

	LabelModifie->Visible=true;
	AffTotal();
}
// 0 partout
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::BtBnMazClick(TObject *Sender)
{
	int r,c;
	for(r=1;r<LaGrille->RowCount;r++)
	for(c=1;c<LaGrille->ColCount;c++)
	LaGrille->Cells[c][r]="";
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartDefFrm::EdCodeKeyPress(TObject *Sender,
		char &Key)
{
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TFenRepartDefFrm::LaGrilleSelectCell(TObject *Sender,
		int ACol, int ARow, bool &CanSelect)
{
	AffTotal();
}
//---------------------------------------------------------------------------

void __fastcall TFenRepartDefFrm::BtBnACopierClick(TObject *Sender)
{
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	if(c>=4)return;
	ACopier=LaGrille->Cells[c][r];

}
//---------------------------------------------------------------------------

void __fastcall TFenRepartDefFrm::BtBnResteClick(TObject *Sender)
{
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	float tot,reste;
	if(c>=4)return;

	tot=Repart->LireTotal(LaGrille);
	reste=100-tot;

	LaGrille->Cells[c][r]=reste;

	LabelModifie->Visible=true;
	AffTotal();

}
//---------------------------------------------------------------------------

void __fastcall TFenRepartDefFrm::BtBnCopierClick(TObject *Sender)
{
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	if(c>=4)return;
	LaGrille->Cells[c][r]=ACopier;

}
//---------------------------------------------------------------------------

//--------------------------------------------
void TFenRepartDefFrm::IniCaption(void) {
	BtBn0->Caption = LC_BtBn0;
	BtBnMaz->Caption = LC_BtBnMaz;
	BtBn100->Caption = LC_BtBn100;
	BtBnEgal->Caption = LC_BtBnEgal;
	BtBnACopier->Caption = LC_BtBnACopier;
	GBCategorie->Caption = T->LC_RGCat;
	GBCode->Caption = T->LC_GBCode;
	BtBnCopier->Caption = T->LC_BtBnCopier;
	BtBnCopieRepart->Caption = LC_BtBnCopieRepart;
	BtBnReste->Caption = LC_BtBnReste;
	LabelModifie->Caption = T->LC_LabelModifie;
	FenRepartDefFrm->Caption = LC_FenRepartDefFrm;
	BtBnSup->Caption = T->LC_BtBnSupBesTrav;
	LabTotPcent->Caption = T->LC_LabTotPcent;
}
//--------------------------------------------
void TFenRepartDefFrm::TexteCaption(void) {
	LC_BtBn0 = T->TrouveCaption("FenRepartDef", "LC_BtBn0");
	LC_BtBnMaz = T->TrouveCaption("FenRepartDef", "LC_BtBnMaz");
	LC_BtBn100 = T->TrouveCaption("FenRepartDef", "LC_BtBn100");
	LC_BtBnEgal = T->TrouveCaption("FenRepartDef", "LC_BtBnEgal");
	LC_BtBnACopier = T->TrouveCaption("FenRepartDef", "LC_BtBnACopier");
	LC_RGCat = T->TrouveCaption("CL_Trad", "LC_RGCat");
	LC_GBCode = T->TrouveCaption("CL_Trad", "LC_GBCode");
	LC_BtBnCopier = T->TrouveCaption("CL_Trad", "LC_BtBnCopier");
	LC_BtBnCopieRepart = T->TrouveCaption("FenRepartDef", "LC_BtBnCopieRepart");
	LC_BtBnReste = T->TrouveCaption("FenRepartDef", "LC_BtBnReste");
	LC_LabelModifie = T->TrouveCaption("CL_Trad", "LC_LabelModifie");
	LC_FenRepartDefFrm = T->TrouveCaption("FenRepartDef", "LC_FenRepartDefFrm");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");
	LC_LabTotPcent = T->TrouveCaption("CL_Trad", "LC_LabTotPcent");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TFenRepartDefFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TFenRepartDefFrm::LaGrilleSetEditText(TObject *Sender,
		int ACol, int ARow, const AnsiString Value)
{
	LabelModifie->Visible=true; //180512
}
//---------------------------------------------------------------------------

