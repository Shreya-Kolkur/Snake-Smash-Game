#ifndef SNAKESMASH_H_INCLUDED
#define SNAKESMASH_H_INCLUDED

struct location{
    int x[1000];
    int y[1000];
};

typedef struct node{
    struct location sloc;
    int length;
    char score[20];
    int dir;
}node;

typedef node* snake;


typedef struct box{
    int x;
    int y;
    int weight;
    struct box *next;
}box;

typedef struct block{
    box *b;
    int size;
}block;

typedef struct eat{
    box *f;
    int size;
}eat;


//prototypes for block and food
void initblock(block *B);
void addbox(box *B,int m,int n);
void initfood(eat *F);
void addfood(eat *F,int m,int n);
void addingblock(block *B,int c);
void addingblock2(block *B,int c);
void addingfood(eat *F,int c);
void addingfood2(eat *F,int c);
void displayblock(block B);
void displayfood(eat F);
void deletefood(eat *F);
void deleteblock(block *B);
void checkfood(snake *S,eat *F);
int checkblock(snake *S,block *B);

//prototypes for snake
void init(snake *S,int l,char sco[20]);
void init2(snake *S,int l,char sco[20]);
int drawborder(char *file1,char *file2);
void drawsnake(snake *S,int d,int l,int go);

//prototypes when game finishes
void finish(char *score,int h,int go);
void finish2(char *name);

#endif // SNAKESMASH_H_INCLUDED
