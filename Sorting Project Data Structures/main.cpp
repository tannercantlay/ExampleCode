#include "Sorting.h"
#include <fstream>
#include <iostream>

int main(int argc, char * argv[]){


  int values[10000];
  int start = 0;;
  int end;

  std::fstream fs;

  fs.open(argv[1], std::fstream::in);
  if(fs.is_open()) {
    int input;
    fs >> input;
    int index = 0;
    while (!fs.eof()) {
      values[index] = input;
      index++;
      fs >> input;
    }
    end = index;
  }
  else {
    std::cout << "Failed to open the input file" << std::endl;
    return 0;
  }

  std::cout << "selection-sort (s)   merge-sort (m)   heap-sort (h)   quick-sort-fp (q)   quick-sort-rp (r)" << std::endl;

  std::cout << "Enter the algorithm: ";
  char input;
  while(!(std::cin >> input)){
    std::cout << "Invalid option. Please enter a valid option." << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Enter the algorithm: ";
  }
  if(input == 's'){
    int numComparisons = 0;
    numComparisons = SelectionSort(values, end);

    for(int i = 0; i < end; i++){
      std::cout << values[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\t #Selection-sort comparions:  " << numComparisons << std::endl;
  }
  else if(input == 'm'){
    int numComparisons = 0;
    numComparisons = MergeSort(values, start, end -1);

    for(int i = 0; i < end; i++){
      std::cout << values[i] << " ";
    }
    std::cout << "\n";
    std::cout << "\t #Merge-sort comparions:  " << numComparisons << std::endl;

  }
  else if(input == 'h'){
    int numComparisons = 0;

    numComparisons = HeapSort(values, end);
    for(int i = 0; i < end; i++){
      std::cout << values[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\t #Heap-sort comparions:  " << numComparisons << std::endl;
  }
  else if(input =='q'){
    int numComparisons = 0;
    numComparisons = QuickSort(values, start, end -1);

    for(int i = 0; i < end; i++){
      std::cout << values[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\t #Quick-sort-fp comparions:" << numComparisons << std::endl;
  }
  else if(input == 'r'){
    int numComparisons = 0;
    numComparisons = RandomQuickSort(values, start, end -1);

    for(int i = 0; i < end; i++){
      std::cout << values[i] << " ";
    }
    std::cout << "\n";
    std::cout << "\t #Quick-sort-rp comparions:" << numComparisons << std::endl;
  }

}
