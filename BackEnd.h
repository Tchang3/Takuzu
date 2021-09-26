//Var global
int** Board = NULL;
int** PlayerBoard = NULL;
int** ResetBoard = NULL;

char* Scan = NULL;
char* Scan2 = NULL;
int Attempt = 0; //Compteur global
int n = 0;
int BACKSize;
int TotalN;

//Structure pour retour en arrière
typedef struct _Position
{
    int lgn; //Ligne
    int cln; //Colonne
    int valeur; //Le chiffre à backup
}Position;

//Créer une position facilement
Position create_Position(int lgn, int cln, int valeur)
{
    Position temp;
    temp.lgn = lgn;
    temp.cln = cln;
    temp.valeur = valeur;
    return temp;
}

Position* BACK = NULL;
Position* InterBACK = NULL;

//CORE FUNCTION - Vérifier la validité d'un coup
int VerifPos(int** Board, int n, int lgn, int cln, char* Scan, char* Scan2)
{
    Attempt++;
    int i,j;
    int Zero = 0;
    int Un = 0;

    //                            PREMIERE VERIF PAR LE NOMBRE
    //         Verification nombre colonne
    for(i=0;i<n;i++)
    {
        if( Board[i][cln] == 1 )
        {
            Un++;
        }
        else if( Board[i][cln] == 0 )
        {
            Zero++;
        }
    }

    if(Un > (n/2) || Zero > (n/2))
    {
        return 0;
    }

    Un = 0;
    Zero = 0;
    //         Verification nombre ligne
    for(i=0;i<n;i++)
    {
        if( Board[lgn][i] == 1 )
        {
            Un++;
        }
        else if( Board[lgn][i] == 0 )
        {
            Zero++;
        }
    }

    if(Un > (n/2) || Zero > (n/2))
    {
        return 0;
    }

    //                             DEUXIEME VERIF POUR ENCHAINEMENT
    //           VERIF POUR ENCHAINEMENT DE 3 POUR LIGNES

    char Scanned[32];
    Scan[0] = '\0';
    Scanned[0] = '\0';

    for(i=0;i<n;i++)
    {
        sprintf(Scanned,"%d",Board[lgn][i]); //Transformer int vers char
        strcat(Scan,Scanned);               //puis concaténation
    }

    if(strstr(Scan,"111") != NULL)
    {
        return 0;
    }
    else if(strstr(Scan,"000") != NULL)
    {
        return 0;
    }

    //          VERIF POUR LES DOUBLONS DE LIGNES.
    Scanned[0] = '\0';
    i = 0;
    do{
        if( i != lgn ) //Si même ligne alors continuer
        {
            Scan2[0]= '\0';

            for(j=0;j<n;j++)
            {
                sprintf(Scanned,"%d",Board[i][j]);
                strcat(Scan2,Scanned);
            }
            if(strcmp( Scan,Scan2 ) == 0)
            {
                return 0;
            }
        }
    }while(++i<n);

    Scan[0] = '\0';
    Scanned[0] = '\0';

    //           VERIF POUR ENCHAINEMENT DE 3 POUR COLONNES
    for(i=0;i<n;i++)
    {
        sprintf(Scanned,"%d",Board[i][cln]);
        strcat(Scan,Scanned);
    }
    if(strstr(Scan,"111") != NULL)
    {
        return 0;
    }
    else if(strstr(Scan,"000") != NULL)
    {
        return 0;
    }

    //          VERIF POUR LES DOUBLONS DE COLONNES.
    Scanned[0] = '\0';
    j = 0; //
    do{
        if( j != cln )
        {
            Scan2[0]= '\0';

            for(i=0;i<n;i++)
            {
                sprintf(Scanned,"%d",Board[i][j]);
                strcat(Scan2,Scanned);
            }
            if(strcmp( Scan,Scan2 ) == 0)
            {
                return 0;
            }
        }
    }while(++j<n);

    //LE COUP EST VALIDE.
    return 1;
}

//OBTENIR LE NOMBRE DE CASE VIDE POUR BACK
int GetNumberOfFreeCase(int n)
{
    int Number = 0;
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(ResetBoard[i][j] != 1 && ResetBoard[i][j] != 0)
            {
                Number++;
            }
        }
    }
    return Number;
}

/* CORE FUNCTION - RECURSIVE SOLVER
    RETOURNE 2 SI COUP CORRECTE
    RETOURNE 3 SI NON RESPECT DES REGLES */
int BoardSolver(int** Board, int n, int lgn, int cln, char* Scan, char* Scan2)
{
    //DETECTION D'UN ELEMENT NON MODIFIABLE.
    if( Board[lgn][cln] == 1 || Board[lgn][cln]== 0 )
    {
        int Test;
        if( cln < (n-1) && lgn < n ) //Passer à la ligne suivante
            {Test = BoardSolver( Board , n , lgn , ( (cln+1)%n ),Scan,Scan2);}
        else if(cln<n && lgn<(n-1)) //Passer à la colonne suivante
            {Test = BoardSolver( Board , n , (lgn+1) , ( (cln+1)%n ),Scan,Scan2);}
        else if(lgn == (n-1) && cln == (n-1)) //Dernière valeur
        {
            return 2;
        }

        if(Test== 0 || Test == 3)
        {
            return 3;
        }
        else if(Test == 2)
        {
            return 2;
        }
    }
    //DETECTION D'UNE CASE JOUABLE
    else if(Attempt < 16777216*5)
    {
        int Tag[2] = {0,1};
        int RValor = rand()%2;
        Board[lgn][cln] = Tag[RValor];
        int Test = VerifPos(Board,n,lgn,cln,Scan,Scan2);
        //PASSER A LA SUITE SI COUP VALIDE
        if(Test==1)
        {
            if( cln<(n-1) && lgn<n )
                {Test = BoardSolver( Board , n , lgn , ( (cln+1)%n ),Scan,Scan2);}
            else if(cln<n && lgn<(n-1))
                {Test = BoardSolver( Board , n , (lgn+1) , ( (cln+1)%n ),Scan,Scan2);}
            else if(lgn == (n-1) && cln == (n-1))
            {
                return 2;
            }
        }

        if(Test== -1)
        {
            return -1;
        }
        else if(Test == 2)
        {
            return 2;
        }
        //TEST 2 SI LE PRECEDENT A éCHOUé
        else if(Test==0 || Test == 3)
        {
            RValor = (RValor+1)%2;
            Board[lgn][cln] = Tag[RValor];
            Test = VerifPos(Board,n,lgn,cln,Scan,Scan2);
            if(Test==1)
            {
                //PASSER A LA SUITE SI SUCCES
                if( cln<(n-1) && lgn<n )
                    {Test = BoardSolver( Board , n , lgn , ( (cln+1) %n ),Scan,Scan2);}
                else if(cln<n && lgn<(n-1))
                    {Test = BoardSolver( Board , n , (lgn+1) , ( (cln+1) %n ),Scan,Scan2);}
                else if(lgn == (n-1) && cln == (n-1))
                {
                    return 2;
                }
            }
            //RETOUR EN ARRIERE SI DOUBLE ECHEC
            if(Test == 0 || Test == 3)
            {
                Attempt++;
                Board[lgn][cln] = rand()%5+4;
                return 3;
            }
            else if(Test == -1)
            {
                return -1;
            }
            else if(Test == 2)
            {
                return 2;
            }
        }
    }
    else
    {
        return -1;
    }
    return -1;
}


//AFFICHER LE PLATEAU SUR LA CONSOLE
void ShowBoard(int** Board, int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",Board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//REINITIALISER LE PLATEAU DU JOUEUR
void ReinitBoard(int** ResetBoard, int** PlayerBoard, int n, Position* BACK, int BACKSize)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            PlayerBoard[i][j] = ResetBoard[i][j];
        }
    }
    BACKSize = 1;
    BACK = NULL;
    BACK = (Position*)malloc(BACKSize*sizeof(Position));
}


//CORE FUNCTION - CACHER DES VALEURS DU TABLEAU LORS DE L'INITIALISATION
void HideBoard(int** ResetBoard, int** PlayerBoard, int n)
{
    int i = 0;
    int AleaLGN,AleaCLN;
    do{
        AleaLGN = rand()%n;
        AleaCLN = rand()%n;
        if(PlayerBoard[AleaLGN][AleaCLN] == 1 || PlayerBoard[AleaLGN][AleaCLN] == 0)
        {
            PlayerBoard[AleaLGN][AleaCLN] = rand()%7+3;
            ResetBoard[AleaLGN][AleaCLN] = PlayerBoard[AleaLGN][AleaCLN];
        }
        else
        {
            i--;
        }
    }while(++i < ((n*n)/2)) ;
}

//CORE FUNCTION - GENERER UN PLATEAU ALEATOIRE
void GenerateBoard(int** Board, int** PlayerBoard,int** ResetBoard, int n, char* Scan, char* Scan2)
{
    Attempt = 0;
    BACKSize = 1;
    int Try,lgn,cln;

    //Plateau de nombres invalides
    for(lgn=0;lgn<n;lgn++)
    {
        for(cln=0;cln<n;cln++)
        {
            Board[lgn][cln] = rand()%7+3;
        }
    }

    //Initialisation du plateau valide
    Try = BoardSolver(Board,n,0,0,Scan,Scan2);
    while(Try == -1 || Try == 3)
    {
        for(lgn=0;lgn<n;lgn++)
        {
            for(cln=0;cln<n;cln++)
            {
                Board[lgn][cln] = rand()%7+3;
            }
        }
        Attempt = 0;
        Try = BoardSolver(Board,n,0,0,Scan,Scan2);
    }


    //Initialisation du plateau de reference (ResetBoard)
    for(lgn=0;lgn<n;lgn++)
    {
        for(cln=0;cln<n;cln++)
        {
            PlayerBoard[lgn][cln] = Board[lgn][cln];
            ResetBoard[lgn][cln] = Board[lgn][cln];
        }
    }

    //Plateau du joueur maintenant caché
    HideBoard(ResetBoard,PlayerBoard,n);
}

//CORE FUNCTION - ESSAIE DE TOUTES LES POSSIBILITéS
void TargetBoardResolver(int** PlayerBoard, int** ResetBoard, int n, char* Scan, char* Scan2)
{
    int Try;
    Try = BoardSolver(PlayerBoard,n,0,0,Scan,Scan2);
    while(Try!=2 && Try!= 7)
    {
        Attempt = 0;
        ReinitBoard(ResetBoard,PlayerBoard,n,BACK,BACKSize);
        Try = BoardSolver(PlayerBoard,n,0,0,Scan,Scan2);
    }
}

//AIDE AU JOUEUR PAR 1 CASE CORRECTE
void GetHelp(int** ResetBoard,int** Board, int n, char* Scan, char* Scan2)
{
    int Try,lgn,cln;
    TotalN++;

    //Board Intermédiaire
    for(lgn=0;lgn<n;lgn++)
    {
        for(cln=0;cln<n;cln++)
        {
            Board[lgn][cln] = ResetBoard[lgn][cln];
        }
    }

    //Résoudre Board
    Try = BoardSolver(Board,n,0,0,Scan,Scan2);
    while(Try!=2 && Try!= 7)
    {
        Attempt = 0;
        ReinitBoard(ResetBoard,Board,n,BACK,BACKSize);
        Try = BoardSolver(Board,n,0,0,Scan,Scan2);
    }

    //Attribuer Board à ResetBoard
    lgn = rand()%n;
    cln = rand()%n;
    while(Board[lgn][cln] == ResetBoard[lgn][cln])
    {
        lgn = rand()%n;
        cln = rand()%n;
    }
    ResetBoard[lgn][cln] = Board[lgn][cln];
    PlayerBoard[lgn][cln] = Board[lgn][cln];
    for(lgn=0;lgn<n;lgn++)
    {
        Board[lgn] = NULL;
    }
    for(lgn=0;lgn<n;lgn++)
    {
        Board[lgn] = static_cast<int*>(malloc(n*sizeof(int)));
    }
}

//FERMETURE DU PLATEAU ISSUE D'UN RETOUR AU MENU PRINCIPAL OU FERMETURE DEFINITIVE
void BackEnd_Close(int** PlayerBoard,int** ResetBoard, int** Board, char* Scan, char* Scan2,int n,Position* BACK,Position* InterBACK)
{
    int lgn;
    if(Scan != NULL)
        free(Scan);
    if(Scan2 != NULL)
        free(Scan2);

    for(lgn=0;lgn<n;lgn++)
    {
        if(Board[lgn] != NULL)
            {free(Board[lgn]);}

        if(ResetBoard[lgn] != NULL)
            {free(ResetBoard[lgn]);}

        if(PlayerBoard[lgn] != NULL)
            {free(PlayerBoard[lgn]);}
    }

    if(BACK!= NULL)
        free(BACK);
    if(InterBACK!= NULL)
        free(InterBACK);

}

//REALLOC PRESERVANT LES VALEURS DES STRUCTURES POSITIONS
void transfert(int BACKorRBACK)
{
    /*Un coup est joué
    Un
    */
    if(BACKorRBACK == 1)
    {
        int i;
        free(InterBACK);
        InterBACK = static_cast<Position*>(malloc(BACKSize*sizeof(Position)));
        for(i=0;i<BACKSize;i++)
        {
            InterBACK[i].lgn = BACK[i].lgn;
            InterBACK[i].cln = BACK[i].cln;
            InterBACK[i].valeur = BACK[i].valeur;
        }
        BACKSize++;
        free(BACK);
        BACK = static_cast<Position*>(malloc(BACKSize*sizeof(Position)));
        for(i=0;i<BACKSize-1;i++)
        {
            BACK[i].lgn = InterBACK[i].lgn;
            BACK[i].cln = InterBACK[i].cln;
            BACK[i].valeur = InterBACK[i].valeur;
        }
    }
    //Un retour en arrière est effectué
    else if(BACKorRBACK == 0)
    {
        int i;
        free(InterBACK);
        InterBACK = static_cast<Position*>(malloc(BACKSize*sizeof(Position)));
        for(i=0;i<BACKSize-1;i++)
        {
            InterBACK[i].lgn = BACK[i].lgn;
            InterBACK[i].cln = BACK[i].cln;
            InterBACK[i].valeur = BACK[i].valeur;
        }
        BACKSize--;
        free(BACK);
        BACK = static_cast<Position*>(malloc(BACKSize*sizeof(Position)));
        for(i=0;i<BACKSize;i++)
        {
            BACK[i].lgn = InterBACK[i].lgn;
            BACK[i].cln = InterBACK[i].cln;
            BACK[i].valeur = InterBACK[i].valeur;
        }
    }
}

int BackEnd_main()
{
    int lgn;
    Board = static_cast<int**>(malloc(n*sizeof(int*)));
    PlayerBoard = static_cast<int**>(malloc(n*sizeof(int*)));
    ResetBoard = static_cast<int**>(malloc(n*sizeof(int*)));

    //INITIALISATION
    for(lgn=0;lgn<n;lgn++)
    {
        Board[lgn] = static_cast<int*>(malloc(n*sizeof(int)));
        PlayerBoard[lgn] = static_cast<int*>(malloc(n*sizeof(int)));
        ResetBoard[lgn] = static_cast<int*>(malloc(n*sizeof(int)));
    }
    //Création des deux comparateurs
    Scan = static_cast<char*>(malloc((n+1)*sizeof(char)));
    Scan2 = static_cast<char*>(malloc((n+1)*sizeof(char)));

    BACK = static_cast<Position*>(malloc(BACKSize*sizeof(Position)));
    InterBACK = static_cast<Position*>(malloc(BACKSize*sizeof(Position)));

    return 0;
}

//VERIFIER VICTOIRE PLATEAU ALEATOIRE DU JOUEUR
int CheckWin()
{
    int lgn,cln;
    for(lgn=0;lgn<n;lgn++)
    {
        for(cln=0;cln<n;cln++)
        {
            if(PlayerBoard[lgn][cln] == 1 || PlayerBoard[lgn][cln] == 0)
            {
                if(VerifPos(PlayerBoard,n,lgn,cln,Scan,Scan2) == 1)
                {
                    ;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}

//PARTIE DEFI EXEMPLES

void DEFIONE()
{
    // DEFI 1
    int lgn,cln;
    for(lgn=0;lgn<n;lgn++)
    {
        for(cln=0;cln<n;cln++)
        {
            ResetBoard[lgn][cln] = rand()%7+3;
        }
    }

    ResetBoard[0][0] = 1;
    ResetBoard[0][2] = 1;
    ResetBoard[0][3] = 1;
    ResetBoard[0][5] = 1;
    ResetBoard[0][7] = 0;

    ResetBoard[1][2] = 1;

    ResetBoard[2][0] = 0;
    ResetBoard[2][7] = 0;

    ResetBoard[3][0] = 0;
    ResetBoard[3][2] = 0;
    ResetBoard[3][5] = 1;
    ResetBoard[3][6] = 1;

    ResetBoard[4][0] = 1;
    ResetBoard[4][4] = 0;
    ResetBoard[4][7] = 1;

    ResetBoard[5][4] = 1;

    ResetBoard[6][1] = 0;
    ResetBoard[6][2] = 1;
    ResetBoard[6][3] = 1;
    ResetBoard[6][4] = 0;
    ResetBoard[6][5] = 1;

    ResetBoard[7][1] = 1;
    ResetBoard[7][3] = 0;
    ResetBoard[7][6] = 0;
}

void DEFITWO()
{
    // DEFI 1
    int lgn,cln;
    for(lgn=0;lgn<n;lgn++)
    {
        for(cln=0;cln<n;cln++)
        {
            ResetBoard[lgn][cln] = rand()%7+3;
        }
    }

    ResetBoard[0][0] = 0;
    ResetBoard[0][1] = 0;
    ResetBoard[0][2] = 1;
    ResetBoard[0][3] = 0;
    ResetBoard[0][4] = 1;
    ResetBoard[0][5] = 0;


    ResetBoard[1][0] = 1;
    ResetBoard[1][2] = 0;
    ResetBoard[1][4] = 0;

    ResetBoard[2][0] = 0;
    ResetBoard[2][1] = 1;
    ResetBoard[2][2] = 0;
    ResetBoard[2][6] = 1;

    ResetBoard[3][0] = 0;
    ResetBoard[3][4] = 0;
    ResetBoard[3][6] = 1;

    ResetBoard[4][0] = 1;
    ResetBoard[4][5] = 1;

    ResetBoard[5][1] = 0;
    ResetBoard[5][2] = 0;
    ResetBoard[5][3] = 1;
    ResetBoard[5][4] = 1;
    ResetBoard[5][5] = 0;
    ResetBoard[5][6] = 0;

    ResetBoard[6][7] = 0;

    ResetBoard[7][2] = 0;
    ResetBoard[7][6] = 0;
    ResetBoard[7][7] = 0;
}
