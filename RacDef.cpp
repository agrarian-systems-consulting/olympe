//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Forme00.h"
#include "Resultat.h"
#include "TVDico.h"
#include "TVChoixComp.h"
#include "TVChoixEtat.h"
#include "TVChoixComp.h"
#include "TVDico.h"
#include "QRSortieQuant.h"
#include "Main.h"
#include "AgriSaisie.h"

#include "RacDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern CL_ES *ES;
TRacDefFrm *RacDefFrm;
//---------------------------------------------------------------------------
__fastcall TRacDefFrm::TRacDefFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TRacDefFrm::FormCreate(TObject *Sender)
{
	int r;

	SLstRaccourci= new TStringList;
	SLstCode=new TStringList;

	SG->ColCount=7;
	SG->RowCount=21;

	SG->ColWidths[0]=32;
	SG->ColWidths[1]=128;
	SG->ColWidths[2]=128;
	SG->ColWidths[3]=128;
	SG->ColWidths[4]=256;
	SG->ColWidths[5]=32;
	SG->ColWidths[6]=128;

	SG->Cells[1][0]="Origine";
	SG->Cells[2][0]="Famille";
	SG->Cells[3][0]="Categorie";
	SG->Cells[4][0]="Nom";
	SG->Cells[5][0]="Type";
	SG->Cells[6][0]="Alias";

	for(r=0;r<SG->RowCount;r++)SG->Cells[0][r]=r;

}
//---------------------------------------------------------------------------
void __fastcall TRacDefFrm::FormActivate(TObject *Sender)
{
	static bool debut=true;
	if(AgriEnCours==NULL)
	{
		ShowMessage("Choisir un Agri !!");
		return;
	}
	if(debut==false)
	return;
	debut=false;
	Concatener();
	/*
	 ES->IniV_Elt();
	 Forme0Frm->CreeTVToutElt(TV,AgriEnCours,true);//Complet);
	 */
	LireFichier();
	VersSG();

}
//---------------------------------------------------------------------------
void __fastcall TRacDefFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
//	TVDicoFrm->Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TRacDefFrm::Concatener(void) {
	AnsiString as;
//TTreeView *TVSrc;
	TTreeNode *pAll, *tN0;
	AgriSaisieFrm->Calcul0(AgriEnCours);
	Forme0Frm->CreeTVEtat(TVChoixEtatFrm->TV, V_CatEtatSortie, V_EtatSortie);
	Forme0Frm->CreeTVToutElt(TVDicoFrm->TV, AgriEnCours, false);
	ResultatFrm->AjouteEtat(TVDicoFrm->TV);
	Forme0Frm->CreeTVEtat(TVChoixCompFrm->TV, V_CatSerieComp, V_SerieComp);

	TV->Items->Clear();
	pAll = new TTreeNode(TV->Items);

	SLstCode->Clear();
	SLstCode->Sorted = true;

	//Standard  table
	as = AnsiString("T_") + ResultatFrm->BtBnStandard->Caption; //"Standard";
	SLstCode->AddObject(as, (TObject*) STANDARD);

	tN0 = TV->Items->Add(pAll, as);
	ConcatLB(TV, tN0, ResultatFrm->LBSortie);

	//Dictionnaire Graphique
	as = AnsiString("G_") + TVDicoFrm->Caption; //"Dictionnaire";
	SLstCode->AddObject(as, (TObject*) DICO);
	tN0 = TV->Items->Add(pAll, as);
	ConcatTV(TV, tN0, TVDicoFrm->TV);

	//"Serie comparaison";      Comparaison
	as = AnsiString("C_") + TVChoixCompFrm->Caption; //"Serie comparaison";
	SLstCode->AddObject(as, (TObject*) COMPARAISON);
	tN0 = TV->Items->Add(pAll, as);
	ConcatTV(TV, tN0, TVChoixCompFrm->TV);

}
//---------------------------------------------------------------------------
void TRacDefFrm::ConcatTV(TTreeView *tVDest, TTreeNode *tN0, TTreeView *tVSrc) {
	int n;
	AnsiString as;
	void* object;
//TTreeNodes* pT;
	TTreeNode *tN;
	TTreeNode *tN1, *tN2;
	int level;

	for (n = 0; n < tVSrc->Items->Count; n++) {
		tN = tVSrc->Items->Item[n];
		level = tN->Level;
		as = tN->Text;
//        if(as=="[...]");
//        	continue;
		object = tN->Data;
		if (level == 0)
			tN1 = tVDest->Items->AddChildObject(tN0, as, object);
		else if (level == 1)
			tN2 = tVDest->Items->AddChildObject(tN1, as, object);
		else if (level == 2)
			tVDest->Items->AddChildObject(tN2, as, object);
		else
			ShowMessage("level >3");
	}
}
//---------------------------------------------------------------------------
void TRacDefFrm::ConcatLB(TTreeView *tVDest, TTreeNode *tN0, TListBox *lBSrc) {
	int n;
	AnsiString as;
	TObject* object;
	TTreeNode *tN;
	for (n = 0; n < lBSrc->Items->Count; n++) {
		as = lBSrc->Items->Strings[n];
		object = lBSrc->Items->Objects[n];
		tN = tVDest->Items->AddChildObject(tN0, as, object);
		if (n == 9) // Etats de sortie
			ConcatTV(tVDest, tN, TVChoixEtatFrm->TV);
	}
}
//---------------------------------------------------------------------------
void TRacDefFrm::VersSG(void) {
	int r;
	int n;
	CL_EltRac *eltRac;
	SG->RowCount = 21;
	if (SLstRaccourci->Count > SG->RowCount)
		SG->RowCount = SLstRaccourci->Count + 5;
	for (r = 1; r < SG->RowCount; r++)
		SG->Cells[0][r] = r;

	for (n = 0, r = 1; n < SLstRaccourci->Count; n++, r++) {
		eltRac = (CL_EltRac*) SLstRaccourci->Objects[n];
		SG->Objects[0][r] = SLstRaccourci->Objects[n];
		SG->Cells[0][r] = r;
		eltRac->VersSG(SG, r);
	}
}
//---------------------------------------------------------------------------
//  lit seult l'alias
//---------------------------------------------------------------------------
void TRacDefFrm::DeSG(void) {
	int r;
	CL_EltRac *eltRac;
	AnsiString as;
	SLstRaccourci->Clear();
	for (r = 1; r < SG->RowCount; r++) {
		eltRac = (CL_EltRac*) SG->Objects[0][r];
		if (eltRac == NULL)
			continue;
		eltRac->Alias = SG->Cells[6][r];

		SLstRaccourci->AddObject("", (TObject*) eltRac);
	}
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TRacDefFrm::TVChange(TObject *Sender, TTreeNode *Node)
{
	int r; //,c;
	TTreeNode *parent1,*parent2,*parent3;
	CL_EltRac *eltRac;
	AnsiString asParent1,asParent2,asParent3;
	AnsiString as;
	AnsiString asRien="   ";
	int itemIndex;
	if(Node->Level==0)
	return;
	if(Node->getFirstChild()!=NULL)
	return;
	asParent1="";
	asParent2="";
	asParent3="";

	parent1=Node->Parent;
	asParent1=parent1->Text;
	if(Node->Level>=2)
	{
		parent2=parent1->Parent;
		asParent2=parent2->Text;
		if(Node->Level>=3)
		{
			parent3=parent2->Parent;
			asParent3=parent3->Text;
		}
	}
	r=SG->Row;
	if(Node->Level==1) //Standard=0
	{
		eltRac=new CL_EltRac();
		eltRac->Origine=asParent1;

		SLstCode->Find(asParent1,itemIndex);
		eltRac->NoOrigine=(int)SLstCode->Objects[itemIndex];
		eltRac->Type=eltRac->Origine[1];
		eltRac->Nom=TV->Selected->Text;
		eltRac->Alias=TV->Selected->Text;

		SG->Cells[1][r]=eltRac->Origine;
		SG->Cells[4][r]=eltRac->Nom;
		SG->Cells[5][r]=AnsiString(eltRac->Type);
		SG->Cells[6][r]=eltRac->Alias;

	}
	else if(Node->Level==2) // T Serie comparaison
							// Dictionnaire Poste  Bilan  CEG  ....
	{

		eltRac=new CL_EltRac();

		eltRac->Origine=asParent2;
		SLstCode->Find(eltRac->Origine,itemIndex);
		eltRac->NoOrigine=(int)SLstCode->Objects[itemIndex];
		eltRac->Type=eltRac->Origine[1];
		if(eltRac->NoOrigine==DICO)
		{
			eltRac->Famille=asParent1;
			if(eltRac->Famille=="Poste")
			eltRac->NoFamille=POSTE;
			else
			eltRac->Famille=asParent1;
			eltRac->Nom=TV->Selected->Text;
			eltRac->Alias=TV->Selected->Text;

		}
		if(eltRac->NoOrigine==COMPARAISON)
		{
			eltRac->Famille=asParent1;
			eltRac->Nom=TV->Selected->Text;
			eltRac->Alias=TV->Selected->Text;
		}
		SG->Cells[1][r]=eltRac->Origine;
		SG->Cells[2][r]=eltRac->Famille;
		SG->Cells[3][r]=eltRac->Categorie;
		SG->Cells[4][r]=eltRac->Nom;
		SG->Cells[5][r]=AnsiString(eltRac->Type);
		SG->Cells[6][r]=eltRac->Alias;
		/*
		 if(asParent2=="C_Série Comparaisons" )
		 eltRac->NoOrigine=COMPARAISON;
		 else if(asParent2=="G_Dictionnaire" )
		 eltRac->NoOrigine=DICO;
		 eltRac->Famille=asParent1;
		 eltRac->NoFamille=STANDARD;
		 */
	}
	else if(Node->Level==3) // T Standard et Etat de sortie
							// G  Dictionnaire et Indicateur
	{
		eltRac=new CL_EltRac();
		eltRac->Origine=asParent3;
		eltRac->Type=eltRac->Origine[1];
		SLstCode->Find(asParent3,itemIndex);
		eltRac->NoOrigine=(int)SLstCode->Objects[itemIndex];

		eltRac->Famille=asParent2;
		eltRac->NoFamille=ETAT;

		eltRac->Categorie=asParent1;
		eltRac->Nom=TV->Selected->Text;
		eltRac->Alias=TV->Selected->Text;

		SG->Cells[1][r]=eltRac->Origine;
		SG->Cells[2][r]=eltRac->Famille;
		SG->Cells[3][r]=eltRac->Categorie;
		SG->Cells[4][r]=eltRac->Nom;
		SG->Cells[5][r]=AnsiString(eltRac->Type);
		SG->Cells[6][r]=eltRac->Alias;
	}
	/*
	 eltRac->Type=eltRac->Origine[1];

	 SG->Cells[4][r]=TV->Selected->Text;
	 SG->Cells[5][r]=AnsiString(eltRac->Type);
	 SG->Cells[6][r]=TV->Selected->Text;    //alias
	 */
	SG->Objects[0][SG->Row]=(TObject*)eltRac;
	SG->Row++;

	LabelModifie->Visible=true;

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TRacDefFrm::Executer(CL_EltRac *eltRac) {
	int n;
	TTreeNode *tN;
	if (eltRac->Origine == "Standard") {
		if (eltRac->Famille == "  -") {
			n = TrouveLBNo(ResultatFrm->LBSortie, eltRac->Nom);
			ResultatFrm->AffUneSortie(n);
		} else if (eltRac->Famille == "Etats de sortie") {
			CL_EtatSortie *etat;
			tN = TrouveTVNo1(TVChoixEtatFrm->TV, eltRac->Categorie,
					eltRac->Nom);
			etat = (CL_EtatSortie*) tN->Data;
			QRSortieQuantFrm->Etat(etat, ResultatFrm->Agri);

		}
	} else if (eltRac->Origine == "Dictionnaire") {
		CL_Elt *eltAComp; //element A Comparer

		if (eltRac->Famille == "Poste") {
			tN = TrouveTVNo1(TVDicoFrm->TV, eltRac->Famille, eltRac->Nom);
			eltAComp = (CL_Elt*) tN->Data;
			ResultatFrm->RetourDeLBCompAgri(eltAComp->NoFamille,
					eltAComp->NoCategorie, eltAComp->NoItem);
		} else {
			tN = TrouveTVNo3(TVDicoFrm->TV, eltRac);
			eltAComp = (CL_Elt*) tN->Data;
			ResultatFrm->RetourDeLBCompAgri(eltAComp->NoFamille,
					eltAComp->NoCategorie, eltAComp->NoItem);
		}
	} else if (eltRac->Origine == "Serie comparaison") {
		CL_EtatSortie *serieComp;

		tN = TrouveTVNo1(TVChoixCompFrm->TV, eltRac->Famille, eltRac->Nom);
		serieComp = (CL_EtatSortie*) tN->Data;
		ResultatFrm->RetourDeTVChoixComp(serieComp);
	}
}
//---------------------------------------------------------------------------
int TRacDefFrm::TrouveLBNo(TListBox *lB, AnsiString as0) {
	int n;
	AnsiString as;
	for (n = 0; n < lB->Count; n++) {
		as = lB->Items->Strings[n];
		if (as == as0)
			return n;
	}
	return 0;
}
//---------------------------------------------------------------------------
TTreeNode* TRacDefFrm::TrouveTVNo1(TTreeView *tV, AnsiString as0,
		AnsiString as1) {
	int i;
	TTreeNode *tN0, *tN1;
	tN0 = tV->Items->Item[0];
	while (1) {
		if (tN0->Text == as0) {
			for (i = 0; i < tN0->Count; i++) {
				tN1 = tN0->Item[i];
				if (tN1->Text == as1)
					return tN1;
			}
		} else
			tN0 = tN0->getNextSibling();
	}
//    ShowMessage("TrouveTVNo");
}
//---------------------------------------------------------------------------
TTreeNode* TRacDefFrm::TrouveTVNo3(TTreeView *tV, CL_EltRac *eltRac) {
	int i; //,j,k,l;
	TTreeNode *tN0, *tN1, *tN2;
	tN0 = tV->Items->Item[0];
	while (1) {
		if (tN0->Text == eltRac->Famille) {
			tN1 = tN0->Item[0];
			while (1) {
				if (tN1->Text == eltRac->Categorie) {
					for (i = 0; i < tN1->Count; i++) {
						tN2 = tN1->Item[i];
						if (tN2->Text == eltRac->Nom)
							return tN2;
					}
				} else
					tN1 = tN1->getNextSibling();

			}
		} else
			tN0 = tN0->getNextSibling();
	}

//    ShowMessage("TrouveTVNo");
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TRacDefFrm::SGKeyPress(TObject *Sender, char &Key)
{
	int c; //,r;
	c=SG->Col;
//	r=SG->Row;
	if(c!=5) {Key=0;return;}
	LabelModifie->Visible=true;
	/*
	 //G ou T  Graphique Table
	 if(Key=='t'||Key=='T'){Key=0;SG->Cells[c][r]="T";return;}
	 if(Key=='G'||Key=='g'){Key=0;SG->Cells[c][r]="G";return;}
	 Key=0;
	 LabelModifie->Visible=true;
	 */
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TRacDefFrm::BtBnVideToutClick(TObject *Sender)
{
	int r,c;
	int rep;
	rep=MessageBox(Handle," Je supprime TOUT Vous êtes sur ?","SUPPRESSION",MB_YESNO);
//	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDNO)
	return;

	for(r=1;r<SG->RowCount;r++)
	{
		SG->Objects[0][r]=NULL;
		for(c=1;c<SG->ColCount;c++)
		SG->Cells[c][r]="";
	}
	SG->Row=1;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRacDefFrm::BtSupClick(TObject *Sender)
{
	int r,r0,c;
	r0=SG->Row;
	for(r=r0;r<SG->RowCount-1;r++)
	{
		SG->Objects[0][r]=SG->Objects[0][r+1];
		for(c=1;c<SG->ColCount;c++)
		SG->Cells[c][r]=SG->Cells[c][r+1];
	}
	r=SG->RowCount-1;
	for(c=1;c<SG->ColCount;c++)
	SG->Cells[c][r]="";
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRacDefFrm::BtBnClBasClick(TObject *Sender)
{
	int c,r;
	TObject *object;
	AnsiString as;
	r=SG->Row;
	if(r==SG->RowCount) return;

	LabelModifie->Visible=true;
	object=SG->Objects[0][r];
	SG->Objects[0][r]=SG->Objects[0][r+1];
	SG->Objects[0][r+1]=object;
	for(c=1;c<SG->RowCount;c++)
	{
		as=SG->Cells[c][r];
		SG->Cells[c][r]=SG->Cells[c][r+1];
		SG->Cells[c][r+1]=as;
	}
	SG->Row++;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRacDefFrm::BtBnClHautClick(TObject *Sender)
{
	int c,r;
	TObject *object;
	AnsiString as;
	r=SG->Row;
	if(r==1) return;

	LabelModifie->Visible=true;
	object=SG->Objects[0][r];
	SG->Objects[0][r]=SG->Objects[0][r-1];
	SG->Objects[0][r-1]=object;
	for(c=1;c<SG->RowCount;c++)
	{
		as=SG->Cells[c][r];
		SG->Cells[c][r]=SG->Cells[c][r-1];
		SG->Cells[c][r-1]=as;
	}
	SG->Row--;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRacDefFrm::BtBnSaveClick(TObject *Sender)
{
	EcrireFichier();
}
//---------------------------------------------------------------------------
void TRacDefFrm::TailleSG(int r) {
	SG->Row++;
	if (r > SG->RowCount - 3) {
		SG->RowCount++;
		SG->Cells[0][r] = r;
		SG->Cells[0][r + 1] = r + 1;
		SG->Objects[0][r] = NULL;
		SG->Objects[0][r + 1] = NULL;
	}
}

//---------------------------------------------------------------------------
void TRacDefFrm::EcrireFichier(void) {
	int n; //,i,j;
	CL_EltRac *eltRac;

	char* nomFich;
	AnsiString as;
	as = MainForm->AsDirOlympe + "\\Raccourci.csv";
	nomFich = as.c_str();
//	nomFich="c://OlympeInter//Wag2009//Raccourci.csv";

	ofstream fichier(nomFich);
	DeSG();
	n = SLstRaccourci->Count;
	fichier << "Raccourcis" << ";\n";

	fichier << "nbRaccourci" << ";" << n << ";\n";

	for (n = 0; n < SLstRaccourci->Count; n++) {
		eltRac = (CL_EltRac*) SLstRaccourci->Objects[n];
		fichier << eltRac->Origine.c_str() << ";";

		fichier << eltRac->Famille.c_str() << ";";
		fichier << eltRac->Categorie.c_str() << ";";
		fichier << eltRac->Nom.c_str() << ";";
		fichier << eltRac->Alias.c_str() << ";"; //Alias
		fichier << eltRac->Type << ";"; //Alias

		fichier << eltRac->NoOrigine << ";";
		fichier << eltRac->NoFamille << ";\n";

	}

	fichier.close();
	ShowMessage(AnsiString(nomFich) + "   Stocke");
}
//---------------------------------------------------------------------------
void TRacDefFrm::LireFichier(void) {
	char* nomFich;
	int n, nb; //,nCar;

	AnsiString as;
	FILE *fichier;
	char chaine[1000];
	char *ptr;
	CL_EltRac *eltRac;
	as = MainForm->AsDirOlympe + "\\Raccourci.csv";
	nomFich = as.c_str();

	fichier = fopen(nomFich, "r");
	if (fichier == NULL)
		return;

	fgets(chaine, 1000, fichier);
	ptr = strtok(chaine, ";");
	as = ptr;
	if (as != "Raccourcis") {
		ShowMessage("Ce n'est pas le bon fichier");
		return;
	}
	fgets(chaine, 1000, fichier);

	ptr = strtok(chaine, ";");
	ptr = strtok(NULL, ";");
	nb = atoi(ptr);

	SLstRaccourci->Clear();
	for (n = 0; n < nb; n++) {
		eltRac = new CL_EltRac();
		fgets(chaine, 1000, fichier);

		ptr = strtok(chaine, ";");
		eltRac->Origine = ptr;

		ptr = strtok(NULL, ";");
		eltRac->Famille = ptr;

		ptr = strtok(NULL, ";");
		eltRac->Categorie = ptr;

		ptr = strtok(NULL, ";");
		eltRac->Nom = ptr;

		ptr = strtok(NULL, ";");
		eltRac->Alias = ptr;

		ptr = strtok(NULL, ";");
		eltRac->Type = ptr[0];

		ptr = strtok(NULL, ";");
		eltRac->NoOrigine = atoi(ptr);

		ptr = strtok(NULL, ";");
		eltRac->NoFamille = atoi(ptr);

		SLstRaccourci->AddObject("", (TObject*) eltRac);
	}
	fclose(fichier);
}

//-----------------------------------------------------------------------------
void __fastcall TRacDefFrm::SGClick(TObject *Sender)
{
	int r;
	r=SG->Row;
	r=r;
}
//---------------------------------------------------------------------------

void __fastcall TRacDefFrm::BtBnTestClick(TObject *Sender)
{
	int n;
	CL_EltRac* eltRac;
//    RacDefFrm->LireFichier();
	DeSG();
	ResultatFrm->LBRac->Items->Clear();
	for(n=0;n<SLstRaccourci->Count;n++)
	{
		eltRac=(CL_EltRac*)RacDefFrm->SLstRaccourci->Objects[n];
		ResultatFrm->LBRac->AddItem(eltRac->Alias,(TObject*)eltRac);
	}
	ResultatFrm->Show();
}
//---------------------------------------------------------------------------

