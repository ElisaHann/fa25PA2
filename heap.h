//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() {
        size = 0;
    }

    void push(int idx, int weightArr[]) {
        if (size >= 64) {
            cerr << "Heap Overflow" << endl;
            exit(1);
        }
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        if (size == 0) {
            cerr << "Heap Underflow" << endl;
            exit(1);
        }
        int root = data[0];
        size--;
        if (size > 0) {
            data[0] = data[size];
            downheap(0, weightArr);
        }
        return root;
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]] || (weightArr[data[pos]] == weightArr[data[parent]] && data[pos] < data[parent])) {
                int tmp = data[pos];
                data[pos] = data[parent];
                data[parent] = tmp;
                pos = parent;
            }
            else {
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int min = pos;

            if (left < size && (weightArr[data[left]] < weightArr[data[min]] || (weightArr[data[left]] == weightArr[data[min]] && data[left] < data[min]))){
                min = left;
            }
            if (right < size && (weightArr[data[right]] < weightArr[data[min]] || (weightArr[data[right]] == weightArr[data[min]] && data[right] < data[min]))) {
                min = right;
            }
            if (min == pos) {
                return;
            }
            int tmp = data[pos];
            data[pos] = data[min];
            data[min] = tmp;
            pos = min;
        }
    }
};

#endif