#include <iostream>
using namespace std;

class Student;
class Mentor;
class Skill {
public:
    int skillID;
    string skillName;
	string description;
    Skill() : skillID(0), skillName(""), description("") {}

    Skill(int id, string name, string des) : skillID(id), skillName(name), description(des) {}
    void showskillDetails(){
    	cout<<"skill ID: "<<skillID<<endl;
    	cout<<"skill name: "<<skillName<<endl;
    	cout<<"skill Description: "<<description<<endl;
    	
	}
	void updateSkillDescription(string NewDescription){
		description=NewDescription;
		
	}
};

class Sport {
public:
    int id;
    string name;
    string description;
    Skill requiredSkills[5];
    int currentSkills;
    Sport() : id(0), name(""), description(""), currentSkills(0) {}
    Sport(int i, string n, string d) : id(i), name(n), description(d), currentSkills(0) {}
    void addSkill(const Skill& s) {
        if (currentSkills < 5) {
            requiredSkills[currentSkills++] = s;
        }
    }

    void removeSkill(const Skill& s) {
        for (int i = 0; i < currentSkills; ++i) {
            if (requiredSkills[i].skillID == s.skillID) {
                for (int j = i; j < currentSkills - 1; ++j) {
                    requiredSkills[j] = requiredSkills[j + 1];
                }
                requiredSkills[currentSkills - 1] = Skill();
                currentSkills--;
                break;
            }
        }
    }
};

class Student {
public:
    int studentID;
    string name;
    int age;
    Sport sportsInterests[5]; 
    int currentInterests;
    Mentor* mentorAssigned;

    Student(int id, string n, int a) : studentID(id), name(n), age(a), mentorAssigned(nullptr), currentInterests(0) {}

    void registerForMentorship(Mentor& m);

    void viewMentorDetails();

    void updateSportsInterest(const Sport& s) {
        if (currentInterests < 5) {
            sportsInterests[currentInterests++] = s;
            cout << "Sport interest updated!" << endl;
        } else {
            cout << "Cannot add more sports interests." << endl;
        }
    }
};

class Mentor {
public:
    int mentorID;
    string name;
    Sport sportsExpertise[5];
    int maxLearners;
    Student* assignedLearners[10];
    int currentLearners;

    Mentor(int id, string n, int max) : mentorID(id), name(n), maxLearners(max), currentLearners(0) {}

    void assignLearner(Student* s) {
        if (currentLearners < maxLearners) {
            assignedLearners[currentLearners++] = s;
            cout << "Student assigned to mentor successfully!" << endl;
        } else {
            cout << "Capacity full!" << endl;
        }
    }

    void removeLearner(Student* s) {
        for (int i = 0; i < currentLearners; ++i) {
            if (assignedLearners[i] == s) {
                for (int j = i; j < currentLearners - 1; ++j) {
                    assignedLearners[j] = assignedLearners[j + 1];
                }
                assignedLearners[currentLearners - 1] = nullptr;
                currentLearners--;
                cout << "Student removed successfully!" << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    }

    void viewLearners() {
        if (currentLearners == 0) {
            cout << "No learners assigned." << endl;
            return;
        }
        cout << "Learners under mentor " << name << ":" << endl;
        for (int i = 0; i < currentLearners; ++i) {
            cout << assignedLearners[i]->name << " (ID: " << assignedLearners[i]->studentID << ")" << endl;
        }
    }

    void provideGuidance() {
        string guidance;
        cout << "Enter guidance: ";
        cin>>guidance;
        cout << "Guidance provided!!" << endl;
    }
};
 void Student :: registerForMentorship(Mentor& m) {
        if (m.currentLearners >= m.maxLearners) {
            cout << "Space not available." << endl;
        } else {
            mentorAssigned = &m;
            m.assignLearner(this);
        }
    }
    
    void Student :: viewMentorDetails() {
        if (mentorAssigned == nullptr) {
            cout << "No mentor assigned." << endl;
        } else {
            cout << "Mentor ID: " << mentorAssigned->mentorID << endl;
            cout << "Mentor Name: " << mentorAssigned->name << endl;
            cout << "Sports Expertise: ";
            for (int i = 0; i < 5; ++i) {
                if (!mentorAssigned->sportsExpertise[i].name.empty()) {
                    cout << "ID: " << mentorAssigned->sportsExpertise[i].id << ", Name: "
                         << mentorAssigned->sportsExpertise[i].name << ", Description: "
                         << mentorAssigned->sportsExpertise[i].description;
                    cout << " | ";
                }
            }
            cout << endl;
        }
    }



int main() {
    Mentor m1(101, "Coach Aashir", 3);
    m1.sportsExpertise[0] = Sport(1, "Football", "Team sport played with a spherical ball");
    m1.sportsExpertise[1] = Sport(2, "Basketball", "Sport played on a rectangular court");
    m1.sportsExpertise[0].addSkill(Skill(1, "Kicking","should know kicking"));
    m1.sportsExpertise[0].addSkill(Skill(2, "Running","should be fast"));
    Student s1(1, "Arshia", 20);
    Student s2(2, "Alishba", 21);
    s1.updateSportsInterest(Sport(3, "Tennis", "Racquet sport played individually"));
    s2.updateSportsInterest(Sport(4, "Soccer", "Most popular sport worldwide"));
    s1.registerForMentorship(m1);
    s2.registerForMentorship(m1);
    s1.viewMentorDetails();
    m1.viewLearners();
    m1.provideGuidance();
    m1.removeLearner(&s1);
    m1.viewLearners();
    return 0;
}
