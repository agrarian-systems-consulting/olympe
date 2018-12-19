//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <dir.h>
#include <vcl.h>
#include <stdio.h>
using namespace std;

#pragma package(smart_init)

#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "Main.h"
#include "FichierLire.h"

#include "Compilateur.h"

//extern
#include "Olympe.hse"
#include "LesVecteurs.hse"

#include "FichierEcrireXml.h"
extern CL_ES *ES;
extern CL_Compil *Compil;
extern CL_Xml *Xml;
#include "FichierLireXml.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void CL_Xml::LireFichier(void) {
	char nomFichier[MAXPATH];
	char entreeNom[MAXPATH];
	char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT];
	AnsiString date;
	TDateTime time;
	AnsiString s;
	strncpy(nomFichier, ES->FEcriture.c_str(), MAXPATH);

	// Construire le nom du fichier.Xml !!! */
	fnsplit(nomFichier, drive, dir, name, ext);

	fnmerge(entreeNom, drive, dir, name, ".xml");
//	fnmerge( entreeNom, drive, dir, name, ".txt");

	ShowMessage(entreeNom);

	MainForm->XmlScanner->LoadFromFile(entreeNom);
//    MainForm->XmlScanner->Execute();
//    MainForm->XmlScanner->StartScan();

	while (MainForm->XmlScanner->XmlParser->Scan()) {
		switch (MainForm->XmlScanner->XmlParser->CurPartType) {
		case ptStartTag:
			s = MainForm->XmlScanner->XmlParser->CurName;
			break;
		case ptEmptyTag:
			break;
		case ptCData:
			break;
		case ptEndTag:
			break;
		case ptPI:
			break;
		case ptContent:
			s = MainForm->XmlScanner->XmlParser->CurContent;
			break;
		default:
			break;
		}
	}
}
