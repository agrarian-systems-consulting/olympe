//---------------------------------------------------------------------------

#ifndef AideEmpLTH
#define AideEmpLTH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAideEmpLTFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TRichEdit	*RichEdit1;
	void __fastcall Memo1Click(TObject *Sender);
	void __fastcall RichEdit1ContextPopup(TObject *Sender,
			TPoint &MousePos, bool &Handled);
	void __fastcall RichEdit1Enter(TObject *Sender);
	void __fastcall RichEdit1SelectionChange(TObject *Sender);
private: // D�clarations utilisateur
public:// D�clarations utilisateur
	__fastcall TAideEmpLTFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAideEmpLTFrm *AideEmpLTFrm;
//---------------------------------------------------------------------------
#endif
