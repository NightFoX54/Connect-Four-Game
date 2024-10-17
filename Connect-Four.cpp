#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <stdlib.h>     //including the necessary libraries for our program.

using namespace std;

void printRules(); //prints the game rules

void gameStatus(int arr[6][7]); //prints the game board

void gameMove(int arr[6][7],int n,int y); //implements the player's move to the board

void incorrectMove(int arr[6][7],int *y);  //checks wether the move is correct or not

void incorrectMoveAi(int arr[6][7], int *y); //checks the ai's move

int gameOver(int arr[6][7]); //checks wether the board is full or not

int winningCondition(int arr[6][7], int p, int comp); //checks the winning conditions to find the winner.

int inputCheck(string input, int x, int y);

int harderAi(int arr[6][7]); //a better ai for single player mode

int returnDifferent4(int arr[6][7], int x[2], int y[2], int z[2], int k[2], int player, vector<int> &banned);

int returnDifferent3(int arr[6][7], int x[2], int y[2], int z[2], int k[2], int player);

int checkUnder(int arr[6][7], int x[2]);

//declaring the prototypes of the functions that we will use.



int main(){
    int arr[6][7] = {}; //declaring a multidimentional array for the gameboard
    int y;
    int player = 0;
    string input;
    int difficulty=0;
    srand(time(NULL)); //random number generater for ai in singleplayer
    
    printRules();
    
    while(player != 1 && player != 2){ //while loop just in case in player presses anything other than 1 or 2
        cout<<"\nPress 1 for singleplayer, Press 2 for multiplayer : ";
        getline(cin, input); //getting input from user for singleplayer or multiplayer
        player = inputCheck(input, 1, 2);

    
        switch(player){ //using switch case to seperate singleplayer and multiplayer
            case 1: //codes for singleplayer

                while(difficulty != 1 && difficulty != 2){
                    cout << "\n|DIFFICULTY|\n1) Easy\n2) Hard\nChoose a difficulty to start:  ";
                    getline(cin, input);
                    difficulty = inputCheck(input, 1, 2);
                    switch(difficulty){
                        case 1:
                            while(1){  //looping the game around the players until someone wins
                                cout << "player's turn\n";
                                gameStatus(arr);
                                cout << "\nChoose a column to play:";
                                getline(cin, input);
                                y = inputCheck(input, 1, 7);
                                cout << endl;
                                incorrectMove(arr,&y);
                                gameMove(arr,1,y);
                                if(winningCondition(arr,1,0)) //if winningCondition returns 1 breaks out of the loop
                                    break;
                                if(gameOver(arr)) //if gameOver returns 1 breaks out of the loop
                                    break;
                        
                    
                                cout << "computer's turn\n";
                                y = rand() % 7 + 1; //creating random number for the ai move
                                cout << "\nComputer chose column" << y <<"to play.\n";
                                incorrectMoveAi(arr,&y);
                                gameMove(arr,2,y);
                                if(winningCondition(arr,2,1)) 
                                    break;
                                if(gameOver(arr)) 
                                    break;
                            }
                            break;

                        case 2:
                            while(1){
                                cout << "\nComputer's turn\n";
                                y = harderAi(arr);
                                incorrectMoveAi(arr,&y);
                                cout << "Computer chose column " << y << ".\n";
                                cout << endl;
                                gameMove(arr,2,y);
                                if(winningCondition(arr,2,1)) 
                                    break;
                                if(gameOver(arr)) 
                                    break;

                                cout << "player's turn\n";
                                gameStatus(arr);
                                cout << "\nChoose a column to play:";
                                getline(cin, input);
                                y = inputCheck(input, 1, 7);
                                cout << endl;
                                incorrectMove(arr,&y);
                                gameMove(arr,1,y);
                                if(winningCondition(arr,1,0)) //if winningCondition returns 1 breaks out of the loop
                                    break;
                                if(gameOver(arr)) //if gameOver returns 1 breaks out of the loop
                                    break;
                            }
                        break;

                        default:
                            cout << "\nIncorrect input, try again.\n";
                    }
                }
                break;
                 
            case 2: //codes for multiplayer.
                while(1){ 
                    cout << "player 1's turn\n";
                    gameStatus(arr);
                    cout << "\nChoose a column to play:";
                    getline(cin, input);
                    y = inputCheck(input, 1, 7);
                    cout << endl;
                    incorrectMove(arr,&y);
                    gameMove(arr,1,y);
                    if(winningCondition(arr,1,0)) 
                        break;
                    if(gameOver(arr)) 
                        break;
            
        
                    cout << "player 2's turn\n";
                    gameStatus(arr);
                    cout << "\nChoose a column to play:";
                    getline(cin, input);
                    y = inputCheck(input, 1, 7);
                    cout << endl;
                    incorrectMove(arr,&y);
                    gameMove(arr,2,y);
                    if(winningCondition(arr,2,0)) 
                        break;
                    if(gameOver(arr)) 
                        break;
                }
                break;
            default:
                cout << "\nIncorrect input, try again.\n";
        }
    }
    

    cout << "\nGame is finished\n";
    gameStatus(arr);
return 0;
}

void printRules(){
    cout << "======================== RULES ====================================\n";
    cout << "1) Players must connect 4 of the same numbers in a row to win.\n";
    cout << "2) Only one number is played at a time.\n";
    cout << "3) Players can be on the offensive or defensive.\n";
    cout << "4) The game ends when there is a 4-in-a-row or a stalemate.\n";
    cout << "-------------------------------------------------------------------\n";
}

void gameStatus(int arr[6][7]){
    cout << endl;
    for(int i = 0; i < 6; i++){ //prints the gameboard
        cout << "|"; //prints "|" at the beginning to make it look like a board
        for(int j = 0; j < 7; j++){
            if(arr[i][j] == 0)
                cout << "   |"; //if there are no input at the current character prints space
            else{
                if(arr[i][j] == 1)
                    cout << " X |"; //if there is an input prints the character.
                else
                    cout << " O |"; //if there is an input prints the character.
            }
        }
        if(i<6)
            cout << "\n ----------------------------\n"; //prints this between lines.
    }
    for(int i = 1; i < 8; i++){ //prints numbers of rows at the end of the board.
        cout << "  " << i << " ";
    }
    cout << "\n";
}

void gameMove(int arr[6][7],int n,int y){
    for(int i = 5; i>=0 ; i--){
        if(arr[i][y-1] == 0){ //checks the lowest possible row to play
            arr[i][y-1] = n; //inputs the players number to that row
            break;
        }
    }
  
}
void incorrectMove(int arr[6][7],int *y){
    while(arr[0][*y-1] > 0 || *y < 1 || *y > 7){ // checks if the players input is between 1 and 7, and wether the column is full or not.
            if(*y < 1 || *y > 7)
                cout << "The column you chose is not between 1 and 7\n";
            else
                cout << "The column you chose is full\n";
            cout << "Please choose another column:";
            string input;
            getline(cin, input);
            *y = inputCheck(input, 1, 7);
            cout << endl;
        }
}

void incorrectMoveAi(int arr[6][7], int *y){
    while(arr[0][*y-1] > 0){ //checks wether the row that ai chose is full or not.
        *y = rand() % 7 + 1; //if the row is full generates another number.
    }
}

int gameOver(int arr[6][7]){
    int emptyColumnCount = 0;
    for(int i = 0; i < 7; i++){
        if(arr[0][i] == 0)
            emptyColumnCount++; //increases the emptyColumnCount if the column is empty.
    }
    if(emptyColumnCount == 0){
        cout << "No empty spaces left"; //if the emptyColumnCount remains 0 prints this.
        return 1; //returns 1 to end the game
    }
    else
        return 0; //returns 0 to continue the game
}

int winningCondition(int arr[6][7], int p, int comp){
    for(int x = 0; x < 6; x++){ //checks horizontal wins
        for(int y = 0; y < 4; y++){
            if(arr[x][y] == p && arr[x][y+1] == p && arr[x][y+2] == p && arr[x][y+3] == p)
            {
                if(comp == 1)
                    cout << "Computer won!\n";

                else
                    cout << "Player" << p << " won";
                return 1; //returns 1 to end the game
            }
        }
    }

    for(int x = 0; x < 3; x++){ //checks vertical wins
        for(int y = 0; y < 7; y++){
            if(arr[x][y] == p && arr[x+1][y] == p && arr[x+2][y] == p && arr[x+3][y] == p)
            {
                if(comp == 1)
                    cout << "Computer won!\n";

                else
                    cout << "Player" << p << " won";
                return 1;
            }
        }
    }

    for(int x = 0; x < 3; x++){ //checks diagonal wins from top left to bottom right
        for(int y = 0; y < 4; y++){
            if(arr[x][y] == p && arr[x+1][y+1] == p && arr[x+2][y+2] == p && arr[x+3][y+3] == p)
            {
                if(comp == 1)
                    cout << "Computer won!\n";

                else
                    cout << "Player" << p << " won";
                return 1;
            }
        }
    }

    for(int x = 0; x < 3; x++){ //checks diagonal wins from top right to bottom left
        for(int y = 6; y > 2; y--){
            if(arr[x][y] == p && arr[x+1][y-1] == p && arr[x+2][y-2] == p && arr[x+3][y-3] == p)
            {
                if(comp == 1)
                    cout << "Computer won!\n";

                else
                    cout << "Player" << p << " won";
                return 1;
            }
        }
    }
    return 0; //returns 0 to continue the game
}

int inputCheck(string input, int x, int y){
    char c = input[0];

    while(c < '0' + x || c > '0' + y){
        cout << endl << "Incorrect input. Please type a number between " << x << " and "<< y <<" : ";
        getline(cin, input);
        c = input[0];
    }
    return (c - '0');
}


int harderAi(int arr[6][7]){
    vector<int> banned;
    int dontMove = 0;
    int out = 1;
    //start of first win conditions
    for(int x = 0; x < 6; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x, y+1};
            int c[2] = {x,y+2};
            int d[2] = {x,y+3};
            if(out = returnDifferent4(arr, a, b, c, d, 2, banned)){
                return out;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 7; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y};
            int c[2] = {x+2,y};
            int d[2] = {x+3,y};
            if(out = returnDifferent4(arr, a, b, c, d, 2, banned)){
                return out;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y+1};
            int c[2] = {x+2,y+2};
            int d[2] = {x+3,y+3};
            if(out = returnDifferent4(arr, a, b, c, d, 2, banned)){
                return out;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 6; y > 2; y--){
            int a[2] = {x,y};
            int b[2] = {x+1, y-1};
            int c[2] = {x+2,y-2};
            int d[2] = {x+3,y-3};
            if(out = returnDifferent4(arr, a, b, c, d, 2, banned)){
                return out;
            }
        }
    }
    //end of first win conditions

    //start of first block conditions
    for(int x = 0; x < 6; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x, y+1};
            int c[2] = {x,y+2};
            int d[2] = {x,y+3};
            if(out = returnDifferent4(arr, a, b, c, d, 1, banned)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 7; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y};
            int c[2] = {x+2,y};
            int d[2] = {x+3,y};
            if(out = returnDifferent4(arr, a, b, c, d, 1, banned)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y+1};
            int c[2] = {x+2,y+2};
            int d[2] = {x+3,y+3};
            if(out = returnDifferent4(arr, a, b, c, d, 1, banned)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 6; y > 2; y--){
            int a[2] = {x,y};
            int b[2] = {x+1, y-1};
            int c[2] = {x+2,y-2};
            int d[2] = {x+3,y-3};
            if(out = returnDifferent4(arr, a, b, c, d, 1, banned)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }
    //end of first block conditions

    //start of second win conditions
    for(int x = 0; x < 6; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x, y+1};
            int c[2] = {x,y+2};
            int d[2] = {x,y+3};
            if(out = returnDifferent3(arr, a, b, c, d, 2)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 7; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y};
            int c[2] = {x+2,y};
            int d[2] = {x+3,y};
            if(out = returnDifferent3(arr, a, b, c, d, 2)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y+1};
            int c[2] = {x+2,y+2};
            int d[2] = {x+3,y+3};
            if(out = returnDifferent3(arr, a, b, c, d, 2)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 6; y > 2; y--){
            int a[2] = {x,y};
            int b[2] = {x+1, y-1};
            int c[2] = {x+2,y-2};
            int d[2] = {x+3,y-3};
            if(out = returnDifferent3(arr, a, b, c, d, 2)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }
    //end of second win conditions

    //start of second block conditions
    for(int x = 0; x < 6; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x, y+1};
            int c[2] = {x,y+2};
            int d[2] = {x,y+3};
            if(out = returnDifferent3(arr, a, b, c, d, 1)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 7; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y};
            int c[2] = {x+2,y};
            int d[2] = {x+3,y};
            if(out = returnDifferent3(arr, a, b, c, d, 1)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 0; y < 4; y++){
            int a[2] = {x,y};
            int b[2] = {x+1, y+1};
            int c[2] = {x+2,y+2};
            int d[2] = {x+3,y+3};
            if(out = returnDifferent3(arr, a, b, c, d, 1)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }

    for(int x = 0; x < 3; x++){ 
        for(int y = 6; y > 2; y--){
            int a[2] = {x,y};
            int b[2] = {x+1, y-1};
            int c[2] = {x+2,y-2};
            int d[2] = {x+3,y-3};
            if(out = returnDifferent3(arr, a, b, c, d, 1)){
                for(int i = 0; i < banned.size(); i++){
                    if(out == banned[i])
                        dontMove = 1;
                }
                if(dontMove == 0)
                    return out;
                dontMove = 0;
            }
        }
    }
    //end of second win conditions
    while(1){
        int output = rand() % 7 + 1;
        for(int i = 0; i < banned.size(); i++){
            if(output == banned[i])
                dontMove = 1;
        }
        if(!dontMove)
            return output;
        dontMove = 0;
    }
    return rand() % 7 + 1;
}

int returnDifferent4(int arr[6][7], int x[2], int y[2], int z[2], int k[2], int player, vector<int> &banned){
    if(arr[x[0]][x[1]] == player && arr[y[0]][y[1]] == player && arr[z[0]][z[1]] == player && arr[k[0]][k[1]] == 0){
        if(!checkUnder(arr,k) && player == 1){
            banned.push_back((k[1] + 1));
        }
        else if(checkUnder(arr,k))
            return (k[1] + 1);
    }
    if(arr[x[0]][x[1]] == player && arr[y[0]][y[1]] == player && arr[k[0]][k[1]] == player && arr[z[0]][z[1]] == 0){
        if(!checkUnder(arr,z) && player == 1){
            banned.push_back((z[1] + 1));
        }
        else if(checkUnder(arr,z))
            return (z[1] + 1);
    }
    if(arr[x[0]][x[1]] == player && arr[k[0]][k[1]] == player && arr[z[0]][z[1]] == player && arr[y[0]][y[1]] == 0){
        if(!checkUnder(arr,y) && player == 1){
            banned.push_back((y[1] + 1));
        }
        else if(checkUnder(arr, y))
            return (y[1] + 1);
    }
    if(arr[k[0]][k[1]] == player && arr[y[0]][y[1]] == player && arr[z[0]][z[1]] == player && arr[x[0]][x[1]] == 0){
        if(!checkUnder(arr,x) && player == 1){
            banned.push_back((x[1] + 1));
        }
        else if(checkUnder(arr, x))
            return (x[1] + 1);
    }
    return 0;
}

int returnDifferent3(int arr[6][7], int x[2], int y[2], int z[2], int k[2], int player){
    if(arr[x[0]][x[1]] == player && arr[y[0]][y[1]] == player && arr[z[0]][z[1]] == 0 && arr[k[0]][k[1]] == 0){
        if(checkUnder(arr,z))
            return (z[1] + 1);
        else if(checkUnder(arr,k))
            return (k[1] + 1);
    }
    if(arr[x[0]][x[1]] == player && arr[y[0]][y[1]] == 0 && arr[z[0]][z[1]] == player && arr[k[0]][k[1]] == 0){
        if(checkUnder(arr,y))
            return (y[1] + 1);
        else if(checkUnder(arr,k))
            return (k[1] + 1);
    }
    if(arr[x[0]][x[1]] == 0 && arr[y[0]][y[1]] == player && arr[z[0]][z[1]] == player && arr[k[0]][k[1]] == 0){
        if(checkUnder(arr,x))
            return (x[1] + 1);
        else if(checkUnder(arr,k))
            return (k[1] + 1);
    }
    if(arr[x[0]][x[1]] == player && arr[y[0]][y[1]] == 0 && arr[z[0]][z[1]] == 0 && arr[k[0]][k[1]] == player){
        if(checkUnder(arr,z))
            return (z[1] + 1);
        else if(checkUnder(arr,y))
            return (y[1] + 1);
    }
    if(arr[x[0]][x[1]] == 0 && arr[y[0]][y[1]] == player && arr[z[0]][z[1]] == 0 && arr[k[0]][k[1]] == player){
        if(checkUnder(arr,z))
            return (z[1] + 1);
        else if(checkUnder(arr,x))
            return (x[1] + 1);
    }
    if(arr[x[0]][x[1]] == 0 && arr[y[0]][y[1]] == 0 && arr[z[0]][z[1]] == player && arr[k[0]][k[1]] == player){
        if(checkUnder(arr,y))
            return (y[1] + 1);
        else if(checkUnder(arr,x))
            return (x[1] + 1);
    }
    return 0;
}

int checkUnder(int arr[6][7], int x[2]){
    if(arr[x[0]+1][x[1]] != 0 || x[0] == 5)
        return 1;
    return 0;
}
