//***************************************************************
//            HEADER FILEs USED IN THE PROJECT
//***************************************************************

#include <iostream>
#include <string.h>
#include <queue>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""

//***************************************************************
//    	      STRUCTURE TO DEFINE A NODE
//***************************************************************

struct Node
{
    char ch;
    int frequency;
    Node *left, *right;
};

//***************************************************************
//    	FUNCTION TO ALLOCATE A NEW TREE NODE
//***************************************************************

Node *getNode(char ch, int frequency, Node *left, Node *right)
{
    Node *node = new Node();
    node->ch = ch;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

//*****************************************************************
// STRUCTURE TO COMPARISON OF OBJECT TO BE USED TO ORDER THE HEAP
//*****************************************************************

struct comp
{
    bool operator()(const Node *l, const Node *r) const
    {
        // THE HIGHEST PRIORITY ITEM HAS THE LOWEST FREQUENCY
        return l->frequency > r->frequency;
    }
};

//********************************************************************
// UTILITY FUNC TO CHECK IF HUFFMAN TREE CONTAINS ONLY A SINGLE NODE
//*********************************************************************

bool isLeaf(Node *root)
{
    return root->left == nullptr && root->right == nullptr;
}

//*************************************************************************
//  FUNCTION TO TRAVERSE THE HUFFMAN TREE & STORE HUFFMAN CODES IN A MAP
//                  (FUNCTION TO ENCODE THE STRING)
//**************************************************************************

void encode(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
    {
        return;
    }

    // CONDITION TO CHECK IF A LEAF NODE IS FOUND
    if (isLeaf(root))
    {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

//*************************************************************************
//  FUNCTION TO TRAVERSE THE HUFFMAN TREE & DECODE THE ENCODED STRING
//**************************************************************************

void decoding(Node *root, int &index, string str)
{
    if (root == nullptr)
    {
        return;
    }

    // CONDITION TO CHECK IF A LEAF NODE IS FOUND
    if (isLeaf(root))
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
    {
        decoding(root->left, index, str);
    }
    else
    {
        decoding(root->right, index, str);
    }
}

//***************************************************************
//  FUNCTION TO BUILD HUFFMAN TREE & DECODE THE GIVEN INPUT TEXT
//***************************************************************

void huffman(string text)
{
    // BASE CASE EMPTY STRING
    if (text == EMPTY_STRING)
    {
        return;
    }

    // COUNT THE FREQUENCY OF APPEARANCE & STORE IT IN A MAP
    unordered_map<char, int> frequency;
    for (char ch : text)
    {
        frequency[ch]++;
    }

    // CREATE A PRIORITY QUEUE TO STORE LIVE NODES OF THE HUFFMAN TREES
    priority_queue<Node *, vector<Node *>, comp> pq;

    // CREATE A LEAF NODE FOR EACH CHARACTER AND ADD IT TO THE PRIORITY QUEUE
    for (auto pair : frequency)
    {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // PERFORM THE LOOP TILL THERE IS MORE THAN ONE NODE IN THE QUEUE
    while (pq.size() != 1)
    {
        // REMOVE THE TWO NODES OF THE HIGHEST PRIORITY(THE LOWEST FREQUENCY) FROM THE QUEUE
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        /*CREATE A NEW INTERNAL NODE WITH THESE TWO NODES AS CHILDREN AND WITH A FREQUENCY EQUAL
        TO THE SUM OF TWO NODES FREQUENCY */
        // ADD THE NEW NODE TO THE PRIORITY QUEUE
        int sum = left->frequency + right->frequency;
        pq.push(getNode('\0', sum, left, right));
    }

    // ROOT STORES POINTER TO THE ROOT OF THE HUFFMAN TREE
    Node *root = pq.top();

    // TRAVERSE THE HUFFMAN TREE & STORES HUFFMAN CODES IN A MAP
    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);

    //***************************************************************
    //  PRINTING OF HUFFMAN CODES
    //***************************************************************
    cout << "\nHuffman Codes are : \n"
         << endl;
    for (auto pair : huffmanCode)
    {
        cout << pair.first << " " << pair.second << endl;
    }

    //***************************************************************
    //  PRINTING OF ORIGINAL STRING
    //***************************************************************
    cout << "\nThe original string is : "
         << text << endl;

    string str;
    for (char ch : text)
    {
        str += huffmanCode[ch];
    }

    //***************************************************************
    //  PRINTING OF ENCODED STRING & ITS SIZE (IN BITS)
    //  PRINTING OF DECODED STRING
    //***************************************************************

    cout << "\nThe encoded string is : "
         << str << "\n\nSize of encoded string : " << str.length();
    cout << "\n\nThe decoded string is : ";

    if (isLeaf(root))
    {
        // SPECIAL CASE FOR INPUT LIKE a,aa,aaa etc.
        while (root->frequency--)
        {
            cout << root->ch;
        }
    }
    else
    {
        // TRAVERSE THE HUFFMAN TREE AGAIN THIS TIME DECODE THE ENCODED STRING
        int index = -1;
        while (index < (int)str.size() - 1)
        {
            decoding(root, index, str);
        }
    }
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//***************************************************************

void intro()
{
    cout << "HUFFMAN CODING";
    cout << "\nMADE BY : DEEPAK SINGH (2K20/MC/38)";
    cout << "\n\t  GIRDHAR JHA (2K20/MC/51)";
    cout << "\nCOLLEGE : DELHI TECHNOLOGICAL UNIVERSITY";
}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//***************************************************************

int main()
{
    string text;
    intro();
    cout << "\n\nEnter your String : ";
    cin >> text;
    cout << "Size of string text : " << text.length() * 8 << "\n";
    huffman(text);
    return 0;
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
