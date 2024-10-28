#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

string select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();
    list<Goat> trip;
    again = true;
    while (again) {
        int choice = main_menu();
        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                cout << "A new goat has been added." << endl;
                break;
            case 2:
                if (!trip.empty()) {
                    delete_goat(trip);
                    cout << "A goat has been deleted." << endl;
                } else {
                    cout << "No goats to delete." << endl;
                }
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                again = false;
                cout << "Exiting Goat Manager 3001. Goodbye!" << endl;
                break;
        }
    }


    return 0;
}

int main_menu() {
  int choice;
  cout << "\n*** GOAT MANAGER 3001 ***" << endl;
  while (true) {
    cout << "[1] Add a goat\n[2] Delete a goat\n[3] List goats\n[4] "
            "Quit\nChoice --> ";
    cin >> choice;
    if (choice >= 1 && choice <= 4) {
      break;
    } else {
      cout << "Invalid input, try again" << endl;
    }
  }
  return choice;
}
void add_goat(list<Goat> &trip, string names[], string colors[]) {
  trip.push_back(Goat(names[rand() % SZ_NAMES], rand() % (MAX_AGE + 1),
                      colors[rand() % SZ_COLORS]));
}
void delete_goat(list<Goat> &trip) {
  string choice = select_goat(trip);
  for (auto it = trip.begin(); it != trip.end(); ++it) {
    if (it->get_name() == choice) {
      trip.erase(it);
      return;
    }
  }
}

void display_trip(list<Goat> trip) {
  int index = 1;
  for (auto it : trip) {

    cout << "[" << index++ << "] " << it.get_name() << " (" << it.get_age()
         << ", " << it.get_color() << ")" << endl;
  }
}
string select_goat(list<Goat> trip) {
  display_trip(trip);
  string choice;
  cout << "select a goat: ";
  cin >> choice;
  return choice;
}
