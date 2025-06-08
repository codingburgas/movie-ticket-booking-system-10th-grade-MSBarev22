#include "user.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct User {
    string username;
    string password;
};

vector<User> users;

void loadUsers() {
    ifstream in("users.txt");
    User u;
    while (in >> u.username >> u.password) users.push_back(u);
    in.close();
}

void saveUser(const string& username, const string& password) {
    ofstream out("users.txt", ios::app);
    out << username << " " << password << endl;
    out.close();
    users.push_back({ username, password });
}

bool login(string& loggedUser) {
    string user, pass;
    cout << "Username: "; cin >> user;
    cout << "Password: "; cin >> pass;
    for (auto& u : users) {
        if (u.username == user && u.password == pass) {
            loggedUser = user;
            return true;
        }
    }
    cout << "Invalid login.\n";
    return false;
}

void signup() {
    string user, pass;
    cout << "Choose username: "; cin >> user;
    cout << "Choose password: "; cin >> pass;
    saveUser(user, pass);
    cout << "Registered successfully.\n";
}
