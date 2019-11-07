#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

/*
----------------------------- PART 1 FUNCTIONS -------------------------------
*/
//------------------------------ lcs_it -----------------------------------
//return LCS length iteratively with the 2D matrix passed as parameter
int lcs_it(int **C, string X, string Y, int m, int n){
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i] == Y[j]) {
                C[i][j] = C[i - 1][j - 1] + 1;
            }
            else {
                C[i][j] = max(C[i - 1][j], C[i][j - 1]);
            }
        }
    }
    return C[m - 1][n - 1];
}

//------------------------------ backtrack -----------------------------------
//return LCS string recursively via backtracking through a populated 2D LCS matrix
string backtrack(int **C, string X, string Y, int m, int n){
    if ((m == 0) || (n == 0)) {
        return "";
    }
    if (X[m] == Y[n]) {
        return backtrack(C, X, Y, m - 1, n - 1) + X[m];
    }
    else if (C[m - 1][n] > C[m][n - 1]){
        return backtrack(C, X, Y, m - 1, n);
    }
    else {
        return backtrack(C, X, Y, m, n - 1);
    }
}

/*
----------------------------- PART 2 FUNCTIONS -------------------------------
*/
//---------------------------- lcs_it_test --------------------------------
//return LCS length iteratively with 2D matrix initiated in function, not as parameter
int lcs_it_test(string X, string Y, int m, int n){
    int **C=new int*[m + 1];
    for (int i = 0; i < m + 1; i++) {
        C[i] = new int [n + 1];
    }
    for (int k = 0; k < m + 1; k++) {
        for (int l = 0; l < n + 1; l++) {
            C[k][l] = 0;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i] == Y[j]) {
                C[i][j] = C[i - 1][j - 1] + 1;
            }
            else {
                C[i][j] = max(C[i - 1][j], C[i][j - 1]);
            }
        }
    }
    return C[m - 1][n - 1];
}

//----------------------------- lcs_re --------------------------------
//return LCS length recursively, 2D matrix not required - all stored on stack as function executes
int lcs_re(string X, string Y, int m, int n) {
    if ((m == 1) || (n == 1)) {
        return 0;
    }
    else if (X[m - 1] == Y[n - 1]) {
        return lcs_re(X, Y, m - 1, n - 1) + 1; 
    }
    return max(lcs_re(X, Y, m - 1, n), lcs_re(X, Y, m, n - 1));
}


int main() {
    string X = " ";
    string Y = " ";

    //read the text file and load them onto the strings
    ifstream input("C:\\Users\\seane\\OneDrive\\Documents\\projects\\helloworld\\program2\\input.txt");
    char current_char;
    bool next_string;
    while(input.get(current_char)) {
        if (current_char == '\n') {
            next_string = true;
            continue;
        }
        if (next_string == false) {
            X += current_char;
        }
        else Y += current_char;
    }
    input.close();

    //create 2d array to store LCS values
    int m = X.size();
    int n = Y.size();

    int **C=new int*[m + 1];
    for (int i = 0; i < m + 1; i++) {
        C[i] = new int [n + 1];
    }
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            C[i][j] = 0;
        }
    }
    
    //function calls
    //part 1
    cout << "Testing part 1 functions..." << endl;
    int len = lcs_it(C, X, Y, m, n);
    cout << "Final Length via lcs_it: " << len << endl;

    string str = backtrack(C, X, Y, m, n);
    cout << "LCS via backtrack: " << str << endl << endl;

    //part 2
    cout << "Testing part 2 functions..." << endl;
    int trial_size_1;
    cout << "Enter a trial length for two strings, from which LCS length will be drawn via iteration (less than " << min(X.size(), Y.size()) << "): "; 
    cin >> trial_size_1;
    int len_test = lcs_it_test(X, Y, trial_size_1, trial_size_1);
    int len_test_2 = lcs_it_test(X, Y, m, n);
    cout << "Final Length via lcs_it_test: " << len_test << " ...or, if running both strings at full length: " << len_test_2 << endl;

    int trial_size_2;
    cout << "Enter a trial length for two strings, from which LCS length will be drawn via recursion (less than 20): "; 
    cin >> trial_size_2;
    int len_rec_test = lcs_re(X, Y, trial_size_2, trial_size_2);
    cout << "Final Length via lcs_re: " << len_rec_test << endl << endl;

    //time testing part 2 functions   
    cout << "Time testing function finding LCS length via iteration (left number = length of string/problem size): " << endl;
    int start_s, stop_s;
    start_s = clock();
    for (int i = 1; i <= 800; i++){
        lcs_it_test(X, Y, i, i);
        stop_s = clock();
        clog << i << ":\t" << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    }
    cout << "Time testing function finding LCS length via recursion (left number = length of string/problem size): " << endl;
    start_s = clock();
    for (int i = 1; i <= 20; i++){
        lcs_re(X, Y, i, i);
        stop_s = clock();
        clog << i << ":\t" << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    }


    return 0;
}