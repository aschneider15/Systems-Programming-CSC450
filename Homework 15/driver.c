#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(){
    const char * filepath = "genesis.txt";
    const char * filepath_new = "genesis_copy.txt";
    FILE * inputstream = fopen(filepath, "rb");
    FILE * outputstream = fopen(filepath_new, "wb+");
    
    int size;
    fseek(inputstream, 0, SEEK_END);
    size = ftell(inputstream);
    int mid = size/2;
    char buffer[mid];

    int pid = fork();//create new thread
        //goal is to have one thread transport first half of text file
        //and have the other thread transport the second half.
        //from this point on, each thread has a copy of every var above.

    //child process has pid of zero
    if(pid == 0) {
        fseek(inputstream, 0, SEEK_SET); //child will start from beginning
        fread(buffer, mid, 1, inputstream);
        fwrite(buffer, mid, 1, outputstream);
        fflush(outputstream);
        fclose(inputstream);
        fclose(outputstream);
    } else {//parent pid unknown, but it's not zero
        fseek(inputstream, mid + 1, SEEK_SET); //child will start from beginning
        fread(buffer, mid, 1, inputstream);
        fseek(outputstream, mid + 1, SEEK_SET);
        sleep(1);//completely defeats the purpose of concurrency... but necessary
                //to ensure that threads execute in correct order.
        fwrite(buffer, mid, 1, outputstream);
        fflush(outputstream);
    }
    
    return 0;
}
