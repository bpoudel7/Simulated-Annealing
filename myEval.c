


            |f(x)
            |
            |
            |
            |
            |
          90|                                            /\
            |                                           /  \
            |                                          /    \
          65|-----------------------------------------/      \------------------------------------------
            |
            |
       _____|______________________________________________________________________________________________x  
            |
            |
            
            fig. Plot for the function for which a Hill Climbing Algorithm finds it difficult to converge to optimal solution
            

double eval(int *vec)
{
    int i;
    double returnValue;
    for(i = 0; i < 100; i++)
    {
        if(i == 48) 
         returnValue = 75;
        else if(i == 49)
         returnValue = 80;
        else if(i == 50)
         returnValue = 85;
        else if(i == 51) 
         returnValue = 90;
        else if(i == 52)
         returnValue = 85;
        else if(i == 52)
         returnValue = 80;
        else if(i == 52)
         returnValue = 75;
        else
         returnValue = 65;
    }
    return(returnValue);
}


