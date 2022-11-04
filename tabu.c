#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FORBIDDEN 2
#define Msize 6
int path_ans[Msize-1];
int cost_ans = INT_MAX;
int costMatrix[Msize][Msize] ;

struct forbiddenword
{
    int a[FORBIDDEN];
    int head;
};
struct MINBUFF
{
    int cost;
    int flag;
};
void printMat( int size)
{
    for(int i = 0 ; i < size ; i ++)
    {
        for(int j =0 ; j < size ; j++)
        {
            printf("%d ",costMatrix[i][j]);
        }
        printf("\n");
    }
}
void InitMat()
{



    for(int i = 0 ; i < Msize  ; i++)
    {
        for(int j = 0 ; j < Msize  ; j++)
        {
            costMatrix[i][j] = i == j ? 0 : rand() % 23 + 1 ;
        }
    }

}
int getcost(int * path, int size)
{
    int cost = 0;

    for(int i = 0 ; i < size-2 ; i++)
    {
        //printf("%d + %d  \n",cost,costMatrix[path[i]-1][path[i+1]-1] );
        cost += costMatrix[path[i]-1][path[i+1]-1] ;
    }
    cost = cost + costMatrix[0][path[0]-1] + costMatrix[path[Msize-2]-1][0] ;

    return cost;
}
int changcost(int * path, int i)
{
    int cost = 0;
    if(i == 0)
    {
        cost = -costMatrix[0][path[i]-1] -costMatrix[path[i]-1][path[i+1]-1] - costMatrix[path[i+1]-1][path[i+2]-1] + costMatrix[0][path[i+1]-1] +costMatrix[path[i+1]-1][path[i]-1] +costMatrix[path[i]-1][path[i+2]-1] ;
    }
    else if( i == Msize - 3)
    {
        cost = -costMatrix[path[i-1]-1][path[i]-1] -costMatrix[path[i]-1][path[i+1]-1] - costMatrix[path[i+1]-1][0] + costMatrix[path[i-1]-1][path[i+1]-1] +costMatrix[path[i+1]-1][path[i]-1] +costMatrix[path[i]-1][0] ;
    }
    else
    {
        cost = -costMatrix[path[i-1]-1][path[i]-1] -costMatrix[path[i]-1][path[i+1]-1] - costMatrix[path[i+1]-1][path[i+2]-1] + costMatrix[path[i-1]-1][path[i+1]-1] +costMatrix[path[i+1]-1][path[i]-1] +costMatrix[path[i]-1][path[i+2]-1] ;
    }
    return cost;
}
int choseswaptarget(int * path, struct forbiddenword *Ftable)
{
    int dif_cost = INT_MAX;
    int index = -1 ;
    int skip_event = 0 ;
    int temp ;
    for(int i = 0 ; i < Msize - 3 ; i++)
    {
        int k =( 0x1 << path[i]) + (0x1 << path[i+1]);
        for(int j = 0 ; j < FORBIDDEN; j++)
        {
            if(k == Ftable->a[j])
            {
                skip_event = 1;
            }
        }
        if(skip_event)
        {
            skip_event = 0 ;
            continue ;
        }
        temp = changcost(path, i) ;
        if(temp < dif_cost)
        {
            dif_cost = temp ;
            index = i ;
        }
    }

    return index;


}
void printfFtable(struct forbiddenword * Ftable)
{
    //printf("head = %d\n", Ftable->head);
    for(int i = 0 ; i < FORBIDDEN ; i++ )
    {
        //printf("禁止 %x \n", Ftable->a[i]);
    }
}
void SwapPath(int * path, int i, struct forbiddenword * Ftable )
{

    //printf("交換 %d %d\n", path[i],path[i+1]);
    Ftable->head = (Ftable->head + 1) % FORBIDDEN ;
    Ftable->a[Ftable->head] =( 0x1 << path[i] )+ (0x1 << path[i+1]) ;
    path[i] ^= path[i+1] ;
    path[i+1] ^= path[i] ;
    path[i] ^= path[i+1] ;

    int temp = getcost(path, Msize) ;
    if(temp < cost_ans)
    {
        cost_ans = temp ;
        for(int i = 0 ; i < Msize - 1 ; i ++)
        {
            path_ans[i] = path[i];
        }
    }
    printfFtable(Ftable);

}

int main()
{
    srand(time(NULL)) ;
    int round = 5000;
    struct forbiddenword Ftable =
    {
        .a = {0},
        .head = 0,
    };
    int path[Msize - 1] ;
    int iterator=10;

    while(round--)
    {
        iterator=10;
        for(int i = 0 ; i < Msize-1 ; i++ )
        {
            path[i] = i+2 ;
        }
        InitMat();
        //printMat(Msize);
        cost_ans = getcost(path, Msize) ;
        for(int i = 0 ; i < Msize - 1 ; i ++)
        {
            path_ans[i] = path[i];
        }
        while(iterator--)
        {
            int s = choseswaptarget(path, &Ftable);
            if(s == -1)
            {
                //      printf("提早進入終止條件\n");
                break ;
            }
            SwapPath(path, s, &Ftable);

        }
        //printf("cost = %d\n", cost_ans);
        //printf("迭代結束 cost = %d\n",getcost(path_ans, Msize));

        //printf("1->");
        //for(int i = 0 ; i < Msize - 1 ; i++)
        //{
        //  printf("%d->",path_ans[i]);
        //}
        //printf("1\n");



    }
    return 0;
}
