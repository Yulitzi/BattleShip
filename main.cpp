/* 
 * File:   main.cpp
 * Author: Yulitzi Vizcarra
 * Created on June 4, 2020, 10:38 AM
 * Purpose:  Battleship Game
 */

/* COMMENTS ON MY OWN PROGRESS NOT FOR PURPOSE OF GRADING
 *  Does not have to be full implementation of game
 * COMPLETED:
 *  Printing 8x8 table
 *  Allowing user to Place ships with random value so input all 5 ships in HORIZONTAL format
 *  Displaying their ships with unique characters
 *  Allow user to input in VERTICAL format (rotate)                     
 *  If tile is occupied, output an error and have them retry           
 *  If input is out of bounds, output an error and have them retry      
 *  Create AI to create their own board and play against player
 *  Place ships with random values                                 
 *  Launch attacks against player ships
 *  Create an ATTACK mode
 *  DRAW a conceptualization of enemy map
 *  Place "M" if MISS
 *  Place "X" if HIT
 *  Able to attack back and forth until either side runs out of ship tiles
 *  AI attacks randomly, no pattern whatsoever
 *  Eliminate out of bounds error when generating AI Table
 *  Might just restrict the boundaries from 1 - 7 rather 1 - 8 for table
 
 * To Do: 
 * Displays amount of ship tiles each side has              OPTIONAL IF TIME ALLOWS
 * Edit AI Display to count up instead of down
 * Ex: "5 CRUISER Tiles Destroyed"
 */

//System Libraries Here
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <vector>

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

void userAtk(string [][COLS], string [][COLS], int, int, int, vector<int>, vector<int>);    //User attack phase
void compAtk(string [][COLS], string [][COLS], int, int, int);  //CPU Attack phase
void batRep(string [][COLS], string [][COLS], string [][COLS], string [][COLS], int, bool&, vector<int>, vector<int>);  //Repeats attack phase
void shipChk(string [][COLS], string [][COLS], int);    //Checks if ship exists
void bubSort(int [],int);   //Bubble sort
void selSort(int [],int);   //Selection sort
int binary(int [],int,int); //Binary search
bool isDone(bool&); //Checks if game is still repeating


//Program Execution Begins Here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));  //Random # for CPU
    
    int pos2, pos1; //Stores coordinates   
    const int ROWS = 8;   // # of COLS
    int cpuHOV;           //Stores HORZ or VERT for COMPUTER placement
    bool repeat = true;     //Loops the battle sequence
    
    string hov; //Stores HORZ or VERT position
    string board [ROWS][COLS];      //USER board
    string boardAI [ROWS][COLS];    //CPU board
    string targtAI [ROWS][COLS];    //CPU targeting board
    string targtU [ROWS][COLS];     //USER targeting board
    
    char menuPck;       //Used for determining menu option
    vector<int> xVal, yVal; //Stores coordinates
    
    ifstream inFile;    //Input file stream
    ofstream outFile;   //Output file stream
    inFile.open("userIN.txt");    //Opens the input file  
    outFile.open("Results.txt");   //Opens the output file   

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
            cout<<"- Have fun! The game will now begin"<<endl;
        };
        default:
        
            if(inFile){
                for(int i = 0; i <1; i++){      //First line
                    getline(inFile, hov);
                }
            }
            else{
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            }
            
            if(hov == "H" || hov == "h"){
                h_u_ca(board, ROWS, pos1, pos2);
            }   //Carrier
            if(hov == "V" ||hov == "v"){
                v_u_ca(board, ROWS, pos1, pos2);
            }

            //REPRINT THE TABLE
            prntTbl(board, ROWS);


          
            if(inFile){
                for(int i = 1; i <2; i++){      //Second line
                getline(inFile, hov);
                }
            }
            else{
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            }
            if(hov == "H" || hov == "h"){
                h_u_b(board, ROWS, pos1, pos2);
            }   //Battleship
            if(hov == "V" ||hov == "v"){
                v_u_b(board, ROWS, pos1, pos2);
            }

            //REPRINT THE TABLE
            prntTbl(board, ROWS);


          
            if(inFile){
                for(int i = 1; i <2; i++){      //Third line
                getline(inFile, hov);
                }
            }
            else{
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            }

            if(hov == "H" || hov == "h"){
                h_u_cr(board, ROWS, pos1, pos2);
            }   //Cruiser  
            if(hov == "V" ||hov == "v"){
                v_u_cr(board, ROWS, pos1, pos2);
            }

            //REPRINT THE TABLE
            prntTbl(board, ROWS);

            
            if(inFile){
                for(int i = 1; i <2; i++){      //Fourth line
                getline(inFile, hov);
                }
            }
            else{
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            }
            if(hov == "H" || hov == "h"){
                h_u_s(board, ROWS, pos1, pos2);
            }   //Submarine  
            if(hov == "V" ||hov == "v"){
                v_u_s(board, ROWS, pos1, pos2);
            }
            //REPRINT THE TABLE
            prntTbl(board, ROWS);

            
            if(inFile){
                for(int i = 1; i <5; i++){      //Fifth line
                getline(inFile, hov);
                }
            }
            else{
                cout<<"Enter H to place your ship in a horizontal position"<<endl;
                cout<<"Enter V to place your ship in a vertical position"<<endl;
                cin>>hov;
            }

            if(hov == "H" || hov == "h"){
                h_u_d(board, ROWS, pos1, pos2);
            }   //Destroyer    
            if(hov == "V" ||hov == "v"){
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

            /*cout<<"COMPUTER GENERATED TABLE"<<endl<<endl<<endl<<endl;
            cout<<"    1   2   3   4   5   6   7   8"<<endl;
            cout<<"  +---+---+---+---+---+---+---+---+"<<endl;*/
            //prntTbl(boardAI, ROWS);   //Print AI Table


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

            cout<<endl<<endl<<"  ========= Attack Phase ========="<<endl;
            prntTbl(targtAI, ROWS);
            cout<<"Here, you will indicate where you would like to attack"<<endl;
            cout<<"Hits are represented by 'X' and misses are represented by 'M'"<<endl;
            cout<<"Input format: ROW COLUMN"<<endl;
            cout<<"Ex: 3 1"<<endl<<endl;

            while(repeat == 1){
                batRep(board, boardAI, targtAI, targtU, ROWS, repeat, xVal, yVal);
            }
            for(int i = 0; i < xVal.size(); i++){
                outFile<<i<<". "<<xVal.at(i)<<" "<<yVal.at(i)<<endl;
            }
            outFile.close();
            inFile.close();
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

    //Checks if ship is out of bounds


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
 //   cout<<"CAR POS: "<<pos1<<" "<<pos2<<endl;
}    //HORZ, AI, CARRIER
void v_a_cr(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    //Checks for errors (double placement, out of bounds)

    /*while(((pos1 > 8 - 2) || pos1 < 1)){
        cout<<"VERT CRUISER OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
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
    cout<<"CRU POS: "<<pos1<<" "<<pos2<<endl;
}    //VERT, AI, CRUISER
void h_a_cr(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    /*while(((pos2 > 8 - 2) || pos2 < 1)){
        cout<<"HORZ CRUISER OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
    //Checks for errors (double placement, out of bounds)
    while(((pos2 >= 8 - 2) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1-1][pos2] == "B" || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "B" || boardAI[pos1-1][pos2+1] == "A"
          || boardAI[pos1-1][pos2+2] == "B" || boardAI[pos1-1][pos2+2] == "A")){
         //       cout<<"HORZ CRU DUPE"<<endl;
                    pos1 = rand()%7 + 1;
                    pos2 = rand()%7 + 1;
    }

    //Test input for a Cruiser from B4 to D4
    for(int row = pos1 - 1; row <(ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col <(COLS + (pos2 - 6)); col++){
            boardAI[row][col] = "C";
        }
    }
  //  cout<<"CRU POS: "<<pos1<<" "<<pos2<<endl;
}    //HORZ, AI, CRUISER
void v_a_b(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    //Checks if Carrier position is out of bounds

    /*while(((pos1 > (8-3)) || pos1 < 1)){
        cout<<"VERT BATTLESHIP OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
    //Checks if carrier position is occupied
    while(((pos1 >= (8-3)) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "A" 
          || boardAI[pos1][pos2-1] == "A"
          || boardAI[pos1+1][pos2-1] == "A"
          || boardAI[pos1+2][pos2-1] == "A"
          || boardAI[pos1+3][pos2-1] == "A")){
      //              cout<<"VERT BAT DUPE"<<endl;
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }

    //Checks if ship is out of bounds


    //Processes the Battleship [4]
    for(int row = pos1 - 1; row < (ROWS + (pos1-5)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            boardAI[row][col] = "B";
        }
    }
  //  cout<<"BAT POS: "<<pos1<<" "<<pos2<<endl;
}     //VERT, AI, BATTLE
void h_a_b(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    //Checks if Carrier position is occupied
    /*while(((pos2 > 8 - 3) || pos2 < 1)){
        cout<<"HORZ BATTLESHIP OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
    while(((pos2 >= 8 - 3) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "A" 
          || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "A"
          || boardAI[pos1-1][pos2+2] == "A"
          || boardAI[pos1-1][pos2+3] == "A")){
        //            cout<<"HORZ BAT DUPE"<<endl;
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }

    //Processes the Battleship [4]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 5)); col++){
            boardAI[row][col] = "B";
        }
    }
 //   cout<<"BAT POS: "<<pos1<<" "<<pos2<<endl;
}     //HORZ, AI, BATTLE
void v_a_s(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    //Checks for errors (double placement, out of bounds)

    /*while(((pos1 > 8 - 2) || pos1 < 1)){
        cout<<"VERT SUBMARINE OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
    while(((pos1 >= 8 - 2) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1][pos2-1] == "C" || boardAI[pos1][pos2-1] == "B" || boardAI[pos1][pos2-1] == "A"
          || boardAI[pos1+1][pos2-1] == "C" || boardAI[pos1+1][pos2-1] == "B" || boardAI[pos1+1][pos2-1] == "A")){
    //    cout<<"VERT SUB DUPE"<<endl;
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }

    //Processes the Submarine [3]
    for(int row = pos1 - 1; row < (ROWS + (pos1-6)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - COLS)); col++){
            boardAI[row][col] = "D";
        }
    }
 //   cout<<"SUB POS: "<<pos1<<" "<<pos2<<endl;
}     //VERT, AI, SUB
void h_a_s(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    /*while(((pos2 > 8 - 2) || pos2 < 1)){
        cout<<"HORZ SUBMARINE OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
    //Checks for errors (double placement, out of bounds)
    while(((pos2 >= 8 - 2) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1-1][pos2] == "C" || boardAI[pos1-1][pos2] == "B" || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "C" || boardAI[pos1-1][pos2+1] == "B" || boardAI[pos1-1][pos2+1] == "A")){
  //      cout<<"HORZ SUB DUPE"<<endl;
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }

    //Processes the Submarine [3]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 6)); col++){
            boardAI[row][col] = "D";
        }
    }
   // cout<<"SUB POS: "<<pos1<<" "<<pos2<<endl;
}     //HORZ, AI, SUB
void v_a_d(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    /*while(((pos1 > 8 - 1) || pos1 < 1)){
        cout<<"VERT DESTROYER OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
    if(pos1 == 7){
        while(((pos1 >= 8 - 1) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "D" || boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
        || boardAI[pos1][pos2-1] == "D" || boardAI[pos1][pos2-1] == "C" || boardAI[pos1][pos2-1] == "B" || boardAI[pos1][pos2-1] == "A")){
        //Will go out of bounds if ship is placed along the 7th row
      //      cout<<"VERT DES DUPE"<<endl;
                pos1 = rand()%7 + 1;
                pos2 = rand()%7 + 1;
        }
    }
    else{
        while(((pos1 > 8 - 1) || pos1 < 1) || (boardAI[pos1-1][pos2-1] == "D" || boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
        || boardAI[pos1][pos2-1] == "D" || boardAI[pos1][pos2-1] == "C" || boardAI[pos1][pos2-1] == "B" || boardAI[pos1][pos2-1] == "A"
        || boardAI[pos1+1][pos2-1] == "D" || boardAI[pos1+1][pos2-1] == "C" || boardAI[pos1+1][pos2-1] == "B" || boardAI[pos1+1][pos2-1] == "A")){
        //Will go out of bounds if ship is placed along the 7th row
       //         cout<<"VERT DES DUPE"<<endl;
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
  //  cout<<"DES POS: "<<pos1<<" "<<pos2<<endl;
}     //VERT, AI, DES
void h_a_d(string boardAI[][COLS], int ROWS, int pos1, int pos2){
    pos1 = rand()%7 + 1;
    pos2 = rand()%7 + 1;

    /*while(((pos2 > 8 - 1) || pos2 < 1)){
        cout<<"HORZ DESTROYER OoB"<<endl;
        pos1 = rand()%7 + 1;
        pos2 = rand()%7 + 1;
    }*/
    
    //Checks for errors (double placement, out of bounds)
    while(((pos2 >= 8 - 1) || pos2 < 1) || (boardAI[pos1-1][pos2-1] == "D" || boardAI[pos1-1][pos2-1] == "C" || boardAI[pos1-1][pos2-1] == "B" || boardAI[pos1-1][pos2-1] == "A"
          || boardAI[pos1-1][pos2] == "D" || boardAI[pos1-1][pos2] == "C" || boardAI[pos1-1][pos2] == "B" || boardAI[pos1-1][pos2] == "A"
          || boardAI[pos1-1][pos2+1] == "D" || boardAI[pos1-1][pos2+1] == "C" || boardAI[pos1-1][pos2+1] == "B" || boardAI[pos1-1][pos2+1] == "A")){
         //       cout<<"HORZ DES DUPE"<<endl;
                        pos1 = rand()%7 + 1;
                        pos2 = rand()%7 + 1;
    }
   // cout<<"DES POS: "<<pos1<<" "<<pos2<<endl;
    //Processes the Destroyer [2]
    for(int row = pos1 - 1; row < (ROWS + (pos1-ROWS)); row++){
        for(int col = pos2 - 1; col < (COLS + (pos2 - 7)); col++){
            boardAI[row][col] = "E";
        }
    }
}     //HORZ, AI, DES

void shipChk(string board[][COLS], string boardAI[][COLS], int ROWS){
    int aCntU, bCntU, cCntU, dCntU, eCntU;          //Counts # of ships for user board
    aCntU = bCntU = cCntU = dCntU = eCntU = 0;
    int aCntA, bCntA, cCntA, dCntA, eCntA;          //Counts # of ships for AI board
    aCntA = bCntA = cCntA = dCntA = eCntA = 0;
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            if(board[row][col] == "A")aCntU++;
            if(board[row][col] == "B")bCntU++;
            if(board[row][col] == "C")cCntU++;
            if(board[row][col] == "D")dCntU++;
            if(board[row][col] == "E")eCntU++;
        }
    }
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            if(boardAI[row][col] == "A")aCntA++;
            if(boardAI[row][col] == "B")bCntA++;
            if(boardAI[row][col] == "C")cCntA++;
            if(boardAI[row][col] == "D")dCntA++;
            if(boardAI[row][col] == "E")eCntA++;
        }
    }
    /*cout<<"PLAYER Carrier Tiles: "<<setw(5)<<aCntU<<endl;
    cout<<"PLAYER Battleship Tiles: "<<setw(2)<<bCntU<<endl;
    cout<<"PLAYER Cruiser Tiles: "<<setw(5)<<cCntU<<endl;
    cout<<"PLAYER Submarine Tiles: "<<setw(3)<<dCntU<<endl;
    cout<<"PLAYER Destroyer Tiles: "<<setw(3)<<eCntU<<endl<<endl;
    cout<<"AI Carrier Tiles: "<<setw(9)<<aCntA<<endl;
    cout<<"AI Battleship Tiles: "<<setw(6)<<bCntA<<endl;
    cout<<"AI Cruiser Tiles: "<<setw(9)<<cCntA<<endl;
    cout<<"AI Submarine Tiles: "<<setw(7)<<dCntA<<endl;
    cout<<"AI Destroyer Tiles: "<<setw(7)<<eCntA<<endl;*/
}
void userAtk(string boardAI[][COLS], string targtAI[][COLS], int ROWS, vector<int> xVal, vector<int> yVal){
    int pos1;
    int pos2;
    cin>>pos1>>pos2;
    xVal.push_back(pos1);   //ROW
    yVal.push_back(pos2);   //COL
    
    pos1-=1;
    pos2-=1;
    if(boardAI[pos1][pos2] == "A" || boardAI[pos1][pos2] == "B" ||
        boardAI[pos1][pos2] == "C" || boardAI[pos1][pos2] == "D" ||
        boardAI[pos1][pos2] == "E" || boardAI[pos1][pos2] == "X"){
        targtAI[pos1][pos2] = "X";
        boardAI[pos1][pos2] = "X";
    }
    else{
        targtAI[pos1][pos2] = "M";
        boardAI[pos1][pos2] = "M";
    }
    
    prntTbl(targtAI,ROWS);
}
void compAtk(string board[][COLS], string targtU[][COLS], int ROWS){
    int pos1 = rand()%7 + 1;
    int pos2 = rand()%7 + 1;
 

    
    if(board[pos1][pos2] == "A" || board[pos1][pos2] == "B" ||
        board[pos1][pos2] == "C" || board[pos1][pos2] == "D" ||
        board[pos1][pos2] == "E" || board[pos1][pos2] == "X"){
        board[pos1][pos2] = "X";
    }
    else{
        board[pos1][pos2] = "M";
    }
    prntTbl(board,ROWS);
}
void batRep(string board[][COLS], string boardAI[][COLS], string targtAI[][COLS],
            string targtU[][COLS], int ROWS, bool &repeat, vector<int> xVal, vector<int> yVal){ 
    int letCntU = 0;
    int letCntA = 0;
    static int numLoop = 0;
    
    userAtk(boardAI, targtAI, ROWS, xVal, yVal);
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            if(boardAI[row][col] == "A" || boardAI[row][col] == "B" || 
               boardAI[row][col] == "C" || boardAI[row][col] == "D" || 
               boardAI[row][col] == "E"){
                letCntA++;
            }
            
        }
    }
    compAtk(board, targtU, ROWS);
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            if(board[row][col] == "A" || board[row][col] == "B" || 
               board[row][col] == "C" || board[row][col] == "D" || 
               board[row][col] == "E"){
               letCntU++;
            }
        }
    }
    numLoop++;
    //cout<<"User Has "<<letCntU<<" tiles remaining."<<endl;
    cout<<endl;
    shipChk(board, boardAI, ROWS);
    if(letCntU == 0 || letCntA == 0){
        repeat = false;
        if(letCntU == 0){
            cout<<"CPU Wins!"<<endl;
        }
        else if(letCntA == 0){
            cout<<"PLAYER Wins!"<<endl;
        }
    }
    else{
        repeat = true;
    }
}
bool isDone(bool &repeat){
    int temp;
    (repeat==1)?temp = 1 : temp = 0;
    if(temp == 1){
        return false;
    }
    else{
        return true;
    }
}
void bubSort(int a[],int n){
    bool swap;
    do{
        swap=false;
        for(int j=0;j<n-1;j++){
            if(a[j]>a[j+1]){
                int temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
                swap=true;
            }
        }
    }while(swap);
}
void selSort(int a[],int n){
    for(int pos=0;pos<n-1;pos++){
        int indx=pos;
        for(int i=pos+1;i<n;i++){
            if(a[indx]>a[i])indx=i;
        }
        //Perform Swap
        int temp=a[indx];
        a[indx]=a[pos];
        a[pos]=temp;
    }
}
int  binary(int a[],int n,int val){
    int high=n-1,low=0;
    do{
        int mid=(high+low)/2;
        if(a[mid]==val)return mid;
        else if(val>a[mid]){
            low=mid+1;
        }else{
            high=mid-1;
        }
    }while(high>=low);
    return -1;
}


