/*
 * 
 *  Title: COP4531 Assignment 2: Longest Common Subsequence
 *  Author: Cody Carmona
 *  Subject:
 *      This program accepts two input strings which contains file names. It then reads strings from these file names
 *          and finds the longest common subsequence betweeen them with memorization
 */
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

/* Used to represent the arrow portion of the memorized LCS_LENGTH algorithm */
enum Direction{
    UP,
    LEFT,
    UPLEFT,
    NONE
};

/* Copies LCS-LENGTH from textbook 15.4. Instead of using arrays and tables b and c, this uses 1 2D vector of pairs
    Note the pairs have their integer value as pair.first and the direction enum as pair.second */
std::vector<std::vector<std::pair<int, Direction>>> LCS_LENGTH(std::string X, std::string Y){
    int m = X.size();
    int n = Y.size();
    // Init 2D vector with all pairs that have integer value 0 and Direction value NONE
    std::vector<std::vector<std::pair<int, Direction>>> cb(m + 1, std::vector<std::pair<int, Direction>>(n + 1, std::pair<int, Direction>(0, Direction::NONE)));
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            // If X[i] == Y[j]. Notice we subtract 1 whereas the textbook does not
            if(X[i - 1] == Y[j - 1]){
                cb[i][j].first = cb[i - 1][j - 1].first + 1;
                cb[i][j].second = Direction::UPLEFT;
            }
            // Check if upper value is >=
            else if(cb[i - 1][j] >= cb[i][j- 1]){
                cb[i][j].first = cb[i - 1][j].first;
                cb[i][j].second = Direction::UP;
            }
            // Use left pair integer value
            else{
                cb[i][j].first = cb[i][j - 1].first;
                cb[i][j].second = Direction::LEFT;
            }
        }
    }
    return cb;
}


/* Copies PRINT_LCS from textbook 15.4. Adjusted to work with 2d vector of pairs rather than array b */
void PRINT_LCS(std::vector<std::vector<std::pair<int, Direction>>> cb, std::string X, int i, int j){
    // base case
    if(i == 0 || j == 0)
        return;
    // case in which we have a match, follow and print value
    if(cb[i][j].second == Direction::UPLEFT){
        PRINT_LCS(cb, X, i - 1, j - 1);
        std::cout << X[i - 1];
    }
    // otherwise, check if we can go up
    else if(cb[i][j].second == Direction::UP){
        PRINT_LCS(cb, X, i - 1, j);
    }
    // default go left
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
    std::vector<std::vector<std::pair<int, Direction>>> cb = LCS_LENGTH(X, Y);

    // Print LCS
    PRINT_LCS(cb, X, X.size(), Y.size());

    return 0;
}