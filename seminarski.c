#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

void print (int m, int n, int mat[m][n])
{
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%d ", mat[i][j]);
            if(j==n-1)
            {
                printf("\n");
            }
        }
    }
    printf("\n");
}

void print_niz (int m, int niz[])
{

    printf("\n");
    for(int i=0; i<m; i++)
    {
        printf("%d ", niz[i]);

    }

    //printf("\n");
}

void promjesaj (int m, int n, int mat[m][n])
{
    int rand_row=0;
    int rand_col=0;
    int pom;
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            rand_row = rand() % m;
            rand_col = rand() % n;

            pom= mat[i][j];
            mat[i][j]= mat[rand_row][rand_col];
            mat[rand_row][rand_col] = pom;
        }
    }


}

void create(int m, int n, int mat[m][n], int proc_min, int proc_max)
{
    float proc_nula;
    int br_nula,pom;
    //  srand(time(0));
    pom = (rand() % (proc_max - proc_min + 1)) +proc_min;
    proc_nula=0.01*pom;
    br_nula= m * n * proc_nula;
    //printf("br nula %d\n",br_nula);
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (br_nula>0)
            {
                mat[i][j]=0;
                br_nula--;
            }
            else
            {
                mat[i][j]=1;
            }

        }

    }
    promjesaj(m,n,mat);
    //ispisivanje dosadasnje matrice
    //print(m,n,mat);


}

void transformToCSR(int m, int n, int mat[m][n], int A[], int IA[], int JA[])
{

    int br_A=0;


    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (mat[i][j]==1)
            {
                A[br_A]=mat[i][j];
                IA[br_A]=i;
                JA[br_A]=j;
                br_A=br_A+1;
            }



        }

    }
    A[br_A]=-1;
    IA[br_A]=-1;
    JA[br_A]=-1;
    //printf("\n%d\n",br_A);


    //printf("Niz IA[]\n");
    print_niz((br_A),IA);
    //printf("Niz JA[]\n");
    print_niz((br_A),JA);
    //printf("Niz A[]\n");
    print_niz((br_A ),A);
    printf("\n");
}

void sum(int m, int n, int A[m][n], int B[m][n], int C[m][n])
{

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

}

void product(int m, int n, int p, int A[m][n], int B[n][p], int C[m][p])
{

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void summ(int A1[], int IA1[], int JA1[],int A2[], int IA2[], int JA2[],int A[], int IA[], int JA[])
{
    int br=0;
    int br1=0;
    int br2=0;

    while(IA1[br1]!=-1 && IA2[br2]!=-1)
    {

        if(IA1[br1]<IA2[br2])
        {
            IA[br]=IA1[br1];
            JA[br]=JA1[br1];
            A[br]=A1[br1];
            br++;
            br1++;
        }
        else if(IA1[br1]==IA2[br2])
        {
            if(JA1[br1]<JA2[br2])
            {
                IA[br]=IA1[br1];
                JA[br]=JA1[br1];
                A[br]=A1[br1];
                br++;
                br1++;
            }
            else if (JA1[br1]==JA2[br2])
            {
                IA[br]=IA1[br1];
                JA[br]=JA1[br1];
                A[br]=A1[br1]+A2[br2];
                br++;
                br1++;
                br2++;
            }
            else
            {
                IA[br]=IA2[br2];
                JA[br]=JA2[br2];
                A[br]=A2[br2];
                br++;
                br2++;
            }

        }
        else
        {
            IA[br]=IA2[br2];
            JA[br]=JA2[br2];
            A[br]=A2[br2];
            br++;
            br2++;
        }

    }
    while(IA1[br1]!=-1){
        IA[br]=IA1[br1];
        JA[br]=JA1[br1];
        A[br]=A1[br1];
        br++;
        br1++;
    }
    while(IA2[br2]!=-1){
        IA[br]=IA2[br2];
        JA[br]=JA2[br2];
        A[br]=A2[br2];
        br++;
        br2++;
    }


    printf("\n");
    //printf("IA:\n");
    for(int i=0; i<br ; i++)
    {
        printf("%d ", IA[i]);

    }
    printf("\n");
    //printf("JA:\n");
    for(int i=0; i<br ; i++)
    {
        printf("%d ", JA[i]);

    }

    printf("\n");
    for(int i=0; i<br ; i++)
    {
        printf("%d ", A[i]);

    }
    printf("\n");



}

int main ()
{

    int m=100;
    int n=10;
    int p=100;
    int matA[m][n],matB[100][100],matC[100][100];
    int proc_min = 40;
    int proc_max = 50;
    int A[20000],IA[20000],JA[20000];
    int A1[10000],IA1[10000],JA1[10000];
    int A2[10000],IA2[10000],JA2[10000];

    srand(time(NULL) * getpid() );


    /*

   for(int i=0; i<10; i++)
    {

        create(m, n, matA, proc_min, proc_max);
        print(m,n,matA);
        create(m, n, matB, proc_min, proc_max);
        print(m,n,matB);
        sum(m,n,matA,matB,matC);
        print(m,n,matC);
    }

    */


    /*
   for(int i=0; i<10; i++)
    {

        create(m, n, matA, proc_min, proc_max);
        print(m,n,matA);
        create(m, n, matB, proc_min, proc_max);
        print(m,n,matB);
        transformToCSR(m,n,matA,A1,IA1,JA1);
        transformToCSR(m,n,matB,A2,IA2,JA2);
        summ(A1,IA1,JA1,A2,IA2,JA2,A,IA,JA);
    }

    */


    /*

   for(int i=0; i<10; i++)
    {

        create(m, n, matA, proc_min, proc_max);
        print(m,n,matA);
        create(n, p, matB, proc_min, proc_max);
        print(n,p,matB);
        product(m,n,p,matA,matB,matC);
        print(m,p,matC);
    }

    */


    return 0;
}
