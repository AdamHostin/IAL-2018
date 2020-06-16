
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2018
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int errflg;
int solved;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
    
	L->First = NULL;
	L->Act = NULL;
	L->Last = NULL;
return;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/
	
	L->Act = L->First;				//Nastavi prvy prvok ako aktivny
	
	while(L->Act != NULL){			//Kym existuje aktivny prvok

		L->First = L->Act->rptr;	// Nastavi nasledujuci prvok ako prvy
		free(L->Act);				// Uvolni aktivny prvok 
		L->Act = L->First;			// Nastavi dalsi prvok ako aktualny 
	}
	L->Last = NULL;
return;
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
tDLElemPtr NFirst = malloc(sizeof(struct tDLElem));		//Alokuje pamat pre novy prvok
	
	if (NFirst == NULL){ 								// V pripade zlyhania alokacie vola DLError() 
		
		DLError();
	}
	else{
		NFirst->data = val;				//Nahra nove data
		NFirst->lptr = NULL;			
		NFirst->rptr = L->First;		// A pointer na nasledujuci prvok nastavi na prvy prvok v zozname 
		if (L->First == NULL){
			L->Last = NFirst;			// Ak je zoznam prázdny nový prvok sa nastavi aj na posledny 
		}
		else{
			L->First->lptr = NFirst;
		}
		L->First = NFirst;
	}
return;
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
	
	tDLElemPtr NLast = NULL;
	
	if ((NLast = malloc(sizeof(struct tDLElem))) == NULL){	//Alokuje pamat pre novy prvok
		DLError();
	}
	else{
		NLast->data = val;
		NLast->lptr = L->Last;			// A pointer na predchadzajuci prvok nastavi na posledny prvok v zozname 
		NLast->rptr = NULL;
		if (L->First == NULL){
			L->First = NLast;			// Ak je zoznam prázdny nový prvok sa nastavi aj na prvy 
		}
		else{
			L->Last->rptr = NLast;
		}
	
	L->Last = NLast;
	}
return;
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	

	L->Act = L->First;
return;
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	
	
 L->Act = L->Last;
return;
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

	
	if (L->First == NULL){			//Ak je zoznam prazdny vola sa DLError()
		DLError();
	}
	else{
		*val = L->First->data;		//Inak sa hodnota prveho prvku skopiruje na miesto kam ukazuje *val
	}
return;
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	
	if (L->First == NULL){			//Ak je zoznam prazdny vola sa DLError()
		DLError();
	}
	else{
		*val = L->Last->data;		//Inak sa hodnota posledneho prvku skopiruje na miesto kam ukazuje *val
	}
return;
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	
	
	if (L->First != NULL){				//Ak zoznam nie je prazdny funkcia pokracuje 

		if (L->Act == L->First){			// Ak je prvy prvok zaroven aktivny aktivita sa nastavi na NULL 
			L->Act = NULL;
		}					
		if (L->First == L->Last){		// Ak má zoznam len jeden prvok je nutne zrusit pointer na prvy aj posledny prvok 
		
			L->First = NULL;
			L->Last = NULL;
		}
		else{
		
			L->First = L->First->rptr;	// Prvym prvkom sa stava nasledujuci prvok 
			L->First->lptr = NULL;
		}	
	}
return;
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	
	if (L->First != NULL){				//Ak zoznam nie je prazdny funkcia pokracuje 

		if (L->Act == L->Last)			// Ak je prvy prvok zaroven aktivny aktivita sa nastavi na NULL 
			L->Act = NULL;				
		if (L->First == L->Last){		// Ak má zoznam len jeden prvok je nutne zrusit pointer na prvy aj posledny prvok 
		
			L->First = NULL;
			L->Last = NULL;
		}
		else{
		
			L->Last = L->Last->lptr;	// Prvym prvkom sa stava nasledujuci prvok 
			L->Last->rptr = NULL;
		}	
	}
return;
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	
	if ((L->Act != NULL) && (L->Act != L->Last)){	// Obratena podmienka zo zadania
	
		tDLElemPtr tmp = L->Act->rptr;				// Do pomocnej premennej tmp si ulozi za aktivnym prvkom 
		L->Act->rptr = tmp->rptr;					// Ako nasledujuci prvok nastavi prvok za prvkom, ktory bude vymazany 
		if (tmp == L->Last){						// Ak je vymazany prvok posledným, aktivny prvok sa stava poslednym 
			L->Last = L->Act;
		}
		else{
			tmp->rptr->lptr = L->Act;				// Inak prepoji prvok za vymazanym prvkom s prvkom aktivnym 
		}
		
		free(tmp);
	}
return;
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	
	if ((L->Act != NULL) && (L->Act != L->First)){ 	// Obratena podmienka zo zadania
		tDLElemPtr tmp = L->Act->lptr;				// Do pomocnej premennej tmp ulozi prvok pred aktivnym prvkom
		L->Act->lptr = tmp->lptr;					// Ako predcházajuci prvok nastavi prvok pred tým, ktory bude vymazany
		if (tmp == L->First){						// Ak je vymazany prvok prvym, aktivny prvok sa stava prvym 
			L->First = L->Act;
		}
		else{
			tmp->lptr->rptr = L->Act;				// Inak prepoji prvok pred vymazanym prvkom s prvkom aktivnym 
		}
		free(tmp);
	}
return;
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
	if (L->Act != NULL){
		
		tDLElemPtr NInsert = malloc(sizeof(struct tDLElem));	// Alokácia
	
		if (NInsert == NULL){
			
			DLError();
			return;
		}
	
		NInsert->data = val;				// Nahra data z val do noveho prvku
		NInsert->lptr = L->Act;				// Nastavi aktivny prvok ako prvok pred novym prvkom
		NInsert->rptr = L->Act->rptr;		// Nastavi prvok za aktivnym prvkom ako prvok za novym prvkom
		L->Act->rptr = NInsert;				// Nastavi novy prvok ako prvok za aktivnym prvkom
		if (L->Act == L->Last){				// Ak je aktivny prvok posledny nastavy novy prvok ako posledny

			L->Last = NInsert;
		}
		else{								// Inak nastavy povodny prvok pred aktivnym prvok ako pred novym prvkom
			NInsert->rptr->lptr = NInsert;
		}
	}
return;
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	
	if (L->Act != NULL){
		
		tDLElemPtr NInsert = malloc(sizeof(struct tDLElem));	// Alokácia
	
		if (NInsert == NULL){

			DLError();
			return;
		}
	
		NInsert->data = val;			// Nahra data z val do noveho prvku
		NInsert->rptr = L->Act;			// Nastavi parametre predchadzajuceho a nasledujuceho prvku pre novy prvok
		NInsert->lptr = L->Act->lptr;
		L->Act->lptr = NInsert;			
		if (L->Act == L->First){		//Nastavi okolite prvky, v pripade potreby novy prvok
			L->First = NInsert;
		}
		else{
			NInsert->lptr->rptr = NInsert;
		}
	}
return;
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/

		
	if (L->Act != NULL){

		*val = L->Act->data;
	}
	else{
		
		DLError();
	}
return;
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
	
	if (L->Act != NULL){		// Ak je zoznam aktivny data aktivneho prvku sa aktualizuju 
		L->Act->data = val;
	}
return;
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	
	if (L->Act != NULL){		// Ak je zoznam aktivny
		
		if (L->Act == L->Last){	// Ak je aktivny prvok posledny aktivita sa nastavi na NULL
			L->Act = NULL;
		}
		else{					// Inak sa aktivita posunie na dalsi prvok
			L->Act = L->Act->rptr; 
		}
	}
return;
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
	
	if (L->Act != NULL){			// Ak je zoznam aktivny
		
		if (L->Act == L->First){	// Ak je aktivny prvok prvy aktivita sa nastavi na NULL
			L->Act = NULL;
		}
		else{						// Inak sa aktivita posunie na predchadzajuci prvok
			L->Act = L->Act->lptr;	
		}
	}
return;
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	
	
 return L->Act != NULL;
}

/* Konec c206.c*/
