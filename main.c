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
    if (filePtr == NULL){
        printf("rut ro");
    };
    // char line[100];
    char character;
    int8_t thirdColumn;
    int lines = -1;
    int column = 0;
    char * dataTable[3][fileLength];
    //while for new line
    while(!feof(filePtr)){
        thirdColumn = 0;
        character = getc(filePtr);
        ++lines;
        column = 0;
        // For new Line
        if(lines<fileLength) {
            dataTable[0][lines] = malloc(sizeof(char)*1);
            dataTable[1][lines] = malloc(sizeof(char)*1);
            dataTable[2][lines] = malloc(sizeof(char)*1);
        }

        while(character != '\n' && character != EOF) {
            // printf("%c", character);
            character = getc(filePtr);

            if(character== '\'' || character=='\n'){
                thirdColumn = 1;
            } else {
                if(character==' ' && thirdColumn == 0) {
                    ++column;
                }
                // need to add rollac for dataTable later
                strncat(dataTable[column][lines], &character, 1);
            }
        }
    }
    fclose(filePtr);
    
    int col0Max=0;
    int col1Max=0;
    int col2Max=0;

    for(int i=0; i< fileLength; i++){
        int temp0 =strlen(dataTable[0][i]);
        int temp1 =strlen(dataTable[1][i]);
        int temp2 =strlen(dataTable[2][i]);

        if(temp0>col0Max)
            col0Max=temp0;
        if(temp1>col1Max)
            col1Max=temp1;
        if(temp2>col2Max)
            col2Max=temp2;
    }
    printline(col0Max+col1Max+col2Max);
    for(int i=0; i< fileLength; i++){
        printf("|");
        printf(" %s ",dataTable[0][i]);
        printSpaces(col1Max-strlen(dataTable[0][i]));
        printf("|");
        printSpaces(col1Max-strlen(dataTable[1][i]));
        printf("%s ",dataTable[1][i]);
        printf("|");
        printf("%s ",dataTable[2][i]);
        printSpaces(col2Max-strlen(dataTable[2][i]));
        printf("|\n");
        if(i == 0)
            printline(col0Max+col1Max+col2Max);
    }
    printline(col0Max+col1Max+col2Max);
}

void printline(int length) {
    for(int i=0; i<length+8; i++){
        printf("-");
    }
    printf("\n");
}

void printSpaces(int length){
    for(int i=0; i<length; i++){
        printf(" ");
    }
}