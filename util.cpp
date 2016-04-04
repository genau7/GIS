#include "util.h"

FileParser::FileParser(){}

void initData(int vNum, std::vector<std::vector<int> >* data){
    for(int row=0; row<vNum; row++){
        std::vector<int> rowData;
        for(int col=0; col<vNum; col++)
            rowData.push_back(0);
        data->push_back(rowData);
    }
}

std::vector<std::vector<int> >* FileParser::readMatrix(std::string filename){
    std::ifstream file;
    std::vector<std::vector<int> >* data = new std::vector<std::vector<int> >;
    file.open(filename.c_str());
    if(!file.is_open()){
        //throw error
        std::cout<<"File "<<filename<<" cannot be read!\n";
        return NULL;
    }
    //get the number of vertices
    unsigned vNum;
    file >> vNum ;
    initData(vNum, data);

    for(int row=0; row<vNum; row++){
        for(int col=0; col<vNum; col++){
            int distance;
            file >> distance;
            if(distance == 9999) distance = INT_MAX;
            int* cell = &(data->at(row).at(col));
            *cell = distance;
        }
    }
    return data;
}
