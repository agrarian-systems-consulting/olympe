//---------------------------------------------------------------------------

#ifndef AideH
#define AideH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TAideFrm: public TForm {
	__published: // Composants gérés par l'EDI
TLabel	*LabTest;
//	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
private:// Déclarations de l'utilisateur

	bool ChargerHtmlHelp(void);
	bool EstCree;
	HWND m_hWindow;
	AnsiString AsNomFichAide;
	DWORD m_Cookie;

public:// Déclarations de l'utilisateur
//HTML_HELP_PROC Mon_HtmlHelp;

	bool Initialiser(char langue);
	char Langue;
	void AfficherAide(char langue,int HelpContextId);
	void Fermer(void);

	__fastcall TAideFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAideFrm *AideFrm;
//---------------------------------------------------------------------------
#endif
