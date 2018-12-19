//---------------------------------------------------------------------------

#ifndef TVChoixRepartH
#define TVChoixRepartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

#include "OlympeDec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"

//---------------------------------------------------------------------------
class TTVChoixRepartFrm: public TForm {
	__published: // Composants gérés par l'EDI
TTreeView	*TV;
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall TVExpanded(TObject *Sender, TTreeNode *Node);
private: // Déclarations utilisateur
	void __fastcall Definir(void);
	void __fastcall Copier(void);
	void __fastcall Choisir(void);
	void __fastcall NouvelleCat(void);
	CL_Categorie *Categorie;
public:// Déclarations utilisateur
	AnsiString AFaire;
	TTreeNode* TrouverPere(TTreeView *tv,TTreeNode *tn0);

	__fastcall TTVChoixRepartFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixRepartFrm *TVChoixRepartFrm;
//---------------------------------------------------------------------------
#endif
