//---------------------------------------------------------------------------

#ifndef GereProcedureH
#define GereProcedureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <dir.h>
#include <vector.h>
#include <vector.h>
#include "GereComparaison.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
//#include <msxmldom.hpp>
//#include <XMLDoc.hpp>
//#include <xmldom.hpp>
//#include <XMLIntf.hpp>
//#include <algorithm>

using namespace std;

#include "GereComparaison.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
/*
 #include <msxmldom.hpp>
 #include <XMLDoc.hpp>
 #include <xmldom.hpp>
 #include <XMLIntf.hpp>
 #include <algorithm>

 using namespace std;
 */
//#include "GereComparaison.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
/*
 #include <msxmldom.hpp>
 #include <XMLDoc.hpp>
 #include <xmldom.hpp>
 #include <XMLIntf.hpp>
 */
#include "GereComparaison.h"

//---------------------------------------------------------------------------
class TGereProcedureFrm: public TGereComparaisonFrm {
	__published: // Composants gérés par l'EDI
TOpenDialog	*OpenDProcedure;
	TBitBtn *BtBnLesProcedures;
	TXMLDocument *XMLDoc;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall TVClick(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtAtelierCopierClick(TObject *Sender);
	void __fastcall BtBnFermerClick(TObject *Sender);
	void __fastcall BtAtelierSupprimerClick(TObject *Sender);
	void __fastcall BtAtelierCreerClick(TObject *Sender);
	void __fastcall BtAtelierModifClick(TObject *Sender);
	void __fastcall BtBnLesProceduresClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);

private: // Déclarations de l'utilisateur
	bool __fastcall DemanderNomFichierProcedure(void);
	void TGereProcedureFrm::CreerNomFichProcedure(void);

protected:
	virtual bool __fastcall CEstBon(void);
	virtual void __fastcall StockerOrdre(void);
	void __fastcall BtCatCopierClick(TObject *Sender);

	bool __fastcall VerifNomProcedure(AnsiString newNom,int action);

	//xml
//    bool __fastcall LireXml(void);
	void __fastcall CreeLesProceduresTxt(AnsiString s);

public:// Déclarations de l'utilisateur
	CL_Procedure *Procedure;
	bool __fastcall LireXml(void);
	virtual void __fastcall CreeTV(void);
	//provisoire
	AnsiString NomFichierProcedure;
	// utilisé par DefProcedure
	void __fastcall EcrireXml(void);
	void __fastcall EcrireXmlTxt(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GereProcedureFrm;
	AnsiString LC_BtBnLesProcedures;
	AnsiString LC_GBAtelier;

	__fastcall TGereProcedureFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereProcedureFrm *GereProcedureFrm;
//---------------------------------------------------------------------------
#endif
