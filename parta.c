#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Creates an array of pcbs in heap memory and sets each pcb's values accordingly.
 */
struct pcb* init_procs(int* bursts, int blen) {

    struct pcb *pcb_array = malloc(blen * sizeof(struct pcb));

    for (int i = 0; i < blen; i++){
        pcb_array[i].pid = i;
        pcb_array[i].burst_left = bursts[i];
        pcb_array[i].wait = 0;
    }

    return pcb_array;
}

/**
 * Prints out the pid, burst left, and wait time of an array of pcbs
 */
void printall(struct pcb* procs, int plen) {
    
    for (int i = 0; i < plen; i++){
        printf("pid: %d\nburst left: %d\nwait: %d", procs[i].pid, procs[i].burst_left, procs[i].wait);
    }

}

/**
 * Takes in an array of pcbs, the current process, and the amount of time that process takes.
 * Goes throught the array, if the element's pid is equal to the current processes then it reduces burst_left by amount.
 * Other wise, as long as the burst left isn't zero, wait is incremented by amount.
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    
    for (int i = 0; i < plen; i++){
        if (i == current){
            procs[i].burst_left -= amount;
        }
        else if (procs[i].burst_left > 0){
            procs[i].wait += amount;
        }
    }

}

/**
 * Takes in a list of pcbs and the length of that list.
 * Calls run_proc to 'execute' the current process. 
 * Keeps track of total time and returns it.
 */
int fcfs_run(struct pcb* procs, int plen) {

    int total = 0;
    
    for (int i = 0; i < plen; i++){
        total += procs[i].burst_left;
        run_proc(procs, plen, i, procs[i].burst_left);
    }

    return total;
}

/**
 * Takes in the current pcb, takes in a list of pcbs, and the length of the list.
 * Iterates through the list in a circular manner starting at current + 1.
 * If the burst left is zero it skipps the pcb, other wise it returns the pid of the current pcb.
 * If all of the pcbs in have a burst left of zero it reutrns -1.
 */
int rr_next(int current, struct pcb* procs, int plen) {

    int next = (current + 1) % plen;

    for (int i = 0; i < plen; i++){

        if (procs[next].burst_left == 0){
            next++;
            next %= plen;
            continue;
        }
        else{
            return procs[next].pid;
        }
    }

    return -1;
}
/**
 * TODO: Describe what the function does
 */
int rr_run(struct pcb* procs, int plen, int quantum) {

    int current = 0;
    int total = 0;
    
    do{

        if (procs[current].burst_left < quantum){

            total += procs[current].burst_left;
            run_proc(procs, plen, current, procs[current].burst_left);
            
        }
        else{

            run_proc(procs, plen, current, quantum);
            total += quantum;

        }

        current = rr_next(current, procs, plen);

    } while(current != -1);

    return total;
}

