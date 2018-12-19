//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Util.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
int IsalnumA(unsigned char c) {
// prise en compte de é à etc
	if (isalnum(c))
		return 1;
	if (c == '_')
		return 1;
	if (c == '.')
		return 1;
	if (c == 27)
		return 1; //  '
	if (c >= 128 && c <= 176)
		return 1;
	if (c >= 224 && c <= 244)
		return 1;

	return 0;
}
