//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#pragma hdrstop
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "DebutXml.h"
#include "LireXml.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LibXmlComps"
#pragma link "LibXmlParser"
#pragma resource "*.dfm"
TLireXmlFrm *LireXmlFrm;
//---------------------------------------------------------------------------
__fastcall TLireXmlFrm::TLireXmlFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLireXmlFrm::FormActivate(TObject *Sender)
{

	XmlScanner->LoadFromFile(DebutXmlFrm->OpenDialog->FileName);
	Scanner();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TLireXmlFrm::Scanner(void)
{
	int i;

	AnsiString as,asName,asValue;
	XmlScanner->XmlParser->StartScan();
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;

			if(as=="Olympe") break;
			else if(as=="LesSystemeUnite")
			LireLesSystemesUnite(as);
			else if(as=="LesTva")
			LireLesTva(as);
			else if(as=="LesTvaDefaut")
			LireLesTvaDefaut(as);

			else if(as=="LesProduits")
			LireLesItems(as,V_CatProduit,V_Produit);
			else if(as=="LesCharges")
			LireLesItems(as,V_CatCharge,V_Charge);
			else if(as=="LesExternalites")
			LireLesItems(as,V_CatExternalite,V_Externalite);
			else if(as=="LesTroupeaux")
			LireLesBestiaux(as,V_CatBestiaux,V_Bestiaux);
			else if(as=="LesCalendriers")
			LireLesCalendriers(as,V_Calendrier);

			else if(as=="LesChargesStructure")
			LireLesItems(as,V_CatChStruct,V_ChStruct);
			else if(as=="LesDepensesDiverses")
			LireLesItems(as,V_CatDepDiv,V_DepDiv);
			else if(as=="LesRecettesDiverses")
			LireLesItems(as,V_CatRecDiv,V_RecDiv);
			else if(as=="LesDepensesPrivees")
			LireLesItems(as,V_CatDepFam,V_DepFam);
			else if(as=="LesRecettesPrivees")
			LireLesItems(as,V_CatRecFam,V_RecFam);

			else if(as=="LesVariables")
			LireLesItems(as,V_CatVar,V_Variable);
			else if(as=="LesEspeces")
			LireLesEspeces(as);

			else if(as=="LesCultures")
			LireLesAteliers(as,V_CatCulture,V_Culture);
			else if(as=="LesAnimaux")
			LireLesAteliers(as,V_CatAnimaux,V_Animaux);
			else if(as=="LesVivriers")
			LireLesAteliers(as,V_CatVivrier,V_Vivrier);
			else if(as=="LesPerennes")
			LireLesAteliers(as,NULL ,V_Perenne);

			else if(as=="LesIndicateurs")
			LireLesIndicateurs(as);
			else break;
			break;
			/*
			 case ptEmptyTag:
			 as=XmlScanner->XmlParser->CurName;
			 if(as=="Olympe")  ;
			 else if(as=="LesSystemeUnite")  LireLesSystemesUnite();
			 else if(as=="LesTva")           LireLesTva();
			 for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
			 {
			 asName=XmlScanner->XmlParser->CurAttr->Name(i);
			 asValue=XmlScanner->XmlParser->CurAttr->Value(i);
			 }
			 break;
			 case ptContent:
			 as=XmlScanner->XmlParser->CurName;
			 break;
			 case ptCData:
			 as=XmlScanner->XmlParser->CurName;
			 break;
			 */
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Olympe") return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
/*

 - <LesSystemeUnite>
 <SystemeUnite uAtelier="f" uEntreprise="f" uRegion="Kf" ratio21="1.000000" ratio32="1000.000000" monnaie="O" />
 <SystemeUnite uAtelier="q" uEntreprise="q" uRegion="T" ratio21="1.000000" ratio32="10.000000" monnaie="N" />
 */
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesSystemesUnite(AnsiString balise)
{
	int i;
	AnsiString as,asName,asValue;
	CL_SystemeUnite *sys;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptEmptyTag:
			sys=new CL_SystemeUnite();
			as=XmlScanner->XmlParser->CurName;
			for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
			{
				asName=XmlScanner->XmlParser->CurAttr->Name(i);
				asValue=XmlScanner->XmlParser->CurAttr->Value(i);
				if (asName=="uAtelier") sys->UUt=asValue;
				else if(asName=="uEntreprise") sys->UTrans=asValue;
				else if(asName=="uRegion") sys->UGlobal=asValue;
				else if(asName=="ratio21") sys->Ratio=(float)asValue.ToDouble();
				else if(asName=="ratio32") sys->RatioG=(float)asValue.ToDouble();
				else if(asName=="monnaie") sys->Monnaie=asValue[1];
			}
			//penser au numero maintenant inutile
			// verifier si existe
			V_SystemeUnite->ins(sys);
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
/*
 - <LesTva>
 <tva nom="SansTva" taux="1.000000" />
 <tva nom="reduit" taux="5.100000" />
 <tva nom="normal" taux="21.000000" />
 </LesTva>
 */
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesTva(AnsiString balise)
{
	int i;
	AnsiString as,asName,asValue;
	CL_Tva *tva;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptEmptyTag:
			tva=new CL_Tva();
			as=XmlScanner->XmlParser->CurName;
			for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
			{
				asName=XmlScanner->XmlParser->CurAttr->Name(i);
				asValue=XmlScanner->XmlParser->CurAttr->Value(i);
				if(asName=="nom")tva->Nom=asValue;
				else if(asName=="taux")tva->Taux=(float)asValue.ToDouble();
			}
			V_Tva->ins(tva);
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
/*
 - <LesTvaDefaut>
 <TvaDefaut nom="reduit" />
 <TvaImmo nom="reduit" />
 </LesTvaDefaut>
 */
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesTvaDefaut(AnsiString balise)
{
	int i;
	AnsiString as,asName,asValue;
	CL_Tva *tva;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="TvaDefaut") tva=TvaDefaut;
			else if(as=="TvaImmo") tva=TvaImmo;
			tva=tva; //aew
			for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
			{
				asName=XmlScanner->XmlParser->CurAttr->Name(i);
				asValue=XmlScanner->XmlParser->CurAttr->Value(i);
				if(asName=="nom") tva=V_Tva->trouve(asValue);
			}
			break;

			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
/*
 - <LesProduits>

 - <Categorie nom="Abricots">
 <Item nom="abricot cal1" prix="6000.000000" unite="T" tva="reduit" />
 <Item nom="abricot cal2" prix="5000.000000" unite="T" tva="reduit" />
 <Item nom="test" prix="6.000000" unite="kg" tva="reduit" />
 <Item nom="divers" prix="1.000000" unite="f" tva="reduit" />
 </Categorie>
 */
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesItems(AnsiString balise,
		CL_Vecteur<CL_Categorie> *vCat,
		CL_Vecteur<CL_Item> *vItem)

{
	int i;
	AnsiString as,asName,asValue;
	CL_Categorie *cat;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Categorie")
			{
				cat=new CL_Categorie();
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if(asName=="nom")
					{
						cat->Nom=asValue;
						vCat->ins(cat);
						break; //je sors du for
					}
				}
				LireItem(as,cat,vItem);
				break;
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
//  <Item nom="abricot cal1" prix="6000.000000" unite="T" tva="reduit" />
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireItem(AnsiString balise,CL_Categorie *cat,
		CL_Vecteur<CL_Item> *vItem)
{
	int i;
	AnsiString as,asName,asValue;
	CL_Item *item;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			item=new CL_Item();
			item->Categorie=cat;
			for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
			{
				asName=XmlScanner->XmlParser->CurAttr->Name(i);
				asValue=XmlScanner->XmlParser->CurAttr->Value(i);
				if (asName=="nom") item->Nom=asValue;
				else if(asName=="prix") item->Prix=(float)asValue.ToDouble();
				else if(asName=="unite")item->SysUnite=TrouveSystemeUnite(asValue);
				else if(asName=="tva") item->Tva=V_Tva->trouve(asValue);
			}
			vItem->ins(item);
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
CL_SystemeUnite* TLireXmlFrm::TrouveSystemeUnite(AnsiString UUt) {
	int i;
	CL_SystemeUnite *sysUnite;
	for (i = 0; i < V_SystemeUnite->Nbelt; i++) {
		sysUnite = V_SystemeUnite->Vecteur[i];
		if (sysUnite->UUt == UUt)
			return sysUnite;
	}
	return NULL;
}

//------------------------------------------------------------------------------------
/*
 - <LesTroupeaux>
 - <Troupeau nom="divers">
 <Animal nom="Vache" valInv="0.000000" Prix="0.000000" tva="reduit" /> 
 <Animal nom="g PAV" valInv="0.000000" Prix="0.000000" tva="reduit" /> 
 </Troupeau>
 - <Troupeau nom="Laitier">
 - <Animal nom="VL" valInv="10000.000000" Prix="10000.000000" tva="reduit">
 <origine no="2" /> 
 <genere no="5" taux="50.000000" /> 
 <genere no="6" taux="50.000000" /> 
 </Animal>
 - <Animal nom="VL1" valInv="12000.000000" Prix="12000.000000" tva="reduit">
 <origine no="3" /> 
 <genere no="5" taux="50.000000" />
 <genere no="6" taux="50.000000" /> 
 </Animal>
 - <Animal nom="Gpav" valInv="8000.000000" Prix="8000.000000" tva="reduit">
 <origine no="4" /> 
 </Animal>
 - <Animal nom="G12 24" valInv="6000.000000" Prix="6000.000000" tva="reduit">
 <origine no="5" /> 
 </Animal>
 <Animal nom="G0 12" valInv="3000.000000" Prix="3000.000000" tva="reduit" />
 <Animal nom="Male" valInv="1000.000000" Prix="1000.000000" tva="reduit" />
 </Troupeau>
 <Troupeau nom="bidon" />
 </LesTroupeaux>

 */

//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesBestiaux(AnsiString balise,
		CL_Vecteur<CL_Categorie> *vCat,
		CL_Vecteur<CL_Bestiaux> *vBestiaux)

{
	int i;
	AnsiString as,asName,asValue;
	CL_Categorie *cat;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Troupeau")
			{
				cat=new CL_Categorie();
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if(asName=="nom")
					{
						cat->Nom=asValue;
						vCat->ins(cat);
						break; //je sors du for
					}
				}
				LireBestiaux(as,cat,vBestiaux);
				break;
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
/*
 - <LesTroupeaux>
 - <Troupeau nom="divers">
 <Animal nom="Vache" valInv="0.000000" Prix="0.000000" tva="reduit" />
 <Animal nom="g PAV" valInv="0.000000" Prix="0.000000" tva="reduit" />
 </Troupeau>
 - <Troupeau nom="Laitier">
 - <Animal nom="VL" valInv="10000.000000" Prix="10000.000000" tva="reduit">
 <origine no="2" />
 <genere no="5" taux="50.000000" />
 <genere no="6" taux="50.000000" />
 </Animal>
 - <Animal nom="VL1" valInv="12000.000000" Prix="12000.000000" tva="reduit">
 <origine no="3" />
 <genere no="5" taux="50.000000" />
 <genere no="6" taux="50.000000" />
 </Animal>
 - <Animal nom="Gpav" valInv="8000.000000" Prix="8000.000000" tva="reduit">
 <origine no="4" />
 </Animal>
 - <Animal nom="G12 24" valInv="6000.000000" Prix="6000.000000" tva="reduit">
 <origine no="5" />
 </Animal>
 <Animal nom="G0 12" valInv="3000.000000" Prix="3000.000000" tva="reduit" />
 <Animal nom="Male" valInv="1000.000000" Prix="1000.000000" tva="reduit" />
 </Troupeau>
 <Troupeau nom="bidon" />
 </LesTroupeaux>
 */
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireBestiaux(AnsiString balise,CL_Categorie *cat,
		CL_Vecteur<CL_Bestiaux> *vBestiaux)
{
	int i;
	int jDonne;
	AnsiString as,asName,asValue;
	CL_Bestiaux *bestiaux;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Animal")
			{
				bestiaux=new CL_Bestiaux();
				jDonne=0;
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="nom") bestiaux->Nom=asValue;
					else if(asName=="valInv") bestiaux->ValInv=(float)asValue.ToDouble();
					else if(asName=="prix") bestiaux->Prix=(float)asValue.ToDouble();
					else if(asName=="tva") bestiaux->Tva=V_Tva->trouve(asValue);
				}
				vBestiaux->ins(bestiaux);
			}
			break;
			case ptContent:
			as=XmlScanner->XmlParser->CurName;
			break;

			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="origine")
			{
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="no") {bestiaux->NoOrigine=asValue.ToInt();break;}
				}
			}
			else if(as=="genere")
			{
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="no") bestiaux->DonneNo[jDonne]=asValue.ToInt();
					else if(asName=="taux") bestiaux->DonnePcent[jDonne]=(float)asValue.ToDouble();
				}
				jDonne++;
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesCalendriers(AnsiString balise,
		CL_Vecteur<CL_Calendrier> *vCat)
{
	int i;
//int n;
	AnsiString as,asName,asValue;
	CL_Calendrier *calendrier;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Calendrier")
			{
				calendrier=new CL_Calendrier();
				//n=calendrier->V_Periode->Nbelt;
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if(asName=="nom")
					{
						calendrier->Nom=asValue;
						vCat->ins(calendrier);
						break; //je sors du for
					}
				}
				LireCalendrier(as,calendrier);
				break;
			}
			break;

			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireCalendrier(AnsiString balise,CL_Calendrier *calendrier)
{
	int i;
	AnsiString as,asName,asValue;
	CL_Periode *periode;
//int n;
	while(XmlScanner->XmlParser->Scan())
	{
		//n=XmlScanner->XmlParser->CurPartType;
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="LesPeriodes")
			{
				// qu'est ce qu on fait ??
			}
			break;
			case ptContent:
			as=XmlScanner->XmlParser->CurName;
			break;

			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Periode")
			{
				periode=new CL_Periode();
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="nom") periode->Nom=asValue;
					else if(asName=="debut")LirePeriodeBorne(asValue,periode->JDeb,periode->MDeb);
					else if(asName=="fin") LirePeriodeBorne(asValue,periode->JFin,periode->MFin);
//                        else if(asName=="JDebut")periode->JDeb=asValue.ToInt();
//                        else if(asName=="MDebut")periode->MDeb=asValue.ToInt();
//                        else if(asName=="JFin")  periode->JFin=asValue.ToInt();
//                        else if(asName=="MFin")  periode->MFin=asValue.ToInt();
					else if(asName=="heureParJour")periode->HpJ=(float)asValue.ToDouble();
					else if(asName=="PcentDispo") periode->PcentDispo=asValue.ToInt();
				}
				periode->CalculDuree();
				periode->CalculDispo();
				calendrier->V_Periode->ins(periode);
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LirePeriodeBorne(AnsiString asValue,int &x,int &y)
{

}

//------------------------------------------------------------------------------------
/*
 - <LesEspeces>
 <Espece nom="Abricotier" debAmor="3" Maxi="20" Phase="1 3 5 10 15" />
 <Espece nom="Cerisier" debAmor="3" Maxi="15" Phase="1 3 6 12 15" />
 <Espece nom="Framboisier" debAmor="2" Maxi="5" Phase="1 6" />
 <Espece nom="cacao" debAmor="10" Maxi="25" Phase="1 2 10 25" />
 </LesEspeces>
 */
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesEspeces(AnsiString balise)

{
	int i;
	AnsiString as,asName,asValue;
	CL_Espece *espece;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			break;
			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			espece=new CL_Espece();
			for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
			{
				asName=XmlScanner->XmlParser->CurAttr->Name(i);
				asValue=XmlScanner->XmlParser->CurAttr->Value(i);
				if (asName=="nom") espece->Nom=asValue;
				else if(asName=="debAmor") espece->DebAmor=asValue.ToInt();
				else if(asName=="Maxi") espece->DurAmor=asValue.ToInt();
				else if(asName=="Phase") LirePhase(asValue,espece->Phase);
			}
			V_Espece->ins(espece);
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LirePhase(AnsiString as,int* phase)
{
	istringstream iss(as.c_str());
	int n;
	int p;
	n=0;
	while(iss >> p)
	{
		phase[n++]=p;
	}
}
//------------------------------------------------------------------------------------
/*
 - <LesCultures>
 - <Categorie nom="Céréales">
 - <Culture nom="Ble" nbPhase="3">
 - <LesProduits>
 - <Produit nom="blé" categorie="Céréales">
 <phase n="1" val="100.000000" />
 </Produit>
 - <Produit nom="bugday" categorie="Céréales">
 <phase n="1" val="30.000000" />
 </Produit>
 </LesProduits>
 - <LesCharges>
 - <Charge nom="Ammonitrate" categorie="Engrais">
 <phase n="0" val="100.000000" />
 <phase n="1" val="200.000000" />
 </Charge>
 - <Charge nom="Scorie" categorie="Engrais">
 <phase n="1" val="150.000000" />
 </Charge>
 - <Charge nom="triple 12" categorie="Engrais">
 <phase n="1" val="200.000000" />
 </Charge>
 </LesCharges>
 - <LesChargesVolume>
 - <Charge nomProduit="blé" catProduit="Céréales" nomCharge="sac50" catCharge="Emballage">
 <phase n="1" val="2.000000" />
 </Charge>
 </LesChargesVolume>
 - <LesExternalites>
 - <Externalite nom="azote" categorie="Négative">
 <phase n="1" val="0.100000" />
 </Externalite>
 </LesExternalites>
 </Culture>
 */
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesAteliers(AnsiString balise,
		CL_Vecteur<CL_Categorie> *vCat,
		CL_Vecteur<CL_Atelier> *vAtelier)

{
	int i;
	AnsiString as,asName,asValue;
	CL_Categorie *cat;
	CL_Espece *espece;

	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Categorie")
			{
				cat=new CL_Categorie();
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if(asName=="nom")
					{
						cat->Nom=asValue;
						vCat->ins(cat);
						break; //je sors du for
					}
				}
				espece=NULL;
				LireAtelier(as,cat,espece,vAtelier);
			}
			else if(as=="Espece")
			{
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if(asName=="nom")
					{
						espece=V_Espece->trouve(asValue);
						break; //je sors du for
					}
				}
				cat=NULL;
				LireAtelier(as,cat,espece,vAtelier);
				break;
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireAtelier(AnsiString balise,
		CL_Categorie *cat,CL_Espece *espece,
		CL_Vecteur<CL_Atelier> *vAtelier)
{
	int i;
	AnsiString as,asName,asValue;
	CL_Atelier* atelier;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			//- <Culture nom="Ble" nbPhase="3">
			//- <LesProduits>
			//- <Produit nom="blé" categorie="Céréales">

			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Culture"||as=="Animal" ||as=="Vivrier"||as=="Perenne")
			{
				atelier=new CL_Atelier();
				atelier->Categorie=cat;
				atelier->Espece=espece;
				if (as=="Culture")atelier->Nature=CULTURE;
				else if(as=="Animal" )atelier->Nature=ANIMAUX;
				else if(as=="Vivrier")atelier->Nature=VIVRIER;
				else if(as=="Perenne")atelier->Nature=PERENNE;

				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="nom") atelier->Nom=asValue;
					else if(asName=="nbPhase") atelier->NbPhase=asValue.ToInt();
				}
				vAtelier->ins(atelier);
			}
			else if(as=="LesProduits")
			LireProChaAtelier(as,atelier,atelier->V_Produit);
			else if(as=="LesCharges")
			LireProChaAtelier(as,atelier,atelier->V_Charge);
			else if(as=="LesChargesVolume")
			LireChaVolAtelier(as,atelier,atelier->V_ChargeVolume);
			else if(as=="LesExternalites")
			LireProChaAtelier(as,atelier,atelier->V_Externalite);
			break;
			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireProChaAtelier(AnsiString balise,CL_Atelier *atelier,CL_Vecteur<CL_ItemParAtelier> *vItemPA)
{
	int i;
	int n;
	float val;
	AnsiString as,asName,asValue;
	AnsiString asNomItem,asNomCat;
	CL_ItemParAtelier *itemPA;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Produit" || as=="Charge"|| as=="Externalite")
			{
				itemPA=new CL_ItemParAtelier();
				itemPA->QtePhase=new float[atelier->NbPhase];
				memset(itemPA->QtePhase,0,sizeof(float)*atelier->NbPhase);
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="nom") asNomItem=asValue;
					else if(asName=="categorie") asNomCat=asValue;
				}
				itemPA->Item=TrouveItem(as,asNomCat,asNomItem);
				vItemPA->ins(itemPA);
			}
			break;
			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="phase")
			{
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="n") n= asValue.ToInt();
					else if(asName=="val") val=(float)asValue.ToDouble();
				}
				itemPA->QtePhase[n]=val;
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
CL_Item* __fastcall TLireXmlFrm::TrouveItem(AnsiString as,
		AnsiString asNomCat,AnsiString asNomItem)
{
	int n;
	CL_Vecteur<CL_Categorie> *vCat;
	CL_Vecteur<CL_Item> *vItem;

	CL_Categorie *cat;
	CL_Item *item;

	if(as=="Produit")
	{
		vCat=V_CatProduit;
		vItem=V_Produit;
	}
	else if(as=="Charge")
	{
		vCat=V_CatCharge;
		vItem=V_Charge;
	}
	else if(as=="Externalite")
	{
		vCat=V_CatExternalite;
		vItem=V_Externalite;
	}
	else
	return NULL;

	cat=vCat->trouve(asNomCat);
	for(n=0;n<vItem->Nbelt;n++)
	{
		item=vItem->Vecteur[n];
		if(item->Nom==asNomItem && item->Categorie==cat)
		return item;
	}
	return NULL;
}
//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireChaVolAtelier(AnsiString balise,CL_Atelier *atelier,CL_Vecteur<CL_ItemParAtelier> *vItemPA)
{
	int i;
	int n;
	float val;
	AnsiString as,asName,asValue;
	AnsiString asNomProduit,asNomCatProd;
	AnsiString asNomCharge,asNomCatCharge;
	CL_ItemParAtelier *itemPA,*itPAProd;
	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if( as=="Charge")
			{
				itemPA=new CL_ItemParAtelier();
				itemPA->QtePhase=new float[atelier->NbPhase];
				memset(itemPA->QtePhase,0,sizeof(float)*atelier->NbPhase);
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="nomProduit") asNomProduit= asValue;
					else if(asName=="catProduit") asNomCatProd= asValue;
					else if(asName=="nomCharge") asNomCharge= asValue;
					else if(asName=="catCharge") asNomCatCharge=asValue;
				}

				itemPA->Item=TrouveItem(as,asNomCatCharge,asNomCharge);
				vItemPA->ins(itemPA);
				for(i=0;i<atelier->V_Produit->Nbelt;i++)
				{
					itPAProd=atelier->V_Produit->Vecteur[i];
					if(itPAProd->Item->Nom==asNomProduit
							&& itPAProd->Item->Categorie->Nom==asNomCatProd)
					{
						itemPA->ItemPA=itPAProd;
						break;
					}
				}
			}
			break;
			case ptEmptyTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="phase")
			{
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if (asName=="n") n= asValue.ToInt();
					else if(asName=="val") val=(float)asValue.ToDouble();
				}
				itemPA->QtePhase[n]=val;
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}

//------------------------------------------------------------------------------------
void __fastcall TLireXmlFrm::LireLesIndicateurs(AnsiString balise)
{
	int i;
	AnsiString as,asName,asValue;
	CL_Categorie *cat;
	CL_Espece *espece;

	while(XmlScanner->XmlParser->Scan())
	{
		switch(XmlScanner->XmlParser->CurPartType)
		{
			case ptStartTag:
			as=XmlScanner->XmlParser->CurName;
			if(as=="Categorie")
			{
				cat=new CL_Categorie();
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if(asName=="nom")
					{
						cat->Nom=asValue;
//?                           vCat->ins(cat);
						break;//je sors du for
					}
				}
//??                    LireAtelier(as,cat,espece,vAtelier);
			}
			else if(as=="Espece")
			{
				for(i=0;i<XmlScanner->XmlParser->CurAttr->Count;i++)
				{
					asName=XmlScanner->XmlParser->CurAttr->Name(i);
					asValue=XmlScanner->XmlParser->CurAttr->Value(i);
					if(asName=="nom")
					{
						espece=V_Espece->trouve(asValue);
						break; //je sors du for
					}
				}
				cat=NULL;
//??                    LireAtelier(as,cat,espece,vAtelier);
				break;
			}
			break;
			case ptEndTag:
			as=XmlScanner->XmlParser->CurName;
			if(as==balise)
			return;
			break;

		}
	}
}
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/*
 int i;
 AnsiString as,asName,asValue;
 while(XmlScanner->XmlParser->Scan())
 {
 switch(XmlScanner->XmlParser->CurPartType)
 {
 case ptStartTag:
 as=XmlScanner->XmlParser->CurName;
 if(as=="Categorie") { LireItem(as);break;}
 else
 break;

 case ptEndTag:
 as=XmlScanner->XmlParser->CurName;
 if(as==balise)
 return;
 break;

 }
 }
 }
 */

