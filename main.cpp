//
//  main.cpp
//  UFPT
//
//  Created by Henry Kerins on 9/17/16.
//  Copyright © 2016 Henry Kerins. All rights reserved.
//

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    int a, b, c;
    int sum = -1;
    vector<pair<int, int>> empty;
    cin >> a >> b;
    
    int** arr2d = new int*[a];
    for (int i = 0; i < a; ++i)
        arr2d[i] = new int[b];
    
    for (int i = 0; i < a; ++i){
        for (int j = 0; j < b ; ++j){
            cin >> c;
            arr2d[i][j] = c;
            if (c == 0){
                pair<int, int> xypair (i, j);
                empty.push_back(xypair);
            }
            
        }
    }
    //check all but last row to make sure input works
    for(int i = 0; i < a-1; i++){
        //check all but last column for right, bottom, right bottom
        for(int j = 0; j < b -1; j++){
            if(arr2d[i][j] == 0)
                continue;
            if(arr2d[i][j] >= arr2d[i][j+1] && arr2d[i][j+1] != 0){
                cout << sum;
                return 0;
            }
            if(arr2d[i][j] >= arr2d[i+1][j] && arr2d[i+1][j] != 0){
                cout << sum;
                return 0;
            }
            if(arr2d[i][j] % 2 == arr2d[i+1][j+1] % 2 && arr2d[i+1][j+1] != 0){
                cout << sum;
                return 0;
            }
            //test all but first column for bottom left diagonal
            if(j != 0){
                if(arr2d[i][j] % 2 == arr2d[i+1][j-1] % 2 && arr2d[i+1][j-1] != 0){
                    cout << sum;
                    return 0;
                }

            }
        }
    }
    //check last column for bottom, bottom left
    for(int i = 0; i < a-1; i++){
        if(arr2d[i][b-1] == 0)
            continue;
        if(arr2d[i][b-1] >= arr2d[i+1][b-1] && arr2d[i+1][b-1] != 0){
            cout << sum;
            return 0;
        }
        if(b > 1){
            
            if(arr2d[i][b-1] % 2 == arr2d[i+1][b-2] % 2 && arr2d[i+1][b-2] != 0){
                cout << sum;
                return 0;
            }
        }
    }
    
    //check last row for number to right
    for(int i = 0; i < b-1; i++){
        if(arr2d[a-1][i] >= arr2d[a-1][i+1] && arr2d[a-1][i+1] != 0){
            cout << sum;
            return 0;
        }
    }
    
    
    for(vector<pair<int, int>>::const_iterator iter = empty.begin(); iter != empty.end(); ++iter){
        pair<int, int> nextPair = *iter;
        int x = nextPair.first;
        int y = nextPair.second;
        int max = 0;
        bool added = false;
        //find max value preceding the 0 and make the zero that max+1
        for (int i = 0; i < y; ++i){
            if (arr2d[x][i] >= max){
                max = arr2d[x][i] + 1;
                arr2d[x][y] = max;
            }
        }
        //check its value in row
        for (int i = 0; i < x; ++i){
            if (arr2d[i][y] >= arr2d[x][y]){
                max = arr2d[i][y] + 1;
                arr2d[x][y] = max;
            }
        }
        //check that its below remaining row values
        for (int i = y; i < b-1; ++i){
            if (arr2d[x][y] >= arr2d[x][i+1] && arr2d[x][i+1] != 0){
                cout << sum;
                return 0;
            }
        }
        //check that its below remaining column values
        for (int i = x; i < a-1; ++i){
            if (arr2d[x][y] >= arr2d[i+1][y] && arr2d[i+1][y] != 0){
                cout << sum;
                return 0;
            }
        }
        //make sure its not zero
        if (arr2d[x][y] == 0){
            arr2d[x][y] = 1;
        }
        
        
        //check that this value follows all the rules
        //if theres a row below it
        int valTemp = arr2d[x][y];
        if(x < a-1){
            
            //if it has a bottom left diagonal
            if(y > 0){
                //if left bottom diagonal modulus is the same, add 1. if its nonzero, lock parity
                if((arr2d[x+1][y-1]) != 0){
                    if((arr2d[x][y] % 2) == (arr2d[x+1][y-1] % 2)){
                        arr2d[x][y] = (arr2d[x][y]+1);
                    }
                    added = true;
                }

                //if it has bottom right diagonal as well
                if(y < b-1){
                    //if bottom left and bottom right are not the same modulus
                    if(((arr2d[x+1][y-1] % 2) != (arr2d[x+1][y+1] % 2)) && arr2d[x+1][y-1] != 0 && arr2d[x+1][y+1] != 0){
                        cout << sum;
                        return 0;
                    }
                    //if right bottom diagonal modulus is the same, add 1. if its nonzero, lock parity
                    if((arr2d[x+1][y+1]) != 0){
                        if((arr2d[x][y] % 2) == (arr2d[x+1][y+1] % 2)){
                            if(added){
                                cout << sum;
                                return 0;
                            }
                            arr2d[x][y] = (arr2d[x][y]+1);
                        }
                        added = true;
                    }
                    
                }
                //at this point we have checked it against both bottom diagonals, as well as
                //the bottom diagonals against each other, and added is true if our parity is locked in
                
                //if it has upper left diagonal
                if(x > 0){
                    //if upper left and bottom left are not the same
                    if(((arr2d[x+1][y-1] % 2) != (arr2d[x-1][y-1] % 2)) && arr2d[x+1][y-1] != 0 && arr2d[x-1][y-1] != 0){
                        cout << sum;
                        return 0;
                    }
                   
                    //if top left diagonal modulus is the same, add 1. if its nonzero, lock parity
                    if ((arr2d[x-1][y-1]) != 0){
                        if((arr2d[x][y] % 2) == (arr2d[x-1][y-1] % 2)){
                            if(added){
                                cout << sum;
                                return 0;
                            }
                            arr2d[x][y] = (arr2d[x][y]+1);
                        }
                        added = true;
                    }
                    //if it has upper right diagonal
                    if(y < b-1){
                        //if upper right and upper left are not the same
                        if(((arr2d[x-1][y-1] % 2) != (arr2d[x-1][y+1] % 2)) && arr2d[x-1][y-1] != 0 && arr2d[x-1][y+1] != 0){
                            cout << sum;
                            return 0;
                        }
                        //if upper right and bottom left are not the same
                        if(((arr2d[x+1][y-1] % 2) != (arr2d[x-1][y+1] % 2)) && arr2d[x+1][y-1] != 0 && arr2d[x-1][y+1] != 0){
                            cout << sum;
                            return 0;
                        }
                        //if upper right and bottom right are not the same
                        if(((arr2d[x+1][y+1] % 2) != (arr2d[x-1][y+1] % 2)) && arr2d[x+1][y+1] != 0 && arr2d[x-1][y+1] != 0){
                            cout << sum;
                            return 0;
                        }
                        //if upper left and bottom right are not the same (we check this here because we know they exist)
                        if(((arr2d[x+1][y+1] % 2) != (arr2d[x-1][y-1] % 2)) && arr2d[x+1][y+1] != 0 && arr2d[x-1][y-1] != 0){
                            cout << sum;
                            return 0;
                        }
                        //if top right diagonal modulus is the same, add 1. if its nonzero, lock parity
                        if ((arr2d[x-1][y+1]) != 0){
                            if((arr2d[x][y] % 2) == (arr2d[x-1][y+1] % 2)){
                                if(added){
                                    cout << sum;
                                    return 0;
                                }
                                arr2d[x][y] = (arr2d[x][y]+1);
                            }
                            added = true;
                        }
                        
                    }
                    
                }
               
                //at this point weve checked the upper two corners for scenarios where we have a lower row
                
            }
            //if it has no bottom left but it has bottom right
            else if(y < b-1){
                
                //if right bottom diagonal modulus is the same, add 1. if its nonzero, lock parity
                if((arr2d[x+1][y+1]) != 0){
                    if((arr2d[x][y] % 2) == (arr2d[x+1][y+1] % 2)){
                        if(added){
                            cout << sum;
                            return 0;
                        }
                        arr2d[x][y] = (arr2d[x][y]+1);
                    }
                    added = true;
                }
                
                //if it has upper right diagonal
                if(x > 0){
                    //if upper right and bottom right are not the same
                    if(((arr2d[x+1][y+1] % 2) != (arr2d[x-1][y+1] % 2)) && arr2d[x+1][y+1] != 0 && arr2d[x-1][y+1] != 0){
                        cout << sum;
                        return 0;
                    }
                    //if top right diagonal modulus is the same, add 1. if its nonzero, lock parity
                    if ((arr2d[x-1][y+1]) != 0){
                        if((arr2d[x][y] % 2) == (arr2d[x-1][y+1] % 2)){
                            if(added){
                                cout << sum;
                                return 0;
                            }
                            arr2d[x][y] = (arr2d[x][y]+1);
                        }
                        added = true;
                    }
                    
                }
            }
            
            //now we have checked all modulus when there is a bottom row
            
            //if its greater than or equal to number below it
            for(int i = x; i < a-1; i++){
                if(arr2d[x][y] >= arr2d[i+1][y] && arr2d[i+1][y] != 0){
                    cout << sum;
                    return 0;
                }
            }
        }
        //if theres nothing below it but a row above it
        else if(x > 0){
            //if it has upper left and right diagonals
            if(y > 0 && y < b -1){
                if(((arr2d[x-1][y-1] % 2) != (arr2d[x-1][y+1] % 2)) && arr2d[x-1][y-1] != 0 && arr2d[x-1][y+1] != 0){
                    cout << sum;
                    return 0;
                }
                //if top left  diagonal modulus is the same, add 1. if its nonzero, lock parity
                if((arr2d[x-1][y-1]) != 0){
                    if((arr2d[x][y] % 2) == (arr2d[x-1][y-1] % 2)){
                        if(added){
                            cout << sum;
                            return 0;
                        }
                        arr2d[x][y] = (arr2d[x][y]+1);
                    }
                    added = true;
                }
                //if top right diagonal modulus is the same, add 1. if its nonzero, lock parity
                if((arr2d[x-1][y+1]) != 0){
                    if((arr2d[x][y] % 2) == (arr2d[x-1][y+1] % 2)){
                        if(added){
                            cout << sum;
                            return 0;
                        }
                        arr2d[x][y] = (arr2d[x][y]+1);
                    }
                    added = true;
                }
            }
            //if it only has upper left diagonal
            else if(y > 0){
                //if top left  diagonal modulus is the same, add 1. if its nonzero, lock parity
                if((arr2d[x-1][y-1]) != 0){
                    if((arr2d[x][y] % 2) == (arr2d[x-1][y-1] % 2)){
                        if(added){
                            cout << sum;
                            return 0;
                        }
                        arr2d[x][y] = (arr2d[x][y]+1);
                    }
                    added = true;
                }
            }
            //if it only has upper right diagonal
            else if(y < b-1){
                //if top right diagonal modulus is the same, add 1. if its nonzero, lock parity
                if((arr2d[x-1][y+1]) != 0){
                    if((arr2d[x][y] % 2) == (arr2d[x-1][y+1] % 2)){
                        if(added){
                            cout << sum;
                            return 0;
                        }
                        arr2d[x][y] = (arr2d[x][y]+1);
                    }
                    added = true;
                }
            }
            
        }
        //repeat checks now that you may have added 1
        //check that its below remaining row values
        for (int i = y; i < b-1; ++i){
            if (arr2d[x][y] >= arr2d[x][i+1] && arr2d[x][i+1] != 0){
                cout << sum;
                return 0;
            }
        }
        //check that its below remaining column values
        for (int i = x; i < a-1; ++i){
            if (arr2d[x][y] >= arr2d[i+1][y] && arr2d[i+1][y] != 0){
                cout << sum;
                return 0;
            }
        }
        
    }
    sum = 0;
    
    for (int i = 0; i < a; ++i){
        for (int j = 0; j < b ; ++j){
            sum += arr2d[i][j];
            //cout << arr2d[i][j] << " ";
        }
        //cout << "\n";
    }
    cout << sum;
    
    return 0;
}




