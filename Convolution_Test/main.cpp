#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[]){
    
    unsigned int size_of_input = atoi(argv[1]), size_of_kernel = atoi(argv[2]), input_channel_size = atoi(argv[3]), output_channel_size = atoi(argv[4]), size_of_output = size_of_input - size_of_kernel + 1;
    
    int operand [size_of_input][size_of_input][input_channel_size];
    int kernel [size_of_kernel][size_of_kernel][input_channel_size][output_channel_size];
    int result [size_of_output][size_of_output][output_channel_size];
    
    ifstream feaFile(argv[5]);
    ifstream kerFile(argv[6]);
    if(feaFile.is_open()){
        for(int i = 0; i < size_of_input ; i++){
            for(int j = 0; j < size_of_input ; j++){
                for(int k = 0; k < input_channel_size; k++){
                    string str;
                    getline(feaFile,str);
                    if(!str.compare("") || feaFile.eof()) break;
                    operand[i][j][k] = stoi(str);
                    cout << operand[i][j][k] << endl;
                }
            }
        }
        feaFile.close();
    }
    else cout << "Error : feature cannot be open" << endl;

    if(kerFile.is_open()){
        for(int i = 0; i < size_of_output; i++){
            for(int j = 0; j < size_of_output; j++){
                for(int k = 0; k < input_channel_size; k++){
                    for(int l = 0; l < output_channel_size; l++){
                        string str;
                        getline(kerFile,str);
                        if(!str.compare("") || kerFile.eof()) break;
                        kernel[i][j][k][l] = stoi(str);
                        cout << kernel[i][j][k][l] << endl;
                    }
                }
            }
        }
        kerFile.close();
    }
    else cout << "Error : kernel cannot be open" << endl;

    for(int i = 0; i < size_of_output; i++){
        for(int j = 0; j < size_of_output; j++){
            for(int k = 0; k < output_channel_size; k++) result[i][j][k] = 0;
        }
    }
    
    for(int i = 0; i < size_of_output; i++){
        for(int j = 0; j < size_of_output; j++){
            for(int k = 0; k < output_channel_size; k++){
                for(int l = 0 ; l < input_channel_size; l++){
                    result[i][j][k] += operand[i][j][l] * kernel[0][0][l][k];
                    result[i][j][k] += operand[i][j+1][l] * kernel[0][1][l][k];
                    result[i][j][k] += operand[i][j+2][l] * kernel[0][2][l][k];
                    result[i][j][k] += operand[i+1][j][l] * kernel[1][0][l][k];
                    result[i][j][k] += operand[i+1][j+1][l] * kernel[1][1][l][k];
                    result[i][j][k] += operand[i+1][j+2][l] * kernel[1][2][l][k];
                    result[i][j][k] += operand[i+2][j][l] * kernel[2][0][l][k];
                    result[i][j][k] += operand[i+2][j+1][l] * kernel[2][1][l][k];
                    result[i][j][k] += operand[i+2][j+2][l] * kernel[2][2][l][k];
                    cout << result[i][j][k] << endl;
                }
            }
        }
    }
    
    ofstream writeDUMP;
    writeDUMP.open("/Users/laurent01/Desktop/Test_Dump",ios::in|ios::app);
    if(writeDUMP.is_open()){
        for(int i = 0; i < size_of_output; i++){
            for(int j = 0; j < size_of_output; j++){
                for(int k = 0; k < output_channel_size; k++){
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
