/*----------------------------------------------------------------------
  HBWINDOW.C
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 15-06-95
  ----------------------------------------------------------------------*/

#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include "hbwindow.h"
#include "hbcursor.h"

static int far *VideoAdres;
static int hWnd=-1;
static hbWindow *WindowStruc[MAXWINDOWS];
static unsigned int aKleur[]={1,1,1,1,1};

/*----------------------------------------------------------------------
  MakeWindow
  ----------------------------------------------------------------------*/
void MakeWindow(int Boven,int Links,int Onder,int Rechts,
		int Stijl,unsigned int Attr)
{

  if (hWnd<MAXWINDOWS-1) {

    hWnd++;
    WindowStruc[hWnd]=(hbWindow *) malloc(sizeof(hbWindow));

	 WindowStruc[hWnd]->Clip=(char *)
	 malloc(((Onder-Boven+2)*(Rechts-Links+3))*2);

    gettextinfo(&WindowStruc[hWnd]->TextInfo);

	 gettext(Links,Boven,Rechts+2,Onder+1,WindowStruc[hWnd]->Clip);

    textattr(Attr);
    window(Links,Boven,Rechts,Onder);
    clrscr();
	 if (Stijl)
      Box(Boven,Links,Onder,Rechts,Stijl,Attr);
    Schaduw(Boven,Links,Onder,Rechts);

  }

}

/*----------------------------------------------------------------------
  TitleWindow
  ----------------------------------------------------------------------*/
void TitleWindow(int Positie,const char *Titel)
{

  int x,y,Lengte;
  struct text_info TextInfo;

  Lengte=strlen(Titel);
  gettextinfo(&TextInfo);

  switch(Positie) {

  case LINKSBOVEN:

      x=2;
      y=1;
      break;

  case MIDDENBOVEN:

		x=((TextInfo.winright-TextInfo.winleft+3)/2)-(Lengte/2);
		y=1;
		break;

  case RECHTSBOVEN:

		x=TextInfo.winright-TextInfo.winleft+1-Lengte;
		y=1;
		break;

  case LINKSONDER:

		x=2;
		y=TextInfo.winbottom-TextInfo.wintop+1;
		break;

  case MIDDENONDER:
		x=((TextInfo.winright-TextInfo.winleft+3)/2)-(Lengte/2);
		y=TextInfo.winbottom-TextInfo.wintop+1;
      break;

  case RECHTSONDER:

      x=TextInfo.winright-TextInfo.winleft+1-Lengte;
      y=TextInfo.winbottom-TextInfo.wintop+1;
      break;

  }

  gotoxy(x,y);
  cprintf("%s",Titel);

}

/*----------------------------------------------------------------------
  PrintcWindow
  ----------------------------------------------------------------------*/
void PrintcWindow(int Regel,const char *Tekst)
{

  int x,Lengte;
  struct text_info TextInfo;

  Lengte=strlen(Tekst);
  gettextinfo(&TextInfo);

  x=((TextInfo.winright-TextInfo.winleft+3)/2)-(Lengte/2);

  gotoxy(x,Regel);
  cprintf("%s",Tekst);


}

/*----------------------------------------------------------------------
  hbPrint
  ----------------------------------------------------------------------*/
void hbPrint(int y,int x,const char *Tekst,unsigned int Attr)
{

  int VorigeCursor;
  struct text_info TextInfo;

  gettextinfo(&TextInfo);
  VorigeCursor=SetCursor(UIT);

  textattr(Attr);
  window(x,y,80,25);
  cputs(Tekst);
  SetCursor(VorigeCursor);

  window(TextInfo.winleft,TextInfo.wintop,
			TextInfo.winright,TextInfo.winbottom);
  textattr(TextInfo.attribute);
  gotoxy(TextInfo.curx,TextInfo.cury);

}

/*----------------------------------------------------------------------
  ClearWindow
  ----------------------------------------------------------------------*/
void ClearWindow(void)
{

  int i,j;
  unsigned char Teken;
  struct text_info TextInfo;

  if (hWnd>=0) {

    gettextinfo(&TextInfo);
    Teken=' ';

    for(i=TextInfo.wintop;i<TextInfo.winbottom-1;i++)
      for(j=TextInfo.winleft;j<TextInfo.winright-1;j++)
	*(VideoAdres+(i*80)+j)=Teken | (TextInfo.attribute << 8);

  }

}

/*----------------------------------------------------------------------
  RemoveWindow
  ----------------------------------------------------------------------*/
void RemoveWindow(void)
{

  struct text_info TextInfo;

  if (hWnd>=0) {

    gettextinfo(&TextInfo);

	 puttext(TextInfo.winleft,TextInfo.wintop,TextInfo.winright+2,
				TextInfo.winbottom+1,WindowStruc[hWnd]->Clip);

	 window(WindowStruc[hWnd]->TextInfo.winleft,
		WindowStruc[hWnd]->TextInfo.wintop,
		WindowStruc[hWnd]->TextInfo.winright,
		WindowStruc[hWnd]->TextInfo.winbottom);

	 textattr(WindowStruc[hWnd]->TextInfo.attribute);

	 free(WindowStruc[hWnd]->Clip);
	 hWnd--;
  }

}

/*----------------------------------------------------------------------
  HideWindow
  ----------------------------------------------------------------------*/
void HideWindow(void)
{

  ToggleWindow();

}

/*----------------------------------------------------------------------
  ShowWindow
  ----------------------------------------------------------------------*/
void ShowWindow(void)
{

  ToggleWindow();

}

/*----------------------------------------------------------------------
  ToggleWindow
  ----------------------------------------------------------------------*/
void ToggleWindow(void)
{

  struct text_info TextInfo;
  char *Clip;
  int Grootte;

  if (hWnd>=0) {

	 gettextinfo(&TextInfo);

	 Grootte=((TextInfo.winbottom-TextInfo.wintop+2)*
				(TextInfo.winright-TextInfo.winleft+3))*2;
	 Clip=(char *) malloc(Grootte);

	 gettext(TextInfo.winleft,TextInfo.wintop,TextInfo.winright+2,
				TextInfo.winbottom+1,Clip);

	 puttext(TextInfo.winleft,TextInfo.wintop,TextInfo.winright+2,
				TextInfo.winbottom+1,WindowStruc[hWnd]->Clip);

	 memcpy(WindowStruc[hWnd]->Clip,Clip,Grootte);
	 free(Clip);

  }

}

/*----------------------------------------------------------------------
  Box
  ----------------------------------------------------------------------*/
void Box(int Boven,int Links,int Onder,int Rechts,
	      int Stijl,unsigned int Attr)
{

  unsigned char LinksBoven,RechtsBoven,LinksOnder,RechtsOnder,
		Horizontaal,Verticaal;
  unsigned int Attrib;
  int i;

  switch (Stijl) {

  case ENKEL:

      LinksBoven='Ú';
      RechtsBoven='¿';
      LinksOnder='À';
      RechtsOnder='Ù';
      Horizontaal='Ä';
      Verticaal='³';
      break;

  case DUBBEL:

      LinksBoven='É';
      RechtsBoven='»';
		LinksOnder='È';
      RechtsOnder='¼';
      Horizontaal='Í';
      Verticaal='º';
      break;

  }

  Attrib=Attr << 8;

  if (Links==Rechts) {
	 *(VideoAdres+((Boven-1)*80)+Links-1)=Verticaal | Attrib;
	 *(VideoAdres+((Onder-1)*80)+Links-1)=Verticaal | Attrib;
  }
  else
	 if (Boven==Onder) {
		*(VideoAdres+((Boven-1)*80)+Links-1)=Horizontaal | Attrib;
		*(VideoAdres+((Boven-1)*80)+Rechts-1)=Horizontaal | Attrib;
	 }
	 else {
		*(VideoAdres+((Boven-1)*80)+Links-1)=LinksBoven | Attrib;
		*(VideoAdres+((Boven-1)*80)+Rechts-1)=RechtsBoven | Attrib;
		*(VideoAdres+((Onder-1)*80)+Links-1)=LinksOnder | Attrib;
		*(VideoAdres+((Onder-1)*80)+Rechts-1)=RechtsOnder | Attrib;
	 }

  for(i=0;i<(Rechts-Links-1);i++) {
	 *(VideoAdres+((Boven-1)*80)+Links+i)=Horizontaal | Attrib;
	 *(VideoAdres+((Onder-1)*80)+Links+i)=Horizontaal | Attrib;
  }

  for(i=0;i<(Onder-Boven-1);i++) {
	 *(VideoAdres+((Boven+i)*80)+Links-1)=Verticaal | Attrib;
	 *(VideoAdres+((Boven+i)*80)+Rechts-1)=Verticaal | Attrib;
  }

}

/*----------------------------------------------------------------------
  BepaalVideo
  ----------------------------------------------------------------------*/
void BepaalVideo(void)
{

  union REGS regs;

  int86(0x11,&regs,&regs);
  VideoAdres=(int far *) ((regs.x.ax & 0x30) == 0x30 ? 0xB0000000L :
              0xB8000000L);

}

/*----------------------------------------------------------------------
  VideoGeheugen
  ----------------------------------------------------------------------*/
int far *VideoGeheugen(void)
{

  return(VideoAdres);

}

/*----------------------------------------------------------------------
   Schaduw
  ----------------------------------------------------------------------*/
void Schaduw(int Boven,int Links,int Onder,int Rechts)
{

  int i,j;
  unsigned int Waarde,Teken;

  for(j=0;j<2;j++)
    for(i=Boven;i<Onder;i++) {
      Waarde=*(VideoAdres+(80*i)+Rechts+j);
      Teken=(Waarde & 0x00ff);
      *(VideoAdres+(80*i)+Rechts+j)=Teken | 0x0700;
    }

  for(i=Links+1;i<(Rechts+2);i++) {
    Waarde=*(VideoAdres+(80*Onder)+i);
    Teken=(Waarde & 0x00ff);
    *(VideoAdres+(80*Onder)+i)=Teken | 0x0700;
  }

}

/*----------------------------------------------------------------------
  Achtergrond
  ----------------------------------------------------------------------*/
void Achtergrond(unsigned char Teken,unsigned int Attr)
{

  int i,j;

  for(i=0;i<25;i++)
    for(j=0;j<80;j++)
      *(VideoAdres+(i*80)+j)=Teken | Attr;

}

/*----------------------------------------------------------------------
  GetColor
  ----------------------------------------------------------------------*/
unsigned int GetColor(int Soort)
{

  unsigned int Kleur;

  Kleur=aKleur[Soort];

  return(Kleur);

}

/*----------------------------------------------------------------------
  SetColor
  ----------------------------------------------------------------------*/
unsigned int SetColor(int Soort,unsigned int Attr)
{

  unsigned int VorigeKleur;

  VorigeKleur=aKleur[Soort];
  aKleur[Soort]=Attr;

  return(VorigeKleur);

}

/*----------------------------------------------------------------------
  Invers
  ----------------------------------------------------------------------*/
unsigned int Invers(unsigned int Attr)
{

  unsigned int InversAttr;

  InversAttr=((Attr ^ 0x00ff) & 0x007f);
/* InversAttr=((DlgAttr ^ 0xffff) & 0xff7f);
	heeft hetzelfde resultaat.                */

  return(InversAttr);

}

/*----------------------------------------------------------------------
  Ogenblikje
  ----------------------------------------------------------------------*/
void Ogenblikje(unsigned int Attr)
{

  MakeWindow(11,26,15,55,DUBBEL,Attr);
  PrintcWindow(3,"Een ogenblikje...");

}

/*
EOF HBWINDOW.C
------------------------------------------------------------------------*/