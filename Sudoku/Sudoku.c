//
//  Sudoku.c
//  ProzProg
//
//  Created by David Aziamoe on 07.19.2020
//  Copyright © 2020 King Gemini. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#define WinWidth w.ws_col
#define WinHeight w.ws_row

struct Eingabe {
    short wert;
    bool fixedStatus;
} ;

struct Eingabe StructZahl[9][9];

void Feld(){
    short i=0,j=0;
    system("clear");
    puts("               Sudoku \n");


    for (i = 0;i<9;i++){
        if (i==0)
            printf("     1  2  3   4  5  6   7  8  9  \n");

        if ((i%3)==0)

           printf("   +---------+---------+---------+ \n");

        for (j = 0;j<9;j++){
            if (j==0) {
                printf(" %d ",i+1);
            }
            if ((j%3) == 0)
            printf("|");

            // printf(" %s ",a[i][j]==0 ? str1 : a[i][j] );

            if (StructZahl[i][j].wert==0)
                 printf("   ");
            else
                printf(" %d ", StructZahl[i][j].wert );

            if (j == 8)
                printf("|\n");

        }
        if (i==8)
        printf("   +---------+---------+---------+ \n");
    }
    //printf("| %d  %d  %d | %d "); // line 2
}

int regelpruefung(short x, short y, short z){
    short rx,ry,t=0,k,m;

    // Zahlprüfung 0<x<10
    t=0;
    if (x==0 && y==0 && z==0)
         exit(0) ;

    if (x<1 || x>9) {
        printf("Ungültige Reihenzahl!\n");
        return 1;
    }
    if (y<1 || y>9)  {
        printf("Ungültige Spaltenzahl! \n");
        return 1;
       }

    if (z<1 || z>9) {
        printf("Ungültige Eingabe! \n");
        return 1;

    }

    if (StructZahl[x-1][y-1].fixedStatus == true) {
        printf("Diese Zahl wurde generiert! Ungültige Eingabe \n");
        return 1;

    }

    //Anpassung
    x=x-1;
    y=y-1;

    //Linienprüfung; Zeile und Spalte
    //Zeile
    for (k = 0; k<9; k++){
        if (StructZahl[k][y].wert== z) {
            printf("Zahl in dieser Spalte schon vorhanden! \n");
            return 1;
        }
    }

    // Spalte
    for (k = 0; k<9; k++){
        if (StructZahl[x][k].wert == z) {
            printf("Zahl in dieser Zeile schon vorhanden! \n");
            return 1;

        }
    }

    // Kästechenprüfung
    rx = x%3;
    ry= y%3;

   for ( k = x - rx; k<x-rx+3;k++){
       for ( m = y-ry; m<y-ry+3;m++){
            if (StructZahl[k][m].wert == z) {
                printf("Zahl in dem Kästechen schon vorhanden! \n");
                return 1;
            }
        }
    }

 return 0;
}

int regelcheck(short x, short y, short z){
    short rx,ry,t=0,k,m;

    // Zahlprüfung 0<x<10
    t=0;

    if (x<0 || x>8) return 1;
    if (y<0 || y>8) return 1;
    if (z<1 || z>9) return 1;

    if (StructZahl[x][y].fixedStatus == true) return 1;


    //Linienprüfung; Zeile und Spalte
    //Zeile
    for (k = 0; k<9; k++){
        if (StructZahl[k][y].wert== z) return 1;
    }

    // Spalte
    for (k = 0; k<9; k++){
        if (StructZahl[x][k].wert == z) return 1;
    }

    // Kästechenprüfung
    rx = x%3;
    ry= y%3;


    for ( k = x - rx; k<x-rx+3;k++){
        for ( m = y-ry; m<y-ry+3;m++){
            if (StructZahl[k][m].wert == z)
                return 1;

        }
    }

    return 0;
}

int check(){
    short ib=0,jb=0;

    for (ib = 0 ; ib<9;ib++){
        for (jb=0 ; jb<9; jb++){
            if (StructZahl[ib][jb].wert==0)
                return 1;
        }
    }

    return 0;
}

void randomZero(){
    short x,t1,t2,n=0;
    time_t t;
    bool check = true;

    srand((unsigned) time(&t));
    system("clear");
    puts("               Sudoku \n");

    while (check) {
      printf("Wie viele Zahlen wollen sie generieren? (10 bis 70):");
      scanf("%hd", &n);
      if (n>10 && n<70)
          check = false;
      else printf("Zahl nicht in dem Intervall \n");
    }

    n = 81-n;

    for (x=0; x<=n; x++){
        t1 = rand() %9;
        t2 = rand() %9;

        if (StructZahl[t1][t2].wert != 0) {
            StructZahl[t1][t2].wert= 0;
            StructZahl[t1][t2].fixedStatus = false;
        }
        else
          --x;
    }
}
void Solver(){

}

void Generate() {
    int ZahlArray[9]={0};
    short i=0,j=0,x=0,c=0;
    short y = 0,k=0,s;
    time_t t;

    srand((unsigned) time(&t));

    for(i=0; i<9;i++) {
        for(j=0; j<9;j++) {

           for (y=0;y<9;y++){
               ZahlArray[y] = 0;
           }
           //Available Numbers Array
            c=0;
            k=0;
            for (k=1;k<10;k++){
                if (regelcheck(i,j,k) == 0){
                    ZahlArray[c] = k;
                    c +=1;
                }
            }
           if (c==0){
              if (j<3) {
                  for (s=0;s<4;s++){
                      StructZahl[i][s].wert= 0;
                      StructZahl[i][s].fixedStatus = false;
                  }
                  j=-1;
              }
              if (j>2 && j<6) {
                  for (s=0;s<6;s++){
                      StructZahl[i][s].wert= 0;
                      StructZahl[i][s].fixedStatus = false;
                  }
                  j=-1;
              }
              if (j>5 && j<=8) {
                  if (i>=7) {
                      for (s=0;s<9;s++){
                          StructZahl[i][s].wert= 0;
                          StructZahl[i][s].fixedStatus = false;
                      }
                      j=-1;
                  }
                  else {
                     for (s=3;s<9;s++){
                         StructZahl[i][s].wert= 0;
                         StructZahl[i][s].fixedStatus = false;
                      }
                     j=2;
                  }
              }
          }

          if (c>0){
            x = ZahlArray[rand() % c];
            StructZahl[i][j].wert= x;
            StructZahl[i][j].fixedStatus = true;
          }
        }
    }
}

void initialization(){
  short i=0,j=0;
  for (i=0 ;i<9;i++) {
      for (j=0 ;j<9;j++) {
          StructZahl[i][j].wert = 0;
          StructZahl[i][j].fixedStatus = false;
      }
  }
  Generate();
  randomZero();
  Feld();
}

int main(){
    short zahl;
    short i=0,j=0;

    initialization();

    do {
        do {
          puts("Eingabe (Zeile Spalte Wert)");
          puts("0 0 0 eingeben um das spiel zu beenden");
          printf("Eingabe: ");

          scanf("%hd %hd %hd",&i,&j,&zahl);
        } while (regelpruefung(i, j,zahl)==1);

          StructZahl[i-1][j-1].wert = zahl;
          Feld();
    } while (check()==1);

    puts("Glückwunsch!!");
    return 0;
}
