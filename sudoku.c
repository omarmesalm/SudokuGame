#include <stdio.h>
#include <stdlib.h>
#include<conio.h>


#define row_size 9
#define col_size 9

unsigned char sudo[row_size][col_size]={{ 5 , 3 ,' ',' ', 7 ,' ',' ',' ',' '},
                                        { 6 ,' ',' ', 1 , 9 , 5 ,' ',' ',' '},
                                        {' ', 9 , 8 ,' ',' ',' ',' ', 6 ,' '},
                                        { 8 ,' ',' ',' ', 6 ,' ',' ',' ', 3 },
                                        { 4 ,' ',' ', 8 ,' ', 3 ,' ',' ', 1 },
                                        { 7 ,' ',' ',' ', 2 ,' ',' ',' ', 6 },
                                        {' ', 6 ,' ',' ',' ',' ', 2 , 8 ,' '},
                                        {' ',' ',' ', 4 , 1 , 9 ,' ',' ', 5 },
                                        {' ',' ',' ',' ', 8 ,' ',' ', 7 , 9 }
                                        };


const unsigned char DefaultSudo[row_size][col_size] = {{ 5 , 3 ,' ',' ', 7 ,' ',' ',' ',' '},
                                                       { 6 ,' ',' ', 1 , 9 , 5 ,' ',' ',' '},
                                                       {' ', 9 , 8 ,' ',' ',' ',' ', 6 ,' '},
                                                       { 8 ,' ',' ',' ', 6 ,' ',' ',' ', 3 },
                                                       { 4 ,' ',' ', 8 ,' ', 3 ,' ',' ', 1 },
                                                       { 7 ,' ',' ',' ', 2 ,' ',' ',' ', 6 },
                                                       {' ', 6 ,' ',' ',' ',' ', 2 , 8 ,' '},
                                                       {' ',' ',' ', 4 , 1 , 9 ,' ',' ', 5 },
                                                       {' ',' ',' ',' ', 8 ,' ',' ', 7 , 9 }
                                                      };





void SudokuPrint(char arr[][9], char row, char col)
{
    int i,j;

    printf("\n");
    printf("\t   ");
    for(i=0; i<row; i++)
    {
        printf("   %d  ", i);
    }
    printf("\n");
    printf("\t   _______________________________________________________\n");

    for(i=0; i<row; i++)
    {
        printf("\t%d  ",i);
        for(j=0; j<col; j++)
        {
            if(arr[i][j] != ' ')
            {
                printf("|  %d  ", arr[i][j]);
            }
            else
            {
                printf("|  %c  ", arr[i][j]);
            }
        }
        printf("|\n");
        printf("\t   _______________________________________________________\n");
    }

    printf("\n");
}


char PrimaryPositions(char arr[][9], char x, char y)
{
    char flag=0;

    if(arr[x][y] != ' ')
    {
        flag = 1;
    }
    return flag;
}


char iSFinished(char sudo[][9], char row, char col)
{
    char i, j, flag = 0;

    for(i=0; (i<row) && (flag==0); i++)
    {
        for(j=0; j<col; j++)
        {
            if(sudo[i][j] == ' ')
            {
                flag = 1;
            }
        }
    }
    return flag;
}

void RemoveData(char arr[][9], char row, char col, char x_axis, char y_axis, char* isRemoved)
{
    char ErrorState =0;

    if((x_axis >= row) || (x_axis < 0) || (y_axis >= col) || (y_axis < 0))
    {
        ErrorState = 1;

    }

    else
    {
        if(PrimaryPositions(arr, x_axis, y_axis))
        {
            *isRemoved = 1;
        }
        else
        {
            sudo[x_axis][y_axis] = ' ';
        }
    }

}

char CheckRow(char arr[][9], char row, char col, char n)
{
    char i, isFind=0, flag;

    flag=0;
    for(i=0; (i<col)&&(flag==0); i++)
    {
        if(arr[row][i] == n)
        {
            isFind = 1;
            flag = 1;
        }
    }

    return isFind;
}

char CheckColumn(char arr[][9], char row, char col, char n)
{
    char i, isFind=0, flag;

    flag=0;
    for(i=0; (i<row)&&(flag==0); i++)
    {
        if(arr[i][col] == n)
        {
            isFind = 1;
            flag = 1;
        }
    }

    return isFind;
}



char SetData(char arr[][9], char row, char col, char x, char y, char n, char* isRowData, char* isColData, char* dataStatus)
{
    char ErrorState = 0;

    if((x >= row) || (y >= col) || (n > 9 || n < 1))
    {
        ErrorState = 1;
    }
    else
    {
        if(arr[x][y]==' ')
        {
            if(CheckRow(arr, x, col, n))
            {
                *isRowData = 1;
                ErrorState = 1;
            }
            else if(CheckColumn(arr, row, y, n))
            {
                *isColData = 1;
                ErrorState = 1;
            }
            else
            {
                arr[x][y]=n;
            }
        }
        else
        {
            *dataStatus = 1;
            ErrorState = 1;
        }

    }

    return ErrorState;
}


int main()
{
    int in_x, in_y, data, x_del, y_del;
    char Row_Checked=0, Col_Checked=0, Data_Checked=0, Data_Removed=0;
    char option, game=1;
    char rows = row_size;
    char columns = col_size;
    char State = 0;


    printf("-------------------------Welcome to Sudoku-------------------------\n\n");
    printf("Options :-\n");
    printf("e - to enter a new number\n");
    printf("c - to clear a number\n\n");

    SudokuPrint(sudo, rows, columns);


    while(game)
    {
        Row_Checked=0;
        Col_Checked=0;
        Data_Checked=0;


        printf("Enter the option:");
        fflush(stdin);
        scanf("%c", &option);

        system("cls");

        SudokuPrint(sudo, rows, columns);

        if(option == 'e')
        {
            printf("Enter the data\n");
            scanf("%d", &data);

            printf("Enter the position x\n");
            scanf("%d", &in_x);

            printf("Enter the position y\n");
            scanf("%d", &in_y);

            State = SetData(sudo, rows, columns, in_x, in_y, data, &Row_Checked, &Col_Checked, &Data_Checked);
            if(State)
            {
                if(in_x >= rows)
                {
                    printf("Wrong Entry, out of rows range\n");
                }
                if(in_y >= columns)
                {
                    printf("Wrong Entry, out of columns range\n");
                }
                if(data > 9 || data < 1)
                {
                    printf("Wrong Entry, data must be between 1->9\n");
                }
                if(Row_Checked)
                {
                    printf("Wrong Entry, there is the same entry data in the Row\n");
                }
                if(Col_Checked)
                {
                    printf("Wrong Entry, there is the same entry data in the Column\n");
                }
                if(Data_Checked)
                {
                    printf("Wrong Entry, there is a data in this position\n");
                }
            }

            if (iSFinished(sudo, rows, columns)==0)
            {
                game = 0;
            }

        }

        else if(option == 'c')
        {
            printf("Enter the location (x,y) to remove\n");
            scanf("%d  %d", &x_del, &y_del);
            RemoveData(DefaultSudo, rows, columns, x_del, y_del, &Data_Removed);
            if(Data_Removed)
            {
                printf("Invalid, you can't change this location!!\n");
            }
        }
        else
        {
            printf("Invalid!!, please select (e) to enter data or (c) to clear\n");
        }


        SudokuPrint(sudo, rows, columns);

    }

    printf("Congratulations, you won!!\n");

    return 0;
}



