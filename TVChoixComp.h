//---------------------------------------------------------------------------

#ifndef TVChoixCompH
#define TVChoixCompH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixCompFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TTreeView	*TV;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall TVClick(TObject *Sender);
private: // D�clarations utilisateur
public:// D�clarations utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_TVChoixCompFrm;

	__fastcall TTVChoixCompFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixCompFrm *TVChoixCompFrm;
//---------------------------------------------------------------------------
#endif
