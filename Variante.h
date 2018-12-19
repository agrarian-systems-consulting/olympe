//---------------------------------------------------------------------------
#ifndef VarianteH
#define VarianteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVVarianteFrm: public TForm {
	__published: // Composants gérés par l'EDI
TTreeView	*TV;
	void __fastcall FormResize(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TTVVarianteFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVVarianteFrm *TVVarianteFrm;
//---------------------------------------------------------------------------
#endif
