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
        if (id_2 == input.Code)
        {
if 
            gotoxy(1,26);
            //D
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