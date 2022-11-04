#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Msize 6
#define MASK (0xFFFFFFFF >> (32-Msize +1) )
int cost = INT_MAX;
int callnum = 0 ;
int path[Msize-1];
int minpath[Msize-1];
int costmatrix[Msize][Msize] ;

void InitMat()
{


    for(int i = 0 ; i < Msize; i ++)
    {
        for(int j = 0 ; j < Msize; j++ )
        {
            costmatrix[i][j] = i == j ? 0 : rand() % 23 +1;
        }
    }


}
void printMat( int size)
{
    for(int i = 0 ; i < size ; i ++)
    {
        for(int j =0 ; j < size ; j++)
        {
            printf("%d ",costmatrix[i][j]);
        }
        printf("\n");
    }
}
void exhaustive( int bitmask,int  acc,int parent,int level)
{



    for(int k = bitmask, j = 1,i = 1; k != MASK;)
    {

        if((k & j) == 0)
        {

            //acc = acc + costmatrix[parent][i];
            k |= j;
            path[level] = i;
            exhaustive(bitmask|j,acc + costmatrix[parent][i], i,level+1);

        }
        j<<=1 ;
        i++;
    }
    if(bitmask == MASK)
    {
        acc += costmatrix[parent][0];

        if(cost > acc )
        {
            cost = acc  ;
            for(int i = 0 ; i < Msize-1 ; i ++)
            {
                minpath[i] = path[i];
            }
            //printf("cost = %d\n",cost);


            return ;
        }

    }
}
int main()
{

    srand(time(NULL));
    //printMat( Msize);
    int round =2;
    while(round--)
    {
        InitMat();
        printMat( Msize);
        cost = INT_MAX;
        exhaustive(0, 0, 0,0) ;
        printf("cost = %d\n 1->",cost);

        for(int i = 0 ; i < Msize-1 ; i ++)
        {
            printf("%d->",minpath[i]+1);
        }
        printf("1\n");
    }




    return 0;
}
