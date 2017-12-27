//
//  150140707
//  Muhammet Uçan
//  SmallVector.h
//  homework1
//

#include <iostream>
#include <cmath>
#include <cstring>
#ifndef SmallVector_h
#define SmallVector_h
#define SBUF 32

using namespace std;

class SmallVector{
private:
    int vector[SBUF];
    int *dVector,*dTemp;
    int size,capacity,dynSize;
public:
    SmallVector(int[] = 0, int = 0); // constructor
    ~SmallVector(); // destructor
    SmallVector(const SmallVector&); // copy constructor
    
    int getSize() const;
    void push_back(int);
    void push_back(const int[],const int);
    int pop_back();
    SmallVector reverse() const;
    
    //operator overloadings
    SmallVector operator+ (const SmallVector&); // concatenating
    SmallVector operator* (int); // copying object n times
    int& operator[] (int); // subscript
    const int& operator[] (int) const; // subscript const
    const SmallVector& operator= (const SmallVector&); // chain assignment
};

void arrayCopy(int *dst, const int src[], int size) {
    // takes two array and copyies second to first one with given size
    for (int i=0; i<size; i++)
        dst[i] = src[i];
}

SmallVector::SmallVector(int in_array[], int in_size) { // constructor
    size = in_size;
    if (size <= 32) {
        arrayCopy(vector, in_array, in_size);
        capacity = 32;
        dynSize = 0;
    }
    if (size > 32){
        capacity = size;
        dynSize = size-32;
        
        arrayCopy(vector, in_array, 32);
        
        dVector = new int [dynSize];
        int i=32;
        for (int j=0; j<dynSize; j++) {
            dVector[j]= in_array[i];
            i++;
        }
    }
}

SmallVector::SmallVector(const SmallVector& object_in) { // copy constructor
    size = object_in.size;
    if (size <= 32) {
        arrayCopy(vector, object_in.vector, object_in.size);
        capacity = 32;
        dynSize = 0;
    }
    if (size > 32){
        capacity = size;
        dynSize = size-32;
        
        arrayCopy(vector, object_in.vector, 32);
        
        dVector = new int [dynSize];
        int i=32;
        for (int j=0; j<dynSize; j++) {
            dVector[j]= object_in[i];
            i++;
        }
    }
}

SmallVector::~SmallVector() {  // destructor
    if (size>32) delete [] dVector;
}

int SmallVector::getSize() const {
    return size;
}

void SmallVector::push_back(int toAdd) {
    if (size<32) { // there is empty space and capacity
        vector[size++] = toAdd;
    } else { // there is no static space, dynamic memory should be allocated, make temp, copy old, add, copy back
        dTemp = new int [dynSize+1];
        arrayCopy(dTemp, dVector, dynSize);
        if (size>32) delete [] dVector;
        dVector = new int [dynSize + 1];
        dTemp[dynSize] = toAdd;
        arrayCopy(dVector, dTemp, dynSize+1);
        size++;
        capacity++;
        dynSize++;
        delete [] dTemp;
    }
}

void SmallVector::push_back(const int *toAdd, const int in_size) {
    if (size + in_size <= 32) { // static is sufficient for both
        for (int i=0; i<in_size; i++) {
            vector[size+i] = toAdd[i];
        }
    } else if (size < 32 && size + in_size > 32) { // static buffer is not suffucient
        for (int i=0; i<32-size; i++) {
            vector[size+i] = toAdd[i];
        }
        dynSize = in_size - (32-size);
        dVector = new int [dynSize];
        for (int j=0; j<dynSize; j++) {
            dVector[j] = toAdd[32-size+j];
        }
        capacity = size + in_size;
    } else if (size >= 32) { // no empty space in static
        dTemp = new int [in_size + dynSize];
        arrayCopy(dTemp, dVector, dynSize);
        if (size>32) delete [] dVector;
        
        for (int i = 0; i<in_size; i++) {
            dTemp[dynSize+i] = toAdd[i];
        }
        dynSize += in_size;
        capacity += in_size;
        dVector = new int [dynSize];
        arrayCopy(dVector, dTemp, dynSize);
        delete [] dTemp;
    }
    size += in_size;
}

int SmallVector::pop_back() {
    if (size == 0) {cout << "There is no element. "; return 0;}
    int temp;
    if (size <= 32) {
        size--;
        temp = vector[size];
        vector[size] = 0;
        return temp;
    } else {
        size--;
        capacity--;
        temp = dVector[dynSize];
        dVector[dynSize] = 0; // assigned 0 because of undefined behavior, although memory is going to be released, intentionally value setted to 0
        // memory regulation
        dynSize--;
        int *tempVector = new int [dynSize];
        memmove(tempVector, dVector, dynSize);
        delete [] dVector;
        dVector = new int [size-32];
        memmove(dVector, tempVector, dynSize);
        delete [] tempVector;
        return temp;
    }
}

SmallVector SmallVector::reverse() const {
    SmallVector temp_return(*this);
    for (int i = size-1,j=0; i>=0; i--,j++) {
        temp_return[j] = (*this)[i];
    }
    return temp_return;
}

SmallVector SmallVector::operator+ (const SmallVector& in_object){
    SmallVector temp;
    if (size + in_object.size <=32) {
        temp.push_back(vector, size);
        temp.push_back(in_object.vector, in_object.size);
    }
    else if (size < 32 && size + in_object.size > 32) {
        temp.push_back(vector, size);
        temp.push_back(in_object.vector, 32-size);
        temp.push_back(in_object.vector+32-size, in_object.size-in_object.dynSize-(32-size));
        if (in_object.dynSize != 0) temp.push_back(in_object.dVector, in_object.dynSize);
    }
    else if (size>32) {
        temp.push_back(vector, size-dynSize);
        temp.push_back(dVector, dynSize);
        temp.push_back(in_object.vector, in_object.size-in_object.dynSize);
        temp.push_back(in_object.dVector, in_object.dynSize);
    }
    return temp;
}

SmallVector SmallVector::operator* (int times) {
    SmallVector temp;
    for (int i=0; i<times; i++) {
        if (size <=32)temp.push_back(vector, size);
        else if (size>32) {
            temp.push_back(vector, size-dynSize);
            temp.push_back(dVector, dynSize);
        }
    }
    return temp;
}

int& SmallVector::operator[](int i) { // subscript overloading
    if (i>=32 && i<size) {
        return dVector[i-32];
    }
    else if (i<0 && i+size>=0) {
        if(size > 32 && i>=32-size) return dVector[i+size-32];
        else if (size > 32 && i<32-size) return vector[i+size];
        else return vector[i+size];
    }else if(i>=size) {
        if (size>32) return dVector[dynSize-1];
        else return vector[size-1];
    }else if(i+size<0) {
        return vector[0];
    }
    else return vector[i];
}

const int& SmallVector::operator[](int i) const { // subscript overloading const version
    if (i>=32 && i<size) {
        return dVector[i-32];
    }
    else if (i<0 && i+size>=0) {
        if(size > 32 && i>=32-size) return dVector[i+size-32];
        else if (size > 32 && i<32-size) return vector[i+size];
        else return vector[i+size];
    }else if(i>=size) {
        if (size>32) return dVector[dynSize-1];
        else return vector[size-1];
    }else if(i+size<0) {
        return vector[0];
    }
    else return vector[i];
}

const SmallVector& SmallVector::operator=(const SmallVector& object_in) {
    size = object_in.size;
    dynSize = object_in.dynSize;
    capacity = object_in.capacity;
    memcpy(vector, object_in.vector, sizeof(object_in.vector));
    if (object_in.dynSize != 0) {
        dVector = new int [dynSize];
        for (int i=0; i<dynSize; i++) {
            dVector[i] = object_in.dVector[i];
        }
    }
    return *this;
}

#endif /* SmallVector_h */
