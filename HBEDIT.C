/*----------------------------------------------------------------------
  HBEDIT.C
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 12-06-95
  ----------------------------------------------------------------------*/
#include <alloc.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include "hbtoets.h"
#include "hbcursor.h"
#include "hbinkey.h"
#include "hbedit.h"

#define FALSE 0
#define TRUE 1

#define ONBEKEND 0
#define NUMERIEK 1

static int Type,Insert=TRUE,Mask;

EditLijst_t *VolgendVeld(EditLijst_t *HuidigeEdit,EditLijst_t *NieuweEdit,
								 char *WerkEdit);

void VerwerkMask(EditLijst_t *Edit, char *WerkEdit);
void VerwijderMask(EditLijst_t *HuidigeEdit, char *WerkEdit);

/*----------------------------------------------------------------------
  Edit
  ----------------------------------------------------------------------*/
void hbEdit(EditKop_t *EditBlok,int Nummer)
{

  int Toets,Pos=0,VorigeCursor,Doorgaan=TRUE,i,Geldig;
  char WerkEdit[90],Kopie[90];
  EditLijst_t *HuidigeEdit,*BeginEdit;

  Type=ONBEKEND;
  HuidigeEdit=EditBlok->Eerste;

  for (i=0;i<EditBlok->Aantal;i++) {
	 if (Nummer==(i+1)) {
		BeginEdit=HuidigeEdit;
		textattr(HuidigeEdit->Data->EditKleur);
	 }
	 else
		textattr(HuidigeEdit->Data->Kleur);
	 gotoxy(HuidigeEdit->Data->x,HuidigeEdit->Data->y);
	 cputs(HuidigeEdit->Data->Tekst);
	 HuidigeEdit=HuidigeEdit->Volgende;
  }

  HuidigeEdit=BeginEdit;
  Mask=(strlen(HuidigeEdit->Data->Mask) > 0);

  VerwerkMask(HuidigeEdit,WerkEdit);

  VorigeCursor=SetCursor(AAN);

  if (!Insert)
	 SetCursor(HALF);

  while (Doorgaan) {

	 if (Pos==strlen(WerkEdit))
		Pos--;

	 textattr(HuidigeEdit->Data->EditKleur);
	 gotoxy(HuidigeEdit->Data->x+Pos,HuidigeEdit->Data->y);

	 Toets=hbInkey(0);

	 switch (Toets) {

	 case K_HOME:
		  Pos=0;
		  break;

	 case K_END:
		  Pos=strlen(WerkEdit)-1;
		  break;

	 case K_LEFT:
		  Pos=(Pos > 0 ? --Pos : Pos);
		  break;

	 case K_RIGHT:
		  Pos=(Pos < (strlen(WerkEdit)-1) ? ++Pos : Pos);
		  break;

	 case K_INS:
		  if (Insert) {
			 Insert=FALSE;
			 SetCursor(HALF);
		  }
		  else {
			 Insert=TRUE;
			 SetCursor(AAN);
		  }
		  break;

	 case K_DEL:
		  for (i=Pos;i<strlen(WerkEdit);i++)
			 WerkEdit[i]=(i==(strlen(WerkEdit)-1) ? ' ' : WerkEdit[i+1]);
		  cputs(WerkEdit+Pos);
		  break;

	 case K_BS:
		  if (Pos>0) {
			 Pos--;
			 gotoxy(HuidigeEdit->Data->x+Pos,HuidigeEdit->Data->y);
			 if (Insert) {
				for (i=Pos;i<strlen(WerkEdit);i++)
				  WerkEdit[i]=(i==(strlen(WerkEdit)-1) ? ' ' : WerkEdit[i+1]);
				cputs(WerkEdit+Pos);
			 }
			 else {
				WerkEdit[Pos]=' ';
				cputs(" ");
			 }
		  }
		  break;

	 case K_CTRL_Y:
		  for (i=0;i<strlen(WerkEdit);i++)
			 WerkEdit[i]=' ';
		  Pos=0;
		  gotoxy(HuidigeEdit->Data->x+Pos,HuidigeEdit->Data->y);
		  cputs(WerkEdit);
		  break;

	 case K_SH_TAB:
	 case K_UP:
		  if (HuidigeEdit->Vorige) {
			 if ((HuidigeEdit->Data->Controle ?
					(*HuidigeEdit->Data->Controle)(WerkEdit) : TRUE)) {
				HuidigeEdit=VolgendVeld(HuidigeEdit,HuidigeEdit->Vorige,WerkEdit);
				Pos=0;
			 }
		  }
		  else
			 Doorgaan=!(HuidigeEdit->Data->Controle ?
							(*HuidigeEdit->Data->Controle)(WerkEdit) : TRUE);
		  break;

	 case K_ESC:
		  Doorgaan=FALSE;
		  break;

	 case K_ENTER:
	 case K_TAB:
	 case K_DOWN:
		  if (HuidigeEdit->Volgende) {
			 if ((HuidigeEdit->Data->Controle ?
					(*HuidigeEdit->Data->Controle)(WerkEdit) : TRUE)) {
				HuidigeEdit=VolgendVeld(HuidigeEdit,HuidigeEdit->Volgende,WerkEdit);
				Pos=0;
			 }
		  }
		  else
			 Doorgaan=!(HuidigeEdit->Data->Controle ?
			            (*HuidigeEdit->Data->Controle)(WerkEdit) : TRUE);
		  break;

	 default:
		  if (Toets>0) {

			 Geldig=TRUE;

			 if (Mask)

				switch (HuidigeEdit->Data->Mask[Pos]) {

				case '9':
					 if (!isdigit(Toets))
						Geldig=FALSE;
					 break;

				case '!':
					 if (isalpha(Toets))
						Toets=toupper(Toets);
					 break;

				case 'a':
					 if (!isalpha(Toets))
						Geldig=FALSE;
					 break;

				case 'A':
					 if (isalpha(Toets))
						Toets=toupper(Toets);
					 else
						Geldig=FALSE;
					 break;

				case 'N':
					 if (!isascii(Toets))
						Geldig=FALSE;
					 break;

				case 'X':
					 break;

				default:
					 if (HuidigeEdit->Data->Mask[Pos] != Toets)
						Geldig=FALSE;
					 break;

				}

			 if (Geldig) {

				if (Insert)
				  strcpy(Kopie,WerkEdit+Pos);
				WerkEdit[Pos]=Toets;
				cprintf("%c",WerkEdit[Pos]);
				Pos++;
				if (Insert && strlen(Kopie)>1)
				  cputs(strncpy(WerkEdit+Pos,Kopie,(strlen(WerkEdit)-Pos)));

			 }

		  }

		  break;


	 }

  }

  textattr(HuidigeEdit->Data->Kleur);
  gotoxy(HuidigeEdit->Data->x,HuidigeEdit->Data->y);
  cputs(WerkEdit);

  EditBlok->LaatsteToets=Toets;
  VerwijderMask(HuidigeEdit,WerkEdit);
  SetCursor(VorigeCursor);

}

/*----------------------------------------------------------------------
  VerwerkMask
  ----------------------------------------------------------------------*/
void VerwerkMask(EditLijst_t *Edit,char *WerkEdit)
{

  char *TempMask,*TempEdit;

  #define MASK Edit->Data->Mask

  if (strlen(MASK))
	 strcpy(WerkEdit,MASK);
  else
	 strcpy(WerkEdit,Edit->Data->Tekst);

  if (strlen(MASK)) {

	 TempMask=strchr(WerkEdit,'.');

	 if (TempMask && !strchr(TempMask,'.')) {

		Type=NUMERIEK;
		strset(TempMask+1,'0');
		TempEdit=strchr(Edit->Data->Tekst,'.');

		if (TempEdit)
		  strncpy(TempMask+1,TempEdit+1,strlen(TempEdit+1));

		strrev(Edit->Data->Tekst);
		strrev(WerkEdit);

		TempMask=strchr(WerkEdit,'.');
		TempEdit=strchr(Edit->Data->Tekst,'.');

		if (TempEdit)
		  TempEdit++;
		else
		  TempEdit=Edit->Data->Tekst;

		TempMask++;

		while (*TempEdit) {

		  if (*TempMask != ',')

			 *TempMask=*TempEdit++;

		  TempMask++;

		}

		while (*TempMask) {

		  if (*TempMask != ',')

			 *TempMask=' ';

		  TempMask++;

		}

		strrev(Edit->Data->Tekst);
		strrev(WerkEdit);

	 }
	 else {

		TempMask=WerkEdit;
		TempEdit=Edit->Data->Tekst;

		while (*TempEdit) {

		  if (!strchr(",.()-/",*TempMask))

			 *TempMask=*TempEdit++;

		  TempMask++;

		}

		while (*TempMask) {

		  if (!strchr(",.()-/",*TempMask))

			 *TempMask=' ';

		  TempMask++;

		}


	 }

  }

}

/*----------------------------------------------------------------------
  VerwijderMask
  ----------------------------------------------------------------------*/
void VerwijderMask(EditLijst_t *HuidigeEdit, char *WerkEdit)
{

  char *TokenString="      ",*TempString;

  TempString=HuidigeEdit->Data->Tekst;

  if (strlen(HuidigeEdit->Data->Mask) > 0) {

	 if (Type==NUMERIEK)
		strcpy(TokenString,",()-/");
	 else
		strcpy(TokenString,",.()-/");

	 while (*TempString) {

		if (!strchr(TokenString,*WerkEdit))

		  *TempString++=*WerkEdit;

		WerkEdit++;

	 }

  }
  else

	 strcpy(HuidigeEdit->Data->Tekst,WerkEdit);

}

/*----------------------------------------------------------------------
  VolgendVeld
  ----------------------------------------------------------------------*/
EditLijst_t *VolgendVeld(EditLijst_t *HuidigeEdit,EditLijst_t *NieuweEdit,
								 char *WerkEdit)
{

  textattr(HuidigeEdit->Data->Kleur);
  gotoxy(HuidigeEdit->Data->x,HuidigeEdit->Data->y);
  cputs(WerkEdit);
  VerwijderMask(HuidigeEdit,WerkEdit);
  HuidigeEdit=NieuweEdit;
  Mask=(strlen(HuidigeEdit->Data->Mask) > 0);
  VerwerkMask(HuidigeEdit,WerkEdit);
  textattr(HuidigeEdit->Data->EditKleur);
  gotoxy(HuidigeEdit->Data->x,HuidigeEdit->Data->y);
  cputs(WerkEdit);

  return(HuidigeEdit);

}

/*----------------------------------------------------------------------
  EditNieuw
  ----------------------------------------------------------------------*/
EditKop_t *EditNieuw(void)
{

  EditKop_t *Nieuw;

  Nieuw=(EditKop_t *) malloc(sizeof(EditKop_t));

  if (Nieuw) {
	 Nieuw->Aantal=0;
	 Nieuw->Eerste=Nieuw->Laatste=NULL;
	 Nieuw->LaatsteToets=0;
  }
  else
	 exit(1);

  return(Nieuw);

}

/*----------------------------------------------------------------------
  NieuwElement
  ----------------------------------------------------------------------*/
EditLijst_t *NieuwElement(EditData_t *Data,EditLijst_t *Vorige,
								 EditLijst_t *Volgende)
{

  EditLijst_t *Nieuw;

  Nieuw=(EditLijst_t *) malloc(sizeof(EditLijst_t));

  if (Nieuw) {
	 Nieuw->Data=Data;
	 Nieuw->Vorige=Vorige;
	 Nieuw->Volgende=Volgende;
  }
  else
	 exit(1);

  return(Nieuw);

}

/*----------------------------------------------------------------------
  EditInvoegen
  ----------------------------------------------------------------------*/
EditLijst_t *EditInvoegen(EditKop_t *EditBlok,
								  EditLijst_t *Positie,
								  const char *Tekst,
								  const char *Mask,
								  const char *Picture,
								  int y,
								  int x,
								  unsigned int EditKleur,
								  unsigned int Kleur,
								  int (*Voorwaarde)(struct EditLijst *Element),
					           int (*Controle)(char *Veldwaarde))
{

  EditLijst_t *Nieuw;
  EditData_t *Data;

  Data=(EditData_t *) malloc(sizeof(EditData_t));
  if (!Data)
	 exit(1);
  Data->Tekst=(char *) calloc(strlen(Tekst)+1,sizeof(char));
  if (!Data->Tekst)
	 exit(1);
  strcpy(Data->Tekst,Tekst);
  Data->Mask=(char *) calloc(strlen(Mask)+1,sizeof(char));
  if (!Data->Mask)
	 exit(1);
  strcpy(Data->Mask,Mask);
  Data->Picture=(char *) calloc(strlen(Picture)+1,sizeof(char));
  if (!Data->Picture)
	 exit(1);
  strcpy(Data->Picture,Picture);
  Data->y=y;
  Data->x=x;
  Data->EditKleur=EditKleur;
  Data->Kleur=Kleur;
  Data->Voorwaarde=Voorwaarde;
  Data->Controle=Controle;

  if (Positie) {                    /* Er moet worden ingevoegd */
	 Nieuw=NieuwElement(Data,Positie->Vorige,Positie);
	 if (Nieuw) {
		if (Nieuw->Vorige)
		  Nieuw->Vorige->Volgende=Nieuw;
		else
		  EditBlok->Eerste=Nieuw;
		Positie->Vorige=Nieuw;
		EditBlok->Aantal++;
	 }
  }
  else {                            /* Er moet worden toegevoegd */
	 if (EditBlok->Laatste) {
		Nieuw=NieuwElement(Data,EditBlok->Laatste,NULL);
		if (Nieuw) {
		  EditBlok->Laatste->Volgende=Nieuw;
		  EditBlok->Laatste=Nieuw;
		  EditBlok->Aantal++;
		}
	 }
	 else {                          /* EditBlok is leeg */
		Nieuw=NieuwElement(Data,NULL,NULL);
		if (Nieuw) {
		  EditBlok->Eerste=Nieuw;
		  EditBlok->Laatste=Nieuw;
		  EditBlok->Aantal++;
		}
	 }
  }

  return(Nieuw);

}

/*----------------------------------------------------------------------
  WisElement
  ----------------------------------------------------------------------*/
void WisElement(EditKop_t *EditBlok,EditLijst_t *EditElement)
{

  if (EditElement->Vorige)
	 EditElement->Vorige->Volgende=EditElement->Volgende;
  else
	 EditBlok->Eerste=EditElement->Volgende;

  if (EditElement->Volgende)
	 EditElement->Volgende->Vorige=EditElement->Vorige;
  else
	 EditBlok->Laatste=EditElement->Vorige;

  EditBlok->Aantal--;
  free(EditElement->Data->Tekst);
  free(EditElement->Data->Mask);
  free(EditElement->Data->Picture);
  free(EditElement->Data);
  free(EditElement);

  return;

}

/*----------------------------------------------------------------------
  WisEditBlok
  ----------------------------------------------------------------------*/
void WisEditBlok(EditKop_t *EditBlok)
{

  while(EditBlok->Laatste)
	 WisElement(EditBlok,EditBlok->Laatste);

  free(EditBlok);

  return;

}

/*
EOF HBEDIT.C
------------------------------------------------------------------------*/
