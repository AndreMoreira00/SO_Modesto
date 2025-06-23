#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    typedef enum {
        BLOQUEADO,
        DESBLOQUEADO
    } ProcessState;

    srand(time(NULL));

    int random_time = rand()%10;
    printf("%d", random_time);
    
    int random_class = rand()%2;
    printf("%d", random_class);



    return 0;
}
