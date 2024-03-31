#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool check_cellnumber(long long int CellNumber) {
    string numStr = to_string(CellNumber);
    int length = numStr.length();
    if (length != 10 || (length == 11 && numStr[0] != '0')) {
        cout << "Invalid number format. Please enter a 10-digit number." << endl;
        return false;
    }
    return true;
}

bool number_exists(const map<string, long long int>& Contacts, long long int CellNumber) {
    for (const auto& pair : Contacts) {
        if (pair.second == CellNumber) {
            return true;
        }
    }
    return false;
}

bool name_exists(const map<string, long long int>& Contacts, const string& Name) {
    return Contacts.find(Name) != Contacts.end();
}

int main() {
    map<string, long long int> Contacts;
    string Name;
    long long int CellNumber;
    int choice = 1;

    while (choice) {
        cout << "Enter the contact number: ";
        cin >> CellNumber;

        // Check if the number is valid
        while (!check_cellnumber(CellNumber)) {
            cout << "Please enter a valid 10-digit number: ";
            cin >> CellNumber;
        }

        // Check if the number already exists
        if (number_exists(Contacts, CellNumber)) {
            cout << "Skipping this contact. Please enter a new number." << endl;
            continue; // Skip to the next iteration
        }

        cin.ignore(); // Ignore newline character after reading choice

        // Read the name and check if it already exists
        cout << "Enter the Name: ";
        getline(cin, Name);

        while (name_exists(Contacts, Name)) {
            cout << "Name already exists. Please enter a new name: ";
            getline(cin, Name);
        }

        // Map the string to the integer
        Contacts[Name] = CellNumber;

        cout << "Enter 1 to add more contacts: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character after reading choice
    }

    // Display the mapped values in sorted order by name
    cout << "----------@CONTACTS@----------" << endl;
    cout << "NAME" << " -> " << "NUMBER" << endl;
    for (const auto& pair : Contacts) {
        cout << pair.first << " -> " << pair.second << endl;
    }

    // Prompt the user to enter incoming call numbers
    cout << "Enter incoming call numbers (enter 0 to stop): " << endl;
    vector<long long int> incomingCalls;
    long long int incomingNumber;
    while (true) {
        cin >> incomingNumber;
        if (incomingNumber == 0) {
            break;
        }
        if (!check_cellnumber(incomingNumber)) {
            cout << "Invalid number format. Please enter a 10-digit number." << endl;
            continue;
        }
        if (!number_exists(Contacts, incomingNumber)) {
            char choice;
            cout << "Unknown number. Do you want to save it? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cin.ignore(); // Ignore newline character after reading choice
                cout << "Enter the Name: ";
                getline(cin, Name);
                Contacts[Name] = incomingNumber;
            }
        }
        incomingCalls.push_back(incomingNumber);
    }

    // Count the number of times each contact number was dialed
    map<long long int, pair<string, int>> dialedCounts;
    for (long long int number : incomingCalls) {
        for (const auto& pair : Contacts) {
            if (pair.second == number) {
                dialedCounts[number].second++;
                dialedCounts[number].first = pair.first; // Store the name
            }
        }
    }

    // Display the results
    cout << "----------@DIALED COUNTS@----------" << endl;
    cout << "NAME" << " -> " << "NUMBER" << " -> " << "COUNT" << endl;
    for (const auto& pair : dialedCounts) {
        cout << pair.second.first << " -> " << pair.first << " -> " << pair.second.second << endl;
    }

    return 0;
}
