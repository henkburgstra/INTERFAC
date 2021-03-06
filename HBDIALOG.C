/*----------------------------------------------------------------------
  HBDIALOG.C
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 27-05-95
  ----------------------------------------------------------------------*/
#include <conio.h>
#include <dos.h>
#include <string.h>
#include "hbwindow.h"
#include "hbdialog.h"
#include "hbtoets.h"
#include "hbinkey.h"
#include "hbcursor.h"

#define FALSE 0
#define TRUE 1

static int Stoppen=FALSE,Pos=0;

/*----------------------------------------------------------------------
  Dialoog
  ----------------------------------------------------------------------*/

int Dialoog(const char **DlgButton,int DlgLoop,const char **DlgTekst,
				const char *DlgTitel,unsigned int DlgAttr,
				void (*DlgFunktie)(void))
{

  int VorigeCursor,LengteButtons=0,AantalButtons=0,LengteTekst=0,
		AantalTekst=0,LengteDialoog=0,i,xPos,yPos,xPos2,yPos2,
		Boven,Links,Onder,Rechts,Toets=0,BeginPos,NieuwePos,Verschuiving;
  unsigned int InversAttr;

  Stoppen=FALSE;
  Pos=0;

  InversAttr=Invers(DlgAttr);
  VorigeCursor=SetCursor(UIT);

  for(AantalButtons=0;DlgButton[AantalButtons];AantalButtons++)
	 LengteButtons+=(strlen(DlgButton[AantalButtons])+4);

  for(AantalTekst=0;DlgTekst[AantalTekst];AantalTekst++)
	 LengteTekst=(strlen(DlgTekst[AantalTekst])>LengteTekst ?
					  strlen(DlgTekst[AantalTekst]) : LengteTekst);

  LengteDialoog=(LengteButtons>LengteTekst ? LengteButtons : LengteTekst+4);

  Boven=13-((AantalTekst+6)/2);
  Links=41-((LengteDialoog+2)/2);
  Onder=Boven+AantalTekst+6;
  Rechts=Links+LengteDialoog;

  MakeWindow(Boven,Links,Onder,Rechts,DUBBEL,DlgAttr);
  TitleWindow(MIDDENBOVEN,DlgTitel);

  for(i=0;DlgTekst[i];i++)
	 PrintcWindow(i+3,DlgTekst[i]);

  BeginPos=xPos=Links+((Rechts-Links+1)/2)-(LengteButtons/2);
  xPos2=xPos-Links+2;
  yPos2=AantalTekst+5;
  yPos=yPos2+Boven-2;

  for(i=0;i<AantalButtons;i++) {
	 Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[i])+1,ENKEL,DlgAttr);
	 gotoxy(xPos2,yPos2);
	 cprintf("%s",DlgButton[i]);
	 xPos+=(strlen(DlgButton[i])+6);
	 xPos2=xPos-Links+2;
  }

  if (DlgFunktie) {
	 (*DlgFunktie)();
	 if (Pos != -1)
		Stoppen=FALSE;
  }

  textattr(InversAttr);
  xPos=BeginPos;
  xPos2=xPos-Links+2;
  Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[Pos])+1,DUBBEL,DlgAttr);
  gotoxy(xPos2,yPos2);
  cprintf("%s",DlgButton[0]);

  while(!Stoppen) {

	 NieuwePos=Pos;

	 Toets=hbInkey(0);

	 switch(Toets) {

	 case K_LEFT:
	 case K_SH_TAB:
		  if (Pos>0) {
			 NieuwePos--;
			 Verschuiving=-(strlen(DlgButton[NieuwePos])+6);
		  }
		  else
			 if (DlgFunktie) {
				Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[Pos])+1,ENKEL,DlgAttr);
				textattr(DlgAttr);
				gotoxy(xPos2,yPos2);
				cprintf("%s",DlgButton[Pos]);
				(*DlgFunktie)();
				if (Pos != -1)
				  Stoppen=FALSE;
				Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[Pos])+1,DUBBEL,DlgAttr);
				textattr(InversAttr);
				gotoxy(xPos2,yPos2);
				cprintf("%s",DlgButton[Pos]);
			 }
		  break;

	 case K_RIGHT:
	 case K_TAB:
		  if (Pos<(AantalButtons-1)) {
			 NieuwePos++;
			 Verschuiving=strlen(DlgButton[Pos])+6;
		  }
		  break;

	 case K_ENTER:
		  if (Pos == (DlgLoop-1)) {
			 Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[Pos])+1,ENKEL,DlgAttr);
			 textattr(DlgAttr);
			 gotoxy(xPos2,yPos2);
			 cprintf("%s",DlgButton[Pos]);
			 (*DlgFunktie)();
			 if (Pos != -1)
				Stoppen=FALSE;
			 Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[Pos])+1,DUBBEL,DlgAttr);
			 textattr(InversAttr);
			 gotoxy(xPos2,yPos2);
			 cprintf("%s",DlgButton[Pos]);
		  }
		  else
			 Stoppen=TRUE;

		  break;

	 case K_ESC:
		  Pos=-1;
		  Stoppen=TRUE;
		  break;

	 }

	 if (NieuwePos != Pos && Pos > -1) {
		Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[Pos])+1,ENKEL,DlgAttr);
		textattr(DlgAttr);
		gotoxy(xPos2,yPos2);
		cprintf("%s",DlgButton[Pos]);
		xPos+=Verschuiving;
		xPos2=xPos-Links+2;
		Pos=NieuwePos;
		Box(yPos,xPos,yPos+2,xPos+strlen(DlgButton[Pos])+1,DUBBEL,DlgAttr);
		textattr(InversAttr);
		gotoxy(xPos2,yPos2);
		cprintf("%s",DlgButton[Pos]);
	 }

  }

  RemoveWindow();
  SetCursor(VorigeCursor);

  return(Pos+1);

}

/*----------------------------------------------------------------------
  EindeDialoog
  ----------------------------------------------------------------------*/
void EindeDialoog(void)
{

  Pos=-1;
  Stoppen=TRUE;

}

/*----------------------------------------------------------------------
  FoutToon
  ----------------------------------------------------------------------*/
void FoutToon(void)
{

  sound(100);
  delay(300);
  nosound();

}

/*
EOF HBDIALOG.C
------------------------------------------------------------------------*/