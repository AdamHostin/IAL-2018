
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam předá
** někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int errflg;
int solved;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	
	L->First = NULL;
	L->Act = NULL;
	
return;
}

void DisposeList (tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
	
	L->Act = L->First;				// Nastavi prvy prvok ako aktivny 
	
	while(L->Act != NULL){			//Pokial existuje aktivny prvok

		L->First = L->Act->ptr;		// Nastavi novy prvy prvok 
		free(L->Act);				// Uvolni aktualny aktivny prvok 
		L->Act = L->First;			// Nastavi novy prvy prvok ako aktivny 
	}
return;
}

void InsertFirst (tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
    

	tElemPtr NFirst = malloc(sizeof(struct tElem));
	
    if (NFirst  == NULL){		// Ak alokacia nezdarila vola sa Error() a konci 
    
		Error();
		return;
	}
	
	NFirst->data = val;			// Do datovej zlozky noveho prvku vlozi obsah val 
	NFirst->ptr = L->First;		// Novy prvy prvok zoznamu bude ukazovat na povodny prvy prvok zoznamu 
	L->First = NFirst; 			// Novy prvok zoznamu bude nastaveny ako zaciatocny 
return;
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	
	L->Act = L->First;
return;
}

void CopyFirst (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	
	if (L->First != NULL){ 		//Ak prvy prvok existuje
	
		*val = L->First->data;	// Ak je zoznam neprazdny ulozi data na adresu *val 
	}
	else{
		Error();				// Inak zavola Error()
	} 
return;
}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
	
	if (L->First != NULL){				//Ak prvy prvok existuje
	
		if (L->Act == L->First){
			L->Act = NULL;				// Ak je prvy prvok aktivny, aktivita sa nastavi na NULL 
		}
		L->First = L->First->ptr;		// Prvým prvkom sa stáva nasledujúci prvok 
	}
return;
} 	

void PostDelete (tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
	
	if ((L->Act != NULL) && (L->Act->ptr != NULL)){	//ak existuju aktivny prvok a prvok za aktivnym prvkom
	
		tElemPtr tmp = L->Act->ptr;		// Do premennej tmp vloži prvok za aktivnym prvkom 
		L->Act->ptr = tmp->ptr;			// Ako nasledujuci prvok nastavi prvok za prvkom ktory je vymazany
		free(tmp);
	}
return;
}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	
	if (L->Act != NULL){					//Ak prvy prvok existuje
	
		tElemPtr tmp = NULL;
		if ((tmp = malloc(sizeof(struct tElem))) == NULL){			// Ak sa malloc nezdari zavola sa  funkcia Error() a končí sa
		
			Error();
		}
		else{
			tmp->data = val;			// Do datovej casti tmp sa ulozi hodnota val 
			tmp->ptr = L->Act->ptr;		// Prvok za tmp bude ukazovat na prvok za aktivnim prvkom
			L->Act->ptr = tmp;			// tmp sa priradi aktualnemu prvku
		}
	}
return;
}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	
	if (L->Act != NULL)				//Ak existuje aktivny prvok, inak zavola Error()
	{
		*val = L->Act->data;		// Data aktivneho prvku priradi do *val
	}
	else{
		Error();						
	}
return;
}

void Actualize (tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
	
	
	if (L->Act != NULL){				//Ak existuje aktivny prvok
		L->Act->data = val;			//val sa priradi aktivnemu prvku
	}
return;
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
	
	if (L->Act != NULL){				//Ak existuje aktivny prvok
		L->Act = L->Act->ptr;		// Presunie aktivitu na nasledujuci prvok 
	}
return;
}

int Active (tList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	
	return L->Act != NULL;
}

/* Konec c201.c */
