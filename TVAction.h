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
	__published: // Composants g�r�s par l'EDI
TTreeView	*TV;
	void __fastcall TVDblClick(TObject *Sender);
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur
	__fastcall TTVActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVActionFrm *TVActionFrm;
//---------------------------------------------------------------------------
#endif
