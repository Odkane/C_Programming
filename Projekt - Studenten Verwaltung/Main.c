//
//  main_projekt.c
//  ProzProg
//
//  Created by David Aziamoe on 08.01.20.
//  Copyright © 2020 King Gemini. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ProjektHeader.h"
#include <stdbool.h>
#include <sys/ioctl.h>

FILE *FileData = NULL;
Student* Stu;
Noten* Mark;
char Line[111];


void AddStudent() {

    int n=0, Matr=0, Alter=0, wahl = 0;
    char Vor[50],Nach[50];
    char* temp;

    FileData = fopen(Datafile, "r+");

    if (FileData == NULL)
       exit(1);

    Line[0] = '\0';

     while (fgets(Line, 110, FileData) != NULL) {
        temp = strtok(Line, ",");
         n = atoi(temp);
        if (n >= Matr)
            Matr = n+1;
     }
    if ((n == 0) && (Matr == 0))
        Matr = 1;

    if ((n == 0) && (Matr == 1))
        rewind(FileData);

    Head();

    space(20); printf("%s%s%sNeuer Student%s%s \n \n", BOLD,KNRM,UNDERLINE,NO_BOLD,NO_UNDERLINE);
    printf("Matrikelnummer     : %d \n", Matr);
    printf("Vorname eingeben   : "); scanf("%s",Vor);
    printf("Nachname eingeben  : "); scanf("%s", Nach);
    printf("Alter eingeben     : "); scanf("%d", &Alter);
    puts("");

    fprintf(FileData,  "%d,%s,%s,%d \n", Matr, Vor, Nach,Alter);

    fclose(FileData);

    printf("Student %d erfolgreich eingetragen! \n \n", Matr);

    printf("Wollen Sie einen weiteren Student Eintragen? (0 für Nein, 1 für Ja): ");
    scanf("%d",&wahl);

    if (wahl == 1)
        AddStudent();
    else
        MenuProject();
}

/*
 if(strstr(Fach,Teilstring) != NULL)
    strcmp()

 */

void Tausch (Student *Stu1, Student *Stu2) {
    Student temp;

    temp = *Stu1;
    *Stu1 = *Stu2;
    *Stu2 = temp;
}

void SearchStudent(int MatrSearch){

    int Matr= 1, Alter=0, wahl = 0;
    char Vor[50],Nach[50],Fach[50];
    int LineLength = 0, var=0;
    char* temp;
    bool found = false;

    Line[0] = '\0';

    Head();
    space(20); printf("%s%s%sSuche Menu%s%s \n \n", BOLD,KNRM,UNDERLINE,NO_BOLD,NO_UNDERLINE);

    if (MatrSearch == 0) {
        printf("Geben Sie die Matrikelnummer des Studenten ein: ");
        scanf("%d", &MatrSearch);
    }

    FileData = fopen(Datafile, "r");

    if (FileData == NULL)
        exit(1);

    while (fgets(Line, 110, FileData) != NULL) {
        LineLength = (int) strlen(Line);

        temp = strtok(Line, ",");

        while (temp != NULL) {
            switch (var) {
                case 0 :
                    Matr = atoi(temp);
                    break;
                case 1 :
                    strcpy(Vor, temp);
                    break;
                case 2 :
                    strcpy(Nach, temp);
                    break;
                case 3 :
                    Alter = atoi(temp);
                    break;
            }
            temp = strtok(NULL, ",");
            var++;
        }

        if (Matr == MatrSearch) {
            found = true;
            break;
        }
        var=0;
    }

     fclose(FileData);

    if (found == false) {
        printf("\nDie Matrikelnummer %d existiert nicht in der Datenbank.  \n\n",MatrSearch );
        printf("Wollen Sie einen weiteren Student suchen? (0 für Nein, 1 für Ja): ");
        scanf("%d",&wahl);
        if (wahl == 1)
            SearchStudent(0);
        else
            MenuProject();
    }
    else {
        Head();
        printf("Matrikelnummer : %d \n",Matr);
        printf("Vorname        : %s \n",Vor);
        printf("Nachname       : %s \n",Nach);
        printf("Alter          : %d \n",Alter);
        puts("");

        MarkSheet(Matr);

        puts("");
        puts("1. Note hinzufügen");
        puts("2. Note korrigieren");
        puts("3. Note löschen");
        puts("4. Studentendaten ändern");
        puts("5. Studentendaten löschen ");
        puts("6. Anderer Student suchen");
        puts("7. Projekt Menu");
        puts("");
        printf("Ihre Auswahl : ");

        scanf("%d",&wahl);

        switch (wahl) {
            case 1 :
                AddMark(Matr);
                SearchStudent(Matr);
                break;
            case 2 :
                  printf("Geben Sie das Fach ein: ");
                  scanf("%s",Fach);
                  ModifyMark(Matr, Fach);
            case 3 :
                printf("Geben Sie das Fach ein: ");
                scanf("%s",Fach);
                DeleteMark(Matr, Fach);
            case 4 :
                ModifyStudent(Matr);
                SearchStudent(Matr);
                break;
            case 5 :
                DeleteStudent(Matr);
                break;
            case 6 :
                SearchStudent(0);
                break;
            case 7 :
                MenuProject();
                break;

            default : SearchStudent(Matr);
        }
    }
}

void Reorganise(){


}

void RewriteFile(){

}

void AddMark(int Matr){

    int wahl = 0;
    char Fach[50];
    float Note = 0.0;


    FileData = fopen(Recordfile, "a+");

    if (FileData == NULL)
        exit(1);

    Head();

    space(20); printf("%s%s%sNeue Note%s%s \n \n", BOLD,KNRM,UNDERLINE,NO_BOLD,NO_UNDERLINE);
    printf("Matrikelnummer    : %d \n", Matr);
    printf("Fach eingeben     : "); scanf("%s", Fach);
    printf("Note eingeben     : "); scanf("%f", &Note);

    puts("");

    fprintf(FileData,  "%d,%s,%.1f\n", Matr, Fach, Note);

    fclose(FileData);

    printf("Neue Note für den Studenten %d erfolgreich eingetragen! \n \n", Matr);

    printf("Wollen Sie einen weiteren Note Eintragen? (0 für Nein, 1 für Ja): ");
    scanf("%d",&wahl);

    if (wahl == 1)
        AddMark(Matr);
    else
        SearchStudent(Matr);

}

void ModifyStudent(int matr){
    int n = 0, i=0;
    int Matr= 1, Alter=0, wahl = 0;
    char Vor[50],Nach[50];
    int  var=0;
    char* temp;


    n= AnzahlLinie(1);

    Line[0] = '\0';

    Stu = (Student*)malloc(n*sizeof(Student));

    FileData = fopen(Datafile, "r");

    while (fgets(Line, 110, FileData) != NULL) {

        temp = strtok(Line, ",");

        while (temp != NULL) {
            switch (var) {
                case 0 :
                    Matr = atoi(temp);
                    break;
                case 1 :
                    strcpy(Vor, temp);
                    break;
                case 2 :
                    strcpy(Nach, temp);
                    break;
                case 3 :
                    Alter = atoi(temp);
                    break;
            }
            temp = strtok(NULL, ",");
            var++;
        }

        Stu[i].Matrikel = Matr;
        strcpy(Stu[i].Vorname, Vor);
        strcpy(Stu[i].Nachname, Nach);
        Stu[i].Alter = Alter;

        if (Matr == matr)
            Stu[i].Status = TRUE ;
        else
            Stu[i].Status = FALSE;

        var = 0;
        i++;
        free(temp);

    }

    fclose(FileData);

    FileData = fopen(Datafile,"w");
    i = 0;
    for (i = 0 ; i<n; i++) {
        if (Stu[i].Status == FALSE)
           fprintf(FileData, "%d,%s,%s,%d\n",Stu[i].Matrikel,Stu[i].Vorname,Stu[i].Nachname,Stu[i].Alter);
        else {
            printf("Matrikelnummer    : %d\n", Stu[i].Matrikel );
            printf("Alter Vorname : %s | Ändern? (0 für Nein, 1 für Ja) : ", Stu[i].Vorname);
            scanf("%d",&wahl);
            if (wahl == 1) {
                printf("Neuer Name : ");
                scanf("%s",Vor);
                wahl = 0;
            }
            else strcpy(Vor,Stu[i].Vorname);

            printf("Alter Nachname : %s | Ändern? (0 für Nein, 1 für Ja): ", Stu[i].Nachname);
            scanf("%d",&wahl);
            if (wahl == 1) {
                printf("Neuer Nachname : ");
                scanf("%s",Nach);
                wahl = 0;
            }
            else strcpy(Nach,Stu[i].Nachname);

            printf("Vorheriger Alter : %d | Behalten? (0 für Nein, 1 für Ja) \n", Stu[i].Alter);
            scanf("%d",&wahl);
            if (wahl == 1) {
                printf("Jetziger Alter : ");
                scanf("%d",&Alter);
                wahl = 0;
            }
            else Alter = Stu[i].Alter;

            fprintf( FileData,"%d,%s,%s,%d\n",Stu[i].Matrikel,Vor,Nach,Alter);
        }

    }

    fclose(FileData);

    printf("Der Student %d wurde aktualisiert \n", matr);

    free(Stu);

    MenuProject();
}

void ModifyMark(int matr, char fach[50]){
int n = 0, i=0,Matr=0,wahl=0;
char Fach[50];
double Note = 0.0;
int  var=0;
char* temp;
booleen Found = FALSE;


n = AnzahlLinie(2);

Line[0] = '\0';

Mark = (Noten*)malloc(n*sizeof(Noten));

FileData = fopen(Recordfile, "r");

while (fgets(Line, 110, FileData) != NULL) {

    temp = strtok(Line, ",");

    while (temp != NULL) {
        switch (var) {
            case 0 :
                Matr = atoi(temp);
                break;
            case 1 :
                strcpy(Fach, temp);
                break;
            case 2 :
                Note = atof(temp);
                break;
        }
        temp = strtok(NULL, ",");
        var++;
    }

    Mark[i].Matrikel = Matr;
    strcpy(Mark[i].Fach, Fach);
    Mark[i].Note = Note;

    if ((matr == Matr) && strstr(Fach,fach) !=NULL) {
        Mark[i].Status = TRUE;
        Found = TRUE;
    }
    else
        Mark[i].Status = FALSE;

    var = 0;
    i++;
    free(temp);

}
fclose(FileData);

    if (Found == FALSE) {

        printf("\nDas Fach %s existiert noch nicht für den Studenten %d. \n\n",fach,matr );
        printf("Wollen Sie ein anderes Fach für den Studenten suchen? (0 für Nein, 1 für Ja): ");
        scanf("%d",&wahl);
        if (wahl == 1) {
            printf("Geben Sie das Fach ein: ");
            scanf("%s",fach);
            ModifyMark(matr, fach);
        }
        else
            SearchStudent(matr);
    }
else {
FileData = fopen(Recordfile, "w");

i =0;

for (i = 0 ; i<n; i++) {
    if (Mark[i].Status == FALSE)
       fprintf(FileData, "%d,%s,%.1lf\n",Mark[i].Matrikel,Mark[i].Fach,Mark[i].Note);
    else {
        printf("Matrikel : %d\n", Mark[i].Matrikel );
        printf("Fach     : %s ", Mark[i].Fach);
        printf("Note     : %lf | Ändern? (0 für Nein, 1 für Ja): ", Mark[i].Note);
        scanf("%d",&wahl);
        if (wahl == 1) {
            printf("Neue Note : ");
            scanf("%lf",&Note);
            wahl = 0;
        }
        else Note = Mark[i].Note;

        fprintf( FileData,"%d,%s,%.1f\n",Mark[i].Matrikel,Mark[i].Fach,Note);
    }
}

fclose(FileData);
free(Mark);

    SearchStudent(matr);
 }
}
void DeleteMark(int matr,char fach[50]){
    int n = 0, i=0,Matr=0,wahl=0;
    char Fach[50];
    double Note = 0.0;
    int  var=0;
    char* temp;
    booleen Found = FALSE;


    n = AnzahlLinie(2);

    Line[0] = '\0';

    Mark = (Noten*)malloc(n*sizeof(Noten));

    FileData = fopen(Recordfile, "r");

    while (fgets(Line, 110, FileData) != NULL) {

        temp = strtok(Line, ",");

        while (temp != NULL) {
            switch (var) {
                case 0 :
                    Matr = atoi(temp);
                    break;
                case 1 :
                    strcpy(Fach, temp);
                    break;
                case 2 :
                    Note = atof(temp);
                    break;
            }
            temp = strtok(NULL, ",");
            var++;
        }

        Mark[i].Matrikel = Matr;
        strcpy(Mark[i].Fach, Fach);
        Mark[i].Note = Note;

        if ((matr == Matr) && strstr(Fach,fach) !=NULL) {
            Mark[i].Status = TRUE;
            Found = TRUE;
        }
        else
            Mark[i].Status = FALSE;

        var = 0;
        i++;
        free(temp);

    }
    fclose(FileData);

        if (Found == FALSE) {
            printf("\nDas Fach %s existiert noch nicht für den Studenten %d. \n\n",fach,matr );
            printf("Wollen Sie ein anderes Fach für den Studenten suchen? (0 für Nein, 1 für Ja): ");
            scanf("%d",&wahl);
            if (wahl == 1) {
                printf("Geben Sie das Fach ein: ");
                scanf("%s",fach);
                ModifyMark(matr, fach);
            }
            else
                SearchStudent(matr);
        }
    else {
    FileData = fopen(Recordfile, "w");

    i =0;

    for (i = 0 ; i<n; i++) {
        if (Mark[i].Status == FALSE)
           fprintf(FileData, "%d,%s,%.1lf\n",Mark[i].Matrikel,Mark[i].Fach,Mark[i].Note);
    }

    fclose(FileData);
    free(Mark);

        SearchStudent(matr);
     }
}

void DeleteStudent(int matr) {
    int n = 0, i=0;
    int Matr=1, Alter=0;
    char Vor[50],Nach[50];
    int  var=0;
    char* temp;


    n= AnzahlLinie(1);

    Line[0] = '\0';

    Stu = (Student*)malloc(n*sizeof(Student));

    FileData = fopen(Datafile, "r");

    while (fgets(Line, 110, FileData) != NULL) {

        temp = strtok(Line, ",");

        while (temp != NULL) {
            switch (var) {
                case 0 :
                    Matr = atoi(temp);
                    break;
                case 1 :
                    strcpy(Vor, temp);
                    break;
                case 2 :
                    strcpy(Nach, temp);
                    break;
                case 3 :
                    Alter = atoi(temp);
                    break;
            }
            temp = strtok(NULL, ",");
            var++;
        }

        Stu[i].Matrikel = Matr;
        strcpy(Stu[i].Vorname, Vor);
        strcpy(Stu[i].Nachname, Nach);
        Stu[i].Alter = Alter;

        if (matr == Matr)
            Stu[i].Status = TRUE;
        else
            Stu[i].Status = FALSE;

        var = 0;
        i++;
        free(temp);

    }

    fclose(FileData);

    FileData = fopen(Datafile, "w");

    i = 0;
    for (i = 0 ; i<n; i++) {
        if (Stu[i].Status == FALSE)
           fprintf(FileData, "%d,%s,%s,%d\n",Stu[i].Matrikel,Stu[i].Vorname,Stu[i].Nachname,Stu[i].Alter);
    }

    fclose(FileData);

    free(Stu);

    DeleteAllMark(matr);

    printf("Der Student %d wurde gelöscht", matr);
    MenuProject();
}

void DeleteAllMark(int matr) {
    int n = 0, i=0,Matr=0;
    char Fach[50];
    double Note = 0.0;
    int  var=0;
    char* temp;


    n = AnzahlLinie(2);

    Line[0] = '\0';

    Mark = (Noten*)malloc(n*sizeof(Noten));

    FileData = fopen(Recordfile, "r");

    while (fgets(Line, 110, FileData) != NULL) {

        temp = strtok(Line, ",");

        while (temp != NULL) {
            switch (var) {
                case 0 :
                    Matr = atoi(temp);
                    break;
                case 1 :
                    strcpy(Fach, temp);
                    break;
                case 2 :
                    Note = atof(temp);
                    break;
            }
            temp = strtok(NULL, ",");
            var++;
        }

        Mark[i].Matrikel = Matr;
        strcpy(Mark[i].Fach, Fach);
        Mark[i].Note = Note;

        if (matr == Matr)
            Stu[i].Status = TRUE ;
        else
            Stu[i].Status = FALSE;

        var = 0;
        i++;
        free(temp);

    }
    fclose(FileData);

    FileData = fopen(Recordfile, "w");

    i =0;

    for (i = 0 ; i<n; i++) {
        if (Mark[i].Status == FALSE)
           fprintf(FileData, "%d,%s,%.1lf\n",Mark[i].Matrikel,Mark[i].Fach,Mark[i].Note);
    }

    fclose(FileData);
    free(Mark);
}


void StudentListe(){

    int  wahl = 0, var=0;
   //int LineLength = 0;
    char Vor[50],Nach[50], Matr[10], Alter[10];
    char* temp;

    FileData = fopen(Datafile, "r");

    if (FileData == NULL)
        exit(1);

    Line[0] = '\0';

    Head();

    space(20);printf("%s%s%sListe aller Studenten %s%s\n\n", BOLD,KNRM,UNDERLINE,NO_BOLD,NO_UNDERLINE);

    space(10); strich(70);
    space(10); printf("Matrikel"); space(2);printf("|Vorname"); space(18);printf("|Nachname"); space(16); printf("|Alter \n");
    space(10); strich(70);

    while (fgets(Line, 110, FileData) != NULL) {
       // LineLength = (int) strlen(Line);
        temp = strtok(Line, ",");
        while (temp != NULL) {
            switch (var) {
                case 0 :
                    strcpy(Matr, temp);
                    break;
                case 1 :
                    strcpy(Vor, temp);
                    break;
                case 2 :
                    strcpy(Nach, temp);
                    break;
                case 3 :
                    strcpy(Alter, temp);
                    break;
            }
            temp = strtok(NULL, ",");
            var++;
        }

        space(10); printf("%-10s %-25s %-25s %-5s",Matr,Vor,Nach,Alter);
        space(8); strich(70);

        var = 0;
       // LineLength = 0;
        free(temp);

    }

    fclose(FileData);

    puts("");
    puts("1. Student hinzufügen | 2. Student auswählen | 3. Student löschen |4. Studentendaten ändern | 5. Project Menu ");
    printf("Ihre Auswahl: ");

    scanf("%d",&wahl);

    switch (wahl) {
        case 1 :
            AddStudent();
            break;
        case 2 :
            printf("Matrikelnummer des Studenten eingeben: ");
            scanf("%d",&var);
            SearchStudent(var);
            break;
        case 3 :
            printf("Matrikelnummer des Studenten eingeben: ");
            scanf("%d",&var);
            DeleteStudent(var);
        case 4 :
            printf("Matrikelnummer des Studenten eingeben: ");
            scanf("%d",&var);
            ModifyStudent(var);
            break;
        case 5 :
            MenuProject();
            break;
        default : StudentListe();
    }

}

void MarkSheet(int Mat){

    int  var=0, LineLength = 0, n=0;
    char Note[10],Fach[30], Matr[10];
    char* temp;

    FileData = fopen(Recordfile, "r");

    if (FileData == NULL)
        exit(1);

    Line[0] = '\0';

    space(20);printf("%s%s%sNotenspiegel%s%s\n\n", BOLD,KNRM,UNDERLINE,NO_BOLD,NO_UNDERLINE);

    space(10); strich(35);
    space(10); printf("N°");space(3);printf("|Fach"); space(20);printf("|Note\n");
    space(10); strich(35);

    while (fgets(Line, 110, FileData) != NULL) {
        LineLength = (int) strlen(Line);
        temp = strtok(Line, ",");
        while (temp != NULL) {
            switch (var) {
                case 0 :
                    strcpy(Matr, temp);
                    break;
                case 1 :
                    strcpy(Fach, temp);
                    break;
                case 2 :
                    strcpy(Note, temp);
                    break;
            }
            temp = strtok(NULL, ",");
            var++;
        }
        if (Mat == atoi(Matr)) {
            n++;
            space(10); printf("%-5d %-24s %-5s",n,Fach,Note);
            space(9); strich(35);
        }
        var = 0;
        LineLength = 0;
        free(temp);

    }

    fclose(FileData);


}
void space(int n){

    for (int i = 0; i<n ; i++)
        printf(" ");
}

void strich(int n){

    for (int i = 0; i<n ; i++)
      printf("-");

    puts("");
}
void Head(){
    int x=10;

    system("clear");
    space(WinWidth - 27); puts("Author : Yao Aziamoe - 2020");
    printf("%s%s \n",BOLD,KCYN);
    space(WinWidth/2 - 19); strich(39);
    space(WinWidth/2 - 20); printf("|"); space(39); printf("|\n");
    space(WinWidth/2 - 20); printf("|"); space(x) ; printf("%sSTUDENTENVERWALTUNG%s",UNDERLINE,NO_UNDERLINE);space(x);printf("|\n");
    space(WinWidth/2 - 20); printf("|"); space(39); printf("|\n");
    space(WinWidth/2 - 19); strich(39);
    puts("");
    printf("%s%s \n",NO_BOLD,KNRM);

}

void MenuProject(){
    int wahl=0;

    Head();

    space(20);printf("%s%s%sProjekt Menu%s%s\n\n", BOLD,KNRM,UNDERLINE,NO_BOLD,NO_UNDERLINE);
    puts("1. Neuer Student eintragen");
    puts("2. Suche nach einem Studenten");
    puts("3. Liste aller Studenten");
    puts("4. Programm beenden \n");
    printf("Ihre Auswahl : ");
    scanf("%d",&wahl);

    //End();

    switch (wahl) {
        case 1 : AddStudent(); break;
        case 2 : SearchStudent(0); break;
        case 3 : StudentListe(); break;
        case 4 :
            printf("\nDanke für die Benutzung des Programms, Bis zum nächsten mal! \n\n");
            exit(0);
            break;
        default : MenuProject();
    }
}

int AnzahlLinie(int i){
    int Anzahl =0;
    char Line[111];

    Line[0] = '\0';

    switch (i) {
        case 1:
            FileData = fopen(Datafile, "r");
            break;

        case 2 :
            FileData = fopen(Recordfile, "r");
            break;
    }

    while (fgets(Line, 110, FileData) != NULL) {
        Anzahl++;
    }

    fclose(FileData);

    return Anzahl;
}


int main(){

    ioctl(0, TIOCGWINSZ, &w);

    MenuProject();

    return 0;
}
