#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const * a, char const * b);
int cmp(const void * a, const void * b);
void IOerror();

int main(void)
{
    char * word = (char *) malloc(sizeof(char));
    char ** line = (char **) malloc(sizeof(char *));
    int letterNum = 0;
    int wordNum = 0;
    
    char c = getchar();
    IOerror();
    
    //Remove leading Whitespace
    while (c == ' ')
    {
        c = getchar();
        IOerror();
    }
    
    char cc = getchar();
    IOerror();

    while (!feof(stdin))
    {   
        //Write c > word
        word[letterNum] = c;
        char * temp = realloc(word, (letterNum + 2) * sizeof(char));
        if (temp == NULL)
        {
            free(word);
            fprintf(stderr, "Error allocating memory.");
            exit(1);
        }
        else
        {
            word = temp;
        }

        //Whitespace
        if (c == ' ')
        {
            //Write word > line
            line[wordNum] = word;
            char ** ttemp = realloc(line, (wordNum + 2) * sizeof(char*));
            if (ttemp == NULL)
            {
                free(line);
                fprintf(stderr, "Error allocating more memory.");
                exit(1);
            }
            else
            {
                line = ttemp;
                wordNum++;
                //Reset Word
                letterNum = -1;
                word = NULL;
                word = (char *) malloc(sizeof(char));
            }
            //Ignore Extra Whitespace
            while (cc == ' ')
            {
                cc = getchar();
                IOerror();
            }
        }

        //Iterate
        letterNum++;
        c = cc;
        cc = getchar();
        IOerror();
    }
    
    //Add ' ' to the the end of word if not already there
    if (letterNum > 0 && word[letterNum - 1] != ' ')
    {
        word[letterNum] = c;
        letterNum++;
        
        if (c != ' ')
        {
            word[letterNum] = ' ';
        }
        
        line[wordNum] = word;
        wordNum++;
    }

    //Sort
    qsort(line, wordNum, sizeof(char*), cmp);
    
    //Ouput 
    size_t i;
    for (i = 0; i < wordNum; i++)
    {
        size_t j = 0;
        while (1)
        {
            putchar(line[i][j]);
            IOerror();
            if (line[i][j] == ' ')
            {
                break;
            }
            j++;
        }
    }
    
    //Free Memory
    size_t k;
    for (k = 0; k < wordNum; k++)
    {
        free(line[k]);
    }
    
    free(line);
    exit(0);
}

//FROBCMP as described in the assignment
int frobcmp(char const * a, char const * b)
{
    while (*a != ' ' && *b != ' ')
    {  
        char x = *a ^ 42;
        char y = *b ^ 42;
        if (x < y) return -1;
        if (x > y) return 1;
        a++;
        b++;
    }
    
    return 0;
}

//Pointer to be used in qsort
int cmp(const void * a, const void * b)
{
    return frobcmp(* (const char**) a, * (const char**) b);
}

//I/O error exit
void IOerror()
{
    if (ferror(stdin) || ferror(stdout))
    {
        fprintf(stderr, "Error with Input/Output.");
        exit(1);
    }
}
