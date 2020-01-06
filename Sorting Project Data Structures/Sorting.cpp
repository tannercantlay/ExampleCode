#include <iostream>
#include "Sorting.h"
#include <cstdlib>

int MinIndex(int values[], int start, int end, int & numComp){

  int indexOfMin = start;
  for(int index = start + 1; index <= end; index++){
    if(values[index] < values [indexOfMin]){
      numComp++;
      indexOfMin = index;
    }
  }
  return indexOfMin;
};

int SelectionSort(int values[], int numValues){
  int endIndex = numValues -1;
  int numComparisons = 0;
  for(int current = 0; current < endIndex; current++){
    std::swap(values[current],values[MinIndex(values, current, endIndex, numComparisons)]);
    numComparisons++;
  }
  return numComparisons;
};

int Merge(int values[], int leftFirst, int leftLast, int rightFirst, int rightLast){
  int tempArray[10000];
  int index = leftFirst;
  int saveFirst = leftFirst;
  int numComp = 0;
  while((leftFirst <= leftLast) && (rightFirst <= rightLast)){

    if(values[leftFirst] < values[rightFirst]){

      tempArray[index] = values[leftFirst];
      leftFirst++;
    }
    else{

      tempArray[index] = values[rightFirst];
      rightFirst++;

    }
    index++;
    numComp++;
  }
  while(leftFirst <= leftLast){
    tempArray[index] = values[leftFirst];
    leftFirst++;
    index++;
  }
  while(rightFirst <= rightLast){
    tempArray[index] = values[rightFirst];
    rightFirst++;
    index++;
  }

  for(index = saveFirst; index <= rightLast; index++){
    values[index] = tempArray[index];
  }
  return numComp;
};
int MergeSort(int values[], int first, int last){
  int numComp = 0;
  if ( first < last){
    int middle = (first + last) / 2;
    numComp += MergeSort(values, first, middle);
    numComp += MergeSort(values, middle + 1, last);
    numComp += Merge( values, first, middle, middle + 1, last);
  }
  return numComp;
};
int Split(int values[], int first, int last , int & counter){

  int start = first -1;
  int end = last + 1;

  int splitVal = values[first];

  while(true){
    do{
      start++;
      counter++;
    }while(values[start] < splitVal /*&& start <= first*/);
    do{
      end--;
      counter++;
    }while(values[end] > splitVal /*&& start <= last*/);
    if(start >= end){
      return end;
    }
    std::swap(values[start], values[end]);
  }

};
int QuickSort(int values[], int first, int last){
  int counter = 0;
  if(first < last){
    int splitPoint = Split(values, first, last, counter);
    //std::cout << "called split" << std::endl;
    counter += QuickSort(values, first, splitPoint);
    counter += QuickSort(values, splitPoint +1, last);
  }
  return counter;

};
int RandomQuickSort(int values[], int first, int last){
  int counter = 0;
  if(first < last){

    std::srand(time(NULL));
    int n = std::rand();
    int random = first + n %(last-first);
    //std::cout << "random number is:" << random << std::endl;
    std::swap(values[random], values[first]);
    int splitPoint = Split(values, first, last, counter);
    //std::cout << "called split" << std::endl;
    counter += RandomQuickSort(values, first, splitPoint);
    counter += RandomQuickSort(values, splitPoint +1, last);
  }
  return counter;


};
int ReheapDown(int values[], int root, int bottom){

  int maxChild;
  int rightChild;
  int leftChild;
  int numComp = 0;

  leftChild = root * 2 + 1;
  rightChild = root * 2 + 2;

  if(leftChild <= bottom){

    if (leftChild == bottom){
      maxChild = leftChild;
    }
    else{
      if(values[leftChild] <= values[rightChild]){
        maxChild = rightChild;
      }
      else{
        maxChild = leftChild;
      }
      numComp++;
    }
    if(values[root] < values [maxChild]){
      std::swap(values[root], values[maxChild]);
      numComp += ReheapDown (values, maxChild, bottom);
    }

  }
  return numComp;

};
int HeapSort(int values[], int numValues){
  int numComp = 0;
  int random = 0;
  int index;
  for(index = numValues/2-1; index >= 0; index--){

    random += ReheapDown(values, index, numValues -1);

  }

  for(index = numValues -1; index >= 1; index--){

    std::swap(values[0], values[index]);
    numComp += ReheapDown(values, 0, index -1);

  }
  return numComp;
};
