#include <bits/stdc++.h>
using namespace std;

/*
wall '#'
start/End *
vmark 'x' 
*/



void printMaze(vector<vector<char>> maze) {
    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[i].size(); j++){
            cout << maze[i][j] << " ";
        }
        cout << endl;
        cout << endl;
    }
}

int main() {
    //gets user input
    vector<vector<char>> maze = 
        //SAMPLE INPUT
        {{'#', '*', '#', ' ', '#', '#'},
        {'#', ' ', '#', ' ', '#', '#'},
        {'#', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', '#'},
        {'#', '#', '#', ' ', '#', '#'},
        {'#', ' ', ' ', ' ', '#', '#'},
        {'#', ' ', '#', '#', '#', '#'},
        {'*', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', '#'}};
    vector<vector<char>> originalCopy = maze;

    int posX = -1;
    int posY = -1;
    int startPosX = -1;
    int startPosY = -1;

    //find index of starting point
    for(int y = 0; y < maze.size(); y++){
        if(posX != -1) break;

        for(int x = 0; x < maze[y].size(); x++){
            if(maze[y][x] == '*') {
                posX = x;
                startPosX = x;
                posY = y;
                startPosY = y;
            }
        }
    }
    maze[startPosY][startPosX] = 'x';

    vector<vector<int>> steps = {};

    //determine the boundaries of the maze (the uppermost and leftmost boundary are automatically 0)
    int maxX = maze[0].size()-1;
    int maxY = maze.size()-1;

    while(maze[posY][posX] != '*') {
        //stores original position which will be appended to "steps" if "moved" is true
        bool moved = false;
        int originalX = posX;
        int originalY = posY;

        //travel up?
        if(posY > 0 && maze[posY - 1][posX] != 'x' && maze[posY - 1][posX] != '#') {
            posY--;
            moved = true;
        }
         
        //travel rightwards?
        else if(posX < maxX && maze[posY][posX + 1] != 'x' && maze[posY][posX + 1] != '#'){
            posX++;
            moved = true;
        }

        //travel downwards?
        else if(posY < maxY && maze[posY + 1][posX] != 'x' && maze[posY + 1][posX] != '#'){ 
            posY++;
            moved = true;
        }

        //travel leftwards?
        else if(posX > 0 && maze[posY][posX - 1] != 'x' && maze[posY][posX - 1] != '#'){
            posX--;
            moved = true;
        }

        //add the step for future backtracking
        if (moved) {
            steps.push_back({originalX, originalY});
        } else {
            //backtrack here
            if (!steps.empty()) {
                posX = steps.back()[0];
                posY = steps.back()[1];
                steps.pop_back();
            } else {
                break; // No more steps to backtrack to
            }
        }
        if(maze[posY][posX] != '*') {
            maze[posY][posX] = 'x';
        }
    }

    //prints out the shortest path
    cout << "Original: " << endl;
    printMaze(originalCopy);
    for(int i = 0; i < steps.size(); i++){
        originalCopy[steps[i][1]][steps[i][0]] = 'X';
    }
    //after the algorithm, the starting position will be marked 'x', change it back to '*'
    originalCopy[startPosY][startPosX] = '*'; 
    cout << "Solution: " << endl;
    printMaze(originalCopy);
    return 0;
}
