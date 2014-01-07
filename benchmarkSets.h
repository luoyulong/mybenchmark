#ifndef BENCHMARKSETS_H
#define BENCHMARKSETS_H
#include <malloc.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"
#define N 16
#define STEPS 100
#define DATATYPE float
void stencil_3D_27P(DATATYPE*** next,DATATYPE*** now,
                    DATATYPE alpha,DATATYPE beta,DATATYPE gamma,DATATYPE delta);

void stencil_3D_27P_OPT(DATATYPE*** next,DATATYPE*** now,
                        DATATYPE alpha,DATATYPE beta,DATATYPE gamma,DATATYPE delta);
void run();
#endif // BENCHMARKSETS_H
