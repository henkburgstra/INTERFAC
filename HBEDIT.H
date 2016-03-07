/*----------------------------------------------------------------------
  HBEDIT.H
  Copyright 1995 H.G.Burgstra
  Datum laatste wijziging: 07-03-95
  ----------------------------------------------------------------------*/

typedef struct {
  char *Tekst,*Mask,*Picture;
  int y,x;
  unsigned int EditKleur,Kleur;
  int (*Voorwaarde) (struct EditLijst *Element);
  int (*Controle) (char *Veldwaarde);
} EditData_t;

struct EditLijst {
  struct EditLijst *Volgende;
  struct EditLijst *Vorige;
  EditData_t *Data;
};

typedef struct EditLijst EditLijst_t;

struct EditKop {
  struct EditLijst *Eerste;
  struct EditLijst *Laatste;
  int Aantal;
  int LaatsteToets;
};

typedef struct EditKop EditKop_t;

void hbEdit(EditKop_t *EditBlok,int Nummer);
EditKop_t *EditNieuw(void);
EditLijst_t *NieuwElement(EditData_t *Data,EditLijst_t *Vorige,
								 EditLijst_t *Volgende);
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
								  int (*Controle)(char *Veldwaarde));
void WisElement(EditKop_t *EditBlok,EditLijst_t *EditElement);
void WisEditBlok(EditKop_t *EditBlok);


/*
EOF HBEDIT.H
------------------------------------------------------------------------*/