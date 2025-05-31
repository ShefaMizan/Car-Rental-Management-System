#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Car {
public:
    int carID;
    string companyName;
    string model;
    int year;
    double price;
    bool availability;

    Car(int id, string company, string mdl, int yr, double prc, bool avail)
        : carID(id), companyName(company), model(mdl), year(yr), price(prc), availability(avail) {}
};

class User {
public:
    string username;
    string password;

    User(string usr, string pass)
        : username(usr), password(pass) {}
};

class Rental {
public:
    int rentalID;
    string username;
    int carID;
    int rentalDays;

    Rental(int id, string usr, int car, int days)
        : rentalID(id), username(usr), carID(car), rentalDays(days) {}
};

class CarRentalSystem {
private:
    vector<Car> cars;
    vector<User> users;
    vector<Rental> rentals;

public:
    void readCarsFromFile() {
        ifstream file("cars.txt");
        if (file.is_open()) {
            int id, year;
            string company, model;
            double price;
            bool avail;
            while (file >> id >> company >> model >> year >> price >> avail) {
                cars.push_back(Car(id, company, model, year, price, avail));
            }
            file.close();
        }
    }

    void writeCarsToFile() {
        ofstream file("cars.txt");
        if (file.is_open()) {
            for (const Car &car : cars) {
                file << car.carID << " " << car.companyName << " " << car.model << " " << car.year << " " << car.price << " " << car.availability << endl;
            }
            file.close();
        }
    }

    void readUsersFromFile() {
        ifstream file("users.txt");
        if (file.is_open()) {
            string username, password;
            while (file >> username >> password) {
                users.push_back(User(username, password));
            }
            file.close();
        }
    }

    void writeUsersToFile() {
        ofstream file("users.txt");
        if (file.is_open()) {
            for (const User &user : users) {
                file << user.username << " " << user.password << endl;
            }
            file.close();
        }
    }

    void readRentalsFromFile() {
        ifstream file("rentals.txt");
        if (file.is_open()) {
            int id, carID, days;
            string username;
            while (file >> id >> username >> carID >> days) {
                rentals.push_back(Rental(id, username, carID, days));
            }
            file.close();
        }
    }

    void writeRentalsToFile() {
        ofstream file("rentals.txt");
        if (file.is_open()) {
            for (const Rental &rental : rentals) {
                file << rental.rentalID << " " << rental.username << " " << rental.carID << " " << rental.rentalDays << endl;
            }
            file.close();
        }
    }

    int generateCarID() {
        if (cars.empty()) {
            return 1;
        }
        return cars.back().carID + 1;
    }

    int generateRentalID() {
        if (rentals.empty()) {
            return 1;
        }
        return rentals.back().rentalID + 1;
    }

    void addCar() {
        int id = generateCarID();
        string company, model;
        int year;
        double price;
        bool avail;
        cout << "Enter company name: ";
        cin >> company;
        cout << "Enter model: ";
        cin >> model;
        cout << "Enter year: ";
        cin >> year;
        cout << "Enter price: ";
        cin >> price;
        cout << "Is available? (1 for available, 0 for not available): ";
        cin >> avail;
        cars.push_back(Car(id, company, model, year, price, avail));
        writeCarsToFile();
    }

    void modifyCar() {
        int id;
        cout << "Enter the car ID to modify: ";
        cin >> id;
        for (Car &car : cars) {
            if (car.carID == id) {
                string company, model;
                int year;
                double price;
                bool avail;
                cout << "Enter new company name: ";
                cin >> company;
                cout << "Enter new model: ";
                cin >> model;
                cout << "Enter new year: ";
                cin >> year;
                cout << "Enter new price: ";
                cin >> price;
                cout << "Is available? (1 for available, 0 for not available): ";
                cin >> avail;
                car.companyName = company;
                car.model = model;
                car.year = year;
                car.price = price;
                car.availability = avail;
                writeCarsToFile();
                cout << "Car modified successfully!" << endl;
                return;
            }
        }
        cout << "Car not found with ID: " << id << endl;
    }



    void removeCar() {
        int id;
        cout << "Enter the car ID to remove: ";
        cin >> id;
        int indexToRemove = -1;

        for (int i = 0; i < cars.size(); ++i) {
            if (cars[i].carID == id) {
                indexToRemove = i;
                break;
            }
        }

        if (indexToRemove != -1) {
            cars.erase(cars.begin() + indexToRemove);
            writeCarsToFile();
            cout << "Car removed successfully!" << endl;
        } else {
            cout << "Car not found with ID: " << id << endl;
        }
    }

    void viewAllCars() {
        cout << "Car ID | Company Name | Model | Year | Price | Availability" << endl;
        for (const Car &car : cars) {
            cout << car.carID << " | " << car.companyName << " | " << car.model << " | " << car.year << " | " << car.price << " | " << (car.availability ? "Available" : "Not Available") << endl;
        }
    }

    void adminPanel() {
        string username, password;
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;
        if (username == "admin" && password == "adminpass") {
            int choice;
            do {
                cout << "\nAdmin Panel\n";
                cout << "1. Add Car\n";
                cout << "2. Modify Car\n";
                cout << "3. Remove Car\n";
                cout << "4. View All Cars\n";
                cout << "5. View Rental History\n";
                cout << "6. Quit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                case 1: addCar(); break;
                case 2: modifyCar(); break;
                case 3: removeCar(); break;
                case 4: viewAllCars(); break;
                case 5: viewRentalHistory(); break;
                case 6: cout << "Exiting admin panel...\n"; break;
                default: cout << "Invalid choice, please try again.\n";
                }
            } while (choice != 6);
        } else {
            cout << "Invalid admin credentials.\n";
        }
    }

    void userPanel() {
        string username, password;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        if (isValidUser(username, password)) {
            int choice;
            do {
                cout << "\nUser Panel\n";
                cout << "1. View Available Cars\n";
                cout << "2. Search and Filter Cars\n";
                cout << "3. Rent a Car\n";
                cout << "4. Return a Car\n";
                cout << "5. View Personal Rental History\n";
                cout << "6. Quit\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                case 1: viewAvailableCars(); break;
                case 2: searchAndFilterCars(); break;
                case 3: rentCar(username); break;
                case 4: returnCar(username); break;
                case 5: viewPersonalRentalHistory(username); break;
                case 6: cout << "Exiting user panel...\n"; break;
                default: cout << "Invalid choice, please try again.\n";
                }
            } while (choice != 6);
        } else {
            cout << "Invalid user credentials.\n";
        }
    }

    bool isValidUser(const string &username, const string &password) {
        for (const User &user : users) {
            if (user.username == username && user.password == password) {
                return true;
            }
        }
        return false;
    }

    void viewAvailableCars() {
        cout << "Available Cars:\n";
        cout << "Car ID | Company Name | Model | Year | Price" << endl;
        for (const Car &car : cars) {
            if (car.availability) {
                cout << car.carID << " | " << car.companyName << " | " << car.model << " | " << car.year << " | " << car.price << endl;
            }
        }
    }

    void searchAndFilterCars() {
        double minPrice, maxPrice;
        cout << "Enter minimum price: ";
        cin >> minPrice;
        cout << "Enter maximum price: ";
        cin >> maxPrice;
        cout << "Filtered Cars:\n";
        cout << "Car ID | Company Name | Model | Year | Price" << endl;
        for (const Car &car : cars) {
            if (car.availability && car.price >= minPrice && car.price <= maxPrice) {
                cout << car.carID << " | " << car.companyName << " | " << car.model << " | " << car.year << " | " << car.price << endl;
            }
        }
    }

    void rentCar(const string &username) {
        int carID, rentalDays;
        cout << "Enter the Car ID to rent: ";
        cin >> carID;
        cout << "Enter the number of rental days: ";
        cin >> rentalDays;
        for (Car &car : cars) {
            if (car.carID == carID && car.availability) {
                int rentalID = generateRentalID();
                car.availability = false;
                rentals.push_back(Rental(rentalID, username, carID, rentalDays));
                writeCarsToFile();
                writeRentalsToFile();
                cout << "Car rented successfully! Rental ID: " << rentalID << endl;
                return;
            }
        }
        cout << "Car not found or not available with ID: " << carID << endl;
    }



    void returnCar(const string &username) {
        int rentalID;
        cout << "Enter the Rental ID to return: ";
        cin >> rentalID;
        int indexToReturn = -1;

        for (int i = 0; i < rentals.size(); ++i) {
            if (rentals[i].rentalID == rentalID && rentals[i].username == username) {
                indexToReturn = i;
                break;
            }
        }

        if (indexToReturn != -1) {
            Rental &rental = rentals[indexToReturn];
            for (Car &car : cars) {
                if (car.carID == rental.carID) {
                    car.availability = true;
                    break;
                }
            }
            rentals.erase(rentals.begin() + indexToReturn);
            writeCarsToFile();
            writeRentalsToFile();
            cout << "Car returned successfully!\n";
        } else {
            cout << "Rental not found with ID: " << rentalID << endl;
        }
    }

    void viewRentalHistory() {
        cout << "Rental History:\n";
        cout << "Rental ID | Username | Car Model | Rental Days" << endl;
        for (const Rental &rental : rentals) {
            cout << rental.rentalID << " | " << rental.username << " | " << getCarModel(rental.carID) << " | " << rental.rentalDays << endl;
        }
    }

    string getCarModel(int carID) {
        for (const Car &car : cars) {
            if (car.carID == carID) {
                return car.model;
            }
        }
        return "Unknown";
    }

    void viewPersonalRentalHistory(const string &username) {
        cout << "Personal Rental History for " << username << ":\n";
        cout << "Rental ID | Car Model | Rental Days" << endl;
        for (const Rental &rental : rentals) {
            if (rental.username == username) {
                cout << rental.rentalID << " | " << getCarModel(rental.carID) << " | " << rental.rentalDays << endl;
            }
        }
    }

    void run() {
        readCarsFromFile();
        readUsersFromFile();
        readRentalsFromFile();
        int choice;
        do {
            cout << "\nMain Menu\n";
            cout << "1. Sign In\n";
            cout << "2. Sign Up\n";
            cout << "3. Quit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1: signIn(); break;
            case 2: signUp(); break;
            case 3: cout << "Exiting the program...\n"; break;
            default: cout << "Invalid choice, please try again.\n";
            }
        } while (choice != 3);
    }

    void signIn() {
        int userType;
        cout << "Choose user type:\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "Enter your choice: ";
        cin >> userType;
        switch (userType) {
        case 1: adminPanel(); break;
        case 2: userPanel(); break;
        default: cout << "Invalid choice, returning to main menu...\n";
        }
    }

    void signUp() {
        string username, password;
        cout << "Enter your desired username: ";
        cin >> username;
        cout << "Enter your desired password: ";
        cin >> password;

        users.push_back(User(username, password));
        writeUsersToFile();
        cout << "User registered successfully!\n";
    }
};

int main() {
    CarRentalSystem system;
    system.run();
    return 0;
}
