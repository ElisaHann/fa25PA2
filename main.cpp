//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    //checks if there are any leaf nodes
    if (nextFree == 0) {
        return -1;
    }
    if (nextFree == 1) {
        return 0;
    }

    MinHeap heap;

    //pushes leaves into heap
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }
    //makes the next free for the internal nodes
    int curNext = nextFree;

    while (heap.size > 1) {
        int leftIdx = heap.pop(weightArr);
        int rightIdx = heap.pop(weightArr);

    //displays an error if the next node exceeds the max amount of nodes
        if (curNext >= MAX_NODES) {
            cerr << "Error: too many nodes.\n";
            exit(1);
        }

       //creates the parent and internal node
        int parent = curNext++;
        weightArr[parent] = weightArr[leftIdx] + weightArr[rightIdx];
        leftArr[parent] = leftIdx;
        rightArr[parent] = rightIdx;
        charArr[parent] = '\0';

        //pushes the node to the heap
        heap.push(parent, weightArr);
    }

    //the node remaining is the root node
    int root = heap.pop(weightArr);
    return root;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // Uses stack<pair<int, string>> to simulate DFS traversal.
    stack<pair<int, string>> stack;
    stack.push({root, ""});

    while (!stack.empty()) {
        //compiler stores cur as the top node
        auto cur = stack.top();
        stack.pop();
        int node = cur.first;
        const string& path = cur.second;

        //checks if the node is a leaf
        bool isLeaf = (leftArr[node] == -1 && rightArr[node] == -1);

        //if the node is a leaf, the character is recieved and saved as the code
        if (isLeaf) {
            char ch = charArr[node];
            if (ch >= 'a' && ch <= 'z') {
                //assigns 0 if there is only one character
                codes[ch - 'a'] = path.empty() ? string("0") : path;
            }
        }
        //pushes children in heap
            else {
                if (rightArr[node] != -1) {
                    stack.push({rightArr[node], path + "1"});
                }
                    if (leftArr[node] != -1) {
                        stack.push({leftArr[node], path + "0"});
                    }
                }
            }
        }

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}