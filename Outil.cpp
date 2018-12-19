//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include <Clipbrd.hpp>
#include <utilcls.h>

#include "Main.h"
#include "CL_Trad.h"

#include "Outil.h"
/*
 test excel 2007  xlsx remplacé par xlsxx
 */
//------------------------modifier le 19/08/2010 par Rebaubier William-------
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOutilFrm *OutilFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TOutilFrm::TOutilFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool TOutilFrm::ClipboardFormatOK(int noFormat) {
	int noF;

	/*
	 n=CF_TEXT;        1
	 n=CF_BITMAP;      2
	 n=CF_METAFILEPICT;3
	 n=CF_PICTURE;
	 n=CF_COMPONENT;
	 */
	for (int i = 0; i < Clipboard()->FormatCount; i++) {
		noF = Clipboard()->Formats[i];
		if (noF == noFormat) //CF_BITMAP)
			return true;
	}
	switch (noFormat) {
	case CF_BITMAP:
		ShowMessage("Clipboard ne contient pas une image Bitmap");
		break;
	case CF_TEXT:
		ShowMessage("Clipboard ne contient pas de Texte");
		break;
	}
	return false;
}

//---------------------------------------------------------------------------
void TOutilFrm::LireClipBoard(TStringGrid *sG, int col0, int row0) {
	int nLu;
	char buf[10000];
	int b;

	char mot[50];
	int m;

	int col, row;
	char car;

	nLu = Clipboard()->GetTextBuf(buf, 10000);
	if (nLu == 0)
		return;

	ColCB = sG->Col;
	RowCB = sG->Row;

	row = row0; //SG->Row;
	col = col0; //SG->Col;
	b = 0;
	m = 0;
//    nLi=1;
	while (1) {
		car = buf[b++];
		if (b >= nLu)
			break;
		switch (car) {
		case 0:
			break;

		case '\r':
		case '\t':
		case ';':
		case ',': //voir les autres séparateurs
		case '\n':
			mot[m] = 0;
			m = 0;
			sG->Cells[col][row] = mot;
			mot[m] = 0;
			col++;
			if (col > sG->ColCount)
				sG->ColCount++;
			if (car == '\n') {
				row++;
				if (row > sG->RowCount)
					sG->RowCount += 10;
				col = col0;
			}
			break;

		default:
			if (car != 34) //"
				mot[m++] = car;
		}
	}

}
//---------------------------------------------------------------------------
int TOutilFrm::EcrireClipBoard(TStringGrid *sg, int cDebSel, int rDebSel,
		int cFinSel, int rFinSel) {
	AnsiString as;
	int c, r;
	//possibilité de restaurer CtrlZ
	if (SLRestaurer == NULL)
		SLRestaurer = new TStringList;
	SLRestaurer->Clear();
	//ShowMessage("EcrireClipBoard");
	Clipboard()->Clear();
	for (r = rDebSel; r < rFinSel + 1; r++) {
		for (c = cDebSel; c < cFinSel + 1; c++) {
			SLRestaurer->Add(sg->Cells[c][r]);
			as += sg->Cells[c][r];
			if (c < cFinSel)
				as += '\t';
			else
				as += "\r\n";
		}
	}
	Clipboard()->SetTextBuf(as.c_str());
	Clipboard()->Close();
//    ShowMessage(as);
	return 1;
}
//---------------------------------------------------------------------------
void TOutilFrm::Restaurer(TStringGrid *sG, int cDebSel, int rDebSel,
		int cFinSel, int rFinSel)

		{
	int n;
	int c, r;
	if (SLRestaurer == NULL)
		return;
	n = 0;
	for (r = rDebSel; r < rFinSel + 1; r++) {
		for (c = cDebSel; c < cFinSel + 1; c++) {
			if (n > SLRestaurer->Count)
				return;
			sG->Cells[c][r] = SLRestaurer->Strings[n++];
		}
	}
}
//---------------------------------------------------------------------------
void TOutilFrm::VersExcel(TStringGrid *sG, int cDebSel, int rDebSel,
		int cFinSel, int rFinSel) {
	AnsiString as;
	char *ptr;
	char chaine[10];
	int i, j;

	try {
		AsFileExcel = MainForm->AsDirOlympe + "\\" + "Olympe.xls";
		if (FileExists(AsFileExcel))
			DeleteFile(AsFileExcel.c_str()); //141008

// ouvrir Excel
		vMSExcel = Variant::CreateObject("Excel.Application");
		vMSExcel.OlePropertySet("Visible", true);
		vMSExcel.OlePropertySet("DisplayAlerts", false); //141009
//creer classeur
		vXLWorkbooks = vMSExcel.OlePropertyGet("Workbooks");
		vXLWorkbook = vXLWorkbooks.OleFunction("Add");
//ecrire
		vWorksheet = vXLWorkbook.OlePropertyGet("Worksheets", 1); //141009

		for (i = 0; i < rFinSel; i++) {
			for (j = 0; j < cFinSel; j++) {
				ptr = Range(i, j);
				strcpy(chaine, ptr);
				vRange = chaine;
				as = sG->Cells[j][i];
				RetirerSepMillier(as);
				vValue = as.c_str();
				vCell = vWorksheet.OlePropertyGet("Range", vRange);
				vCell.OlePropertySet("Value", vValue);
			}
		} //??
		vSaveChanges = Unassigned;

		AsFileExcel = MainForm->AsDirOlympe + "\\" + "Olympe.xls";
		vFileName = AsFileExcel.c_str();

		vXLWorkbook.OleFunction("Saveas", vFileName);
		vMSExcel.OlePropertySet("DisplayAlerts", true);
		vMSExcel = Unassigned;
	} catch (Exception *E) {
		ShowMessage(L_Excel);
	}
}
//---------------------------------------------------------------------------
void TOutilFrm::RetirerSepMillier(AnsiString &as) {
	int car;
	char chaine[500];
	int n, i;
	if (as == "")
		return;

	car = as[1];
	if (car < '0' || car > '9')
		return;
	for (n = 1, i = 0; n < as.Length() + 1; n++) //atto 190810
			{
		car = (int) as[n];
		if (car != -96)
			chaine[i++] = car;
	}
	chaine[i] = 0;
	as = chaine;
}

//---------------------------------------------------------------------------
void TOutilFrm::DExcel(TStringGrid *sG, int cDebSel, int rDebSel, int cFinSel,
		int rFinSel) {
	int i, j;
	char *ptr;
	char chaine[10];
	AnsiString as, asFile;
	FILE *fileExcel;

	fileExcel = fopen(AsFileExcel.c_str(), "r");
	if (fileExcel == NULL) {
		ShowMessage("Envoyer d'abord sur Excel");
		return;
	} else
		fclose(fileExcel);

// ouvrir Excel
	vMSExcel = Variant::CreateObject("Excel.Application");

	vFileName = AsFileExcel.c_str();
	vLink = Unassigned;

	//creer classeur
	vXLWorkbooks = vMSExcel.OlePropertyGet("Workbooks");
	vXLWorkbook = vXLWorkbooks.OleFunction("Open", vFileName, vLink, vReadOnly);

	vWorksheet = vXLWorkbook.OlePropertyGet("Worksheets", 1);

	for (i = 0; i < rFinSel; i++) {
		for (j = 0; j < cFinSel; j++) {
			ptr = Range(i, j);
			strcpy(chaine, ptr);
			vRange = chaine;

			vCell = vWorksheet.OlePropertyGet("Range", vRange);
			as = vCell.OlePropertyGet("Value");
			sG->Cells[j][i] = as;
		}
	}

	vMSExcel.OleFunction("Quit");
	vMSExcel = Unassigned;

	DeleteFile(AsFileExcel.c_str());
}
//---------------------------------------------------------------------------
char* TOutilFrm::Range(int i, int j) {
	AnsiString as;
	char range[10];
	char *ptr;
	int a, b;
	/*  i j
	 0 0 A1
	 1 0 A2
	 2 0 A3

	 0 1  B1
	 0 26 Z1
	 0 27 AA1
	 */

	a = j / 26;
	b = j % 26;
	if (a == 0) {
		range[0] = 'A' + b;
		range[1] = 0;
	} else {
		range[0] = 'A' + a - 1;
		range[1] = 'A' + b;
		range[2] = 0;
	}

	as = AnsiString(i + 1);
	ptr = strcat(range, as.c_str());
	return ptr;
}
//========================================================================
void TOutilFrm::TexteChaine(void) {
	L_Excel = T->TrouveTexte("MainForm", "L_Excel");
}
