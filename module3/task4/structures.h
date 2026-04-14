#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_CMD_LEN 1024
#define MAX_ARGS    64
#define MAX_STAGES  64

typedef struct {
    char *argv[MAX_ARGS];
    int   argc;
    char *infile;   
    char *outfile;  
} CmdStage;

#endif 