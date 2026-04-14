#ifndef LOGIC_H
#define LOGIC_H

#include "structures.h"

int  is_builtin(const char *cmd);
int  parse_line(char *line, CmdStage stages[]);
void run_pipeline(CmdStage stages[], int n);

#endif 