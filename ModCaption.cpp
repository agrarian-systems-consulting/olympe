//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ModCaption.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TModCaptionFrm *ModCaptionFrm;
//---------------------------------------------------------------------------
__fastcall TModCaptionFrm::TModCaptionFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TModCaptionFrm::Button1Click(TObject *Sender)
{
//    ModCaption();
	NomProgramme();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TModCaptionFrm::ModCaption(void)
{
	FILE *FichierLire,*FichierEcrire;
	char chaine[200];
	char nomProg[200];
	char nomVar[200];
	char texteF[100];
	char texteA[100];
	char texteE[100];
	char *fin;
	int n,i;
	FichierLire = fopen("OlympeCaption.csv", "r");
	FichierEcrire = fopen("OlympeCaption2.csv", "w");
	if(FichierLire==NULL)
	{
		ShowMessage(" Pas De Fichier OlympeCaption.csv");
		return;
	}
	if(FichierEcrire==NULL)
	{
		ShowMessage(" Problème OlympeCaption2.csv");
		return;
	}
	while(1)
	{
		fin=fgets(chaine,sizeof(chaine),FichierLire);
		if(fin==NULL) break;

		//ligne vide ou ligne commence par / est ignorée
		if(chaine[0]=='\n' || chaine[0]=='/')
		{
			fputs(chaine,FichierEcrire);
			continue;
		}
		//nomProg
		n=0;i=0; while(chaine[n]!=';')nomProg[i++]=chaine[n++]; nomProg[i]=0;

		//nomVar
		nomVar[0]=0;
		strcat(nomVar,"LC_");
		n++;i=3; while(chaine[n]!=';')nomVar[i++]=chaine[n++]; nomVar[i]=0;

		while(1)
		{
			n++;i=0;
			while(chaine[n]!=';')texteF[i++]=chaine[n++];
			texteF[i]=0;

			n++;i=0;
			if(chaine[n]=='\n')break;
			while(chaine[n]!=';')texteA[i++]=chaine[n++];
			texteA[i]=0;

			n++;i=0;
			if(chaine[n]=='\n')break;
			while(chaine[n]!=';'&& chaine[n]!='\n')texteE[i++]=chaine[n++];
			texteE[i]=0;

			break;
		}
		fprintf(FichierEcrire,"%s;%s;%s;%s\n",nomProg,nomVar,texteF,texteA,texteE);
	}
	fclose(FichierLire);
	fclose(FichierEcrire);
	return;
}
//---------------------------------------------------------------------------
void __fastcall TModCaptionFrm::NomProgramme(void)
{
	FILE *FichierLire,*FichierEcrire;
	char chaine[200];
	char nomProg[200],nomProg0[200];
	char *fin;
	int n,i;
	strcpy(nomProg0,"aaa");
	FichierLire = fopen("OlympeCaption.csv", "r");
	FichierEcrire = fopen("NomProg.txt", "w");
	if(FichierLire==NULL)
	{
		ShowMessage(" Pas De Fichier OlympeCaption.csv");
		return;
	}
	if(FichierEcrire==NULL)
	{
		ShowMessage(" Problème nomProg.csv");
		return;
	}
	while(1)
	{
		fin=fgets(chaine,sizeof(chaine),FichierLire);
		if(fin==NULL) break;

		//ligne vide ou ligne commence par / est ignorée
		if(chaine[0]=='\n' || chaine[0]=='/')
		{
			continue;
		}
		//nomProg
		n=0;i=0; while(chaine[n]!=';')nomProg[i++]=chaine[n++]; nomProg[i]=0;
		if(strcmp(nomProg,nomProg0)!=0)
		{
			fprintf(FichierEcrire,"    %sFrm->TexteCaption();\n",nomProg);
			strcpy(nomProg0,nomProg);
		}
	}
	fclose(FichierLire);
	fclose(FichierEcrire);
	return;
}

