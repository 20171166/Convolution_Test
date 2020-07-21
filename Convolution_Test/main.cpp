#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[]){
    
    unsigned int size_of_input = 5, size_of_kernel = 3, input_channel_size = 3, output_channel_size = 4, size_of_output = 3;
    
    int operand [size_of_input][size_of_input][input_channel_size];
    int kernel [output_channel_size][size_of_kernel][size_of_kernel][input_channel_size];
    int result [output_channel_size][size_of_output][size_of_output];
    
    ifstream feaFile(argv[1]);
    ifstream kerFile(argv[2]);
    if(feaFile.is_open()){
        for(int i = 0; i < size_of_input ; i++){
            for(int j = 0; j < size_of_input ; j++){
                for(int k = 0; k < size_of_kernel; k++){
                    string str;
                    getline(feaFile,str);
                    if(!str.compare("") || feaFile.eof()) cout << "Error occured" << endl;
                    operand[i][j][k] = stoi(str,NULL);
                }
            }
        }
        feaFile.close();
    }
    else cout << "Error : feature cannot be open" << endl;

    if(kerFile.is_open()){
        for(int l = 0; l < output_channel_size; l++){
            for(int i = 0; i < size_of_output; i++){
                for(int j = 0; j < size_of_output; j++){
                    for(int k = 0; k < input_channel_size; k++){
                        string str;
                        getline(feaFile,str);
                        cout << str << endl;
                        if(!str.compare("") || feaFile.eof()) cout << "Error occured" << endl;
                        kernel[l][i][j][k] = stoi(str,NULL);
                    }
                }
            }
        }
        kerFile.close();
    }
    else cout << "Error : kernel cannot be open" << endl;

    for(int i = 0; i < output_channel_size; i++){
        for(int j = 0; j < size_of_output; j++){
            for(int k = 0; k < size_of_output; k++) {
                result[i][j][k] = 0;
                for(int n = 0; n < input_channel_size; n++){
                    result[i][j][k] += (operand[j][k][n] * kernel[i][0][0][n] + operand[j][k + 1][n] * kernel[i][0][1][n] + operand[j][k + 2][n] * kernel[i][0][2][n] + operand[j + 1][k][n] * kernel[i][1][0][n] + operand[j+1][k+1][n] * kernel[i][1][1][n] + operand[j+1][k+2][n] * kernel[i][1][2][n] + operand[j+2][k][n] * kernel[i][2][0][n] + operand[j+2][k+1][n] * kernel[i][2][1][n] + operand[j+2][k+2][n] * kernel[i][2][2][n]);
                }
            }
        }
    }
    
    ofstream writeDUMP;
    writeDUMP.open("/Users/laurent01/Desktop/Test_Dump",ios::in|ios::app);
    if(writeDUMP.is_open()){
        for(int i = 0; i < output_channel_size; i++){
            for(int j = 0; j < size_of_output; j++){
                for(int k = 0; k < size_of_output; k++){
                    stringstream stream;
                    stream << dec << result[i][j][k];
                    string result(stream.str());
                    writeDUMP << result << "\n";
                }
            }
        }
        writeDUMP.close();
    }
    else cout << "ERROR : File is not open" << endl;

    
    return 0;
}
