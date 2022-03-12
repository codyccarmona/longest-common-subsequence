/*
 * 
 *  Title: COP4531 Assignment 2: Longest Common Subsequence
 *  Author: Cody Carmona
 *  Subject:
 *      This program accepts two input strings which contains file names. It then reads strings from these file names
 *          and finds the longest common subsequence betweeen them with memoization
 */
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

/* Copies LCS-LENGTH from textbook 15.4. Instead of using arrays and tables b and c, this uses 1 2D vector of integers
    NOTE: We do not implement the memorized portion here (no arrows) */
int MEMOIZED_LCS_LENGTH(std::vector<std::vector<int>> c, std::string X, std::string Y, int i, int j){
    if(c[i][j] > -1)
        return c[i][j];

    if(i == 0 || j == 0)
        c[i][j] = 0;
    else{
        if(X[i - 1] == Y[j - 1])
            c[i][j] = MEMOIZED_LCS_LENGTH(c, X, Y, i - 1, j - 1) + 1;
        else    
            c[i][j] = std::max(MEMOIZED_LCS_LENGTH(c, X, Y, i, j - 1), MEMOIZED_LCS_LENGTH(c, X, Y, i - 1, j));
        
    }
    return c[i][j];
}

/* Memoized version of LCS_LENGTH provided in 15.4. The major difference is how the table is built. Rather than going through row by row,
    MEMOIZED_LCS_LENGTH is used to compute each cell value */
std::vector<std::vector<int>> LCS_LENGTH(std::string X, std::string Y){
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> c(m + 1, std::vector<int>(n + 1, -1));
    for(int i = m; i >= 0; i--){
        for(int j = n; j >= 0; j--){
            if(c[i][j] == -1)
                c[i][j] = MEMOIZED_LCS_LENGTH(c, X, Y, i, j);
        }
    }
    return c;
}

/* Copies PRINT_LCS from textbook 15.4. */
void PRINT_LCS(std::vector<std::vector<int>> c, std::string X, int i, int j){
    // Base case
    if(i == 0 || j == 0)
        return;

    // If upper left value is current value - 1 and upper left, left, and upper all match, then we found
    //  a match. Print value and follow upper left element
    if(c[i][j] - 1 == c[i - 1][j - 1] && c[i - 1][j - 1] == c[i][j - 1] && c[i - 1][j - 1] == c[i -1][j]){
        PRINT_LCS(c, X, i - 1, j - 1);
        std::cout << X[i - 1];
    }
    // Otherwise, is upper the same or bigger than left, follow it
    else if(c[i -1][j] >= c[i][j - 1]){
        PRINT_LCS(c, X, i - 1, j);
    }
    // Default follow left value
    else{
        PRINT_LCS(c, X, i, j - 1);
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
    std::vector<std::vector<int>> c = LCS_LENGTH(X, Y);
    // Print LCS
    PRINT_LCS(c, X, X.size(), Y.size());

    return 0;
}