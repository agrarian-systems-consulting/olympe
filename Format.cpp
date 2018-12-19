//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "Resultat.h"
//#include "Graph.h"
#include "Format.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormatFrm *FormatFrm;
//---------------------------------------------------------------------------
__fastcall TFormatFrm::TFormatFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TFormatFrm::FormActivate(TObject *Sender)
{
	ComboBoxTrait->Enabled=false;
	ScrollBarEpai->Enabled=false;
	ButtonColor->Enabled=false;
	PanelColor->Enabled=false;

	RadioGroup->Items->Clear();
	/*  111002
	 PanelColor2->Color=GraphiqueFrm->Chart->Gradient->EndColor;

	 for(int t=0;t<ResultatFrm->LBGauche->Items->Count;t++)
	 {
	 if (GraphiqueFrm->Series1->Active==true)
	 RadioGroup->Items->AddObject(ResultatFrm->LBGauche->Items->Strings[t],(TObject*)GraphiqueFrm->Series->Objects[t]);
	 else
	 RadioGroup->Items->AddObject(ResultatFrm->LBGauche->Items->Strings[t],(TObject*)GraphiqueFrm->Series->Objects[t+10]);
	 }
	 RadioGroup->ItemIndex=0;    //171001
	 EditTitre->Text=GraphiqueFrm->Chart->Title->Text->Text.Trim();
	 EditAbsG->Text=GraphiqueFrm->Chart->LeftAxis->Title->Caption;
	 // EditAbsD->Text=GraphiqueFrm->Chart->RightAxis->Title->Caption;
	 EditOrd->Text=GraphiqueFrm->Chart->BottomAxis->Title->Caption;
	 */
}
//---------------------------------------------------------------------------

void __fastcall TFormatFrm::RadioGroupClick(TObject *Sender)
{
	ButtonColor->Enabled=true;
	PanelColor->Enabled=true;
	/*  111002
	 PanelColor->Color=((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->SeriesColor;
	 if(GraphiqueFrm->Series1->Active==true)
	 {
	 ScrollBarEpai->Enabled=true;
	 ScrollBarEpai->Position=((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->LinePen->Width;
	 LabelEpai->Caption="Epaisseur : "+(AnsiString)ScrollBarEpai->Position;
	 ComboBoxTrait->Enabled=true;
	 ComboBoxTrait->ItemIndex=((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->LinePen->Style;
	 }
	 */
}
//---------------------------------------------------------------------------

void __fastcall TFormatFrm::ComboBoxTraitChange(TObject *Sender)
{
	/*111002
	 ((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->LinePen->Width=1;
	 ((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->LinePen->Style=(TPenStyle)(ComboBoxTrait->ItemIndex+1);
	 ScrollBarEpai->Position=((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->LinePen->Width;
	 LabelEpai->Caption="Epaisseur : "+(AnsiString)ScrollBarEpai->Position;
	 */
}
//---------------------------------------------------------------------------

void __fastcall TFormatFrm::ButtonColorClick(TObject *Sender)
{
	/*111002
	 if (ColorDialog->Execute())
	 {
	 ((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->SeriesColor=ColorDialog->Color;
	 PanelColor->Color=((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->SeriesColor;
	 }
	 */
}
//---------------------------------------------------------------------------

void __fastcall TFormatFrm::ButtoncolorfondClick(TObject *Sender)
{
	/*111002
	 if (ColorDialog->Execute())
	 {
	 GraphiqueFrm->Chart->Gradient->EndColor=ColorDialog->Color;
	 PanelColor2->Color=GraphiqueFrm->Chart->Gradient->EndColor;
	 }
	 */
}
//---------------------------------------------------------------------------

void __fastcall TFormatFrm::CheckBox3DClick(TObject *Sender)
{
	/*111002
	 if (CheckBox3D->Checked==true)
	 GraphiqueFrm->Chart->View3D=true;
	 else
	 GraphiqueFrm->Chart->View3D=false;
	 */
}
//---------------------------------------------------------------------------

void __fastcall TFormatFrm::ScrollBarEpaiChange(TObject *Sender)
{
	/*111002
	 LabelEpai->Caption="Epaisseur : "+(AnsiString)ScrollBarEpai->Position;
	 ((TLineSeries*)RadioGroup->Items->Objects[RadioGroup->ItemIndex])->LinePen->Width=ScrollBarEpai->Position;
	 */
}
//---------------------------------------------------------------------------
void __fastcall TFormatFrm::EditTitreChange(TObject *Sender)
{
	/*111002

	 GraphiqueFrm->Chart->Title->Text->Text=EditTitre->Text;
	 GraphiqueFrm->Chart->Refresh();
	 */
}
//---------------------------------------------------------------------------
void __fastcall TFormatFrm::EditAbsGChange(TObject *Sender)
{
	/*111002

	 GraphiqueFrm->Chart->LeftAxis->Title->Caption=EditAbsG->Text;
	 GraphiqueFrm->Chart->Refresh();
	 */
}
//---------------------------------------------------------------------------

void __fastcall TFormatFrm::EditOrdChange(TObject *Sender)
{
	/*111002

	 GraphiqueFrm->Chart->BottomAxis->Title->Caption=EditOrd->Text;
	 GraphiqueFrm->Chart->Refresh();
	 */
}
//---------------------------------------------------------------------------

