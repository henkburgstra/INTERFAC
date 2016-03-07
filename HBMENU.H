/*----------------------------------------------------------------------
  HBMENU.H
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 30-04-95
  ----------------------------------------------------------------------*/

struct Menu_m {
  struct Menu_m *Volgende;
  struct Menu_m *Vorige;
  struct Menu_m *Moeder;
  struct Optie_m *EersteOptie;
  struct Optie_m *LaatsteOptie;
  struct MenuData_m *Data;
};

typedef struct Menu_m Menu_t;

struct MenuData_m {
  int y;
  int x;
  char *Titel;
  int MenuHelp;
  int Aantal;
};

typedef struct MenuData_m MenuData_t;

struct Optie_m {
  struct Optie_m *Volgende;
  struct Optie_m *Vorige;
  struct OptieData_m *Data;
};

typedef struct Optie_m Optie_t;

struct OptieData_m {
  char *OptieTekst;
  char Kiezer;
  char *StatusRegel;
  void far (*Funktie)(void);
  int Enabled;
};

typedef struct OptieData_m OptieData_t;

void InitMenu(void);
Menu_t near *CreateMenu(char *Titel,int y,int x,int MenuHelp);
void AddItem(Menu_t *Menu,char *OptieTekst,char Kiezer,
		       char *StatusRegel,void far (*Funktie)(void),int Enabled);
void EnableItem(Menu_t *Menu,int Optie);
void DisableItem(Menu_t *Menu,int Optie);
void MenuLoop(Menu_t *StartMenu);
int ExecuteMenu(Menu_t *Menu);

/*
EOF HBMENU.H
------------------------------------------------------------------------*/