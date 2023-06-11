#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

struct Person {
    std::string name;
    int age;
};

bool sorted_by_name_gt(const Person &person1, const Person &person2) {
    return person1.name < person2.name;
}

bool sorted_by_age_less(const Person &person1, const Person &person2) {
    return person1.age > person2.age;
}

void sort_persons(std::vector<Person> &persons, bool sort) {
    if (sort) {
        std::sort(persons.begin(), persons.end(), sorted_by_age_less);
    } else {
        std::sort(persons.begin(), persons.end(), sorted_by_name_gt);
    }
}

void json(const std::vector<Person> &persons, const std::string &filename) {
    std::ofstream file(filename);

    std::vector<Person> sortedByName = persons;
    sort_persons(sortedByName, false);

    std::vector<Person> sortedByAge = persons;
    sort_persons(sortedByAge, true);

    file << "{\n\t"
         << "\"sorted_by_name_gt\" : [";
    for (auto a = sortedByName.begin(); a != sortedByName.end(); ++a) {
        if (a != sortedByName.begin()) {
            file << ",";
        }
        file << "{"
             << "\"name\": \"" << a->name << "\","
             << "\"age\": " << a->age << ""
             << "}";
    }
    file << "],\n\t"
         << "\"sorted_by_age_less\" : [";
    for (auto a = sortedByAge.begin(); a != sortedByAge.end(); ++a) {
        if (a != sortedByAge.begin()) {
            file << ",";
        }
        file << "{"
             << "\"name\": \"" << a->name << "\","
             << "\"age\": " << a->age << ""
             << "}";
    }
    file << "]\n"
         << "}\n";
}

int main(int argc, char *argv[]) {
    std::vector<Person> persons;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        size_t pos = arg.find(':');
        if (pos != std::string::npos)
            persons.push_back({arg.substr(0, pos), std::stoi(arg.substr(pos + 1))});
    }

    //хорошее дополнение
    /*if (persons.empty()) {
        std::cerr << "no valid data" << std::endl;

        return 1;
    }*/

    json(persons, "sort.json");

    return 0;
}