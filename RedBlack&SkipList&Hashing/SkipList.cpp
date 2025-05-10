#include <iostream>
#include <map>
#include <cstdlib> // For rand()
#include <stack>   // For std::stack
#include <queue>

using namespace std;


struct Node {
    int value;
    Node* right;
    Node* down;

    Node(int val) : value(val), right(nullptr), down(nullptr) {}
};

struct SkipList {
    Node* head;
    int levelCount;

    SkipList() {
        head = new Node(INT_MIN);
        levelCount = 1;
    }
};

// Search function
Node* search(SkipList& skipList, int target) {
    Node* currentNode = skipList.head;

    while (currentNode) {
        while (currentNode->right && currentNode->right->value < target) {
            currentNode = currentNode->right;
        }

        if (currentNode->right && currentNode->right->value == target) {
            return currentNode->right;
        }

        currentNode = currentNode->down;
    }

    return nullptr;
}

void insertAfter(Node* insertionPoint, Node* newNode) {
    newNode->right = insertionPoint->right;
    insertionPoint->right = newNode;
}

// Insert function
void insert(SkipList& skipList, int value) {
    Node* currentNode = skipList.head;
    stack<Node*> insertionPoints;
    while (currentNode) {
        while (currentNode->right && currentNode->right->value < value) {
            currentNode = currentNode->right;
        }
        insertionPoints.push(currentNode);
        currentNode = currentNode->down;
    }
    Node* lowestLevelNode = insertionPoints.top();
    insertionPoints.pop();
    Node* newNode = new Node(value);
    insertAfter(lowestLevelNode, newNode);
    int level = 1;
    while ((rand() % 2) == 0) { // 50% chance to promote
        if (level >= skipList.levelCount) {
            Node* newLevelHead = new Node(INT_MIN);
            newLevelHead->down = skipList.head;
            skipList.head = newLevelHead;
            skipList.levelCount++;
        }

        if (insertionPoints.empty()) {
            break;
        }

        Node* insertionPoint = insertionPoints.top();
        insertionPoints.pop();

        Node* upperLevelNode = new Node(value);
        insertAfter(insertionPoint, upperLevelNode);
        upperLevelNode->down = newNode;
        newNode = upperLevelNode;
        level++;
    }
}

// Delete function
bool deleteNode(SkipList& skipList, int target) {
    Node* currentNode = skipList.head;
    bool found = false;

    while (currentNode) {
        while (currentNode->right && currentNode->right->value < target) {
            currentNode = currentNode->right;
        }

        if (currentNode->right && currentNode->right->value == target) {
            found = true;
            Node* nodeToDelete = currentNode->right;
            currentNode->right = nodeToDelete->right;
            delete nodeToDelete;
        }

        currentNode = currentNode->down;
    }

    return found;
}

void printSkipList(SkipList& skipList) {
    Node* level = skipList.head;
    while (level) {
        Node* node = level->right;
        while (node) {
            cout << node->value << " ";
            node = node->right;
        }
        cout << "\n";
        level = level->down;
    }
    cout << endl;
}



class ModSkipList {
// Define the Player structure
    struct Player {
        int id;          // Unique player ID
        int score = 0;   // Player's score

        Player(int id, int score = 0): id(id), score(score){};
    };


// Define the MNode structure
    struct MNode {
        Player *player = nullptr;  // Pointer to the associated player
        MNode *right = nullptr;
        MNode *down = nullptr;

        MNode(Player *p = nullptr) : player(p) {}
        MNode(int id, int sc){
            player = new Player(id, sc);
        }
    };

// Define the SkipList structure

    MNode *head;
    int levelCount;

public:
    ModSkipList() {
        head = new MNode();
        levelCount = 1;
    }


// Search for a player's Mnode by their ID
    MNode *search(int playerId) {
        MNode* currentNode = head;

        while (currentNode) {
            while (currentNode->right && currentNode->right->player->id < playerId) {
                currentNode = currentNode->right;
            }

            if (currentNode->right && currentNode->right->player->id == playerId) {
                return currentNode->right;
            }

            currentNode = currentNode->down;
        }

        return nullptr;
    }

// Insert or update a player's score in the skip list
    void updateScore(int id, int newScore) {
        MNode *existingMNode = search(id);

        // If the player exists, update their score and re-insert
        if (existingMNode) {
            existingMNode->player->score = newScore;
            return;
        }else{
            cout<<"Player is not in the game\n";
            cout<<"Add player?: Y/N\n";
            char choice; cin>>choice;
            if(choice == 'Y'){
                Insert(id, newScore);
            }
        }

    }


    void Insert(int id, int score) {
        if (search(id)) {
            cout << "Player with ID " << id << " already exists.\n";
            return;
        }
        MNode *currentNode = head;
        stack<MNode*> insertionPoints;
        while (currentNode) {
            while (currentNode->right && currentNode->right->player->id < id) {
                currentNode = currentNode->right;
            }
            insertionPoints.push(currentNode);
            currentNode = currentNode->down;
        }
        MNode *lowestLevelNode = insertionPoints.top();
        insertionPoints.pop();
        MNode *newNode = new MNode(id , score);
        //insert after
        newNode->right = lowestLevelNode->right;
        lowestLevelNode->right = newNode;

        int level = 1;
        while ((rand() % 2) == 0) { // 50% chance to promote
            if (level >= levelCount) {
                MNode *newLevelHead = new MNode();
                newLevelHead->down = head;
                head = newLevelHead;
                levelCount++;
            }

            if (insertionPoints.empty()) {
                break;
            }

            MNode *insertionPoint = insertionPoints.top();
            insertionPoints.pop();

            MNode *upperLevelNode = new MNode(id, score);

            //insert after
            upperLevelNode->right = insertionPoint->right;
            insertionPoint->right = upperLevelNode;
            upperLevelNode->down = newNode;
            newNode = upperLevelNode;
            level++;
        }
    }

// Retrieve the top N active players
    void getTopPlayers(int n) {
        priority_queue<pair<int, int>> topPlayers;
        MNode *currentMNode = head;

        // Traverse to the lowest level
        while (currentMNode->down) {
            currentMNode = currentMNode->down;
        }

        // Traverse the bottom level and collect the players
        currentMNode = currentMNode->right;
        while (currentMNode) {
            if (currentMNode->player) {
                topPlayers.push({currentMNode->player->score, currentMNode->player->id});
            }
            currentMNode = currentMNode->right;
        }

        while (n-- && !topPlayers.empty()){
            auto topPlayer = topPlayers.top();
            topPlayers.pop();
            cout << "(ID: " << topPlayer.second<<", Score: "<<topPlayer.first << ")\n";
        }
    }

// Print the skip list for debugging
    void printSkipList() {
        MNode *level = head;
        while (level) {
            MNode *Mnode = level->right;
            while (Mnode) {
                cout << "(ID: " << Mnode->player->id<<", Score: "<<Mnode->player->score;cout << ") ";
                Mnode = Mnode->right;
            }
            cout << "\n";
            level = level->down;
        }
        cout << endl;
    }

    void removePlayer( int playerId) {
        MNode *currentLevel = head;
        bool found = false;

        while (currentLevel) {
            MNode *currentMNode = currentLevel;
            while (currentMNode->right && currentMNode->right->player && currentMNode->right->player->id != playerId) {
                currentMNode = currentMNode->right;
            }

            // If the next node matches the player ID, remove it
            if (currentMNode->right && currentMNode->right->player && currentMNode->right->player->id == playerId) {
                MNode *toDelete = currentMNode->right;
                currentMNode->right = toDelete->right; // Remove node from current level
                delete toDelete; // Free the memory
                found = true;
            }

            // Move down to the next level
            currentLevel = currentLevel->down;
        }

    }

};


int main(){
//    SkipList skipList;
//
//    // Insert elements into the skip list
//    cout << "\nInserting elements: 10, 20, 30, 40, 50";
//    insert(skipList, 10);
//    insert(skipList, 20);
//    insert(skipList, 30);
//    insert(skipList, 40);
//    insert(skipList, 50);
//
//    // Print the skip list after insertion
//    cout << "\nSkip List after insertions:";
//    printSkipList(skipList);
//
//    // Search for specific elements
//    cout << "\nSearching for elements:";
//    int searchValues[] = {20, 35, 50};
//    for (int value : searchValues) {
//        Node* result = search(skipList, value);
//        if (result) {
//            cout << "\nElement " << value << " found in the skip list.";
//        } else {
//            cout << "\nElement " << value << " not found in the skip list.";
//        }
//    }
//
//    // Delete specific elements
//    cout << "\nDeleting elements: 20, 40";
//    deleteNode(skipList, 20);
//    deleteNode(skipList, 40);
//
//    // Print the skip list after deletions
//    cout << "\nSkip List after deletions:";
//    printSkipList(skipList);
//
//    // Attempt to delete an element not in the list
//    cout << "\nAttempting to delete an element not in the list (60):";
//    if (!deleteNode(skipList, 60)) {
//        cout << "\nElement 60 not found, so it cannot be deleted.\n\n";
//    }
//
//
    ModSkipList modskipList;

    modskipList.Insert(1, 10);
    modskipList.Insert(2, 20);
    modskipList.Insert(3, 30);

    modskipList.getTopPlayers(3);
    cout<<"\n";
    modskipList.updateScore(2, 40);
    modskipList.getTopPlayers(3);
    cout<<"\n";
    modskipList.removePlayer(3);
    modskipList.getTopPlayers(2);
    cout<<"_______________________\n";
    cout << "Player SkipList test\n"
            "Top 2 Players:\n";
    modskipList.getTopPlayers(2);

    cout << "Skip List Structure:\n";
    modskipList.printSkipList();


    modskipList.updateScore(1, 250);
    cout << "After updating Player 1's score to 250:\n";
    modskipList.getTopPlayers(3);

    cout << "Skip List Structure:\n";
    modskipList.printSkipList();


    modskipList.removePlayer(2);
    cout << "After removing Player 2:\n";
    modskipList.getTopPlayers(3);

    cout << "Skip List Structure:\n";
    modskipList.printSkipList();


    modskipList.updateScore(4, 300);
    cout << "After adding Player 4:\n";
    modskipList.getTopPlayers(3);

    cout << "Skip List Structure:\n";
    modskipList.printSkipList();


    for (int i = 5; i <= 50; ++i) {
        modskipList.Insert(i, rand() % 500); // Random scores between 0 and 499
    }

    cout << "Top 5 Players after random insertions:\n";
    modskipList.getTopPlayers(5);


}