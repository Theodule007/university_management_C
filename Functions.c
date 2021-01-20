#include "headers.h"
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

}

typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

int isValidDate(Date *validDate)
{
    //check range of year,month and day
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    int MIN_YR = current_time->tm_year + 1900;

    if (validDate->yyyy > 2030 ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
char *GetDate()
{
    Date getDate = {0}; //variable to store date
    int status = 0; //variable to check status
    static char date[50];

    //get date year,month and day from user
    scanf("%d/%d/%d",&getDate.dd,&getDate.mm,&getDate.yyyy);
    //check date validity
    status = isValidDate(&getDate);
    if(status !=1)
    {
        printf("Veuillez entrer une date valide!\n");
        clean_stdin();
        GetDate();
    }
    else
    {
        sprintf(date,"%d/%d/%d",getDate.dd,getDate.mm,getDate.yyyy);
	    return date;
    }

}

char * GetNIF()
 {
    int d1, d2, d3,d4;
    int val;
    static char NIF[20];
    gotoxy(1,26);printf("                                                            ");
    gotoxy(1,27);printf("                                                            ");

   gotoxy(1,26); printf("Entrez NIF/CIN en format xxx-xxx-xxx-x:");

    val = scanf("%d-%d-%d-%d", &d1, &d2, &d3 , &d4);
    // check if scanf was successful
    if(val == 4)
    {
     sprintf(NIF,"%d-%d-%d-%d",d1,d2,d3,d4);
	  return NIF;
    }
    clean_stdin();
    gotoxy(1,26);printf("Format de NIF/CIN invalid, veuillez reesayer!");
    gotoxy(1,27);printf("Pressez 'Enter' pour reessayer");
    GetNIF();

}

int GetLastID(int fileCode)
{
    int id;
    FILE *infile;
	char file[20];

	struct Utilisateur input;
	char fichier1[] = "Utilisateur.bin";
	int size1 = sizeof(struct Utilisateur);

    struct Cours input2;
    char fichier2[] = "Cours.bin";
    int size2 = sizeof(struct Cours);

    struct Ouvrage input3;
    char fichier3[] = "Ouvrage.bin";
    int size3 = sizeof(struct Ouvrage);

	if (fileCode == 1)
	{
		infile = fopen (fichier1, "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,size1, 1, infile))
		id = input.Code;

	}
    else if (fileCode == 2)
	{
		infile = fopen (fichier2, "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input2,size2, 1, infile))
		id = input2.Code;

	}
	 else if (fileCode == 3)
	{
		infile = fopen (fichier3, "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input3,size3, 1, infile))
		id = input3.Code;

	}


	fclose (infile);
	return id;
}

char *GetString()
{

    static char text[100];
    fflush(stdin);
    //printf(">>");
    //clean_stdin();
     if (fgets(text, 100, stdin) == NULL)
     {
     gotoxy(1,27); printf("Ce champ est obligatoire .");
	  clean_stdin();
	  gotoxy(1,27); printf("                        ");
      GetString();
     }
     strtok(text, "\n");
     return text;

}

int GetAccess (  )
//returns the module ,ie access level
{
	FILE *infile;
	struct Utilisateur input;

	char code[100];
	int user,id, val ;
    clearWindow();

        print_heading("Connection");
        gotoxy(37,10);printf("Code Utilisateur  : ");
        val = scanf("%d",&id);

        gotoxy(37,12);printf("Mot de Passe      : ");

        strcpy(code,GetPassword());
        if (val == 0)
        {
            gotoxy(37,14);printf("ID ou mot de Passe incorrect");
            gotoxy(37,16);printf("Pressez 'Enter' pour reesayer");
            getch();
            GetAccess();
            return 0;
        }



	infile = fopen ("Utilisateur.bin", "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,sizeof(struct Utilisateur), 1, infile))
	{


		if (id ==input.Code )
		{
			if (strcmp(code, input.Password)== 0)
			{
                clearWindow();
				return input.Module;
			}
		}

	}
	gotoxy(37,14);printf("ID ou mot de Passe incorrect");
            gotoxy(37,16);printf("Pressez 'Enter' pour reesayer");
            getch();
	 GetAccess();
		return 0;
}

char *Today ()
{
	time_t t ;
	struct tm *tmp ;
	static char MY_TIME[50];
	time( &t );


	tmp = localtime( &t );
	strftime(MY_TIME, sizeof(MY_TIME), "%x - %I:%M%p", tmp);

	return MY_TIME;
}

int Choix(int min,int max , char *warning)
{
  char term;
  int input;
  fflush(stdin);
    //clean_stdin();
  if (scanf("%d%c", &input, &term) == 2 && term == '\n'&& input>=min && input <= max)
   {
     return input;
   }
  else
   {
    printf("%s",warning);
     Choix(min,max,warning);
   }
}

int AddUser ()
{
struct Utilisateur NewUser;
int test;
FILE *fp;
    fp= fopen("Utilisateur.bin", "rb");
    int c = fgetc(fp);
    if (c == EOF)
     {
       NewUser.Code = 1;
     }
      else{
    NewUser.Code = GetLastID(1)+1;//
      }
      fclose(fp);
gotoxy(37,10);printf("Code Utilisateur : %d",NewUser.Code);

gotoxy(1,26);strcpy(NewUser.NIF,GetNIF());

gotoxy(1,26);printf("                                                                    ");

gotoxy(37,11);printf("NIF/CIN          : %s",NewUser.NIF);

gotoxy(1,26);printf("Entrez le Nom : ");
strcpy(NewUser.Nom,GetString());
gotoxy(37,12);printf("Nom              : %s",NewUser.Nom);
gotoxy(1,26);printf("                                               ");

gotoxy(1,26);printf("Entrez le Prenom : ");
strcpy(NewUser.Prenom,GetString());
gotoxy(1,26);printf("                                               ");
gotoxy(37,13);printf("Prenom           : %s",NewUser.Prenom);
gotoxy(1,26);printf("                                               ");

gotoxy(1,26);printf("Entrez le Mot de Passe : ");
strcpy(NewUser.Password,GetPassword());
gotoxy(1,26);printf("                                               ");
gotoxy(37,14);printf("Mot de Passe     : ******");
strcpy(NewUser.Date,Today());
gotoxy(37,15);printf("Date             : %s",NewUser.Date);

gotoxy(1,26);printf("Choisissez une categorie.");
gotoxy(1,27);printf("0 : Administrateur 1-Etudiant(e) 2-Professeur 3-Agent administratif 4-Bibliothecaire");
gotoxy(1,28);printf(">>");
test=Choix(0,4,"Veuillez choisir par la liste!");
NewUser.Module =test;

if (test== 0)
   strcpy(NewUser.Type, "Administrateur");
   else
   strcpy(NewUser.Type, "Utilisateur");
gotoxy(1,26);printf("                                                                                                                           ");
    gotoxy(1,27);printf("                                                                                                                           ");
    gotoxy(1,28);printf("                                                                                                                ");

gotoxy(37,16);printf("Type             : %s",NewUser.Type);






switch ((test))
   {
   case 0:
       strcpy(NewUser.Categorie, "Administrateur");
       gotoxy(37,17);printf("Categorie        : %s",NewUser.Categorie);
       break;
   case 1:
       strcpy(NewUser.Categorie, "Etudiant(e)");
        gotoxy(37,17);printf("Categorie       : %s",NewUser.Categorie);
	   AddStudent(NewUser.Code,NewUser.Nom,NewUser.Prenom);
       break;
   case 2:
       strcpy(NewUser.Categorie, "Professeur");
        gotoxy(37,17);printf("Categorie        : %s",NewUser.Categorie);
	   AddTeacher(NewUser.Code,NewUser.Nom,NewUser.Prenom);
       break;
    case 3:
       strcpy(NewUser.Categorie, "Agent Administratif");
        gotoxy(37,17);printf("Categorie        : %s",NewUser.Categorie);
       AddPersonnel (NewUser.Code,NewUser.Nom,NewUser.Prenom);
       break;
    case 4:
       strcpy(NewUser.Categorie, "Bibliothecaire");
        gotoxy(37,17);printf("Categorie         : %s",NewUser.Categorie);
       AddBibliothecaire (NewUser.Code);
       break;
   }


FILE *outfile;

	// open file for writing
	outfile = fopen ("Utilisateur.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct Utilisateur), 1, outfile);

	if(fwrite != 0)
		{gotoxy(1,26);printf("Votre utilisateur a ete enregistre avec succes. Code : %d",NewUser.Code);
		gotoxy(1,26);printf("                                                                                               ");
		}
	else
		{gotoxy(1,26);printf("Erreurs lors de l'enregistrement.");
		gotoxy(1,27);printf("                                                                                               ");
		}

	// close file
	fclose (outfile);



return 1;
}

int AddStudent (int id , char *nom ,char *prenom )
{
    struct Student NewUser;
    int test ,test2 ,cur ;
     time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    cur = current_time->tm_year + 1900;
    // printf("Current year = %d\n",(current_time->tm_year + 1900));

    NewUser.Code = id;
    gotoxy(1,26);printf("Veullez entrer la session (max 20) :  ");
    NewUser.Session=Choix(1,20,"Veuillez choisir un nombre entre 1 et 20!");
    gotoxy(37,18);printf("Session         : %d",NewUser.Session);
    gotoxy(1,26);printf("                                                                                   ");
    gotoxy(1,27);printf("                                                                                               ");
    gotoxy(1,26);printf("Veuillez entrer l'annee d'admission : ");
    NewUser.AnneeAdm=Choix(1988,cur,"Veuillez entrer une annee entre 1988 et l'annee actuelle!");
    gotoxy(37,19);printf("Session         : %d",NewUser.AnneeAdm);
    gotoxy(1,26);printf("                                                                                                ");
    gotoxy(1,27);printf("                                                                                             ");
    gotoxy(1,26);printf("Choisissez une Faculte.");
    gotoxy(1,27);printf("0-FSEA  1-FSGA 2-FSAE 3-FSJP 4-FSED 5-FSSA");
    gotoxy(1,28);printf(">>");
   test=Choix(0,5,"Veuillez choisir par la liste!");
    gotoxy(1,26);printf("                                                                                                                                                                                              ");
    gotoxy(1,27);printf("                                                                                                                                                                                                       ");
    gotoxy(1,28);printf("                                                                                                                                                                                             ");

switch ((test))
   {
   case 0:

       strcpy(NewUser.Faculte, "FSEA");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
      gotoxy(1,26); printf("Choisissez une Section. ");
       gotoxy(1,27);printf("1-Gestion des Ressources humaines 2-Gestion des Affaires 3-Comptabilite de Management 4-Micro finance");
      gotoxy(1,28); printf("5-Gestion de Projet 6-Marketing 7-Sciences economiques 8-Sciences administratives-PME 9-Sciences administratives-Sciences comptables");
      gotoxy(1,29);printf("10-Sciences administratives-Gestion touristique1 1-Sciences administratives-Gestion des institutions financieres");
      gotoxy(1,30);printf("12-Sciences administratives-Finance 13-Maitrise en comptabilite:Controle-Audit 14-Maîtrise en gestion de projet");
      gotoxy(1,31); test2=Choix(1,14,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Gestion des Ressources humaines");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");

            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 1:
            strcpy(NewUser.Section, "Gestion des Affaires");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Comptabilite de Management");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 3:
            strcpy(NewUser.Section, "Micro finance");
            break;
        case 4:
            strcpy(NewUser.Section, "Gestion de Projet");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 5:
            strcpy(NewUser.Section, "Marketing");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 6:
            strcpy(NewUser.Section, "Sciences economiques");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 7:
            strcpy(NewUser.Section, "Sciences administratives-PME");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 8:
            strcpy(NewUser.Section, "Sciences Adm-Sciences comptables");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 9:
            strcpy(NewUser.Section, "Sciences Adm-Gestion touristique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 10:
            strcpy(NewUser.Section, "Sciences Adm-Gestion institutions financieres");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 11:
            strcpy(NewUser.Section, "Sciences Adm-Finance");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 12:
            strcpy(NewUser.Section, "Maitrise en comptabilite:Controle-Audit");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 13:
            strcpy(NewUser.Section, "Maitrise en gestion de projet");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        }
       break;
   case 1:
       strcpy(NewUser.Faculte, "FSGA");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
      gotoxy(1,27); printf("0-Certificat en Informatique 1-Licence en Genie Informatique 2-Licence en Genie Civil 3-Licence en Genie Électrique-Energie electrique");
      gotoxy(1,28); printf("4-Licence en Genie Electrique-Telecommunications 5-Licence en Genie Industriel 6-Licence en Architecture 7-Licence en Génie de l'Environnement");
       gotoxy(1,29);printf(">>");
       test2=Choix(0,7,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Informatique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Faculte);
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Genie Informatique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                       ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Genie Civil");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                                ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 3:
            strcpy(NewUser.Section, "Genie Electrique-Energie electrique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                            ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 4:
            strcpy(NewUser.Section, "Genie Electrique-Telecommunications");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                         ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 5:
            strcpy(NewUser.Section, "Licence en Genie Industriel");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                            ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 6:
            strcpy(NewUser.Section, "Licence en Architecture");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 7:
            strcpy(NewUser.Section, "Licence en Genie de l'Environnement");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                            ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        }
       break;
   case 2:
       strcpy(NewUser.Faculte, "FSAE");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
       gotoxy(1,27);printf("0 : Ingénieur agronome-Entrepreneuriat et Production 1 : Sante Publique");
       gotoxy(1,28);printf("2 : Technicien Superieur en Sciences Vétérinaires et Production Animale");
       gotoxy(1,29);printf(">>");

       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Ingenieur agronome-Entrepreneuriat et Production");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 1:
            strcpy(NewUser.Section, "Ingenieur agronome-Sciences de la Vie et Technologie");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Technicien Superieur en Sciences Veterinaires et Production Animale");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        }
       break;
    case 4:
       strcpy(NewUser.Faculte, " FSJP");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
       gotoxy(1,27);printf("0-Certificat en Droit des affaires 1-Licence en Sciences Juridiques 2-Licence en Sciences Politiques\n");
       gotoxy(1,28);printf(">>");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Droit des affaires");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Sciences Juridiques");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Sciences Politiques");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        }

       break;
    case 3:
       strcpy(NewUser.Faculte, "FSED");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
       gotoxy(1,27);printf("0-Licence en Sciences de l’Education 1-Licence d’Enseignement 2-Maitrise en Sciences de l’Education 3-Licence en Relations internationales");
       gotoxy(1,28);printf(">>");
       test2=Choix(0,3,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Licence en Sciences de l’Education");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 1:
            strcpy(NewUser.Section, "Licence d’Enseignement");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Maitrise en Sciences de l’Education");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 3:
            strcpy(NewUser.Section, "Licence en Relations internationales");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        }
       break;
    case 5:

       strcpy(NewUser.Faculte, "FSSA");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       printf("Choisissez une Section. ");
       printf("0-Medecine generale 1 : Sante Publique 2 : Soins infirmiers avec option Maladies Infectieuses\n");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Medecine generale");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 1:
            strcpy(NewUser.Section, "Sante Publique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Soins infirmiers");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        }

       break;
   }
//    printf("New student infos \n");
//    printf("ID : %d\nFaculte : %s\n",NewUser.Code,NewUser.Faculte);
//    printf("Section : %s\n",NewUser.Section);
//    printf("Session : %d\n",NewUser.Session);
//    printf("Password : %s\nAnne Admission : %d\n",NewUser.Password,NewUser.AnneeAdm);
     AdmEtud(NewUser.Code , nom ,prenom,NewUser.Faculte);

    FILE *outfile;

	// open file for writing
	outfile = fopen ("Etudiant.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct Student), 1, outfile);

	if(fwrite != 0)
		{gotoxy(1,26);printf("Votre etudiant a ete enregistre avec succes. ");}
	else
		{gotoxy(1,26);printf("Erreurs lors de l'enregistrement.");}

	// close file
	fclose (outfile);



}


int AddTeacher (int id , char *nom ,char *prenom )
{
    struct Teacher NewUser;
    int test ,test2 ,cur ;


    NewUser.Code = id;
    gotoxy(1,26);printf("Veuillez choisir le type de professeur ");
    gotoxy(1,27);printf("0 : Titulaire 1 : Travaux Pratiques 2 : Travaux Dirigees");
    gotoxy(1,28);printf(">>");
    cur = Choix(0,2,"Veuillez choisir parmis la liste");
    switch ((cur))
    {
    case 0:
        strcpy(NewUser.Type, "Titulaire");
        gotoxy(1,26);
        printf("                                                                                                                                    ");
        gotoxy(1,27);
        printf("                                                                                                                                    ");
        gotoxy(1,28);
        printf("                                                                                                                                    ");
        gotoxy(37,18);
        printf("Type             : %s",NewUser.Type);
        break;
    case 1:
        strcpy(NewUser.Type, "Travaux Pratiques");
        gotoxy(1,26);
        printf("                                                                                                                                    ");
        gotoxy(1,27);
        printf("                                                                                                                                    ");
        gotoxy(1,28);
        printf("                                                                                                                                    ");
        gotoxy(37,18);
        printf("Type             : %s",NewUser.Type);

        break;
    case 2:
        strcpy(NewUser.Type, "Travaux Dirigees");
        gotoxy(1,26);
        printf("                                                                                                                                    ");
        gotoxy(1,27);
        printf("                                                                                                                                    ");
        gotoxy(1,28);
        printf("                                                                                                                                    ");
        gotoxy(37,18);
        printf("Type             : %s",NewUser.Type);

        break;
    }
    gotoxy(1,26);printf("Veuillez choisir le nombre de cours : ");
   cur =0;
    NewUser.Nbcours = Choix(1,20,"Veuillez choisir une valeur entre 1 et 20");
   gotoxy(1,26);printf("                                                ");
    gotoxy(1,26);printf("Veuillez entrer les cours Dispenses : ");
    char alt[100];
   for (cur = 1;cur<=NewUser.Nbcours;cur++)
   {
      gotoxy(1,27+cur); printf("Entrez le cours #%d ",cur);
        strcpy(alt,GetString());
        strcat(alt," - ");

   }
   strcpy(NewUser.Cours,alt);
   gotoxy(1,26);printf("                                                                                                 ");
   gotoxy(1,27);printf("                                                                                                 ");
   gotoxy(1,28);printf("                                                                                                 ");
   gotoxy(1,29);printf("                                                                                                 ");
   gotoxy(1,30);printf("                                                                                                 ");
   gotoxy(37,19);
        printf("Nombre Cours     : %d",cur-1);
 gotoxy(1,26);printf("                                                                                                ");
    gotoxy(1,27);printf("                                                                                             ");
    gotoxy(1,26);printf("Choisissez une Faculte.");
    gotoxy(1,27);printf("0-FSEA  1-FSGA 2-FSAE 3-FSJP 4-FSED 5-FSSA");
    gotoxy(1,28);printf(">>");
   test=Choix(0,5,"Veuillez choisir par la liste!");
    gotoxy(1,26);printf("                                                                                                                                                                                              ");
    gotoxy(1,27);printf("                                                                                                                                                                                                       ");
    gotoxy(1,28);printf("                                                                                                                                                                                             ");

switch ((test))
   {
   case 0:

       strcpy(NewUser.Faculte, "FSEA");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
      gotoxy(1,26); printf("Choisissez une Section. ");
       gotoxy(1,27);printf("1-Gestion des Ressources humaines 2-Gestion des Affaires 3-Comptabilite de Management 4-Micro finance");
      gotoxy(1,28); printf("5-Gestion de Projet 6-Marketing 7-Sciences economiques 8-Sciences administratives-PME 9-Sciences administratives-Sciences comptables");
      gotoxy(1,29);printf("10-Sciences administratives-Gestion touristique1 1-Sciences administratives-Gestion des institutions financieres");
      gotoxy(1,30);printf("12-Sciences administratives-Finance 13-Maitrise en comptabilite:Controle-Audit 14-Maîtrise en gestion de projet");
      gotoxy(1,31); test2=Choix(1,14,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Gestion des Ressources humaines");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                            ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");

           gotoxy(37,21);printf("Section         : Ressources humaines");
            break;
        case 1:
            strcpy(NewUser.Section, "Gestion des Affaires");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Comptabilite de Management");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Comptabilite");
            break;
        case 3:
            strcpy(NewUser.Section, "Micro finance");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Micro finance");
            break;
        case 4:
            strcpy(NewUser.Section, "Gestion de Projet");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 5:
            strcpy(NewUser.Section, "Marketing");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 6:
            strcpy(NewUser.Section, "Sciences economiques");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : %s",NewUser.Section);
            break;
        case 7:
            strcpy(NewUser.Section, "Sciences administratives-PME");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : PME");
            break;
        case 8:
            strcpy(NewUser.Section, "Sciences Adm-Sciences comptables");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Sciences comptables");
            break;
        case 9:
            strcpy(NewUser.Section, "Sciences Adm-Gestion touristique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         :Gestion touristique");
            break;
        case 10:
            strcpy(NewUser.Section, "Sciences Adm-Gestion institutions financieres");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Gestion inst. fin.");
            break;
        case 11:
            strcpy(NewUser.Section, "Sciences Adm-Finance");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Finance");
            break;
        case 12:
            strcpy(NewUser.Section, "Maitrise en comptabilite:Controle-Audit");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Controle-Audit");
            break;
        case 13:
            strcpy(NewUser.Section, "Maitrise en gestion de projet");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Gestion de projet");
            break;
        }
       break;
   case 1:
       strcpy(NewUser.Faculte, "FSGA");
        gotoxy(37,20);printf("Faculte          : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
      gotoxy(1,27); printf("0-Certificat en Informatique 1-Licence en Genie Informatique 2-Licence en Genie Civil ");
      gotoxy(1,28); printf("3-Licence en Genie Electrique-Energie electrique 4-Licence en Genie Electrique-Telecommunications ");
             gotoxy(1,29); printf("5-Licence en Genie Industriel  6-Licence en Architecture 7-Licence en Genie de l'Environnement");
       gotoxy(1,30);printf(">>");
       test2=Choix(0,7,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Informatique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section          :Cert.Informatique");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Genie Informatique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                       ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section          : Genie Informatique");
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Genie Civil");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                                ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section          : Genie Civil");
            break;
        case 3:
            strcpy(NewUser.Section, "Genie Electrique-Energie electrique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                            ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section          : Genie Electrique-Energie");
            break;
        case 4:
            strcpy(NewUser.Section, "Genie Electrique-Telecommunications");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                         ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section          : Genie Electrique-Telecom");
            break;
        case 5:
            strcpy(NewUser.Section, "Licence en Genie Industriel");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                            ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section          : Genie Industriel");
            break;
        case 6:
            strcpy(NewUser.Section, "Licence en Architecture");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         :Architecture");
            break;
        case 7:
            strcpy(NewUser.Section, "Licence en Genie de l'Environnement");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                                            ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(1,30);printf("                                                                                                                                    ");
            gotoxy(1,31);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Genie Environnement");
            break;
        }
       break;
   case 2:
       strcpy(NewUser.Faculte, "FSAE");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
       gotoxy(1,27);printf("0 : Ingénieur agronome-Entrepreneuriat et Production 1 : Sante Publique");
       gotoxy(1,28);printf("2 : Technicien Superieur en Sciences Vétérinaires et Production Animale");
       gotoxy(1,29);printf(">>");

       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Ingenieur agronome-Entrepreneuriat et Production");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         :Ingenieur agronome-E&P");
            break;
        case 1:
            strcpy(NewUser.Section, "Ingenieur agronome-Sciences de la Vie et Technologie");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Ingenieur agronome-SVT");
            break;
        case 2:
            strcpy(NewUser.Section, "Technicien Superieur en Sciences Veterinaires et Production Animale");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(1,29);printf("                                                                                                                                    ");
            gotoxy(37,21);printf("Section         : Technicien");
            break;
        }
       break;
    case 4:
       strcpy(NewUser.Faculte, " FSJP");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
       gotoxy(1,27);printf("0-Certificat en Droit des affaires 1-Licence en Sciences Juridiques 2-Licence en Sciences Politiques");
       gotoxy(1,28);printf(">>");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Droit des affaires");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : Certificat en Droit");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Sciences Juridiques");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : Sciences Juridiques");
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Sciences Politiques");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : Sciences Politiques");
            break;
        }

       break;
    case 3:
       strcpy(NewUser.Faculte, "FSED");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       gotoxy(1,26);printf("Choisissez une Section. ");
       gotoxy(1,27);printf("0-Licence en Sciences de l’Education 1-Licence d’Enseignement 2-Maitrise en Sciences de l’Education 3-Licence en Relations internationales");
       gotoxy(1,28);printf(">>");
       test2=Choix(0,3,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Licence en Sciences de l’Education");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : Sciences de l’Education");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence d’Enseignement");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Maitrise en Sciences de l’Education");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : Mac .Sciences de l’Edu");
            break;
        case 3:
            strcpy(NewUser.Section, "Licence en Relations internationales");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : Relations internationales");
            break;
        }
       break;
    case 5:

       strcpy(NewUser.Faculte, "FSSA");
        gotoxy(37,20);printf("Faculte         : %s",NewUser.Faculte);
       printf("Choisissez une Section. ");
       printf("0-Medecine generale 1 : Sante Publique 2 : Soins infirmiers avec option Maladies Infectieuses");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Medecine generale");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 1:
            strcpy(NewUser.Section, "Sante Publique");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        case 2:
            strcpy(NewUser.Section, "Soins infirmiers");
            gotoxy(1,26);printf("                                                                                                                                    ");
            gotoxy(1,27);printf("                                                                                                                                    ");
            gotoxy(1,28);printf("                                                                                                                                    ");
            gotoxy(37,20);printf("Section         : %s",NewUser.Section);
            break;
        }

       break;
   }
//    printf("New student infos \n");
//    printf("ID : %d\nFaculte : %s\n",NewUser.Code,NewUser.Faculte);
//    printf("Section : %s\n",NewUser.Section);
//    printf("NbrCOurs : %d\n",NewUser.Nbcours);
//    printf("Type : %s\n",NewUser.Type);
     AdmProf(NewUser.Code ,nom ,prenom,NewUser.Nbcours);
    FILE *outfile;

	// open file for writing
	outfile = fopen ("Professeur.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct Teacher), 1, outfile);

	if(fwrite != 0)
		{gotoxy(1,26);printf("Votre Professeur a ete enregistre avec succes. ");}
	else
		{gotoxy(1,26);printf("Erreurs lors de l'enregistrement.\n");}

	// close file
	fclose (outfile);



}

int AddPersonnel (int id , char *nom ,char *prenom)
{
    struct PersonAdm NewUser;
    int test ,test2 ,cur, val = 1 ;
    time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    cur = current_time->tm_year + 1900;

    NewUser.Code=id;
    gotoxy(1,26);printf("Veuillez entrer l'annee d'entree en fonction ");
    NewUser.Annee=Choix(1988,cur,"Veuillez entrer une annee entre 1988 et l'annee actuelle!");
    gotoxy(37,18);printf("Entree en fonction     :  %d",NewUser.Annee);
    gotoxy(1,26);printf("                                                                                ");

    gotoxy(1,26);printf("Veuillez entrer la Direction d’Affectation. ");
    strcpy(NewUser.Affectation, GetString());
    gotoxy(37,19);printf("Direction d’Affectation :  %d",NewUser.Affectation);
    gotoxy(1,26);printf("                                                                                ");

    gotoxy(1,26);printf("Veuillez entrer le poste. ");
    strcpy(NewUser.Poste, GetString());
    gotoxy(37,20);printf("Poste                   :  %d",NewUser.Poste);
    gotoxy(1,26);printf("                                                                                ");

    gotoxy(1,26);printf("Veuillez entrer le Supérieur Hiérarchique. \n");
    strcpy(NewUser.Superieur, GetString());
    gotoxy(37,21);printf("Poste                   :  %d",NewUser.Poste);
    gotoxy(1,26);printf("                                                                                ");


   AdmPers(NewUser.Code , nom ,prenom,NewUser.Affectation,NewUser.Poste);


    FILE *outfile;

	// open file for writing
	outfile = fopen ("PersonnelAdministratif.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct PersonAdm), 1, outfile);

	if(fwrite != 0)
		{gotoxy(1,26);printf("Personnel Administratif enregistre avec succes. ");
		gotoxy(1,26);printf("                                                                                ");
		}
	else
		{gotoxy(1,26);printf("Erreurs lors de l'enregistrement.\n");
        gotoxy(1,26);printf("                                                                                ");
		}
	// close file
	fclose (outfile);
}

int AddBibliothecaire (int id)
{
    struct Bibliothecaire NewUser;
    int test ,test2 ,cur ;
     time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    cur = current_time->tm_year + 1900;

    NewUser.Code=id;
    printf("Veuillez entrer l'annee d'admission\n");
    NewUser.Annee=Choix(1988,cur,"Veuillez entrer une annee entre 1988 et l'annee actuelle!");

    printf("Veuillez choisir le niveau. \n");
    printf("1 : Niveau 1 \n2 :  Niveau 2\n");
    cur = Choix(1,2,"Veuillez choisir parmis les niveaux existants");
    switch (cur)
    {
    case 1:
        strcpy(NewUser.Niveau, "N1");
        break;

    case 2:
        strcpy(NewUser.Niveau, "N2");
        break;

    }

    printf("Veuillez entrer le Supérieur Hiérarchique. \n");
    strcpy(NewUser.Superieur, GetString());

   printf("*********Received value : %d",id);

   printf("New student infos \n");
   printf("ID : %d\n",NewUser.Code);
   printf("nIVEAU : %s\n",NewUser.Niveau);
   printf("Superieur : %s\n",NewUser.Superieur);
   printf("Anne Admission : %d\n",NewUser.Annee);

    FILE *outfile;

	// open file for writing
	outfile = fopen ("Bibliothecaire.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct PersonAdm), 1, outfile);

	if(fwrite != 0)
		printf("Votre etudiant a ete enregistre avec succes. ");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);
}

char *GetTeacher(int code)
{
    FILE *infile;
    static char teacher[200];

    struct AdmTeacher input;

		infile = fopen ("AdministrationProf.bin", "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,sizeof(struct AdmTeacher), 1, infile))
    {
        if (code = input.Code)
            {
                strcpy(teacher,input.Prenom);
                strcat(teacher," ");
                strcat(teacher,input.Nom);
                fclose (infile);
                return teacher;
            }
    }
    printf("Professeur introuvable\n");

    printf("Choisissez 1 pour reessayer ou 2 saisir le nom du professeur\n");
    int test;
    test = Choix(1, 2, "Veuillez entrer '1' ou '2'");
    if (test==1)
    {
        GetTeacher(code);
    }
    strcpy(teacher,GetString());
    fclose (infile);
    return NULL;

}

int AddCourse()
{
    struct Cours NewCourse;
    int test;
    int test1;
    char prof[300];
    FILE *fp;
    fp= fopen("Cours.bin", "rb");
    int c = fgetc(fp);
    if (c == EOF)
     {
       NewCourse.Code = 1;
     }
      else{
    NewCourse.Code = GetLastID(2)+1;//
      }
      fclose(fp);
    gotoxy(37,10);printf("Entrez le Titre Du cours : ");
    strcpy(NewCourse.Titre, GetString());
    gotoxy(37,11);printf("Choisissez une Faculte. \n");
    gotoxy(37,12);printf("0:FSEA-1:FSGA-2:FSAE-3:FSJP-4:FSED-5:FSSA");
    gotoxy(37,13);
    test = Choix2(0, 5, "Veuillez choisir par la liste!",37,13);
    switch (test)
    {
    case 0:
        strcpy(NewCourse.Faculte, "FSEA");
        break;
    case 1:
        strcpy(NewCourse.Faculte, "FSGA");
        break;
    case 2:
        strcpy(NewCourse.Faculte, "FSAE");
        break;
    case 3:
        strcpy(NewCourse.Faculte, "FSJP");
        break;
    case 4:
        strcpy(NewCourse.Faculte, "FSED");
        break;
    case 5:
        strcpy(NewCourse.Faculte, "FSSA");
        break;
    }
   gotoxy(37,14); printf("Choisissez le Type du cours. \n");
    gotoxy(37,15);printf("0:Obligatoire - 1:Optionnel");
    gotoxy(37+38,15);
    test = Choix2(0, 1, "Veuillez choisir parmis la liste!",37+38,15);
    switch (test)
    {
    case 0:
        strcpy(NewCourse.Type, "Obligatoire");
        break;
    case 1:
        strcpy(NewCourse.Type, "Optionnel");
        break;
    }
    test = 0;
    gotoxy(37,16);printf("Entrez le nbre de credit.(max 20)");gotoxy(37+38,16);

    NewCourse.NbCredit = Choix2(1, 20, "Veuillez choisir un nmbre de credit entre 1 et 20!",37+38,16);
    test = 0;
    gotoxy(37,17);printf("Entrez le nombre de prof (1 ou 2)"); gotoxy(37+38,17);
    test = Choix2(1, 2, "Veuillez entrer '1' ou '2'",37+38,17);
    if (test == 1)
    {
        gotoxy(37,18);printf("Entrez le code du professeur  : ");gotoxy(37+38,18);
        test1 = Choix2(1, 9999, "Veuillez verifier le format du code!",37+38,18);
        strcpy(NewCourse.Prof1, GetTeacher(test1));

    }
    else
    {
       gotoxy(37,18); printf("Entrez le code du professeur 1: ");gotoxy(37+38,18);
        test1 = Choix2(1, 9999, "Veuillez verifier le format du code!",37+38,18);
        strcpy(NewCourse.Prof1, GetTeacher(test1));
        test1=0;
        gotoxy(37,19);printf("Entrez le code du professeur 2: ");gotoxy(37+38,19);
         test1 = Choix2(1, 9999, "Veuillez verifier le format du code!",37+38,19);
        strcpy(NewCourse.Prof2, GetTeacher(test1));
    }

    //printf("Code : %d\nTitre : %s\nFaculte : %s\nType :%s\nCredit : %d\nProf : %s\n", NewCourse.Code, NewCourse.Titre, NewCourse.Faculte, NewCourse.Type, NewCourse.NbCredit,NewCourse.Prof1);
    AdmCours(NewCourse.Code, NewCourse.Titre, NewCourse.Faculte, NewCourse.NbCredit);
    FILE *outfile;

    // open file for writing
    outfile = fopen("Cours.bin", "ab");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit(1);
    }

    // write struct to file
    fwrite(&NewCourse, sizeof(struct Cours), 1, outfile);

    if (fwrite != 0)
        {gotoxy(1,26);printf("Message : Votre Cours a ete enregistre avec succes.");}
    else
       {
        gotoxy(1,26);printf("Message : Erreurs lors de l'enregistrement.\n");
       }

    // close file
    fclose(outfile);
}

int AdmProf(int code , char *nom ,char *prenom,int NbrCours)
{
    struct AdmTeacher input;
    input.Code = code;
    strcpy(input.Nom, nom);
    strcpy(input.Prenom, prenom);
    input.Nbcours = NbrCours;

    gotoxy(1,26);printf("Veuillez entrer le salaire. ");
    strcpy(input.Salaire, MoneyTester());
     gotoxy(37,22);printf("Salaire          : %s",input.Salaire);
    gotoxy(1,26);printf("                                               ");
    gotoxy(1,26);printf("Veuillez entrer le nombre de Credit.");
    input.Nbcredit = Choix(1,100,"Choisissez une valeur de credit entre 1 et 100");
     gotoxy(37,23);printf("Nombre de Credit : %d",input.Nbcredit);
    gotoxy(1,26);printf("                                               ");

     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationProf.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&input, sizeof(struct AdmTeacher), 1, outfile);

	// close file
	fclose (outfile);

}





int AdmCours(int code , char *titre ,char *fac,int credit)
{
    struct AdmCours input;
    input.Code = code;
    input.NbCredit = credit;
    strcpy(input.Titre, titre);
    strcpy(input.Faculte, fac);
    gotoxy(37,20); printf("Veuillez entrer le cout du cours.\n");
    strcpy(input.Cout, MoneyTester2(0));
     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationCours.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&input, sizeof(struct AdmCours), 1, outfile);

	// close file
	fclose (outfile);

}

int AdmPers(int code , char *nom ,char *prenom,char *direction,char *fonction)
{
    struct AdmPers input;
    input.Code = code;
    strcpy(input.NomEmp, nom);
    strcpy(input.PrenomEmp, prenom);
    strcpy(input.Direction, direction);
    strcpy(input.Fonction, fonction);



    gotoxy(1,26);printf("Veuillez entrer le salaire de l'employe.");
    strcpy(input.Salaire, MoneyTester());
    gotoxy(37,21);printf("Salaire             :%s",input.Salaire);
    gotoxy(1,26);printf("                                               ");
     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationPers.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	fwrite (&input, sizeof(struct AdmPers), 1, outfile);


	fclose (outfile);

}

int AdmEtud(int code , char *nom ,char *prenom,char *faculte)
{
    struct AdmStudent input;
    input.Code = code;
    strcpy(input.NomEtud, nom);
    strcpy(input.PrenomEtud, prenom);
    strcpy(input.Faculte, faculte);


    gotoxy(1,26);printf("Veuillez entrer le montant a payer.\n");
    strcpy(input.Montant, MoneyTester());
    gotoxy(37,22);printf("Montant          :%s",input.Montant);
    gotoxy(1,26);printf("                                                                                 ");
   gotoxy(1,26); printf("Veuillez entrer la date du prochain versement (format :xx/xx/xxxx).\n");
    strcpy(input.Date, GetDate());
    gotoxy(37,23);printf("Date          :%s",input.Date);
    gotoxy(1,26);printf("                                                                                             ");

     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationEtudiant.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	fwrite (&input, sizeof(struct AdmStudent), 1, outfile);


	fclose (outfile);

}

int AddBook()
{
struct Ouvrage NewBook;
int cur;
time_t s;
FILE *fp;
fp = fopen ("Ouvrage.bin", "rb");
struct tm* current_time;
s = time(NULL);
current_time = localtime(&s);
cur = current_time->tm_year + 1900;
int c = fgetc(fp);
if (c == EOF)
{
    NewBook.Code = 1;
}
else{
    NewBook.Code = GetLastID(3)+1;//
}
fclose(fp);
gotoxy(37,10);printf("Code Livre         : %d",NewBook.Code);

gotoxy(1,26);printf("Entrez la Categorie : ");
strcpy(NewBook.Categorie,GetString());
gotoxy(1,26);printf("                                                                    ");
gotoxy(37,11);printf("Categorie          : %s",NewBook.Categorie);

gotoxy(1,26);printf("Entrez la Titre : ");
strcpy(NewBook.Titre,GetString());
gotoxy(1,26);printf("                                                                    ");
gotoxy(37,12);printf("Titre              : %s",NewBook.Titre);

gotoxy(1,26);printf("Entrez l'Edition : ");
strcpy(NewBook.Edition,GetString());
gotoxy(1,26);printf("                                                                    ");
gotoxy(37,13);printf("Edition            : %s",NewBook.Edition);

gotoxy(1,26);printf("Entrez l'annee d'Edition : ");
NewBook.Annee=Choix(1,cur,"Veuillez entrer une annee entre 1 et l'annee actuelle!");
gotoxy(1,26);printf("                                                                    ");
gotoxy(37,14);printf("Annee Edition      : %d",NewBook.Annee);


gotoxy(1,26);printf("Entrez le nombre d'Auteurs (1 ou 2):");
cur=0;
cur=Choix(1,2,"Veuillez entrer '1' ou '2'");
gotoxy(1,26);printf("                                                                    ");
if (cur==1)
{
 gotoxy(1,26);printf("Entrez l'Auteur     : ");
 strcpy(NewBook.Auteur1,GetString());
  gotoxy(1,26);printf("                                                                    ");
gotoxy(37,15);printf("Auteur             : %s",NewBook.Auteur1);

 gotoxy(1,26);printf("Entrez le nombre de page : ");


NewBook.NbPage=Choix(1,9999,"Veuillez reesayer!");
gotoxy(1,26);printf("                                                                    ");
gotoxy(37,16);printf("Nombre Pages       : %d",NewBook.NbPage);

}
else
{
 gotoxy(1,26);printf("Entrez l'Auteur 1: ");
 strcpy(NewBook.Auteur1,GetString());
 gotoxy(1,26);printf("                                                                    ");
gotoxy(37,15);printf("Auteur 1         : %s",NewBook.Auteur1);

 gotoxy(1,26);printf("Entrez l'Auteur 2: ");
 strcpy(NewBook.Auteur1,GetString());
 gotoxy(1,26);printf("                                                                    ");
gotoxy(37,16);printf("Auteur 2         : %s",NewBook.Auteur1);


 gotoxy(1,26);printf("Entrez le nombre de page");
NewBook.NbPage=Choix(1,9999,"Veuillez reesayer!");
gotoxy(1,26);printf("                                                                    ");
gotoxy(37,17);printf("Nombre Pages        : %d",NewBook.NbPage);
}



NewBook.Statut = 1;


 FILE *outfile;

	// open file for writing
	outfile = fopen ("Ouvrage.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewBook, sizeof(struct Ouvrage), 1, outfile);

	if(fwrite != 0)
		{
		   gotoxy(1,26);printf("Votre ouvrage a ete enregistre avec succes. ");
		}
	else
		{
		     gotoxy(1,26);printf("Erreurs lors de l'enregistrement.\n");
		}

	// close file
	fclose (outfile);

}

struct NomComplet getFullName(int code)
{
    FILE *infile;

    struct NomComplet user;
    struct Utilisateur input;

    infile = fopen("Utilisateur.bin", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    while (fread(&input, sizeof(struct Utilisateur), 1, infile))
    {
        if (code = input.Code)
        {
            strcpy(user.prenom, input.Prenom);
            strcpy(user.nom, input.Nom);
            fclose(infile);
            return user;
        }
    }
}

int Emprunt(int codeUser, int codeBook)
{
    int test;
    struct NomComplet user;
    struct Ouvrage book;
   // printf("Entrez le code du livre a empruter");
    test = CheckBookAvailable(codeBook);
    if (test==0)
    {
         gotoxy(1,26);printf("Erreur durant l'operation d'emprunt!");
        return 0;
    }
    user = getFullName(codeUser);

    FILE *infile,*temp;

	infile = fopen ("Ouvrage.bin", "rb");
    temp = fopen ("Temp.bin", "ab");

	if (infile == NULL || temp == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&book,sizeof(struct Ouvrage), 1, infile))
    {
        if (book.Code == codeBook)
        {
            strcpy(book.PrenomEmp,user.prenom);
            strcpy(book.NomEmp,user.nom);
            book.CodeEmp = codeUser;
            strcpy(book.DateSortie, Today());
            book.Statut = 0;
            gotoxy(37,11);printf("Emprunt reussi!");
        }
       fwrite(&book,sizeof(struct Ouvrage), 1, temp) ;

    }

	fclose (infile);
    fclose(temp);
    remove("Ouvrage.bin");
    rename("Temp.bin","Ouvrage.bin");
gotoxy(1,26);printf("                                                                           ");
}

int CheckBookAvailable(int code)
{
    FILE *infile;

    struct Ouvrage input;

    infile = fopen("Ouvrage.bin", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    while (fread(&input, sizeof(struct Ouvrage), 1, infile))
    {

        if (code == input.Code)
        {
            if (input.Statut == 1)
            {
                gotoxy(37,10);printf("Le livre :%s est disponible", input.Titre);
                fclose(infile);
                return 1;
            }
            else
            {
                gotoxy(37,10);printf("Le livre n'est pas disponible");

                fclose(infile);


                return 0;
            }
        }

    }
    gotoxy(37,10); printf("Le livre  n'est pas a la bibliotheque.");

                fclose(infile);
                return 0;
}

int Retour (int codeUser ,int codeBook)
{
     int test;
    struct Ouvrage book;
    test = CheckBookAvailableR(codeBook);
    if (test==0)
    {
        gotoxy(1,26);printf("Erreur durant l'operation d'emprunt!");
        return 0;
    }

    FILE *infile,*temp;

	infile = fopen ("Ouvrage.bin", "rb");
    temp = fopen ("Temp.bin", "ab");

	if (infile == NULL || temp == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&book,sizeof(struct Ouvrage), 1, infile))
    {
        if (book.Code == codeBook)
        {
            strcpy(book.PrenomEmp,"");
            strcpy(book.NomEmp,"");
            book.CodeEmp = 0;
            strcpy(book.DateRetour, Today());
            book.Statut = 1;
            gotoxy(37,11);printf("Retour reussi!");
        }
       fwrite(&book,sizeof(struct Ouvrage), 1, temp) ;

    }

	fclose (infile);
    fclose(temp);
    remove("Ouvrage.bin");
    rename("Temp.bin","Ouvrage.bin");
    gotoxy(1,26);printf("                                                                           ");


}

int CheckBookAvailableR(int code)
{
    FILE *infile;

    struct Ouvrage input;

    infile = fopen("Ouvrage.bin", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    while (fread(&input, sizeof(struct Ouvrage), 1, infile))
    {

        if (code == input.Code)
        {
            if (input.Statut == 0)
            {
                gotoxy(37,10);printf("Le livre a retourner est:%s", input.Titre);
                fclose(infile);
                return 1;
            }
            else
            {
                gotoxy(37,10);printf("Ce livre a deja ete retourne !");
                return 0;
            }
        }

    }
     gotoxy(1,26);printf("Le livre  n'est pas a la bibliotheque.");

    return 0;
}

void ReadFileUser()
{
    int id;
    FILE *infile;
	char file[20];

	struct Utilisateur input;

		infile = fopen ("Utilisateur.bin", "rb");

	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {
        printf("Code :%d\n",input.Code);
        printf("Nom :%s\n",input.Nom);
        printf("Prenom :%s\n",input.Prenom);
        printf("NIF-CIN :%s\n",input.NIF);
		printf("Date :%s\n",input.Date);
        printf("Type:%s\n",input.Type);
        printf("Categorie :%s\n",input.Categorie);
        printf("Module : %d\n",input.Module);
		printf("----------------------\n");
    }

	fclose (infile);

}

void Report (int fileCode)
{
    FILE *infile,*temp;
	char file[20];

	struct Utilisateur input;


    infile = fopen ("Utilisateur.bin", "rb");
    temp = fopen("Report.txt","w");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
	fprintf(temp,"Code\tPrenom\tNom\t\n");

	while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {
        if (input.Module == fileCode)
        {
            fprintf(temp,"%d\t\t%s\t\t%s\n",input.Code,input.Prenom,input.Nom);
        }

    }
    fclose(infile);
    fclose(temp);
    switch (fileCode)
    {
    case 0:
        rename("Report.txt","ReportAdmin.txt");
        break;
    case 1:
        rename("Report.txt","ReportEtudiant.txt");
        break;
    case 2:
        rename("Report.txt","ReportProfesseurs.txt");
        break;
    case 3:
        rename("Report.txt","ReportPersonnelAdministratif.txt");
        break;
    case 4:
        rename("Report.txt","ReportBibliothecaire.txt");
        break;
    }

}

int ChangePassword(int id)
{
    struct Utilisateur input;
    FILE *infile,*temp;

    infile = fopen ("Utilisateur.bin", "rb");
    temp = fopen ("Temp.bin", "ab");

    if (infile == NULL || temp == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {
        if (id == input.Code)
        {
            gotoxy(1,26);
            printf("Entrez le nouveau mot de passe ");
            strcpy(input.Password,GetPassword()) ;
        }
        fwrite(&input,sizeof(struct Utilisateur), 1, temp) ;

    }

    fclose (infile);
    fclose(temp);
    remove("Utilisateur.bin");
    rename("Temp.bin","Utilisateur.bin");
    gotoxy(1,26);
    printf("                                                           ");
    gotoxy(1,26);
    printf("Succes!Pressez 'Entrer' pour continuer");
    // gotoxy(1,27);printf("Pressez 'Entrer' pour continuer");
    getch();
    gotoxy(1,26);
    printf("                                                   ");
    // gotoxy(1,27);printf("                                                   ");
    return 0;

}

int CheckUserAvailability (int id)
{
    FILE *infile;

    struct Utilisateur input;

    infile = fopen ("Utilisateur.bin", "rb");

    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {


        if(id == input.Code)
        {
            fclose (infile);

            return id;
        }

    }

    fclose (infile);
    return 0;

}




void AfficherBiblio(int code)
{

    FILE *infile;

	struct Ouvrage input;
	int i =0;

		infile = fopen ("Ouvrage.bin", "rb");

	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

    if (code == 0)
    {

       while(fread(&input,sizeof(struct Ouvrage), 1, infile))
    {
        gotoxy(37,10+i);printf("Categorie :%s  ",input.Categorie);
        i++;

    }

	fclose (infile);
	return;
    }
    else
    {

        while(fread(&input,sizeof(struct Ouvrage), 1, infile))
    {
       gotoxy(37,10+i); printf("Code : %d    Titre :%s",input.Code,input.Titre);
        i++;
    }
        fclose (infile);
        return;
    }


}


