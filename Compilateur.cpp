//---------------------------------------------------------------------------
#include <vcl.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "Erreur.h"
#include "Main.h"

#include "Compilateur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//   Compilateur

//-----------------------------------------------------------------------------
/*
 GRAMMAIRE
 instruction    : expression_add
 | expression_si
 | affectation

 expression_si  :SI (condition_OU ) suite_si [SINON suite_si]

 suite_si       : expression_si
 | affectation

 affectation    : INDIC= expression_add

 expression_add :expression_mul <op_add expression_mul >
 op_add         : + | -
 expression_mul :expression_num <op_mul expression_num >
 op_mul         : * | \
expression_num : (expression_add)
 | NOMBRE <%>
 | un_Identificateur

 un_Identificateur : IDENT [ (un_exercice) ]
 un_exercice       : N [op_add NOMBRE ]


 condition_OU   : condition_ET < OU condition_ET >
 condition_ET   : expression_comp < ET expression_comp >
 expression_comp: expression_add < op_comp  expression_add >
 op_comp        : > | < | >= | <= | # | <> | =


 Exemple
 Prime
 si (vache <20)           Prime=vache*250
 sinon si (vache <50)     Prime=20*250+(vache-20)*150
 sinon                    Prime=9500
 numero branche
 code   r1     r2      apG  apD
 0  SI     -1      x       1     2
 1  ID      x      x       6
 2  SI     -1      x       3     4
 3  ID      x      x       5
 4  ID      x      x       5
 5  PONT   -1     -1       6
 6  PONT   -1     -1      -1
 7  ID      x      x      -1    -1

 */

//-----------------------------------------------------------------------------
float CL_Compil::DepouilleFormule(CL_Agriculteur *agri, int an, char *flot) {
//a supprimer voir AgriSaisie
	return 0.;
}
//-----------------------------------------------------------------------------
void CL_Compil::Compiler(char *flot) {
	AnsiString date;
	TDateTime time;
	ofstream outfile("compil.txt");

//    TestCompil=true;
	TestCompil = false;
	if (TestCompil == true) {

		time = TDateTime::CurrentDateTime();
		date = time.DateTimeString();

		outfile << date.c_str() << endl;
		outfile << endl;
		outfile << flot << endl;

	}
	Flot = flot;
	ErreurFrm->Edit->Clear();
	ErreurFrm->Edit->Text = (char*) Flot;
	//en test
	if (EstInitialise == false) {
		IniLexique();
		Arbre = new CL_Arbre();
		Reseau = new CL_Reseau();
	}
	Erreur = false;
	Valeur = 0;

	Pos = 0;

	Reseau->MailleX = 0;
	Arbre->BrancheX = 0;

	instruction(outfile);
	// Impression test

	if (TestCompil == true) {
		if (Arbre->BrancheX)
			ecrireArbre(outfile);
		if (Reseau->MailleX)
			ecrireReseau(outfile);
		outfile.close();
		ShowMessage("Arbre est écrit");
	}
}
//-----------------------------------------------------------------------------
void CL_Compil::instruction(ofstream &outfile) {
	int noBranche;
	LeMot = analex();
	if (TestCompil == true)
		impLeMot("instruction", outfile);

	switch (LeMot) {
	case 0:
		return;
	case SI:
		LeMot = analex(); //je lis LeMot ce doit être (  verif à faire dans blocSI
		if (TestCompil == true)
			impLeMot("instruction", outfile);
		blocSI(-1, outfile); // A faire
		break;
	default:
		noBranche = expressionAdd(outfile);
		if (Erreur)
			return;
		if (Arbre->LesBranches[noBranche].type != NUM)
			erreur("mauvaise définition d'indicateur");
	}
	if (Flot[Pos] != 0) {
		ErreurFrm->Edit->Lines->Add(" le texte n'a pas été lu jusqu'au bout");
		Erreur = true;
		ErreurFrm->Show();
	}

}
//-----------------------------------------------------------------------------
//  formule de calcul
//-----------------------------------------------------------------------------

// ------------------------------------------------------------------------
// expression_add() : expression_mul < op_add expression_mul >
// ------------------------------------------------------------------------
int CL_Compil::expressionAdd(ofstream &outfile) {
	int op_add;
	int typeG, typeD, expG, expD;

	expG = expressionMul(outfile);
	if (Erreur)
		return (ERREUR);
	typeG = Arbre->LesBranches[expG].type;

	while (LeMot == '+' || LeMot == '-') {
		op_add = LeMot;
		if (typeG != NUM)
			return erreur("expression incorrecte 1");
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionAdd", outfile);

		expD = expressionMul(outfile);
		if (Erreur)
			return (ERREUR);
		typeD = Arbre->LesBranches[expD].type;
		switch (typeD) {
		case NUM:
			break;
		default:
			return erreur("expression incorrecte 2");
		}
		expG = stockBranche(op_add, expG, expD, -1, typeG);
	}
	return (expG);
}
// ------------------------------------------------------------------------
// expression_mul() : operande < op_mul operande >
// ------------------------------------------------------------------------
int CL_Compil::expressionMul(ofstream &outfile) {
	int op_mul;
	int expG, expD;
//ernfatal(NON,"expression_mul");
	expG = expressionNum(outfile);
	if (Erreur)
		return (ERREUR);

	while (LeMot == '*' || LeMot == '/') {
		if (Arbre->LesBranches[expG].type != NUM)
			return erreur("expression incorrecte 3");
		op_mul = LeMot;
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionMul", outfile);
		expD = expressionNum(outfile);
		if (Erreur)
			return (ERREUR);
		if (Arbre->LesBranches[expD].type != NUM)
			return erreur("expression incorrecte 4");

		expG = stockBranche(op_mul, expG, expD, -1, NUM);
	}

	return (expG);
}
// ------------------------------------------------------------------------
/* expressionNum()

 expression_num        : ( expression_add )
 | MUNAIRE expression_num
 | valeur_num
 | unIdent
 | SIGMA
 | TOTSUR

 */
// ------------------------------------------------------------------------------
int CL_Compil::expressionNum(ofstream &outfile) {
	int branche, code;
	branche = -1;
	code = LeMot;
	switch (code) {
	case IDENT:
		branche = unIdent(outfile);
		if (Erreur)
			return (ERREUR);
		return branche;

	case SIGMA:
		branche = unTotal(outfile);
		if (Erreur)
			return (ERREUR);
		return branche;

	case TOTSUR:
		branche = stockBranche(TOTSUR, branche, -1, -1, NUM);
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("Total_Culture", outfile);
		return branche;

	case '(':
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionNum", outfile);
		branche = expressionAdd(outfile);
		if (Erreur)
			return (ERREUR);
		if (LeMot != ')')
			return erreur("manque ')'  ");
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionNum", outfile);
		return (branche);

	case LOG: //log(expressionADD)
	case EXP:
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionNum", outfile);

		branche = expressionNum(outfile); // ( exp_mul  ) 
		if (Erreur)
			return (ERREUR);

		branche = stockBranche(code, branche, -1, -1, NUM);
		return (branche);

	case '-': //   Moins unaire
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionNum", outfile);
		branche = expressionNum(outfile);
		if (Erreur)
			return (ERREUR);
		if (Arbre->LesBranches[branche].type != NUM)
			return erreur("expression incorrecte 6");
		branche = stockBranche(MUNAIRE, branche, -1, -1, NUM);
		return (branche);

	case NOMBRE: // numerique
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionNum", outfile);
		if (LeMot == '%') {
			//Valeur=Valeur/100.;
			branche = stockBranche(NOMBRE, '%', -1, -1, NUM);
			LeMot = analex();
			if (TestCompil == true)
				impLeMot("expressionNum", outfile);
		} else
			branche = stockBranche(NOMBRE, -1, -1, -1, NUM);
		return (branche);

	case 'N': // n° année
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionNum", outfile);
		branche = stockBranche('N', -1, -1, -1, NUM);
		return (branche);

	case AN: // n° année
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionNum", outfile);
		branche = stockBranche(AN, -1, -1, -1, NUM);
		return (branche);

	case 0:
		return 0;

	default:
		return erreur("expression incorrecte 7");
	}
//LeMot = analex();

//return( branche ); ?????
}
// ------------------------------------------------------------------------
/* unIdent()

 Poste:Produit        NoFamille=POSTE NoCategorie=-1 NoItem
 Charge:Engrais:Ammonitrate
 -> NoFamille NoCategorie NoItem
 code type  0   1   2   Valeur Connu
 IDENT NUM  NoF  NoC NoI         N

 AMOR     (n)
 AMOR     (n-3,n+1)
 marge_ha (n-3,n+1)
 marge_ha
 T_produit(ble(n-3,n))                                        arg()
 code type  0   1   2   Valeur Connu
 AMOR                 0   POSTE NUM  -1  -1  AMOR        N

 AMOR(n)              0     'N' NUM  -1  -1  -1          N
 1   POSTE NUM   0  -1  AMOR        N


 marge_ha             0   INDIC NUM   -1  -1 num_indic   N

 T_produit(ble(n-3,n+1))
 0     'N' NUM  -1  -1  -1          N
 1     NUM NUM  -1  -1  -1     3    O
 2      -  NUM   0   1  -1          N
 3     'N' NUM  -1  -1  -1          N
 4     NUM NUM  -1  -1  -1     1    O
 5      +  NUM   3   4  -1          N
 6  T_PROD NUM   2   5  num_elt     N

 je sais qu'il s'agit de poste_1  arg(1)==-1
 poste_2  arg(0)!=-1  et arg(1)!=-1
 */
// ------------------------------------------------------------------------
int CL_Compil::unIdent(ofstream &outfile) {
	int branche; //b_d
	int date;
// nom du poste ou de l'indic

	if (LeMot != IDENT)
		return erreur("attente d'un Poste d'un indicateur");

	LeMot = analex();
	if (TestCompil == true)
		impLeMot("unIdent", outfile);
	//je n'avais pas prévu les mvt d'animaux ST_Branche arg[3]
	//ecritElt(branche.arg[0],branche.arg[1],branche.arg[2]) cf
	//void CL_Compil:: ecritElt(int noFam,int noCat,int noItem)
	//void CL_Compil::deLArbre(int n,int opPrec)  dans CompFormule
	// aprés je me suis aperçu que c'etait idiot de trier les elt sur noCategorie
	// le noItem suffit
	// donc j'utilise pour les mvt d'animaux noCat pour stocker le noType
	//voir aussi
	//CL_Elt *CL_Compil:: trouveElt(int noFam,int noCat,int noItem)
	// dans CompAnalex
	if (NoFamille == MVT)
		NoCategorie = NoType;

	if (LeMot != '(') // cas habituel
			{
		branche = stockBranche(IDENT, NoFamille, NoCategorie, NoItem, NUM);
		return branche;
	}
// date  ident(N-1)

//    LeMot = analex();
	date = uneAnnee(outfile);
	if (date == ERREUR)
		return ERREUR;
	branche = stockBranche(IDENT, NoFamille, NoCategorie, NoItem, NUM, date);
	LeMot = analex();
	if (TestCompil == true)
		impLeMot("unIdent", outfile);
	return branche;
}
// ------------------------------------------------------------------------
//une_annee qqchose (N)  ou (N-1)     (0)
//truc(N)  date=100
//truc(N-2) date =2
//truc(3)   date=100+3
// ------------------------------------------------------------------------
int CL_Compil::uneAnnee(ofstream &outfile) {
	int date;
	LeMot = analex();
	if (TestCompil == true)
		impLeMot("uneAnnee", outfile);
	if (LeMot == 'N') {
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("uneAnnee", outfile);
		if (LeMot == '-') //indic(N-1)
				{
			LeMot = analex();
			if (TestCompil == true)
				impLeMot("uneAnnee", outfile);
			if (LeMot != NOMBRE)
				return erreur("erreur dans l'expression d'une date");
			date = int(Valeur);
			LeMot = analex();
			if (TestCompil == true)
				impLeMot("uneAnnee", outfile);
			if (LeMot != ')')
				return erreur("erreur manque ) dans l'expression d'une date");
		} else //indic(N)
		{
			date = 100;
			if (TestCompil == true)
				impLeMot("uneAnnee", outfile);
			if (LeMot != ')')
				return erreur("erreur manque ) dans l'expression d'une date");
		}
	} else if (LeMot == NOMBRE) //indic(0)
			{
		date = int(Valeur);
		if (date < 1 || date > 10)
			return erreur("erreur expression date erronée ou <1 ou >10 ");
		date += 100;
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("uneAnnee", outfile);
		if (LeMot != ')')
			return erreur("erreur manque ) dans l'expression d'une date");
	}
	return date;
}
/*
 // ------------------------------------------------------------------------
 int CL_Compil::uneAnnee(ofstream &outfile)
 {
 int date;
 LeMot = analex();
 if(TestCompil==true)impLeMot("uneAnnee", outfile);
 if(LeMot=='N')

 if(LeMot!='N')
 return erreur("erreur dans l'expression d'une date");
 LeMot=analex();
 if(TestCompil==true)impLeMot("uneAnnee", outfile);
 if(LeMot!='-')
 return erreur("erreur dans l'expression d'une date");
 LeMot=analex();
 if(TestCompil==true)impLeMot("uneAnnee", outfile);
 if(LeMot!=NOMBRE)
 return erreur("erreur dans l'expression d'une date");
 date=int(Valeur);
 LeMot=analex();
 if(TestCompil==true)impLeMot("uneAnnee", outfile);
 if(LeMot!=')')
 return erreur("erreur manque ) dans l'expression d'une date");
 return date;
 }
 */
// ------------------------------------------------------------------------
int CL_Compil::unTotal(ofstream &outfile) {
	int branche; //b_d
// nom du poste ou de l'indic

	if (LeMot != SIGMA)
		return erreur("attente d'un Total");
	lireTotal(); //il lit  (Quant Produit:Café )
	branche = stockBranche(SIGMA, NoFamille, NoCategorie, -1, NUM);

	LeMot = analex();
	if (TestCompil == true)
		impLeMot("unTotal", outfile);
	return branche;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-------------SI------------------------------------------------------------
//---------------------------------------------------------------------------

// ------------------------------------------------------------------------
// bloc_si()
// ------------------------------------------------------------------------
int CL_Compil::blocSI(int reseau, ofstream &outfile) {
	int reseauSI, reseauG, reseauD;
	int branche;

	if (LeMot != '(')
		return erreur("manque '('");
	LeMot = analex(); //lit identificateur et s'arrete sur < > = #
	if (TestCompil == true)
		impLeMot("blocSI", outfile);
	branche = conditionOU(outfile);
	if (Erreur)
		return ERREUR;

	if (LeMot != ')')
		return erreur("manque ')'");

	LeMot = analex();
	if (TestCompil == true)
		impLeMot("blocSI", outfile);
	reseauSI = stockMailleSI(branche, reseau);
	reseauG = suiteSI(reseauSI, outfile);
	if (Erreur)
		return (ERREUR);

	if (LeMot == SINON) {
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("blocSI", outfile);
		reseauD = suiteSI(reseauSI, outfile);
	} else if (LeMot == SI)
		reseauD = suiteSI(reseauSI, outfile);
	else if (LeMot == SINONSI) {
		LeMot = SI;
		reseauD = suiteSI(reseauSI, outfile);
	}

	else
		reseauD = reseauSI;

	if (Erreur)
		return (ERREUR);

	reseau = stockMaillePont(reseauG, reseauD);
	return (reseau);
}

// ------------------------------------------------------------------------
// suiteSi()
// ------------------------------------------------------------------------
int CL_Compil::suiteSI(int reseau, ofstream &outfile) {
	int branche;
	switch (LeMot) {
	case 0:
		return reseau;
	case SI:
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("suiteSI", outfile);
		reseau = blocSI(reseau, outfile);
		break;
	default:
		branche = expressionAdd(outfile);
		reseau = stockMaille(NUM, branche, reseau);
		break;
	}
	return (reseau);
}
// ------------------------------------------------------------------------
// condition_OU()
// ------------------------------------------------------------------------
int CL_Compil::conditionOU(ofstream &outfile) {
	int brancheG, brancheD;

	brancheG = conditionET(outfile);
	if (Erreur)
		return (ERREUR);

	while (LeMot == OU) {
		if (Arbre->LesBranches[brancheG].type != BOOLEEN)
			return (erreur("expression incorrecte"));
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("conditionOU", outfile);
		brancheD = conditionET(outfile);
		if (Erreur)
			return (ERREUR);
		if (Arbre->LesBranches[brancheD].type != BOOLEEN)
			return (erreur("expression incorrecte"));
		brancheG = stockBranche(OU, brancheG, brancheD, -1, BOOLEEN);
	}

	return (brancheG);
}
// ------------------------------------------------------------------------
// condition_ET()
// ------------------------------------------------------------------------
int CL_Compil::conditionET(ofstream &outfile) {
	int brancheG, brancheD;
	brancheG = expressionComp(outfile);
	if (Erreur)
		return (ERREUR);

	while (LeMot == ET) {
		if (Arbre->LesBranches[brancheG].type != BOOLEEN)
			return (erreur("expression incorrecte"));
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("conditionET", outfile);
		brancheD = expressionComp(outfile);
		if (Erreur)
			return (ERREUR);
		if (Arbre->LesBranches[brancheD].type != BOOLEEN)
			return (erreur("expression incorrecte"));
		brancheG = stockBranche(ET, brancheG, brancheD, -1, BOOLEEN);
	}

	return (brancheG);
}
// ------------------------------------------------------------------------
// expression_comp()
// N.B. : "x<y<z"  est transform‚ en "x<y ET y<z"
// ------------------------------------------------------------------------
int CL_Compil::expressionComp(ofstream &outfile) {
	int opComp = 0;
	int expG, expD;
	int brancheG, branche;
	bool ajoutET = false;

	branche = expG = expressionAdd(outfile);
	brancheG = branche; //aew
	if (Erreur)
		return (ERREUR);

	while (LeMot == '<' || LeMot == '>' || LeMot == INFEG || LeMot == SUPEG
			|| LeMot == '=' || LeMot == '#') {
		opComp = LeMot;
		LeMot = analex();
		if (TestCompil == true)
			impLeMot("expressionComp", outfile);
		expD = expressionAdd(outfile);
		if (Erreur
				|| Arbre->LesBranches[expG].type
						!= Arbre->LesBranches[expD].type)
			return (erreur("expression incorrecte"));
		branche = stockBranche(opComp, expG, expD, -1, BOOLEEN);

		// plusieurs comparaisons ???
		if (ajoutET)
			branche = stockBranche(ET, brancheG, branche, -1, BOOLEEN);

		ajoutET = true;
		expG = expD;
		brancheG = branche;

	}
	return (branche);
}
// ------------------------------------------------------------------------
// creProg
// pour tableau produit charges
// crèation directe du prog pour une formule cf AgriSaisieFormule
// ------------------------------------------------------------------------
CL_Prog *CL_Compil::CreeProg(int noFamille, CL_Item *item) {
	CL_Prog *prog;
	int QXX, PXX;
	prog = new CL_Prog();
	prog->Arbre = new CL_Arbre(10, 10);
	switch (noFamille) {
	case PRODUIT:
		QXX = QPRODUIT;
		PXX = PPRODUIT;
		break;
	case CHARGE:
		QXX = QCHARGE;
		PXX = PCHARGE;
		break;
	case EXTPOS:
		QXX = EXTPOS;
		break;
	case EXTNEG:
		QXX = EXTNEG;
		break;
	default:
		ShowMessage("oubli CreeProg Compilateur");
	}
	switch (noFamille) {
	case PRODUIT:
	case CHARGE:
		prog = CreeProgQuantPrix(QXX, PXX, item);
		return prog;
	case EXTPOS:
	case EXTNEG:
		prog = CreeProgVal(QXX, item);
		return prog;
	}
	return prog; //aew
}
// ------------------------------------------------------------------------
CL_Prog *CL_Compil::CreeProgQuantPrix(int QXX, int PXX, CL_Item *item) {
	CL_Prog *prog;
	int i;
	prog = new CL_Prog();
	prog->Arbre = new CL_Arbre(10, 10);
	for (i = 0; i < 2; i++) {
		prog->Arbre->LesBranches[i].code = IDENT;
		//prog->Arbre->LesBranches[0].arg[0]=QCHARGE;
		prog->Arbre->LesBranches[i].arg[1] = item->Categorie->No;
		prog->Arbre->LesBranches[i].arg[2] = item->No;
		prog->Arbre->LesBranches[1].valeur = 0;
		prog->Arbre->LesBranches[i].type = NUM;
		prog->Arbre->LesBranches[i].date = 0;
	}

	prog->Arbre->LesBranches[0].arg[0] = QXX;
	prog->Arbre->LesBranches[1].arg[0] = PXX;

	i = 2;
	prog->Arbre->LesBranches[i].code = '*';
	prog->Arbre->LesBranches[i].arg[0] = 0;
	prog->Arbre->LesBranches[i].arg[1] = 1;
	prog->Arbre->LesBranches[i].arg[2] = -1;
	prog->Arbre->LesBranches[1].valeur = 0;
	prog->Arbre->LesBranches[i].type = NUM;
	prog->Arbre->LesBranches[i].date = 0;

	prog->Arbre->BrancheX = 3;
	return prog;
}
// ------------------------------------------------------------------------
CL_Prog *CL_Compil::CreeProgVal(int QXX, CL_Item *item) {
	CL_Prog *prog;
	prog = new CL_Prog();
	prog->Arbre = new CL_Arbre(10, 10);
	prog->Arbre->LesBranches[0].arg[0] = QXX;
	prog->Arbre->LesBranches[0].code = IDENT;
	prog->Arbre->LesBranches[0].arg[1] = item->Categorie->No;
	prog->Arbre->LesBranches[0].arg[2] = item->No;
	prog->Arbre->LesBranches[0].valeur = 0;
	prog->Arbre->LesBranches[0].type = NUM;
	prog->Arbre->LesBranches[0].date = 0;

	prog->Arbre->BrancheX = 1;
	return prog;
}
// ------------------------------------------------------------------------
/* Stockage des Arbres :
 -------------------
 class CL_Arbre
 {
 public:
 CL_Arbre(int BrancheMax=50, int Delta=50);
 CL_Arbre(CL_Arbre *Ancien);
 ~CL_Arbre();
 ST_Branche *LesBranches;
 int   BrancheX;
 int   BrancheMax;
 int   Delta;
 AnsiString Texte;
 };
 struct ST_Branche
 {
 int code;
 int arg[3];
 float valeur;
 int type;
 int date;
 };

 structure :  ST_ARBRE
 {
 int code;    code de la feuille
 int type;    type de feuille (BOOL, NUM, DATE)
 int arg[3];  3 arguments
 float valeur;
 char connu;
 }

 selon le code :
 - opérateur binaire :
 arg[0] = brancheGauche, arg[1] = brancheDroite, arg[2] = -1
 - proposition
 code   = ID_PROP
 arg[0] = nø de la proposition =nø ident
 arg[1] = VRAI ou FAUX
 arg[2] = op‚rateur (=|#)

 - un ident
 arg[0] = NoFamille, arg[1] = NoCategorie, arg[2] =NoItem
 */
// ------------------------------------------------------------------------
// stockBranche() stocker dans l'arbre
// ------------------------------------------------------------------------
//----------------------------------------------------------------------------
int CL_Compil::stockBranche(int code, int a0, int a1, int a2, int type,
		int date) {
	int n;
	ST_Branche branche;
//Stocke = OUI;

	branche.code = code;
	branche.arg[0] = a0;
	branche.arg[1] = a1;
	branche.arg[2] = a2;
	branche.type = type; // type d'expression (BOOL, NUM, DATE, ...)
	branche.date = date;
	branche.valeur = 0.;
	if (branche.code == NOMBRE)
		branche.valeur = Valeur;
	else
		branche.valeur = 0.;

// recherche d'une branche de même type
	for (n = 0; n < Arbre->BrancheX; n++)
		if (memcmp(&Arbre->LesBranches[n], &branche, sizeof(ST_Branche)) == 0)
			return (n);
// réallocation si n‚cessaire
	if (Arbre->BrancheX >= Arbre->BrancheMax || Arbre->BrancheMax == 0)
		reallouerArbre();
	n = Arbre->BrancheX;
	Arbre->LesBranches[n].code = branche.code;
	Arbre->LesBranches[n].arg[0] = branche.arg[0];
	Arbre->LesBranches[n].arg[1] = branche.arg[1];
	Arbre->LesBranches[n].arg[2] = branche.arg[2];
	Arbre->LesBranches[n].type = branche.type;
	Arbre->LesBranches[n].valeur = branche.valeur;
	Arbre->LesBranches[n].date = date;
	Arbre->BrancheX++;

	return n;
}
// ---------------------------------------------------------------------------
void CL_Compil::reallouerArbre(void) {
	int n;
	ST_Branche *lesBranches2;
	n = Arbre->BrancheMax + Arbre->Delta;
	lesBranches2 = new ST_Branche[n];
	memcpy(lesBranches2, Arbre->LesBranches,
			sizeof(ST_Branche) * Arbre->BrancheMax);
	Arbre->BrancheMax += Arbre->Delta;
	delete Arbre->LesBranches;
	Arbre->LesBranches = lesBranches2;
}

//----------------------------------------------------------------------------
void CL_Compil::ecrireArbre(ofstream &outfile) {
	int n;
	ST_Branche branche;
	char chaine[100];
	outfile << "ARBRE   " << endl;
	for (n = 0; n < Arbre->BrancheX; n++) {
		branche = Arbre->LesBranches[n];

		sprintf(chaine, "%3d %-9.9s      %3d  %3d  %3d  %-9.9s %2d  %6.2f", n,
				nomSymbole(branche.code), branche.arg[0], branche.arg[1],
				branche.arg[2], nomSymbole(branche.type), branche.date,
				branche.valeur);
		outfile << chaine << endl;
	}
}
// ------------------------------------------------------------------------
// stock_reseau()
// ------------------------------------------------------------------------
//int CL_Compil::stockMaille( int code, int numero,int arbre, int avant)
int CL_Compil::stockMaille(int code, int branche, int avant) {
	int m = Reseau->MailleX++;

	if (Reseau->MailleX >= Reseau->MailleMax || Reseau->MailleMax == 0)
		reallouerReseau();

	Reseau->LesMailles[m].code = code;
	if (avant >= 0) {
		if (Reseau->LesMailles[avant].apG == -1)
			Reseau->LesMailles[avant].apG = m;
		else
			Reseau->LesMailles[avant].apD = m;
	}

	Reseau->LesMailles[m].branche = branche;
	Reseau->LesMailles[m].apD = -1; // jamais utilisé
	Reseau->LesMailles[m].apG = -1; // sera informé par la suite
	return (m);
}
// ------------------------------------------------------------------------
// stockMailleSI()
// ------------------------------------------------------------------------
int CL_Compil::stockMailleSI(int branche, int avant) {
	int m = Reseau->MailleX++;

//		 avant          un SI a 1 seul avant (G)
//			            et deux aprés (G et D)

	if (Reseau->MailleX >= Reseau->MailleMax || Reseau->MailleMax == 0)
		reallouerReseau();

	Reseau->LesMailles[m].code = SI;

	if (avant >= 0) {
		if (Reseau->LesMailles[avant].apG == -1)
			Reseau->LesMailles[avant].apG = m; //Reseau->MailleX;
		else
			Reseau->LesMailles[avant].apD = m; //Reseau->MailleX;
	}

	Reseau->LesMailles[m].branche = branche;
	Reseau->LesMailles[m].apG = -1;
	Reseau->LesMailles[m].apD = -1;

	return (m);
}
// ------------------------------------------------------------------------
// stock_reseau_PONT()
// ------------------------------------------------------------------------
int CL_Compil::stockMaillePont(int mG, int mD) {
	int m = Reseau->MailleX++;

//	avant_g   avant_d       un PONT a 2 avant (G et D)
//                     et un seul après (G)

	if (Reseau->MailleX >= Reseau->MailleMax || Reseau->MailleMax == 0)
		reallouerReseau();

	Reseau->LesMailles[m].code = PONT;
	Reseau->LesMailles[m].branche = -1;

	Reseau->LesMailles[m].apG = -1;
	Reseau->LesMailles[m].apD = -1;

	Reseau->LesMailles[mG].apG = m;
	if (Reseau->LesMailles[mD].apG == -1)
		Reseau->LesMailles[mD].apG = m;
	else
		Reseau->LesMailles[mD].apD = m;

	return (m);
}

// ---------------------------------------------------------------------------
void CL_Compil::reallouerReseau(void) {
	int n;
	ST_Maille *lesMailles2;
	n = Reseau->MailleMax + Reseau->Delta;
	lesMailles2 = new ST_Maille[n];
	memcpy(lesMailles2, Reseau->LesMailles,
			sizeof(ST_Maille) * Reseau->MailleMax);
	Reseau->MailleMax += Reseau->Delta;
	delete Reseau->LesMailles;
	Reseau->LesMailles = lesMailles2;
}

// ---------------------------------------------------------------------------
void CL_Compil::ecrireReseau(ofstream &outfile) {
	int i, n;
	ST_Maille maille;
	ST_Branche branche;
	char chaine[100];
	outfile << "RESEAU   " << endl;
	for (i = 0; i < Reseau->MailleX; i++) {
		maille = Reseau->LesMailles[i];
		sprintf(chaine, "%3d %-9.9s %3d      %3d  %3d", i,
				nomSymbole(maille.code), maille.branche, maille.apG,
				maille.apD);
		outfile << chaine << endl;
	}

	outfile << endl;
	outfile << "ARBRE   " << endl;
	outfile << endl;

	for (n = 0; n < Arbre->BrancheX; n++) {
		branche = Arbre->LesBranches[n];

		sprintf(chaine, "%3d %-9.9s      %3d  %3d  %3d  %-9.9s %2d  %6.2f", n,
				nomSymbole(branche.code), branche.arg[0], branche.arg[1],
				branche.arg[2], nomSymbole(branche.type), branche.date,
				branche.valeur);
		outfile << chaine << endl;
	}

}

//----------------------------------------------------------------------------
char* CL_Compil::nomSymbole(int n) {
	static char chaine[10];

	if (n < 256) {
		memset(chaine, ' ', sizeof(chaine));
		chaine[9] = 0;
		chaine[3] = (char) n;
		return chaine;
	}
	switch (MainForm->Langue) {
	case 'F':
		switch (n) {
		case ERREUR:
			return "ERREUR";
		case NOMBRE:
			return "NOMBRE";
		case NUM:
			return "NUM";
		case IDENT:
			return "IDENT";
		case FIN:
			return "FIN";
		case INFEG:
			return "INFEG";
		case SUPEG:
			return "SUPEG";
		case MUNAIRE:
			return "MUNAIRE";
		case ET:
			return "ET";
		case OU:
			return "OU";
		case SI:
			return "SI     ";
		case SINON:
			return "SINON  ";
		case SINONSI:
			return "SINONSI";
		case BOOLEEN:
			return "BOOLEEN";
		case PONT:
			return "PONT";
		case SIGMA:
			return "TOTAL";
		case AN:
			return "AN";
		case LOG:
			return "LOG";
		case EXP:
			return "EXP";
		case TOTSUR:
			return "TOTAL_Culture"; //"TOTSUR";

		default:
			return "????";
		}
	case 'A':
		switch (n) {
		case ERREUR:
			return "ERROR";
		case NOMBRE:
			return "NUMBER";
		case NUM:
			return "NUM";
		case IDENT:
			return "IDENT";
		case FIN:
			return "END";
		case INFEG:
			return " <= ";
		case SUPEG:
			return " >= ";
		case MUNAIRE:
			return "MUNAIRE";
		case ET:
			return "AND";
		case OU:
			return "OR";
		case SI:
			return "IF     ";
		case SINON:
			return "ELSE  ";
		case SINONSI:
			return "ELSEIF";
		case BOOLEEN:
			return "BOOLEAN";
		case PONT:
			return "PONT";
		case SIGMA:
			return "TOTAL";
		case AN:
			return "YEAR";
		case LOG:
			return "LOG";
		case EXP:
			return "EXP";
		case TOTSUR:
			return "TOTAL_Crop"; //"TOTSUR";

		default:
			return "????";
		}

	}
	return "????";
}

//----------------------------------------------------------------------------
void CL_Compil::impLeMot(char *ouJeSuis, ofstream &outfile) {
	char car;
	if (LeMot < 256) {
		car = (char) LeMot;
		outfile << car << "     " << ouJeSuis << endl;
		return;
	}
	switch (LeMot) {
	case ERREUR:
		outfile << "ERREUR";
		break;
	case NOMBRE:
		outfile << "NOMBRE" << "    " << Valeur;
		break;
	case NUM:
		outfile << "NUM";
		break;
	case IDENT:
		outfile << "IDENT";
		break;
	case FIN:
		outfile << "FIN";
		break;
	case INFEG:
		outfile << "INFEG";
		break;
	case SUPEG:
		outfile << "SUPEG";
		break;
	case MUNAIRE:
		outfile << "MUNAIRE";
		break;
	case ET:
		outfile << "ET";
		break;
	case OU:
		outfile << "OU";
		break;
	case SI:
		outfile << "SI";
		break;
	case SINON:
		outfile << "SINON";
		break;
	case SINONSI:
		outfile << "SINONSI";
		break;
	case BOOLEEN:
		outfile << "BOOLEEN";
		break;
	case PONT:
		outfile << "PONT";
		break;
	case SIGMA:
		outfile << "TOTAL";
		break;
	case AN:
		outfile << "AN";
		break;
	case LOG:
		outfile << "LOG";
		break;
	case EXP:
		outfile << "EXP";
		break;
	case TOTSUR:
		outfile << "TOTSUR";
		break;
	default:
		outfile << "????";
		break;
	}
	outfile << "        " << ouJeSuis << endl;

}

