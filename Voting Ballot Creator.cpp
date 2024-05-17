#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Define a structure for candidate/option
struct Candidate {
    string name;
    int votes;
};

// Define a class for managing ballots
class Ballot {
private:
    vector<Candidate> candidates;

public:
    // Function to add a new candidate to the ballot
    void addCandidate(const Candidate& candidate) {
        candidates.push_back(candidate);
        cout << "Candidate added successfully." << endl;
    }

    // Function to update details of a candidate
    void modifyCandidate(const string& name, const Candidate& updatedCandidate) {
        for (int i = 0; i < candidates.size(); ++i) {
            if (candidates[i].name == name) {
                candidates[i] = updatedCandidate;
                cout << "Candidate details updated successfully." << endl;
                return;
            }
        }
        cout << "Candidate with name " << name << " not found." << endl;
    }

    // Function to remove a candidate from the ballot
    void deleteCandidate(const string& name) {
        for (auto it = candidates.begin(); it != candidates.end(); ++it) {
            if (it->name == name) {
                candidates.erase(it);
                cout << "Candidate removed successfully." << endl;
                return;
            }
        }
        cout << "Candidate with name " << name << " not found." << endl;
    }

    // Function to display all candidates in the ballot
    void listCandidates() {
        if (candidates.empty()) {
            cout << "No candidates in the ballot." << endl;
            return;
        }

        // Sort candidates by votes in ascending order
        sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) {
            return a.votes < b.votes;
        });

        cout << "Candidates in the ballot (sorted by votes):" << endl;
        for (const auto& candidate : candidates) {
            cout << "Name: " << candidate.name << ", Votes: " << candidate.votes << endl;
        }
    }
    
    // Function to save ballot to a file
    void exportBallot(const string& filename) {
        ofstream FileOut(filename);
        if (FileOut.is_open()) {
            for (const auto& candidate : candidates) {
                FileOut << candidate.name << "," << candidate.votes << endl;
            }
            cout << "Ballot saved to file." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Function to load ballot from a file
    void importBallot(const string& filename) {
        ifstream FileIn(filename);
        if (FileIn.is_open()) {
            candidates.clear(); // Clear existing candidates
            string line;
            while (getline(FileIn, line)) {
                size_t pos = line.find(',');
                if (pos != string::npos) {
                    string name = line.substr(0, pos);
                    int votes = stoi(line.substr(pos + 1));
                    candidates.push_back({name, votes});
                }
            }
            cout << "Ballot loaded from file." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }
};

int main() {
    Ballot ballot;

    // Load ballot from file if it exists
    ballot.importBallot("ballot.txt");

    while (true) {
        cout << "\nVoting Ballot Management System\n";
        cout << "1. Add Candidate\n";
        cout << "2. Update Candidate\n";
        cout << "3. Remove Candidate\n";
        cout << "4. Display Candidates\n";
        cout << "5. Save Ballot to File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string name;
            int votes = 0; // New candidates start with 0 votes

            cout << "Enter candidate name: ";
            cin.ignore();
            getline(cin, name);


            Candidate newCandidate = {name, votes};
            ballot.addCandidate(newCandidate);
        } 
        else if (choice == 2) {
            string name;
            cout << "Enter name of the candidate to update: ";
            cin.ignore();
            getline(cin, name);

            Candidate updatedCandidate;
            cout << "Enter updated name: ";
            getline(cin, updatedCandidate.name);

            cout << "Enter updated votes: ";
            cin >> updatedCandidate.votes;

            ballot.modifyCandidate(name, updatedCandidate);
        } 
        else if (choice == 3) {
            string name;
            cout << "Enter name of the candidate to remove: ";
            cin.ignore();
            getline(cin, name);
            ballot.deleteCandidate(name);
        } 
        else if (choice == 4) {
            ballot.listCandidates();
        } 
        else if (choice == 5) {
            ballot.exportBallot("ballot.txt");
        } 
        else if (choice == 6) {
            cout << "Exiting program. Goodbye!";
            return 0;
        } 
        else {
            cout << "Invalid choice. Please try again.";
        }
    }

    return 0;
}
