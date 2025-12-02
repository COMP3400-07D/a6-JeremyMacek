#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if (argc < 2){
        perror("ERROR: Not enough args");
        return 1;
    }

    char fcfs[] = "fcfs";
    char rr[] = "rr";

    if (strcmp(argv[0], fcfs) == 0){

        printf("Using fcfs");

        int *bursts = (int *) malloc ((argc - 1) * sizeof(int));
        for (int i = 1; i < argc; i ++){
            bursts[i - 1] = (int) argv[i] - 0;
            printf("Accepted P%d: Burst %d\n", i - 1, bursts[i - 1]);
        }

        int total = fcfs_run(init_procs(bursts, argc - 1), argc - 1);
        printf("Average wait time: %.2f", (double) (total/argc - 1));

    }
    else if (strcmp(argv[0], rr) == 0){

        if (argc < 3){
            perror("Missing argumetns");
            return 1;
        }

        printf("Using RR(%s)", argv[1]);

        int *bursts = (int *) malloc ((argc - 1) * sizeof(int));
        for (int i = 1; i < argc; i ++){
            bursts[i - 1] = (int) argv[i] - 0;
            printf("Accepted P%d: Burst %d\n", i - 1, bursts[i - 1]);
        }

        int total = rr_run(init_procs(bursts, argc - 1), argc - 1, (int) (argv[1] - 0));
        printf("Average wait time: %.2f", (double) (total/argc - 1));

    }
    else{
        printf("ERROR: Enter valib scheduleing method first");
    }

    return 0;
}
