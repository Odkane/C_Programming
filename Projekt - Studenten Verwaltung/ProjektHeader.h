//
//  ProjektHeader.h
//  ProzProg
//
//  Created by David Aziamoe on 08.01.20.
//  Copyright © 2020 King Gemini. All rights reserved.
//

#ifndef ProjektHeader_h
#define ProjektHeader_h


// Text Color Encode
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define UNDERLINE    "\033[4m"
#define NO_UNDERLINE "\033[24m"

#define BOLD         "\033[1m"
#define NO_BOLD      "\033[22m"

#define Recordfile  "record.txt"

#define Datafile "data.txt"


#define WinWidth w.ws_col
#define WinHeight w.ws_row

typedef enum booleen {
    TRUE,
    FALSE
} booleen;

struct winsize w;

typedef struct Student Student;
typedef struct Noten Noten;


struct Student {
    int Matrikel;
    char Vorname[50];
    char Nachname [50];
    int Alter;
    booleen Status;
};

struct Noten {
    int Matrikel;
    char Fach[50];
    double Note;
    booleen Status;
};

void AddStudent(void);
void SearchStudent(int);
void StudentListe(void);
void Tausch(Student* , Student*);
void Reorganise(void);
void RewriteFile(void);
void AddMark(int);
void MarkSheet(int);
void ModifyStudent(int);
void ModifyMark(int, char[]);
void DeleteStudent(int);
void DeleteMark(int,char[]);
void MenuProject(void);
void Head(void);
void End(void);
void space(int);


void strich(int);
int AnzahlLinie(int);
void DeleteAllMark(int);


#endif /* ProjektHeader_h */
