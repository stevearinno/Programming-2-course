#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
public:
    Student();
    Student(const string& name, int student_id);
    string fetch_name() const;
    int fetch_student_id() const;
    void print() const;
private:
    string name_;
    int    id_;


};

Student::Student( const string& name, int student_id ):
    name_(name), id_(student_id) {
}

string Student::fetch_name() const{
    return name_;
}

int Student::fetch_student_id() const{
    return id_;
}

void Student::print() const{
    cout << name_ << " " << id_ << endl;
}

string separateName(string nameScore){
    int colonPos = nameScore.find(":");
    return nameScore.substr(0,colonPos+1);
}

int separateScore(string nameScore){
    int colonPos = nameScore.find(":");
    string scoreStr = nameScore.substr(colonPos+1, nameScore.length()-(colonPos+1));
    int scoreInt = stoi(scoreStr);
    return scoreInt;
}

bool compare_names(const Student& stud1, const Student& stud2) {
    if ( stud1.fetch_name() < stud2.fetch_name() ) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    string filename = "";
    string nameScore;
    vector <Student> students;
    //vector <Student>::iterator iter;

    //Student new_student(string name_, int score_);

    cout << "Input file: ";
    getline(cin, filename);

    ifstream file_object(filename);
    if ( not file_object ) {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return 1;
    }
    else {
        while ( getline(file_object, nameScore) ){
            Student new_student(separateName(nameScore), separateScore(nameScore));
            //students.push_back(new_student);
            int len = students.size();

            if (len >0){
                    bool flag= 1;
                    bool flag2=1;


                        while (flag){
                            for (int a = 0; a < len; a++){
                                if (students.at(a).fetch_name() == separateName(nameScore)){
                                    //bool flag2 = 1;
                                        while (flag2){
                                            int newScore = students.at(a).fetch_student_id() + separateScore(nameScore);
                                            Student new_student2(separateName(nameScore), newScore);
                                            students.at(a) = (new_student2);
                                            flag2 = 0;
                                        }

                                }
                            }
                            flag = 0;
                            if (flag2){
                                students.push_back(new_student);
                            }


                        }




            }
            else{
                students.push_back(new_student);         }


        }
        cout << "Final scores:" << endl;

        sort(students.begin(), students.end(), compare_names);


        for ( const auto& stud : students ) {
            stud.print();
        }

    }


}
