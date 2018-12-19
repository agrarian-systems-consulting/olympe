//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "Erreur.h"
//#include "Analex.h"
#include "Main.h"
#include "CL_Trad.h"
#include "Compilateur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
extern CL_Trad *T;
/**/
//------------------------------------------------------------------
void CL_Compil::IniLexique(void) {
	Lexique = new TStringList;
	Lexique->Sorted = true;
	switch (MainForm->Langue) {
	case 'F':
		Lexique->AddObject("total", (TObject*) SIGMA);
		Lexique->AddObject("et", (TObject*) ET);
		Lexique->AddObject("ou", (TObject*) OU);
		Lexique->AddObject("si", (TObject*) SI);
		Lexique->AddObject("sinon", (TObject*) SINON);
		Lexique->AddObject("sinonsi", (TObject*) SINONSI);
		Lexique->AddObject("an", (TObject*) AN);
		Lexique->AddObject("log", (TObject*) LOG);
		Lexique->AddObject("exp", (TObject*) EXP);
		Lexique->AddObject("Total_Culture", (TObject*) TOTSUR);
		break;
	case 'E':
		Lexique->AddObject("total", (TObject*) SIGMA);
		Lexique->AddObject("and", (TObject*) ET);
		Lexique->AddObject("or", (TObject*) OU);
		Lexique->AddObject("if", (TObject*) SI);
		Lexique->AddObject("else", (TObject*) SINON);
		Lexique->AddObject("elseif", (TObject*) SINONSI);
		Lexique->AddObject("year", (TObject*) AN);
		Lexique->AddObject("log", (TObject*) LOG);
		Lexique->AddObject("exp", (TObject*) EXP);
		Lexique->AddObject("Total_Crop", (TObject*) TOTSUR);
		break;
	}
}
//----------------------------------------------------------------------------
int CL_Compil::analex(void) {
	unsigned char car;
	char ccar;
	int code;
	int crochet;
//bool continuer=true;
	while (1) {
		car = Flot[Pos];
		switch (car) {
		case 0:
			return 0;
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			Pos++;
			break;
		case '+':
		case '-':
		case '/':
		case '*':
		case '(':
		case ')':
		case '{':
		case '}':
		case '#':
		case '=':
		case '%':
			Pos++;
			return car;
		case '<':
			if (Flot[Pos + 1] == '=') {
				Pos += 2;
				return INFEG;
			} else {
				Pos++;
				return car;
			}
		case '>':
			if (Flot[Pos + 1] == '=') {
				Pos += 2;
				return SUPEG;
			} else {
				Pos++;
				return car;
			}
		case 'N': //121103
		case 'n':
			if (Flot[Pos + 1] == ' ') {
				Pos += 2;
				return 'N';
			} //cf Resultat(N -1)
			if (Flot[Pos + 1] == 160) {
				Pos += 2;
				return 'N';
			} //cf Resultat(N -1)
			if (Flot[Pos + 1] == '\n') {
				Pos += 2;
				return 'N';
			} //cf Resultat(N -1)
			if (Flot[Pos + 1] == '\r') {
				Pos += 2;
				return 'N';
			} //cf Resultat(N -1)
			if (Flot[Pos + 1] == 0) {
				Pos += 2;
				return 'N';
			} //cf Resultat(N -1)
			if (Flot[Pos + 1] == '-') {
				Pos += 1;
				return 'N';
			} //cf Resultat(N-1)
			if (Flot[Pos + 1] == '<') {
				Pos += 1;
				return 'N';
			} //cf Resultat(N<2)
			if (Flot[Pos + 1] == '>') {
				Pos += 1;
				return 'N';
			} //cf Resultat(N>2)
			if (Flot[Pos + 1] == ')') {
				Pos += 1;
				return 'N';
			} //cf Resultat(N)
			else
				break;

		case '[':
			crochet = 1;
			while (1) {
				Pos++;
				ccar = Flot[Pos];
				if (ccar == 0)
					erreur(T->L_PasFinComm.c_str()); //"Absence de fin de Commentaire ]");

				if (ccar != '[' && ccar != ']')
					continue;

				if (ccar == '[')
					crochet++;
				else if (ccar == ']')
					crochet--;

//                    if(crochet==0) continuer=true;Pos++;break;
				if (crochet == 0)
					Pos++;
				break;
			}
		default: //mot cle  nombre  identificateur
			if (isalnumA(car)) {
				code = anaTexte();
				return code;
			} else {
				erreur(T->L_CarInco.c_str()); //"caractère inconnu");
				return ERREUR;
			}

		}
	}
}
/* prévu pour commentaire
 mais pose problème pour charges d'orge        '
 case 39://'
 while(1)
 {
 Pos++;
 ccar=Flot[Pos];
 if(ccar=='\n'){ continuer=true;Pos++;break;}
 if(ccar==0)   { continuer=true;break;}
 }
 break;
 */
//----------------------------------------------------------------------------
// anaTexte doit trouver
//ou un mot du lexique: et ou si sinon sinonsi  log  exp
//ou un nombre
//ou un identificateur +- long
//----------------------------------------------------------------------------
int CL_Compil::anaTexte(void) {
	char mot[LONNOM];
	int motCle;
	int m = 0;
	memset(mot, ' ', sizeof(mot));
	// sauter les blancs
	while (1) {
		if (Flot[Pos] == ' ' || Flot[Pos] == 160)
			Pos++; //101002  ''=160
		else
			break;
	}

	//mot clé
	motCle = estMotCle();
	if (motCle > 0)
		return motCle;

	// numérique
	if (isdigit(Flot[Pos]))
		return lireNombre();

	// on sait maintenant que ce n'est ni un mot cle ni un nombre
	//on doit trouver un identificateur (chaine s'arretant avec un séparateur)
	//     xxx:yyy        cf lireIdent
	//  ou xxx:yyy:www
	//  ou xxx:yyy:www:zzz
	while (1) {
		//est ce la fin de l'identificateur ? si oui sortir du while
		// et donner la main à lireIdent
		if (estSeparateur(Pos) == true) {
			mot[m] = 0;
			break;
		}
		mot[m++] = Flot[Pos++];
	}
	//identificateur de variable
	return lireIdent(mot);
}
//----------------------------------------------------------------------------
//Séparateur   ET OU à mettre!!!!!!!
//----------------------------------------------------------------------------
bool CL_Compil::estSeparateur(int pos) {
	char nom[10];
	if (Flot[pos] == 0 || Flot[pos] == '(' || Flot[pos] == ')'
			|| Flot[pos] == '<' || Flot[pos] == '>' || Flot[pos] == '='
			|| Flot[pos] == '#' || Flot[pos] == '*' || Flot[pos] == '/'
			|| Flot[pos] == '+' || Flot[pos] == '-' || Flot[pos] == '\r'
			|| Flot[pos] == '\n')
		return true;
	else if (Flot[pos] == ' ' || Flot[pos] == 160) {
		strncpy(nom, Flot + pos + 1, 3);
		nom[3] = 0;
		// voir pour introduire et ou actuellement erreur oubien->ou
		if (strcmpi(nom, nomSymbole(ET)) == 0)
			return true;
		if (strcmpi(nom, nomSymbole(OU)) == 0)
			return true;
		//if(strcmpi(nom,"et ")==0) return true;
		//if(strcmpi(nom,"ou ")==0) return true;
		return false;
	} else
		return false;
}
//----------------------------------------------------------------------------
int CL_Compil::estMotCle(void) {
	int motCle;
	int n;
	AnsiString asNom;
//char nom[LONNOM+1];
	char nom[15];
	int pos = Pos;
	int index;
	//trouver le mot il s'arrete avec blanc,parenthese ouvrante, fin de fichier
	n = 0;
	while (1) {
		if (Flot[pos] == VIDE)
			break;
		if (Flot[pos] == '(')
			break;
		if (Flot[pos] == ' ')
			break;
		if (Flot[pos] == 160)
			break; //Flot[pos]==''
		if (Flot[pos] == '\n')
			break;
		if (Flot[pos] == '\r')
			break;
		if (Flot[pos] == '=')
			break;
		if (Flot[pos] == '>')
			break;
		if (Flot[pos] == '<')
			break;
		if (Flot[pos] == '#')
			break;
		if (Flot[pos] == '+')
			break;
		if (Flot[pos] == '-')
			break;
		if (Flot[pos] == '*')
			break;
		if (Flot[pos] == '/')
			break;
//??        if(Flot[pos]==':')   break;  //011206

		nom[n++] = Flot[pos++];
		if (n >= 14)
			return 0; //pas de mot cle de + de 15 caracteres  TOTAT->L_Culture 13 caractères
	}
	nom[n] = VIDE;
	asNom = AnsiString(nom);
	if (Lexique->Find(asNom, index)) {
		motCle = (int) Lexique->Objects[index];
		Pos = pos;
		return motCle;
	}
	return 0;
}
//----------------------------------------------------------------------------
//Nombre
//----------------------------------------------------------------------------
int CL_Compil::lireNombre(void) {
	int n;
	char nombre[40];
// attention un nombre a été introduit 1 000 000
//  la premiere compil ok
// je le modifie 1 200 000
// pb de compil les blancs' ' 32 en ascii ont été remplacés par'' 160 en ascii
	n = 0;
	while (1) {
		if (n > 39)
			return erreur(T->L_NbLong.c_str()); //"nombre trop long");
		if (isdigit(Flot[Pos]))
			nombre[n++] = Flot[Pos++];
		else if (Flot[Pos] == '.' || Flot[Pos] == ',') {
			nombre[n++] = '.';
			Pos++;
		} else if (Flot[Pos] == ' ' && isdigit(Flot[Pos + 1])) {
			nombre[n++] = Flot[Pos + 1];
			Pos += 2;
		} else if (Flot[Pos] == 160 && isdigit(Flot[Pos + 1])) {
			nombre[n++] = Flot[Pos + 1];
			Pos += 2;
		} else
			break;
	}
	nombre[n] = 0;
	Valeur = atof(nombre);
	return NOMBRE;
}
//-----------------------------------------------------------------------------
// Ident
//-----------------------------------------------------------------------------
/*
 NomFamille:NomCategorie:NomItem
 ou
 Poste:NomItem
 ou
 TOTAL(NomFamille:NomCategorie)
 De saisie ProduitsAutres
 ChargesAutres
 ChStr
 Externalites   et provisoirement
 V:NomCategorieVariable:NomVariable
 de indicateur
 Poste
 Produit

 V:Surface:Avoine
 */

//-----------------------------------------------------------------------------
int CL_Compil::lireIdent(char *mot) {
//CL_Poste *poste;
	AnsiString nomFamille, nomCategorie, nomItem, nomType;
	char type;
	int pos = 0;
	int noType; // cftrouveTypeAnimaux vendus achat...
	//NomFamille
	nomFamille = lireNom(mot, pos);
//    poste=V_Poste->trouve(nomFamille);
	/*
	 if     (nomFamille.AnsiCompareIC(AnsiString("Poste"))==0)          type=0;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Ceg"))==0)            type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Bilan"))==0)          type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Immobilisation"))==0) type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Subvention"))==0)     type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Tva"))==0)            type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Emprunt"))==0)        type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Emprunt LT"))==0)     type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Emprunt CT"))==0)     type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Emprunt Privé"))==0)  type=1;
	 else if(nomFamille.AnsiCompareIC(AnsiString("Mvt Animaux"))==0)    type=3;
	 */
	if (nomFamille.AnsiCompareIC(T->L_Poste) == 0)
		type = 0;
	else if (nomFamille.AnsiCompareIC(T->L_Ceg) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Bilan) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Immobilisation) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Subvention) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Tva) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Emprunt) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Emprunt_LT) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Emprunt_CT) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Emprunt_Prive) == 0)
		type = 1;
	else if (nomFamille.AnsiCompareIC(T->L_Mvt_Animaux) == 0)
		type = 3;
	else if (nomFamille.AnsiCompareIC(AnsiString("Calendrier")) == 0)
		type = 0; //110306
	else
		type = 2;
	switch (type) {
	case 0: //ex Poste:Recettes Produits
		nomItem = lireNom(mot, pos);
		return trouveElt(nomItem);

	case 1: //ex Ceg:Produits    //Subvention:Valeur
		nomItem = lireNom(mot, pos);
		return trouveElt(nomFamille, nomItem);

	case 2: //ex Produits:Cereales:ble
		nomCategorie = lireNom(mot, pos);
		nomItem = lireNom(mot, pos);
		return trouveElt(nomFamille, nomCategorie, nomItem);

	case 3: //Mvt Animaux
			//ex Mvt Animaux:Bovins Lait:Effectifs:VL velage 3 ans
		nomCategorie = lireNom(mot, pos);
		nomType = lireNom(mot, pos);
		nomItem = lireNom(mot, pos);
		noType = trouveTypeAnimaux(nomType);
		return trouveElt(MVT, nomCategorie, noType, nomItem);
	}
	return 0; //aew
}
//-------------------------------------------------------------------------
int CL_Compil::trouveTypeAnimaux(AnsiString nomType) {
	// si modif des noms ici modifier aussi dans TvDico EtablirNomMvtAni
	/*
	 if(nomType=="Effectifs")        return EFF;       //160
	 if(nomType=="Eff Vendus")       return EFFV;      //161
	 if(nomType=="Eff Achetés")      return EFFA;      //162
	 if(nomType=="Val Ventes")       return VALV;      //163
	 if(nomType=="Val Achats")       return VALA;      //164
	 if(nomType=="Val Inv")          return VALINV;    //165
	 */
	if (nomType == T->L_Effectifs)
		return EFF; //160
	if (nomType == T->L_Eff_Vendus)
		return EFFV; //161
	if (nomType == T->L_Eff_Achetes)
		return EFFA; //162
	if (nomType == T->L_Val_Ventes)
		return VALV; //163
	if (nomType == T->L_Val_Achats)
		return VALA; //164
	if (nomType == T->L_Val_Inv)
		return VALINV; //165
	return EFF; //aew
}
//-------------------------------------------------------------------------
AnsiString CL_Compil::lireNom(char *mot, int &pos) {
	int n = 0;
	char nom[LONNOM + 1];
	AnsiString asNom;
	memset(nom, ' ', sizeof(nom));
	while (1) {
		if (mot[pos] == VIDE)
			break;
		if (mot[pos] == ':') {
			pos++;
			break;
		}
		nom[n++] = mot[pos++];
	}
	nom[n] = VIDE;
	asNom = AnsiString(nom);
	asNom = asNom.Trim();
	return asNom;
}
//  QuantProduit:Café
//-----------------------------------------------------------------------------
int CL_Compil::lireTotal(void) {
	int n, pos;
	AnsiString nomFamille, nomCategorie;
	char mot[LONNOM];
	n = 0;
	LeMot = analex();
	if (LeMot != '(')
		return erreur(T->L_ParFerm.c_str()); //"manque (");
	while (1) {
		if (Flot[Pos] == ')') {
			mot[n] = 0;
			break;
		}
		mot[n++] = Flot[Pos++];
	}
	pos = 0;
	//NomFamille NomCategorie
	nomFamille = lireNom(mot, pos);
	nomCategorie = lireNom(mot, pos);

	LeMot = analex();

	if (LeMot != ')')
		return erreur(T->L_ParOuv.c_str()); //"manque )");
	return trouveEltFamCat(nomFamille, nomCategorie);
}
//-------------------------------------------------------------------------------
bool CL_Compil::lire2Points(void) {
	while (1) {
		if (Flot[Pos] == VIDE)
			break;
		if (Flot[Pos] == '\n') {
			Pos++;
			continue;
		}
		if (Flot[Pos] == ' ') {
			Pos++;
			continue;
		}
		if (Flot[Pos] == ':') {
			Pos++;
			return true;
		}
	}
	erreur(T->L_2Point.c_str()); //"Manque : ");
	return false;
}
//-------------------------------------------------------------------------------
// Poste:Produits
//-------------------------------------------------------------------------------
//int CL_Compil::trouveElt(AnsiString &nomItem)
int CL_Compil::trouveElt(AnsiString nomItem) {
	CL_Elt *elt;
	AnsiString AEcrire;
	for (int i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (!(elt->NoFamille == POSTE || elt->NoFamille == CALENDRIER))
			continue; //110306
		if (stricmp(elt->Nom, nomItem.c_str()) == 0) {
			NoFamille = elt->NoFamille;
			NoCategorie = elt->NoCategorie;
			NoItem = elt->NoItem;
			return IDENT;
		}
	}
	AEcrire = AnsiString("Poste  ") + nomItem + T->L_Inco; //"  Inconnu";
	return erreur(AEcrire.c_str());
//    return erreur("Poste Inconnu ou opérateur oublié");
}
//-------------------------------------------------------------------------------
// Emprunt:Annuités
// Variables:Rendement:Avoine
//-------------------------------------------------------------------------------
int CL_Compil::trouveElt(AnsiString nomFamille, AnsiString nomItem) {
	CL_Elt *elt;
	AnsiString AEcrire;
	for (int i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (stricmp(elt->NomFamille, nomFamille.c_str()) == 0) {
			if (stricmp(elt->Nom, nomItem.c_str()) == 0) {
				NoFamille = elt->NoFamille;
				NoCategorie = elt->NoCategorie;
				NoItem = elt->NoItem;
				return IDENT;
			}
		}
	}
	AEcrire = nomFamille + "  :  " + nomItem + T->L_Inco; //"  Inconnu";
	return erreur(AEcrire.c_str());
//    return erreur("Identificateur Inconnu");
}
//-------------------------------------------------------------------------------
// Charges:Engrais:Ammonitrate
// Variables:Rendement:Avoine
//-------------------------------------------------------------------------------
int CL_Compil::trouveElt(AnsiString nomFamille, AnsiString nomCategorie,
		AnsiString nomItem) {
	CL_Elt *elt;
	AnsiString AEcrire;
	for (int i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (stricmp(elt->NomFamille, nomFamille.c_str()) == 0) {
			if (stricmp(elt->NomCat, nomCategorie.c_str()) == 0) {
				if (stricmp(elt->Nom, nomItem.c_str()) == 0) {
					NoFamille = elt->NoFamille;
					NoCategorie = elt->NoCategorie;
					NoItem = elt->NoItem;
					return IDENT;
				}
			}
		}
	}
	AEcrire = nomFamille + "  " + T->L_IdentInco; //"Identificateur Inconnu";
	return erreur(AEcrire.c_str());

//    return erreur("Identificateur Inconnu");
}
//-------------------------------------------------------------------------------
// Mvt Animaux:Laitier:Effectifs:VL
//-------------------------------------------------------------------------------
int CL_Compil::trouveElt(int noFamille, AnsiString nomCategorie, int type,
		AnsiString nomItem) {
	CL_Elt *elt;
	AnsiString AEcrire;
	for (int i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (elt->NoFamille != noFamille)
			continue;

		if (stricmp(elt->NomCat, nomCategorie.c_str()) == 0) {
			if (elt->NoType != type)
				continue;

			// je fais l'impasse sur le type :Effectifs Eff Vendu
			if (stricmp(elt->Nom, nomItem.c_str()) == 0) {
				NoFamille = elt->NoFamille;
				NoCategorie = elt->NoCategorie;
				NoItem = elt->NoItem;
				NoType = elt->NoType;
				return IDENT;
			}
		}
	}
	return erreur(T->L_IdentInco.c_str()); //"Identificateur Inconnu");
}
//-------------------------------------------------------------------------------
// Emprunt:Annuités
// Variables:Rendement:Avoine
//-------------------------------------------------------------------------------
int CL_Compil::trouveEltFamCat(AnsiString nomFamille, AnsiString nomCat) {
	CL_Elt *elt;
	for (int i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (stricmp(elt->NomFamille, nomFamille.c_str()) == 0) {
			if (stricmp(elt->NomCat, nomCat.c_str()) == 0) {
				NoFamille = elt->NoFamille;
				NoCategorie = elt->NoCategorie;
				return SIGMA;
			}
		}
	}
	return erreur(T->L_IdentInco.c_str()); //"Identificateur Inconnu");
}
/*-------------------------------------------------------------------------*/
int CL_Compil::erreur(char *message) {
//	Flot[Pos]=VIDE;
	ErreurFrm->Edit->Lines->Add((char*) Flot);

	ErreurFrm->Edit->Lines->Add(message);
	Erreur = true;
	ErreurFrm->Show();
	return ERREUR;
	/*
	 setmem(Chaine_erreur,sizeof(Chaine_erreur),' ');
	 Chaine_erreur[Pos]=24;     //position de l'erreur
	 Chaine_erreur[Pos+1]=' ';
	 Chaine_erreur[Pos+2]=VIDE;
	 strcat(Chaine_erreur,message);
	 */

}
//------------------------------------------------------------------
//int CL_Compil::isalnumA(int c)
int CL_Compil::isalnumA(unsigned char c) {
// prise en compte de é à etc
	if (isalnum(c))
		return 1;
	if (c == '_')
		return 1;
	if (c == '.')
		return 1;
	if (c >= 128 && c <= 176)
		return 1;
	if (c >= 224 && c <= 244)
		return 1;

	return 0;
}
//------------------------------------------------------------------
/*
 T->L_PasFinComm=       "Absence de fin de Commentaire ]";
 T->L_CarInco=          "caractère inconnu";
 T->L_NbLong=           "nombre trop long";

 T->L_ParFerm=           "manque (";
 T->L_ParOuv=            "manque )";
 T->L_2Point=            "manque : ";
 T->L_Inco=              "  Inconnu";
 T->L_IdentInco=         "Identificateur Inconnu";



 T->L_Poste=            "Poste";
 T->L_Ceg=              "Ceg";
 T->L_Bilan=            "Bilan";
 T->L_Immobilisation=   "Immobilisation";
 T->L_Subvention=       "Subvention";
 T->L_Tva=              "Tva";
 T->L_Emprunt=          "Emprunt";
 T->L_Emprunt_LT=       "Emprunt LT";
 T->L_Emprunt_CT=       "Emprunt CT";
 T->L_Emprunt_Prive=    "Emprunt Privé";
 T->L_Mvt_animaux=      "Mvt Animaux";

 T->L_Effectifs=        "Effectifs";
 T->L_Eff Vendus=       "Eff Vendus";
 T->L_Eff Achetés=      "Eff Achetés";
 T->L_Val Ventes=       "Val Ventes";
 T->L_Val Achats=       "Val Achats";
 T->L_Val Inv=          "Val Inv";

 T->L_ParFerm=           "manque (";
 T->L_ParOuv=            "manque )";
 T->L_2Point=            "manque : ";
 T->L_Inco=              "  Inconnu";
 T->L_IdentInco=         "Identificateur Inconnu";

 */

