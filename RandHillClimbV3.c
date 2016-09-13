///////////////////////////////////////Black Box Optimization///////////////////////////////////
//@Author: Bikash Poudel                                                                      //
//@Course: CS 776: Evolutionary Computing                                                     //                                    
//@Algorithm: Simulated Annealing                                                             //
//@Problem Statement: Optimization of a Black Box Function that takes 100-bit number as input //
//                    and outputs a double value.                                             //   
////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////Headers/////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

///////////////////////////////////////Symbolic Constants/////////////////////////////////////////
#define MAX_ITER 1000000
#define T_LIMIT  400

//////////////////////////////////////Black Box Function to Optimize//////////////////////////////
double eval(int *pj);

//////////////////////////////////////Returns the wall clock time value///////////////////////////
double WallClockTime(  )
{
   struct timeval wct;
   gettimeofday (&wct, NULL);
   return wct.tv_sec + wct.tv_usec * 1.0e-6;
}

///////////////////////////Functions For Simulated Annealing based Hill Climber//////////////////

/*
  Function that copies src array into dst array
*/
void CopyVector(int *src, int *dst)
{
    int i;
    for(i = 0; i < 100; i++)
    {
        dst[i] = src[i];
    }
}

/*
  Generate a random 100-bit vector
*/
void GenRandStart(int *sv)
{
    int i, value;
    
    for(i = 0; i < 100; i++)
    {
        value = rand() % 2; //generate 1-bit random value
        sv[i] = value;
    }   
}


/*  Function that generates a ramdom samples in the solution space.
    The best solution so far is taken as input and modified randomly.
*/
void GenNextSample(int *v)
{
    int i, index;
    
    //the loop runs from 0 to a random value in between 0 and 99
    //for(i = 0; i < (rand() % 100); i++)
    //the loop runs for only one iteration thus changing only 1-bit
    for(i = 0; i < 1; i++)
    {
        //generate a random index 
        index = rand() % 100;
        //flip the bits of the random locations
        v[index] = v[index] ^ 0b1;
    }        
}

/*
  Main routine
*/

int main(void)
{
    int    vec[100], 
           vec1[100];
           
    int    i, 
           j, 
           maxIter = 0;
           
    double T       = 1,  // value of T for Boltzmann distribution
           pAccept = 0, // acceptance probability 
           pSample = 0; // probability value of a sample solution 
                        //computed based on Boltzmann distribution 
           
    double bestFitness, 
           fitness;
    
    double startTime, stopTime;
    
    time_t tsec;
    
    //start measuring the time 
    startTime = WallClockTime();
       
    //initialize the RNG with a seed
    srand((unsigned) time(&tsec));
    
    for(i = 0; i < 100; i++)
    {
        vec[i]      = 0;
    }
    
    bestFitness = eval(vec);
    
    CopyVector(vec, vec1);
    
    for(j = 0; j < MAX_ITER; j++)
    {   
        /*
           Change T after T_LIMIT iterations      
        */
        if(j%T_LIMIT == 0)
        {
            if(T > 0)
            {
                T = T - 0.00001;
            }
            else
            {
                break;
            }
        }
        
        //Generate another random candidate solution
        GenNextSample(vec1);
        
        //evaluate the fitness of the candidate solution
        fitness = eval(vec1);
        
        //generate a random acceptance probability in [0,1] for the newly 
        //generated candidate solution
        pAccept = (double) (rand() % 10000) / 10000.0;
        
        //generate the probability value corresponding this candidate solution 
        pSample = exp((double)(fitness - bestFitness)/T);
        
        //if the fitness of the new candidate is better then 
        //this new candidate is used for next iteration
        if(fitness >= bestFitness)
        {
            //save the best fitness value so far
            bestFitness = fitness;
            
            //save the best solution so far 
            CopyVector(vec1, vec);
            
            //save the maximum iteration to find the optimum solution
            maxIter = j;
        }
        //if the new fitness is not better then with small probability
        //choose a new random start
        else if(pSample > pAccept)
        {
            GenRandStart(vec1);
        }
        //use the previous best solution for next iteration
        else
        {
            CopyVector(vec, vec1);
        }
        
    }//main loop ends
    
    //stop time 
    stopTime = WallClockTime();
    
    printf("\n********************************If 1 percent of bits of best solution is changed randomly*******************************\n");
    printf("\nThe optimum solution vector is - \n");
    printf("Vec[100] = ");
    
    //displaying the solution vector
    for(i = 0; i < 100; i++)
    {
        printf("%d", vec[i]);
        if(i == 46)
        {
            printf("\n");
        }
        else
        {
            printf(" ");    
        }
         
    }
    
    printf("\nThe optimum fitness value of the function is - %lf - after %d iterations at time %lf seconds", bestFitness, maxIter, (stopTime - startTime));
    
    printf("\n************************************************************************************************************************\n");
    
    return 0;
  
}
