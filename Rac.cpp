//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
//#include "FichierLire.h"
#include "LesVecteurs.hse"

//#include "Forme00.h"
#include "AgriSaisie.h"
#include "ResGraph.h"
#include "Resultat.h"
#include "TVChoixComp.h"
#include "TVChoixEtat.h"
#include "TVChoixComp.h"
#include "TVDico.h"
#include "QRSortieQuant.h"

#include "RacDef.h"

#include "Rac.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRacFrm *RacFrm;
//---------------------------------------------------------------------------
__fastcall TRacFrm::TRacFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TRacFrm::FormActivate(TObject *Sender)
{
	VersLBRac(RacDefFrm->SLstRaccourci);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TRacFrm::VersLBRac(TStringList *sLst) {
	int n;
	CL_EltRac *eltRac;
	LBRac->Items->Clear();
	for (n = 0; n < sLst->Count; n++) {
		eltRac = (CL_EltRac*) RacDefFrm->SLstRaccourci->Objects[n];
		LBRac->AddItem(eltRac->Alias, (TObject*) eltRac);
	}
}
//---------------------------------------------------------------------------
void __fastcall TRacFrm::LBRacClick(TObject *Sender)
{
	int n;
	CL_EltRac *eltRac;
	n=LBRac->ItemIndex;
	eltRac=(CL_EltRac*)LBRac->Items->Objects[n];
	if(eltRac==NULL)
	return;

//    ResultatFrm->RetourDeLBCompAgri(elt->NoFamille,elt->NoCategorie,elt->NoItem);
	TraiterElt(eltRac);

}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TRacFrm::TraiterElt(CL_EltRac *eltRac) {
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
		TVDicoFrm->Visible = false;

	} else if (eltRac->Origine == "Serie comparaison") {
		CL_EtatSortie *serieComp;

		tN = TrouveTVNo1(TVChoixCompFrm->TV, eltRac->Famille, eltRac->Nom);
		serieComp = (CL_EtatSortie*) tN->Data;
		ResultatFrm->RetourDeTVChoixComp(serieComp);
	}
}
//---------------------------------------------------------------------------
int TRacFrm::TrouveLBNo(TListBox *lB, AnsiString as0) {
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
TTreeNode* TRacFrm::TrouveTVNo1(TTreeView *tV, AnsiString as0, AnsiString as1) {
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
TTreeNode* TRacFrm::TrouveTVNo3(TTreeView *tV, CL_EltRac *eltRac) {
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

