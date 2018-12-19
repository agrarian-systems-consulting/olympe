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
#include "Compilateur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
/**/
//------------------------------------------------------------------
void CL_Compil::IniLexique(void) {
	Lexique = new TStringList;
	Lexique->Sorted = true;

	Lexique->AddObject("et", (TObject*) ET);
	Lexique->AddObject("ou", (TObject*) OU);
	Lexique->AddObject("si", (TObject*) SI);
	Lexique->AddObject("sinon", (TObject*) SINON);
	Lexique->AddObject("sinonsi", (TObject*) SINONSI);

}
//----------------------------------------------------------------------------
int CL_Compil::analex(void) {
	char car, ccar;
	int code;
	int crochet;
	bool continuer = false;
	while (1) {
		car = Flot[Pos];
		switch (car) {
		case 0:
			return 0;
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			continuer = true;
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
		case 'N':
			if (Flot[Pos + 1] == ' ') {
				Pos += 2;
				return 'N';
			} //cf Resultat(N)
			else
				break;
		case 39: //'
			while (1) {
				Pos++;
				ccar = Flot[Pos];
				if (ccar == '\n') {
					continuer = true;
					Pos++;
					break;
				}
				if (ccar == 0) {
					continuer = true;
					break;
				}
			}
			break;
		case '[':
			crochet = 1;
			while (1) {
				Pos++;
				ccar = Flot[Pos];
				if (ccar == 0)
					erreur("Absence de fin de Commentaire ]");

				if (ccar != '[' && ccar != ']')
					continue;

				if (ccar == '[')
					crochet++;
				else if (ccar == ']')
					crochet--;

				if (crochet == 0)
					continuer = true;
				Pos++;
				break;
			}
		default:
			if (isalnum(car)) {
				continuer = false;
				break;
			}
			erreur("caractère inconnu");
			return ERREUR;

		}
		if (continuer == false)
			break; //sortie du while
	}
	code = anaTexte();
	return code;
}
//----------------------------------------------------------------------------
int CL_Compil::anaTexte(void) {
	char mot[40];
	int m = 0;
	int pos;
	int index;
	int code;
	bool trouve;
	AnsiString asMot;
	// sauter les blancs
	while (1) {
		if (Flot[Pos] == ' ')
			Pos++;
		else
			break;
	}
	// numérique
	if (isdigit(Flot[Pos]))
		return lireNombre();

	// les mots cle blanc séparateur
	pos = Pos;
	while (1) {
		if (Flot[pos] == ' ' || Flot[pos] == 0) {
			mot[m] = 0;
			break;
		}
		if (isalpha(Flot[pos]) == 0) {
			mot[m] = 0;
			break;
		}
		mot[m++] = Flot[pos++];
	}
	asMot = AnsiString(mot);
	asMot = asMot.LowerCase();
	trouve = Lexique->Find(asMot, index);
	if (trouve == true) {
		code = (int) (Lexique->Objects[index]);
		Pos = pos;
		return code;
	}

	//identificateur de variable
	return lireIdent();
}
//----------------------------------------------------------------------------
//Nombre
//----------------------------------------------------------------------------
int CL_Compil::lireNombre(void) {
	int n;
	char nombre[40];
	n = 0;
	while (1) {
		if (n > 39)
			return erreur("nombre trop long");
		if (isdigit(Flot[Pos]))
			nombre[n++] = Flot[Pos++];
		else if (Flot[Pos] == '.' || Flot[Pos] == ',') {
			nombre[n++] = '.';
			Pos++;
		} else if (Flot[Pos] == ' ' && isdigit(Flot[Pos + 1])) {
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
int CL_Compil::lireIdent(void) {
	AnsiString nomFamille, nomCategorie, nomItem;
//char type;
//CL_Categorie *categorie;
//CL_Item      *item;
//CL_Valeur    *valeur;

	//NomFamille
	lireNom(nomFamille);
	if (nomFamille.AnsiCompareIC(AnsiString("Poste")) == 0) {
		if (lire2Points() == false)
			return ERREUR;
		lireNom(nomItem);
		return trouveElt(nomItem);
	} else {
		if (lire2Points() == false)
			return ERREUR;
		lireNom(nomCategorie);
		if (lire2Points() == false)
			return ERREUR;
		lireNom(nomItem);
		return trouveElt(nomFamille, nomCategorie, nomItem);
	}
}
//-------------------------------------------------------------------------     nom=lireNom(nom);
void CL_Compil::lireNom(AnsiString &asNom) {
	int n = 0;
	char nom[100];

	while (1) {
		if (Flot[Pos] == VIDE)
			break;
		if (n > 99) {
			erreur("nom trop long");
			return;
		}

		if (isalnumA(Flot[Pos]))
			nom[n++] = Flot[Pos++];
		else if (isdigit(Flot[Pos]))
			nom[n++] = Flot[Pos++];

		else if (Flot[Pos] == ' ')
			nom[n++] = Flot[Pos++];
		else if (Flot[Pos] == '_')
			nom[n++] = Flot[Pos++];
		else
			break;
	}
	nom[n] = VIDE;
	asNom = AnsiString(nom);
	asNom = asNom.Trim();
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
	erreur("Manque : ");
	return false;
}
//-------------------------------------------------------------------------------
// Poste:Produits
//-------------------------------------------------------------------------------
int CL_Compil::trouveElt(AnsiString &nomItem) {
	CL_Elt *elt;
	for (int i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (elt->NoFamille != POSTE)
			continue;
		if (stricmp(elt->Nom, nomItem.c_str()) == 0) {
			NoFamille = elt->NoFamille;
			NoCategorie = elt->NoCategorie;
			NoItem = elt->NoItem;
			return IDENT;
		}
	}
	return erreur("Poste Inconnu");
}
//-------------------------------------------------------------------------------
// Charges:Engrais:Ammonitrate
// Variables:Rendement:Avoine
//-------------------------------------------------------------------------------
int CL_Compil::trouveElt(AnsiString &nomFamille, AnsiString &nomCategorie,
		AnsiString &nomItem) {
	CL_Elt *elt;
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
	return erreur("Identificateur Inconnu");
}
/*-------------------------------------------------------------------------*/
int CL_Compil::erreur(char *message) {
//	Flot[Pos]=VIDE;
	ErreurFrm->Edit->Lines->Add(Flot);

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

