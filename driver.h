#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>

#define BUFFER_SIZE 1000
#define SIZE 100
int number_of_teams;
int flag=1;
int matches [BUFFER_SIZE][BUFFER_SIZE];
int segid,segid1,segid2,segid3,segmentId;
int *track;int *won;int *loose;int *draw;int *goals;

void compute_final_matrix(){
    printf("Teams   W   D   L   GS   Points\n");
    //printf("\n");
    printf("-------------------------------\n");
    for(int i=1;i<=number_of_teams;i++){
        printf("%d \t%d   %d   %d   %d\t %d\n",i,won[i],draw[i],loose[i],goals[i],won[i]*3+draw[i]);
    }
}

int charToint(char c){
    return c-'0';
}
void readfile(int *number_of_teams,int (*matches)[BUFFER_SIZE]){
    FILE * fPtr;
    char buffer[BUFFER_SIZE];
    int totalRead = 0;

    fPtr = fopen("inp.txt", "r");
    if(fPtr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have read privilege.\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(buffer, BUFFER_SIZE, fPtr) != NULL) 
    {
        totalRead = strlen(buffer);int ro;int col;
        for(int i=0;i<totalRead;i++){
            const char ch=buffer[i];
            if(isalnum(ch)){
                if(totalRead==2){
                    *number_of_teams=charToint(ch);
                }
                else{
                    if(flag){ro=charToint(ch);flag=0;}
                    else{col=charToint(ch);flag=1;}
                }
            }
        }
        if(totalRead>2){
            matches[ro][col]=1;
        }
    } 
    fclose(fPtr);
}
void initialize_sharedmem(){
    goals = (int *)shmat(segid,NULL,0);
    track=(int *) shmat(segmentId, NULL, 0);
    won=(int *) shmat(segid1, NULL, 0);
    loose=(int *) shmat(segid2, NULL, 0);
    draw=(int *) shmat(segid3, NULL, 0);
    track[0]=0;won[0]=0;loose[0]=0;draw[0]=0;goals[0]=0;
}

void init(int *segmentId,int *segid,int *segid1,int *segid2,int *segid3){
    const int shareSize = sizeof(int) * (2 + SIZE);
    *segmentId = shmget(IPC_PRIVATE, shareSize, S_IRUSR | S_IWUSR);
    *segid=shmget(IPC_PRIVATE,sizeof(int)*SIZE,S_IRUSR|S_IWUSR);
    *segid1=shmget(IPC_PRIVATE,sizeof(int)*SIZE,S_IRUSR|S_IWUSR);
    *segid2=shmget(IPC_PRIVATE,sizeof(int)*SIZE,S_IRUSR|S_IWUSR);
    *segid3=shmget(IPC_PRIVATE,sizeof(int)*SIZE,S_IRUSR|S_IWUSR);
    if(*segid==-1 || *segid1==-1 || *segid2==-1 || *segid3==-1 || *segmentId==-1)
    {perror("Failed to allocate sharedmemory");}
}
void printmat(){
    for(int i=1;i<=number_of_teams;i++){
        for(int j=1;j<=number_of_teams;j++){
            if(matches[i][j] && i!=j){
                printf("1 ");
            }else{printf("0 ");}
        }printf("\n");
    }
}