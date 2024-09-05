#include <iostream>
#include <vector>
using namespace std;

/*
 * The class SparseRow is meant to show what values are inside the matrix.
 */

//define all your classes here (as given above)
class SparseRow {
    protected:
        int row; //Row#
        int col; //Column#
        int value; //We will assume that all our values will be integer;

    public:
        SparseRow (); //default constructor; row=-1;col=-1;value=0
        void display(); // print Row#, Column#, value
        friend ostream& operator<< (ostream& s, const SparseRow& p) {
            if (!(p.row == -1) && !(p.col == -1)) {
                s << p.row << ", " << p.col << endl;
            }
                return s;
        }
        
    //other methods that are necessary such as get and set
        SparseRow(int r, int c, int v);
        int getRow();
        int getCol();
        int getValue();
        void setRowCol(int r, int c);
};

/* SparseRow()
 * This is a default constructor that assigns all instance values of row and col to -1 and value to 0. 
 */
SparseRow::SparseRow() {
    row = -1;
    col = -1;
    value = 0;
}

/* SparseRow(int r, int c, int v)
 * This constructor is needed so that a value can be set to or receive from a spot on the 
 * matrix, and it gives values that the method display() can give that is not -1.
 * r - rows
 * c - columns
 * v - value 
 */
SparseRow::SparseRow(int r, int c, int v) {
    row = r;
    col = c;
    value = v;
}

/* display()
 * This method's purpose is to show what row and column a non-common value is in.
 */
void SparseRow::display() {
    cout << row << ", " << col << ", " << value << endl;
}

/* getRow()
 * Returns row
 */
int SparseRow::getRow() {

    return row;
}

/* getCol()
 * Returns col
 */
int SparseRow::getCol() {

    return col;
}

/* getValue()
 * Returns value
 */
int SparseRow::getValue() {

    return value;
}

/* setRolCol(int row, int col)
 * Sets the row and column values
 */
void SparseRow::setRowCol(int r, int c) {
    row = r;
    col = c;
}

/*
 * The SparseMatrix class is meant to create and manipulate a matrix.
 */
class SparseMatrix {
    protected:
        int noRows; //Number of rows of the original matrix
        int noCols; //Number of columns of the original matrix
        int commonValue; //read from input
        int noNonSparseValues; // number of non common values
        SparseRow* myMatrix; //Array
    public:
        SparseMatrix ();
        SparseMatrix (int n, int m, int cv);
        SparseMatrix* Transpose (); //Matrix Transpose
        SparseMatrix* Multiply (SparseMatrix& M);
        SparseMatrix* Addition (SparseMatrix& M);
        friend ostream& operator<< (ostream& s, const SparseMatrix& sm);
        void displayMatrix (); //Display the matrix in its original format
        
    //other methods that are necessary such as get and set
        SparseMatrix(int n, int m, int cv, int noNSV); // assigns values to all instance variabels

        std::vector<SparseRow> all; // stores all of the values
        vector<SparseRow> storeAllValues(); // method stores all of the values into the all vector

        std::vector<SparseRow> nonCommonValues; // holds all of the uncommon values in an array that includes the row, col, and value
        vector<SparseRow> storeNonCommonValues(); // by going through the all vector and finding non common values it will add it to the vector

        void displaySparseMatrix();
        int getNoRows();
        int getNoCols();
};

ostream& operator<< (ostream& s, const SparseMatrix& sm) {
    s << sm.noRows << " " << sm.noCols << endl;
    return s;
}
/* SparseMatrix()
 * This is the default construtor that sets noRows, noCols, and commonValue to a default value. 
 * I used -1 for rows and cols because you cannot have a negative amount of rows. I used 
 * NULL for commonValue because it can be anything, so the variable having no value is best.
 */
SparseMatrix::SparseMatrix() {
    int noRows = -1;
    int noCols = -1;
    int commonValue = 0;
}

/* SparseMatrix(int n, int m, int cv)
 * This constructor creates the format of the matrix.
 * n - the number of rows
 * m - the number of columns
 * cv - the common value
 */
SparseMatrix::SparseMatrix (int n, int m, int cv) {
    noRows = n;
    noCols = m;
    commonValue = cv;
}

/* SparseMatrix(int n, int m, int cv, int noNSV)
 * Unlike the previous one, this constructor says the amount of non-commonValues to store
 * n - the number of rows
 * m - the number of columns
 * cv - the common value
 * noNSV - the amount of non-common values
 */
SparseMatrix::SparseMatrix(int n, int m, int cv, int noNSV) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
}

/* displaySparseMatrix()
 * This method displays the values that are not the commonValue.
 * We can do this with a for loop that goes through the vector
 */
void SparseMatrix:: displaySparseMatrix() {
    for (int i = 0; i < noNonSparseValues; ++i) {
        cout << nonCommonValues.at(i).getRow() << ", " << nonCommonValues.at(i).getCol() << ", " << nonCommonValues.at(i).getValue() << endl;
    }
} 

/* storeAllValues()
 * Stores all of the read values into the all vector
 * Searched "in c++, why does it say "no matching member function for call to 'push_back'""
 */
vector<SparseRow> SparseMatrix::storeAllValues() {
// Outer for loop goes through every row
    int value;
    for (int a = 0; a < noRows; ++a) {     
// Inner for loop goes through every values or row (column)
        for (int b = 0; b < noCols; ++b) {
            cin >> value;
            myMatrix = new SparseRow(a, b, value);
            all.push_back(*myMatrix);
        }
    }
    return all;
}

/* storeNonCommonValues()
 * Function goes through every element in all vector and finds the nonCommonValue, then adds it
 * Searched "in c++, why does it say "no matching member function for call to 'push_back'""
 */
vector<SparseRow> SparseMatrix::storeNonCommonValues() {
    int index = 0; // to go through all of the elements in the all vector
// Outer for loop goes through every row of all vector
    for (int c = 0; c < noRows; ++c) {
// Inner for loop goes through every row's value (column)
        for (int d = 0; d < noCols; ++d) {
            if (all.at(index).getValue() != commonValue) {
                myMatrix = new SparseRow(c, d, all.at(index).getValue());
                nonCommonValues.push_back(*myMatrix);
            }
            index++;
        }
    }
    return nonCommonValues;
}

/* Transpose()
 * This method swtiches the values of rows and columns of the non common values. 
 * Simply, it is a copy of the displaySparseMatrix, but we are just switching the variables
 * of rows and columns.
 * Issues - When the main calls the transpose method, it prints out the noRow and noColumn 
 * values, so I need to figure out why it does that.
 * Solution - Instead of just printing out the swapped variables, I created a new object of SparseMatrix and SparseRow.
 */
SparseMatrix* SparseMatrix:: Transpose() {
    SparseMatrix* tempVector = new SparseMatrix(); // the new transposed matrix that is going to be returned
    SparseRow* temp; // swaps the row and col values
// For loop goes through every element of nonCommonValues vector
    for (int i = 0; i < (*this).nonCommonValues.size(); ++i) {
// Swapping the places of rows and columns and putting into the new object then adding it to the vector
        temp = new SparseRow((*this).nonCommonValues.at(i).getCol(), (*this).nonCommonValues.at(i).getRow(), (*this).nonCommonValues.at(i).getValue());
        (*tempVector).nonCommonValues.push_back(*temp);
    }

    // prints transposed
    for (int j = 0; j < (*tempVector).nonCommonValues.size(); ++j) {
        cout << (*tempVector).nonCommonValues.at(j).getRow() << ", " << (*tempVector).nonCommonValues.at(j).getCol() << ", " << (*tempVector).nonCommonValues.at(j).getValue() << endl;
    } 

    return tempVector;
}

/* Multiply (SparseMatrix& M) 
 * Multiplies the va
 */
SparseMatrix* SparseMatrix::Multiply (SparseMatrix& M) {
    SparseMatrix* product = new SparseMatrix();
    SparseRow* element; // creates a spot of the matrix, in which we can add to product's all vector
    int dotProduct; // the value that will be put into product's all vector 
    int colIndex = 0; //changes the column to multiply matric
    int ind = 0; // goes throguh the entire all vector
    int c; // declared here so that it can be accessed by constructor
    int b; // declared here so that it can be accessed by constructor
    int arrayIndex; // variable to repeatedly go through the array

// For loop finds all of the elements of the multiplied matrix
    for (int a = 0; a < ((*this).getNoRows()); ++a) {
        int values[M.getNoRows()];
// For loop goes through each row in puts every value in that row into an array
        for (int i = 0; i < M.getNoRows(); i++) {
            values[i] = (*this).all.at(ind).getValue(); // puts values of row into array
            ind++; // increments ind to access the rest of the other values
        }
    colIndex = 0; // resets
// For loop inserts the value for each row spot in new matrix
        for (b = 0; b < (*this).getNoCols(); ++b) {
            dotProduct = 0; // resets dotproduct
            arrayIndex = 0; // resets arrayIndex so that it can repeatedly go through the array
// For loop finds dot product            
            for (c = 0; c < M.all.size(); c += M.getNoCols()) {
                dotProduct += (values[arrayIndex] * M.all.at(colIndex + c).getValue()); // finds dot product
                arrayIndex++; // goes through array
            }
            element = new SparseRow(a, b, dotProduct); // creates SparseRow object
            (*product).all.push_back(*element); // adds object ot the all vector
            colIndex++; //
        }
    }
    
    int index = 0; // goes through the all vector
    // Outer for loop prints the row
    for (int i = 0; i < M.getNoRows(); ++i) {
    // Inner for loop prints the values of the row (column)
            for (int j = 0; j < M.getNoCols(); ++j) {
                cout << (*product).all.at(index).getValue() << " ";
                ++index;
            }      
            cout << endl; 
    } 

    return product;
}

/* Add (SparseMatrix& M) 
 * Adds the aligning values together into one main matrix
 * M - the first SparseMatrix
 */
SparseMatrix* SparseMatrix::Addition(SparseMatrix& M) {
    SparseMatrix* temp = new SparseMatrix(); // temporary object, returns value
    int value;
    int index = 0; // goes through all of the values
//For loop goes through the firstOne object
    for (int i = 0; i < M.getNoRows(); ++i) { // goes through every row of firstOne object
//Inner for loop goes through the secondOne object
        for (int j = 0; j < M.getNoCols(); ++j) { // goes through every row's value (columns)
            value = (*this).all.at(index).getValue() + M.all.at(index).getValue(); // adds up the values
            myMatrix = new SparseRow(i, j, value); // creates variable with respected position and added values
            (*temp).all.push_back(*myMatrix); // adds it to vector
            ++index;
        }
    }

   int element = 0; // goes through the all vector
// Outer for loop prints the row
   for (int i = 0; i < M.getNoRows(); ++i) {
// Inner for loop prints the values of the row (column)
        for (int j = 0; j < M.getNoCols(); ++j) {
            cout << (*temp).all.at(element).getValue() << " ";
            ++element;
        }      
        cout << endl; 
    } 

    return temp;
}

/* displayMatrix ()
 * This method displays the matrix in a matrix format.
 * Using a nested for loop will make this happen.
 */
void SparseMatrix::displayMatrix() {
    int index = 0; // goes through the all vector
// Outer for loop prints the row
    for (int i = 0; i < getNoRows(); ++i) {
// Inner for loop prints the values of the row (column)
        for (int j = 0; j < getNoCols(); ++j) {
            cout << all.at(index).getValue() << " ";
            ++index;
        }      
        cout << endl; 
    }
}

int SparseMatrix::getNoRows() {
    
    return noRows;
}
int SparseMatrix::getNoCols() {
    return noCols;
}

//write the methods after the class definition
int main () {
    int n, m, cv, noNSV;
    SparseMatrix* temp;

    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
//Write the Statements to read in the first matrix
    (*firstOne).storeAllValues();
    (*firstOne).storeNonCommonValues();
   
    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);

//Write the Statements to read in the second matrix
/* I can check these statements and the functions by putting the input.txt in the folder and
 * checking if the output matches with the output file.
 */
    (*secondOne).storeAllValues();
    (*secondOne).storeNonCommonValues();

    cout << "First one in sparse matrix format" << endl;
    (*firstOne).displaySparseMatrix();

    cout << "After transpose" << endl;
    ((*firstOne).Transpose());

    cout << "First one in matrix format" << endl;
    (*firstOne).displayMatrix();

    cout << "Second one in sparse matrix format" << endl;
    (*secondOne).displaySparseMatrix();

    cout << "After transpose" << endl;
    ((*secondOne).Transpose());

    cout << "Second one in matrix format" << endl;
    (*secondOne).displayMatrix();

    cout << "Matrix Addition Result" << endl;
    if ((*firstOne).getNoRows() == (*secondOne).getNoRows() && (*firstOne).getNoCols() == (*secondOne).getNoCols()) {
        temp = ((*firstOne).Addition(*secondOne));
    }
    else {
        cout << "Matrix addition is not possible" << endl;
    }

    cout << "Matrix Multiplication Result" << endl;
    if ((*firstOne).getNoCols() == (*secondOne).getNoRows()) {
        temp = ((*firstOne).Multiply(*secondOne));
    }
    else {
        cout << "Matrix multiplication is not possible" << endl;
    }

};