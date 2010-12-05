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
#include <fstream>

#include "client/questiongame/QuestionClientGame.h"
#include "server/questiongame/QuestionServerGame.h"

//Threads
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS     5

QuestionServerGame* questionServerGame;
QuestionClientGame* questionClientGame;

void *RunListenServerForServer(void *t)
{
	while(true)
        {
                questionServerGame->run();      
        }
}

void *RunListenServerForClient(void *t)
{
	while(true)
        {
                questionClientGame->run();
        }
}

int main(int argc, char *argv[])
{


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
               
		pthread_t listenServerThreadForServer;
                long t = 2;

                questionServerGame  = new QuestionServerGame();
                
		int rc = pthread_create(&listenServerThreadForServer, NULL, RunListenServerForServer , (void *) t );             

                if (rc)
                {
                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                        exit(-1);
                }
        
		pthread_exit(NULL);
        }
        
	else if (two.compare(str) == 0)
        {
                std::cout << "Launch QuestionClientGame\n";
		
		pthread_t listenServerThreadForClient;
                long t = 2;

                questionClientGame  = new QuestionClientGame();
                
		int rc = pthread_create(&listenServerThreadForClient, NULL, RunListenServerForClient , (void *) t );             

                if (rc)
                {
                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                        exit(-1);
                }
        
		pthread_exit(NULL);

        }

        else
        {
                std::cout << "I don't know what you want so I am doing nothing!\n";
        }
}

