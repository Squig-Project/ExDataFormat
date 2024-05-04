#ifndef MAIN_H
#define MAIN_H

#define MAX_TOKENS 1024
#define MAX_TOKEN_LENGTH 256

char total_tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
void parse(const char *file);

#endif // MAIN_H