//---------------------------------------------------------------------------

#ifndef TVActionH
#define TVActionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVActionFrm: public TForm {
	__published: // Composants gérés par l'EDI
TTreeView	*TV;
	void __fastcall TVDblClick(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TTVActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVActionFrm *TVActionFrm;
//---------------------------------------------------------------------------
#endif
