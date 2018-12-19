//---------------------------------------------------------------------------

#ifndef OutilH
#define OutilH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <Grids.hpp>
#include <Clipbrd.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TOutilFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RG;
private: // Déclarations de l'utilisateur
	TStringList *SLRestaurer;
	AnsiString AsFileExcel;
	int ColCB,RowCB;
	Variant vMSExcel;
	Variant vFileName,vXLWorkbook,vXLWorkbooks;
	Variant vLink,vReadOnly;
	Variant vValue,vRange,vCell;
	Variant vWorksheet,vSheetName;
	Variant vSaveChanges;
	char* Range(int i,int j);
	void RetirerSepMillier(AnsiString &as);

public:// Déclarations de l'utilisateur
	bool ClipboardFormatOK(int noFormat);
	bool CopierClipboard(void);
	void LireClipBoard(TStringGrid *sG,int col,int row);
	int EcrireClipBoard(TStringGrid *sg,int cDebSel,int rDebSel,
			int cFinSel,int rFinSel);
	void Restaurer(TStringGrid *sG,int cDebSel,int rDebSel,
			int cFinSel,int rFinSel);
	void VersExcel(TStringGrid *sG,
			int cDebSel,int rDebSel,int cFinSel,int rFinSel);
	void DExcel(TStringGrid *sG,
			int cDebSel,int rDebSel,int cFinSel,int rFinSel);

	AnsiString L_Excel;
	void TexteChaine ();
	__fastcall TOutilFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOutilFrm *OutilFrm;
//---------------------------------------------------------------------------
#endif
