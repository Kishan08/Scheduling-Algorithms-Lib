/*
    Problem Defination : Implementation of Round Robin Sched. algorith.

    Input : file:"./input"

    Output : On stdout ( Standard Output Console)
                --file://"./write" Finish time of the processes
                --file://"./trace" Entire Trace of the algorithm

    Compiling : file://"./run" Script file

    Special Notes : RoundRobin Algorith Implementation
                    -- Dynamically allocated pid
                    -- Dynamic process entries rather to statics

    Dependencies :  process.h   Structure of process stamp's Header as Include
                    preq.h      Header as pre-requisites for the queue implementation
                    preq.c      Implementation of pre-requisites! ;) --may need optimization

    To solve for additional functionality : file://"./trace" --not implemented! (Don't 'cat' it)

    Implementation by : Jay Dihenkar! ( ;) )
                        date : 8th March 2014
                        guide : Mr. Hasmukh Rathod
                            Proffesor, Computer Science and Engineering
                            Parul Institue of Enginnering and Technology,
                            Baroda.

*/

#include<stdio.h>
#include<stdlib.h>
#include"preq.h"

static int g_pid=100;

FILE *write;
int quant=2;
void roundrobin(pptr* head,pptr* tail,const int count);
int main() {

  pptr head=NULL;
  pptr tail=NULL;
  int i=0;
  int tpid,tarr_time,tburst_time;
  pptr tprocess;
  FILE *read;
  read=fopen("input","r");
  write=fopen("write","w");
  //trace=fopen("trace","w");
  for(i=1;i<=3;i++) {
    //fscanf(read,"%d",&tpid);
    tpid=++g_pid;
    fscanf(read,"%d",&tarr_time);
    fscanf(read,"%d",&tburst_time);
    tprocess=create_process(tpid,tarr_time,tburst_time);
    add_to_queue(&head,&tail,tprocess);
  } fclose(read);

  tprocess=head;
  i=0;
  while(tprocess!=NULL) {
    ++i;
    tprocess=tprocess->next;
  }
  roundrobin(&head,&tail,i);
  return 0;
}


//roundrobin algorithm -- no text referred developed from self logic : Jay Dihenkar
//date : 8th March 2014.
void roundrobin(pptr* head,pptr* tail,const int count) {

  pptr parray[count];
  pptr pqueue[count];
  pptr tmp;
  int topIndex=-1;
  int i,j,t;
  int rr=0;
  int global_time=0;
  int qindex=-1;
  tmp=(*head);
  while(tmp!=NULL) {
    parray[++topIndex]=tmp;
    tmp=tmp->next;
  }
  i=0;
  while((topIndex>-1&&i<topIndex) || qindex>-1) {
    while(parray[i]->arr_time<=global_time && i<=topIndex) {
      qindex++;
      pqueue[qindex]=parray[i];
      i++;
    }

    if(qindex==-1) { //free cycle for cpu...
      printf("\nThe slot %d to %d for cpu is free!\n",global_time,global_time+1);
      fprintf(write,"\nThe slot %d to %d for cpu is free!\n",global_time,global_time+1);
      goto end_of_loop;
    }

if(rr>qindex) { rr=0;
}
      global_time+=quant;
      pqueue[rr]->burst_time-=quant;
      printf("\nThe process %d is served for 1 slot.. Rem Time is : %d",pqueue[rr]->pid,pqueue[rr]->burst_time);
      if(pqueue[rr]->burst_time<1) {
      printf("\nThe process pid:%d is served.. Finish Time : %d\n",pqueue[rr]->pid,global_time);
      fprintf(write,"\nThe process pid:%d is served.. Finish Time : %d\n",pqueue[rr]->pid,global_time);

	for(t=rr;t<qindex;t++) {
	pqueue[t] = pqueue[t+1];
      }
      qindex--;
      }
    //having served remove the process from queue
      rr++;
      continue;
      end_of_loop:global_time++;
      if(global_time>100) {
	return;
      }
  }

}






