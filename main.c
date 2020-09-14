#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void openFile(char fileName[]);
int getFileLineNumber(char fileName[]);
void printline(int length);
void printSpaces(int length);


int main(int a, char** args) {
    char file[1000] = "./";
    char * input = args[1];
    strcat(file, input);
    openFile(file);
}

int getFileLineNumber(char fileName[]) {
    FILE * filePtr = fopen(fileName, "r"); 
    int lines=0;
    int character;
    while(!feof(filePtr)){
        //while for nav line
        character = getc(filePtr);
        if(character == '\n'){
            ++lines;
        }
    }
    fclose(filePtr);
    return lines;
}

void openFile(char fileName[]) {
    const int fileLength = getFileLineNumber(fileName);
    FILE * filePtr = fopen(fileName, "r"); 
    char character;
    int thirdColumn;
    // int lines = -1;
    int column = 0;
    char ** dataTable[3];
    dataTable[0] = calloc(sizeof(char*),fileLength);
    dataTable[1] = calloc(sizeof(char*),fileLength);
    dataTable[2] = calloc(sizeof(char*),fileLength);
    int col0Char,col1Char, col2Char;
    int col0Max=0;
    int col1Max=0;
    int col2Max=0;
    //while for new line
    // while(!feof(filePtr)){
    for(int lines=0; lines<fileLength; lines++){
        thirdColumn = 0;
        character = 'a';
        column = 0;
        dataTable[0][lines] = malloc(1);
        dataTable[1][lines] = malloc(1);
        dataTable[2][lines] = malloc(1);
        dataTable[0][lines][0] = '\0';
        dataTable[1][lines][0] = '\0';
        dataTable[2][lines][0] = '\0';
        col0Char=0;
        col1Char=0;
        col2Char=0;
        // free(str);
        while(character != '\n' && character != EOF) {
            // printf("%c", character);
            character = getc(filePtr);

            if(character== '\'' || character=='\n'){
                thirdColumn = 1;
            } else {
                if(character==' ' && thirdColumn == 0) {
                    ++column;
                }else{
                    if(column == 0){
                        ++col0Char;
                        dataTable[column][lines] = realloc(dataTable[column][lines], col0Char+1);
                        // dataTable[column][lines][col0Char-1] = character;
                        if(col0Char>col0Max)
                            col0Max = col0Char;
                    }
                    if(column == 1){
                        ++col1Char;
                        dataTable[column][lines] = realloc(dataTable[column][lines], col1Char+1);
                        // dataTable[column][lines][col1Char-1] = character;
                        if(col1Char>col1Max)
                            col1Max = col1Char;
                    }
                    if(column == 2){
                        ++col2Char;
                        dataTable[column][lines] = realloc(dataTable[column][lines], col2Char+1);
                        // dataTable[column][lines][col2Char-1] = character;
                        if(col2Char>col2Max)
                            col2Max = col2Char;
                    }
                        //strcat(dataTable[column][lines], &character);
                       strncat(dataTable[column][lines], &character, 1);
                }
            }
        }
    }

    fclose(filePtr);

    // for(int i=0; i< fileLength; i++){
    //     int temp0 =strlen(dataTable[0][i]);
    //     int temp1 =strlen(dataTable[1][i]);
    //     int temp2 =strlen(dataTable[2][i]);

    //     if(temp0>col0Max)
    //         col0Max=temp0;
    //     if(temp1>col1Max)
    //         col1Max=temp1;
    //     if(temp2>col2Max)
    //         col2Max=temp2;
    // }

    printline(col0Max+col1Max+col2Max);
    for(int i=0; i< fileLength; i++){
        printf("|");
        printf(" %s ", dataTable[0][i]);
        printSpaces(col0Max-strlen(dataTable[0][i]));
        printf("|");
        printSpaces(col1Max-strlen(dataTable[1][i]));
        printf(" %s ",dataTable[1][i]);
        printf("|");
        printf(" %s ",dataTable[2][i]);
        printSpaces(col2Max-strlen(dataTable[2][i]));
        printf("|\n");
        if(i == 0)
            printline(col0Max+col1Max+col2Max);
        free(dataTable[0][i]);
        free(dataTable[1][i]);
        free(dataTable[2][i]);
    }
    free(dataTable[0]);
    free(dataTable[1]);
    free(dataTable[2]);

    printline(col0Max+col1Max+col2Max);
}

void printline(int length) {
    for(int i=0; i<length+10; i++){
        printf("-");
    }
    printf("\n");
}

void printSpaces(int length){
    for(int i=0; i<length; i++){
        printf(" ");
    }
}