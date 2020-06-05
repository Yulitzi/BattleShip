/* 
 * File:   main.cpp
 * Author: Yulitzi Vizcarra
 * Created on May 3, 2020, 12:31 PM
 * Purpose:  Battleship Game Prototype 1
 */
//System Libraries Here
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
const int COLS = 8;

//Function Prototypes Here
void prntTbl(string [][COLS], int);
void v_u_ca(string [][COLS], int, int, int);    //VERT, USER, CARRIER
void h_u_ca(string [][COLS], int, int, int);    //HORZ, USER, CARRIER
void v_a_ca(string [][COLS], int, int, int);    //VERT, AI, CARRIER
void h_a_ca(string [][COLS], int, int, int);    //HORZ, AI, CARRIER
void v_u_b(string [][COLS], int, int, int);     //VERT, USER, BATTLE
void h_u_b(string [][COLS], int, int, int);     //HORZ, USER, BATTLE
void v_a_b(string [][COLS], int, int, int);     //VERT, AI, BATTLE
void h_a_b(string [][COLS], int, int, int);     //HORZ, AI, BATTLE
void v_u_d(string [][COLS], int, int, int);     //VERT, USER, DESTROY
void h_u_d(string [][COLS], int, int, int);     //HORZ, USER, DESTROY
void v_a_d(string [][COLS], int, int, int);     //VERT, AI, DESTROY
void h_a_d(string [][COLS], int, int, int);     //HORZ, AI, DESTROY
void v_u_s(string [][COLS], int, int, int);     //VERT, USER, SUB
void h_u_s(string [][COLS], int, int, int);     //HORZ, USER, SUB
void v_a_s(string [][COLS], int, int, int);     //VERT, AI, SUB
void h_a_s(string [][COLS], int, int, int);     //HORZ, AI, SUB
void v_u_cr(string [][COLS], int, int, int);    //VERT, USER, CRUISER
void h_u_cr(string [][COLS], int, int, int);    //HORZ, USER, CRUISER
void v_a_cr(string [][COLS], int, int, int);    //VERT, AI, CRUISER
void h_a_cr(string [][COLS], int, int, int);    //HORZ, AI, CRUISER


//Program Execution Begins Here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));  //Random # for CPU
    const int ROWS = 8;   // # of COLS
    int pos2, pos1; //Stores coordinates   
    int cpuHOV;           //Stores HORZ or VERT for COMPUTER placement
    bool repeat = true;     //Loops the battle sequence
    
    string hov; //Stores HORZ or VERT position
    string board [ROWS][COLS];      //USER board
    string boardAI [ROWS][COLS];    //CPU board
    string targtAI [ROWS][COLS];    //CPU targeting board
    string targtU [ROWS][COLS];     //USER targeting board
    int info [ROWS];
    
    char menuPck;       //Used for determining menu option

    cout.setf(ios::fixed);     
    cout.setf(ios::showpoint);
    cout.precision(2);

    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            board[col][row] = ".";
        }
    }   //Fill user table
    
    //Outputs new, FIRST table
    prntTbl(board, ROWS);
    
    //Input
    cout<<"Welcome to Battleship!"<<endl;
    cout<<"Please select an option by entering its respective number"<<endl;
    cout<<"1) Rules"<<endl<<"2) Play"<<endl;
    cin>>menuPck;
    switch(menuPck){
        case '1':{
            cout<<"- Your main goal is to destroy all of the enemy's ship tiles"<<endl;
            cout<<"- There are a total of 17 tiles to destroy, 5 ships in total"<<endl;
            cout<<"- Input is formatted so: 2 4, where 2 is the row and 4 is the column"<<endl;
            cout<<"- Do not place a ship that is out of bounds. Attempts to do so will be corrected"<<endl;
            cout<<"- Have fun! The game will now begin!"<<endl;
        };
        default:
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            if(hov == "H"){
                h_u_ca(board, ROWS, pos1, pos2);
            }   //Carrier
            if(hov == "V"){
                v_u_ca(board, ROWS, pos1, pos2);
            }
            //REPRINT THE TABLE
            prntTbl(board, ROWS);
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            if(hov == "H"){
                h_u_b(board, ROWS, pos1, pos2);
            }   //Battleship
            if(hov == "V"){
                v_u_b(board, ROWS, pos1, pos2);
            }
            //REPRINT THE TABLE
            prntTbl(board, ROWS);
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            if(hov == "H"){
                h_u_cr(board, ROWS, pos1, pos2);
            }   //Cruiser  
            if(hov == "V"){
                v_u_cr(board, ROWS, pos1, pos2);
            }
            //REPRINT THE TABLE
            prntTbl(board, ROWS);
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
        
            if(hov == "H"){
                h_u_s(board, ROWS, pos1, pos2);
            }   //Submarine  
            if(hov == "V"){
                v_u_s(board, ROWS, pos1, pos2);
            }
            //REPRINT THE TABLE
            prntTbl(board, ROWS);

                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            if(hov == "H"){
                h_u_d(board, ROWS, pos1, pos2);
            }   //Destroyer    
            if(hov == "V"){
                v_u_d(board, ROWS, pos1, pos2);
            }
            //REPRINT THE TABLE
            prntTbl(board, ROWS);
            
            //Beginning of Computer Phase
            
            for(int row = 0; row < ROWS; row++){
                for(int col = 0; col < COLS; col++){
                    boardAI[col][row] = ".";
                }
            }   //Fill AI table

            //Input
            cpuHOV = rand() % 2;
            if(cpuHOV == 0){
                h_a_ca(boardAI, ROWS, pos1, pos2);
            }   //Carrier
            if(cpuHOV == 1){
                v_a_ca(boardAI, ROWS, pos1, pos2);
            }
            //tEST

            //Places battleship
            cpuHOV = rand() % 2;
            if(cpuHOV == 0){
                h_a_b(boardAI, ROWS, pos1, pos2);
            }   //Battleship  
            if(cpuHOV == 1){
                v_a_b(boardAI, ROWS, pos1, pos2);
            }

            //Places cruiser
           cpuHOV = rand() % 2;
            if(cpuHOV == 0){
                h_a_cr(boardAI, ROWS, pos1, pos2);
            }   //Cruiser   
            if(cpuHOV == 1){
                v_a_cr(boardAI, ROWS, pos1, pos2);
            }

            //Places submarine
            cpuHOV = rand() % 2;
            if(cpuHOV == 0){
                h_a_s(boardAI, ROWS, pos1, pos2);
            }   //Submarine  
            if(cpuHOV == 1){
                v_a_s(boardAI, ROWS, pos1, pos2);
            }

            //Places destroyer [2]
            cpuHOV = rand() % 2;

            if(cpuHOV == 0){
                h_a_d(boardAI, ROWS, pos1, pos2);
            }   //Destroyer   
            if(cpuHOV == 1){
                v_a_d(boardAI, ROWS, pos1, pos2);
            }
            for(int row = 0; row < ROWS; row++){
                for(int col = 0; col < COLS; col++){
                    targtAI[col][row] = ".";
                }
            }   //Fills targeting board for user
            for(int row = 0; row < ROWS; row++){
                for(int col = 0; col < COLS; col++){
                    targtAI[col][row] = ".";
                }
            }   //Fills targeting board for AI

            //Exit
            return 0;
    }
}

void prntTbl(string board[][COLS], int rows){
    cout<<"    1   2   3   4   5   6   7   8"<<endl;
    cout<<"  +---+---+---+---+---+---+---+---+"<<endl;
    for(int row = 0; row < rows; row++){    //Prints | along sides of row
        cout<<row+1<<" | ";     
        for(int col = 0; col < 8; col++){
            cout<<board[row][col] <<" | ";  //Prints | between columns
        }
        cout<<endl;
        cout<<"  +---+---+---+---+---+---+---+---+"<<endl;
    }
}

void v_u_ca(string board[][COLS], int ROWS, int pos1 = 1, int pos2 = 1){    //VERT, USER, CARRIER
    cout<<"Please enter the location of your carrier (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    //Checks if carrier is being placed out of bounds
    while(((pos1 > 8 - 4) || pos1 < 1)){

                        cout<<"Ship is out of bounds!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }
    //Processes the Carrier [5]
    for(int row = pos1 - 1; row < (ROWS + (pos1-4)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2-COLS)); col++){
            board[row][col] = "A";
        }
    }
}   //VERT, USER, CARRIER
void h_u_ca(string board[][COLS], int ROWS, int pos1 = 1, int pos2 = 1){    //HORZ, USER, CARRIER
    cout<<"Please enter the location of your carrier (Row, Column)"<<endl;
    cin>>pos1>>pos2;


    //Checks if carrier is out of bounds
    while(((pos2 > 8 - 4) || pos2 < 1)){

                        cout<<"Ship is out of bounds!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }
    //Processes the Carrier [5]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2-4)); col++){
            board[row][col] = "A";
        }
    }
}   //HORZ, USER, CARRIER
void v_u_b(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your battleship (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    //Checks if Carrier position is out of bounds

    while(((pos1 > (8-3)) || pos1 < 1)){
        cout<<"The ship is out of bounds!"<<endl;
        cout<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }

    //Checks if carrier position is occupied
    while((board[pos1-1][pos2-1] == "A" 
          || board[pos1][pos2-1] == "A"
          || board[pos1+1][pos2-1] == "A"
          || board[pos1+2][pos2-1] == "A"
          || board[pos1+3][pos2-1] == "A")){

                        cout<<"There is already a ship there!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }
    //Processes the Battleship [4]
    for(int row = pos1 - 1; row < (ROWS + (pos1-5)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            board[row][col] = "B";
        }
    }
}     //VERT, USER, BATTLE
void h_u_b(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your battleship (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    //Checks if Carrier position is occupied
    while(((pos2 > 8 - 3) || pos2 < 1)){
        cout<<"Ship is out of bounds!"<<endl<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }
    while((board[pos1-1][pos2-1] == "A" 
          || board[pos1-1][pos2] == "A"
          || board[pos1-1][pos2+1] == "A"
          || board[pos1-1][pos2+2] == "A"
          || board[pos1-1][pos2+3] == "A")){

                        cout<<"There is already a ship there!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }
    //Processes the Battleship [4]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 5)); col++){
            board[row][col] = "B";
        }
    }
}     //HORZ, USER, BATTLE
void v_u_d(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your destroyer (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    while(((pos1 > 8 - 1) || pos1 < 1)){
        cout<<"Ship is out of bounds!"<<endl<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }
    if(pos1 == 7){
        while((board[pos1-1][pos2-1] == "D" || board[pos1-1][pos2-1] == "C" || board[pos1-1][pos2-1] == "B" || board[pos1-1][pos2-1] == "A"
        || board[pos1][pos2-1] == "D" || board[pos1][pos2-1] == "C" || board[pos1][pos2-1] == "B" || board[pos1][pos2-1] == "A")){
        //Will go out of bounds if ship is placed along the 7th row

            cout<<"Invalid position! There is already a ship there OR ship is out of bounds!"<<endl;
            cout<<"Please enter a new position"<<endl;
            cin>>pos1>>pos2;
        }
    }
    else{
    while((board[pos1-1][pos2-1] == "D" || board[pos1-1][pos2-1] == "C" || board[pos1-1][pos2-1] == "B" || board[pos1-1][pos2-1] == "A"
    || board[pos1][pos2-1] == "D" || board[pos1][pos2-1] == "C" || board[pos1][pos2-1] == "B" || board[pos1][pos2-1] == "A"
    || board[pos1+1][pos2-1] == "D" || board[pos1+1][pos2-1] == "C" || board[pos1+1][pos2-1] == "B" || board[pos1+1][pos2-1] == "A")){
    //Will go out of bounds if ship is placed along the 7th row

        cout<<"Invalid position! There is already a ship there OR ship is out of bounds!"<<endl;
        cout<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }}

    //Processes the Destroyer [2]
    for(int row = pos1 - 1; row < (ROWS + (pos1-7)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            board[row][col] = "E";
        }
    }
}     //VERT, USER, DESTROY
void h_u_d(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your destroyer (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    while(((pos2 > 8 - 1) || pos2 < 1)){
        cout<<"Please enter the location of your destroyer (Row, Column)"<<endl;
        cin>>pos1>>pos2;
    }
    //Checks for errors (double placement, out of bounds)
    while((board[pos1-1][pos2-1] == "D" || board[pos1-1][pos2-1] == "C" || board[pos1-1][pos2-1] == "B" || board[pos1-1][pos2-1] == "A"
          || board[pos1-1][pos2] == "D" || board[pos1-1][pos2] == "C" || board[pos1-1][pos2] == "B" || board[pos1-1][pos2] == "A"
          || board[pos1-1][pos2+1] == "D" || board[pos1-1][pos2+1] == "C" || board[pos1-1][pos2+1] == "B" || board[pos1-1][pos2+1] == "A")){

                        cout<<"Invalid position! There is already a ship there OR ship is out of bounds!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }

    //Processes the Destroyer [2]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 7)); col++){
            board[row][col] = "E";
        }
    }
}     //HORZ, USER, DESTROY
void v_u_s(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your submarine (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    //Checks for errors (double placement, out of bounds)

    while(((pos1 > 8 - 2) || pos1 < 1)){
        cout<<"Ship is out of bounds!"<<endl<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }
    while((board[pos1-1][pos2-1] == "C" || board[pos1-1][pos2-1] == "B" || board[pos1-1][pos2-1] == "A"
          || board[pos1][pos2-1] == "C" || board[pos1][pos2-1] == "B" || board[pos1][pos2-1] == "A"
          || board[pos1+1][pos2-1] == "C" || board[pos1+1][pos2-1] == "B" || board[pos1+1][pos2-1] == "A")){

                        cout<<"Invalid position! There is already a ship there OR ship is out of bounds!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }

    //Processes the Submarine [3]
    for(int row = pos1 - 1; row < (ROWS + (pos1-6)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            board[row][col] = "D";
        }
    }
}     //VERT, USER, SUB
void h_u_s(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your submarine (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    while(((pos2 > 8 - 2) || pos2 < 1)){
        cout<<"Ship is out of bounds!"<<endl<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }
    //Checks for errors (double placement, out of bounds)
    while((board[pos1-1][pos2-1] == "C" || board[pos1-1][pos2-1] == "B" || board[pos1-1][pos2-1] == "A"
          || board[pos1-1][pos2] == "C" || board[pos1-1][pos2] == "B" || board[pos1-1][pos2] == "A"
          || board[pos1-1][pos2+1] == "C" || board[pos1-1][pos2+1] == "B" || board[pos1-1][pos2+1] == "A")){
                        cout<<"Invalid position! There is already a ship there OR ship is out of bounds!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }

    //Processes the Submarine [3]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 6)); col++){
            board[row][col] = "D";
        }
    }
}     //HORZ, USER, SUB
void v_u_cr(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your cruiser (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    //Checks for errors (double placement, out of bounds)

    while(((pos1 > 8 - 2) || pos1 < 1)){
        cout<<"Ship is out of bounds!"<<endl<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }
    while((board[pos1-1][pos2-1] == "B" || board[pos1-1][pos2-1] == "A"
          || board[pos1][pos2-1] == "B" || board[pos1][pos2-1] == "A"
          || board[pos1+1][pos2-1] == "B" || board[pos1+1][pos2-1] == "A"
          || board[pos1+2][pos2-1] == "B" || board[pos1+2][pos2-1] == "A")){

                        cout<<"Invalid position! There is already a ship there OR ship is out of bounds!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }

    //Test input for a Cruiser from B4 to D4
    for(int row = pos1 - 1; row <(ROWS + (pos1-6)); row++){
        for(int col = pos2 - 1; col <(COLS + (pos2 - COLS)); col++){
            board[row][col] = "C";
        }
    }
}    //VERT, USER, CRUISER
void h_u_cr(string board[][COLS], int ROWS, int pos1, int pos2){
    cout<<"Please enter the location of your cruiser (Row, Column)"<<endl;
    cin>>pos1>>pos2;

    while(((pos2 > 8 - 2) || pos2 < 1)){
        cout<<"Ship is out of bounds!"<<endl<<"Please enter a new position"<<endl;
        cin>>pos1>>pos2;
    }
    //Checks for errors (double placement, out of bounds)
    while((board[pos1-1][pos2-1] == "B" || board[pos1-1][pos2-1] == "A"
          || board[pos1-1][pos2] == "B" || board[pos1-1][pos2] == "A"
          || board[pos1-1][pos2+1] == "B" || board[pos1-1][pos2+1] == "A"
          || board[pos1-1][pos2+2] == "B" || board[pos1-1][pos2+2] == "A")){

                        cout<<"Invalid position! There is already a ship there OR ship is out of bounds!"<<endl;
                        cout<<"Please enter a new position"<<endl;
                        cin>>pos1>>pos2;
    }

    //Test input for a Cruiser from B4 to D4
    for(int row = pos1 - 1; row <(ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col <(COLS + (pos2 - 6)); col++){
            board[row][col] = "C";
        }
    }
}   //HORZ, USER, CRUISER
void v_a_ca(string board[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    //Checks if carrier is being placed out of bounds
    while(((pos1 >= 8 - 4) || pos1 < 1)){
        //cout<<"VERT CARRIER OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }
    
    //Processes the Carrier [5]
    for(int row = pos1 - 1; row < (ROWS + (pos1-4)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2-COLS)); col++){
            board[row][col] = "A";
        }
    }
    //cout<<"CAR POS: "<<pos1<<" "<<pos2<<endl;
}    //VERT, AI, CARRIER
void h_a_ca(string board[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;


    //Checks if carrier is out of bounds
    while(((pos2 >= 8 - 4) || pos2 < 1)){
       // cout<<"HORZ CARRIER OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }
    //Processes the Carrier [5]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2-4)); col++){    
            board[row][col] = "A";
        }
    }
}    //HORZ, AI, CARRIER
void v_a_cr(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;
    while(((pos1 >= 8 - 2) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1][pos2-1] == "B" || boardAI[pos1][pos2-1] == "A"
          || boardAI[pos1+1][pos2-1] == "B" || boardAI[pos1+1][pos2-1] == "A"
          || boardAI[pos1+2][pos2-1] == "B" || boardAI[pos1+2][pos2-1] == "A")){
       // cout<<"VERT CRU DUPE"<<endl;
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }
    //Test input for a Cruiser from B4 to D4
    for(int row = pos1 - 1; row <(ROWS + (pos1-6)); row++){
        for(int col = pos2 - 1; col <(COLS + (pos2 - COLS)); col++){
            boardAI[row][col] = "C";
        }
    }
    //cout<<"CRU POS: "<<pos1<<" "<<pos2<<endl;
}    //VERT, AI, CRUISER
void h_a_cr(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;
    //Checks for errors (double placement, out of bounds)
    while(((pos2 >= 8 - 2) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1-1][pos2] == "B" || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "B" || boardAI[pos1-1][pos2+1] == "A"
          || boardAI[pos1-1][pos2+2] == "B" || boardAI[pos1-1][pos2+2] == "A")){
                    pos1 = rand()%7 + 1;
                    pos2 = rand()%7 + 1;
    }
    //Test input for a Cruiser from B4 to D4
    for(int row = pos1 - 1; row <(ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col <(COLS + (pos2 - 6)); col++){
            boardAI[row][col] = "C";
        }
    }
}    //HORZ, AI, CRUISER
void v_a_b(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;
    //Checks if carrier position is occupied
    while(((pos1 >= (8-3)) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "A" 
          || boardAI[pos1][pos2-1] == "A"
          || boardAI[pos1+1][pos2-1] == "A"
          || boardAI[pos1+2][pos2-1] == "A"
          || boardAI[pos1+3][pos2-1] == "A")){
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }
    //Processes the Battleship [4]
    for(int row = pos1 - 1; row < (ROWS + (pos1-5)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            boardAI[row][col] = "B";
        }
    }
}     //VERT, AI, BATTLE
void h_a_b(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1; 
    while(((pos2 >= 8 - 3) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "A" 
          || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "A"
          || boardAI[pos1-1][pos2+2] == "A"
          || boardAI[pos1-1][pos2+3] == "A")){
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }
   //Processes the Battleship [4]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 5)); col++){
            boardAI[row][col] = "B";
        }
    }
}     //HORZ, AI, BATTLE
void v_a_s(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;
    while(((pos1 >= 8 - 2) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1][pos2-1] == "C" || boardAI[pos1][pos2-1] == "B" || boardAI[pos1][pos2-1] == "A"
          || boardAI[pos1+1][pos2-1] == "C" || boardAI[pos1+1][pos2-1] == "B" || boardAI[pos1+1][pos2-1] == "A")){
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }
    //Processes the Submarine [3]
    for(int row = pos1 - 1; row < (ROWS + (pos1-6)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            boardAI[row][col] = "D";
        }
    }
}     //VERT, AI, SUB
void h_a_s(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;
    //Checks for errors (double placement, out of bounds)
    while(((pos2 >= 8 - 2) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1-1][pos2] == "C" || boardAI[pos1-1][pos2] == "B" || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "C" || boardAI[pos1-1][pos2+1] == "B" || boardAI[pos1-1][pos2+1] == "A")){
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }
    //Processes the Submarine [3]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 6)); col++){
            boardAI[row][col] = "D";
        }
    }
}     //HORZ, AI, SUB
void v_a_d(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;
    if(pos1 == 7){
        while(((pos1 >= 8 - 1) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "D" || boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
        || boardAI[pos1][pos2-1] == "D" || boardAI[pos1][pos2-1] == "C" || boardAI[pos1][pos2-1] == "B" || boardAI[pos1][pos2-1] == "A")){
        //Will go out of bounds if ship is placed along the 7th row
                pos1 = rand()%7 + 1;
                pos2 = rand()%7 + 1;
        }
    }
    else{
        while(((pos1 > 8 - 1) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "D" || boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
        || boardAI[pos1][pos2-1] == "D" || boardAI[pos1][pos2-1] == "C" || boardAI[pos1][pos2-1] == "B" || boardAI[pos1][pos2-1] == "A"
        || boardAI[pos1+1][pos2-1] == "D" || boardAI[pos1+1][pos2-1] == "C" || boardAI[pos1+1][pos2-1] == "B" || boardAI[pos1+1][pos2-1] == "A")){
        //Will go out of bounds if ship is placed along the 7th row
                    pos1 = rand()%7 + 1;
                    pos2 = rand()%7 + 1;
        }
    }
    //Processes the Destroyer [2]
    for(int row = pos1 - 1; row < (ROWS + (pos1-7)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            boardAI[row][col] = "E";
        }
    }
}     //VERT, AI, DES
void h_a_d(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;
    //Checks for errors (double placement, out of bounds)
    while(((pos2 >= 8 - 1) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "D" || boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1-1][pos2] == "D" || boardAI[pos1-1][pos2] == "C" || boardAI[pos1-1][pos2] == "B" || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "D" || boardAI[pos1-1][pos2+1] == "C" || boardAI[pos1-1][pos2+1] == "B" || boardAI[pos1-1][pos2+1] == "A")){
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }
    //Processes the Destroyer [2]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 7)); col++){
            boardAI[row][col] = "E";
        }
    }
}     //HORZ, AI, DES






