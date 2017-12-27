
//
//  Muhammet Uçan 150140707
//  ucanmu@itu.edu.tr
//  Homework 1
//  Created by Muhammet Uçan on 1.03.2016
//  Copyright © 2016 Muhammet Uçan. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // VARIABLES
    int numberOfPlayers, probability ,win, score, toss, playerNumber, a, b;
    int round = 1, team1ScoreCounter = 0 ,team2ScoreCounter = 0, team1PassCounter = 0, team2PassCounter = 0;
    float passRandom, passSuccessTeam1 = 0, passSuccessTeam2 = 0;
    srand((unsigned int)time(NULL));
    
    // Take variables from user
    printf("Enter the number of players per team (N): ");
    scanf("%d",&numberOfPlayers);
    printf("Enter probability for a successful pass (P): ");
    scanf("%d",&probability);
    printf("Enter number of passes to win a single round (W): ");
    scanf("%d",&win);
    printf("Enter target score (S): ");
    scanf("%d",&score);
    
    while (team1ScoreCounter != score && team2ScoreCounter != score) { // the loop for counting score point and generating rounds until either one of team wins
        printf("Round-%d:\n",round);
        toss = rand()%2;
        a= 0, b= 0;
        
        if (toss == 0) { //first team starts
            passSuccessTeam1 = 100;
            passSuccessTeam2 = 0;
            printf("    Team 1 is selected\n");
        }
        else if (toss == 1) { //second team starts
            passSuccessTeam1 = 0;
            passSuccessTeam2 = 100;
            printf("    Team 2 is selected\n");
        }
        
        while (team1PassCounter != win && team2PassCounter != win) { // the loop for counting pass and end round if one of team reaches enough pass to win
            
            if (passSuccessTeam1 >= passSuccessTeam2) { // if first team captures the ball
                if (team2PassCounter != 0) {
                    printf("\n    Team 1 captured the ball!\n");
                    team2PassCounter = 0;
                }
                
                playerNumber = 1 + rand()%numberOfPlayers;
                while (playerNumber == a) {  // the loop in order to prevent player to pass by himself
                    playerNumber = 1 + rand()%numberOfPlayers;
                    if (playerNumber != a) {
                        break;
                    }
                }
                
                (team1PassCounter != 0) ? printf(" -> Player %d",playerNumber) : printf("    Player %d",playerNumber); // prints pass, if the pass first pass does not print " > "
                
                a = playerNumber;
                team1PassCounter++;
                
                if (team1PassCounter == win) {
                    team1ScoreCounter++;
                    printf("\n    Success! New Score of Team1 is %d\n",team1ScoreCounter);
                }
                
                passRandom = 1 + rand()%100;
                passSuccessTeam1 = (float)probability / (float)passRandom;
                passSuccessTeam2 = (100-(float)probability) / (float)(100-passRandom);
                
            }
            else if (passSuccessTeam2 > passSuccessTeam1)  {
                
                if (team1PassCounter != 0) { // if second team captures the ball
                    printf("\n    Team 2 captured the ball!\n");
                    team1PassCounter = 0;
                }
                
                playerNumber = 1 + rand()%numberOfPlayers;
                while (playerNumber == b) { // the loop in order to prevent player to pass by himself
                    playerNumber = 1 + rand()%numberOfPlayers;
                    if (playerNumber != b) {
                        break;
                    }
                }
                
                (team2PassCounter != 0) ? printf(" -> Player %d",playerNumber) : printf("    Player %d",playerNumber); // prints pass, if the pass first pass does not print " > "
                
                b = playerNumber;
                team2PassCounter++;
                
                if (team2PassCounter == win) {
                    team2ScoreCounter++;
                    printf("\n    Success! New Score of Team2 is %d\n",team2ScoreCounter);
                }
                
                passRandom = 1 + rand()%100;
                passSuccessTeam2 = (float)probability / (float)passRandom;
                passSuccessTeam1 = (100-(float)probability) / (float)(100-passRandom);
                
            }
        }
        
        team1PassCounter = 0;
        team2PassCounter = 0;
        round++;
    }
    
    (team1ScoreCounter == score) ? printf("GAME OVER! Team1 reached the target score(%d) and won the game!\n",score) : printf("GAME OVER! Team2 reached the target score(%d) and won the game!\n",score);
    return 0;
}
