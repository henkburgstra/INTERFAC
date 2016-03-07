/*----------------------------------------------------------------------
  HBWINDOW.H
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 15-06-95
  ----------------------------------------------------------------------*/
#define MAXWINDOWS 20

#define GEEN 0
#define ENKEL 1
#define DUBBEL 2

#define LINKSBOVEN 0
#define MIDDENBOVEN 1
#define RECHTSBOVEN 2
#define LINKSONDER 3
#define MIDDENONDER 4
#define RECHTSONDER 5

#define POPUP_KLEUR 0
#define MENU_KLEUR 1
#define ACHTERGROND_KLEUR 2
#define FOUT_KLEUR 3
#define HELP_KLEUR 4

typedef struct {
  char *Clip;
  struct text_info TextInfo;
} hbWindow;

void MakeWindow(int Boven,int Links,int Onder,int Rechts,
		int Stijl,unsigned int Attr);
void TitleWindow(int Positie,const char *Titel);
void PrintcWindow(int Regel,const char *Tekst);
void hbPrint(int y,int x,const char *Tekst,unsigned int Attr);
void ClearWindow(void);
void RemoveWindow(void);
void HideWindow(void);
void ShowWindow(void);
void ToggleWindow(void);
void Box(int Boven,int Links,int Onder,int Rechts,
	 int Stijl,unsigned int Attr);
void BepaalVideo(void);
int far *VideoGeheugen(void);
void Schaduw(int Boven,int Links,int Onder,int Rechts);
void Achtergrond(unsigned char Teken,unsigned int Attr);
unsigned int GetColor(int Soort);
unsigned int SetColor(int Soort,unsigned int Attr);
unsigned int Invers(unsigned int Attr);
void Ogenblikje(unsigned int Attr);

/*
EOF HBWINDOW.H
------------------------------------------------------------------------*/