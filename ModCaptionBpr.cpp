//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ModCaption.cpp", ModCaptionFrm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	try {
		Application->Initialize();
		Application->CreateForm(__classid(TModCaptionFrm), &ModCaptionFrm);
		Application->Run();
	} catch (Exception &exception) {
		Application->ShowException(&exception);
	} catch (...) {
		try {
			throw Exception("");
		} catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
