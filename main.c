#include<string.h>
#include<windows.h>
#include<stdio.h>
#include"main.h"

#define MAX_TOKENS 1024
#define MAX_TOKEN_LENGTH 256

char total_tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];

void parse(const char *file) 
{
    HANDLE file_handle = CreateFileA(
        file,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (file_handle == INVALID_HANDLE_VALUE) 
    {
        return;
    }

    LARGE_INTEGER file_size = {0};
    if (!GetFileSizeEx(file_handle, &file_size)) 
    {
        return;
    }

    char *buffer = (char *)VirtualAlloc(NULL, file_size.QuadPart + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (buffer == NULL) 
    {
        CloseHandle(file_handle);
        return;
    }

    if (!ReadFile(file_handle, buffer, file_size.QuadPart, 0, NULL)) 
    {
        VirtualFree(buffer, 0, MEM_RELEASE);
        CloseHandle(file_handle);
        return;
    }

    buffer[file_size.QuadPart] = '\0';

    CloseHandle(file_handle);

    int index = 0;
    char *token = strtok(buffer, "{;:}");

    while (token != NULL && index < MAX_TOKENS) 
    {
        strcpy(total_tokens[index], token);
        index++;
        token = strtok(NULL, "{;:}");
    }

    VirtualFree(buffer, 0, MEM_RELEASE);
}

int main() 
{
    parse("example.txt");

    for (int i = 0; i < MAX_TOKENS && total_tokens[i][0] != '\0'; i++) 
    {
        printf("%s\n", total_tokens[i]);
    }

    getchar();
    return 0;
}