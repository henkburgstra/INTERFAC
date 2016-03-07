/*----------------------------------------------------------------------
  HBDIALOG.H
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 27-05-95
  ----------------------------------------------------------------------*/

int Dialoog(const char **DlgButton,int DlgLoop,const char **DlgTekst,
				const char *DlgTitel,unsigned int DlgAttr,
				void (*DlgFunktie)(void));
void EindeDialoog(void);
void FoutToon(void);				
/*
EOF HBDIALOG.H
------------------------------------------------------------------------*/				
