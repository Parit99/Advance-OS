#include "driver.h"
void simulate(int a,int b){   
    while(track[b]);
    srand(time(NULL)^(getpid()<<16));
    int home=rand()%6;
    int away=rand()%6;
    printf("Starting match: Team %d vs Team %d\n",a,b);
    printf("Match ended: Team %d vs Team %d   Result:%d-%d\n",a,b,home,away);
    if(home>away){
        won[a]+=1;loose[b]+=1;
    }
    else if(away>home){won[b]+=1;loose[a]+=1;}
    else{draw[a]+=1;draw[b]+=1;}
    goals[a]+=home;goals[b]+=away;
    track[a]=0;track[b]=0;
    
}

void fix_match(int stat,int state){
    while(track[stat]);
    simulate(stat,state);
    
}

void create_childs(int stat){
    pid_t childs[number_of_teams];
    int cnt=0;pid_t id;
    for(int i=1;i<=number_of_teams-1;i++){
        id=fork();
        if(id==0){
            if(i>=stat){fix_match(stat,i+1);}
            else{fix_match(stat,i);}
            exit(0);
        }
        else{
            childs[cnt++]=id;
            kill(id,SIGSTOP);
        }
    }
    for(int i=0;i<cnt;i++){
        kill(childs[i],SIGCONT);
        sleep(3);
    }
    while(wait(NULL)!=-1); 
}

int create_process(){
    pid_t childs[number_of_teams];
    int cnt=0;pid_t id;
    for(int i=0;i<number_of_teams;i++){
        id=fork();
        if(id==-1){perror("Fork failed");exit(EXIT_FAILURE);}
        if(id==0){
            create_childs(i+1);
            exit(0);
        }
        else{
            childs[cnt++]=id;
            kill(id,SIGSTOP);
        }
    }
    for(int i=0;i<cnt;i++){
        kill(childs[i],SIGCONT);
    }
    while(wait(NULL)!=-1);
    return 0;
}

int main()
{
    readfile(&number_of_teams,matches);
    printf("Printing Matrix \n");
    printmat();
    printf("\n");
    printf("Number of matches %d\n",number_of_teams);
    init(&segmentId,&segid,&segid1,&segid2,&segid3);
    initialize_sharedmem();
    for(int i=1;i<=number_of_teams;i++){
        track[i]=0;won[i]=0;loose[i]=0;draw[i]=0;goals[0]=0;
    }
    int status=create_process();
    if(status==0){
        compute_final_matrix();
    }
    return 0;
}