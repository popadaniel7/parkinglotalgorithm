#include <iostream> /// libraries used in this project
#include <math.h>
#include <vector>

using namespace std; /// used for convience

#define M 5

class Matrix /// class Matrix which is used as a tool to represent the parking lot
{
private:
    int** squareParkingLotInitial; /// the initial parking lot, as the problem states it
    int** squareParkingLotFinal; /// the final parking lot, which is generated manually
    int** auxParkingLot; /// auxiliar parking lot
public:
    void createParkingLotInitial() /// parking lot constructor
    {
        squareParkingLotInitial = new int* [M]; /// memory allocation
        for (int i = 1; i <= M; i++)
            squareParkingLotInitial[i] = new int[M]; /// memory allocation

        for (int i = 1; i <= M; i++)
            for (int j = 1; j <= M; j++)
                squareParkingLotInitial[i][j] = 0; /// intializing the matrix

        for (int i = 1; i <= M; i++)
            squareParkingLotInitial[i][1] = i; /// putting the cars where should be at first, as the problem states
    }
    void createParkingLotFinal() /// final parking lot constructor
    {
        squareParkingLotFinal = new int* [M]; /// memory allocation
        for (int i = 1; i <= M; i++)
            squareParkingLotFinal[i] = new int[M]; /// memory allocation

        for (int i = 1; i <= M; i++)
            for (int j = 1; j <= M; j++)
                squareParkingLotFinal[i][j] = 0; /// initializing the matrix

        for (int i = 1; i <= M; i++)
            squareParkingLotFinal[i][M] = M - i + 1; /// putting the cars where should be at the end, as the problem states
    }
    void createAuxParkingLot() /// auxiliar parking lot constructor
    {
        auxParkingLot = new int* [M]; /// memory allocation
        for (int i = 1; i <= M; i++)
            auxParkingLot[i] = new int[M]; /// memory allocation
    }
    void displayParkingLot() /// parking lot print function
    {
        for (int i = 1; i <= M; i++)
        {
            for (int j = 1; j <= M; j++)
                cout << squareParkingLotInitial[i][j] << " ";
            cout << endl;
        }
    }
    bool areParkingLotsDifferent() /// bool function to check if the initial matrix reached the end goal of the problem
    {
        for (int i = 1; i <= M; i++)
        {
            for (int j = 1; j <= M; j++)
            {
                if (squareParkingLotInitial[i][j] != squareParkingLotFinal[i][j])
                    return true;
            }
        }
        return false;
    }
    void moveCarsInParkingLot() /// the main function of the problem which does all the work
    {
        int numberOfSteps = 0; /// number of steps variable which counts the number of iterations done

        displayParkingLot(); /// display the initial matrix
        cout << endl;

        while (areParkingLotsDifferent() == true && numberOfSteps <= M*M+1) /// main loop which does the work
        {
            vector<bool> hasMoved(M + 1, false); /// bool vector which stores if the car has moved or not
            numberOfSteps++; /// number of steps increase

            for (int i = 1; i <= M; i++) /// loop where the steps execute
            {
                int rowSrc = get_rowSrc(i); /// getter for rows
                int colSrc = get_colSrc(i); /// getter for columns
                int rowDest = M - i + 1; /// this variable is used to determine where the car should arrive and it changes
                /// while the iterator i increase, as the problem states

                if (hasMoved[i] == false)/// if the car did not move
                {
                    if (rowSrc < rowDest) /// if the current position is before the destination row
                    {
                        /// move down
                        if (squareParkingLotInitial[rowSrc + 1][colSrc] == 0)
                        {
                            /// if there is a empty spot, the car will interchange positions with the empty spot
                            /// more specifically if the car is noted as "1" it will interchange with the value "0"
                            /// after this operation is done print parking lot
                            auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                            squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc + 1][colSrc];
                            squareParkingLotInitial[rowSrc + 1][colSrc] = auxParkingLot[1][1];
                            displayParkingLot();
                            cout << endl;
                        }
                        else if (squareParkingLotInitial[rowSrc + 1][colSrc] != 0)
                        {
                            /// if there is a car below, hop over it if there is an empty spot two rows below the initial position
                            if (rowSrc + 2 <= M && hasMoved[squareParkingLotInitial[rowSrc + 1][colSrc]] == false && squareParkingLotInitial[rowSrc + 2][colSrc] == 0)
                            {
                                /// if there is not a empty spot in the following below row, but on the one below that
                                /// interchange values
                                /// move the car down
                                /// the car that occupied the immediate spot stays in place
                                auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc + 2][colSrc];
                                squareParkingLotInitial[rowSrc + 2][colSrc] = auxParkingLot[1][1];
                                hasMoved[squareParkingLotInitial[rowSrc + 1][colSrc]] = true;
                                displayParkingLot();
                                cout << endl;
                            }
                            /// move right
                            else if (colSrc + 1 <= M && squareParkingLotInitial[rowSrc][colSrc + 1] == 0)
                            {
                                //
                                auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc + 1];
                                squareParkingLotInitial[rowSrc][colSrc + 1] = auxParkingLot[1][1];
                                displayParkingLot();
                                cout << endl;
                            }
                            /// hop over right
                            else if (colSrc + 1 <= M && squareParkingLotInitial[rowSrc][colSrc + 1] != 0)
                            {
                                ///
                                if (colSrc + 2 <= M && hasMoved[squareParkingLotInitial[rowSrc][colSrc + 2]] == false && squareParkingLotInitial[rowSrc][colSrc + 2] == 0)
                                {
                                    auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                    squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc + 2];
                                    squareParkingLotInitial[rowSrc][colSrc + 2] = auxParkingLot[1][1];
                                    hasMoved[squareParkingLotInitial[rowSrc][colSrc + 1]] = true;
                                    displayParkingLot();
                                    cout << endl;
                                }
                            }
                            /// move left
                            else if (colSrc - 1 > 0 && squareParkingLotInitial[rowSrc][colSrc - 1] == 0)
                            {
                                auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc - 1];
                                squareParkingLotInitial[rowSrc][colSrc - 1] = auxParkingLot[1][1];
                                displayParkingLot();
                                cout << endl;
                            }
                            /// hop over left
                            else if (colSrc - 2 > 0 && hasMoved[squareParkingLotInitial[rowSrc][colSrc - 2]] == false && squareParkingLotInitial[rowSrc][colSrc - 1] != 0)
                            {
                                auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc - 2];
                                squareParkingLotInitial[rowSrc][colSrc - 2] = auxParkingLot[1][1];
                                hasMoved[squareParkingLotInitial[rowSrc][colSrc - 1]] = true;
                                displayParkingLot();
                                cout << endl;
                            }
                        }
                    }
                    else if (rowSrc > rowDest) /// if the current position is after the destination row
                    {
                        // move up
                        if (squareParkingLotInitial[rowSrc - 1][colSrc] == 0)
                        {
                            //
                            auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                            squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc - 1][colSrc];
                            squareParkingLotInitial[rowSrc - 1][colSrc] = auxParkingLot[1][1];
                            displayParkingLot();
                            cout << endl;
                        }
                        else if (squareParkingLotInitial[rowSrc - 1][colSrc] != 0)
                        {
                            /// hop over up
                            if (rowSrc - 2 > 0 && hasMoved[squareParkingLotInitial[rowSrc - 1][colSrc]] == false && squareParkingLotInitial[rowSrc - 2][colSrc] == 0)
                            {
                                //
                                auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc - 2][colSrc];
                                squareParkingLotInitial[rowSrc - 2][colSrc] = auxParkingLot[1][1];
                                hasMoved[squareParkingLotInitial[rowSrc - 1][colSrc]] = true;
                                displayParkingLot();
                                cout << endl;
                            }
                            // move right
                            else if (squareParkingLotInitial[rowSrc][colSrc + 1] == 0)
                            {
                                //
                                auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc + 1];
                                squareParkingLotInitial[rowSrc][colSrc + 1] = auxParkingLot[1][1];
                                displayParkingLot();
                                cout << endl;
                            }
                            else if (squareParkingLotInitial[rowSrc][colSrc + 1] != 0)
                            {
                                // hop over rigth

                                if (colSrc + 2 <= M && hasMoved[squareParkingLotInitial[rowSrc][colSrc + 2]] == false && squareParkingLotInitial[rowSrc][colSrc + 2] == 0)
                                {
                                    //
                                    auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                                    squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc + 2];
                                    squareParkingLotInitial[rowSrc][colSrc + 2] = auxParkingLot[1][1];
                                    hasMoved[squareParkingLotInitial[rowSrc][colSrc + 1]] = true;
                                    displayParkingLot();
                                    cout << endl;
                                }
                            }
                        }


                    }
                    else if (rowSrc == rowDest) /// if the current position is on the destination row
                    {
                        // we only move to the right because we reached the destination row, so we only need to reach the right column
                        if (colSrc + 1 <= M && squareParkingLotInitial[rowSrc][colSrc + 1] == 0)
                        {
                            //
                            auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                            squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc + 1];
                            squareParkingLotInitial[rowSrc][colSrc + 1] = auxParkingLot[1][1];
                            displayParkingLot();
                            cout << endl;
                        }
                        // hop over right
                        else if (colSrc + 2 <= M && hasMoved[squareParkingLotInitial[rowSrc][colSrc + 2]] == false && squareParkingLotInitial[rowSrc][colSrc + 1] != 0)
                        {
                            auxParkingLot[1][1] = squareParkingLotInitial[rowSrc][colSrc];
                            squareParkingLotInitial[rowSrc][colSrc] = squareParkingLotInitial[rowSrc][colSrc + 2];
                            squareParkingLotInitial[rowSrc][colSrc + 2] = auxParkingLot[1][1];
                            hasMoved[squareParkingLotInitial[rowSrc][colSrc + 1]] = true;
                            displayParkingLot();
                            cout << endl;
                        }
                        

                    }
                }
            }
        }
    }

    int get_rowSrc(int iterator_)///row getter
    {
        for (int i = 1; i <= M; i++)
            for (int j = 1; j <= M; j++)
                if (squareParkingLotInitial[i][j] == iterator_)
                    return i;
        return -1;///-1 if there is no row
    }
    int get_colSrc(int iterator_)///column getter
    {
        for (int i = 1; i <= M; i++)
            for (int j = 1; j <= M; j++)
                if (squareParkingLotInitial[i][j] == iterator_)
                    return j;
        return -1;///-1 if there is no column
    }

};


int main()
{
    Matrix* p = new Matrix; /// p pointer of type Matrix to access the Matrix methods


    p->createAuxParkingLot(); /// creates auxiliar parking lot
    p->createParkingLotFinal(); /// creates final parking lot
    p->createParkingLotInitial(); /// creates initial parking lot

    p->moveCarsInParkingLot(); /// calls for the main function where everything happens

    return 0;
}
