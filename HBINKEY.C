/*----------------------------------------------------------------------
  HBINKEY.C
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 03-06-95
  ----------------------------------------------------------------------*/
#include <stdlib.h>
#include <conio.h>
#include <bios.h>
#include <time.h>
#include "hbinkey.h"
#include "hbtoets.h"
#include "hbwindow.h"
#include "help.h"

static int TijdX=70,TijdY=1;
static unsigned int Kleur=WHITE+(RED<<4);

/*----------------------------------------------------------------------
  hbInkey
  ----------------------------------------------------------------------*/
int hbInkey(int Tijdsduur)
{

  int Toets;
  time_t BeginTijd=0;
  char HuidigeTijd[9];

  Tijdsduur++;   /* WEGHALEN !!!!! alleen om warning te vermijden. */
  /* BeginTijd=time(NULL); */

  for(;;) {
	 /* Doe van alles en nog wat. */
	 /* Kijk of er een muistoets is ingedrukt etc. */
	 if ((time(NULL)-BeginTijd) >= 1) {
		_strtime(HuidigeTijd);
		hbPrint(TijdY,TijdX,HuidigeTijd,Kleur);
		BeginTijd=time(NULL);
	 }

	 if (bioskey(1)>0) {
		Toets=bioskey(0);
		Toets=((Toets & 0xff)==0 ? -(Toets>>8) : (Toets & 0xff));

		if (Toets==K_F1)
		  Help();
		else
		  break;
	 }
  }

  return(Toets);

}

/*----------------------------------------------------------------------
  TijdYX
  ----------------------------------------------------------------------*/
void TijdYX(int Y, int X)
{

  TijdY=Y;
  TijdX=X;

}

/*----------------------------------------------------------------------
  TijdKleur
  ----------------------------------------------------------------------*/
void TijdKleur(unsigned int NieuweKleur)
{

  Kleur=NieuweKleur;

}

/*
EOF HBINKEY.C
------------------------------------------------------------------------*/