/*///////////////////////////////////////////////////////////////////////////////
//PRZYKLAD DYDAKTYCZNY APLIKACJI DZIALAJACEJ W TRYBIE KONSOLI TEKSTOWEJ ANSI C //
/////////////////////////// Wersja 3, kwiecien'2022 /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//PRAWA AUTORSKIE DO PAKIETU,OPRACOWANIE I KOMENTARZE: PROF.JAROSLAW SZYMANDA  //
/////////////////////////////////////////////////////////////////////////////////
//Przyklad syntaktycznie przygotowany do kompilacji ANSI C w Dev-C++ 5.11      //
//WERSJA INSTALACYJNA Dev-C++ 5.11 DO POBRANIA ZE STRONY KURSU                 //
////////////////////////////////////////////////////////////////////////////// //
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//W ramach zajec projektowych wykorzystujacych pakiet Dev-C++ nie tworzymy plikow
//projektu:*.dev;*.cpp;itd. DOPUSZCZALNE SA WYLACZNIE PLIKI ZRODLOWE *.c i *.h //
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/* BARDZO WAZNE - ABY ZACHOWAC PRAWIDLOWE DZIANIE PROGRAMU W BLOKACH:BEGIN-END 
   NIE NALEZY WPROWADZAC ZADNYCH MODYFIKACJI                                   */

/* W opcjach dla linkera:Narzedzia-->Opcje kompilatora--> -static-libgcc -lws2_32 
   W opcjach dla kompilatora:Narzedzia-->Opcje kompilatora-->Kompilator-->     
   Wytwarzanie/optymalizacja kodu-->Zachowaj zgodnosc ze standardem ANSI C:YES */

/* W USTAWIENIACH REGIONALNYCH SYSTEMU "MS WINDOWS" USTAWIC DOMYSLNIE KROPKE "." 
   JAKO SEPARATOR DZIESIETNY W FORMACIE PREZENTACJI LICZB RZECZYWISTYCH !!!    
   ZLE: 3,14159265; DOBRZE: 3.14159265                                         */
   
/* W opisach interfejsu konsoli oraz panelu graficznego raczej nie stosowac polskich znakow diakrytycznych */

#include <windows.h>
#include <time.h>
#include <winsock.h>
#include <stdio.h>
#include <conio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h> 
#include "sistlib.h"  
#include "cmadsee.h"  

/* UWAGA: poczatek bloku glownej funkcji ANSI C "int main(){..." zostal przeniesiony do */
/* pliku "cmadsee.h" w celu zwiekszenia czytelnosci kodu programu modulu CMADSEE-KLIENT */   







int i,j;

/*BEGIN of initialization of my variables*/


/*All appearence of all letters on specific freq*/
int freq_tab[19][26];
FILE *fp;
/*All freq ; max appearence of letters freq_tab_max[x][0] =freq ; freq_tab_max[x][1] = appearence ; freq_tab_max[x][2] = ascii -65*/
int freq_tab_max[19][3];
/* 4x the highest letters by appearence*/
int freq_four_max[4][3];

int tempe =0;
/*signatures*/
char sig1[] = "ATK:";
char sig2[] = "ATK:";
char kod_1[4];
char kod_2[] = "23432";



int max_local[2]={0,0};



for(i =0 ;i<19;i++)
{
	for(j=0;j<26;j++)
	freq_tab[i][j]=0;
	
}
/*freq[0][0] = freq ; freq[0][1] = powtorzenia ; freq[0][2] = ascii+65*/

for(i =0 ;i<19;i++)
{
	freq_tab_max[i][0]=i;
	
	for(j=1;j<3;j++)
	{
			freq_tab_max[i][j]=0;
	}
	
}

/*max_local[0] = ilosc powtorzen ; max_local[1] = ascii - 65*/

for(i = 0 ;i<2;i++)
{
	max_local[i] = 0;
}



for(i = 0; i<4;i++)
{
	for(j=0;j<3;j++)
	{
		freq_four_max[i][j] = 0;
	}
}
/*END of initialization of my variables*/







double temp;
quit = '\0';    
   
DOUBLE BitBtn3; /* przykladowa zmienna wykorzystywana podczas weryfikacji statusu przycisku BitBtn3 */

system("cls"); /* Czyszczenie okna konsoli trybu tekstowego */

StartSISTLab();/* Automatyczne uruchomienie "Panelu Graficznego" SiSTLab30 */
/*/////////////////////////////////////////////////////////////////////////////*/

BitBtn3=0; /* przykladowa zmienna wykorzystywana podczas weryfikacji statusu przycisku BitBtn3 */

double FxSyg=50.0; /* FxSyg - czestotliwosc harmonicznej podstawowej sygnalu w Hz */ 
double Fp=2500.0;  /* Fp - czestotliwosc probkowania sygnalu w Hz */

RECONNECT: /* etykieta wykorzystywana podczas automatycznego wznawiania polaczenia z CMADSEE-ENGINE */

   /* Uruchomienie WinSock w wersji 2.2, NIE zmieniac tych parametrow */
   WSAStartup(MAKEWORD(2,2), &wsda);
   
   strcpy(adresip,"156.17.32.93"); /* Adres IPv4 podaje prowadzacy zajecia projektowe */   
   strncpy (szAddress, adresip, strlen(adresip)+1);
   gotoxy(30,8); printf( "CMAD-SEE IPv4: %s ",szAddress);
   iPort = 9090; /* Port wykorzystywany przez modul CMADSEE-ENGINE, podaje prowadzacy zajecia projektowe */

   /* Utworzenie gniazda TCP (portu TCP), w naszych projektach wymagamy protokolu "polaczeniowego" */
   s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
   
   /* Sprawdzenie poprawnosci utworzenia gniazda,trzeba zadbac o jego dostepnosc w systemie MS WINDOWS ! */
   /* "Zapora windows" (firewall), programy antywirusowe np: ESET, itp. */

   /* Sprawdzenie poprawnosci utworzenia gniazda, trzeba zadbac o jego dostepnosc w systemie ! */
   if(s == SOCKET_ERROR)
   {
    system("cls");        
    printf("Blad przy inicjalizacji gniazda %d : ", WSAGetLastError()); 
    system("PAUSE");
    exit(1);       
   }

   /* Informacja o hoscie */
   addr.sin_family = AF_INET;
   addr.sin_port = htons(iPort);
   addr.sin_addr.s_addr = inet_addr(szAddress);
             
   /* Laczenie z modulem CMADSEE-ENGINE*/
   gotoxy(0,6);printf("Laczenie z CMADSEE-ENGINE IPv4 %s Port TCP %d ", szAddress,iPort);
   ret = connect(s, (struct sockaddr *) &addr, sizeof(addr));      
      
   /* Sprawdzenie bledu komunikacji z modulem CMADSEE-ENGINE */
   if(ret == SOCKET_ERROR)
   { 
   gotoxy(0,6);printf("\nBlad przy laczeniu z CMADSEE-ENGINE %d: ",WSAGetLastError());             
   licznik=0;  /* OBLIGATORYJNA zmienna monitorujaca poprawne dzialanie klienta CMADSEE-KLIENT */  
   if (kbhit()){if (getch()=='q')goto koniec;};  /* Zakonczenie dzialajacego klienta */
   }

/* Inicjacja ziarna dla generetora liczb pseudolosowych, ZAWSZE potrzebne gdy korzystamy z rand() */
   srand((unsigned)time(NULL));

/**************************************************************************************************/ 
/* REJESTRACJA KLIENTA, czyli danej grupy projektowej, IDENTYFIKATOR przekazuje prowadzacy zajecia*/
   strcpy(szInBuffer ,"XFB-122-199\n"); /* Informacja CMADSEE-ENGINE */
/**************************************************************************************************/ 

/* Wysylamy do CMADSEE-ENGINE pytanie o zgode na rejestracje w systemie CMAD-SEE */
   ret = send(s, szInBuffer, strlen(szInBuffer), 0); 
/* Analizujemy otrzymana odpowiedz */   
   ret = recv(s, szInBuffer, sizeof(szInBuffer), 0);

   if(ret!=-1){  
   /* Jesli rejestracja zostanie potwierdzona, to tutaj jest nasz identyfikator klienta */
   iBufferLen = ret; 
   szInBuffer[iBufferLen] = '\0';   
   gotoxy(0,8);printf("REJESTRACJA: %s \n",szInBuffer);}

   UstawObiekt(13,0,747,345,0,0,0,1,0,0,0);    /*Panel graficzny --> Ustawienie przycisku    "STOP"  */    
   UstawObiekt(13,0,747,345,0,0,0,1,0,0,0);    /*Panel graficzny --> Ustawienie przycisku    "STOP"  */       



















do { /* Poczatek glownej petli modulu klienta CMADSEE-KLIENT, patrz instrukcja do zajec projektowych   */                        

   CzytajObiekt(13,&BitBtn3); /* Panel graficzny--> Odczytywanie statusu przycisku Stop */
   
   gotoxy(0,9); printf("%i  ",licznik);  licznik++; /* Monitorowanie aktywnosci polaczenia z CMADSEE-ENGINE*/     
   strcpy(SYGNATURA ,"NUL\n"); 
   
  /*****************************************************************************************************/   
  /* Wykorzystanie licznika do okresowej komunikacji CMADSEE-ENGINE z naszym klientem,    */   
  /* w celu anulowania polecenia ostatnio wyslanego do CMADSEE-ENGINE, w tym bloku  */   
  /* aktywnym poleceniem jest jedynie "quit=' '" */   
  if((licznik % 10)==0){quit=' ';}; /* Wazne, NIE ZMIENIAC !,trigerowanie odbioru sygnalu komunikacyjnego */
  /*****************************************************************************************************/
   
switch (quit)
{
  case 'a': /* CYBERATAK "ATK:KOD1:KOD2:KILL:END\n" */   
    
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */ 
                         
   if((ATKon>=0)&&(ATKon<=5)){ATKon++; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */
   
   /*Variable that contains freq*/
   int index =0;
   char kod_1[4];
   
   /*##########################Zbieranie maxow ze wszystkich freq##############################*/
   for(i = 0 ;i<19;i++)
{
	max_local[0] = freq_tab[i][0];
	max_local[1] = 0;
	index =i;
	for(j=1;j<26;j++)
	{
		if(max_local[0]<freq_tab[i][j])
		{
			max_local[0] =freq_tab[i][j];
			max_local[1] = j;
			
		}
			
	}
	
	
	
	
	freq_tab_max[i][0] = index;
	freq_tab_max[i][1] = max_local[0];
	freq_tab_max[i][2] = max_local[1];
	
	
	
}


	/*#########################Koniec Sekcji#################################*/
   
   
   /*#####################Sortowanie malejaco i Zbieranie 4 najwiekszych#####################*/
   for (i = 0; i < 19; i++) {
        for (j = 0; j < 19 - i - 1; j++) {
            if (freq_tab[j][1] < freq_tab[j + 1][1]) {
                int temp0 = freq_tab[j][0];
                int temp1 = freq_tab[j][1];
                int temp2 = freq_tab[j][2];
                freq_tab[j][0] = freq_tab[j + 1][0];
                freq_tab[j][1] = freq_tab[j + 1][1];
                freq_tab[j][2] = freq_tab[j + 1][2];
                freq_tab[j + 1][0] = temp0;
                freq_tab[j + 1][1] = temp1;
                freq_tab[j + 1][2] = temp2;
            }
            
    }
		}
    for(i=0;i<4;i++)
    {
    	for(j=0;j<3;j++)
    	{
    		freq_four_max[i][j] = freq_tab_max[i][j];
    		
		}
	}
	/*#########################Koniec Sekcji#################################*/
	/*#####################Sortowanie rosnaco wedlug freq i Zbieranie 4 pierwszych#####################*/
	int buf[3];
    for (i = 0; i < 4 - 1; i++) 
    {
        for (j = 0; j < 4 - i - 1; j++) 
        {
            if (freq_four_max[j][0] > freq_four_max[j + 1][0]) 
            {
                memcpy(buf, freq_four_max[j], sizeof(buf));
                memcpy(freq_four_max[j], freq_four_max[j + 1], sizeof(buf));
                memcpy(freq_four_max[j + 1], buf, sizeof(buf));
            }
        }
    }
    for(i= 0;i<3;i++)
    {
    	
    	kod_1[i] = freq_four_max[i][2]+65;
    	
	}
	kod_1[4]="\0";
	

   
   
   
   
   
   
   strcat(sig1,kod_1);
   strcat(sig1,kod_2);
   strcat(sig1,":KILL:END\n");
   
	fp = fopen("Data.txt", "w");

	fprintf(fp,"%s",sig1);
   	
   	fclose(fp);
   
   
   /*#########################Koniec Sekcji#################################*/
   
   
   /*"ATK:ZZZZ:12345:KILL:END\n"*/
   
   
   strcpy(SYGNATURA ,sig1);     
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};   
  break;
  case 's': 
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */   
   if(STNon==0){STNon=1; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */
   strcpy(SYGNATURA ,"STN:END\n");            
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};     
  break;
  case 'z': /* ODWOLANIE "ATK:KOD1:KOD2:RESET:END\n" */   
   fflush(stdin);quit='\0';  /* Do przemyslenia ... */                            
   if(ATKon>0){ATKon=0; /* Zabezpieczenie przed przypadkowym przepelnieniem bufora komunikacyjnego */ 
   strcat(sig2,kod_1);
   strcat(sig2,kod_2);
   strcat(sig2,":RESET:END\n");
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);};      
  break;  
  /********************************************* NIE ZMIENIAC! *****************************************/
  case ' ': /*Okresowe odczytywanie probek sygnalu z warstwy komunikacyjnej CMAD-SEE, NIE ZMIENIAC !!! */     			 
   strcpy(SYGNATURA ,"SIN:0,0,0,0,0:0#:END\n");              
   fflush(stdin);quit='\0';
   ret = send(s, SYGNATURA, strlen(SYGNATURA), 0);     
   gotoxy(0,11);printf("KOMUNIKAT:                                                                     :");     
   STNon=0;       
  break;
  /*****************************************************************************************************/  
  case 'r': /* Wznowienie/odswiezenie na ZYCZENIE polaczenia CMADSEE-KLIENT z CMADSEE-ENGINE */   
   fflush(stdin);quit='\0';
   WSACleanup();  /* Zamkniecie WinSock */       
   goto RECONNECT;
  break;
  /*****************************************************************************************************/  
}         

SelectTiming = recvTimeOutTCP(s, 0, 100000);/* Weryfikacja statusu polaczenia z CMADSEE-ENGINE */
   
switch (SelectTiming)
{
  case 0:
  /* Caly czas czekamy na jakakolwiek odpowiedz ... */
  /* printf("\nCMADSEE-ENGINE: Oczekiwanie na odpowiedz ....\n"); */    
  break;
  case -1: 
  /* Nie jest dobrze, trzeba dokladniej zweryfikowac warunki polaczenia z CMADSEE-ENGINE */
  /* printf("\nCMADSEE-ENGINE: Problem z komunikacja: %ld\n", WSAGetLastError()); */  
  break;
  default:     
  /* Jest OK, otrzymana odpowiedz przekazujemy do dalszej czesci naszego algorytmu */    
  ret = recv(s, szInBuffer, sizeof(szInBuffer), 0);   

  if(ret!=-1){ /* To nas zabezpiecza przed nieprawidlowym dalszym przetwarzaniem danych */
  iBufferLen = ret;  
  szInBuffer[iBufferLen] = '\0';   /* Do przemyslenia ... */ 
  
  /* Jezeli mamy zamiar poprawnie interpretowac otrzymywane z CMADSEE-ENGINE dane to         */
  /* NIE nalezy zmieniac znacznikow komunikacyjnych takich jak np: "REP:" oraz ":KON" , itp. */
  
  if ((strstr(szInBuffer,"REP:")>0)&&(strstr(szInBuffer,":KON")>0)){    
    
  gotoxy(0,13);printf("SYGNATURA: %s ",szInBuffer);      
  
  strcpy(komunikat,szInBuffer);      /* Procedura wewnetrzna systemu CMAD-SEE */ 
  dekodowanie(komunikat,Ttab,Ytab);  /* Procedura wewnetrzna systemu CMAD-SEE */ 
      
/* Przyklad prezentacji sygnalu. */
/* W projekcie nalezy uwzglednic takze inne obiekty opisane w "SiSTLab-SEE Instrukcja uzytkownika" */   
  UstawWykres (1,30,100,700,250,0,clBlue,1,50,1, 0.0, 10.0,-200.0,200.0,"Sygnal komunikacyjny","Czas [s]","Aplituda sygnalu [-]",Ttab,Ytab,Ttab,Ytab);  
  
  gendft(Ytab,FxSyg,Fp,Atab, Btab);  /* Procedura wewnetrzna systemu CMAD-SEE */       
     
   /* Adding to  */ 
   for(i=0;i<19;i++)
   { 
 		
	   CzytajObiekt(13,&BitBtn3); /* Panel graficzny--> Ponowne odczytywanie statusu przycisku Stop */
	 	
	   Ctab[i+1]=moduldft(Atab[i+1],Btab[i+1]); /* Procedura wewnetrzna systemu CMAD-SEE */        	
	   Dtab[i+1]=fazadft( Atab[i+1],Btab[i+1]); /* Procedura wewnetrzna systemu CMAD-SEE */     
					/* (ATK:KOD1) */ 
		/*Pomys³y: Podwójne wywo³anie funkcji*/			
	  
	   	
	   /*printf("\n%.5lf\t%d, freq:%d powtorki: %d literka: %d",Ttab[i+1],dbl2ascii(Ctab[i+1]),i,freq_tab[i-1][tempe-1],dbl2ascii(Ctab[i+1])); /* dbl2ascii()-procedura wewnetrzna systemu CMAD-SEE */        
	   
	    tempe = dbl2ascii(Ctab[i+1])-65;
	    
	   
	   
	  
	   
	  
	   if(tempe==0)
	   {
	   	tempe+=1;
	   }
	   
		
	   freq_tab[i][tempe-1]+=1;
	   
	}
	printf(" A B C D E F G H i J K L M N O P Q R S T U V W X Y Z\n");
	for(i =0 ;i<19;i++)
	{
		printf("%d ",i);
		for(j=0;j<26;j++)
			printf("%d ", freq_tab[i][j]);
		printf("\n");	
		
    }
     
	
	

 };
  
 
  if ((strstr(szInBuffer,"CMD:")>0)&&(strstr(szInBuffer,":KON")>0)){      
  /* printf("\a"); /* sygnal dzwiekowy (hardware - PC board speaker) */       
  gotoxy(0,11);printf("KOMUNIKAT:                                                                     :");     
  gotoxy(0,11);printf("KOMUNIKAT: %s\t\t\t\t",szInBuffer);     
  /* ***************************************************************************************************/
  if (strstr(szInBuffer,"FINISH")>0){  /* Komunikat przesylany w przypadku wylaczenia CMADSEE-ENGINE   */  
  quit='q';
  }
  /* ***************************************************************************************************/  
  };   
  break;
  } else { /* Dotyczy: if(ret!=-1){ */
    licznik=0;    /* OBLIGATORYJNA zmienna monitorujaca poprawne dzialanie klienta CMADSEE-KLIENT */    
    WSACleanup(); /* Zamkniecie WinSock */        
    goto RECONNECT;    
    }  
  } /* Dotyczy: switch (SelectTiming)*/ 
 
skok:

if (kbhit()){quit=getch();}
}while ((quit != 'q')&&((int)(BitBtn3) != 1)); /* KONIEC glownej petli modulu klienta CMADSEE-KLIENT */

/*---------------------------------------------------------------------------------------------------*/
/* Na zyczenie bezwarunkowe zakonczenie dzialajacego klienta, mozliwe takze z Panelu graficznego     */
koniec:
/*---------------------------------------------------------------------------------------------------*/

WSACleanup();  /* Zamkniecie WinSock */    
StopSISTLab(); /* Zakonczenie dzialania Panelu Graficznego SiSTLab30 */
consleep(100);
FreeLibrary (hSistlab); /* zwolnienie uchwytu(pamieci) systemowego biblioteki DLL */
FreeLibrary (hSistnum); /* zwolnienie uchwytu(pamieci) systemowego biblioteki DLL */
/* Kod "0" zwracany do systemu operacyjnego po zakonczeniu dzialnia modulu CMADSEE-KLIENT  */
return 0; 
/*---------------------------------------------------------------------------------------------------*/
/* Powodzenia podczas opracowywania projektu */
/* prof. J.Szymanda */
/*---------------------------------------------------------------------------------------------------*/
}
