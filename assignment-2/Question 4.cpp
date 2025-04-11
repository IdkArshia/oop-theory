#include <iostream>
#include <string>
using namespace std;

const int MAX_ASSIGNMENTS=10;
const int MAX_TA_STUDENTS=10;
const int MAX_TA_PROJECTS=2;

unsigned long hashPassword(const string& password){
    unsigned long hash=5381;
    for(int i=0;i<password.length();i++){
        hash=hash*33+password[i];
    }
    return hash;
}

class User{
protected:
    string name;
    int id;
    string email;
    string permissions[5];
    int permissionCount;
    unsigned long hashed_password;
public:
    User(string name,int id,string email,string password,string perms[],int permCount):name(name),id(id),email(email),permissionCount(permCount){
        hashed_password=hashPassword(password);
        for(int i=0;i<permCount;i++){
            permissions[i]=perms[i];
        }
    }
    bool authenticate(string password){
        return hashed_password==hashPassword(password);
    }
    virtual void display(){
        cout<<"Name:"<<name<<",ID:"<<id<<",Email:"<<email<<endl;
    }
    virtual void accessLab(){
        for(int i=0;i<permissionCount;i++){
            if(permissions[i]=="full_lab_access"){
                cout<<name<<" has access to the lab."<<endl;
                return;
            }
        }
        cout<<name<<" does not have access to the lab."<<endl;
    }
    bool hasPermission(string permission){
        for(int i=0;i<permissionCount;i++){
            if(permissions[i]==permission)return true;
        }
        return false;
    }
};

class Student:public User{
protected:
    int assignments[MAX_ASSIGNMENTS];
public:
    Student(string name,int id,string email,string password):User(name,id,email,password,new string[1]{"submit_assignment"},1){
        for(int i=0;i<MAX_ASSIGNMENTS;i++)assignments[i]=0;
    }
    void display(){
        cout<<"Student-";
        User::display();
    }
    void submitAssignment(int index){
        if(index>=0&&index<MAX_ASSIGNMENTS)assignments[index]=1;
    }
    void showAssignments(){
        for(int i=0;i<MAX_ASSIGNMENTS;i++){
            cout<<"Assignment "<<i<<":"<<(assignments[i]?"Submitted":"Not Submitted")<<endl;
        }
    }
};

class TA:public Student{
    Student* assignedStudents[MAX_TA_STUDENTS];
    string projects[MAX_TA_PROJECTS];
    int studentCount;
    int projectCount;
public:
    TA(string name,int id,string email,string password):Student(name,id,email,password){
        permissions[1]="view_projects";
        permissions[2]="manage_students";
        permissionCount=3;
        studentCount=0;
        projectCount=0;
    }
    void display(){
        cout<<"TA-";
        User::display();
    }
    void assignStudent(Student* s){
        if(hasPermission("manage_students")&&studentCount<MAX_TA_STUDENTS){
            assignedStudents[studentCount++]=s;
            cout<<"Student assigned to TA."<<endl;
        }else{
            cout<<"Cannot assign more students."<<endl;
        }
    }
    void addProject(string project){
        if(projectCount<MAX_TA_PROJECTS){
            projects[projectCount++]=project;
            cout<<"Project added."<<endl;
        }else{
            cout<<"Cannot assign more projects to TA."<<endl;
        }
    }
    void viewProjects(){
        for(int i=0;i<projectCount;i++){
            cout<<"Project "<<i+1<<":"<<projects[i]<<endl;
        }
    }
};

class Professor:public User{
public:
    Professor(string name,int id,string email,string password):User(name,id,email,password,new string[2]{"assign_projects","full_lab_access"},2){}
    void display(){
        cout<<"Professor-";
        User::display();
    }
    void assignProjectToTA(TA& ta,string project){
        ta.addProject(project);
    }
};

void authenticateAndPerformAction(User* user,string action){
    if(user->hasPermission(action)){
        cout<<"Action '"<<action<<"' performed by user."<<endl;
    }else{
        cout<<"Permission denied for action:"<<action<<endl;
    }
}

int main(){
    Student s("Arshia",1,"arshia@univ.com","pass123");
    TA ta("Ahmer",2,"ahmer@univ.com","pass456");
    Professor p("Basit",3,"basit@univ.com","secure789");
    s.display();
    ta.display();
    p.display();
    if(s.authenticate("pass123"))authenticateAndPerformAction(&s,"submit_assignment");
    if(ta.authenticate("pass456"))authenticateAndPerformAction(&ta,"view_projects");
    if(p.authenticate("secure789"))authenticateAndPerformAction(&p,"assign_projects");
    s.submitAssignment(2);
    s.showAssignments();
    ta.assignStudent(&s);
    ta.viewProjects();
    p.assignProjectToTA(ta,"AI Research");
    ta.viewProjects();
    return 0;
}
