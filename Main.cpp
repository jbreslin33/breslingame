/******************************************************************************
* FILE: hello.c
* DESCRIPTION:
*   A "hello world" Pthreads program.  Demonstrates thread creation and
*   termination.
* AUTHOR: Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/

#include "Game.h"
#include <iostream>
#include <string>

#include "client/questiongame/QuestionClientGame.h"
#include "server/questiongame/QuestionServerGame.h"

//Threads
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS     5

QuestionServerGame* questionServerGame;

void *PrintHello(void *threadid)
{
        std::cout << "jimbo is here\n";
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
        while (true)
        {

        std::cout << "running PrintHello\n";
        }
   pthread_exit(NULL);
}

void *RunListenServer(void *t)
{
        while(true)
        {
                std::cout << "running RunListenServer function\n";
                questionServerGame->run();      
        }
}

int main(int argc, char *argv[])
{

//Threads
/*
pthread_t threads[NUM_THREADS];
int rc;
long t;
for(t=0;t<NUM_THREADS;t++){
  printf("In main: creating thread %ld\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
pthread_exit(NULL);
*/
//End threads

//Game

      std::cout << "Press Corresponding Number to Launch:\n";
        
        std::cout << "1 = QuestionServerGame\n";
        std::string one = "1";

        std::cout << "2 = QuestionClientGame\n";
        std::string two = "2";
        
        //get user response save to string
        std::string str;
        getline (std::cin,str);


        if (one.compare(str) == 0)
        {
                std::cout << "Launch A QuestionServerGame\n";
                std::cout << "try a thread\n";
                pthread_t listenServerThread1;
                long t = 2;

                questionServerGame  = new QuestionServerGame();
                //game->run();
                int rc = pthread_create(&listenServerThread1, NULL, RunListenServer , (void *) t );             

                if (rc)
                {
                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                        exit(-1);
                }
        
pthread_exit(NULL);
//                QuestionServerGame* game = new QuestionServerGame();
//              pthread_t listenServerThread2;
//              pthread_create(&listenServerThread2, NULL, RunListenServer, (void *) t);                
        }
        else if (two.compare(str) == 0)
        {
                std::cout << "Launch QuestionClientGame\n";
                QuestionClientGame* game = new QuestionClientGame();
        }

        else
        {
                std::cout << "I don't know what you want so I am doing nothing!\n";
        }


}

