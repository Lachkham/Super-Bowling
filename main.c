#include <time.h>
#include <windows.h>
#include <stdio.h>

typedef struct Frame{
    int th1;
    int th2;
    int th3;
    int s;
    int scor;
}fr;
typedef struct PLAYER{
    char nom[23];
    int score;
}player;

void gotoxy(int x, int y){
   HANDLE hConsoleOutput;
   COORD dwCursorPosition;
   dwCursorPosition.X = x;
   dwCursorPosition.Y = y;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);

}
void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
int getInput(char *c){
    if (kbhit())
    {
         *c = getch();
         return 1;
    }
	return 0;
}
void Color(int couleurDuTexte,int couleurDeFond){
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void Acceuil(char nom[23]){
    FILE *fi;
    char ch[101],key='?';
    int i=0;
    Color(15,0);
    fi=fopen("ASCII/Acceuil.txt","rt");
    gotoxy(0,0);
    while(!feof(fi))
    {
        fgets(ch,101,fi);
        printf("%s",ch);
    }
    fclose(fi);
    gotoxy(51,25);
    while(i==0){
        key='?';
        while (key != ' ')
        {
            while (!getInput(&key))
            {
            }
            if(key=='\b'){
                if(i==0){
                    printf("\a");
                }else{
                    i--;
                    nom[i]=' ';
                    gotoxy(51+i,25);
                    printf(" ");
                }
            }else{
                if(key!=' '){
                    if((i<22)&&(toupper(key)>64)&&(toupper(key)<91)){
                        nom[i]=key;
                        gotoxy(51+i,25);
                        printf("%c",key);
                        i++;
                    }
                    else{
                        printf("\a");
                    }
                }
            }
        }
        if(nom[0]==' ')
            i=0;
    }while(i==0);
    nom[i]='\0';
    system("cls");
}
void msg(char* cha){
    FILE *fi;
    int i=10;
    char ch[76],key = '?';
    Color(15,0);
    fi=fopen(cha,"rt");
    while(!feof(fi))
    {
        gotoxy(0,i);
        fgets(ch,76,fi);
        printf("%s",ch);
        i++;
    }
    fclose(fi);
    while (key != ' ')
	{
	    while (!getInput(&key))
		{i++;
		i--;}
	}
	Color(15,0);
	for(i=0;i<51;i++){
        gotoxy(70,i);
        printf(" ");
	}
}
void check(char t[4][4],int i,int j,int *th){
    if (t[i][j]=='O'){
        t[i][j]='X';
        (*th)++;
    }
}
void move_ball(int pas,int n,int pow,char t[4][4]){
    int x=84,y=44,h,f=0;
    switch (pas){
        case 0: h=50;
        break;
        case 1: h=8;
        break;
        case 2: h=5;
        break;
        case 3: h=2;
        break;
    }
    gotoxy(84,45);
    printf("(_)");
    while((y>1)&&(f==0)){
        if(y>5){
            gotoxy(71,y+1);
            printf("*| |                     | |*");
        }else{
            lane(t);
        }
        gotoxy(x,y);
        Color(13,0);
        printf("(_)");
        Color(15,0);
        if((x>95)||(x<73)){
            msg("ASCII/msg/Gutterball.txt");
            f=1;
        }
        if(((45-y)%h)==0)
            x+=n;
        y--;
        if(f==0)
            Sleep(110-4*pow);
    }
}
int pins_fall(char t[4][4],int aim,int pow){
    int th=0,power,part,n=0;
    if (aim!=0){
        n=aim/abs(aim);
    }
    if (pow < 3)
        power=0;
    else
        if (pow < 7)
            power=1;
        else
            if ((pow < 13)||(pow > 16))
                power=2;
            else
                power=3;
    gotoxy(15,30);
    if (abs(aim)<3)
        part=0;
    else
        if (abs(aim)<7)
            part=1;
        else
            if (abs(aim)<13)
                part=2;
            else
                part=3;
    if (power==0){
        gotoxy(84,45);
        printf("(_)");
        Sleep(100);
        gotoxy(71,45);
        printf("*| |                     | |*");
        gotoxy(84,44);
        printf("(_)");
        Sleep(200);
        gotoxy(71,44);
        printf("*| |                     | |*");
        gotoxy(84,43);
        printf("(_)");
        Sleep(500);
        msg("ASCII/msg/Deadball.txt");
    }else{
        move_ball(part,n,pow,t);
        if (part==0){
            if ((power==3)&&(t[3][0]=='O')){
                check(t,2,0,&th);
                check(t,2,1,&th);
                check(t,1,0,&th);
                check(t,1,2,&th);
                check(t,0,0,&th);
                check(t,0,1,&th);
                check(t,0,2,&th);
                check(t,0,3,&th);
            }
            if ((power==2)&&(t[3][0]=='O')){
                check(t,2,0,&th);
                check(t,2,1,&th);
                check(t,0,1,&th);
                check(t,0,2,&th);
            }
            check(t,3,0,&th);
            check(t,1,1,&th);
        }
        if(n==1){
            if (part==1){
                if ((t[2][1]=='O')||(t[1][2]=='O')){
                    check(t,2,1,&th);
                    check(t,1,2,&th);
                    check(t,0,2,&th);
                    if(power>1){
                        check(t,0,2,&th);
                        if (power>2){
                            check(t,0,3,&th);
                            check(t,1,1,&th);
                            check(t,3,0,&th);
                        }

                    }
                }
            }
            if (part==2){
                if(t[0][3]=='O'){
                    check(t,0,3,&th);
                    if(power>1){
                        if((power>2)&&(t[1][2]=='O')){
                            check(t,1,1,&th);
                            check(t,0,1,&th);
                        }
                        check(t,1,2,&th);
                        check(t,0,2,&th);
                    }

                }
            }
        }
        if(n==-1){
            if (part==1){
                if ((t[2][0]=='O')||(t[1][0]=='O')){
                    check(t,2,0,&th);
                    check(t,1,0,&th);
                    check(t,0,1,&th);
                    if(power>1){
                        check(t,0,1,&th);
                        if (power>2){
                            check(t,0,0,&th);
                            check(t,1,1,&th);
                            check(t,3,0,&th);
                        }

                    }
                }
            }
            if (part==2){
                if(t[0][0]=='O'){
                    check(t,0,0,&th);
                    if(power>1){
                        if((power>2)&&(t[1][0]=='O')){
                            check(t,1,1,&th);
                            check(t,0,2,&th);
                        }
                        check(t,1,0,&th);
                        check(t,0,1,&th);
                    }

                }
            }
        }
    }
    lane(t);
    Sleep(1000);
    for(n=0;n<4;n++){
        for(part=0;part<4;part++){
            if (t[n][part]=='X')
                t[n][part]=' ';
        }
    }
    lane(t);
    Sleep(1000);
    return th;
}
void cadre(){
    FILE *fi;
    int i=1;
    char ch[70];
    gotoxy(0,0);
    fi=fopen("ASCII/frame.txt","rt");
    while(!feof(fi))
    {
        Color(15,0);
        fgets(ch,70,fi);
        printf("%s",ch);
    }
    fclose(fi);
    gotoxy(0,0);
    fi=fopen("ASCII/title.txt","rt");
    while(!feof(fi))
    {
        Color(i,0);
        gotoxy(2,i);
        fgets(ch,70,fi);
        printf("%s",ch);
        if (i==15)
            i=1;
        else
            i++;
    }
    Color(15,0);
}
void score_table(){
    FILE *fi;
    int h=40;
    char ch[70];
    Color(15,0);
    fi=fopen("ASCII/score_Table.txt","rt");
    while(!feof(fi))
    {
        fgets(ch,70,fi);
        gotoxy(5,h);
        printf("%s",ch);
        h++;
    }
    fclose(fi);
    gotoxy(4,39);
    printf("Tableau des scores: ");
}
void init_pins(char p[4][4]){
    p[0][0]='O';
    p[0][1]='O';
    p[0][2]='O';
    p[0][3]='O';
    p[1][0]='O';
    p[1][1]='O';
    p[1][2]='O';
    p[1][3]=' ';
    p[2][0]='O';
    p[2][1]='O';
    p[2][2]=' ';
    p[2][3]=' ';
    p[3][0]='O';
    p[3][1]=' ';
    p[3][2]=' ';
    p[3][3]=' ';
}
void lane(char p[4][4]){
    FILE *fi;
    int h=0;
    char ch[70];
    fi=fopen("ASCII/lane.txt","rt");
    while(!feof(fi))
    {
        fgets(ch,70,fi);
        gotoxy(71,h);
        printf("%s",ch);
        h++;
    }
    fclose(fi);
    gotoxy(76,3);
    printf("%c     %c     %c     %c",p[0][0],p[0][1],p[0][2],p[0][3]);
    gotoxy(79,4);
    printf("%c     %c     %c",p[1][0],p[1][1],p[1][2]);
    gotoxy(82,5);
    printf("%c     %c",p[2][0],p[2][1]);
    gotoxy(85,6);
    printf("%c",p[3][0]);

}
void frame_num(char* i){
    FILE *fi;
    int h=11;
    char ch[70];
    fi=fopen(i,"rt");
    Color(12,0);
    while(!feof(fi))
    {
        fgets(ch,70,fi);
        gotoxy(5,h);
        printf("%s",ch);
        h++;
    }
    Color(15,0);
    fclose(fi);
}
void aim_interface(){
    FILE *fi;
    int h=18;
    char ch[27];
    fi=fopen("ASCII/aim.txt","rt");
    while(!feof(fi))
    {
        fgets(ch,27,fi);
        gotoxy(20,h);
        h++;
        printf("%s",ch);
    }
    fclose(fi);
    gotoxy(4,17);
    printf("Visez les Pins: (appuiyer sur \"Espace\")");
}
int aim_ball(){
    FILE *fi;
    int i=15,j=1,h;
    char key = '?',ch[50];
	while (key != ' ')
	{
        while (!getInput(&key))
		{
		    h=32;
            fi=fopen("ASCII/Ball_aim.txt","rt");
            while(!feof(fi))
            {
                Color(13,0);
                fgets(ch,11,fi);
                gotoxy(i,h);
                printf("%s\r",ch);
                h++;
            }
            i=i+j;
            if (i==43)
                j=-1;
            if (i==15)
                j=1;
            fclose(fi);
            Sleep(30);
		}
		Color(15,0);
	}
	Color(15,0);
	printf("\a");
    return i-29;//si la ball est au centre retourne 0
}
void jauge_c(int i){
    if((i-20)<3)
        Color(4,0);
    else{
        if((i-20)<7)
            Color(14,0);
        else
        {
            if(((i-20)<13)||((i-20)>15))
                Color(2,0);
            else
                Color(10,0);
        }
    }
}
int aim_power(){
    int i=32,j=1;
    char key = '?';
    gotoxy(4,31);
    printf("Puissance :");
    gotoxy(19,31);
    Color(4,0);
    printf("0(---");
    Color(14,0);
    printf("----");
    Color(2,0);
    printf("------");
    Color(10,0);
    printf("----");
    Color(2,0);
    printf("------)MAX");
	while (key != ' ')
	{
        while (!getInput(&key))
		{
		    gotoxy(i,31);
		    if (i==42){
                jauge_c(i-1);
                printf("-");
                jauge_c(i);
                printf("|");
                jauge_c(i+1);
                printf(")");
                j=-1;
		    }else {
		        if (i==20){
		            jauge_c(i-1);
                    printf("(");
                    jauge_c(i);
                    printf("|");
                    jauge_c(i+1);
                    printf("-");
                    j=1;
		        }else{
		            jauge_c(i-1);
                    printf("-");
                    jauge_c(i);
                    printf("|");
                    jauge_c(i+1);
                    printf("-");
		        }
		    }
            i=i+j;
            Sleep(30);
		}
	}
	Color(15,0);
	printf("\a");
    return i-20;
}
void aiming(int *aim,int *pow){
    aim_interface();
    *aim=aim_ball();
    *pow=aim_power();
}
void init_frames(fr t[10]){
    int i;
    for(i=0;i<10;i++){
        t[i].th1=-1;
        t[i].th2=-1;
        t[i].th3=-1;
        t[i].s=-1;
        t[i].scor=-1;
    }
}
void aff_score(fr t[10]){
    int i=0;
    while (i<10)
    {
        if (t[i].scor==(-1))
            break;
        gotoxy(7+i*6,43);
        printf("%3d",t[i].scor);
        i++;
    }
    i=0;
    while ((i<10))
    {
        if (t[i].th1==(-1))
            break;
        if (i!=9){
            if(strike(t[i].th1)){
                gotoxy(10+6*i,42);
                printf("X");
            }else{
                gotoxy(8+6*i,42);
                printf("%1d",t[i].th1);
                if (spare(t[i].th1,t[i].th2)){
                    gotoxy(10+6*i,42);
                    printf("/");
                }else{
                    gotoxy(10+6*i,42);
                    printf("%1d",t[i].th2);
                }
            }
            if (t[i].th1==0){
                gotoxy(8+6*i,42);
                printf("-");
            }
            if (t[i].th2==0){
                gotoxy(10+6*i,42);
                printf("-");
            }
        }else{
            if (strike(t[i].th1)){
                gotoxy(61,42);
                printf("X");
                if (strike(t[i].th2)){
                    gotoxy(63,42);
                    printf("X");
                    if (strike(t[i].th3)){
                        gotoxy(65,42);
                        printf("X");
                    }else{
                        gotoxy(65,42);
                        printf("%1d",t[i].th3);
                    }
                }
            }else{
                gotoxy(61,42);
                printf("%1d",t[i].th1);
                if (spare(t[i].th1,t[i].th2)){
                    gotoxy(63,42);
                    printf("/");
                    if (strike(t[i].th3)){
                        gotoxy(65,42);
                        printf("X");
                    }else{
                        gotoxy(65,42);
                        if (t[i].th3==0)
                            printf("-");
                        else
                            printf("%1d",t[i].th3);
                    }
                }else{
                    gotoxy(63,42);
                    printf("%1d",t[i].th2);
                    }
                }
        }

        i++;
    }
}
int game(){
    int aim,pow,i,sc=0;
    char pins[4][4];
    fr t[10];
    init_frames(t);
    for(i=0;i<10;i++){
        cadre();
        init_pins(pins);
        lane(pins);
        switch (i){
            case 0: frame_num("ASCII/Frames/1.txt");
            break;
            case 1: frame_num("ASCII/Frames/2.txt");
            break;
            case 2: frame_num("ASCII/Frames/3.txt");
            break;
            case 3: frame_num("ASCII/Frames/4.txt");
            break;
            case 4: frame_num("ASCII/Frames/5.txt");
            break;
            case 5: frame_num("ASCII/Frames/6.txt");
            break;
            case 6: frame_num("ASCII/Frames/7.txt");
            break;
            case 7: frame_num("ASCII/Frames/8.txt");
            break;
            case 8: frame_num("ASCII/Frames/9.txt");
            break;
            case 9: frame_num("ASCII/Frames/10.txt");
            break;
        }
        aiming(&aim,&pow);
        gotoxy(0,12);
        t[i].th1 = pins_fall(pins,aim,pow);
        if(i!=9){
            if (t[i].th1!=10)
            {
                cadre();
                switch (i){
                    case 0: frame_num("ASCII/Frames/1.txt");
                    break;
                    case 1: frame_num("ASCII/Frames/2.txt");
                    break;
                    case 2: frame_num("ASCII/Frames/3.txt");
                    break;
                    case 3: frame_num("ASCII/Frames/4.txt");
                    break;
                    case 4: frame_num("ASCII/Frames/5.txt");
                    break;
                    case 5: frame_num("ASCII/Frames/6.txt");
                    break;
                    case 6: frame_num("ASCII/Frames/7.txt");
                    break;
                    case 7: frame_num("ASCII/Frames/8.txt");
                    break;
                    case 8: frame_num("ASCII/Frames/9.txt");
                    break;
                    case 9: frame_num("ASCII/Frames/10.txt");
                    break;
                }
                aiming(&aim,&pow);
                gotoxy(0,12);
                t[i].th2 = pins_fall(pins,aim,pow);
                if (spare(t[i].th1,t[i].th2))
                    msg("ASCII/msg/spare.txt");
            }else {
                msg("ASCII/msg/strike.txt");
                t[i].th2=-1;
            }
        }else{
            if (strike(t[i].th1)){
                msg("ASCII/msg/strike.txt");
                init_pins(pins);
            }
            cadre();
            frame_num("ASCII/Frames/10.txt");
            lane(pins);
            aiming(&aim,&pow);
            gotoxy(0,12);
            t[i].th2 = pins_fall(pins,aim,pow);
            if (spare(t[i].th1,t[i].th2)){
                msg("ASCII/msg/spare.txt");
                init_pins(pins);
            }else{
                if (strike(t[i].th2)){
                    msg("ASCII/msg/spare.txt");
                    init_pins(pins);
                }
            }

            if (strike(t[i].th1)||(spare(t[i].th1,t[i].th2)))
            {
                cadre();
                frame_num("ASCII/Frames/10.txt");
                lane(pins);
                aiming(&aim,&pow);
                gotoxy(0,12);
                t[i].th3 = pins_fall(pins,aim,pow);
                if (strike(t[i].th3))
                    msg("ASCII/msg/strike.txt");
            }
        }
        score(t,i,sc);
        aff_score(t);
     }
     return t[9].scor;
}
int strike(int a){
    return a==10;
}
int spare(int a,int b){
    return a+b==10;
}
void score(fr t[],int i,int sc){
    int j;
    if(t[i].th1+t[i].th2 < 10)
        t[i].s=0;
    if(strike(t[i].th1))
     {
        if(i==9)
          t[i].s=3;
        else
          t[i].s=2;
     }
     if(spare(t[i].th1,t[i].th2))
     {
        if(i==9)
          t[i].s=4;
        else
         t[i].s=1;
     }
     for(j=0;j<i;j++)
       {
          //normale
            if(t[j].s==0)
             {
                t[j].scor=sc+t[j].th1+t[j].th2;
                sc=t[j].scor;
                if(t[j+1].s==3)
                    t[j+1].scor=t[j].scor+10+t[j+1].th3;
                if(t[j+1].s==4)
                    t[j+1].scor=t[j].scor+10+t[j+1].th3;
                if(t[j+1].s==0 &&j!=8)
                   t[j+1].scor=t[j].scor+t[j+1].th1+t[j+1].th2;
                if(t[j+1].s==0 &&j==8)
                   t[j+1].scor=t[j].scor+t[j+1].th1+t[j+1].th2+t[j+1].th3;
             }

             //strike
             if(strike(t[j].th1))
                {
                    if(t[j+1].s==0){
                        t[j].scor=sc+10+t[j+1].th1+t[j+1].th2;
                        sc=t[j].scor;
                        if(j!=8)
                            t[j+1].scor=t[j].scor+t[j+1].th1+t[j+1].th2;
                        else
                            t[j+1].scor=t[j].scor+t[j+1].th1+t[j+1].th2+t[j+1].th3;
                    }
                    if(t[j+1].s==1)
                       t[j].scor=sc+10+t[j+1].th1+t[j+1].th2;
                    if(t[j+1].s==2 && j<i-1)
                       t[j].scor=sc+20+t[j+2].th1;

                    if(t[j+1].s==3)
                      {
                        t[j].scor=sc+20+t[j+1].th3;

                        t[j+1].scor=t[j].scor+20+t[j+1].th3;
                      }
                    if(t[j+1].s==4)
                        {
                            t[j].scor=sc+20;

                            t[j+1].scor=t[j].scor+10+t[j+1].th3;

                        }
                    if((t[j+1].s==0)&&(j==8)) {
                        t[j].scor=sc+10+t[j+1].th1+t[j+1].th2;

                        t[j+1].scor=t[j].scor+t[j+1].th1+t[j+1].th2+t[j+1].th3;

                        }
                    sc=t[j].scor;
                 }

        //spare
             if(spare(t[j].th1,t[j].th2))
                {
                    t[j].scor=sc+10+t[j+1].th1;
                    sc=t[j].scor;
                    if(t[j+1].s==0){
                        if(j!=8)
                            t[j+1].scor=t[j].scor+t[j+1].th1+t[j+1].th2;
                        else
                            t[j+1].scor=t[j].scor+t[j+1].th1+t[j+1].th2+t[j+1].th3;
                     }
                    if(t[j+1].s==3)
                        t[j+1].scor=sc+20+t[j+1].th3;
                    if(t[j+1].s==4)
                        t[j+1].scor=sc+10+t[j+1].th3;


                }

       }
       if (t[i].s==0){
            if(i!=8)
                t[i].scor=sc+t[i].th1+t[i].th2;
            else
                t[i].scor=sc+t[i].th1+t[i].th2+t[i].th3;
       }
}
void updatefile(player p){
    int i=0,j;
    player t[10];
    FILE *fi;
    fi=fopen("ASCII/topscore","rb");
    fread(t,sizeof(player),10,fi);
    fclose(fi);
    while((i<10)&&(t[i].score>p.score)){
        i++;
    }
    if(i!=10){
        for(j=i;j<9;j++){
            t[j+1]=t[j];
        }
        t[i]=p;
    }
    fi=fopen("ASCII/topscore","wb");
    fwrite(t,sizeof(player),10,fi);
    fclose(fi);
}
void fin(player p){
    int i=0;
    player t[10];
    char ch[101],key='?';
    FILE *fi;
    fi=fopen("ASCII/final_Score.txt","rt");
    gotoxy(0,0);
    while(!feof(fi)){
        fgets(ch,101,fi);
        printf("%s",ch);
    }


    fi=fopen("ASCII/topscore","rb");
    fread(t,sizeof(player),10,fi);
    fclose(fi);
    gotoxy(54,15);
    printf("%3d",p.score);
    for(i=0;i<10;i++){
        gotoxy(35,27+i);
        printf("%2d - %3d  %s",i+1,t[i].score,t[i].nom);
    }
    while (key != ' ')
	{
	    while (!getInput(&key))
		{i++;
		i--;}
	}
}




void main()
{
    FILE *fi;
    int aim,pow;
    char pins[4][4];
    player p;
    system ("MODE   CON        COLS=101            LINES=50");
    hidecursor();
    Acceuil(&(p.nom));
    score_table();
    gotoxy(10,49);
    p.score=game();
    updatefile(p);
    fin(p);
    gotoxy(15,45);
}
