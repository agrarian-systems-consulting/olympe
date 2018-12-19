//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Erreur.h"
#include "LBTChoix.h"
#include "TVPrixChoix.h"
#include "TVRdtChoix.h"

#include "GereAleaRdt.h"
#include "GereAleaPrix.h"
#include "TendanceEnum.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "AleaPrix.h"
#include "Outil.h"

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TAleaPrixFrm *AleaPrixFrm;
//---------------------------------------------------------------------------
__fastcall TAleaPrixFrm::TAleaPrixFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::FormCreate(TObject *Sender)
{
//    Height=Screen->Height;
//    Width=Screen->Width;

//    EstInitialise=false;  utilisé dans FormActivate de Forme00  surchargé ici

	Origine=0;//A replacer
	Digits=0;
}
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		Initialiser();
		Origine=1;
	}
	GrilleALire=RGPcentVal->ItemIndex;

}
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::Initialiser(void)
{
//	if(EstInitialise==false)
//    {
	LaGrille=Grille0;
	LesGrilles[0]=Grille0;
	AjoutRow=true;
	LabTitre->Caption="";
	GrilleX=1;// a augmenter
	DigitsPrix=2;
	DigitsRdt=2;

	Grille0->Visible= false;
	// ajout item ds menu leblanc p 171
//        LBTChoixFrm->Left= AleaPrixFrm->Left+AleaPrixFrm->Width-LBTChoixFrm->Width;
//        LBTChoixFrm->Top=  AleaPrixFrm->Top+20;
//        EstInitialise=true;

//    }
}
//---------------------------------------------------------------------------/*
/*
 if(CEstBon()==false) return;
 LaGrille->Tag=GTClose;
 PrepareEcran();
 TVTChoixFrm->Close();
 Close();  //utilise FormCloseQuery de AgriSaisie
 //et non celui de Forme00
 */
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::FormCloseQuery(TObject *Sender,bool &CanClose)
{
	int rep;
	if(TVPrixChoixFrm->Visible==true) TVPrixChoixFrm->Close();

	if (Tendance==NULL) // Sinon, une fonction va tester Agri et... (sebastien)
	{
		CanClose=true;
		return;
	}
//220508    DerniereCell();

	if(LabelModifie->Visible==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),T->L_DonModifT.c_str(),
				//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		switch(rep)
		{
			case ID_YES:
//                CellInitiale();    //repére derniére position dans la grille
//                LabelModifie->Visible=true;
			// trouver +lisible   CellInitiale a mis LabelModifie->Visible=false
			/*  inutile je ne verifiais que l'existence d'un nom
			 rep=VerifGrille();
			 if(rep==false)
			 {
			 ErreurFrm->Show();
			 CanClose=false;
			 break;
			 }
			 */
			DesGrilles();
			//Stocker();// peut etre appelé directement
			ES->ecrireFichier();
			MazModif();
			LabelModifie->Visible=false;
			break;
			case ID_CANCEL:
			CanClose=false;
			break;
			case ID_NO:
			break;
		}
	}
	else
	CanClose=true;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::Produit(int *nature)
{
	LabelModifie->Visible=false;
	LabNom->Visible=true;
	RGPcentVal->Visible=true;
	BtDonnees->Visible=true;

	//	if(CEstBon()==false) return;
	if(Tendance!=NULL)
	LabTitre->Caption=Tendance->Nom;
	else
	LabTitre->Caption="";

	switch(nature[1])
	{
		case PRODUIT:
		BtDonnees->Caption=T->L_Produit; //"Produits";
		switch(nature[2])
		{
			case TENDANCE:
			LaGrille->Tag=GTProd;
			break;
			case SCENARIO:
			LaGrille->Tag=GSProd;
			break;
		}
		break;

		case CHARGE:
		BtDonnees->Caption=T->L_Charge; //"Charges";
		switch(nature[2])
		{
			case TENDANCE:
			LaGrille->Tag=GTCharge;
			break;
			case SCENARIO:
			LaGrille->Tag=GSCharge;
			break;
		}
		break;
		case EXTER:
		BtDonnees->Caption=T->L_Exter; //"Externalités";
		switch(nature[2])
		{
			case TENDANCE:
			LaGrille->Tag=GTExter;
			break;
			case SCENARIO:
			LaGrille->Tag=GSExter;
			break;
		}
		break;

	}
	IniGrilleTendance();
//    LabNom->Caption=Tendance->Nom;
	VideGrille(Grille0);
	VersGrille(Grille0);
	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
/*
 //---------------------------------------------------------------------------
 void __fastcall TAleaPrixFrm::BaptiseBouton(void)
 {
 LabelModifie->Visible=false;
 LabNom->Visible=true;
 RGPcentVal->Visible=true;
 BtDonnees->Visible=true;
 //BtDonnees
 switch(LaGrille->Tag)
 {
 case GTProd:
 case GSProd:
 BtDonnees->Caption="Produits";  break;
 case GTCharge:
 case GSCharge:
 BtDonnees->Caption="Charges";   break;
 case GTExter:
 case GSExter:
 BtDonnees->Caption="Externalités";   break;

 default:ShowMessage("PrepareEcran BtDonnees Oubli");
 }
 TVPrixChoixFrm->Close();
 }
 */
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtDonneesClick(TObject *Sender)
{
	//effacer TV LB si visible
	if(TVPrixChoixFrm->Visible==true) {TVPrixChoixFrm->Visible=false;return;}

	TVPrixChoixFrm->LaGrille=LaGrille;
	//actualiser TV ou LB: on a pu creer des nouveaux éléments
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd:
		CreeTVItem(TVPrixChoixFrm->TV,V_CatProduit,V_Produit);break;
		case GTCharge:
		case GSCharge:
		CreeTVItem(TVPrixChoixFrm->TV,V_CatCharge, V_Charge); break;
		default:ShowMessage(" Oubli BtDonneesClick");break;
	}
	//rendre visible
	TVPrixChoixFrm->Visible=true;
	/*
	 //rendre visible
	 switch(LaGrille->Tag)
	 {
	 case GAni:
	 case GVariable:
	 case GExtNeg:
	 case GExtPos:
	 case GDepPrive:
	 case GRecPrive:
	 case GImmo:
	 case GPetit:
	 LBChoixFrm->Visible=true;
	 break;
	 default:
	 TVChoixFrm->Visible=true;
	 break;
	 }
	 */
}

//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtSupClick(TObject *Sender)
{
	int rep;
	int r=LaGrille->Row;
	CL_Delta *delta;
//bool supprimable;
	TObject *object=LaGrille->Objects[0][r];
	if(object==NULL) return;

	SelLigne();
	delta = (CL_Delta*) LaGrille->Objects[0][r];
	r=r;//aew

	rep=MessageBox(Handle,T->L_SupLiQ.c_str(),T->L_SupT.c_str(),
		//rep=MessageBox(Handle," Je supprime la ligne. Vous êtes sur ?","SUPPRESSION",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO)
	{
		DeSelLigne();
		return;
	}
	delta->Flag='S';
	SupprimerLigne();
	GrilleModif[LaGrille->Tag]=true;
	LabelModifie->Visible=true;
	DeSelLigne();
}
//---------------------------------------------------------------------------
//VideTout
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtBnVideToutClick(TObject *Sender)
{
	int r,rep;
	CL_Delta *delta;

	rep=MessageBox(Handle,T->L_SupToutQ.c_str(),T->L_SupT.c_str(),
			//rep=MessageBox(Handle," Attention Je supprime TOUT! Vous êtes sur ?","SUPPRESSION",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	LabelModifie->Visible=true;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		delta = (CL_Delta*) LaGrille->Objects[0][r];
		if(delta) delta->Flag='S';
	}
	VideGrille(LaGrille);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::RGPcentValClick(TObject *Sender)
{
	if(RGPcentVal->ItemIndex==0)GrilleALire=1;
	else GrilleALire=0;
//    DerniereCell();    //200508

	//pour lire la bonne grille
	DesGrilles();
	VersGrille(LaGrille);
	GrilleALire=RGPcentVal->ItemIndex;
	//revenir à case départ
}
//---------------------------------------------------------------------------
/*
 // est appelé par Form00->OnCloseQuery
 //---------------------------------------------------------------------------
 bool __fastcall TAleaPrixFrm::Stocker(void)
 {
 ES->ecrireFichier();
 MazModif();
 LabelModifie->Visible=false;
 return true;
 }
 */
//---------------------------------------------------------------------------
//Stocker
void __fastcall TAleaPrixFrm::BoutAnnulClick(TObject *Sender)
{
//    CEstBon();
}
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtBnStockerClick(TObject *Sender)
{
	if(Tendance==NULL) return;
	DerniereCell();
	if(LabelModifie->Visible==false) return;
	/*
	 rep=VerifGrille();
	 if(rep==false)
	 {
	 ErreurFrm->Show();
	 return;
	 }
	 */
	DesGrilles();
	ES->ecrireFichier();
	MazModif();
	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------

/*
 //---------------------------------------------------------------------------
 bool __fastcall TAleaPrixFrm::PrixExistent(void)
 {
 CL_Vecteur<CL_Delta> *vecteur;
 int r,nbelt;
 CL_Delta *delta;
 CL_Item  *item;
 float prix;
 bool correct;
 vecteur=Tendance->V_Delta;
 nbelt=vecteur->Nbelt;

 correct=true;
 for( r=0;r<nbelt;r++)
 {
 delta=vecteur->Vecteur[r];
 item=delta->Item;
 if(item->Prix==0) correct=false;
 }
 if(correct==false)
 MessageBox(Handle," Il manque des prix!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
 return correct;
 }
 //---------------------------------------------------------------------------
 bool __fastcall TAleaPrixFrm::RdtExistent(void)
 {
 CL_Vecteur<CL_Delta> *vecteur;
 int r,nbelt;
 CL_Delta *delta;
 bool correct;
 vecteur=Tendance->V_Delta;
 nbelt=vecteur->Nbelt;

 correct=true;
 for( r=0;r<nbelt;r++)
 {
 delta=vecteur->Vecteur[r];
 if(delta->Rdt==0) correct=false;
 }
 if(correct==false)
 MessageBox(Handle," Il manque des rendements!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
 return correct;
 }
 */

//---------------------------------------------------------------------------
void TAleaPrixFrm::TexteChaine(void) {

//	L_SupToutQ          =T->TrouveTexte("AleaPrixFrm","L_SupToutQ");
	L_Base = T->TrouveTexte("AleaPrixFrm", "L_Base");

}
//--------------------------------------------
void TAleaPrixFrm::IniCaption(void) {
	BtDonnees->Caption = T->LC_BtDonnees;
	LabNom->Caption = T->LC_LabNom;
	LabTitre->Caption = LC_LabTitre;
	AleaPrixFrm->Caption = LC_AleaPrixFrm;
	RGPcentVal->Items->Strings[0] = LC_Pcent;
	RGPcentVal->Items->Strings[1] = LC_Valeur;
	BtClasser->Caption = T->LC_BtClasser;
	ChBRepTout->Caption = T->LC_ChBRepTout;
}
//--------------------------------------------
void TAleaPrixFrm::TexteCaption(void) {
	LC_BtDonnees = T->TrouveCaption("CL_Trad", "LC_BtDonnees");
	LC_LabNom = T->TrouveCaption("CL_Trad", "LC_LabNom");
	LC_LabTitre = T->TrouveCaption("AleaPrix", "LC_LabTitre");
	LC_AleaPrixFrm = T->TrouveCaption("AleaPrix", "LC_AleaPrixFrm");
	LC_Pcent = T->TrouveCaption("AleaPrix", "LC_Pcent");
	LC_Valeur = T->TrouveCaption("AleaPrix", "LC_Valeur");

	IniCaption();

}

//------------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtBnNotesClick(TObject *Sender)
{
//020507
	NoteAgriFrm->VientDe="AleaPrix";//ne pas traduire
	NoteAgriFrm->Tendance=Tendance;
	NoteAgriFrm->Caption=Tendance->Nom;
	NoteAgriFrm->Memo->Text=Tendance->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TAleaPrixFrm::BtBnPcentClick(TObject *Sender)
{
//
	int c,r,col,n;
	float x1,x2,x3;
	CL_Delta *delta;
//int Digits=2;
	r=LaGrille->Row;
	c=LaGrille->Col;
	if(r<0 ||r >LaGrille->RowCount) return;
	if(c<3) return;
	x1=GrilleFloat(c-1,r);
	if(x1==0)
	{
		ShowMessage("division par zero  !!");
		return;
	}
	delta=(CL_Delta*)LaGrille->Objects[0][r];

	x2=GrilleFloat(c,r);
	delta->Pcent[c-5]=x2;
	for(col=c+1;col<LaGrille->ColCount;col++)
	{
		if(x1==0)
		{
			ShowMessage("division par zero  !!");
			return;
		}
		x3=x2*x2/x1;
		LaGrille->Cells[col][r]=Aff(x3,Digits);
		n=col-5;
		delta->Pcent[n]=x3;
		x1=x2;x2=x3;
	}
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TAleaPrixFrm::RGPrecisionClick(TObject *Sender)
{
	int r;
	int c,col;
	CL_Delta *delta;
	float prix;
	if(RGPrecision->ItemIndex==0) Digits=0;
	else Digits=2;

	for(r=1;r<LaGrille->RowCount;r++)
	{
		delta=(CL_Delta*)LaGrille->Objects[0][r];
		if(delta)
		{
			LaGrille->Cells[4][r]=Forme00Frm->Aff(delta->Item->Prix,DigitsPrix); //040408
			for(c=0,col=5;c<delta->NMax;c++,col++)
			{
				switch(RGPcentVal->ItemIndex)
				{
					case 0: // en pcent
					LaGrille->Cells[col][r]=Aff0(delta->Pcent[c],Digits);
					break;
					case 1:
					prix=(delta->Item->Prix*delta->Pcent[c])/100.;
					LaGrille->Cells[col][r]=Aff0(prix,Digits);
					break;
				}
			}
		}
	}
//    VideGrille(Grille0);
//	VersGrille(Grille0);

}
//---------------------------------------------------------------------------
//200907
void __fastcall TAleaPrixFrm::BtBnVersExcelClick(TObject *Sender)
{
	OutilFrm->VersExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
}
//---------------------------------------------------------------------------

void __fastcall TAleaPrixFrm::BtBnDExcelClick(TObject *Sender)
{
	OutilFrm->DExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
	LabelModifie->Visible==true;

}
//---------------------------------------------------------------------------

bool __fastcall TAleaPrixFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1730;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

