#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include "SnakeSmash.h"

int main(int argc,char *argv[])
{
    int d = 3;
    int d1 = 3;
    int d2 = 3;
    int go;
    go = drawborder(argv[1],argv[2]); //initialization of window
    int k=0;
    int n = 0;
    int m = 0;


   switch(go){
       case 0:{
           char *score = (char*)malloc(sizeof(char)*20);
           score="0000";

           snake S;
           init(&S,10,score);
           int l = S->length;

           int cas = 0;

           eat F;               //food for snake
           initfood(&F);
           addingfood(&F,cas);
           displayfood(F);

           block B;             //block
           initblock(&B);
           addingblock(&B,cas);
           displayblock(B);

           while(1){

                if(k==0)
                        init(&S,l,score);


                //if left or right key is encountered move snake accordingly

                if(GetAsyncKeyState(VK_RIGHT) && S->sloc.x[0]<=530)
                    d=1;

                else if(GetAsyncKeyState(VK_LEFT) && S->sloc.x[0]>=80)
                    d=2;

                else//move up
                    d=3;


                //if length of snake becomes zero end game

                if(S->length==0){
                        finish(S->score,0,0);
                        FILE *fp=fopen(argv[1],"a"); //storing score of players in c.txt file
                        fprintf(fp,"%s\n",S->score);
                        fclose(fp);
                        break;
                }

                checkfood(&S,&F);        //if snake encounters food length increases by weight of food
                int x=checkblock(&S,&B); //if snake encounters block length decreases by weight of block
                if(!x)
                    drawsnake(&S,d,l,go);
                else
                    drawsnake(&S,x,l,go);


                k++;
                if(S->sloc.y[0]<=0 ){     //if snake moves out of the window start the snake again from bottom
                        score = S->score;
                        l = S->length;
                        setfillstyle(1,0);
                        bar(0,0,600,800);
                        deleteblock(&B);
                        deletefood(&F);

                        initblock(&B);   //initialize block and food again for next case
                        initfood(&F);
                        if(cas == 0){
                                addingblock(&B,1);
                                addingfood(&F,1);
                                cas++;
                        }

                        else if(cas == 1){
                                addingblock(&B,2);
                                addingfood(&F,2);
                                cas++;
                        }
                        else if(cas == 2){
                            cas = 0;
                            addingblock(&B,0);
                            addingfood(&F,0);
                        }
                        delay(100);
                        displayfood(F);
                        displayblock(B);
                        k=0;
                }

                if(GetAsyncKeyState(VK_ESCAPE)){
                        finish(S->score,0,0);
                        FILE *fp=fopen(argv[1],"a");//end game if esc key is pressed
                        fprintf(fp,"%s\n",S->score);
                        fclose(fp);
                        break;
                }
           }
           break;
       }


       case 1:{//case for two players
           char *player1 = (char*)malloc(sizeof(char)*30);
           player1="0000";
           char *player2 = (char*)malloc(sizeof(char)*30);
           player2="0000";
           snake S1;
           init(&S1,10,player1);
           snake S2;
           init2(&S2,10,player2);
           int l1 = S1->length;
           int l2 = S2->length;

           int cas = 0;

           //initialize block and food for both snakes in their parts
           eat F1;
           eat F2;
           initfood(&F1);
           initfood(&F2);
           addingfood(&F1,cas);
           addingfood2(&F2,cas);
           displayfood(F1);
           displayfood(F2);

           block B1;
           block B2;
           initblock(&B1);
           initblock(&B2);
           addingblock(&B1,cas);
           addingblock2(&B2,cas);
           displayblock(B1);
           displayblock(B2);
           while(1){


                if(k==0){
                        if(S1->length>0)
                             init(&S1,l1,player1);
                        if(S2->length>0)
                             init2(&S2,l2,player2);
                }


                //move left or right according to the key pressed
                // <(left >(right) for player1
                // 4(left) 6(right) for player2
                if(S1->length>0){
                        if(GetAsyncKeyState(VK_RIGHT) && S1->sloc.x[0]<=530)
                             d1=1;

                        else if(GetAsyncKeyState(VK_LEFT) && S1->sloc.x[0]>=80)
                             d1=2;

                        else
                             d1=3;
                }

                if(S2->length>0){
                        if(GetAsyncKeyState(VK_NUMPAD6) && S2->sloc.x[0]<=1130)
                             d2=1;

                        else if(GetAsyncKeyState(VK_NUMPAD4) && S2->sloc.x[0]>=680)
                             d2=2;

                        else
                             d2=3;
                }


                //if player1 snake's length becomes 0 then finish game for player1 and wait for player2 to complete
                if(S1->length<=0 && !m){
                        finish(S1->score,0,1);
                        if(n)
                            delay(1000);
                        m++;
                }


                //if player2 snake's length becomes 0 then finish game for player2 and wait for player1 to complete
                if(S2->length<=0 && !n){
                        finish(S2->score,600,1);
                        if(m)
                            delay(1000);
                        n++;
                }

                //if both snake's length becomes zero the finish game and declare winner
                if(S1->length<=0 && S2->length<=0){
                        k = strcmp(S1->score,S2->score);
                        char p1[30];
                        char p2[30];
                        FILE *fp=fopen(argv[2],"r+");
                        fscanf(fp,"%s",p1);
                        fscanf(fp,"%s",p2);
                        fclose(fp);
                        if(k>0)
                           finish2(p1);
                        else if(k<0)
                            finish2(p2);
                        else
                            finish2("   DRAW!");
                        break;
                }

                //checking if snakes of the players have encountered block or food
                if(S1->length>0){
                    checkfood(&S1,&F1);
                    int x=checkblock(&S1,&B1);
                    if(!x)
                       drawsnake(&S1,d1,l1,go);
                    else
                       drawsnake(&S1,x,l1,go);
                }

                if(S2->length>0){
                    checkfood(&S2,&F2);
                    int y=checkblock(&S2,&B2);
                    if(!y)
                      drawsnake(&S2,d2,l2,go);
                    else
                      drawsnake(&S2,y,l2,go);
                }

                if(S2->length<=0 || S1->length<=0)
                    delay(60);



                k++;

                //both the snakes move out of window then again start the snakes from bottom

                if((S1->sloc.y[0]<=0 && S2->length<=0) || (S1->length<=0 && S2->sloc.y[0]<=0) || (S1->sloc.y[0]<=0 && S2->sloc.y[0]<=0)){
                        setfillstyle(1,0);
                        if(S1->length>0 && S2->length<=0){
                              player1 = S1->score;
                              l1 = S1->length;
                              bar(0,0,600,800);
                              deleteblock(&B1);
                              deletefood(&F1);
                              initblock(&B1);
                              initfood(&F1);
                              if(cas == 0){
                                addingblock(&B1,1);
                                addingfood(&F1,1);
                                cas++;
                              }

                              else if(cas == 1){
                                addingblock(&B1,2);
                                addingfood(&F1,2);
                                cas++;
                              }
                              else if(cas == 2){
                                cas = 0;
                                addingblock(&B1,0);
                                addingfood(&F1,0);
                              }
                              delay(50);
                              displayfood(F1);
                              displayblock(B1);
                              k=0;
                        }
                        if(S2->length>0 && S1->length<=0){
                              player2 = S2->score;
                              l2 = S2->length;
                              bar(600,0,1200,800);
                              deleteblock(&B2);
                              deletefood(&F2);
                              initblock(&B2);
                              initfood(&F2);
                              if(cas == 0){
                                addingblock2(&B2,1);
                                addingfood2(&F2,1);
                                cas++;
                              }

                              else if(cas == 1){
                                addingblock2(&B2,2);
                                addingfood2(&F2,2);
                                cas++;
                              }
                              else if(cas == 2){
                                cas = 0;
                                addingblock2(&B2,0);
                                addingfood2(&F2,0);
                              }
                              delay(50);
                              displayfood(F2);
                              displayblock(B2);
                              k=0;
                        }
                        if(S1->length>0 && S2->length>0){
                              player1 = S1->score;
                              player2 = S2->score;
                              bar(0,0,1200,800);
                              l2 = S2->length;
                              l1 = S1->length;

                              deleteblock(&B1);
                              deleteblock(&B2);
                              deletefood(&F2);
                              deletefood(&F1);

                              initblock(&B2);
                              initblock(&B1);
                              initfood(&F2);
                              initfood(&F1);
                              if(cas == 0){
                                 addingblock(&B1,1);
                                 addingblock2(&B2,1);
                                 addingfood(&F1,1);
                                 addingfood2(&F2,1);
                                 cas++;
                              }

                              else if(cas == 1){
                                 addingblock(&B1,2);
                                 addingblock2(&B2,2);
                                 addingfood(&F1,2);
                                 addingfood2(&F2,2);
                                 cas++;
                              }

                              else if(cas == 2){
                                 cas = 0;
                                 addingblock(&B1,0);
                                 addingblock2(&B2,0);
                                 addingfood(&F1,0);
                                 addingfood2(&F2,0);
                              }
                              delay(50);
                              displayfood(F1);
                              displayfood(F2);
                              displayblock(B1);
                              displayblock(B2);
                              k=0;
                      }
                }

                //finish game if esc key is pressed and declare winner
                if(GetAsyncKeyState(VK_ESCAPE)){
                        k = strcmp(S1->score,S2->score);
                        char p1[30];
                        char p2[30];
                        FILE *fp=fopen(argv[2],"r+");
                        fscanf(fp,"%s",p1);
                        fscanf(fp,"%s",p2);
                        fclose(fp);
                        if(k>0)
                           finish2(p1);
                        else if(k<0)
                            finish2(p2);
                        else
                            finish2("   DRAW!");
                        break;
                }

           }

           break;

       }
    }
    return 0;
}

