#include <iostream>
using namespace std;

//define all your classes here (as given above)
class SparseRow {
    protected:
        int row; //Row#
        int col; //Column#
        int value; //We will assume that all our values will be integers

    public:
        SparseRow (); //default constructor; row=-1;col=-1;value=0
        void display(); // print Row#, Column#, value, used for transpose and displaySparse
        friend ostream& operator<< (ostream& s, const SparseRow& p);

    //other methods that are necessary such as get and set
        SparseRow(int r, int c, int v);
        int getRow(); // gets row value
        int getCol(); // gets col value
        int getValue(); // gets 'value' value
        void setRow(int r); // sets row value; for addition and multiply functions
        void setCol(int c); // sets col value; for addition and multiply functions
        void setValue(int v); // sets value value; for addition and multiply functions
    };

// Default constructor. Sets default values to the protected instance variables. Assings -1, -1, and 0 to row, col, and value respectively.
SparseRow:: SparseRow() {
    row = -1;
    col = -1;
    value = 0;
}

// main constructor, assigns the specific row, column, and value values into the object
SparseRow:: SparseRow(int r, int c, int v) : row(r), col(c), value(v) {
    row = r;
    col = c;
    value = v;
}

// Displays the row#, col#, and value. This will be used to display the SparseMatrix
void SparseRow:: display() {
    cout << row << ", " << col << ", " << value << endl;
}

// overloads the << assignment in prints out the row, col, and value values
ostream& operator<< (ostream&s, const SparseRow& p) {

    if (p.row != -1 && p.col != -1 && p.value != 0) {
        s << p.row << ", " << p.col << ", " << p.value << endl;
    }

    return s;
}

// all set and get functions
int SparseRow:: getRow() { // gets row value

    return row;
}
int SparseRow:: getCol() { // gets col value

    return col;
}
int SparseRow:: getValue() { // gets 'value' value

    return value;
}
void SparseRow:: setRow(int r) { // sets row value; for addition and multiply functions

    row = r;
}
void SparseRow:: setCol(int c) { // sets col value; for addition and multiply functions
    col = c;
}
void SparseRow:: setValue(int v) { // sets value value; for addition and multiply functions
    value = v;
}

class SparseMatrix {
        protected:
            int noRows; //Number of rows of the original matrix
            int noCols; //Number of columns of the original matrix
            int commonValue; //read from input
            int noNonSparseValues; // the amount of uncommon values
            SparseRow* myArray; // Array
            int myMatrix[100][100]; // two-dimensional array, stores the value into the indexes which represent row and column

        public:
            SparseMatrix ();
            SparseMatrix (int n, int m, int cv, int nsv);
            SparseMatrix* Transpose (); //Matrix Transpose
            SparseMatrix* Multiply (SparseMatrix& M);
            SparseMatrix* Add (SparseMatrix& M);
            friend ostream& operator<< (ostream& s, const SparseMatrix& sm); // prints uncommon value
            void displayMatrix (); //Display the matrix in its original format

    //other methods that are necessary such as get and set
    void storeValues();
    void displaySparseMatrix();
    int getNoRows(); // gets number of rows
    int getNoCols(); // gets number of cols
    int getCommonValue(); // gets the common value
    int getNoNonSparseValue(); // gets the amount of uncommon values
    void setNoRows(int r); // sets # of rows, for functions
    void setNoCols(int c); // sets # of columns, for functions
    void setCommonValue(int cv); // sets common value, for functions
};

// default constructor
SparseMatrix:: SparseMatrix() {
    noRows = -1;
    noCols = -1;
    commonValue = 0;
    noNonSparseValues = -1;
}

// main constructor that assigns that values into the instance variables
SparseMatrix::SparseMatrix(int n, int m, int cv, int nsv) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = nsv;
}

// stores the values into the myMatrix 2d array
void SparseMatrix:: storeValues() {
    int value; // the variable that value is read in to

    for (int i = 0; i < (*this).getNoRows(); ++i) { // Outer for loop goes through every row
        for (int j = 0; j < (*this).getNoCols(); ++j) { // Inner for loop goes through every value in that row
            cin >> value; // stores value
            (*this).myMatrix[i][j] = value; // assigns value
        }
    }
}

// prints all of the values in a matrix format
void SparseMatrix::displayMatrix() {
    for (int i = 0; i < (*this).getNoRows(); ++i) { // goes through every row
        for (int j = 0; j < (*this).getNoCols(); ++j) { // goes through each value in that row
            cout << myMatrix[i][j] << " "; // prints value followed by space
        }
        cout << endl; // after all of the values in row, it skips to next line
    }
}

// prints out all of the uncommon values
void SparseMatrix:: displaySparseMatrix() {
    for (int i = 0; i < (*this).noRows; ++i) { // outer for loop goes through every individual row
        for (int j = 0; j < (*this).noCols; ++j) { // inner for loop goes through every value in that row
            if ((*this).myMatrix[i][j] != (*this).commonValue) { // conditional checks if the value is the same as common value
                cout << i << ", " << j << ", " << (*this).myMatrix[i][j] << endl; // if true, then it prints it out
            }
        }
    }

}

// prints all of the uncommon values
ostream& operator<< (ostream& s, const SparseMatrix& sm) {
/*  for (int i = 0; i < sm.noRows; ++i) { // outer for loop goes through every individual row
        for (int j = 0; j < sm.noCols; ++j) { // inner for loop goes through every value in that row
            if (sm.myMatrix[i][j] != sm.commonValue) { // conditional checks if the value is the same as common value
                s << i << ", " << j << ", " << sm.myMatrix[i][j] << " " << endl; // if true, then it prints it out
            }
        }
    }
*/
    return s;
}

// prints all of the uncommon values but with the row and column flipped
SparseMatrix* SparseMatrix:: Transpose() {
    SparseMatrix* temp;

    for (int i = 0; i < noRows; ++i) { // outer for loop goes through every individual row
        for (int j = 0; j < noCols; ++j) { // inner for loop goes through every value in that row
            if (myMatrix[i][j] != commonValue) { // conditional checks if the value is the same as common value
                cout << j << ", " << i << ", " << myMatrix[i][j] << endl; // if true, then it prints it out with row and column value switched
            }
        }
    }

    return temp;
}

// adds the corresponding elements together to make a new matrix
SparseMatrix* SparseMatrix:: Add(SparseMatrix& M) {
    SparseMatrix* temp = new SparseMatrix(); // creates new object

// Nested for loop adds all of the values together and stores them in the temp object
    for (int i = 0; i < (*this).getNoRows(); ++i) { // outer for loops goes through every row
        for (int j = 0; j < (*this).getNoCols(); ++j) { // inner for loops goes through every column
            (*temp).myMatrix[i][j] = (*this).myMatrix[i][j] + M.myMatrix[i][j]; // adds the values together and stores in the temp object
            cout << (*temp).myMatrix[i][j] << " "; // prints out sum of the two values with a space
        }
        cout << endl; // prints next line after it is done with the row
    }

    return temp;
}

// multiplies the two matrices to make a new matrix
SparseMatrix* SparseMatrix:: Multiply(SparseMatrix& M) {
    SparseMatrix* temp = new SparseMatrix(); //Creating the new object
    int dotProduct; // the dot product of the singular row and column

// Nested for loop multiplies the matrices together
for (int i = 0; i < (*this).getNoRows(); ++i) { // this loop goes through each row, repeats the amount of rows in first matrix
    for (int j = 0; j < (*this).getNoCols(); ++j) { // this loop goes through each column of the second matrix, repeats the amount fo columns in second matrix
        dotProduct = 0; // resets dot product
        for (int k = 0; k < (*this).getNoCols(); ++k) { // this for loop iterates through the rows and columns of the matrices
            // finds the dot product of the singular row and column.
            // i represents the current row of first matrix
            // j represents the current column of second matrix
            // k represents the iteration through the row/column
            dotProduct += (*this).myMatrix[i][k] * (M).myMatrix[k][j]; 
        }    
        (*temp).myMatrix[i][j] = dotProduct; // assigns dot product to index
        cout << (*temp).myMatrix[i][j] << " "; // prints out dotProduct value followed by a space
    }
   cout << endl; // when row is done, goes to new line
}
    return temp;
}

// all get and set functions
int SparseMatrix:: getNoRows() { // gets number of rows
    return noRows;
}
int SparseMatrix:: getNoCols() { // gets number of cols
    return noCols;
}
int SparseMatrix:: getCommonValue() { // gets the common value
    return commonValue;
} 
int SparseMatrix:: getNoNonSparseValue() { // gets the amount of uncommon value 
    return noNonSparseValues;
}
void SparseMatrix:: setNoRows(int r) { // sets # of rows, for functions
    noRows = r;
}
void SparseMatrix:: setNoCols(int c) { // sets # of columns, for functions   
    noCols = c;
}
void SparseMatrix:: setCommonValue(int cv) { // sets common value, for functions
    commonValue = cv;
}

//write the methods after the class definition
int main () {
    int n, m, cv, noNSV;
    SparseMatrix* temp;

//Write the Statements to read in the first matrix
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
    (*firstOne).storeValues();
    
//Write the Statements to read in the second matrix
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);
    (*secondOne).storeValues();

    cout << "First one in sparse matrix format" << endl;
    (*firstOne).displaySparseMatrix();

    cout << "After transpose" << endl;
    cout << (*(*firstOne).Transpose());

    cout << "First one in matrix format" << endl;
    (*firstOne).displayMatrix();

    cout << "Second one in sparse matrix format" << endl;
    (*secondOne).displaySparseMatrix();

    cout << "After transpose" << endl;
    cout << (*(*secondOne).Transpose());   
    
    cout << "Second one in matrix format" << endl;
    (*secondOne).displayMatrix();  
    
    cout << "Matrix Addition Result" << endl;
    // condition is for if the two object's rows or columns are not the same. If not, it makes it impossible to add together
    if ((*firstOne).getNoRows() == (*secondOne).getNoRows() && (*firstOne).getNoCols() == (*secondOne).getNoCols()) { 
        temp = ((*firstOne).Add(*secondOne));                                               
    }
    else {
        cout << "Matrix addition is not possible" << endl;
    }
    
    // condition is for if the firstOne's row is equal to secondOne's column. If not, it makes it impossible to multiply
    cout << "Matrix Multiplication Result" << endl;
    if ((*firstOne).getNoCols() == (*secondOne).getNoRows()) {
        temp = ((*firstOne).Multiply(*secondOne));
    }
    else {
        cout << "Matrix multiplication is not possible" << endl;
    }
}