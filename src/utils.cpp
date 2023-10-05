#include "../include/utils.hpp"

void utils::print(std::vector<int> tab) {
  for (int i = 0; i < tab.size(); i++) {
    std::cout << tab[i] << ", ";
  }
  std::cout << std::endl;
}

void utils::getMapSize(std::ifstream *file, int *width, int *height) {
    std::string line;
    getline(*file, line);
    *width = stoi(line.substr(0, line.find(" ")));
    *height = stoi(line.substr(line.find(" ") + 1, line.length()));
}

void utils::mapToVector(std::ifstream *file, std::vector<std::vector<int>> *vect) {
    std::string line;
    int delim = 0;
    int i = 0, j = 0;

    while (getline(*file, line)) {
        /*
        * Example of the code above for each line:
        *   input :  line = "01 02 03 04 05", delimeter=" "
        *   output:  vect = <1, 2, 3, 4, 5>
        */

        while (line.length() != 0 && delim != -1) {
            delim = line.find(" ");
            (*vect)[i][j] = stoi(line.substr(0, delim));
            line = line.substr(delim+1, line.length());
            j++;
        }

        delim = 0;
        j = 0;
        i++;
    }

}

int utils::getMax(std::vector<std::vector<int>> vect) {
    int max = vect[0][0];
    
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            if(vect[i][j] > max) {
                max = vect[i][j];
            }
        }
    }

    return max;
    
}

std::string utils::addZeros(int number, int max) {
    int max_length = std::to_string(max).length();
    std::string std_number = std::to_string(number);

    while (std_number.length() < max_length) {
        std_number.insert(0, "0");
    }

    return std_number;
}

bool utils::isInsideVect(int value, std::vector<int> vect) {
    for (int val : vect) {
        if (val == value) {
            return true;
        }
    }
    
    return false;
}

int utils::findIndexById(int id, std::vector<utils::Texture> vect) {

    for (int i = 0; i < vect.size(); i++) {
        if(vect[i].id == id) {
            return i;
        }
    }

    return -1;    
}