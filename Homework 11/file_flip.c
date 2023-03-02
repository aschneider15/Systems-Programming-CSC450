#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Stack{
    char ** list;
    unsigned int size;
    unsigned int pos;
};

struct Stack makeStack(unsigned int size);
void destroyStack(struct Stack * stack);
void push(char * str, struct Stack * stack);
char * pop(struct Stack * stack);
char * peek(struct Stack * stack);

//when referencing a specific instance, have to pass by reference (using *)

int main() {
    char * oldpath = "genesis.txt";
    char * newpath = "genesis_line_flip.txt";
    FILE * inputStream = fopen(oldpath, "r");
    FILE * outputStream = fopen(newpath, "w");

    int size = 0;
    int c;
    while((c = fgetc(inputStream)) != EOF){
        if ((char)c == '\n'){
            size = size + 1;
        }
    }
    //return to beginning of fp
    fseek(inputStream, 0, SEEK_SET);
    struct Stack linestack = makeStack(size);
    char * buf = malloc(sizeof(char *) * 1000);

    char * temp;

    //loop push all lines to stack
    while((temp = fgets(buf, 1000, inputStream)) != NULL){
        push(buf, &linestack);
    }

    //once done, loop to pop all lines from stack to new file
    while(linestack.pos > 0){
        temp = pop(&linestack);
        if (temp != NULL){
            fputs(temp, outputStream);
        }
        free(temp);
    }

    free(buf);
    destroyStack(&linestack);
    fclose(inputStream);
    fclose(outputStream);


    
    //loop pushes until entire file is read

    return 0;
}

/*
    push, pop, peek, constructor, destructor
*/

struct Stack makeStack(unsigned int size) {
    struct Stack out;
    out.size = size;
    out.list = malloc(sizeof(char *) * out.size);
    out.pos = 0;
}

void destroyStack(struct Stack * stack) {
    for(int i = 0; i < stack->size; i++) {
        free(stack->list[i]);
    }
    free(stack->list);
}

void push(char * str, struct Stack * stack){
    strcpy(stack->list[stack->pos], str);
    stack->pos = stack->pos + 1;
}

char * pop(struct Stack * stack) {
    char * str = (stack->list[stack->pos]);
    stack->pos = stack->pos - 1;
    return str;
}

char * peek(struct Stack * stack) {
    char * str = (stack->list[stack->pos]);
    return str;
}