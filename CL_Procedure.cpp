//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <sysvari.h>
#include <vector.h>
using namespace std;
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierEcrireXml.h"
#include "Compilateur.h"
#include "CL_Trad.h"

#include "CL_Procedure.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
extern CL_Xml *Xml;
extern CL_Trad *T;

//------------------------------------------------------------------------------
//----------------------------------------------------------------------------
CL_Procedure::CL_Procedure() {
	Supprimable = true;
	V_EltP = new CL_Vecteur<CL_EltProc>;
}
//----------------------------------------------------------------------------
CL_Procedure::CL_Procedure(AnsiString nom) {
	Nom = nom;
	Supprimable = true;
	V_EltP = new CL_Vecteur<CL_EltProc>;
}
//----------------------------------------------------------------------------
CL_Procedure::CL_Procedure(CL_Procedure *source) {
	Supprimable = true;
	Nom = source->Nom;
	AsExe = source->AsExe;
	AsFichier = source->AsFichier;
	Categorie = source->Categorie;
	V_EltP = new CL_Vecteur<CL_EltProc>(source->V_EltP);
}
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
//lire  et ecrire procedure
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CL_Procedure::LireXml(_di_IXMLNode brancheProc) {
	int i, n;
	AnsiString s, sNom, sCat, sFam, sNat;
	_di_IXMLNode feuille;
	CL_EltProc *eltP;

	n = brancheProc->ChildNodes->Count;
	for (i = 0; i < n; i++) {
		feuille = brancheProc->ChildNodes->GetNode(i);
		s = feuille->GetLocalName();
		if (s == "fichiers") {
			AsExe = feuille->Attributes["exe"];
			AsFichier = feuille->Attributes["donnees"];
		} else if (s == "elt") {
			eltP = new CL_EltProc();
			eltP->Nom = feuille->Attributes["nom"];
			eltP->NomCategorie = feuille->Attributes["categorie"];
			eltP->NomFamille = feuille->Attributes["famille"];
			eltP->NomNature = feuille->Attributes["nature"];

			V_EltP->ins(eltP);
		}
	}
}
//-----------------------------------------------------------------------------
// ATTENTION  excel ne reconnait pas les blancs : Olympe en cours
// ne marche pas il prend "en" comme le nom du fichier de données
//-----------------------------------------------------------------------------
void CL_Procedure::Executer(vector<CL_Agriculteur*> vAgri) {
	unsigned int i;
	int n, nTrouve;
	bool rep;
	AnsiString as, asExe, ligneCommande;
	CL_Agriculteur *agri;
	vector<CL_EltProc*> vEltProc;

	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	vEltProc.clear();
	nTrouve = 0;
	for (i = 0; i < vAgri.size(); i++) {
		agri = vAgri[i];
		n = TrouveValeur(agri, vEltProc);
		nTrouve += n;
	}
	if (nTrouve == 0) {
		ShowMessage(T->L_Proc_PasDon); //"Pas de données Je NE lance PAS" );
		return;
	}

	rep = EcrireDonnees(vEltProc);
	if (rep == false)
		return;

	ligneCommande = AsExe + "   " + AsFichier; //151106
	rep = CreateProcess(AsExe.c_str(),
			ligneCommande.c_str(), //AsFichier.c_str(),
			0, 0, false, DETACHED_PROCESS, 0, 0, &siStartupInfo,
			&piProcessInfo);

	if (rep == false) {
		as = T->L_Probleme + AsExe + T->L_Inconnu;
		//as=AnsiString("Problème  ")+AsExe+" Inconnu";
		ShowMessage(as);
	}
	WaitForSingleObject(piProcessInfo.hProcess, INFINITE);
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);

	LireDonnees(vEltProc);
}
//---------------------------------------------------------------------------
//--------------TrouveValeur-------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int CL_Procedure::TrouveValeur(CL_Agriculteur *agri,
		vector<CL_EltProc*> &vEltProc) {
	int n;
	int nTrouve;
	CL_EltProc *eltP, *eltPBis;
	nTrouve = 0;
	for (n = 0; n < V_EltP->Nbelt; n++) {
		eltP = V_EltP->Vecteur[n];

		//eltP->Agri=agri;
		eltP->Type = ' ';
		eltP->Valeur = NULL;
		eltP->Formule = NULL;
		eltP->Ensemble = NULL;

		if (eltP->NomFamille == "Assolement")
			nTrouve += TrValAtelier(agri, agri->V_Culture, eltP);
		else if (eltP->NomFamille == "Animaux")
			nTrouve += TrValAtelier(agri, agri->V_Animaux, eltP);

		else if (eltP->NomFamille == "Produits")
			nTrouve += TrValFormule(agri, agri->V_Produits, eltP);
		else if (eltP->NomFamille == "Charges")
			nTrouve += TrValFormule(agri, agri->V_Charges, eltP);

		else if (eltP->NomFamille == "Variables")
			nTrouve += TrValItem(agri, agri->V_Variable, eltP);

		else if (eltP->NomFamille == "Charges Structure")
			nTrouve += TrValFormule(agri, agri->V_ChStruct, eltP);

		else if (eltP->NomFamille == "Recettes Diverses")
			nTrouve += TrValFormule(agri, agri->V_RecDiv, eltP);
		else if (eltP->NomFamille == "DépensesDiverses")
			nTrouve += TrValFormule(agri, agri->V_DepDiv, eltP);

		else if (eltP->NomFamille == "Négatives")
			nTrouve += TrValFormule(agri, agri->V_ExtNeg, eltP);
		else if (eltP->NomFamille == "Positives")
			nTrouve += TrValFormule(agri, agri->V_ExtPos, eltP);

		else if (eltP->NomFamille == "Recettes Privées")
			nTrouve += TrValFormule(agri, agri->V_RecFam, eltP);
		else if (eltP->NomFamille == "Dépenses Privées")
			nTrouve += TrValFormule(agri, agri->V_DepFam, eltP);

		else if (eltP->NomFamille == "Immobilisation")
			nTrouve += TrValGlobal(agri, "LstNomInvSom", eltP);
		else if (eltP->NomFamille == "Financement")
			nTrouve += TrValGlobal(agri, "LstNomFinSom", eltP);
		else if (eltP->NomNature == "Effectifs et Assolements")
			nTrouve += TrEffAssol(eltP);
		else
			ShowMessage("CL_Procedure::CompleteElt A finir");

		if (eltP->Valeur || eltP->Valeur || eltP->Formule || eltP->Ensemble) {
			eltPBis = new CL_EltProc(eltP);
			eltPBis->Agri = agri;
			vEltProc.push_back(eltPBis);
		}
	}
	return nTrouve;
}
//---------------------------------------------------------------------------
int CL_Procedure::TrValAtelier(CL_Agriculteur *agri,
		CL_Vecteur<CL_Valeur>*vecteur, CL_EltProc *eltP) {
	int i;
	CL_Valeur *valeur;
	eltP->Type = ' ';
	for (i = 0; i < vecteur->Nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		if (eltP->Nom == valeur->Atelier->Nom
				&& eltP->NomCategorie == valeur->Atelier->Categorie->Nom) {
			eltP->Valeur = valeur->Valeur;
			return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
int CL_Procedure::TrValItem(CL_Agriculteur *agri, CL_Vecteur<CL_Valeur>*vecteur,
		CL_EltProc *eltP) {
	int i;
	CL_Valeur *valeur;
	eltP->Type = ' ';
	for (i = 0; i < vecteur->Nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		if (eltP->Nom == valeur->Item->Nom
				&& eltP->NomCategorie == valeur->Item->Categorie->Nom) {
			eltP->Valeur = valeur->Valeur;
			return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
int CL_Procedure::TrValFormule(CL_Agriculteur *agri,
		CL_Vecteur<CL_Formule>*vecteur, CL_EltProc *eltP) {
	int i;
	CL_Formule *formule;
//  je n'envoie que les formules qui contiennent seulement des nombres
	eltP->Type = 'F';
	for (i = 0; i < vecteur->Nbelt; i++) {
		formule = vecteur->Vecteur[i];
		if (SeultNum(formule) == false)
			continue;

		if (eltP->Nom == formule->Item->Nom
				&& eltP->NomCategorie == formule->Item->Categorie->Nom) {
			eltP->Valeur = formule->Valeur;
			eltP->Formule = formule;
			return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
//seulement les  formules avec des nombres peuvent etre modifiées
//---------------------------------------------------------------------------
bool CL_Procedure::SeultNum(CL_Formule *formule) {
	int n, i;
	CL_Prog *prog;
	CL_Arbre *arbre;

	for (n = 0; n < N_X; n++) {
		prog = formule->LesProg[n];
		if (prog == NULL)
			continue;
		if (prog->Reseau != NULL)
			return false;
		arbre = prog->Arbre;
		for (i = 0; i < arbre->BrancheX; i++) {
			if (arbre->LesBranches->type != NOMBRE)
				return false;
		}
	}
	return true;
}
//---------------------------------------------------------------------------
int CL_Procedure::TrValGlobal(CL_Agriculteur *agri, AnsiString NomDeLaListe,
		CL_EltProc *eltP) {
	int i;
	int n;
	int nfN_Xp1;
	CL_FN_Xp1 *fN_Xp1;
	TStringList *lst;
	CL_Vecteur<CL_FN_Xp1> *vecteur;

	eltP->Type = ' ';

	if (NomDeLaListe == AnsiString("LstNomFinSom")) {
		vecteur = agri->V_FinSom;
		nfN_Xp1 = 8;
	} else if (NomDeLaListe == AnsiString("LstNomInvSom")) {
		vecteur = agri->V_InvSom;
		nfN_Xp1 = 7;
	}
	if (vecteur->Nbelt == 0) {
		for (i = 0; i < nfN_Xp1; i++) {
			fN_Xp1 = new CL_FN_Xp1();
			vecteur->ins(fN_Xp1);
		}
	}

	n = LstNom->IndexOf(NomDeLaListe);
	lst = (TStringList*) LstNom->Objects[n];

	for (i = 0; i < lst->Count; i++) {
		if (eltP->Nom == lst->Strings[i]) {
			fN_Xp1 = vecteur->Vecteur[i];
			eltP->Valeur = fN_Xp1->Valeur;
			return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
int CL_Procedure::TrEffAssol(CL_EltProc *eltP) {
	int i;
	CL_Ensemble *ensemble;

	eltP->Type = 'E'; //Ensemble

	for (i = 0; i < V_Ensemble->Nbelt; i++) {
		ensemble = V_Ensemble->Vecteur[i];
		if (ensemble->Nom == eltP->Nom) {
			eltP->Ensemble = ensemble;
			return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
//----------------EcrireDonnees----------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// envoi pour traitement par excel ou .exe
// ATTENTION  dans la ligne de commande le blanc est séparateur
// excel Olympe en cours posera problème
//---------------------------------------------------------------------------
bool CL_Procedure::EcrireDonnees(vector<CL_EltProc*> vEltProc) {
	unsigned int i, n;
	CL_EltProc *eltP;
	AnsiString nomV; //nom de l'agri + n°Variante
	ofstream outfile(AsFichier.c_str());
	if (vEltProc.size() < 1) {
		ShowMessage("Aucune Donnée !  ");
		return false;
	}
	//dans eltP il y a ->Agri
	eltP = vEltProc[0];
	EcrireEnTete(outfile, eltP);
	for (i = 0; i < vEltProc.size(); i++) {
		eltP = vEltProc[i];

		if (eltP->Ensemble) {
			EcrireEnsemble(eltP->Ensemble, outfile);
			continue;
		}
		if (eltP->Valeur == NULL)
			continue;
		nomV = eltP->Agri->NomV();
		outfile << nomV.c_str() << ";"; //1
		outfile << eltP->Nom.c_str() << ";"; //2
		outfile << eltP->NomCategorie.c_str() << ";"; //3
		outfile << eltP->NomFamille.c_str() << ";"; //4
		outfile << eltP->NomNature.c_str() << ";"; //5
		for (n = 0; n < N_X; n++)
			outfile << eltP->Valeur[n] << ";";
		outfile << endl;
	}
	outfile.close();
//    fclose(fichier);
	return true;
}
//---------------------------------------------------------------------------
void CL_Procedure::EcrireEnTete(ofstream &outfile, CL_EltProc *eltP) {
	int n;
	CL_Agriculteur *agri = eltP->Agri;
	outfile << "Agri_variante" << ";"; //1
	outfile << "Nom" << ";"; //2
	outfile << "Categorie" << ";"; //3
	outfile << "Famille" << ";"; //4
	outfile << "Nature" << ";"; //5
	for (n = 0; n < N_X; n++)
		outfile << agri->DefSim->An_0 + n << ";";
	outfile << endl;
}
//---------------------------------------------------------------------------
void CL_Procedure::EcrireNom(AnsiString as, ofstream &outfile) {
	as = as.Trim();
	if (as == "")
		outfile << "  ;";
	else
		outfile << as.c_str() << ";";
}
//---------------------------------------------------------------------------
void CL_Procedure::EcrireEnsemble(CL_Ensemble *ensemble, ofstream &outfile) {
	int i, j, n;
	CL_AgriEff *agriEff;
	CL_Agriculteur *agri;
	CL_Valeur *valeur;
	AnsiString nomV; //nom de l'agri + n°Variante
	//effectifs
	for (i = 0; i < ensemble->V_AgriEff->Nbelt; i++) {
		agriEff = ensemble->V_AgriEff->Vecteur[i];
		nomV = agriEff->Agri->NomV(); //nom de l'agri + n° variante

		outfile << nomV.c_str() << "  ;";
		outfile << ensemble->Nom.c_str() << "  ;";
		outfile << "Effectif" << "  ;";
		outfile << " " << "  ;";
		outfile << "Ensemble" << "  ;";
		for (n = 0; n < N_X; n++)
			outfile << agriEff->Effectif[n] << "  ;";
		outfile << endl;
	}
	//Assolement
	for (i = 0; i < ensemble->V_AgriEff->Nbelt; i++) {
		agriEff = ensemble->V_AgriEff->Vecteur[i];
		agri = agriEff->Agri;
		nomV = agriEff->Agri->NomV();

		for (j = 0; j < agri->V_Culture->Nbelt; j++) {
			valeur = agri->V_Culture->Vecteur[j];
			outfile << nomV.c_str() << "  ;";
			outfile << valeur->Atelier->Nom.c_str() << ";"; //2
			outfile << valeur->Atelier->Categorie->Nom.c_str() << ";"; //3
			outfile << "Assolement" << ";"; //4
			outfile << "Production" << ";"; //5
			for (n = 0; n < N_X; n++)
				outfile << valeur->Valeur[n] << "  ;";
			outfile << endl;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------LireDonnees-------------------------------------------------------
//---------------------------------------------------------------------------
void CL_Procedure::LireDonnees(vector<CL_EltProc*> vEltProc) {
	unsigned int i;
//ifstream infile(AsFichier.c_str());
//int n;
	char chaine[500];
//float val;
	FILE *fichier;
	AnsiString s;
	CL_EltProc *eltP;
	fichier = fopen(AsFichier.c_str(), "r");
	if (fichier == NULL) {
		ShowMessage(
				AnsiString("Impossible d'ouvrir  ") + AsFichier
						+ " il doit déjà être ouvert !");
		return;
	}
	fgets(chaine, 500, fichier);
	for (i = 0; i < vEltProc.size(); i++) {
		eltP = vEltProc[i];
		switch (eltP->Type) {
		case ' ':
			LireValeur(fichier, eltP->Valeur);
			break;
		case 'F':
			LireFormule(fichier, eltP->Formule);
			break;
		case 'E':
			LireEnsemble(fichier, eltP->Ensemble);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void CL_Procedure::LireValeur(FILE *fichier, float *valeur) {
	int c, n;
	char chaine[500];
	AnsiString s;
	char *p;

	fgets(chaine, 500, fichier);
	p = strtok(chaine, ";");
	c = 0;
	n = 0;
	while (p) {
		if (c == 15)
			break; // 5 chaines d'identifiant 10 valeurs
		if (c >= 5) {
			s = AnsiString(p);
			s = s.Trim();
			if (s == NULL)
				break; //à la fin d="\n" ->s=NULL
			valeur[n] = (float) s.ToDouble();
			n++;
		}
		p = strtok(NULL, ";");
		c++;
	}
}
//---------------------------------------------------------------------------
void CL_Procedure::LireFormule(FILE *fichier, CL_Formule *formule) {
	int n;
	float valeur[N_X];
	CL_Prog *prog;
	LireValeur(fichier, valeur);

	for (n = 0; n < N_X; n++) {
		prog = new CL_Prog(valeur[n]);
		formule->LesProg[n] = prog;
		formule->Valeur[n] = valeur[n];
	}
	/*
	 prog->Arbre=new CL_Arbre(1,10);
	 prog->Arbre->LesBranches[0].code=NOMBRE;
	 prog->Arbre->LesBranches[0].arg[0]=-1;
	 prog->Arbre->LesBranches[0].arg[1]=-1;
	 prog->Arbre->LesBranches[0].arg[2]=-1;
	 prog->Arbre->LesBranches[0].type=NUM;

	 prog->Arbre->LesBranches[0].valeur=valeur[n];
	 prog->Arbre->BrancheX=1;
	 formule->LesProg[n]=prog;

	 formule->Valeur[n]=valeur[n];
	 }
	 */
}
//---------------------------------------------------------------------------
void CL_Procedure::LireEnsemble(FILE *fichier, CL_Ensemble *ensemble) {
	int i, j;
	CL_AgriEff *agriEff;
	CL_Agriculteur *agri;
	CL_Valeur *valeur;
	float effectif[N_X];
	for (i = 0; i < ensemble->V_AgriEff->Nbelt; i++) {
		agriEff = ensemble->V_AgriEff->Vecteur[i];
		//LireValeur(fichier,(float*)agriEff->Effectif);
		LireValeur(fichier, effectif);
		for (j = 0; j < N_X; j++)
			agriEff->Effectif[j] = effectif[j];
	}
	//Assolement
	for (i = 0; i < ensemble->V_AgriEff->Nbelt; i++) {
		agriEff = ensemble->V_AgriEff->Vecteur[i];
		agri = agriEff->Agri;
		for (j = 0; j < agri->V_Culture->Nbelt; j++) {
			valeur = agri->V_Culture->Vecteur[j];
			LireValeur(fichier, valeur->Valeur);
		}
	}
}

//2703

//---------------------------------------------------------------------------
void CL_Procedure::EcrireXml(_di_IXMLNode brancheCat, int p) {
	int pX;
	int e, eX, n;
	AnsiString s, sNom, sCat, sFam, sNat;
	_di_IXMLNode brancheProc, racine, feuille;
	CL_EltProc *eltP;

	pX = brancheCat->ChildNodes->GetCount();

	// je rajoute dans la categorie
	if (p < pX)
		brancheProc = brancheCat->ChildNodes->GetNode(p);
	else
		brancheProc = brancheCat->AddChild("procedure");

	brancheProc->SetAttribute("nom", Nom);

	eX = brancheProc->ChildNodes->GetCount();
	if (eX > 0)
		feuille = brancheProc->ChildNodes->GetNode(0);
	else
		feuille = brancheProc->AddChild("fichiers");

	feuille->SetAttribute("exe", AsExe);
	feuille->SetAttribute("donnees", AsFichier);

	for (n = 0, e = 1; n < V_Elt->Nbelt; n++, e++) {
		eltP = V_EltP->Vecteur[n];
		if (e < eX)
			feuille = brancheProc->ChildNodes->GetNode(e);
		else
			feuille = brancheProc->AddChild("elt");
		feuille->SetAttribute("nom", eltP->Nom);
		feuille->SetAttribute("categorie", eltP->NomCategorie);
		feuille->SetAttribute("famille", eltP->NomFamille);
		feuille->SetAttribute("nature", eltP->NomNature);
	}
}
//---------------------------------------------------------------------------
void CL_Procedure::EcrireXmlTxt(ofstream &fichier) {
	int n;
	AnsiString s, sNom, sCat, sFam, sNat;
	_di_IXMLNode brancheProc, racine, feuille;
	CL_EltProc *eltP;
	Xml->baliseDebut(fichier, "procedure", "nom", Nom);
	fichier << "<fichiers  ";
	Xml->ecrire(fichier, "exe", AsExe);
	Xml->ecrire(fichier, "donnees", AsFichier);
	fichier << "/>" << endl;

	for (n = 0; n < V_EltP->Nbelt; n++) {
		eltP = V_EltP->Vecteur[n];
		fichier << "<elt ";
		Xml->ecrire(fichier, "nom", eltP->Nom);
		Xml->ecrire(fichier, "categorie", eltP->NomCategorie);
		Xml->ecrire(fichier, "famille", eltP->NomFamille);
		Xml->ecrire(fichier, "nature", eltP->NomNature);
		fichier << "/>" << endl;
	}
	fichier << "</procedure>" << endl;
}

//---------------------------------------------------------------------------
void CL_Procedure::Afficher(TEdit *EdProc, TEdit *EdExe, TEdit* EdFichier,
		TStringGrid *grille) {
	int n, row;
	CL_EltProc *eltP;

	EdProc->Text = Nom; //nom catégorie
	EdExe->Text = AsExe;
	EdFichier->Text = AsFichier;

	for (n = 0, row = 1; n < V_EltP->Nbelt; n++, row++) {
		eltP = V_EltP->Vecteur[n];

		grille->Cells[0][row] = eltP->Nom;
		if (eltP->NomCategorie != "")
			grille->Cells[1][row] = eltP->NomCategorie;
		if (eltP->NomFamille != "")
			grille->Cells[2][row] = eltP->NomFamille;
		if (eltP->NomNature != "")
			grille->Cells[3][row] = eltP->NomNature;

		if (eltP->Valeur)
			grille->Objects[0][row] = (TObject*) eltP->Valeur;
	}
	grille->RowCount = row + 2;
	grille->Row = 1;
}
//---------------------------------------------------------------------------
void CL_Procedure::LireGrille(TEdit *EdProc, TEdit *EdExe, TEdit* EdFichier,
		TStringGrid *grille) {
	int row;
	CL_EltProc *eltP;

	Nom = EdProc->Text;
	AsExe = EdExe->Text;
	AsFichier = EdFichier->Text;
	V_EltP->vide(); //purge(); ??
	for (row = 1; row < grille->RowCount; row++) {
		if (grille->Cells[0][row].Length() == 0)
			continue;
		eltP = new CL_EltProc();

		eltP->Nom = grille->Cells[0][row];
		eltP->NomCategorie = grille->Cells[1][row];
		eltP->NomFamille = grille->Cells[2][row];
		eltP->NomNature = grille->Cells[3][row];

		V_EltP->ins(eltP);
	}
}
/*
 L_Proc_PasDon=      "Pas de données Je NE lance PAS";
 L_Probleme=         " Problème ";
 L_Inconnu=          " Inconnu  ";

 */
