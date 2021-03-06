#include "benchmarkSets.h"
DATATYPE*** getArray()
{
    DATATYPE* data=(DATATYPE*)malloc(sizeof(DATATYPE)*(N*N*N));
    DATATYPE** p1=(DATATYPE**)malloc(sizeof(DATATYPE*)*(N*N));
    DATATYPE*** p2=(DATATYPE***)malloc(sizeof(DATATYPE**)*(N));
    for(int k=0;k<N;k++)
    {
        p2[k]=p1;
        for(int j=0;j<N;j++)
        {
            p1[j]=data;
            for(int i=0;i<N;i++)
                data[i]=(double) rand ();
            data+=N;
        }
        p1+=N;
    }
    return p2;
}
void run()
{
    DATATYPE*** x=getArray();
    DATATYPE*** y=getArray();


    time_t t_start,t_end;
    t_start = time(NULL) ;
        stencil_3D_27P_OPT(x,y,3,5,3,0.1);
        stencil_3D_27P(x,y,3,5,3,0.1);
   // stencil_3D_7P(x,y,3);
    //stencil_3D_7P_OPT(x,y,3);
    t_end = time(NULL) ;
    std::cout<<"time:"<<(double)difftime(t_end,t_start)<<std::endl;
}



void stencil_3D_7P(DATATYPE*** next,DATATYPE*** now,DATATYPE fac)
{
    int i,j,k,t;
    for (t = 0; t < STEPS; t++) {
        for (k = 1; k < N - 3; k++) {
            for (j = 1; j < N - 3; j++) {
                for (i = 1; i < N - 3; i++) {
                    next[i][j][k]=now[i][j][k+1]+now[i][j][k-1]
                            +now[i][j-1][k]+now[i][j+1][k]
                            +now[i-1][j][k]+now[i+1][j][k]
                            - 6.0 * now[i][j][k] / (fac*fac);
                }
            }
        }

    }
}
void stencil_3D_7P_OPT(DATATYPE*** next,DATATYPE*** now,DATATYPE fac)
{
    int i,j,k,t;
    for (t = 0; t < STEPS; t++)
        for (k = 1; k < N - 3; k++)
            for (i = 1; i < N - 3; i++)
                for (j = 1; j < N - 3; j++)
                    next[i][j][k]=now[i][j][k+1]+now[i][j][k-1]
                            +now[i][j-1][k]+now[i][j+1][k]
                            +now[i-1][j][k]+now[i+1][j][k]
                            - 6.0 * now[i][j][k]/(fac*fac);
}




void stencil_3D_27P(DATATYPE*** next,DATATYPE*** now,
                    DATATYPE alpha,DATATYPE beta,DATATYPE gamma,DATATYPE delta)
{
    int i,j,k;
    for(int tstep=0;tstep<STEPS;tstep++){
#pragma scop
        for(i=1;i<N-1;i++)
            for(j=1;j<N-1;j++)
                for(k=1;k<N-1;k++)
                    next[i][j][k] =
                            alpha * (now[i][j][k] )

                            +beta * (now[i][j][k-1] + now[i][j-1][k] +
                            now[i][j+1][k] + now[i][j][k+1] +now[i-1][j][k] + now[i+1][j][k])

                            +gamma * (now[i-1][j][k-1] + now[i-1][j-1][k]
                            +now[i-1][j+1][k]+now[i-1][j][k+1]

                            +now[i][j-1][k-1]
                            +now[i][j+1][k-1] +now[i][j-1][k+1]+now[i][j+1][k+1]
                            +now[i+1][j][k-1] + now[i+1][j-1][k]+now[i+1][j+1][k] + now[i+1][j][k+1])

                            +delta*(now[i-1][j-1][k-1] + now[i-1][j+1][k-1] +now[i-1][j-1][k+1]
                            + now[i-1][j+1][k+1] +now[i+1][j-1][k-1] + now[i+1][j+1][k-1]
                            +now[i+1][j-1][k+1] + now[i+1][j+1][k+1]);
    }
}
void stencil_3D_27P_OPT(DATATYPE*** next,DATATYPE*** now,
                        DATATYPE alpha,DATATYPE beta,DATATYPE gamma,DATATYPE delta)
{
    int i,j,k;
    for(int tstep=0;tstep<STEPS;tstep++){

        for(i=1;i<N-1;i++)
            for(k=1;k<N-1;k++)
                for(j=1;j<N-1;j++)
                    next[i][j][k] =
                            alpha * (now[i][j][k] )
                            +beta * (now[i][j][k-1] + now[i][j-1][k] +
                            now[i][j+1][k] + now[i][j][k+1] +now[i-1][j][k] + now[i+1][j][k])

                            +gamma * (now[i-1][j][k-1] + now[i-1][j-1][k]
                            +now[i-1][j+1][k]+now[i-1][j][k+1] +now[i][j-1][k-1]
                            +now[i][j+1][k-1] +now[i][j-1][k+1]+now[i][j+1][k+1]
                            +now[i+1][j][k-1] + now[i+1][j-1][k]+now[i+1][j+1][k] + now[i+1][j][k+1])

                            +delta*(now[i-1][j-1][k-1] + now[i-1][j+1][k-1] +now[i-1][j-1][k+1]
                            + now[i-1][j+1][k+1] +now[i+1][j-1][k-1] + now[i+1][j+1][k-1]
                            +now[i+1][j-1][k+1] + now[i+1][j+1][k+1]);
    }
}

