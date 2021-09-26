///////////////////////////////////
/* CE PROGRAMME UTILISE SDL 2.0  */
/* A CONFIGURER AU PREALABLE !!  */
/* FONCTIONNE SANS SDL_image !!  */
///////////////////////////////////

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "BackEnd.h"

#include <SDL.h>
#include <string>
#include <iostream>
//Initialisation des composants necessaires
    SDL_Window* fenetre = NULL; //Création de la fenêtre

    SDL_Surface* surface = NULL; // Création de la surface de la board
    SDL_Surface* ImageBoard8 = NULL;
    SDL_Surface* TitleBoardSurface = NULL;

    //LES CASES DE LA BOARD
    SDL_Surface** Images = NULL;
    SDL_Surface** surfaces = NULL;
    //LES BUTTONS
    SDL_Surface* ButtonSurface = NULL;
    SDL_Surface* RESOLVEButtonSurface = NULL;
    SDL_Surface* RESETButtonSurface = NULL;
    SDL_Surface* HELPButtonSurface = NULL;
    SDL_Surface* BACKButtonSurface = NULL;
    SDL_Surface* QUITButtonSurface = NULL;
    SDL_Surface* QuitMainScreen = NULL;

    SDL_Surface* EasyButton = NULL;
    SDL_Surface* HardButton = NULL;

    SDL_Surface* SelectOne = NULL;
    SDL_Surface* SelectZero = NULL;
    SDL_Surface* Selected = NULL;

    SDL_Surface* DefiButtonOne = NULL;
    SDL_Surface* DefiButtonTwo = NULL;

    //INTERFACES
    SDL_Surface* TitleBoardSetSurface = NULL;
    SDL_Surface* AnimationOne = NULL;
    SDL_Surface* AnimationTwo = NULL;

    //AWOO
    SDL_Surface* AwooImage = NULL;
    SDL_Surface* AwooSurface = NULL;

    //AWOO DIALOGUE
    SDL_Surface* Dialog = NULL;
    SDL_Surface* DialogSurface = NULL;

    //LES RECTANGLES POSITIONS
    SDL_Rect dim, TitleBoardPos, RelativePosOne,RelativePosTwo,NegativePos,AnimationOnePos,AnimationTwoPos;
    SDL_Rect ButtonPrint, RESOLVEButtonPrint, RESETButtonPrint, HELPButtonPrint, BACKButtonPrint, QUITButtonPrint;
    SDL_Rect EasyButtonPrint, HardButtonPrint, QuitMainPrint;
    SDL_Rect SelectOneDim, SelectZeroDim, SelectedDim;
    SDL_Rect AwooDim, AwooDialogDim;
    SDL_Rect DefiOneDim, DefiTwoDim;

//Lancer SDL + Créer fenêtre
int Initiation()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) //Vérification d'échec à l'initialisation
    {
        printf("SDL Init Error ! SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    fenetre = SDL_CreateWindow("TakuzuMAX",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,SDL_WINDOW_SHOWN);
    if(fenetre == NULL)
    {
        printf("SDL Window Error ! SDL_Error : %s\n",SDL_GetError());
        return 0;
    }
    else //Pas besoin de continuer sans fenêtre
    {
        surface = SDL_GetWindowSurface(fenetre);
    }
    return 1;
}

//Charger quelques élements d'interface au tout début du lancement
int loadMedia()
{
    ImageBoard8 = SDL_LoadBMP("Elements/MainScreen.bmp");
    if(ImageBoard8==NULL)
    {
        printf("SDL unable to load image %s !  SDL_Error : %s\n","Board8.bmp",SDL_GetError());
        return 0;
    }

    TitleBoardSurface = SDL_LoadBMP("Elements/TAKUZUMAX.bmp");
    if(TitleBoardSurface==NULL)
    {
        printf("SDL unable to load image %s !  SDL_Error : %s\n","TAKUZUMAX.bmp",SDL_GetError());
        return 0;
    }

    return 1;
}

//Charger les boutons du plateau
int loadMediaSlots(int Board, int ResetBoardValue, int Indice)
{
    if(n==8)
    {
        //MEMORY LEAK PREVENTION - Anti-chevauchement d'images / à regarder sur le gestionnaire des tâches pour confirmer.
        if( Images[Indice] != NULL)
        {
            SDL_FreeSurface(Images[Indice]);
        }

        if(ResetBoardValue == 1 || ResetBoardValue == 0)
        {
            if(ResetBoardValue == 1)
            {
                Images[Indice] = SDL_LoadBMP("Elements/OneR.bmp");
            }
            else if(ResetBoardValue == 0)
            {
                Images[Indice] = SDL_LoadBMP("Elements/ZeroR.bmp");
            }
        }
        else if(Board == 1)
        {
            Images[Indice] = SDL_LoadBMP("Elements/One.bmp");
        }
        else if(Board == 0)
        {
            Images[Indice] = SDL_LoadBMP("Elements/Zero.bmp");
        }
        else
        {
            Images[Indice] = SDL_LoadBMP("Elements/Blank.bmp");
        }

        if(Images[Indice]==NULL)
        {
            printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
            return 0;
        }
    }
    else if(n==4)
    {
        if( Images[Indice] != NULL)
        {
            SDL_FreeSurface(Images[Indice]);
        }
        if(ResetBoardValue == 1 || ResetBoardValue == 0)
        {
            if(ResetBoardValue == 1)
            {
                Images[Indice] = SDL_LoadBMP("Elements/GrosROne.bmp");
            }
            else if(ResetBoardValue == 0)
            {
                Images[Indice] = SDL_LoadBMP("Elements/GrosRZero.bmp");
            }
        }
        else if(Board == 1)
        {
            Images[Indice] = SDL_LoadBMP("Elements/GrosOne.bmp");
        }
        else if(Board == 0)
        {
            Images[Indice] = SDL_LoadBMP("Elements/GrosZero.bmp");
        }
        else
        {
            Images[Indice] = SDL_LoadBMP("Elements/GrosBlank.bmp");
        }

        if(Images[Indice]==NULL)
        {
            printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
            return 0;
        }
    }
    return 1;
}

//Charger facilement les élements nécessaires sur la fenetre
void UltraBlit()
{
    SDL_BlitSurface(ImageBoard8,NULL,surface,NULL);
    SDL_BlitSurface(TitleBoardSurface,NULL,surface,&TitleBoardPos);
    SDL_BlitSurface(ButtonSurface,NULL,surface,&ButtonPrint);
    SDL_BlitSurface(RESOLVEButtonSurface,NULL,surface,&RESOLVEButtonPrint);
    SDL_BlitSurface(HELPButtonSurface,NULL,surface,&HELPButtonPrint);
    SDL_BlitSurface(QUITButtonSurface,NULL,surface,&QUITButtonPrint);
    SDL_BlitSurface(RESETButtonSurface,NULL,surface,&RESETButtonPrint);
    SDL_BlitSurface(BACKButtonSurface,NULL,surface,&BACKButtonPrint);
    if(n==8)
    {
        SDL_BlitSurface(DefiButtonOne,NULL,surface,&DefiOneDim);
        SDL_BlitSurface(DefiButtonTwo,NULL,surface,&DefiTwoDim);
    }
    SDL_BlitSurface(SelectOne,NULL,surface,&SelectOneDim);
    SDL_BlitSurface(SelectZero,NULL,surface,&SelectZeroDim);
    SDL_BlitSurface(Selected,NULL,surface,&SelectedDim);
}

//Coller les Dialogues Aides de Awooo
int DialogueBox(int AwooBox, int validite)
{
    if( Dialog != NULL)
    {
        SDL_FreeSurface(Dialog);
    }

    if(AwooBox == 1 && validite == 1) //Le coup est bon
    {
        Dialog = SDL_LoadBMP("Dialogue/YesGood.bmp");
    }
    else if(AwooBox == 1 && validite == 0) //Le coup est mauvais, précédemment totalement bon.
    {
        Dialog = SDL_LoadBMP("Dialogue/BadMove.bmp");
    }
    else if(AwooBox == 0 && validite == 1) //Le coup est bon mais erreur(s) autre part
    {
        Dialog = SDL_LoadBMP("Dialogue/YesBut.bmp");
    }
    else if(AwooBox == 0 && validite == 0) //Le coup est mauvais, en plus erreur(s) autre part
    {
        Dialog = SDL_LoadBMP("Dialogue/NoNo.bmp");
    }
    else if(AwooBox == 5 && validite == 5) //Le dialogue d'intro pour appuyer sur New
    {
        Dialog = SDL_LoadBMP("Dialogue/Dialogue1.bmp");
    }
    else if(AwooBox == 6 && validite == 5) //Le dialogue après New
    {
        Dialog = SDL_LoadBMP("Dialogue/Dialogue2.bmp");
    }
    else if(AwooBox == 4 && validite == 5) //La board est réinitialisée
    {
        Dialog = SDL_LoadBMP("Dialogue/ResetDialog.bmp");
    }
    else if(AwooBox == 9 && validite == 5) //Victoire
    {
        Dialog = SDL_LoadBMP("Dialogue/DialogWin.bmp");
    }
    else if(AwooBox == 4 && validite == 6) //RollBack
    {
        Dialog = SDL_LoadBMP("Dialogue/Smug.bmp");
    }
    else if(AwooBox == 1 && validite == 7) //Helped
    {
        Dialog = SDL_LoadBMP("Dialogue/HelpDialog.bmp");
    }
    if(Dialog == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }
    SDL_BlitSurface(Dialog,NULL,DialogSurface,NULL);
    return 1;
}

//Charger les différentes expressions de Awoo
int loadMediaAwoo(int AwooBox)
{
    if(AwooImage != NULL)
    {
        SDL_FreeSurface(AwooImage);
    }

    if(AwooBox == 1 || AwooBox == 5 || AwooBox == 6)
    {
        AwooImage = SDL_LoadBMP("Awoo/AwooH.bmp");
    }
    else if(AwooBox == 0)
    {
        AwooImage = SDL_LoadBMP("Awoo/AwooD.bmp");
    }
    else if(AwooBox == 4)
    {
        AwooImage = SDL_LoadBMP("Awoo/AwooT.bmp");
    }
    else if(AwooBox == 9)
    {
        AwooImage = SDL_LoadBMP("Awoo/AwooW.bmp");
    }

    if(AwooImage == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }
    return 1;
}

//Charger les images des buttons
int loadMediaButton()
{
    if(ButtonSurface != NULL)
    {
        SDL_FreeSurface(ButtonSurface);
    }
    ButtonSurface = SDL_LoadBMP("Buttons/NewButton.bmp");
    if(ButtonSurface == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(RESOLVEButtonSurface != NULL)
    {
        SDL_FreeSurface(RESOLVEButtonSurface);
    }
    RESOLVEButtonSurface = SDL_LoadBMP("Buttons/LoadButton.bmp");
    if(RESOLVEButtonSurface == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(HELPButtonSurface != NULL)
    {
        SDL_FreeSurface(HELPButtonSurface);
    }
    HELPButtonSurface = SDL_LoadBMP("Buttons/HELPButton.bmp");
    if(HELPButtonSurface == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(QUITButtonSurface != NULL)
    {
        SDL_FreeSurface(QUITButtonSurface);
    }
    QUITButtonSurface = SDL_LoadBMP("Buttons/QUITButton.bmp");
    if(QUITButtonSurface == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(RESETButtonSurface != NULL)
    {
        SDL_FreeSurface(RESETButtonSurface);
    }
    RESETButtonSurface = SDL_LoadBMP("Buttons/RESETButton.bmp");
    if(RESETButtonSurface == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(BACKButtonSurface != NULL)
    {
        SDL_FreeSurface(BACKButtonSurface);
    }
    BACKButtonSurface = SDL_LoadBMP("Buttons/BACKButton.bmp");
    if(BACKButtonSurface == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(DefiButtonOne != NULL)
    {
        SDL_FreeSurface(DefiButtonOne);
    }
    DefiButtonOne = SDL_LoadBMP("Buttons/DefiOne.bmp");
    if(DefiButtonOne == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(DefiButtonTwo != NULL)
    {
        SDL_FreeSurface(DefiButtonTwo);
    }
    DefiButtonTwo = SDL_LoadBMP("Buttons/DefiTwo.bmp");
    if(DefiButtonTwo == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(SelectOne != NULL)
    {
        SDL_FreeSurface(SelectOne);
    }
    SelectOne = SDL_LoadBMP("Elements/SelectOne.bmp");
    if(SelectOne == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(SelectZero != NULL)
    {
        SDL_FreeSurface(SelectZero);
    }
    SelectZero = SDL_LoadBMP("Elements/SelectZero.bmp");
    if(SelectZero == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(Selected!= NULL)
    {
        SDL_FreeSurface(Selected);
    }
    Selected = SDL_LoadBMP("Elements/Selected.bmp");
    if(Selected == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    return 1;
}

//Fermer mais définitivement le programme
void Close()
{
    //Surface Destruction
    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_FreeSurface(TitleBoardSurface);
    TitleBoardSurface = NULL;

    SDL_FreeSurface(TitleBoardSetSurface);
    TitleBoardSetSurface = NULL;


    SDL_FreeSurface(EasyButton);
    EasyButton = NULL;

    SDL_FreeSurface(HardButton);
    HardButton = NULL;

    //Destruction fenêtre
    SDL_DestroyWindow(fenetre);
    fenetre = NULL;

    //Quitter SDL
    SDL_Quit();
}

//Fermer l'interface de la board pour revenir au menu principal
void NewClose()
{
    int i;
    SDL_FreeSurface(Dialog);
    Dialog = NULL;

    SDL_FreeSurface(DialogSurface);
    DialogSurface = NULL;

    SDL_FreeSurface(SelectOne);
    SelectOne = NULL;

    SDL_FreeSurface(SelectZero);
    SelectZero = NULL;

    SDL_FreeSurface(Selected);
    Selected = NULL;

    if(n==4 || n==8)
    {
        for(i=0;i<n*n;i++)
        {
            SDL_FreeSurface(Images[i]);
            Images[i] = NULL;
            SDL_FreeSurface(surfaces[i]);
            surfaces[i] = NULL;
        }
    }

    SDL_FreeSurface(ButtonSurface);
    ButtonSurface = NULL;

    SDL_FreeSurface(RESOLVEButtonSurface);
    RESOLVEButtonSurface = NULL;

    SDL_FreeSurface(RESETButtonSurface);
    RESETButtonSurface = NULL;

    SDL_FreeSurface(HELPButtonSurface);
    HELPButtonSurface = NULL;

    SDL_FreeSurface(BACKButtonSurface);
    BACKButtonSurface = NULL;

    SDL_FreeSurface(QUITButtonSurface);
    QUITButtonSurface = NULL;

    SDL_FreeSurface(DefiButtonOne);
    DefiButtonOne = NULL;

    SDL_FreeSurface(DefiButtonTwo);
    DefiButtonTwo = NULL;

    SDL_FreeSurface(AwooImage);
    AwooImage = NULL;

    SDL_FreeSurface(AwooSurface);
    AwooImage = NULL;

    SDL_FreeSurface(ImageBoard8);
    ImageBoard8 = NULL;
}

//Charger les images du plateau sur la fenetre
int SuperBlitz()
{
    int Indice = 0;
    int lgn, cln;
    for(lgn=0;lgn<n;lgn++)
    {
        for(cln=0;cln<n;cln++)
        {
            if( !loadMediaSlots(PlayerBoard[lgn][cln],ResetBoard[lgn][cln],Indice) )
            {
                printf("Failed to load media !\n");
                return 0;
            }
            Indice++;
        }
    }
    for(lgn=0;lgn<(n*n);lgn++)
    {
        SDL_BlitSurface(Images[lgn],NULL,surfaces[lgn],NULL);
    }

    return 1;
}

int MainScreenScroll(int Decal)
{
    if(AnimationOnePos.x == 1280)
    {
        AnimationOnePos.x = RelativePosOne.x;
        Decal = 0;
    }
    else if(AnimationOnePos.x == 0 && Decal == 2)
    {
        Decal = 0;
        RelativePosOne.x++;
        AnimationOnePos.x = RelativePosOne.x;
    }
    else if(AnimationOnePos.x == 0 && Decal != 2)
    {
        AnimationOnePos.x = RelativePosOne.x;
    }
    else if(AnimationOnePos.x >= 0 && Decal == 2)
    {
        RelativePosOne.x = -590;
        AnimationOnePos.x++;
        Decal = 0;
    }

    if(RelativePosTwo.x == -1280)
    {
        RelativePosTwo.x = 590;
        AnimationTwoPos.x = RelativePosTwo.x;
        Decal = 0;
    }
    else if(Decal == 0)
    {
        Decal = 0;
        RelativePosTwo.x--;
        AnimationTwoPos.x = RelativePosTwo.x;
    }
    else if(Decal != 0)
    {
        AnimationTwoPos.x = RelativePosTwo.x;
    }

    return Decal;
}

//L'animation du titre dans le plateau
int ScrollTitle(int Decal)
{
    if(TitleBoardPos.x == 1280)
    {
        TitleBoardPos.x = NegativePos.x;
        Decal = 0;
    }
    else if(TitleBoardPos.x == 0 && Decal == 2)
    {
        Decal = 0;
        NegativePos.x++;
        TitleBoardPos.x = NegativePos.x;
    }
    else if(TitleBoardPos.x == 0 && Decal != 2)
    {
        TitleBoardPos.x = NegativePos.x;
    }
    else if(TitleBoardPos.x >= 0 && Decal == 2)
    {
        NegativePos.x = -525;
        TitleBoardPos.x++;
        Decal = 0;
    }
    return Decal;
}

//Après victoire, rendre tous buttons indisponibles sauf New et Quit
int EndMecanism()
{
    if(BACKButtonSurface != NULL)
    {
        SDL_FreeSurface(BACKButtonSurface);
    }
    BACKButtonSurface = SDL_LoadBMP("Buttons/GrisBack.bmp");
    if(BACKButtonSurface == 0)
    {
        printf("ERROR BUTTON !\n");
        return 0;
    }

    if(HELPButtonSurface != NULL)
    {
        SDL_FreeSurface(HELPButtonSurface);
    }
    HELPButtonSurface = SDL_LoadBMP("Buttons/GrisHelp.bmp");
    if(HELPButtonSurface == 0)
    {
        printf("ERROR BUTTON !\n");
        return 0;
    }

    if(RESETButtonSurface != NULL)
    {
        SDL_FreeSurface(RESETButtonSurface);
    }
    RESETButtonSurface = SDL_LoadBMP("Buttons/GrisReset.bmp");
    if(RESETButtonSurface == 0)
    {
        printf("ERROR BUTTON !\n");
        return 0;
    }

    if(RESOLVEButtonSurface != NULL)
    {
        SDL_FreeSurface(RESOLVEButtonSurface);
    }
    RESOLVEButtonSurface = SDL_LoadBMP("Buttons/GrisLoad.bmp");
    if(RESOLVEButtonSurface == 0)
    {
        printf("ERROR BUTTON !\n");
        return 0;
    }
    return 1;
}

//Initialisation des élements dynamiques pour les images et surfaces et préparation du terrain.
int LoadUpN()
{
    int lgn;

    Images = static_cast<SDL_Surface**>(malloc((n*n)*sizeof(SDL_Surface*)));
    for(lgn = 0; lgn<(n*n) ; lgn++)
    {
        Images[lgn] = NULL;
    }
    surfaces = static_cast<SDL_Surface**>(malloc((n*n)*sizeof(SDL_Surface*)));
    for(lgn = 0; lgn<n ; lgn++)
    {
        surfaces[lgn] = NULL;
    }
    for(lgn=0;lgn<(n*n);lgn++)
    {
        if(n==8)
        {
            surfaces[lgn] = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
        }
        else if(n==4)
        {
            surfaces[lgn] = SDL_CreateRGBSurface(0, 120, 120, 32, 0, 0, 0, 0);
        }

    }
    AwooImage = NULL;
    Dialog = NULL;
    if( !loadMediaButton() )
    {
        printf("Failed to load buttons !\n");
        return 0;
    }
    return 1;
}

//Algorithme pour n8 qui retourne si le coup est valide ou non
int BoardPressEight(int buttonx, int buttony,int Selection)
{
    int lgn,cln, Replacement,Coord;
    Replacement = buttonx;
    Coord = 0;

    while(Replacement>=600)
    {
        if(Replacement-70 > 600)
        {
            Replacement -= 70;
            Coord++;
        }
        else
        {
            break;
        }
    }
    cln = Coord;
    Replacement = buttony;
    Coord = 0;
    while(Replacement>=80)
    {
        if(Replacement-70 > 80)
        {
            Replacement -= 70;
            Coord++;
        }
        else
        {
            break;
        }
    }
    lgn = Coord;
    if(ResetBoard[lgn][cln] != 1 && ResetBoard[lgn][cln] != 0)
    {
        if(PlayerBoard[lgn][cln] == Selection) //Selection Egale
        {
            BACK[BACKSize-1] = create_Position(lgn,cln,PlayerBoard[lgn][cln]);
            transfert(1);
            PlayerBoard[lgn][cln] = rand()%7+3;
            if(!SuperBlitz())
            {
                printf("ERROR SUPERBLITZ!\n");
                return -1;
            }
        }
        else //Remplacement ou element ajouté
        {
            BACK[BACKSize-1] = create_Position(lgn,cln,PlayerBoard[lgn][cln]);
            transfert(1);
            PlayerBoard[lgn][cln] = Selection;
            if(BACKButtonSurface != NULL)
            {
                SDL_FreeSurface(BACKButtonSurface);
            }
            BACKButtonSurface = SDL_LoadBMP("Buttons/BackButton.bmp");
            if(BACKButtonSurface == NULL)
            {
                printf("Failed to load button !\n");
                return -1;
            }
        }
        if(!SuperBlitz())
        {
            printf("ERROR SUPERBLITZ!\n");
            return -1;
        }
    }
    return VerifPos(PlayerBoard,n,lgn,cln,Scan,Scan2);
}

//Algorithme pour n4 qui retourne si le coup est valide ou non
int BoardPressFour(int buttonx, int buttony, int Selection)
{
    int lgn,cln, Replacement,Coord;
    Replacement = buttonx;
    Coord = 0;
    while(Replacement>=600)
    {
        if(Replacement-140 > 600)
        {
            Replacement -= 140;
            Coord++;
        }
        else
        {
            break;
        }
    }
    cln = Coord;
    Replacement = buttony;
    Coord = 0;
    while(Replacement>=80)
    {
        if(Replacement-140 > 80)
        {
            Replacement -= 140;
            Coord++;
        }
        else
        {
            break;
        }
    }
    lgn = Coord;
    if(ResetBoard[lgn][cln] != 1 && ResetBoard[lgn][cln] != 0)
    {
        if(PlayerBoard[lgn][cln] == Selection) //Selection Egale
        {
            BACK[BACKSize-1] = create_Position(lgn,cln,PlayerBoard[lgn][cln]);
            transfert(1);
            PlayerBoard[lgn][cln] = rand()%7+3;
            if(!SuperBlitz())
            {
                printf("ERROR SUPERBLITZ!\n");
                return -1;
            }
        }
        else //Remplacement ou element ajouté
        {
            BACK[BACKSize-1] = create_Position(lgn,cln,PlayerBoard[lgn][cln]);
            transfert(1);
            PlayerBoard[lgn][cln] = Selection;
            if(BACKButtonSurface != NULL)
            {
                SDL_FreeSurface(BACKButtonSurface);
            }
            BACKButtonSurface = SDL_LoadBMP("Buttons/BackButton.bmp");
            if(BACKButtonSurface == NULL)
            {
                printf("Failed to load button !\n");
                return -1;
            }
            if(!SuperBlitz())
            {
                printf("ERROR SUPERBLITZ!\n");
                return -1;
            }
        }
    }
    return VerifPos(PlayerBoard,n,lgn,cln,Scan,Scan2);
}

//Charger les images du menu principal
int loadMediaMainScreenButton()
{
    if(AnimationOne != NULL)
    {
        SDL_FreeSurface(AnimationOne);
    }
    AnimationOne = SDL_LoadBMP("Elements/AnimationOne.bmp");
    if(AnimationOne == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(AnimationTwo != NULL)
    {
        SDL_FreeSurface(AnimationTwo);
    }
    AnimationTwo = SDL_LoadBMP("Elements/AnimationTwo.bmp");
    if(AnimationTwo == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(EasyButton != NULL)
    {
        SDL_FreeSurface(EasyButton);
    }
    EasyButton = SDL_LoadBMP("Elements/Easy.bmp");
    if(EasyButton == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }
    if(HardButton != NULL)
    {
        SDL_FreeSurface(HardButton);
    }
    HardButton = SDL_LoadBMP("Elements/Hard.bmp");
    if(HardButton == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(QuitMainScreen != NULL)
    {
        SDL_FreeSurface(QuitMainScreen);
    }
    QuitMainScreen = SDL_LoadBMP("Buttons/QUIT.bmp");
    if(QuitMainScreen == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    if(ImageBoard8 != NULL)
    {
        SDL_FreeSurface(ImageBoard8);
    }
    ImageBoard8 = SDL_LoadBMP("Elements/MainScreen.bmp");
    if(ImageBoard8 == NULL)
    {
        printf("SDL unable to load image !  SDL_Error : %s\n",SDL_GetError());
        return 0;
    }

    return 1;
}



int main(int argc, char* args[])
{
    //INITIALISATION
    if( !Initiation() )
    {
        printf("Failed to initialize !\n");
        goto Quit;
    }

    else if( !loadMedia() )
    {
        printf("Failed to load media !\n");
        goto Quit;
    }
    else
    {
        //MAINLOOP INITIATION
        int lgn,i,j;
        int AwooBox = 5;
        int validite = 5;
        int titlescreen = 0;
        int Decal;
        int Once = 1;
        int quit = 0;
        int ShowIt = 0;
        int Selection = 0;
        int TotalM;
        DialogSurface = SDL_CreateRGBSurface(0, 560, 120, 32, 0, 0, 0, 0);
        ButtonSurface = SDL_CreateRGBSurface(0, 180, 60, 32, 0, 0, 0, 0);
        RESOLVEButtonSurface = SDL_CreateRGBSurface(0, 180, 60, 32, 0, 0, 0, 0);
        HELPButtonSurface = SDL_CreateRGBSurface(0, 180, 60, 32, 0, 0, 0, 0);
        QUITButtonSurface = SDL_CreateRGBSurface(0, 180, 60, 32, 0, 0, 0, 0);
        BACKButtonSurface = SDL_CreateRGBSurface(0, 180, 60, 32, 0, 0, 0, 0);
        RESETButtonSurface = SDL_CreateRGBSurface(0, 180, 60, 32, 0, 0, 0, 0);
        TitleBoardSetSurface = SDL_CreateRGBSurface(0, 525, 60, 32, 0, 0, 0, 0);

        ButtonPrint.x = 20;
        ButtonPrint.y = 450;
        RESETButtonPrint.x = 210;
        RESETButtonPrint.y = 450;
        QUITButtonPrint.x = 400;
        QUITButtonPrint.y = 450;
        BACKButtonPrint.x = 20;
        BACKButtonPrint.y = 530;
        HELPButtonPrint.x = 210;
        HELPButtonPrint.y = 530;
        RESOLVEButtonPrint.x = 400;
        RESOLVEButtonPrint.y = 530;
        AwooDim.x = 15;
        AwooDim.y = 198;
        AwooDialogDim.x = 20;
        AwooDialogDim.y = 120;
        SelectOneDim.x = 1200;
        SelectOneDim.y = 120;
        SelectZeroDim.x = 1200;
        SelectZeroDim.y = 240;
        SelectedDim.x = SelectZeroDim.x;
        SelectedDim.y = SelectZeroDim.y;
        NegativePos.x = -525;
        NegativePos.y = 0;
        RelativePosOne.x = -590;
        RelativePosOne.y = 0;
        RelativePosTwo.x = 590;
        RelativePosTwo.y = 0;
        EasyButtonPrint.x = 500;
        EasyButtonPrint.y = 300;
        HardButtonPrint.x = 500;
        HardButtonPrint.y = 400;
        QuitMainPrint.x = 500;
        QuitMainPrint.y = 500;
        DefiOneDim.x = 1190;
        DefiOneDim.y = 360;
        DefiTwoDim.x = 1190;
        DefiTwoDim.y = 485;
        SDL_Event f;
        SDL_Event e;
//Retour au menu principal
    MainMenu :
        Decal = 0;
        //Charger les boutons du menu
        if(!loadMediaMainScreenButton())
        {
            printf("ERROR LOADING Mainscreen BUTTONS ! \n");
            goto Quit;
        }

        TitleBoardPos.x = 360;
        TitleBoardPos.y = 200;
        SDL_BlitSurface(TitleBoardSurface,NULL,TitleBoardSetSurface,NULL);

        //MENU LOOP
        while( titlescreen != 1 )
        {
            while( SDL_PollEvent(&f) != 0 ) // APPUIE SUR LA CROIX
            {
                if( f.type == SDL_QUIT )
                {
                    goto Quit;
                }
            }
            SDL_BlitSurface(ImageBoard8,NULL,surface,NULL);
            SDL_BlitSurface(AnimationOne,NULL,surface,&AnimationOnePos);
            SDL_BlitSurface(AnimationTwo,NULL,surface,&AnimationTwoPos);
            SDL_BlitSurface(TitleBoardSurface,NULL,surface,&TitleBoardPos);
            SDL_BlitSurface(EasyButton,NULL,surface,&EasyButtonPrint);
            SDL_BlitSurface(HardButton,NULL,surface,&HardButtonPrint);
            SDL_BlitSurface(QuitMainScreen,NULL,surface,&QuitMainPrint);

            //L'animation
            Decal = MainScreenScroll(Decal);
            if(Decal != 2)
            {
                Decal++;;
            }
            if(f.type == SDL_MOUSEBUTTONDOWN)
            {
                //NEW
                if(f.button.y > EasyButtonPrint.y
                        && f.button.y <= EasyButtonPrint.y + 80
                        && f.button.x > EasyButtonPrint.x
                        && f.button.x <= EasyButtonPrint.x + 220
                        && Once == 1)
                {
                    Once = 0;
                    f.button.y = 0;
                    f.button.x = 0;
                    titlescreen = 1;
                    n = 4;
                    BackEnd_main();
                }
                else if(f.button.y > HardButtonPrint.y
                        && f.button.y <= HardButtonPrint.y + 80
                        && f.button.x > HardButtonPrint.x
                        && f.button.x <= HardButtonPrint.x + 220
                        && Once == 1)
                {
                    Once = 0;
                    f.button.y = 0;
                    f.button.x = 0;
                    titlescreen = 1;
                    n = 8;
                    BackEnd_main();
                }
                else if(f.button.y > QuitMainPrint.y
                        && f.button.y <= QuitMainPrint.y + 80
                        && f.button.x > QuitMainPrint.x
                        && f.button.x <= QuitMainPrint.x + 220
                        && Once == 1)
                {
                    Once = 0;
                    goto Quit;
                }

                if(f.type == SDL_MOUSEBUTTONUP)
                {
                    Once = 1;
                }
            }
            SDL_UpdateWindowSurface(fenetre);
        }
        titlescreen = 0;
        SDL_FreeSurface(ImageBoard8);
        ImageBoard8 = NULL;

        TitleBoardPos.x = 0;
        TitleBoardPos.y = 10;

        if(!LoadUpN())
        {
            printf("ERROR LOADUPN !\n");
            goto Quit;
        }

        SDL_BlitSurface(TitleBoardSurface,NULL,TitleBoardSetSurface,NULL);
        SDL_BlitSurface(ImageBoard8,NULL,surface,NULL);
        SDL_BlitSurface(TitleBoardSurface,NULL,surface,&TitleBoardPos);
        SDL_BlitSurface(AwooImage,NULL,AwooSurface,NULL);
        SDL_BlitSurface(Dialog,NULL,DialogSurface,NULL);

        SDL_BlitSurface(ButtonSurface,NULL,surface,&ButtonPrint);
        SDL_BlitSurface(RESOLVEButtonSurface,NULL,surface,&RESOLVEButtonPrint);
        SDL_BlitSurface(HELPButtonSurface,NULL,surface,&HELPButtonPrint);
        SDL_BlitSurface(QUITButtonSurface,NULL,surface,&QUITButtonPrint);
        SDL_BlitSurface(RESETButtonSurface,NULL,surface,&RESETButtonPrint);
        SDL_BlitSurface(BACKButtonSurface,NULL,surface,&BACKButtonPrint);

        quit = 0;
        ShowIt = 0;
        Decal = 0;
        if(ImageBoard8 != NULL)
        {
            SDL_FreeSurface(ImageBoard8);
        }
        ImageBoard8 = SDL_LoadBMP("Elements/Board8.bmp");
        if(ImageBoard8==NULL)
        {
            printf("SDL unable to load image %s !  SDL_Error : %s\n","Board8.bmp",SDL_GetError());
            goto Quit;
        }
        //ACTIVITES DU MAINLOOP
        while( !quit )
        {
            while( SDL_PollEvent(&e) != 0 ) // APPUIE SUR LA CROIX
            {
                if( e.type == SDL_QUIT )
                {
                    goto Quit;
                }
            }

            //Event Bouton Instruction
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                //NEW
                if(e.button.y > ButtonPrint.y
                        && e.button.y <= ButtonPrint.y + 60
                        && e.button.x > ButtonPrint.x
                        && e.button.x <= ButtonPrint.x + 180
                        && Once == 1)
                {
                    Once = 0;
                    TotalN = 0;
                    if(ShowIt == 1)
                    {
                        ReinitBoard(ResetBoard,PlayerBoard,n,BACK,BACKSize);
                    }
                    ShowIt = 1;
                    GenerateBoard(Board,PlayerBoard,ResetBoard,n,Scan,Scan2);
                    TotalM = GetNumberOfFreeCase(n);
                    AwooBox = 6;
                    validite = 5;
                    if(!loadMediaButton())
                    {
                        printf("ERROR BUTTONS!\n");
                        goto Quit;
                    }
                    if(!SuperBlitz())
                    {
                        printf("ERROR SUPERBLITZ!\n");
                        goto Quit;
                    }
                }

                //RESOLVE
                else if(e.button.y > RESOLVEButtonPrint.y
                        && e.button.y <= RESOLVEButtonPrint.y+60
                        && e.button.x > RESOLVEButtonPrint.x
                        && e.button.x <= RESOLVEButtonPrint.x+180
                        && ShowIt == 1
                        && Once == 1)
                {
                    Once = 0;
                    if(ShowIt == 1)
                    {
                        ReinitBoard(ResetBoard,PlayerBoard,n,BACK,BACKSize);
                        TargetBoardResolver(PlayerBoard,ResetBoard,n,Scan,Scan2);
                        if(!SuperBlitz())
                        {
                            printf("ERROR SUPERBLITZ!\n");
                            goto Quit;
                        }
                    }
                }

                //RESET
                else if(e.button.y > RESETButtonPrint.y
                        && e.button.y <= RESETButtonPrint.y+60
                        && e.button.x > RESETButtonPrint.x
                        && e.button.x <= RESETButtonPrint.x+180
                        && ShowIt == 1
                        && Once == 1)
                {
                    Once = 0;
                    if(ShowIt == 1)
                    {
                        ReinitBoard(ResetBoard,PlayerBoard,n, BACK,BACKSize);
                        AwooBox = 4;
                        validite = 5;
                        if(!SuperBlitz())
                        {
                            printf("ERROR SUPERBLITZ!\n");
                            goto Quit;
                        }
                        Once = 0;
                    }
                }

                //HELP
                else if(e.button.y > HELPButtonPrint.y
                        && e.button.y <= HELPButtonPrint.y+60
                        && e.button.x > HELPButtonPrint.x
                        && e.button.x <= HELPButtonPrint.x+180
                        && ShowIt == 1
                        && Once == 1
                        && TotalN < TotalM-1) // <- Modifiable pour déterminer le nombre d'aide possible
                {
                    if(TotalN< TotalM-1)
                    {
                        Once = 0;
                        AwooBox = 1;
                        validite = 7;
                        GetHelp(ResetBoard,Board,n,Scan,Scan2);
                        if(!SuperBlitz())
                        {
                            printf("ERROR SUPERBLITZ!\n");
                            goto Quit;
                        }
                        //Ne plus obtenir de l'aide si c'est la dernière valeur
                        if(TotalN == TotalM-1)
                        {
                            if(HELPButtonSurface != NULL)
                            {
                                SDL_FreeSurface(HELPButtonSurface);
                            }
                            HELPButtonSurface = SDL_LoadBMP("Buttons/GrisHelp.bmp");
                            if(HELPButtonSurface == 0)
                            {
                                printf("ERROR BUTTON !\n");
                                goto Quit;
                            }
                        }
                    }
                }

                //BACK
                else if(e.button.y > BACKButtonPrint.y
                        && e.button.y <= BACKButtonPrint.y+60
                        && e.button.x > BACKButtonPrint.x
                        && e.button.x <= BACKButtonPrint.x+180
                        && ShowIt == 1
                        && Once == 1)
                {
                    Once = 0;
                    if(ShowIt == 1 && BACKSize-2 >= 0)
                    {
                        PlayerBoard[ BACK[BACKSize-2].lgn ][ BACK[BACKSize-2].cln ] = BACK[BACKSize-2].valeur;
                        transfert(0);
                        AwooBox = 4;
                        validite = 6;
                        if(!SuperBlitz())
                        {
                            printf("ERROR SUPERBLITZ!\n");
                            goto Quit;
                        }
                    }
                    else
                    {
                        if(BACKButtonSurface != NULL)
                        {
                            SDL_FreeSurface(BACKButtonSurface);
                        }
                        BACKButtonSurface = SDL_LoadBMP("Buttons/GrisBack.bmp");
                        if(BACKButtonSurface == 0)
                        {
                            printf("ERROR BUTTON !\n");
                            goto Quit;
                        }
                    }
                }

                //QUIT
                else if(e.button.y > QUITButtonPrint.y
                        && e.button.y <= QUITButtonPrint.y+60
                        && e.button.x > QUITButtonPrint.x
                        && e.button.x <= QUITButtonPrint.x+180
                        && Once == 1)
                {
                    TotalN = 0;
                    BackEnd_Close(PlayerBoard,ResetBoard,Board,Scan,Scan2,n,BACK,InterBACK);
                    NewClose();
                    goto MainMenu;
                }

                //Select 0
                else if(e.button.y > SelectZeroDim.y
                        && e.button.y <= SelectZeroDim.y + 60
                        && e.button.x > SelectZeroDim.x
                        && e.button.x <= SelectZeroDim.x + 180
                        && Once == 1)
                {
                    Once = 0;
                    Selection = 0;
                    SelectedDim.x = SelectZeroDim.x;
                    SelectedDim.y = SelectZeroDim.y;
                }

                //Select 1
                else if(e.button.y > SelectOneDim.y
                        && e.button.y <= SelectOneDim.y + 60
                        && e.button.x > SelectOneDim.x
                        && e.button.x <= SelectOneDim.x + 180
                        && Once == 1)
                {
                    Once = 0;
                    Selection = 1;
                    SelectedDim.x = SelectOneDim.x;
                    SelectedDim.y = SelectOneDim.y;
                }
                //Defi One
                else if(e.button.y > DefiOneDim.y
                        && e.button.y <= DefiOneDim.y + 125
                        && e.button.x > DefiOneDim.x
                        && e.button.x <= DefiOneDim.x + 80
                        && n == 8
                        && Once == 1)
                {
                    Once = 0;
                    DEFIONE();
                    ReinitBoard(ResetBoard,PlayerBoard,n, BACK,BACKSize);
                    TotalM = GetNumberOfFreeCase(n);
                    if(!SuperBlitz())
                    {
                        printf("ERROR SUPERBLITZ!\n");
                        goto Quit;
                    }
                }

                //Defi Two
                else if(e.button.y > DefiTwoDim.y
                        && e.button.y <= DefiTwoDim.y + 125
                        && e.button.x > DefiTwoDim.x
                        && e.button.x <= DefiTwoDim.x + 80
                        && n == 8
                        && Once == 1)
                {
                    Once = 0;
                    DEFITWO();
                    ReinitBoard(ResetBoard,PlayerBoard,n, BACK,BACKSize);
                    TotalM = GetNumberOfFreeCase(n);
                    if(!SuperBlitz())
                    {
                        printf("ERROR SUPERBLITZ!\n");
                        goto Quit;
                    }
                }
                //BOARD
                else if(e.button.y >= 80
                        && e.button.y <= 640
                        && e.button.x >= 600
                        && e.button.x <= 1160
                        && ShowIt == 1
                        && Once == 1)
                {
                    Once = 0;
/* POUR EVITER DE COPIER 64 FOIS LES CONDITIONS TRES LONGUES, ON VA PROCEDER A PLUSIEURS CALCULS.*/
                    if(n==8)
                    {
                        validite = BoardPressEight(e.button.x,e.button.y,Selection);
                        if(validite == -1)
                        {
                            printf("ERROR SOMEWHERE VALIDITE!\n");
                            goto Quit;
                        }
                    }
                    else if(n==4)
                    {
                        validite = BoardPressFour(e.button.x,e.button.y,Selection);
                        if(validite == -1)
                        {
                            printf("ERROR SOMEWHERE VALIDITE!\n");
                            goto Quit;
                        }
                    }

                    AwooBox = 0;
                    for(i=0;i<n;i++)
                    {
                        for(j=0;j<n;j++)
                        {
                            AwooBox += VerifPos(PlayerBoard,n,i,j,Scan,Scan2);
                        }
                    }
                    if(AwooBox != n*n)
                    {
                        AwooBox = 0;
                    }
                    else
                    {
                        AwooBox = 1;
                    }
                }
            }
            //Touch Once
            if(e.type == SDL_MOUSEBUTTONUP)
            {
                Once = 1;
            }

            //Montrer la Board
            if(ShowIt == 1)
            {
                dim.x = 620;
                dim.y = 100;
                UltraBlit();
                if(n==8)
                {
                    for(lgn=0;lgn<(n*n);lgn++)
                    {
                        SDL_BlitSurface(surfaces[lgn],NULL,surface,&dim);
                        dim.x += 70;
                        if(lgn%n == (n-1))
                        {
                            dim.x = 620;
                            dim.y += 70;
                        }
                    }
                }
                else if(n==4)
                {
                    for(lgn=0;lgn<(n*n);lgn++)
                    {
                        if(Selection==1)
                        {

                        }
                        SDL_BlitSurface(surfaces[lgn],NULL,surface,&dim);
                        dim.x += 140;
                        if(lgn%n == (n-1))
                        {
                            dim.x = 620;
                            dim.y += 140;
                        }
                    }
                }
            }

            if(ShowIt == 0)
            {
                if( !loadMediaAwoo(5))
                {
                    printf("Awoo Error\n");
                    goto Quit;
                }

                if( !DialogueBox(5,5))
                {
                    printf("Dialogbox Error\n");
                    goto Quit;
                }
                UltraBlit();
                SDL_BlitSurface(AwooImage,NULL,surface,&AwooDim);
                SDL_BlitSurface(Dialog,NULL,surface,&AwooDialogDim);
            }
            else
            {
                while(CheckWin() == 1)
                {
                    while( SDL_PollEvent(&e) != 0 )
                    {
                        if( e.type == SDL_QUIT )
                        {
                            goto Quit;
                        }
                    }
                    if( !loadMediaAwoo(9))
                    {
                        printf("Awoo Error\n");
                        goto Quit;
                    }

                    if( !DialogueBox(9,5))
                    {
                        printf("Dialogbox Error\n");
                        goto Quit;
                    }
                    EndMecanism();
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(e.button.y > ButtonPrint.y
                                && e.button.y <= ButtonPrint.y + 60
                                && e.button.x > ButtonPrint.x
                                && e.button.x <= ButtonPrint.x + 180
                                && Once == 1)
                        {
                            if(ShowIt == 1)
                            {
                                ReinitBoard(ResetBoard,PlayerBoard,n,BACK,BACKSize);
                            }
                            GenerateBoard(Board,PlayerBoard,ResetBoard,n,Scan,Scan2);
                            AwooBox = 6;
                            validite = 5;
                            if(!loadMediaButton())
                            {
                                printf("ERROR BUTTONS!\n");
                                goto Quit;
                            }
                            if(!SuperBlitz())
                            {
                                printf("ERROR SUPERBLITZ!\n");
                                goto Quit;
                            }
                        }
                        else if(e.button.y > QUITButtonPrint.y
                                && e.button.y <= QUITButtonPrint.y+60
                                && e.button.x > QUITButtonPrint.x
                                && e.button.x <= QUITButtonPrint.x+180
                                && Once == 1)
                        {
                            TotalN = 0;
                            BackEnd_Close(PlayerBoard,ResetBoard,Board,Scan,Scan2,n,BACK,InterBACK);
                            NewClose();
                            goto MainMenu;
                        }
                    }
                    if(e.type == SDL_MOUSEBUTTONUP)
                    {
                        Once = 1;
                    }

                    dim.x = 620;
                    dim.y = 100;
                    UltraBlit();
                    if(n==8)
                    {
                        for(lgn=0;lgn<(n*n);lgn++)
                        {
                            SDL_BlitSurface(surfaces[lgn],NULL,surface,&dim);
                            dim.x += 70;
                            if(lgn%n == (n-1))
                            {
                                dim.x = 620;
                                dim.y += 70;
                            }
                        }
                    }
                    else if(n==4)
                    {
                        for(lgn=0;lgn<(n*n);lgn++)
                        {
                            SDL_BlitSurface(surfaces[lgn],NULL,surface,&dim);
                            dim.x += 140;
                            if(lgn%n == (n-1))
                            {
                                dim.x = 620;
                                dim.y += 140;
                            }
                        }
                    }
                    SDL_BlitSurface(AwooImage,NULL,surface,&AwooDim);
                    SDL_BlitSurface(Dialog,NULL,surface,&AwooDialogDim);
                    Decal = ScrollTitle(Decal);
                    if(Decal != 2)
                    {
                        Decal++;
                    }
                    SDL_UpdateWindowSurface(fenetre);
                }

                if( !loadMediaAwoo(AwooBox))
                {
                    printf("Awoo Error\n");
                    goto Quit;
                }

                if( !DialogueBox(AwooBox,validite))
                {
                    printf("Dialogbox Error\n");
                    goto Quit;
                }
                SDL_BlitSurface(AwooImage,NULL,surface,&AwooDim);
                SDL_BlitSurface(Dialog,NULL,surface,&AwooDialogDim);
            }
            SDL_UpdateWindowSurface(fenetre);

            Decal = ScrollTitle(Decal);
            if(Decal != 2)
            {
                Decal++;;
            }
        }
    }
Quit :
    NewClose();
    Close();
    BackEnd_Close(PlayerBoard,ResetBoard,Board,Scan,Scan2,n,BACK,InterBACK);
    return 0;
}

