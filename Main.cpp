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

void *RunListenServer(void *t)
{

	std::ofstream myfile;
	myfile.open ("example.txt",std::ios::app);
        
	while(true)
        {
  		myfile << "Writing this to a file.\n";
                myfile.close();


                std::cout << "running RunListenServer function\n";
                questionServerGame->run();      
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

