#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

void simplex(double tabl[][3], double *c, double *b){
    string str[4] = {"S0" ,"X1", "X2", "X3"};
    string str1[4] = {"X4", "X5", "X6", "F "};
    string check[3] = {"X1", "X2", "X3"};
    double **mat = new double*[4];
    for(int i = 0; i < 4; ++i){
        mat[i] = new double[4];
        for(int j = 0; j < 4; ++j){
            mat[i][j] = 0;
        }
    }



    int line = 0;
    int row = 0;


    for(int i = 0; i < 3; ++i){
        for(int j = 1; j < 4; ++j){
            mat[i][j] = tabl[i][j-1];
        }
    }

    for(int i = 0; i < 3; ++i){
        mat[i][0] = b[i];
        mat[3][i+1] = c[i];
    }


    cout<<"- "<<" ";
    for(int i = 0; i < 4; ++i){
        cout.width(7);
        cout<<str[i]<<" ";
    }
    cout<<endl;
    for(int i = 0; i < 4; ++i){
        cout<<str1[i]<<" ";
        for(int j = 0; j < 4; ++j){
            cout.width(7);
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;


    int k = 1;
    bool test = false;
    while(true){
        test = false;
        for(int i = 1; i < 4; ++i){
            row = i;
            if(mat[3][row] > 0){
                test = true;
                break;
            }
        }
        if(test == false){
            break;
        }


        for(int i = 1; i < 3; ++i){
            double check = 100;
            if(mat[i-1][row] != 0){
                check = mat[i-1][0] / mat[i-1][row];
            }
            if(mat[i][row] != 0){
                if(check > mat[i][0] / mat[i][row]){
                    line = i;
                }
            }
        }


        swap(str[row],str1[line]);

        double razr = mat[line][row];


        double **mat1 = new double*[4];
        for(int i = 0; i < 4; ++i){
            mat1[i] = new double[4];
            for(int j = 0; j < 4; ++j){
                mat1[i][j] = 0;
            }
        }

        mat1[line][row] = 1 / razr;


        for(int i = 0; i < 4; ++i){
            if(i != row){
                mat1[line][i] = mat[line][i] / razr;
            }
        }

        for(int i = 0; i < 4; ++i){
            if(i != line && mat[i][row] != 0){
                mat1[i][row] =  mat[i][row] / -razr;
            }
        }


        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                if(i != line && j != row){
                    mat1[i][j] = mat[i][j] - (mat[i][row] * mat[line][j] / razr);
                }
            }
        }

        for(int i = 0; i < 4; ++i){
            delete[] mat[i];
        }
        delete[] mat;
        mat = mat1;


        cout<<"iteration №"<<k++<<endl;
        cout<<"- "<<" ";
        for(int i = 0; i < 4; ++i){
            cout.width(7);
            cout<<str[i]<<" ";
        }
        cout<<endl;
        for(int i = 0; i < 4; ++i){
            cout<<str1[i]<<" ";
            for(int j = 0; j < 4; ++j){
                cout.width(7);
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;

        line = 0;
        row = 0;
    }

    //проверка
    cout<<"check result:"<<endl;
    cout<<"F = ";
    double result = 0;
    for(int i = 0; i < 3; ++i){
        if(str1[i][1] == '1' || str1[i][1] == '2' || str1[i][1] == '3'){
            cout<<mat[int(str1[i][1]) - 1 - 48][0]<<" * ";
            result = result + c[int(str1[i][1]) - 1 - 48] * mat[int(str1[i][1]) - 1 - 48][0];
            cout<<c[int(str1[i][1]) - 1 - 48];
            if(i < 2){
                cout<<" + ";
            }
        }else{
            cout<<"0";
            if(i < 2){
                cout<<" + ";
            }
        }
    }
    cout<<" = "<<result<<endl;
    cout<<"F = "<<mat[3][0] * -1<<endl;
}




int main(){


    double tabl[3][3] = {{1.0, 1.0, 1.0},
                         {1.0, 1.0, 0.0},
                         {0.0, 0.5, 2.0}};

    double c[3] = {1, 3, 8};
    double b[3] = {7, 2, 4};

    simplex(tabl, c, b);

    return 0;
}
