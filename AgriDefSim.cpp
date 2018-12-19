//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "TVChoix.h"
//#include "TVChoixElt.h"

#include "NoteAgri.h"
#include "AgriSaisie.h"
#include "LesDefSim.h"
#include "AgriClasst.h"

//#include "ChoixCritere.h"
#include "LBTypeZone.h"
#include "CL_Trad.h"
#include "AgriDefSerie.h"
#include "Aide.h"

#include "AgriDefSim.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TAgriDefSimFrm *AgriDefSimFrm;

extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TAgriDefSimFrm::TAgriDefSimFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::FormActivate(TObject *Sender)
{
	//Origine mis à zero dans appel par AgriDefSim
	// evite de passer dedans quand on vient de LBTypeZone
	if(Origine==0)
	{
		LabelModifie->Visible=false;
		AnEstAffiche=false;
		Origine=1;

		LBResultatPour->ItemIndex=NoSerie;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::Aff(void)
{
	// on entre par Aff
	LstCritereTemp=new TList;

	Agri=AgriSaisieFrm->Agri;
	DefSim=Agri->DefSim;

	EdNom->Text= AgriSaisieFrm->Agri->Nom;
	EdVariante->Text= AgriSaisieFrm->Agri->NoVariante;

	EdAn0->Text= DefSim->An_0;
	CBOuv->ItemIndex= DefSim->MDeb-1;

	IniEcran();
	AffTitreCritere();
	AffCritere();

	//...40ans 251006
	//nombre d'années de simulation
	CBNbAnnee->ItemIndex=(DefSim->NbAnSim-10)/10;

//251006
	if(DefSim->NbAnSim>10)
	{
		CreeLBResultatPour(AgriSaisieFrm->Agri->DefSim->NbAnSim);
		GBSerie->Visible=true;
		LBResultatPour->Visible=true;
	}
	else
	{
		GBSerie->Visible=false;
		LBResultatPour->Visible=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::IniEcran(void)
{
	DansIniEcran=true;
	AnAAfficher=false;

	//CBSTP  Control Box Scenario Tendance P=Prix
	//                                     Q=Quantité

	IniCBST(CBSTPProduit,V_TendPrixProd, V_ScenPrixProd);
	IniCBST(CBSTPCharge, V_TendPrixCharge, V_ScenPrixCharge);

	IniCBST(CBSTQProduit,V_TendQProd, V_ScenQProd);
	IniCBST(CBSTQCharge, V_TendQCharge, V_ScenQCharge);
	IniCBST(CBSTQExt, V_TendQExt, V_ScenQExt);

	AffTend(DefSim->TouSPrixProd, DefSim->PrixProd, CBSTPProduit, CBPProduit,
			V_TendPrixProd,V_ScenPrixProd);

	AffTend(DefSim->TouSPrixCharge, DefSim->PrixCharge, CBSTPCharge, CBPCharge,
			V_TendPrixCharge,V_ScenPrixCharge);

	AffTend(DefSim->TouSQProd, DefSim->QProd, CBSTQProduit, CBQProduit,
			V_TendQProd,V_ScenQProd);

	AffTend(DefSim->TouSQCharge, DefSim->QCharge, CBSTQCharge, CBQCharge,
			V_TendQCharge,V_ScenQCharge);

	AffTend(DefSim->TouSQExt, DefSim->QExt, CBSTQExt, CBQExt,
			V_TendQExt,V_ScenQExt);

	if(DefSim->TouSPrixProd==ENCHDEF) DefSim->TypeAlea=ENCHDEF;
	if(DefSim->TouSPrixCharge==ENCHDEF) DefSim->TypeAlea=ENCHDEF;
	if(DefSim->TouSQProd==ENCHDEF) DefSim->TypeAlea=ENCHDEF;
	if(DefSim->TouSQCharge==ENCHDEF) DefSim->TypeAlea=ENCHDEF;
	if(DefSim->TouSQExt==ENCHDEF) DefSim->TypeAlea=ENCHDEF;

	switch(DefSim->TypeAlea)
	{
		case SANS:
		RGAlea->ItemIndex=0;
		GBPrix->Visible= false;
		GBQuantite->Visible=false;
		GBEnch->Visible= false;
		break;

		default:
		RGAlea->ItemIndex=1;
		GBPrix->Visible= true;
		GBQuantite->Visible=true;
		GBEnch->Visible= false;
		break;
	}

	DansIniEcran=false;
	if(AnAAfficher==true)
	{
		GBEnch->Visible=true;
		AffAn();
	}
}
//---------------------------------------------------------------------------
// critères
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::AffTitreCritere(void)
{
	int n;
//TListBox  *lB;

	CL_Categorie *categorie;
	GrilleCritere->ColCount=V_CatTypeZone->Nbelt;
	Forme00Frm->VideGrille(GrilleCritere);

	for(n=0;n<V_CatTypeZone->Nbelt;n++)
	{
		categorie=V_CatTypeZone->Vecteur[n];
		GrilleCritere->Cells[n][0]=categorie->Nom;
		GrilleCritere->Objects[n][0]=(TObject*)categorie;
	}
}
// pour l'agriculteur recherche les critères et les affiche
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::AffCritere(void)
{
	int r,n,k;
	bool trouve;
	CL_Categorie *categorie;
	TList *lstCritere;
	CL_Item *critere;
	CL_Agriculteur *agri=AgriSaisieFrm->Agri;
	lstCritere=agri->LstCritere;

	r=1;

	for(n=0;n<V_CatTypeZone->Nbelt;n++)
	{
		categorie=(CL_Categorie*)GrilleCritere->Objects[n][0];
		trouve=false;
		for (k=0;k<lstCritere->Count;k++)
		{
			critere=(CL_Item*)lstCritere->Items[k];
			if(critere->Categorie->No==categorie->No)
			{
				GrilleCritere->Cells[n][r]=critere->Nom;
				GrilleCritere->Objects[n][r]=(TObject*)critere;
				trouve=true;
				break;
			}
		}
		if(trouve==false)
		{
			GrilleCritere->Cells[n][r]="???";
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::GrilleCritereClick(TObject *Sender)
{
	int c=GrilleCritere->Col;
	int r=1;
	int posG,posH;
	CL_Categorie *categorie;
	TRect rect;
	rect=GrilleCritere->CellRect(c, r);
	posG=Left +GrilleCritere->Left +rect.Left;
	posH=Top +GrilleCritere->Top +rect.Bottom+40; //20??
	r=1;
	categorie=(CL_Categorie *)GrilleCritere->Objects[c][0];
	if(categorie==NULL) return;

	LBTypeZoneFrm->Origine="AgriDefSim";
	LBTypeZoneFrm->CreeLB(posG,posH,r,categorie);
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::AffTend(int TouS,CL_Tendance *tend,
		TComboBox *CBST,TComboBox *CB,
		CL_Vecteur<CL_Tendance> *vTend,CL_Vecteur<CL_Tendance> *vScen)
{
	int itemIndex;
	switch(TouS)
	{
		case 0: //Aucun
		CBST->ItemIndex=0;
		CB->Text="";
		break;
		case 1://Tendance
		CBST->ItemIndex=1;
		IniCB(CB,vTend);
		itemIndex=trouve(vTend,tend);
		CB->ItemIndex=itemIndex;
		break;
		case 2://Scenario
		if(vTend->Nbelt==0)
		CBST->ItemIndex=1;
		else
		CBST->ItemIndex=2;
		IniCB(CB,vScen);
		itemIndex=trouve(vScen,tend);
		CB->ItemIndex=itemIndex;
		AnAAfficher=true;
		break;

	}
	CB->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::AffAn(void)
{
	int an_0,an;
	int c;
	if(AnEstAffiche==true) return;
	GBEnch->Visible=true;
	an_0=DefSim->An_0;
	for(c=0,an=an_0;c<N_X;c++,an++)
	{
		GrilleEnch->Cells[c][0]=an;
		GrilleEnch->Cells[c][1]=DefSim->Enchainement[c];
	}
	AnEstAffiche=true;

}
//---------------------------------------------------------------------------
int __fastcall TAgriDefSimFrm::trouve(CL_Vecteur<CL_Tendance>*v_Tend,CL_Tendance *tend0)
{
	int i;
	CL_Tendance *tend;
	// i+1 car Aucun
	if (tend0==NULL) return 0;
	for(i=0;i<v_Tend->Nbelt;i++)
	{
		tend=v_Tend->Vecteur[i];
		if(tend==tend0)return i;
	}
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::IniCBST(TComboBox *CBST,
		CL_Vecteur<CL_Tendance> *V_Tend,
		CL_Vecteur<CL_Tendance> *V_Scen)

{
	bool actif=false;
	CBST->Text="";
	CBST->Clear();
	CBST->Items->AddObject(L_Aucun,(TObject*) 0);
	//CBST->Items->AddObject("Aucun",(TObject*) 0);
	if( V_Tend->Nbelt >0) {CBST->Items->AddObject(T->L_Tendance,(TObject*) 1);actif=true;}
	//if( V_Tend->Nbelt >0){ CBST->Items->AddObject("Tendance",(TObject*) 1);actif=true;}
	if( V_Scen->Nbelt >0) {CBST->Items->AddObject(T->L_Scenario,(TObject*) 2);actif=true;}
	//if( V_Scen->Nbelt >0){ CBST->Items->AddObject("Scenario",(TObject*) 2);actif=true;}

//    CBST->Font->Color=clRed;
	CBST->Enabled=actif;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::IniCB(TComboBox *CB,CL_Vecteur<CL_Tendance> *V_Tend)
{
	int i;
	CL_Tendance *tendance;
	CB->Text="";
	CB->Clear();
//    CB->Items->AddObject("Aucun",NULL);
	for(i=0;i<V_Tend->Nbelt;i++)
	{
		tendance=V_Tend->Vecteur[i];
		CB->Items->AddObject(tendance->Nom,(TObject*)tendance);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);

	if(rep==IDYES) Application->Terminate();
	else return;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::BtBnNotesClick(TObject *Sender)
{

	NoteAgriFrm->VientDe="AgriDefSim";
	NoteAgriFrm->Agri=AgriSaisieFrm->Agri;
	NoteAgriFrm->Caption=AgriSaisieFrm->Caption;
	NoteAgriFrm->Memo->Text=AgriSaisieFrm->Agri->Notes;

	NoteAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::GrilleEnchKeyPress(TObject *Sender, char &Key)
{
	int c,r;
	LabelModifie->Visible=true;
	c=GrilleEnch->Col;
	r=GrilleEnch->Row;
	r=r; //aew
	if(Key>='A' && Key<='N') {GrilleEnch->Cells[c][r]=Key; return;}
	if(Key>='a' && Key<='n') {Key+='A'-'a';GrilleEnch->Cells[c][r]=Key; return;}
	Key=0;

}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::BtReportDroitClick(TObject *Sender)
{
	int c0,c,r;
	LabelModifie->Visible=true;

	c0=GrilleEnch->Col;
	r=GrilleEnch->Row;
	switch(ChBRepTout->Checked)
	{
		case true:
		for(c=c0;c<N_X;c++)
		GrilleEnch->Cells[c][r]=GrilleEnch->Cells[c0][r];
		break;
		case false:
		for(c=c0;c<N_X;c++)
		{
			if(GrilleEnch->Cells[c][r].Length()>0) continue;
			GrilleEnch->Cells[c][r]=GrilleEnch->Cells[c0][r];
		}
	}
}
//---------------------------------------------------------------------------
//    Alea
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::RGAleaClick(TObject *Sender)
{
//    if(Sender->ClassNameIs("TRadioGroup")==false) return;
	if(DansIniEcran==true) return;

	LabelModifie->Visible=true;

	DefSim->TouSPrixProd= 0;
	DefSim->TouSPrixCharge= 0;
	DefSim->TouSQProd= 0;
	DefSim->TouSQCharge= 0;
	DefSim->TouSQExt= 0;

	DefSim->PrixProd= NULL;
	DefSim->PrixCharge= NULL;
	DefSim->QProd= NULL;
	DefSim->QCharge= NULL;
	DefSim->QExt= NULL;
	strcpy(DefSim->Enchainement,"AAAAAAAAAA");
	for(int c=0;c<N_X;c++)
	GrilleEnch->Cells[c][1]=DefSim->Enchainement[c];

	DefSim->TypeAlea=RGAlea->ItemIndex;
//    if(RGAlea->ItemIndex > 0)
	IniEcran();
}
//---------------------------------------------------------------------------
//  Combo Aucun Tendance Prix
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBSTPProduitClick(TObject *Sender)
{
	int n,n0;
	CL_Tendance *tend;
	LabelModifie->Visible=true;
	n=CBSTPProduit->ItemIndex;

	n0=(int)CBSTPProduit->Items->Objects[n];
	DefSim->TouSPrixProd= n0;
	DefSim->NoPrixProd=0;

	switch(n0)
	{
		case 0:
		DefSim->PrixProd=NULL;
		CBPProduit->Clear();
		break;
		case 1:
		tend=V_TendPrixProd->Vecteur[0];
		//si le premier convient ne pas attendre de click sur CBPProduit
		DefSim->PrixProd=tend;
		DefSim->NoPrixProd=tend->No;
		IniCB(CBPProduit,V_TendPrixProd);
		break;
		case 2:
		tend=V_ScenPrixProd->Vecteur[0];
		DefSim->PrixProd=tend;
		DefSim->NoPrixProd=tend->No;
		IniCB(CBPProduit,V_ScenPrixProd);AffAn();
		break;
	}
	CBPProduit->ItemIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBSTPChargeClick(TObject *Sender)
{
	int n,n0;
	CL_Tendance *tend;

	LabelModifie->Visible=true;
	n=CBSTPCharge->ItemIndex;
	n0=(int)CBSTPCharge->Items->Objects[n];
	DefSim->TouSPrixCharge= n0;
	DefSim->NoPrixCharge=0;

	switch(n0)
	{
		case 0:
		DefSim->PrixCharge=NULL;
		CBPCharge->Clear();
		break;
		case 1:
		tend=V_TendPrixCharge->Vecteur[0];
		DefSim->PrixCharge=tend;
		DefSim->NoPrixCharge=tend->No;
		IniCB(CBPCharge,V_TendPrixCharge);
		break;
		case 2:
		tend=V_ScenPrixCharge->Vecteur[0];
		DefSim->PrixCharge=tend;
		DefSim->NoPrixCharge=tend->No;
		IniCB(CBPCharge,V_ScenPrixCharge);AffAn();
		break;
	}

	CBPCharge->ItemIndex=0;

}
//---------------------------------------------------------------------------

void __fastcall TAgriDefSimFrm::CBSTQProduitClick(TObject *Sender)
{
	int n,n0;
	CL_Tendance *tend;
	LabelModifie->Visible=true;
	n=CBSTQProduit->ItemIndex;
	n0=(int)CBSTQProduit->Items->Objects[n];
	DefSim->TouSQProd= n0;
	DefSim->NoQProd=0;

	switch(n0)
	{
		case 0:
		DefSim->QProd=NULL;
		CBQProduit->Clear();
		break;
		case 1:
		tend=V_TendQProd->Vecteur[0];
		DefSim->QProd=tend;
		DefSim->NoQProd=tend->No;
		IniCB(CBQProduit,V_TendQProd);
		break;
		case 2:
		tend=V_ScenQProd->Vecteur[0];
		DefSim->QProd=tend;
		DefSim->NoQProd=tend->No;
		IniCB(CBQProduit,V_ScenQProd);AffAn();
		break;
	}

	CBQProduit->ItemIndex=0;

}
//---------------------------------------------------------------------------

void __fastcall TAgriDefSimFrm::CBSTQChargeClick(TObject *Sender)
{
	int n,n0;
	CL_Tendance *tend;

	LabelModifie->Visible=true;
	n=CBSTQCharge->ItemIndex;
	n0=(int)CBSTQCharge->Items->Objects[n];
	DefSim->TouSQCharge= n0;
	DefSim->NoQCharge=0;

	switch(n0)
	{
		case 0:
		DefSim->QCharge=NULL;
		CBQCharge->Clear();
		break;
		case 1:
		tend=V_TendQCharge->Vecteur[0];
		DefSim->QCharge=tend;
		DefSim->NoQCharge=tend->No;
		IniCB(CBQCharge,V_TendQCharge);
		break;
		case 2:
		tend=V_ScenQCharge->Vecteur[0];
		DefSim->QCharge=tend;
		DefSim->NoQCharge=tend->No;
		IniCB(CBQCharge,V_ScenQCharge);
		AffAn();
		break;
	}

	CBQCharge->ItemIndex=0;

}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBSTQExtClick(TObject *Sender)
{
	int n,n0;
	CL_Tendance *tend;

	LabelModifie->Visible=true;
	n=CBSTQExt->ItemIndex;
	n0=(int)CBSTQExt->Items->Objects[n];
	DefSim->TouSQExt= n0;
	DefSim->NoQExt=0;

	switch(n0)
	{
		case 0:
		DefSim->QExt=NULL;
		CBQExt->Clear();
		break;
		case 1:
		tend=V_TendQExt->Vecteur[0];
		DefSim->QExt=tend;
		DefSim->NoQExt=tend->No;
		IniCB(CBQExt,V_TendQExt);
		break;
		case 2:
		tend=V_ScenQExt->Vecteur[0];
		DefSim->QExt=tend;
		DefSim->NoQExt=tend->No;
		IniCB(CBQExt,V_ScenQExt);AffAn();
		break;
	}
	CBQExt->ItemIndex=0;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  Combo Prix
//                Produit
//                Charge
//        Quantite
//                Produit
//                Charge
//                Externalite
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBPProduitClick(TObject *Sender)
{
	CL_Tendance *tend;
	int n=CBPProduit->ItemIndex;
	LabelModifie->Visible=true;

	tend=(CL_Tendance*)CBPProduit->Items->Objects[n];
	DefSim->NoPrixProd=tend->No;
	DefSim->PrixProd =tend;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBPChargeClick(TObject *Sender)
{
	CL_Tendance *tend;
	int n=CBPCharge->ItemIndex;
	LabelModifie->Visible=true;

	tend=(CL_Tendance*)CBPCharge->Items->Objects[n];
	DefSim->NoPrixCharge=tend->No;
	DefSim->PrixCharge=tend;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBQProduitClick(TObject *Sender)
{
	CL_Tendance *tend;
	int n=CBQProduit->ItemIndex;
	LabelModifie->Visible=true;

	tend=(CL_Tendance*)CBQProduit->Items->Objects[n];
	DefSim->NoQProd=tend->No;
	DefSim->QProd =tend;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBQChargeClick(TObject *Sender)
{
	CL_Tendance *tend;
	int n=CBQCharge->ItemIndex;
	LabelModifie->Visible=true;

	tend=(CL_Tendance*)CBQCharge->Items->Objects[n];
	DefSim->NoQCharge=tend->No;
	DefSim->QCharge=tend;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBQExtClick(TObject *Sender)
{
	CL_Tendance *tend;
	int n=CBQExt->ItemIndex;
	LabelModifie->Visible=true;

	tend=(CL_Tendance*)CBQExt->Items->Objects[n];
	DefSim->NoQExt=tend->No;
	DefSim->QExt=tend;
}
//---------------------------------------------------------------------------
//Combo   Mois Ouverture
//        Calage
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBOuvChange(TObject *Sender)
{
	LabelModifie->Visible=true;
	DefSim->MDeb=CBOuv->ItemIndex+1;
	Mois_0=DefSim->MDeb;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TAgriDefSimFrm::Verif(void)
{
	bool existe=false;
	AnsiString as;
	char *chaine;
	char car;
	int i;
	if(LabelModifie->Visible==false) return true;
	if(DefSim->An_0 <=1950 ||DefSim->An_0 >=2050 )
	{
		MessageBox(Handle,L_LimDate.c_str(),L_LimDateM.c_str(), MB_OK);
		//MessageBox(Handle,"Doit être compris entre 1950 et 2050","ANNEE ERRONEE", MB_OK);
		return false;
	}

	for(i=0;i<N_X;i++)
	{
		as=GrilleEnch->Cells[i][1];
		chaine=as.c_str();
		car=chaine[0];
		DefSim->Enchainement[i]=car;
	}

	if(DefSim->TypeAlea==SANS) return true;

	if(DefSim->PrixProd) existe=true;
	if(DefSim->PrixCharge) existe=true;
	if(DefSim->QProd) existe=true;
	if(DefSim->QCharge) existe=true;
	if(DefSim->QExt) existe=true;

	if(existe==true) return true;

	switch(DefSim->TypeAlea)
	{
		case TENDANCE:
		MessageBox(Handle,L_ErrTend.c_str(),T->L_Erreur.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,"Aucune tendance","ERREUR",MB_OK|MB_ICONSTOP);
		break;

		case ENCHDEF:
		case ENCHALEA:
		case MCARLO:
		MessageBox(Handle,L_ErrScen.c_str(),T->L_Erreur.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,"Aucun scénario","ERREUR",MB_OK|MB_ICONSTOP);
		break;
	}
	return false; //aew
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::BtBnReprendreClick(TObject *Sender)
{
	LesDefSimFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TAgriDefSimFrm::BtBnConserverClick(TObject *Sender)
{
	CL_AgriDefSim *defSim;
	if(Verif()==false) return;
	if(DefSimExiste()==true) return;
	defSim=new CL_AgriDefSim(DefSim);
	V_DefSim->ins(defSim);
	ES->ecrireFichier();
}
//---------------------------------------------------------------------------
bool __fastcall TAgriDefSimFrm::DefSimExiste(void)
{
	int i;
	CL_AgriDefSim *defSim;
	for (i=0;i<V_DefSim->Nbelt;i++)
	{
		defSim=V_DefSim->Vecteur[i];
		if( EstIdentique(defSim)==true) return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriDefSimFrm::EstIdentique(CL_AgriDefSim *defSim)
{
	if(defSim->TouSPrixProd!= DefSim->TouSPrixProd) return false;
	if(defSim->TouSPrixCharge!= DefSim->TouSPrixCharge) return false;
	if(defSim->TouSQProd!= DefSim->TouSQProd) return false;
	if(defSim->TouSQCharge!= DefSim->TouSQCharge) return false;
	if(defSim->TouSQExt!= DefSim->TouSQExt) return false;

	if(defSim->PrixProd!= DefSim->PrixProd) return false;
	if(defSim->PrixCharge!= DefSim->PrixCharge) return false;
	if(defSim->QProd!= DefSim->QProd) return false;
	if(defSim->QCharge!= DefSim->QCharge) return false;
	if(defSim->QExt!= DefSim->QExt) return false;

	if(strcmp(defSim->Enchainement,DefSim->Enchainement) !=0) return false;

	return true;
}
//---------------------------------------------------------------------------
//An_0
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::EdAn0KeyPress(TObject *Sender, char &Key)
{
	if(Key >='0' && Key <='9')
	{
		LabelModifie->Visible=true;
		return;
	}
	Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::EdAn0Exit(TObject *Sender)
{
	if(EdAn0->Modified==true)
	{
		DefSim->An_0=EdAn0->Text.ToInt();
		AnEstAffiche=false;
		AffAn();
		EdAn0->Modified=false;
	}
}
//---------------------------------------------------------------------------
//  Close
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int c;
	CL_Item *critere;
	if(LabelModifie->Visible==false) {CanClose=true;return;}

	if(Verif()==true)
	{
		// les criteres
		AgriSaisieFrm->Agri->LstCritere->Clear();
		//lstCritere->Clear();
		for(c=0;c<GrilleCritere->ColCount;c++)
		{
			critere=(CL_Item*)GrilleCritere->Objects[c][1];
			if(critere==NULL) continue;
			AgriSaisieFrm->Agri->LstCritere->Add(critere);
		}
		LabelModifie->Visible=false;
		AgriSaisieFrm->Origine=0; // oblige a refaire calcul
		ES->ecrireFichier();

		CanClose=true;
		LBTypeZoneFrm->Visible=false;
		delete LstCritereTemp;// a supprimer
	}
	else CanClose=false;

}
// ceci declenche la création de LstSerie       //300407
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::CBNbAnneeClick(TObject *Sender)
{
	int rep;
	AnsiString asTitre;
	int nbAnSim;
	GBSerie->Visible=false;
	LBResultatPour->Visible=false;

	//...40ans et + 251006
	//nombre d'années de simulation
	nbAnSim=(CBNbAnnee->ItemIndex+1)*10;

	//  on vient de redéfinir la meme chose
	if(Agri->DefSim->NbAnSim==nbAnSim) return;
	// on demande simulation su + de 10 ans
	else if(Agri->DefSim->NbAnSim==10)
	{
//        asTitre =AnsiString("SIMULATION sur   ")+ nbAnSim+AnsiString("  Ans");
//        rep=MessageBox(Handle,"c'est bien sur ",asTitre.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
		asTitre =AnsiString(L_SimSur)+"  "+ nbAnSim+" "+L_An;
		rep=MessageBox(Handle,L_CestSur.c_str(),asTitre.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDNO)
		return;
		//creer Agri->LstSerie
		//           contient des ST_NoAgri   un no un ptr sur CL_Agri..
		//              au début seul No   est initialisé   Agri est NULL
		//                       Agri initialisé par la suite
		AgriDefSerieFrm->DefSerie(Agri,nbAnSim);

		CreeLBResultatPour(nbAnSim);

		GBSerie->Visible=true;
		LBResultatPour->Visible=true;
	}
	// on avait deja simulation sur + de 10 ans et on veut +
//a vérifier
	else if(nbAnSim > AgriSaisieFrm->Agri->DefSim->NbAnSim)
	{
		asTitre =AnsiString("AGRANDIR DUREE SIMULATION à   ")+ nbAnSim+AnsiString("  Ans");
		rep=MessageBox(Handle,"c'est bien sur ",asTitre.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDNO)
		return;
		AgriDefSerieFrm->DefSeriePlus(Agri,nbAnSim);

		CreeLBResultatPour(nbAnSim); //??

		GBSerie->Visible=true;
		LBResultatPour->Visible=true;
	}
	// on avait deja simulation sur + de 10 ans et on veut -
	else if(nbAnSim < AgriSaisieFrm->Agri->DefSim->NbAnSim)
	{
		asTitre =AnsiString("DIMINUER DUREE SIMULATION à   ")+ nbAnSim+AnsiString("  Ans");
		rep=MessageBox(Handle,"c'est bien sur ",asTitre.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDNO)
		return;
		AgriDefSerieFrm->DefSerieMoins(Agri,nbAnSim);

		CreeLBResultatPour(nbAnSim); //??

		GBSerie->Visible=true;
		LBResultatPour->Visible=true;
	}
	LabelModifie->Visible=true; //181207

}
/*
 //---------------------------------------------------------------------------

 void __fastcall TAgriDefSimFrm::LBResultatPourClick(TObject *Sender)
 {
 int n;//,nSerie;
 AnsiString as;
 CL_Agriculteur *agri,*agriAvant;
 AnsiString debNom;
 ST_NoAgri *noAgri,*noAgriPrec;

 NoSerie=LBResultatPour->ItemIndex;
 agriAvant=NULL;
 for(n=0;n<=NoSerie;n++)        //de tte façon calculer le 0
 {
 noAgri=(ST_NoAgri*)Agri->LstSerie->Items[n];
 agri=noAgri->Agri;
 //if(agri==NULL) break;     //à introduire 260407

 if(agriAvant)
 agri->TresoIni=agriAvant->Resultat->SoldeCumul[N_X-1];
 AgriSaisieFrm->Calcul0(agri);
 agriAvant=agri;
 }
 AgriSaisieFrm->Agri=agri;
 agri->TypeAgreg=SANS;
 AgriSaisieFrm->Origine=0;
 AgriSaisieFrm->Show();

 }
 */
//---------------------------------------------------------------------------
void __fastcall TAgriDefSimFrm::LBResultatPourClick(TObject *Sender)
{
	int n,nSerie,nNouv;
	AnsiString as;
	CL_Agriculteur *agri,*agriAvant;
	AnsiString debNom;
	ST_NoAgri *noAgri,*noAgriAvant;

	NoSerie=LBResultatPour->ItemIndex;

	noAgriAvant=(ST_NoAgri*)Agri->LstSerie->Items[0];
	agriAvant=noAgriAvant->Agri;
	for(n=1;n<=NoSerie;n++)
	{
		noAgri=(ST_NoAgri*)Agri->LstSerie->Items[n];
		agri=noAgri->Agri;
		if(agri==NULL)
		AgriDefSerieFrm->DefAgriApres(agriAvant,noAgri);
		agriAvant=noAgri->Agri;
	}
	//calculer les résultats
	// si simul sur + de 10 ans la treso initiale de simul n+1 =
	//                             treso finale de simul n
	agriAvant=NULL;
	for(n=0;n<=NoSerie;n++)//de tte façon calculer le 0
	{
		noAgri=(ST_NoAgri*)Agri->LstSerie->Items[n];
		agri=noAgri->Agri;
		agri->NoSerie=n; //240907
		if(agriAvant)
		agri->TresoIni=agriAvant->Resultat->SoldeCumul[N_X-1];
		AgriSaisieFrm->Calcul0(agri);
		agriAvant=agri;
	}
	AgriSaisieFrm->Agri=agri;
	agri->TypeAgreg=SANS;
	AgriSaisieFrm->Origine=0;
	AgriSaisieFrm->Show();

}
//---------------------------------------------------------------------------
void TAgriDefSimFrm::CreeLBResultatPour(int nAnSerie) {
	AnsiString as;
	int n;
//int n0,n1;
	int anD;
	CL_Agriculteur *agriDepart;
	ST_NoAgri *noAgri;
//    if(Agri->LstSerie==NULL)
//        Agri->LstSerie=new TList;
	noAgri = (ST_NoAgri*) Agri->LstSerie->Items[0];
	if (noAgri->Agri == NULL) //051008
		noAgri->Agri = Agri;
	agriDepart = noAgri->Agri;
	anD = agriDepart->DefSim->An_0;

	LBResultatPour->Clear();
	if (nAnSerie <= 10)
		return;
	for (n = 0; n < nAnSerie; n += 10) {
		/*
		 n0=n+1;n1=n0+9;
		 as=AnsiString (n0)+AnsiString("-")+AnsiString(n1);
		 LBResultatPour->Items->Add(as);
		 */
		as = AnsiString(anD) + AnsiString("-") + AnsiString(anD + 9);
		LBResultatPour->Items->Add(as);
		anD += 10;
	}
}
//---------------------------------------------------------------------------
void TAgriDefSimFrm::TexteChaine(void) {
	L_Aucun = T->TrouveTexte("AgriDefSimFrm", "L_Aucun");
	L_LimDate = T->TrouveTexte("AgriDefSimFrm", "L_LimDate");
	L_LimDateM = T->TrouveTexte("AgriDefSimFrm", "L_LimDateM");
	L_ErrTend = T->TrouveTexte("AgriDefSimFrm", "L_ErrTend");
	L_ErrScen = T->TrouveTexte("AgriDefSimFrm", "L_ErrScen");
	L_Res1 = T->TrouveTexte("AgriDefSimFrm", "L_Res1");
	L_Res2 = T->TrouveTexte("AgriDefSimFrm", "L_Res2");
	L_SimSur = T->TrouveTexte("AgriDefSimFrm", "L_SimSur");
	L_CestSur = T->TrouveTexte("AgriDefSimFrm", "L_CestSur");
	L_An = T->TrouveTexte("AgriDefSimFrm", "L_An");
}
//--------------------------------------------------------------------------
void TAgriDefSimFrm::IniCaption(void) {
	RGAlea->Caption = LC_RGAlea;
	LabAn0->Caption = LC_LabAn0;
//    LabCalage->Caption=LC_LabCalage;
	AgriDefSimFrm->Caption = LC_AgriDefSimFrm;
	LabPCharge->Caption = T->LC_LabPCharge;
	LabQCharge->Caption = T->LC_LabPCharge;
	LabZone->Caption = T->LC_LabZone;
	GBEnch->Caption = LC_GBEnch;
	LabQExt->Caption = LC_LabQExt;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	LabMoisOuv->Caption = LC_LabMoisOuv;
	LabAnMax->Caption = LC_LabAnMax;
	LabNom->Caption = LC_LabNom;
	BtBnNotes->Caption = T->LC_BtBnNotes;
	GBPrix->Caption = T->LC_GBPrix;
	LabPProduit->Caption = T->LC_LabPProduit;
	LabQProduit->Caption = T->LC_LabPProduit;
	GBQuantite->Caption = T->LC_GBQuantite;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	ChBRepTout->Caption = LC_ChBRepTout;
	GBSerie->Caption = LC_GBSerie;
	LabVariante->Caption = LC_LabVariante;
	RGAlea->Items->Strings[0] = LC_Sans;
	RGAlea->Items->Strings[1] = LC_Avec;
}
//--------------------------------------------
void TAgriDefSimFrm::TexteCaption(void) {
	LC_RGAlea = T->TrouveCaption("AgriDefSim", "LC_RGAlea");
	LC_LabAn0 = T->TrouveCaption("AgriDefSim", "LC_LabAn0");
	LC_LabCalage = T->TrouveCaption("AgriDefSim", "LC_LabCalage");
	LC_AgriDefSimFrm = T->TrouveCaption("AgriDefSim", "LC_AgriDefSimFrm");
	LC_LabPCharge = T->TrouveCaption("CL_Trad", "LC_LabPCharge");
	LC_LabZone = T->TrouveCaption("CL_Trad", "LC_LabZone");
	LC_GBEnch = T->TrouveCaption("AgriDefSim", "LC_GBEnch");
	LC_LabQExt = T->TrouveCaption("AgriDefSim", "LC_LabQExt");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_LabMoisOuv = T->TrouveCaption("AgriDefSim", "LC_LabMoisOuv");
	LC_LabAnMax = T->TrouveCaption("AgriDefSim", "LC_LabAnMax");
	LC_LabNom = T->TrouveCaption("AgriDefSim", "LC_LabNom");
	LC_BtBnNotes = T->TrouveCaption("CL_Trad", "LC_BtBnNotes");
	LC_GBPrix = T->TrouveCaption("CL_Trad", "LC_GBPrix");
	LC_LabPProduit = T->TrouveCaption("CL_Trad", "LC_LabPProduit");
	LC_GBQuantite = T->TrouveCaption("CL_Trad", "LC_GBQuantite");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_ChBRepTout = T->TrouveCaption("AgriDefSim", "LC_ChBRepTout");
	LC_GBSerie = T->TrouveCaption("AgriDefSim", "LC_GBSerie");
	LC_LabVariante = T->TrouveCaption("AgriDefSim", "LC_LabVariante");

	LC_Sans = T->TrouveCaption("AgriDefSim", "LC_Sans");
	LC_Avec = T->TrouveCaption("AgriDefSim", "LC_Avec");

	IniCaption();

}

bool __fastcall TAgriDefSimFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=910;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

