#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <random>
#include <chrono>

using namespace std;


// overloading: same functions name with different parameters
/*
int maximum(int a, int b)
{
    return a > b ? a : b;
}

int maximum(double a, double b)
{
    return a > b ? a : b;
}


// function template

// see more http://www.cplusplus.com/doc/oldtutorial/templates/
template <class Type>
Type maximum(Type a, Type b)
{
    Type ret = a > b ? a : b;
    return ret;
}


// multiple types -> function template
template <class Type_1, class Type_2>
Type_1 maximum(Type_1 a, Type_2 b)
{
    Type_1 ret = a > b ? a : b;
    return ret;
}


int f1()
{
    int iCount = 1;
    cout<<iCount<<"\n";
    ++iCount;
}

int f2()
{
    static int iCount = 1;
    cout<<iCount<<"\n";
    ++iCount;
}

int iVar = 5;   // global variable

int f()
{
    int iVar = 8;   // local varivale
    cout<<iVar<<" "<<::iVar<<"\n";
}


// Pass by value and reference:

// a passed by value .. caller don't feel changes
// b passed by reference .. caller feel its changes
int f(int a, int &b)
{
    cout<<a<<" "<<b<<"\n";

    ++a;    b++;
}



// inline function:

// inline: Don't create actual function. Copy code to caller in compile time
// see more https://www.geeksforgeeks.org/inline-functions-cpp/
// see more https://en.cppreference.com/w/cpp/language/constexpr
inline int maximum(int a, int b)
{
    return a > b ? a : b;
}

// see more here about recursion: https://www.youtube.com/watch?v=hyk46UmJPS4&t=1s
// see more here also: https://www.youtube.com/playlist?list=PLPt2dINI2MIYmHYBSEdkdKMf_3nzFMveo

// built-in functioins see more here: https://www.cprogramming.com/function.html
// header files: see more here: https://www.tutorialspoint.com/cprogramming/c_header_files

int factorial(int n)
{
    if(n == 1)
        return 1;
    return n * factorial(n-1);
}



// Profissionally documentation for a function:
// /-*
//  * Read employee data scale its salary using a given factor.
//  *
//  * slarayFactor - IN: factor to divide salary over it.
//  * salary - OUT: the computed salary using input and salaryFactor.
//  * name - OUT: the Concatenated name( first <space> last).
//  *
//  * Return bool: True if read & calcualte correctly. false otherwise.
//  *-/
bool readData(int salaryFactor, double& salary, double& name)
{
    string firstName, secondName;

    cin>>firstName;
    cin>>secondName;
    cin>>salary;

    if(cin.fail() || salaryFactor == 0)
        return false;
    salary/=salaryFactor;
    return true;
}


int getMax(int arr[], int size)
{
    int maxValue = arr[0];
    for(int i = 1; i < size; i++)
        if(maxValue < arr[i])
            maxValue = arr[i];
    return maxValue;
}


int get2Max(int arr[], int size)
{
    assert(size >= 2);  // Note: array size MUST be >= 2. Assert: crash the program if failed

    int fstMax = arr[0], secMax = arr[1];   // initially wrong :) but this how the algorithm works

    if(fstMax < secMax)
        swap(fstMax, secMax);   // swap is a function to swap content of 2 numbers

    for(int i = 2; i< size; i++)    // start from 3rd element
    {
        if(fstMax < arr[i]) // get in it if the new element is bigger than the first max
        {
            secMax = fstMax;    // here we put the new element into the first max and replace the second max with the first max
            fstMax = arr[i];
        }
        else if(secMax < arr[i])    // get in it if the new element is bigger than the second max
            secMax = arr[i];
        else;   // it is only for the new element which is not bigger than both first and second max and we simply skip this new element
    }
    return secMax;
}


// Test 2nd Maximum in Array:

void Test_get2ndMax()
{
    const int SIZE = 10;
    int arr[SIZE];

    for(int i = 0; i < 1000; i++)
    {
        for(int i = 0; i < SIZE; i++)
            arr[i] = (rand() % 100);

        int myAnswer = get2Max(arr, SIZE);

        sort(arr, arr+SIZE);

        int correctAnswer = arr[SIZE-2];

        assert(correctAnswer == myAnswer);
    }
    cout<<"PERFECT\n";
}


void reverseInplace(int arr[], int SIZE)
{
    // In-place algorithm: only use some constants.. don't create new arrays
    // e.g. don't create new array..copy data reversed to it
    // change in the given array itself

    // idea..swap indices: (1st, last) (2nd, 2nd last)
    for(int i = 0; i < SIZE/2; i++)
        swap(arr[i],arr[SIZE-i-1]);
}

void printArr(int arr[], int SIZE)
{
    for(int i = 0; i < SIZE; i++)
        cout<<arr[i]<<" ";
    cout<<"\n";
}

void TestReverseInplace()
{
    const int SIZE = 7;
    int arr[SIZE];
    int cpy[SIZE];

    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j < SIZE; j++)
            arr[j] = cpy[j] = rand() % 100;

        reverseInplace(arr, SIZE);

        reverse(arr, arr+SIZE);

        for(int j = 0; j < SIZE; j++)
            assert(arr[j] == cpy[j]);
    }
    cout<<"PERFECT\n";
}

// test even and odd size of array
void TestReverseInplace()
{
    const int SIZE = 7;
    int arr[SIZE];
    int cpy[SIZE];

    int usedSize = SIZE;
    for(int k = 0; k < 2; k++)
    {
        for(int i = 0; i < 1000; i++)
        {
            for(int j = 0; j < SIZE; j++)
                arr[j] = cpy[j] = rand() % 100;

            reverseInplace(arr, SIZE);

            reverse(arr, arr+SIZE);

            for(int j = 0; j < SIZE; j++)
                assert(arr[j] == cpy[j]);
        }
        cout<<"PERFECT\n";
        usedSize--;
    }

}


// Sliding window Maximum, Algorithm 1: size xk operations
int slidingWindowMax(int arr[], int SIZE, int k)
{
    int Max = 0;

    for(int i = 0; i < (SIZE - k + 1); i++)
    {
        int sum = 0;
        for(int win = 0; win < k; win++)
            sum+= arr[i+win];


        if(i == 0 || sum > Max)
            Max = sum;
    }
    return Max;
}

int slidingWindowMax(int arr[], int SIZE, int k)
{
    int maxWindow = 0;

    for(int win = 0; win < k; win++)
        maxWindow += arr[win];

    int sum = maxWindow;
    for(int i = 1; i < SIZE - k + 1; i++)
    {
        sum = sum - arr[i-1] + arr[i+k-1];
        maxWindow = max(maxWindow, sum);
    }
    return maxWindow;
}


// Insertion sort (Incremental thinking)
void insertionSort(int arr[], int SIZE)
{
    for(int i = 1; i < SIZE; i++)
    {
        int cpy = arr[i];
        int j = i-1;

        for(; j >= 0; j--)
        {
            if(cpy > arr[j])
                break;
            arr[j+1] = arr[j]; //shift
        }
        arr[j+1] = cpy;
    }
}


// Test intsertion sorting
// flush what and why see more: https://stackoverflow.com/questions/14105650/how-does-stdflush-work/14107357#14107357

void TestInsertionSorting()
{
    int SIZE = 3;
    int arr[SIZE];
    int cpy[SIZE];
    int tmp[SIZE];

    for(int test = 0; test < 1000; test++)
    {
        cout<<"TEST #"<<test+1<<"\n"<<flush;

        for(int i = 0; i < SIZE; i++)
            arr[i] = cpy[i] = tmp[i] = rand() % 100;

        insertionSort(arr, SIZE);

        sort(cpy, cpy+SIZE);

        bool passed = true;

        for(int i = 0; i < SIZE; i++)
            passed &= (arr[i] == cpy[i]);   // this & operator is to remain the false value if we face any false result
                                            // like we know about logic gates false & true = false
                                            // so if one of the results was false it will remain false
                                            // becase any true after that && with the previous false will get us false everytime.

        if(!passed)
        {
            for(int i = 0; i < SIZE; i++)
                cout<<tmp[i]<<" "<<flush;
            assert(false);
        }
    }
    cout<<"PERFECT";
}

void merge2SortedArrays(int sorted1[],int sz1, int sorted2[], int sz2, int result[], int sz3)
{
    int idx1 = 0;
    int idx2 = 0;
    int res = 0;

    while(idx1 < sz1 && idx2 < sz2)
    {
        if(sorted1[idx1] < sorted2[idx2])
            result[res++] = sorted1[idx1++];
        else
            result[res++] = sorted2[idx2++];
    }

    while(idx1 < sz1)
        result[res++] = sorted1[idx1++];

    while(idx2 < sz2)
        result[res++] = sorted2[idx2++];
}

void testMerge2SortedArrays()
{
    const int SIZE1 = 5;
    const int SIZE2 = 3;
    const int RES_SIZE = 8;

    int sorted1[SIZE1];
    int sorted2[SIZE2];
    int result[RES_SIZE];
    int cp_result[RES_SIZE];

    for(int test = 0; test < 1000; test++){
        for(int i = 0; i < SIZE1; i++)
            sorted1[i] = random() % 100;

        sort(sorted1, sorted1+SIZE1);

        for(int i = 0; i < SIZE2; i++)
            sorted2[i] = random() % 100;

        sort(sorted2, sorted2+SIZE2);

        merge2SortedArrays(sorted1, SIZE1, sorted2, SIZE2, result, RES_SIZE);
        merge(sorted1, sorted1+SIZE1, sorted2, sorted2+SIZE2, cp_result);


        for(int i = 0; i < RES_SIZE; i++)
            assert(result[i] == cp_result[i]);
    }
    cout<<"PERFECT";

}


// ASCII code see more: http://www.asciitable.com/
// type name see more: http://www.cplusplus.com/reference/typeinfo/type_info/name/
// Strings manipulation see more: https://cal-linux.com/tutorials/strings.html

// other sol. see more: http://www.cplusplus.com/reference/cstdlib/atoi/
int charToInt(string str)
{
    // This program accepts only positve intigers
    // check if there is any chars than digits 0-9
    for(int i = 0; i < str.length(); i++)
        assert(int(str[i]) <= 57 && int(str[i] >= 48));

    // discard any zeros at leftside
    int j = 0;
    for(; str[j] == '0'; j++);

    // converting to int using ASCII code
    int result = int(str[j++]) - '0';

    // converting the nr. digit by digit by mutliply every digit with 10 and add it to the previous result
    while(j < str.length())
    {
        result = result * 10 + (int(str[j++]) - '0');

    }

    return result;

}

bool findCharInString(string str, char ch)
{
    // string find in C++ codes
    // see more: https://stackoverflow.com/questions/24957965/comparing-strings-c/24958019
    // see more: http://www.cplusplus.com/reference/string/string/find/
    bool found = false;
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == ch)
            found = true;
    }
    return found;
}
// Version 2 (Working)
// other emplementation see more: https://www.geeksforgeeks.org/group-multiple-occurrence-of-array-elements-ordered-by-first-occurrence/
// about returning arrays from functions see more: https://www.tutorialspoint.com/cplusplus/cpp_return_arrays_from_functions
// appending in a string and + operator  see more: http://www.cplusplus.com/reference/string/string/operator+/
//                                       see more: https://www.geeksforgeeks.org/stdstringappend-in-c/
//                                       see more: https://www.tutorialspoint.com/cpp_standard_library/cpp_string_append
//Add space to a string                  see more: https://stackoverflow.com/questions/20391415/c-adding-spaces-to-string
//                                       see more: http://www.cplusplus.com/forum/general/225314/
string groupingString(string str)
{
    int e = 0;
    int c = 0;
    string new_str;



    while(e < str.length())
    {
        if(!findCharInString(new_str, str[e]))
        {
            char element_grp = str[e];
            for(int i = e; i < str.length(); i++)
            {
                if(element_grp == str[i])
                {
                    new_str+=str[i];
                }
            }
            new_str+=" ";
            c++;
        }
        e++;

    }
    return new_str;
}
/*
// Version 1 (not Working)
string groupingString(string str)
{
    int e = 0;
    int c = 0;

    while(e < str.length())
    {
        char element_grp = str[e++];

        for(int i = e; i < str.length(); i++)
        {
            if(element_grp == str[i])
            {


                int temp = str[e];
                str[e++] = str[i];
                str[i] = temp;
            }
        }
        c++;
    }
    return str;

    string strGrp[c+1];
    int k = 0;

    for(int i = 0; i < c+1; i++)
    {
        int j = 0;
        char tmp = str[k++];

        while(tmp == str[k])
            strGrp[i][j++] = str[k++];
    }

    strGrp[c] = "\0";

    return strGrp;

}
/*

int compare2Str(string str1,int SIZE_1, string str2,int SIZE_2)
{
    // compareing 2 strings other code
    // see more: https://stackoverflow.com/questions/24957965/comparing-strings-c/24958019
    // Define var to hold the small size of the 2 strings
    int SIZE_SMALLER = 0;   // Declare and initialize it with 0

    // Assign the smallest size to SIZE_SMALLER var
    if(SIZE_1 > SIZE_2)
        SIZE_SMALLER = SIZE_2;
    else
        SIZE_SMALLER = SIZE_1;

    // in case one of the 2 strings are empty
    if(str1.length() == 0 || str2.length() == 0)
    {
        if(str1.length() < str2.length())
            return -1;
        else if (str1.length() > str2.length())
                return 1;
        else
            return 0;
    }

    // looping to the smallest size
    for(int i = 0; i < SIZE_SMALLER; i++)
    {
        // here check if the chars of the 2 strings are the same but we don't reached the
        if(str1[i] == str2[i] && (i+1) < SIZE_SMALLER)
            continue;

        // check if str1 char < str2 char and return -1
        if(str1[i] < str2[i])
            return -1;
        // check if str1 char > str2 char and return 1
        else if(str1[i] > str2[i])
                return 1;
        // here str1 char = str2  char but return 0 only if the are the same size
        else if(SIZE_1 == SIZE_2)
                return 0;
        // here str1 char = str2 char but they are not the same size
        else
        {
            // return -1 if str1 size is smaller than str2 size
            if(SIZE_1 < SIZE_2)
                return -1;
            // return 1 if str1 size is bigger than str2 size
            else
                return 1;
        }
    }

}

void TestCompare2Strings()
{
    // generate a random String of a given size
    // see more: https://www.geeksforgeeks.org/generate-random-string-of-given-size-in-java/
    //
    string CharIntString = "abcdefghijklmnopqrstuvwxyz0123456789";

    for(int i = 0; i < 1000; i++)
    {
        string str1, str2;
        int size1, size2;

        size1 = random() % 100;
        size2 = random() % 100;

        for(int j = 0; j < size1; j++)
        {
            int index = random() % CharIntString.length();
            str1 += CharIntString[index];
        }

        cout<<str1<<"\n";

        for(int k = 0; k < size2; k++)
        {
            int index = random() % CharIntString.length();
            str2 += CharIntString[index];
        }

        cout<<str2<<"\n";

        // string.compare() function
        // see more: http://www.cplusplus.com/reference/string/string/compare/
        int Result1 = compare2Str(str1, size1, str2, size2);
        int Result2 = str1.compare(str2);

        cout<< Result1<<"\n"<<Result2<<"\n";
        if( (Result1 < 0 && Result2 < 0) || (Result1 > 0 && Result2 > 0) || (Result1 == 0 && Result2 == 0) )
            assert(true);
        else
            assert(false);
    }
    cout<<"Perfect\n";
}
string Substrings(string str, int SIZE)
{
    int sum = 0;
    // the nr. of subStrings
    for(int i = 0; i <= SIZE; i++)
        sum += i;

    // adding the nr. of SubStrings into my returning string from this function
    // see more: https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
    string countSubStr = to_string(sum);
    string subStr;
    subStr = "The nr. of SubStrings are: " + countSubStr + "\n";

    // the outer for is to take each char and make subStr to the end of the string
    for(int i = 0; i < SIZE; i++)
    {
        // the inner for is to make each subStr from the given char from the outer
        for(int j = i; j < SIZE; j++)
        {
            // get the previous chars for the given outer loop char
            // string object: http://www.cplusplus.com/reference/string/string/
            for(int k = i; k < j; k++)
                subStr+= str[k];
            // add the last char
            subStr+=str[j];
            subStr = subStr +" ";
        }
        subStr = subStr +"\n";
    }
    return subStr;
}


// check if the string is numbers from 0 to 9
bool isDigitStr(string str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] > 57 || str[i] < 48) // check using the ASCII code boundaries
            return false;
    }
    return true;
}

// check if there is remain or not and return the status by true or false
bool isRemain(int i)
{
    if((i/10) % 10 != 0)
                return true;
            else
                return false;
}

string addLongString(string str1, string str2)
{

    int SIZE1 = str1.length();  // declare var for the string nr.1 size
    int SIZE2 = str2.length();  // declare var for the string nr.2 size
    int nr1 = 0, nr2 = 0;       // declare 2 var for each nr. (char) of our 2 string numbers
    string Result;              // declare the result string

    bool remain = false;        // declare remain var which help us with calculation

    // here we arrange the 2 string numbers so str1 will be the larger and str2 will be the smaller
    if(SIZE1 < SIZE2)
    {
        swap(str1, str2);   // swap the 2 nr. strings
        swap(SIZE1, SIZE2); // swap the size of the 2 nr. strings
    }

    // here we parse each char (number) and add them together
    // considering the remain which may come from the previous calc
    // and considering the different size of the 2 string numbers
    for(int i = 0; i < SIZE1; i++)
    {
        //convert char or string to integer
        //see more: https://stackoverflow.com/questions/37229205/use-of-atoi-function-in-c
        //see more: http://www.cplusplus.com/reference/cstdlib/atoi/
        // assign string see more: http://www.cplusplus.com/reference/string/string/assign/
        //               see more: https://www.geeksforgeeks.org/stdstringassign-in-c/

        // converting the char (number) to integer
        nr1 = str1[SIZE1-1-i] - '0';

        // here we assign 0 to nr.2 if it reached its end
        if(i < SIZE2)
            nr2 = str2[SIZE2-1-i] - '0';
        else
            nr2 = 0;

        // Old try!
        // about sub string see more: http://www.cplusplus.com/reference/string/string/substr/
        //int nr2 = stoi(str1.substr(i,1));

        //cout<<"The 2 numbers we calc now: "nr1<<" "<<nr2<<" ";

        // add the 2 numbers
        int result = nr1 + nr2;

        //cout<<"The result after sum the 2 numbers: - "<<result<<" - ";

        // check if there was remain from the previous calc
        if(remain)
        {
            result++;   // add one
            remain = isRemain(result); // change the remain status considering the current result
        }

        // we do this only at the begining to change the remain status if there is remain from the calc
        if(i == 0)
            remain = isRemain(result);

        //cout<<"The result after sum the remain from previous calc: { "<<result<<" } ";

        // we take the remain from our result out by using mod 10
        // which we add it at the second round
        if(i < SIZE1-1)
            result = result % 10;

        //cout<<"The remain from previous calc: ' "<<remain<<" ' ";
        //cout<<"The result after take the remain away from our calc [ "<<result<<" ] ";
        // concatenate our result as string using a built-in function called to_string()
        // see more: https://stackoverflow.com/questions/16899055/casting-int-to-char-using-c-style-casting
        // see more: https://www.geeksforgeeks.org/converting-string-to-number-and-vice-versa-in-c/
        Result = to_string(result) + Result;

        //cout<<"The final Result as string: ( "<<Result<<" ) || ";


    }
    return Result;
}

// our function return the sum of the given interval in array
int sumQuery(int arr[], int qr1, int qr2)
{
    // we try to keep qr1 the larger nr.
    if(qr1 < qr2)
        swap(qr1, qr2); // swap the content qr1 and qr2

    if(qr1 == qr2) // return the same index because they are the same
        return arr[qr1];
    return arr[qr1] - arr[qr2-1]; // we get the sum of the interval by subtracting the 2 indecies of the sumarr
                                  // but -1 for the start index so we can add also the sart value of the interval
}


bool binarySearch(int arr[], int SIZE, int findNr, int &pos)
{
    // sorting the array first to enable binary search algorithm
    // see more: https://www.geeksforgeeks.org/sort-c-stl/
    sort(arr, arr+SIZE);

    // initialize our vars to start our binary search algorithm
    int top = 0, down = SIZE-1, mid = SIZE/2;
    bool found = false;    // declare check var

    //it will break only if found turned to true
    while(!found)
    {
        // if the nr. we search is not found the 2 indecies (top, down)
        // will acrross each other so the smaller one (top) will be greater than the bigger one (down)
        if( top > down)
            break;
        else if(arr[mid] == findNr) // if our search nr. is found
        {
            found = true;
            pos = mid;
        }
        else if(arr[mid] < findNr) // if mid nr. is smaller than our search nr.
        {
            top = mid + 1;         // we put the top one step after the mid
            mid = (top + down) / 2;// we calculate the new mid
        }
        else                       // if mid nr. is bigger than our search nr.
        {
            down = mid - 1;        // we put the down one step before the mid
            mid = (top + down) / 2;// we calculate the new mid
        }

    }
    return found;
}


// given some nr search in to the array if there are 2 numbers are the sum of this given nr
bool sum2NrInArr(int arr[], int SIZE, int nr, int &arrPos1, int &arrPos2)
{
    int arrNr1 = 0, arrNr2 = 0;
    int mid = SIZE/2;
    int left = 0;
    int right = SIZE-1;
    bool found = false;

    sort(arr, arr+SIZE);



    while(!found && left < right)
    {
        if(arr[mid] < nr && arr[mid] > 0)
        {
            arrNr1 = arr[mid];
            arrNr2 = nr - arr[mid];
            arrPos1 = mid;

            found = binarySearch(arr, SIZE, arrNr2, arrPos2);

            // cout<<"nr1 - "<<arrNr1<<" - \n"<<flush;
            // cout<<"nr2 - "<<arrNr2<<" - \n"<<flush;

            if(!found)
                {
                    if(arrNr1 < arrNr2)
                    {
                        mid++;
                    }
                    else
                    {
                        mid--;
                    }

                }
        }
        else
        {
            if(arr[mid] > nr)
            {
                right = mid - 1;
                mid = (left + right) / 2;
            }else
            {
                left = mid + 1;
                mid = (left + right) / 2;
            }
        }


    }
    return found;
}


void mulArr(int arr[], int SIZE, int nrDigit, int f)
{
    for(int i = 0; i < nrDigit; i++)
    {
        //cout<<"\nbefore Multiply: "<<arr[i]<<"\n";
        arr[i] *= f;
        //cout<<"\nafter Multiply: "<<arr[i]<<" , "<<f<<"\n";
    }   
}
bool isCarry(int c)
{
        if( c / 10 != 0)
        {
            //cout<<"is Carry ";
            return true;
        }
        else
            return false;
}

// calc the factoria of big numbers
// nr of digits of fact 100, see more: https://www.quora.com/How-can-you-count-the-number-of-digits-in-100-factorial
bool bigFac(int fac, int arr[], int SIZE, int &nrDigit)
{
    arr[0] = 1;
    int remain = 0;
    int carryNr = 0;
    int carryPos;
    int factorial = fac;


    if( factorial == 1 || factorial == 0)
        return true;

    if(factorial < 0)
        factorial *= -1;
    // TODO: what is the maximum number of factorial our device can calculate before it crashing down
    // DONE: it is about the size of the array so I don't know exactly its Max capability to caclulate!

    for(int f = 2; f <= factorial; f++)
    {
        mulArr(arr, SIZE, nrDigit, f);
        carryPos = 0;
        // TODO: try -1 as indicator
        // DONE: I used nr. of digits as indicator

        while(carryPos <= (nrDigit-1))
        {
            if(carryPos == (nrDigit-1) && isCarry(arr[carryPos]))
                nrDigit++;

            if( isCarry(arr[carryPos]) )
            {
                carryNr = arr[carryPos]/10;
                //cout<<"Carry nr. "<<carryNr<<" / ";
                remain = arr[carryPos] % 10;
                //cout<<"remain nr."<<remain<<" / \n";

                //cout<<"Pos before taking carry "<<arr[carryPos]<<" | ";
                //cout<<"Pos +1 before sum the carry "<<arr[1+carryPos]<<" || ";
                arr[carryPos] = remain;
                carryPos++;
                arr[carryPos] = arr[carryPos] + carryNr;
                //cout<<"Pos after taking carry "<<arr[1-carryPos]<<" | ";
                //cout<<"Pos after sum the carry "<<arr[carryPos]<<" | \n";
            }
            else
                carryPos++;
        }

        //for(int i = 0; i < SIZE; i++)
          //  cout<<arr[i];
    }
    reverse(arr,arr+nrDigit);
    if(fac < 0)
        arr[0] *= -1;
    return true;
}

bool getPrimeOfRng(bool arr[], int SIZE)
{
    // check if the range is smaller than the first prime nr.
    if(SIZE < 2)
        return false;

    // initialize the first 3 elements
    // cuz' they are fixed
    arr[0] = 0; arr[1] = 0; arr[2] = 1;

    // initialize the array from fourth elemnt to the end to true
    // which can be also represented with '1' value
    for(int i = 3; i < SIZE; i+=2)
        arr[i] = 1;

    // implement sieve algorithm for prime numbers
    for(int i = 3; i < int(sqrt(SIZE)); i+=2)
    {
        // skip if our new iter is false
        // that means that this false value has been updated from 
        // prvious iter. and labled it as non-prime nr.
        // see more: https://www.geeksforgeeks.org/sieve-of-eratosthenes/
        if(arr[i] == 0)
            continue;
        
        // multiply our prime nr. with it self and above
        // untill we reach our range to set all its multipliers to false ('0')
        int result = 0;
        for(int j = i; result < SIZE; j+=2)
        {
            result = i * j;
            arr[result] = 0;
        }
    }
    
    // output our prime numbers
    cout<<2<<"\n";  // we output 2 any way in any range of prime nr.
                    // because its the first prime nr.
    for(int i = 3; i < SIZE; i+=2)
        if(arr[i] == 1)
            cout<<i<<"\n";
    return true;
}


// if I wanna shuffle my array myself:
// see here: https://stackoverflow.com/questions/4111214/c-random-number-generator-without-repeating-numbers/4111273
//           https://en.cppreference.com/w/cpp/numeric/random/srand
//           https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
//           http://www.cplusplus.com/reference/cstdlib/srand/

void generateCycles(int arr[], int SIZE)
{
    // set the values with its indicies
    for(int i = 0; i < SIZE; i++)
        arr[i] = i;

    // shuffling our array values randomly
    // see more: https://www.geeksforgeeks.org/shuffle-vs-random_shuffle-c/
    // see more: https://meetingcpp.com/blog/items/stdrandom_shuffle-is-deprecated.html
    // about removing random_shuffle from c++ 17 
    // see more: https://meetingcpp.com/blog/items/stdrandom_shuffle-is-deprecated.html
    
    // our implementation is from ...
    // see here: https://en.cppreference.com/w/cpp/algorithm/random_shuffle
    // about Random Generators 
    // see here: https://en.wikipedia.org/wiki/Pseudorandom_number_generator

    //random_device rd; // https://en.cppreference.com/w/cpp/numeric/random/random_device
    //mt19937_64 g(rd); //https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
    
    // about rand() and srand() and non-repeating numbers:
    // see here: https://stackoverflow.com/questions/4111214/c-random-number-generator-without-repeating-numbers/4111273
    //           https://en.cppreference.com/w/cpp/numeric/random/srand
    //           https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
    //           http://www.cplusplus.com/reference/cstdlib/srand/
    //           https://en.cppreference.com/w/cpp/numeric/random/srand
    //           https://stackoverflow.com/questions/26786871/randomly-shuffle-c-array-different-each-time

    // about random header file:
    // see here: http://www.cplusplus.com/reference/random/
    //           

    // how to print diferent output each time:
    // see here: https://www.techiedelight.com/shuffle-vector-cpp/
    // about shuffle:
    // see here: http://www.cplusplus.com/reference/algorithm/shuffle/
    //           https://www.geeksforgeeks.org/shuffle-vs-random_shuffle-c/

    // about the random time seed:
    // chrono:
    // see here: http://www.cplusplus.com/reference/chrono/?kw=chrono
    // system_clock:
    // see here: http://www.cplusplus.com/reference/chrono/system_clock/
    // now():
    // see here: http://www.cplusplus.com/reference/chrono/system_clock/now/
    // time_since_epoch()     
    // see here: http://www.cplusplus.com/reference/chrono/time_point/time_since_epoch/
    // count():
    // see here: https://en.cppreference.com/mwiki/index.php?title=Special%3ASearch&search=count%28%29
    //           https://en.cppreference.com/w/cpp/chrono/duration/count
    //           https://stackoverflow.com/questions/21050994/stdchrono-default-duration-for-time-since-epoch
 
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(arr, arr+SIZE, default_random_engine(seed));    
}
// finding the first unvisited index
int findNextCycle(bool arr[], int SIZE)
{   
    int i = 1;
    while(i < SIZE && arr[i])
        i++;

    return i;
}

void printCycles(int arr[], int SIZE)
{
    bool isVisited[SIZE];
    int c = 0;
    //int index = 0; 
    int CycCount = 0;       // declare it to print each cycle permutation nr.
    int stCycle = 0;        // declare it to save the index of the start permutation
    int stNode = 0;         // declare it to assign the start node for each permutation
    int endNode = arr[0];   // declare it to assign the end node for each permutation

    //loop untill reaching the end of our range
    while(c < SIZE)
    {
        // for the end of a cycle and if the start = end 
        if(endNode == stCycle)
        {   
                cout<<stNode<<" -> "<<endNode<<"\n";    // print the permutation
                isVisited[stNode] = true;   // lable it as visited index
                stCycle = findNextCycle(isVisited, SIZE);   // find the next start cycle
                stNode = stCycle;   // assign the start cycle to be also the start node
                endNode = arr[stNode];  // assign the value of then start index to be the end node
                cout<<"Cycle #"<<++CycCount<<"\n\n";    // print the cycle nr. and increment it 
                c++; // increment our count for our while loop

        }else
        {
            cout<<stNode<<" -> "<<endNode<<"\n";    // print the permutation
            isVisited[stNode] = true;   // lable it as visited index
            stNode = endNode; // assign the next start node with the previous end node
            endNode = arr[stNode]; // assign the next end nod with the new start node
            c++;    // increment our count for our while loop
        }        
    }
    
}



int josephusPrb(int N, int K)
{
    int Survived = 0; // declare our survived man var.
    int index = 0;  // declare our killed man index
    bool isKilled[N] = {};  // declare array to hold the state of each man if he isKilled or !isKilled
    
    // Validate our input to prevent <= 0 inputs for both N (nr. of men) K (nr. of turns)
    if(N <= 0 || K <= 0)
    {
        cout<<"Your nr. of men or turns or both is <= 0 !!!\n";
        assert(false);
    }

    // our loop is long as the nr. of men -1 to keep the last one life
    for(int i = 0; i < (N-1); i++)
    {    

            int j = 0;  // we declare our turns iter.
            while(j < K )   // each loop cycle is long as the nr. of turns
            {
                // here we re-assign our index to 0 if it reached the end of the nr. of men
                if(index == N)
                    index = 0;
                // here we only increment our turn if the index of the man status is still life (!isKilled) = 'false'
                if(!isKilled[index])
                    j++;
                // here we kill the man by changing the man statues to (isKilled) = true using our index
                if(j == K)
                    isKilled[index] = true;
                // here we increment our index of the men
                    index++;
            }        
    }
    
    int i = 0;
    for(; i < N; i++)
        if(isKilled[i] == false)
            break;
    Survived = ++i;
    
    return Survived;
}
*/



// TODOs and DONE
// see more: https://stackoverflow.com/questions/9499039/where-does-the-todo-convention-come-from
// see more: https://medium.com/imdoneio/5-ways-using-todo-comments-will-make-you-a-better-programmer-240abd00d9e4
// see more: https://medium.com/imdoneio/the-imdone-pitch-feedback-welcome-386430accf01
int main()
{

    cout<<"Hello world!!!\n";
    cout<<"I am Ahmed \n";


/*
    //-------------------------------------------

    int N; int K;   // declare our nr. of men and nr. of turns
    int survived = 0;   // declare our survived nr. var.   
    bool check = true;  // declare our check validation for input values

    do
    {
        cout<<"Enter your number of Mans: ";
        cin>>N;
        cout<<"Enter the number of turns: ";
        cin>>K;

        // Input validation
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"\n\nPlz enter correct values !!!\n\n";
            check = false;
        }
    }while(!check);
    
    survived = josephusPrb(N,K);
    
    cout<<"The Surviver man nr. is: "<<survived<<"\n";
   
    // --------------------------------------------
    const int SIZE = 10;
    int arr[SIZE];
    
    // generate our random shuffling array
    generateCycles(arr, SIZE);

    // the index output
    for(int i = 0; i < SIZE; i++)
        cout<<i<<" ";
    cout<<"\n";
    
    // output our shuffled array diffrent each time
    for(int i = 0; i < SIZE; i++)
        cout<<arr[i]<<" ";
    cout<<"\n\n";
    
    printCycles(arr, SIZE);


    //----------------------------------------------
    const int SIZE = 1;
    bool arr[SIZE] = {};

    if( getPrimeOfRng(arr, SIZE) );
    else
        cout<<"your range is smaller then 2, plz set your range 2 or above!!!";




    //---------------------------------------------------------------
    const int SIZE = 1000000;
    int arr[SIZE] = {0};
    bool check;
    int fac = 0;
    int nrDigit = 1;
    do{
        cout<<"enter a big fatorial nr. ";
        cin>>fac;

        check = true;
        // input validation
        if(cin.fail())
        {
            cout<<"You should enter correct values!!!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            check = false;
        }
    }while(!check);

    check = bigFac(fac, arr, SIZE, nrDigit);
    if(check)
    {
        cout<<"The factorial "<<fac<<"! = ";
        for(int i = 0; i < nrDigit; i++)
            cout<<arr[i];
        cout<<"\nThe nr of digit of "<<fac<<"! = "<<nrDigit<<"\n";
    }else
    {
        cout<<"Some thing went wrong, please maintain your code!!\n";
    }
    

    const int SIZE = 10;
    int arr[SIZE];
    int pos1 = 0, pos2 = 0;
    int nr = 0;
    bool check;
    bool found;

    do
    {
        check = true;
        cout<<"Enter 10 numbers consecutively: ";
        for(int i = 0; i < SIZE; i++)
        {
            cin>>arr[i];

            // input validation
            if(cin.fail())
            {
                cout<<"Enter correct values !!!\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
                check = false;
                break;
            }
        }
    }while(!check);

    do
    {
        check = true;
        cout<<"Enter a nr. and we find you 2 nr. from the array which there sum equals your nr.: ";
        cin>>nr;

        //input validation
        if(cin.fail())
        {
            cout<<"Enter corrcet values !!!\n\n";
            cin.clear();
            cin.ignore(10000,'\n');
            check = false;
            break;
        }
    }while(!check);

    // about array of refrences and why it is not legal
    // see more: https://stackoverflow.com/questions/1164266/why-are-arrays-of-references-illegal#1164306
    found = sum2NrInArr(arr,SIZE,nr, pos1, pos2);
    if(found)
        cout<<"Found: "<<nr<<" = "<<arr[pos1]<<" + "<<arr[pos2]<<"\n";
    else
        cout<<"The Number "<<nr<<" has no sum of 2 numbers in our array !\n";

    // --------------------------------------------------------------------------------------------------------
    const int SIZE = 10; // declare our size of the array
    int arr[SIZE];
    int pos = 0;         // declare a position which will contain the index of our searching nr. if we found it in the array
    int findNr = 0;      // declare our find nr. which we get it form the usr
    bool check;          // declare check for input validation

    do{
        check = true;
        cout<<"Enter 10 numbers consecutively: ";
        for(int i = 0; i < SIZE; i++)
        {
            cin>>arr[i];

            // input validation
            if(cin.fail())
            {
                cout<<"Enter corrcet values !!!\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
                check = false;
            }
        }
    }while(!check);

    // ----------------------------------------------------------------

    do{
        check = true;
        cout<<"\n Enter the value you want to search in the array: ";
        cin>>findNr;

        // input validation
        if(cin.fail())
        {
            cout<<"Enter corrcet values !!!\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
            check = false;
        }
    }while(!check);

    bool found = binarySearch(arr, SIZE, findNr, pos); // declare found which take the binary search result

    // if the found var is true then we found the nr.
    if(found)
        cout<<"The nr. "<<findNr<<" is found in the array, and it's position is: "<<pos<<"\n";
    //if not then we didn't find the nr.
    else
        cout<<"The nr. you entered is not found!\n";

    //---------------------------------------------------------------------------------------
    const int SIZE = 10;
    int arr[SIZE];  // declare array of size 10
    int addarr[SIZE] = {0}; // declare array to hold the sum of the main array consicutively
    int nr1, nr2; // declare our 2 interval indecies

     // declare check if usr enter false input

    // our validation loop to check the usr input
    do{
        bool check = true;

        cout<<"Plz enter 10 number consecutively:";

        for(int i = 0; i < SIZE; i++)
        {
            cin>>arr[i];
            // input validation
            if(cin.fail())
            {
            cout<<"You should enter correct numbers. \n\n";
            cin.clear();
            cin.ignore(10000, '\n');
            check = false; // we turn our check to false
            break;
            }
            // if we are at the beginning we simply put the value of the arr to our sum array
            if(i == 0)
                addarr[i] = arr[i];
            else
                addarr[i] = addarr[i-1] + arr[i]; // here we sum the array elements consecutively
        }

    }while(!check); // it will only break if the input value is correct

    // usr input the interval indecies
    cout<<"Plz enter 2 index number indicate the interval of your query:";
    cin>>nr1>>nr2;

    // calling the function and print the sum elements of the given interval
    cout<<"the sum of your Query("<<nr1<<", "<<nr2<<")"<<" = "<<sumQuery(addarr, nr1, nr2);


    // --------------------------------------------------
    // getting from the user our 2 numbers as string
    string LongNr1, LongNr2;
    cout<<"Enter your first Long Number: ";
    cin>>LongNr1;
    cout<<"Enter your second Long Number: ";
    cin>>LongNr2;

    // check if the 2 numbers are entered correctly
    if(isDigitStr(LongNr1) && isDigitStr(LongNr2))
    {
        string Result = addLongString(LongNr1, LongNr2);
        cout<<"The Result is: "<<Result<<"\n";
    }
    else
        assert(false);



    string str;
    cout<<"Enter a string ane we offer you all possible substrings: ";
    cin >> str;


    cout<<"\nThe Substrings are: \n";

    // spliting a string to new lines
    // see more: https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
    // see more: https://stackoverflow.com/questions/13172158/c-split-string-by-line
    // error has initializer but incomplete type
    // see more: https://stackoverflow.com/questions/13428164/c-compile-error-has-initializer-but-incomplete-type
    string strLine = Substrings(str, str.length());
    stringstream iss(strLine);

    string LINE;

    // getline cpp
    // see more: http://www.cplusplus.com/reference/string/string/getline/
    while(getline(iss,LINE))
        cout<<LINE<<"\n";


   // -------------------------------------------
   TestCompare2Strings();



    string str1, str2;
    cout<<"Enter two strings and we will compare it for you:\n"
        <<"String nr. 1: ";
    cin >> str1;
    cout<<"\n"
        <<"String nr. 2; ";
    cin >> str2;

    int Result = compare2Str(str1, str1.length(), str2, str2.length());


    if(Result < 0)
        cout<<str1 <<" < "<<str2;
    else if(Result > 0)
                cout<<str1 <<" > "<<str2;
    else
        cout<<str1 <<" = "<<str2;




    string str;


    cout<<"Enter any string and we will group it for you: ";
    cin>>str;

    cout<<groupingString(str);

// ------------------------------------
// Belongs to version 1 (not working)
    string* strGrp;
    strGrp = groupingString(str);

    for(int i = 0; strGrp[i] != "\0"; i++)
        cout<<strGrp[i]<<" ";
// -------------------------------------

//-------------------------------------------------------------------------
    string str;
    cout<<"Enter a number: ";
    cin>>str;




    cout<<"The nr you entered as string \"" <<str<<"\" is converted to "<<charToInt(str)<<" as integer\n";

testMerge2SortedArrays();

    const int SIZE1 = 5;
    const int SIZE2 = 3;
    const int RES_SIZE = 8;

    int sorted1[SIZE1] = {1, 3, 5, 7, 8};
    int sorted2[SIZE2] = {2, 4, 6};
    int result[RES_SIZE];

    merge2SortedArrays(sorted1, SIZE1, sorted2, SIZE2, result, RES_SIZE);

    for(int i = 0; i < RES_SIZE; i++)
        cout<<result[i]<<" ";
    cout<<"\n";




    // to know pracically how flush works!!!
    // see more: https://stackoverflow.com/questions/14105650/how-does-stdflush-work/14107357#14107357
    // here if I write flush it print Line 1... and waite and then print Line 2, Line 3
    // but if I remove flush it will waite first and then print Line 1..., Line 2, and Line 3 at the same time
    // it is because the buffer will output its storage data only if it is full but flush force the buffer to output its
    // stored data even if it is not full yet.
    cout << "Line 1..." << flush;

    usleep(500000);

    cout << "\nLine 2" << endl;

    cout << "Line 3" << endl ;


TestInsertionSorting();

// Insertion array (Incremantal thinking)
int SIZE = 10;
int arr[SIZE];

cout<<"Enter 10 digits consecutively: ";
for(int i = 0; i < SIZE; i++)
    cin>>arr[i];

cout<<"The array before sorting: ";
for(int i = 0; i < SIZE; i++)
    cout<<arr[i]<<" ";

insertionSort(arr, SIZE);

cout<<"\nThe array after sorting: ";
    for(int i = 0; i < SIZE; i++)
        cout<<arr[i]<<" ";

// slideing window Maximum
int SIZE = 10;
int arr[SIZE];
int k = 0;

cout<<"Enter 10 digits consecutively: ";
for(int i = 0; i < SIZE; i++)
    cin>>arr[i];

cout<<"Enter the Window size: \n should be <= 9 \n";
cin>>k;
int maxWindow = slidingWindowMax(arr, SIZE, k);

cout<<"The max sum of 3 nr. in the array are: "<<maxWindow<<"\n";
    cout << "Hello world!" << endl;

    TestReverseInplace();

    const int SIZE = 10;
    int arr[SIZE];

    cout<<"Enter 10 numbers consecutively: ";
    for(int i = 0; i < SIZE; i++)
        cin>>arr[i];


    printArr(arr, SIZE);
    reverseInplace(arr, SIZE);
    printArr(arr, SIZE);


    Test_get2ndMax();

    const int LEN = 7;
    int arr[LEN];

    cout<<"\nEnter 7 numbers consecutively: ";
    for(int i = 0; i < LEN; i++)
        cin>>arr[i];

    cout<<"The second Maximum Value of this arry is: "<<get2Max(arr, LEN)<<"\n";


    const int LEN = 7;
    int arr[LEN] = {7, 9, 3, 6, 3, 77, 22};

    cout<<getMax(arr, LEN)<<"\n\n";



    const int LEN = 7;
    int arr[LEN] = {7, 9, 3, 6, 3, 77, 22};

    int maxValue = arr[0];
    for(int i = 1; i < LEN; i++)
        if(maxValue < arr[i])
            maxValue = arr[i];
    cout<<"Maximum value is: "<<maxValue<<"\n";

    // Playing with the array element and manipulate them as they are several variables

    double values[4] = {7}; // 7  0  0  0

    values[1] = 2 * values[0] + 0.75;
    values[2] = values[1] + 0.25;
    values[3] = values[0] + values[1] + values[2] + 0.25;

    for(int i = 0; (i<sizeof(values)/8); i++)
        cout<<values[i]<<" "<<"\n";

    // Reading a line of charachter: Delimeter

    string str1;
    char str2[100];
    char str3[100];

    getline(cin, str1, '#'); // here the getline will take only the input before # and skip # and finish the operation
    cin.get(str2, 100); // here the get will take then the input after # because getline had already throw the # away
    cin.get(); // read the new line
    cin.getline(str3, 100);

    cout<<"line 1 : "<<str1<<"\n";
    cout<<"line 2 : "<<str2<<"\n";
    cout<<"line 3 : "<<str3<<"\n";


    // in Char arrays we often left the last  byte empty to put '\0' = NULL which indicates the end of the array and we call
    // this last byte sentinel value
    // see more here: https://softwareengineering.stackexchange.com/questions/328225/char-array-why-do-we-need-1-byte-for-sentinel-value
    // see more here: http://aelinik.free.fr/c/ch13.htm

    // Reading a line of chars

    string str1;
    char str2[100];
    char str3[100];

    getline(cin,str1);
    // we can not replace 'get' before 'getline'
    // because 'get' leaves the \n char in the string
    // so when 'getlilne' reads it will see \n char at the begining from the last line
    // and it will terminate because \n char is the delimiter for lines
    // so to prevent this problem we use 'getline' firstly then in the next output we can use 'get'
    // getline() is better to use get()
    cin.getline(str2, 100);
    cin.get(str3, 100);

    cout<<"Line 1 : "<<str1<<"\n"
        <<"Line 2 : "<<str2<<"\n"
        <<"Line 3 : "<<str3<<"\n";


    char msg1[15] = "Hello_World!!!";
    char msg2[15] = "Hello\0World!!!";
    cout<<msg1<<"\n";
    cout<<msg2<<"\n";

    char name1[] = {'a', 'l', 'i'};
    cout<<name1;

    // Char array:
    char name1[4] = {'a', 'l', 'i'};
    char name2[4] = "ali";   // Easier way
    char name3[4] = {'A'
                        , 'l'
                             ,'i'}; // we can seperate the values in many lines

    cout<<name1<<"\n"
        <<name2<<"\n";

    cin>>name3; // read up 3 characters consecutive
    cout<<"You entered: "<<name3<<"\n";


    const int size = 5;
    int heights [size];

    cout<<"Enter #"<<size<<" of heights: ";
    for(int i = 0; i < size; i++)
        cin>>heights[i];

    for(int i = 0; i < size; i++)
        cout<<heights[i]<<" ";
    cout<<"\n";

    cout<<factorial(5)<<"\n ";


    cout<<maximum(2, 4)<<"\n";

    // = to

    cout<<(2 > 4 ? 2 : 4)<<"\n";


    int x = 1, y = 1;
    f(x, y);
    f(x, y);
    f(x, y);


    cout<<maximum(2, 4)<<"\n";
    cout<<maximum(2.4, 4.6)<<"\n";

    cout<<f(5, 3.5);
    cout<<f(3.5, 5);
    cout<<f<int>(3.5, 5);
    cout<<f<double, int>(3.5, 5);

    f1();   f1();   f1();
    cout<<"\n"<<"*******************************************"<<"\n";
    f2();   f2();   f2();


    f();
*/
    return 0;
}

