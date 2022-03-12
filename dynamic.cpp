/*
 * 
 *  Title: COP4531 Assignment 2: Longest Common Subsequence
 *  Author: Cody Carmona
 *  Subject:
 *      This program accepts two input strings which contains file names. It then reads strings from these file names
 *          and finds the longest common subsequence betweeen them without memorization
 */
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

/* Copies LCS-LENGTH from textbook 15.4. Instead of using arrays and tables b and c, this uses 1 2D vector of integers
    NOTE: We do not implement the memorized portion here (no arrows) */
std::vector<std::vector<int>> LCS_LENGTH(std::string X, std::string Y){
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> cb(m + 1, std::vector<int>(n + 1, 0));
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(X[i - 1] == Y[j - 1]){
                cb[i][j] = cb[i - 1][j - 1] + 1;
            }
            else if(cb[i - 1][j] >= cb[i][j- 1]){
                cb[i][j] = cb[i - 1][j];
            }
            else{
                cb[i][j] = cb[i][j - 1];
            }
        }
    }
    return cb;
}

/* Copies PRINT_LCS from textbook 15.4. Adjusted to work with the non-memorized substructure (no arrows)
    Instead, it uses the optimal substructure to print LCS (exact match to structure used to build table) */
void PRINT_LCS(std::vector<std::vector<int>> cb, std::string X, int i, int j){
    // Base case
    if(i == 0 || j == 0)
        return;

    int diagVal = cb[i - 1][j - 1]; // upper left value
    int leftVal = cb[i][j - 1];     // left value
    int upperVal = cb[i -1][j];     // upper value

    // If upper left value is current value - 1 and upper left, left, and upper all match, then we found
    //  a match. Print value and follow upper left element
    if(cb[i][j] - 1 == diagVal && diagVal == leftVal && diagVal == upperVal){
        PRINT_LCS(cb, X, i - 1, j - 1);
        std::cout << X[i - 1];
    }
    // Otherwise, is upper the same or bigger than left, follow it
    else if(upperVal >= leftVal){
        PRINT_LCS(cb, X, i - 1, j);
    }
    // Default follow left value
    else{
        PRINT_LCS(cb, X, i, j - 1);
    }
}

/* Accepts a file name as a string, opens file, reads 1 line, and returns read string */
std::string read_string(std::string file){
    std::string line;
    std::ifstream srcFile(file);
    std::getline(srcFile, line);
    srcFile.close();
    return line;
}

int main(int argc, char** argv){
    std::string X = read_string(argv[1]); // Get first string
    std::string Y = read_string(argv[2]); // Get second string

    // X must be the largest string for both PRINT_LCS and LCS_Length, if X is not larger than Y, swap strings
    if(Y.size() > X.size()){
        std::string temp = Y;
        Y = X;
        X = temp;
    }

    // Build table
    std::vector<std::vector<int>> cb = LCS_LENGTH(X, Y);

    // Print LCS
    PRINT_LCS(cb, X, X.size(), Y.size());

    return 0;
}