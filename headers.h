#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <dos.h>



struct Utilisateur
{
int Code;
char NIF[20];
char Nom[100];
char Prenom[100];
char Password[100];
char Date[20];
char Type[100];
char Categorie[100];
int Module;//0=adm 1= etudiant , 2 = professeur , 3 = agent administratif , 4= bibliothecaire
};

struct Student
{
int Code;
char Faculte[100];
char Section[100];
int Session;
int AnneeAdm;
};

struct AdmStudent
{
int Code;
char NomEtud[100];
char PrenomEtud[100];
char Faculte[100];
char Date[100];
char Montant[100];
};

struct Teacher
{
int Code;
char Faculte[100];
char Section[100];
char Type[100];
int Nbcours;
char Cours[300];
};

struct AdmTeacher
{
int Code;
char Nom[100];
char Prenom[100];
int Nbcours;
int Nbcredit;
char Salaire[100];
};

struct PersonAdm
{
int Code ;
char Affectation[100];
char Poste[100];
int Annee;
char Superieur[100];
};

struct AdmPers
{
int Code ;
char NomEmp[100];
char PrenomEmp[100];
char Direction[100];
char Fonction[100];
char Salaire[100];
};

struct Bibliothecaire
{
int Code ;
char Niveau[100];
int Annee;
char Superieur[100];
};

struct Cours
{
int Code;
char Titre[100];
char Faculte[100];
char Type[100]; //Obligatoire ou optionel
int NbCredit;
char Prof1[100];
char Prof2[100];
};

struct AdmCours
{
int Code;
char Titre[100];
char Faculte[100];
int NbCredit;
char Cout[100];
};

struct Ouvrage
{
int Code;
char Categorie[100];
char Titre[100];
char Edition[100];
int Annee;
char Auteur1[100];
char Auteur2[100];
int NbPage;
char DateEntre[100];
char DateSortie[100];
char DateRetour[100];

int CodeEmp;
char NomEmp[100];
char PrenomEmp[100];
int Statut; //1: Disponible 0:Indisponible
};

struct NomComplet
{
    char nom[100];
    char prenom[100];
};


int GetLastID(int fileCode); // fileCode : 1= Utilisateur.bin 2 = Cours.bin 3 =Ouvrage.bin
int GetAccess ( );
void clean_stdin(void);
char *GetNIF();
char *GetString();
int inputManager();
int Choix(int min,int max , char *warning);
int AddUser ();
void ReadFileUser();
int AddStudent (int id , char *nom ,char *prenom);
int AddTeacher (int id , char *nom ,char *prenom);
int AddPersonnel (int id , char *nom ,char *prenom);
int AddBibliothecaire (int id);
int AddCourse ();
char * MoneyTester() ;
int AdmCours(int code , char *titre ,char *fac,int credit);
int AdmPers(int code , char *nom ,char *prenom,char *direction,char *fonction);
int AdmEtud(int code , char *nom ,char *prenom,char *faculte);
char *GetDate();
int AddBook();
char *GetTeacher(int code);
int AdmProf(int code , char *nom ,char *prenom,int NbrCours);

struct NomComplet getFullName(int code );
int CheckBookAvailable (int code);
int CheckBookAvailableR(int code);
int Retour (int codeUser ,int codeBook);
int ChangePassword(int id);
int CheckUserAvailability (int id);
unsigned long hash(unsigned char *str);
//________________________________Graphics
char * GetPassword();
void SetColor(int ForgC);
void ClearConsoleToColors(int ForgC, int BackC);
void SetColorAndBackground(int ForgC, int BackC);
void drawRectangle();
void clearWindow();
void clearMainWindow();
void window();
int main_window(int id);
int Start();
void print_heading(const char st[]);
void GAccess(int choix);
void PrintCours(int code);
void GCours(int choix);
int Choix2(int min,int max , char *warning,int x,int y);
char * MoneyTester2(int a) ;
void GAdminPerson (int user ,int choix);
void adjustWindowSize();
void AfficherBiblio(int code);
void GBiblio(int id ,int choix);


void gotoxy(int x, int y);
