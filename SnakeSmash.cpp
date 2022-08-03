#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"SnakeSmash.h"
#include<graphics.h>
#include<windows.h>


void init(snake *S,int l,char sco[20]){
    node *s;
    s=(node*)malloc(sizeof(node));
    if(!s)
        return;
    s->sloc.x[0]=260;
    s->sloc.y[0]=760;
    s->dir=3;
    strcpy(s->score,sco);
    *S=s;
    (*S)->length = l;
    return;
}


void init2(snake *S,int l,char sco[20]){
    node *s;
    s=(node*)malloc(sizeof(node));
    if(!s)
        return;
    s->sloc.x[0]=860;
    s->sloc.y[0]=760;
    s->dir=3;
    strcpy(s->score,sco);
    *S=s;
    (*S)->length = l;
    return;
}


int  drawborder(char *file1,char *file2){
    initwindow(600,800);
    setfillstyle(1,2);
    bar(0,0,50,800);
    bar(0,0,600,50);
    bar(0,750,600,800);
    bar(550,0,600,800);
    settextstyle(10,HORIZ_DIR,6);
    outtextxy(120,150,"SNAKE SMASH"); //heading of game

    //drawing a border for the text
    for(int i = 0;i<2;i++){
            if(i==0)
                    for(int j = 300 ; j<500 ;j+=20){
                        setfillstyle(1,12);
                        circle(125,j,10);
                        floodfill(125,j,WHITE);
                    }
            else if(i==1)
                    for(int j = 300 ; j<500 ;j+=20){
                        setfillstyle(1,12);
                        circle(465,j,10);
                        floodfill(465,j,WHITE);
                    }

    }
    for(int i = 0;i<2;i++){
            if(i==0)
                    for(int j = 125 ; j<475 ;j+=20){
                        setfillstyle(1,12);
                        circle(j,300,10);
                        floodfill(j,300,WHITE);
                    }
            else if(i==1)
                    for(int j = 125 ; j<475 ;j+=20){
                        setfillstyle(1,12);
                        circle(j,500,10);
                        floodfill(j,500,WHITE);
                    }

    }

    //selection of single or double player
    setfillstyle(1,15);
    bar(190,342,392,346);
    bar(190,345,194,378);
    bar(388,345,392,378);
    bar(190,378,392,382);
    setbkcolor(0);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(200,350,"Single Player");
    bar(190,424,392,427);
    bar(190,425,194,458);
    bar(388,425,392,458);
    bar(190,458,392,462);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(200,430,"Double Player");
    int m=0;
    int n=0;
    int go=0;
    while(1){
        if(ismouseclick(WM_LBUTTONUP)){
            getmouseclick(WM_LBUTTONUP,m,n);
            if(200<=m && m<=390 && 350<=n && n<=370){
                go=0;
                break;
            }
            else if(200<=m && m<=390 && 430<=n && n<=460){
                go=1;
                break;
            }
        }
    }

    //play button
    setfillstyle(1,0);
    bar(180,340,400,470);
    setfillstyle(1,15);
    bar(254,444,322,447);
    bar(254,445,258,478);
    bar(318,445,322,478);
    bar(254,478,322,482);
    setbkcolor(0);
    settextstyle(10,HORIZ_DIR,3);
    outtextxy(260,450,"Play");
    settextstyle(10,HORIZ_DIR,2);

    //if single player
    if(go == 0){
            outtextxy(140,350,"Enter name: ");
            char name[20];
            scanf("%s",name);
            outtextxy(280,350,name);
            FILE *fp=fopen(file1,"a");//writing name of player into c.txt file
            fprintf(fp,"%s ",name);
            fclose(fp);
    }
    //if double player
    else if(go == 1){
        outtextxy(140,350,"Player1 name: ");
        outtextxy(140,400,"Player2 name: ");
        char player1[30];
        char player2[30];
        scanf("%s",player1);
        scanf("%s",player2);
        outtextxy(300,350,player1);
        outtextxy(300,400,player2);
        FILE *fp=fopen(file2,"w");//writing names of players for further use int b.txt file
        fprintf(fp,"%s_Wins!\n%s_Wins!",player1,player2);
        fclose(fp);
    }

    //wait until Play button is pressed
    while(1){
        if(ismouseclick(WM_LBUTTONUP)){
            getmouseclick(WM_LBUTTONUP,m,n);
            if(260<=m && m<=320 && 450<=n && n<=470)
                break;
        }
    }

    if(go==0){
          //making screen blank and again drawing border
          setfillstyle(1,0);
          bar(0,0,600,800);
          setfillstyle(1,2);
          bar(0,0,50,800);
          bar(550,0,600,800);
          bar(0,760,600,800);
          setbkcolor(0);
          settextstyle(10,HORIZ_DIR,1);
          outtextxy(400,20,"Score:"); // displaying score board
          outtextxy(490,20,"0000");
    }
    //if double player is selected then close previous window and then initialize a wider window for 2 players and divide into two
    else if(go==1){
        closegraph();
        initwindow(1200,1600);
        setfillstyle(1,0);
        bar(0,0,1200,800);
        setfillstyle(1,2);
        bar(0,0,50,800);
        bar(550,0,600,800);
        bar(0,760,1200,800);
        bar(600,0,650,800);
        bar(1150,0,1200,800);

        //displaying scoreboard for players
        setbkcolor(0);
        settextstyle(10,HORIZ_DIR,1);
        outtextxy(400,20,"Player1:");
        outtextxy(490,20,"0000");
        outtextxy(1000,20,"Player2:");
        outtextxy(1090,20,"0000");
    }
    //returning if user choose single or double player and work accordingly
    return go;
}


void drawsnake(snake *S,int d,int l,int go){
    node *s;
    s=*S;

    switch(d){

        case 1:
            s->sloc.x[0]=s->sloc.x[0]+20;
            s->dir=3;
            break;

        case 2:
            s->sloc.x[0]=s->sloc.x[0]-20;
            s->dir=3;
            break;

        case 3:
            s->sloc.y[0]=s->sloc.y[0]-20;
            s->dir=3;
            break;

        default:
            break;
        }

        //displaying snake in group of circle of size of length of snake
        for(int i=0;i<=(*S)->length-1;i++){
                setfillstyle(SOLID_FILL,9);
                circle(s->sloc.x[i],s->sloc.y[i],10);
                floodfill(s->sloc.x[i],s->sloc.y[i],WHITE);
                setfillstyle(1,2);
                bar(0,0,50,800);
                bar(550,0,600,800);
                bar(0,760,600,800);
                setbkcolor(0);
                settextstyle(10,HORIZ_DIR,1);

                //for double player display both scoreboards
                if(go == 1){
                    bar(0,760,1200,800);
                    bar(600,0,650,800);
                    bar(1150,0,1200,800);
                    if(650<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=1150){
                    outtextxy(1000,20,"Player2:");
                    outtextxy(1090,20,(*S)->score);
                    }
                    else if(50<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=550){
                        outtextxy(400,20,"Player1:");
                        outtextxy(490,20,(*S)->score);
                    }
                }
                //for single player display one scoreboard
                else{
                        outtextxy(400,20,"Score:");
                        outtextxy(490,20,(*S)->score);
                }
        }


        //moving snake from bottom to top
        for(int i=599,j=599 ; i>0,j>0 ;i--,j--){
            //to pause the game press ctrl to resume press NUMPAS0
            if(GetAsyncKeyState(VK_CONTROL)){
               while(1){
                if(GetAsyncKeyState(VK_NUMPAD0))
                    break;
               }
            }
            s->sloc.x[i] = s->sloc.x[i-1];
            s->sloc.y[j] = s->sloc.y[j-1];
        }

        setfillstyle(1,0);
        if(go==1)
            delay(20);
        else
            delay(100);
        //making the previous part of the snake as it moves to maintain the display of snake as it is
        bar(s->sloc.x[s->length]-10,s->sloc.y[s->length]-10,s->sloc.x[s->length]+10,s->sloc.y[s->length]+10);
        return;

}


void initblock(block *B){
    B->b=(box*)calloc(sizeof(box),10);
    B->size=0;
    return;
}

void initfood(eat *F){
    F->f=(box*)calloc(sizeof(box),5);
    F->size=0;
    return;
}


void addblock(block *B,int w,int m,int n){
    box *nn=(box*)malloc(sizeof(box));
    nn->x = m;
    nn->y = n;
    nn->weight = w;
    nn->next = NULL;

    box *p = B->b;
    while(p->next){
        p=p->next;
    }
    p->next=nn;

    B->size++;
    return;
}

void addfood(eat *F,int w,int m,int n){
    box *nn=(box*)malloc(sizeof(box));
    nn->x = m;
    nn->y = n;
    nn->weight = w;
    nn->next = NULL;

    box *p = F->f;
    while(p->next)
        p=p->next;
    p->next=nn;

    F->size++;
    return;
}

void addingblock(block *B,int c){

    switch(c){
        case 0:{
            addblock(B,4,120,520);
            addblock(B,4,180,440);
            addblock(B,5,240,360);
            addblock(B,3,300,280);
            addblock(B,6,360,200);
            addblock(B,1,420,500);
            addblock(B,2,340,500);
            addblock(B,5,140,200);
            addblock(B,3,202,200);
            addblock(B,4,400,100);
            break;
        }
        case 1:{
            addblock(B,4,320,500);
            addblock(B,4,240,440);
            addblock(B,5,160,380);
            addblock(B,3,80,320);
            addblock(B,6,160,260);
            addblock(B,1,400,600);
            addblock(B,2,340,200);
            addblock(B,5,440,140);
            addblock(B,3,100,140);
            break;
        }
        case 2:{
            addblock(B,4,340,400);
            addblock(B,4,278,400);
            addblock(B,5,216,400);
            addblock(B,3,154,400);
            addblock(B,6,92,400);
            addblock(B,1,420,400);
            addblock(B,2,340,200);
            addblock(B,5,440,140);
            addblock(B,3,100,140);
            addblock(B,3,160,540);
            break;
        }
    }
        return;
    }


void addingfood(eat *F,int c){
    switch(c){
        case 0:addfood(F,2,200,500);
               addfood(F,3,400,300);
               addfood(F,5,70,300);
               addfood(F,1,200,300);
               addfood(F,4,300,100);
               break;
        case 1:addfood(F,2,200,500);
               addfood(F,3,90,400);
               addfood(F,5,100,200);
               addfood(F,1,400,300);
               addfood(F,4,450,450);
               break;
        case 2:addfood(F,4,150,470);
               addfood(F,1,450,300);
               addfood(F,5,70,300);
               addfood(F,3,200,80);
               addfood(F,2,400,550);
               break;
    }



        return;
    }

//for second player
void addingblock2(block *B,int c){

    switch(c){
        case 0:{
            addblock(B,4,720,520);
            addblock(B,4,780,440);
            addblock(B,5,840,360);
            addblock(B,3,900,280);
            addblock(B,6,960,200);
            addblock(B,1,1020,500);
            addblock(B,2,940,500);
            addblock(B,5,740,200);
            addblock(B,3,802,200);
            addblock(B,4,1000,100);
            break;
        }
        case 1:{
            addblock(B,4,920,500);
            addblock(B,4,840,440);
            addblock(B,5,760,380);
            addblock(B,3,680,320);
            addblock(B,6,760,260);
            addblock(B,1,1000,600);
            addblock(B,2,940,200);
            addblock(B,5,1040,140);
            addblock(B,3,700,140);
            break;
        }
        case 2:{
            addblock(B,4,940,400);
            addblock(B,4,878,400);
            addblock(B,5,816,400);
            addblock(B,3,754,400);
            addblock(B,6,692,400);
            addblock(B,1,1020,400);
            addblock(B,2,940,200);
            addblock(B,5,1040,140);
            addblock(B,3,700,140);
            addblock(B,3,760,540);
            break;
        }
    }
        return;
    }


void addingfood2(eat *F,int c){
    switch(c){
        case 0:addfood(F,2,800,500);
               addfood(F,3,1000,300);
               addfood(F,5,670,300);
               addfood(F,1,800,300);
               addfood(F,4,900,100);
               break;
        case 1:addfood(F,2,800,500);
               addfood(F,3,690,400);
               addfood(F,5,700,200);
               addfood(F,1,1000,300);
               addfood(F,4,1050,450);
               break;
        case 2:addfood(F,4,750,470);
               addfood(F,1,1050,300);
               addfood(F,5,670,300);
               addfood(F,3,1000,80);
               addfood(F,2,1000,550);
               break;
    }
        return;
}




void displayblock(block B){

    setfillstyle(1,12);
    box *p;
    p=B.b;
    settextstyle(1,HORIZ_DIR,3);
    setbkcolor(12);
    for(int i=0;i<=B.size;i++){
        bar(p->x-30,p->y-30,p->x+30,p->y+30);
        switch(p->weight){
            case 1:outtextxy(p->x-10,p->y-8,"1");
                    break;
            case 2:outtextxy(p->x-10,p->y-8,"2");
                   break;
            case 3:outtextxy(p->x-10,p->y-8,"3");
                   break;
            case 4:outtextxy(p->x-10,p->y-8,"4");
                    break;
            case 5:outtextxy(p->x-10,p->y-8,"5");
                    break;
            case 6:outtextxy(p->x-10,p->y-8,"6");
                   break;
        }
        p=p->next;
    }
    return;
}


void displayfood(eat F){
    setfillstyle(SOLID_FILL,5);
    box *p;
    p=F.f;
    settextstyle(1,HORIZ_DIR,1);
    setbkcolor(5);
    for(int i=0;i<=F.size;i++){
        circle(p->x,p->y,15);
        floodfill(p->x,p->y,WHITE);
        switch(p->weight){
            case 1:outtextxy(p->x-8,p->y-10,"1");
                    break;
            case 2:outtextxy(p->x-8,p->y-10,"2");
                   break;
            case 3:outtextxy(p->x-8,p->y-10,"3");
                   break;
            case 4:outtextxy(p->x-8,p->y-10,"4");
                    break;
            case 5:outtextxy(p->x-8,p->y-10,"5");
                    break;
            case 6:outtextxy(p->x-8,p->y-10,"6");
                   break;
        }
        p=p->next;
    }
    return;
}


void deletefood(eat *F){
    F->f=NULL;
    F->size=0;
    return;
}

void deleteblock(block *B){
    B->b = NULL;
    B->size = 0;
    return;
}



void checkfood(snake *S,eat *F){
    box *p;
    p = F->f;
    for(int i = 0;i<=F->size;i++){
            //if snake encounters food
        if((p->x-20 <= (*S)->sloc.x[0] && (*S)->sloc.x[0] <= p->x+20) && (p->y-20 <= (*S)->sloc.y[0] && (*S)->sloc.y[0]-10 <= p->y+20)){
            (*S)->length += p->weight;
            setfillstyle(SOLID_FILL,BLACK);
            bar(p->x-15,p->y-15,p->x+15,p->y+15);
            p->x = 0;
            p->y = 0;
        }
        p = p->next;
    }

}


int checkblock(snake *S,block *B){

    box *p;
    p = B->b;
    for(int i = 0;i<=B->size;i++){
        setfillstyle(1,0);
        if((p->x-30<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=p->x+30) && (*S)->sloc.y[0]-10 == p->y+30){
            //if snake encounters block
            int w = p->weight;
            for(int j = (*S)->length-1 ; j>=(*S)->length - p->weight ; j--){
                if((*S)->length <= 0){
                    return 0;
                 }
                p->weight--;
                settextstyle(1,HORIZ_DIR,3);
                setbkcolor(12);
                switch(p->weight){
                    case 1:outtextxy(p->x-8,p->y-10,"1");
                            break;
                    case 2:outtextxy(p->x-8,p->y-10,"2");
                            break;
                    case 3:outtextxy(p->x-8,p->y-10,"3");
                            break;
                    case 4:outtextxy(p->x-8,p->y-10,"4");
                            break;
                    case 5:outtextxy(p->x-8,p->y-10,"5");
                            break;
                    case 6:outtextxy(p->x-8,p->y-10,"6");
                            break;
                }

                int g = 0;
                int h = 0;
                int no=0;
                char c = (*S)->score[g];
                if(c!='\0'){
                    no=0;
                    while(c!='\0'){
                            no=no*10+(int)(c)-'0';
                            ++g;
                            h++;
                            c=(*S)->score[g];
                    }
                }
                no++;
                (*S)->length--;
                int m;
                for(g = h-1;g>0;g--){
                        m = no%10;
                        no=no/10;
                        (*S)->score[g]=char(m)+'0';
                }


                setbkcolor(0);
                settextstyle(10,HORIZ_DIR,2);
                if(50<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=550)
                    outtextxy(490,20,(*S)->score);
                else
                    outtextxy(1090,20,(*S)->score);

                bar((*S)->sloc.x[(*S)->length]-10,(*S)->sloc.y[(*S)->length]-10,(*S)->sloc.x[(*S)->length]+10,(*S)->sloc.y[(*S)->length]+10);

                if(p->weight>1)
                    delay(50);

                //if in between snake moves away from block
                if(GetAsyncKeyState(VK_RIGHT) && 50<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=550)//for player1
                    return 1;
                else if(GetAsyncKeyState(VK_LEFT) && 50<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=550)
                    return 2;

                if(GetAsyncKeyState(VK_NUMPAD4) && 650<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=1150)//for player2
                    return 1;
                else if(GetAsyncKeyState(VK_NUMPAD6) && 650<=(*S)->sloc.x[0] && (*S)->sloc.x[0]<=1150)
                    return 2;

            }

            //remove block if its weight becomes zero
            setfillstyle(1,0);
            bar(p->x-30,p->y-30,p->x+30,p->y+30);
            p->x = 0;
            p->y = 0;
        }
        //you cannot encounter block from any other side only can from bottom else move up
        else if((*S)->sloc.y[0]>=p->y-30 && (*S)->sloc.y[0]<=p->y+30 && p->x-30<=(*S)->sloc.x[0]+10 && (*S)->sloc.x[0]-10<=p->x+40)
                return 3;
        p = p->next;
    }
    return 0;
}

//display score of player or players when game finishes
void finish(char *score,int h,int go){
    if(go==0){
    setfillstyle(1,0);
    bar(0,0,600,800);
    setfillstyle(1,2);
    bar(0,0,50,800);
    bar(0,0,600,50);
    bar(0,750,600,800);
    bar(550,0,600,800);
    setbkcolor(0);
    settextstyle(10,HORIZ_DIR,6);
        outtextxy(120,150,"GAME OVER!");
    }
    else{
    setfillstyle(1,0);
    bar(0+h,0,600+h,800);
    setfillstyle(1,2);
    bar(0+h,0,50+h,800);
    bar(0+h,0,600+h,50);
    bar(0+h,750,600+h,800);
    bar(550+h,0,600+h,800);
    }

    for(int i = 0;i<2;i++){
            if(i==0)
                    for(int j = 300 ; j<500 ;j+=20){
                        setfillstyle(1,12);
                        circle(125+h,j,10);
                        floodfill(125+h,j,WHITE);
                    }
            else if(i==1)
                    for(int j = 300 ; j<500 ;j+=20){
                        setfillstyle(1,12);
                        circle(465+h,j,10);
                        floodfill(465+h,j,WHITE);
                    }

    }
    for(int i = 0;i<2;i++){
            if(i==0)
                    for(int j = 125 ; j<475 ;j+=20){
                        setfillstyle(1,12);
                        circle(j+h,300,10);
                        floodfill(j+h,300,WHITE);
                    }
            else if(i==1)
                    for(int j = 125 ; j<475 ;j+=20){
                        setfillstyle(1,12);
                        circle(j+h,500,10);
                        floodfill(j+h,500,WHITE);
                    }

    }
    setbkcolor(0);
    settextstyle(10,HORIZ_DIR,2);
    outtextxy(140+h,350,"Your Score: ");
    outtextxy(300+h,350,score);
    settextstyle(10,HORIZ_DIR,3);
    if(go==0){
    outtextxy(260,450,"Exit");
    setfillstyle(1,15);
    bar(254,444,322,447);
    bar(254,445,258,478);
    bar(318,445,322,478);
    bar(254,478,322,482);

    int m=0;
    int n=0;
    while(1){
        if(ismouseclick(WM_LBUTTONUP)){
            getmouseclick(WM_LBUTTONUP,m,n);
            if(260<=m && m<=320 && 450<=n && n<=470)
                break;
        }
    }
    }

    return;

}

//displaying winner in case of multiplayer
void finish2(char *name){
    setfillstyle(1,0);
    bar(0,0,1200,800);
    setfillstyle(1,2);
    bar(0,0,50,800);
    bar(0,0,1200,50);
    bar(0,750,1200,800);
    bar(1150,0,1200,800);
    setbkcolor(0);
    settextstyle(10,HORIZ_DIR,6);
    outtextxy(440,350,name);
    for(int i = 0;i<2;i++){
            if(i==0)
                    for(int j = 300 ; j<500 ;j+=20){
                        setfillstyle(1,12);
                        circle(125,j,10);
                        floodfill(125,j,WHITE);
                    }
            else if(i==1)
                    for(int j = 300 ; j<500 ;j+=20){
                        setfillstyle(1,12);
                        circle(1065,j,10);
                        floodfill(1065,j,WHITE);
                    }

    }
    for(int i = 0;i<2;i++){
            if(i==0)
                    for(int j = 125 ; j<1075 ;j+=20){
                        setfillstyle(1,12);
                        circle(j,300,10);
                        floodfill(j,300,WHITE);
                    }
            else if(i==1)
                    for(int j = 125 ; j<1075 ;j+=20){
                        setfillstyle(1,12);
                        circle(j,500,10);
                        floodfill(j,500,WHITE);
                    }

    }
    settextstyle(10,HORIZ_DIR,3);
    setfillstyle(1,15);
    bar(554,444,622,447);
    bar(554,445,558,478);
    bar(618,445,622,478);
    bar(554,478,622,482);

    outtextxy(560,450,"Exit");

    int m=0;
    int n=0;
    while(1){
        if(ismouseclick(WM_LBUTTONUP)){
            getmouseclick(WM_LBUTTONUP,m,n);
            if(560<=m && m<=620 && 450<=n && n<=470)
                break;
        }
    }

        return;

}
