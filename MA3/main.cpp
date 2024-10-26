#include <map>
#include "generateUsers.hpp"
using namespace std;


map<string, User> buildMapByUserName(vector<User> users) {
    map<string, User> usersMap;

    // int was causing issues with cmake
    size_t i = 0;

    while(i < users.size()) {
        usersMap.insert({users[i].userName, users[i]});
        i++;
    }

    return usersMap;
}


map<string, User> buildMapByEmail(vector<User> users) {
    map<string, User> usersMap;
    size_t i = 0;

    // While I is less than size, this makes it run for USER in the Vector of users
    while(i < users.size()) {
        usersMap.insert({users[i].email, users[i]});
        i++;
    }

    return usersMap;
}


// Code Adapted from site provided in MA3.pdf "https://en.cppreference.com/w/cpp/container/map"
// Capitalized letters are established as smaller value than its lowercase coutnerpart, ie. (C < c)
void printMap(map<string, User> aMap) {
    int count = 0;

    // Function used from the site provided.
    for (auto i = aMap.begin(); i != aMap.end(); ++i){
        cout << "  Node " << count << ": [" << i->first << "]" << endl;
        count++;
    }
    cout << endl;
}

// Capitalized letters are established as smaller value than its lowercase coutnerpart, ie. (C < c), this one uses a for loop to search the map
bool isMapSorted(map<string, User> aMap) {
    string prev, current;
    for (auto i = aMap.begin(); i != aMap.end(); ++i) {
        current = i->second.userName;

        if (!prev.empty() && prev > current) {
                return false;
        }

        prev = current;
    }
    return true;
}


bool testSearchByKey(map<string, User> aMap, string keyToSearch) {

    // Deletion demonstrates find() function, search uses a for loop.
    for (auto i = aMap.begin(); i != aMap.end(); ++i) {
        if (i->first == keyToSearch) {
            return true;
        }
    }
    return false;
}


bool testDeleteByKey(map<string, User> aMap, string keyToDelete) {

    // Instead of doing a for loop, we can use a iterator with the built in find() function for maps: "https://en.cppreference.com/w/cpp/container/map"
    auto iterator = aMap.find(keyToDelete);
    if (iterator != aMap.end()) {
        aMap.erase(iterator);
    }

    // Confirming that the deletion successful
    if (testSearchByKey(aMap, keyToDelete) == false) {
        return true;
    }

    return false;   
}


void printActiveUsers(map<string, User> aMap) {
    int activeThreshold = 800;
    for (auto i = aMap.begin(); i != aMap.end(); ++i) {
        if (i->second.numPosts > activeThreshold) {
            cout << "  " << i->second.userName << " has " << i->second.numPosts << " posts!" << endl;
        }
    }
    cout << endl << endl;
}

// Use a map to store categories, then display most present amongst Users
void printMostPopularCategory(map<string, User> aMap) {    
    map<string, int> categories;

    for (auto i = aMap.begin(); i != aMap.end(); ++i) {
        // Increment the count in category, it will initially be set to 0
        categories[i->second.mostViewedCategory]++;
    }

    // Now find node with max count, it is organized based on key so iterate through whole tree
    int max = 0;
    string popCategory;
    
    for (auto i = categories.begin(); i != categories.end(); ++i) {
        if (max < i->second) {
            max = i->second;
            popCategory = i->first;
        }
    }

    cout << "The most popular category is: " << popCategory << " with " << max << " frequenters!" << endl;
}


int main()
{
    int numUsers = 10;
    vector<User> users = generateUsers(numUsers);


    cout << "Build map with username as key" << endl;
    map<string, User> mapByUserName = buildMapByUserName(users);

    // static cast necessary for cmake, it alleviates comparing two different formats
    if ( mapByUserName.size() == static_cast<size_t>(numUsers))
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;


    cout << "Print \"mapByUserName\" map:" << endl;
    printMap(mapByUserName);
    cout << endl;


    string keyToSearch = "smith55";
    cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByUserName, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    string keyToDelete = "smith55";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByUserName, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    cout << "Test if map's key is sorted" << endl;
    if ( isMapSorted(mapByUserName) )
        cout << "  Order test passed!" << endl << endl;
    else
        cout << "  Order test failed!" << endl << endl;


    cout << "Print usernames with more than 800 tweets:" << endl;
    printActiveUsers(mapByUserName);
    cout << endl;

    cout << "Print the most popular category" << endl;
    printMostPopularCategory(mapByUserName);
    cout << endl;


    cout << " ============================================================================== " << endl << endl;


    cout << "Build map with username as key" << endl;
    map<string, User> mapByEmail = buildMapByEmail(users);
    if ( mapByEmail.size() == static_cast<std::size_t>(numUsers))
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;
    

    keyToSearch = "kat@gmail.com";
    cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByEmail, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    keyToDelete = "kat@gmail.com";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByEmail, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    return 0;
}