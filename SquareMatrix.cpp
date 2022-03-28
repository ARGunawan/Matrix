#include "SquareMatrix.h"
#include <array>
#include <iostream>
using namespace std;

template<class T>
SquareMatrix<T>::SquareMatrix() // default constructor
{   matrixsize_ = 0; //set default size at 0 
    array_memory = nullptr; //sets the head of the pointer at 0 as the default
    array_memory = new T* [matrixsize_]; //Use double pointer to allocate the pointer to 2d array to the size of the matrix

    for(int i = 0; i < matrixsize_; i++) //For loop to run through the matrix
    {
        array_memory[i] = new T [matrixsize_]; //This allocates the pointer of the matrix into the new matrix size
    }
}

template<class T>
SquareMatrix<T>::~SquareMatrix() //destructor 
{
    if(array_memory == nullptr) //if the pointer is pointed at null
    {
        exit; //exit the function and cancel
    }    
    else //otherwise, using a for loop to scan through the size of the matrix and delete the pointer to free up space
    {
        for(int i = 0; i < matrixsize_; i++)
    {
        delete[] array_memory[i];
    }
        delete[] array_memory; //deletes the pointer once more for deallocation
    }
}

//copy constructor
//Matrix is allocated to matrixsize_ to get the size of the matrix
//array_memory is the pointer that will obtain the new size of the matrix
template<class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T> & Matrix): matrixsize_(Matrix.matrixsize_), array_memory(new T* [matrixsize_]) 
{
    for(int i = 0; i < matrixsize_; i++) //for loop to run through the size of matrix
    {
        array_memory[i] = new T[matrixsize_]; //have the pointer be pointed to the new matrix
        for(int j = 0; j < matrixsize_; j++) //nested for loop to run through the elements for row and columns
        {
            array_memory[i][j] = Matrix.array_memory[i][j]; //have elements from the two matrices in the 2d array
        }
    }
}

//move constructor which causes the function the data onto the heap without copying
//Once again Matrix is set to the size of the matrix
//the pointer/array_memory is pointed to the matrix
//the size of the matrix is then set to 0 and the pointer set to nullptr.
template<class T>
SquareMatrix<T>::SquareMatrix(SquareMatrix && Matrix): matrixsize_(Matrix.matrixsize_),array_memory(Matrix.array_memory)
{
    Matrix.matrixsize_ = 0;
    Matrix.array_memory = nullptr;
}

//copy assignment will check for equality
template<class T>
SquareMatrix<T> &SquareMatrix<T>::operator=(const SquareMatrix &Matrix)
{
    if(this == &Matrix) //if the original matrix (this), matches the address of the new matrix exit the program
    {
        exit;
    }
    else //otherwise if the old matrix does not match the address
    {
        if(array_memory != nullptr) //if the pointer is not null
        {
            for(int i = 0; i < matrixsize_; i++) //run the for loop for the size of the matrix
            {
                delete[] array_memory[i]; //delete the pointer within the matrix 
            }
        delete[] array_memory; //deletes to free up space
        }

    matrixsize_ = Matrix.matrixsize_; //set the size of the new matrix
    array_memory = new T* [matrixsize_]; //allocate the pointer to said new matrix

    for(int i = 0; i < matrixsize_; i++) //run a for loop to check the size of the matrix
    {
        array_memory[i] = new T [matrixsize_]; //the pointer of the new matrix gets allocated to it
        for(int j = 0; j < matrixsize_; j++) //create another for loop to run throught the size of the matrix
        {
            array_memory[i][j] = Matrix.array_memory[i][j]; //have the contents of both matrix size be allocated to pointers
        } //this will make sure that the matrix pointer values are equal
    }
    }
    return *this; //return the matrix value
}

//move assignment will check if what is being passed in the parameters are equal
template<class T>
SquareMatrix<T> &SquareMatrix<T>::operator=(SquareMatrix &&Matrix)
{
   if(this == &Matrix) //checks if the original matrix is equal to the address of the current matrix
    {
        exit; //exits the program if the conditions are met
    }
    else //Otherwise run through the else statement
    {
        if(array_memory != nullptr) //if the pointer is not null run a for loop
        {
            for(int i = 0; i < matrixsize_; i++)
            {
                delete[] array_memory[i]; //this once again will prevent memory leaks
            }
            delete[] array_memory; //prevents memory leaks
        }
        matrixsize_ = Matrix.matrixsize_; //sets the size of the Matrix to check for equality
        array_memory = Matrix.array_memory; //sets the pointer of the Matrix to check for equality again
        Matrix.matrixsize_ = 0; //sets size to 0
        Matrix.array_memory = nullptr; //sets pointer to null
    }
    return *this;//returns the matrix value
}


template<class T>
int SquareMatrix<T>::size() const //size function to return the size of the matrix
{
    return matrixsize_; 
}

//This function will check for the equality of the square matrix
template<class T>
bool SquareMatrix<T>::operator==(const SquareMatrix &Matrix_A) const
{

    if(Matrix_A.matrixsize_ != matrixsize_) //if the size of matrix A does not return the same size return false
    {
        return false;
    }

    else //otherwise use a nested for loop to run through said matrix
    {
        for(int i = 0; i < matrixsize_; i++)
        {
            for(int j = 0; j < matrixsize_; j++)
            {
                if(array_memory[i][j] != Matrix_A.array_memory[i][j]) //if the pointers from the matrix and Matrix are not equal return false
                {
                    return false;
                }
            }
        }
        return true; //otherwise true
    }
}

//Purpose is to add for the two matrices together
template <class T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix &Matrix_A)
{
    SquareMatrix<int> Matrix_C; //we create a datatype such that the third matrix called Matrix_C is intiliazed within the function
    Matrix_C.resize(matrixsize_); //We have C set to the size of the matrix to be resized

//create a nested for loop so that the pointers from Matrix C is equal to the first two matrices being added to get the sum of their elements
    for(int i = 0; i < matrixsize_; i++)
    {
        for(int j = 0; j < matrixsize_; j++)
        {
            Matrix_C.array_memory[i][j] = array_memory[i][j] + Matrix_A.array_memory[i][j];
        }
    }
    return Matrix_C; //then finally return the matrix
}

//Purpose is to allocate the rows and columns of the matrices
template<class T>
T& SquareMatrix<T>::at(int row, int column)
{
    //create a nested for loop to run through the size of the matrix
    for(int i = 0; i < matrixsize_; i++)
    {
        for(int j = 0; j < matrixsize_; j++)
        {
            if((row < matrixsize_ && column < matrixsize_) && (row >= 0 && column >= 0))
            //if the row & column is less than the size AND the row & column are greater than or equal to 0 return those values
        {
            return array_memory[row][column];
        }
        else //else use throw std::out_of_range("error") to show that those values are out of the matrix boundaries
        {
            throw std::out_of_range("error");
        }
        }
    }
}

//The purpose of this function is to reformat the size of the matrix 
template<class T> 
void SquareMatrix<T>::resize(int new_size)
{
    //create a for loop to run through the sizes of the matrix
    for(int i = 0; i < matrixsize_; i++)
    {
        delete[] array_memory[i]; //delete the pointers of the elements to free up space and prevent memory leaks
    }

    delete[] array_memory; //prevent the memory leak once more
    array_memory = new T*[new_size]; //allocate the pointers to the matrix size

    for(int i = 0; i < new_size; i++)//use another for loop to run through the new size of the matrix
    { 
        array_memory[i] = new T[new_size]; //the pointers will now be allocated to the new matrix 
    }
    
    matrixsize_ = new_size;// set the the size to be the new size of the matrix as it has been resized
}

