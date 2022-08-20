//////////////////////////////
//// Hizir Ozcelik | Student Id: 991578495
//// Jun 4th, 2022 | version 1.1  @ Sheridan College
//// PROG20799 | Data Structures and Algorithm development - C
//// Class#: 1225 | Prof: Muhammad Mohiuddin
//// This program design for validate any given Sudoku grid. Validation is done by checking every rows and columns has
//// distinct integers from 1 to 9, and display whether it is valid solution or not.
//// Code also create and validate another sudoku grid. First two rows captured from user inputs and validate for range
//// and distinction wise. Other 7 rows are randomly generated and validate for the range and distinction wise as well.
//// Finally code display whether the grid is a valid solution or not.
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int chkRange(int arr[], len);
int chkDuplication(int arr[], int len);
void isValid(int temp);
void printGrid(int row, int col, int temp[row][col]);

#define SIZE 9
#define BUFF_SIZE 100


int main() {
    int testGrid[][SIZE] = {{5, 3, 4, 6, 7, 8, 9, 1, 2},
                            {6, 7, 2, 1, 9, 5, 3, 4, 8},
                            {1, 9, 8, 3, 4, 2, 5, 6, 7},
                            {8, 5, 9, 7, 6, 1, 4, 2, 3},
                            {4, 2, 6, 8, 5, 3, 7, 9, 1},
                            {7, 1, 3, 9, 2, 4, 8, 5, 6},
                            {9, 6, 1, 5, 3, 7, 2, 8, 4},
                            {2, 8, 7, 4, 1, 9, 6, 3, 5},
                            {3, 4, 5, 2, 8, 6, 1, 7, 9}};
    int myGrid[][SIZE] = {0};
    int tempArr[SIZE] = {0};

    printGrid(SIZE, SIZE, testGrid);

    // Rows validation for testGrid
    int temp = 0;
    for (int i = 0; i < SIZE; i++) {
        temp = chkDuplication(testGrid[i], SIZE);
        if (temp != 0) {
            break;
        }
    };

    // Column validation for testGrid if only rows are validated
    // columns are passing a 1D array for duplication check
    if (temp == 0) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                tempArr[j] = testGrid[j][i];
            }//end of inner for loop
            if (chkDuplication(tempArr, SIZE) != 0) {
                temp++;
                break;
            }// end of if statement
            if (temp != 0)
                break;
        }//end of outer for loop
    }// end of outer if statement

    isValid(temp); // Displaying result for given grid

    // taking user inputs for another Sudoku grid
    // myGrid[][] is start to build
    int ctr = 0;
    char buff[BUFF_SIZE];
    puts("Enter row 1 of your Sudoku Grid\nPlease use space/tab key to enter the next values and press \"Return\" after entering nine integers.");
    puts("Remember, to make a valid row of Sudoku grid,all integers should be distinct and range from 1 to 9");

    // first two rows get from user, validated for range and duplication
    for (int i = 0; i < 2; i++) {
        while (ctr != SIZE) {
            fgets(buff, sizeof(buff), stdin);
            ctr = sscanf(buff, "%d%d%d%d%d%d%d%d%d", &myGrid[i][0], &myGrid[i][1], &myGrid[i][2],
                         &myGrid[i][3], &myGrid[i][4], &myGrid[i][5], &myGrid[i][6], &myGrid[i][7], &myGrid[i][8]);
            if (ctr != SIZE) {
                puts("PLEASE, enter nine integers use space/tab key to the next values and press \"Return\" after entering nine integers.");
                puts("Remember, to make a valid row of Sudoku grid,all integers should be distinct and range from 1 to 9");
            } else if (chkRange(myGrid[i], SIZE) != 0) { // range validation
                puts("Range should be 1 to 9, please try again");
                ctr = 0;
            } else if (chkDuplication(myGrid[i], SIZE) != 0) { // duplication validation
                puts("Every number needs to be distinct from each other, please try again");
                ctr = 0;
            }
        }// while loop ends
        if (i == 0) printf("Enter row 2\n"); // if condition for avoid printing statement after second row captured.
        ctr = 0;
    }// end of for loop

    // Generation random rows for myGrid
    srand(time(0));
    temp = 1;

    for (int i = 2; i < SIZE; i++) {
        while (temp != 0) {// continue to generate 9 integers until every integer is distinct
            for (int j = 0; j < SIZE; j++) {
                myGrid[i][j] = (rand() % 9) + 1;// generate integers range from 1 to 9
            };
            temp = chkDuplication(myGrid[i], SIZE); // if function return zero then row is validated
        }
    }

    // printing new generated Sudoku grid
    printGrid(SIZE, SIZE, myGrid);

    // Only column validation is needed for myGrid because rows are already validated for range and duplication
    // columns are passing a 1D array for duplication check
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tempArr[j] = myGrid[j][i];
        }//end of inner for loop
        if (chkDuplication(tempArr, SIZE) != 0) {
            temp++;
            break;
        }// end of if statement
        if (temp != 0)
            break;
    }//end of outer for loop

    isValid(temp); // Displaying result

    return 0;
}// end of main


// This function check user inputs and validate if inputs are in range 1 to 9
int chkRange(int arr[], len) {
    int broke = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] < 1 || arr[i] > 9) {
            broke++;
            break;
        }// end of if statement
    }//end of for loop
    return broke;
}// end of function

// This function check user inputs and validate if all entry is distinct
int chkDuplication(int arr[], int len) {
    int broke = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] == arr[j]) {
                broke++;
                break; // no need for further iteration
            }
        } //end of middle for loop
        if (broke != 0) break;// break for outer for loop
    }//end of outer for loop
    return broke;
}

// This function display result for the sudoku grids
void isValid(int temp){
    if (temp == 0) {
        printf("\nGiven Sudoku grid is valid.\n");
    } else printf("\nIt is an invalid solution.\n");
}

// Display Sudoku grids
void printGrid(int row, int col, int temp[row][col]) {
    printf("\n-----------Sudoku Grid------------\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf(" %d\t", temp[i][j]);
            if (j == col - 1)
                printf("\n");
        } // end of inner for loop
    } //end of outer for loop
}// end of function