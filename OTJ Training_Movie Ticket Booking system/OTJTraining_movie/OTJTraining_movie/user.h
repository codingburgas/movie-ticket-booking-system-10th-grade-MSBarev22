#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

void loadUsers();
void saveUser(const string& username, const string& password);
bool login(string& loggedUser);
void signup();

#endif
