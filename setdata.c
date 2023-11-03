#include "main.h"

/**
 * setdata - Initialize data structure
 *
 * @datast: data structure
 * @av: argument vector
 * Return: void
 */
void setdata(data datast, char **av){
    datast->argv = av;
    datast->command = NULL;
    datast->pid = get,pid();
    
}