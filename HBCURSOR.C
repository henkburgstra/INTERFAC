/*----------------------------------------------------------------------
  HBCURSOR.C
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 26-02-95
  ----------------------------------------------------------------------*/
#include <conio.h>
#include <dos.h>
#include "hbcursor.h"

/*----------------------------------------------------------------------
  WijzigCursor
  ----------------------------------------------------------------------*/
void WijzigCursor(int eerste_scanlijn,int laatste_scanlijn)
{

  union REGS regs;
  regs.h.ah=1;            /* Serviceroutine 1, cursorgrootte instellen */
  regs.h.ch=eerste_scanlijn;
  regs.h.cl=laatste_scanlijn;
  int86(BIOS_VIDEO,&regs,&regs);

}

/*----------------------------------------------------------------------
  SetCursor
  ----------------------------------------------------------------------*/
int SetCursor(int Vorm)
{

  static int HuidigeVorm=AAN;
  int OudeVorm;


  OudeVorm=HuidigeVorm;
  HuidigeVorm=Vorm;

  switch(Vorm) {

  case UIT :

		_setcursortype(_NOCURSOR);
		break;

  case AAN :

		_setcursortype(_NORMALCURSOR);
		break;

  case HALF :

		WijzigCursor(8,14);
		break;

  case HEEL :

		_setcursortype(_SOLIDCURSOR);
		break;

  }

  return (OudeVorm);

}


