#include<iostream>
#include<string>
using namespace std;
class Visitor;
class Ghost{
        
    public:
    	string Wname;
        int Slevel;
        Ghost(string n,int s):Wname(n),Slevel(s){};
        Ghost(){
        	Wname=" ";
        	Slevel=0;
		}
        void haunting(){}
        Ghost operator +(const Ghost &g){
            Ghost temp;
            temp.Wname = Wname + "&" + g.Wname;
            temp.Slevel = Slevel + g.Slevel;
            return temp;
        }
        friend ostream& operator<<(ostream &output,const Ghost &g);
        
};
class HauntedHouse{
    public:
        friend void visit(const HauntedHouse &h , Visitor v[4]);
        string name;
        Ghost *ghosts=new Ghost[3];
        HauntedHouse(string n, Ghost g1, Ghost g2, Ghost g3)
        {
            name=n;
            ghosts[0]=g1;
            ghosts[1]=g2;
            ghosts[2]=g3;
        }
};



ostream& operator<<(ostream &output,const Ghost &g){
    output << "worker name: " << g.Wname << "\nScare level: " << g.Slevel;
    return output;
}

class Poltergeist :virtual public Ghost{
    public:
        Poltergeist(string n, int s) : Ghost(n, s){}
        void haunting(){
            cout << "*objects move*";
        }
};

class Banshee :virtual public Ghost{
    public:
        Banshee(string n, int s) : Ghost(n, s){}
        void haunting(){
            cout << "*loud scream*";
        }
};

class ShadowGhost :virtual public Ghost{
    public:
        ShadowGhost(string n, int s) : Ghost(n, s){}
        void haunting(){
            cout << "*creepy whispers*";
        }
};

class ShadowPoltergeist : public ShadowGhost, public Poltergeist,virtual public Ghost{
    public:
        ShadowPoltergeist(string n, int s) : Ghost(n,s),ShadowGhost(n, s),Poltergeist(n, s){}
};

class ShadowBanshee : public ShadowGhost, public Banshee,virtual public Ghost{
    public:
        ShadowBanshee(string n, int s) : Ghost(n,s),ShadowGhost(n, s),Banshee(n, s){}
};

class PoltergeistBanshee : public Poltergeist, public Banshee,virtual public Ghost{
    public:
        PoltergeistBanshee(string n, int s) : Ghost(n,s),Banshee(n, s),Poltergeist(n, s){}
};

class Visitor {
    string name;
    int bravery;
    string braveryStatus;
    public:
        friend void visit(const HauntedHouse &h , Visitor v[4]);
        Visitor(string n, int b){
            name = n;
            bravery = b;
            if (bravery >= 1 && bravery <= 4){
                braveryStatus = "Cowardly";
            }
            else if (bravery >= 5 && bravery <= 7){
                braveryStatus = "Average";
            }
            if (bravery >= 8 && bravery <= 10){
                braveryStatus = "Fearless";
            }
        }
        void reactToGhost(const Ghost &g){
            if (braveryStatus == "Cowardly"){
                if (g.Slevel <= 4){
                    cout << name << " gets a shaky voice";
                }
                else if (g.Slevel > 4){
                    cout << name << " screams and runs away";
                }
            }
            else if (braveryStatus == "Average"){
                if (g.Slevel <= 4){
                    cout << name << " laughs and taunts the ghost";
                }
                else if (g.Slevel > 4 && g.Slevel <= 7){
                    cout << name << " gets a shaky voice";
                }
                else if (g.Slevel > 7){
                    cout << name << " screams and runs away";    
                }
            }
            else {
                if (g.Slevel <= 7){
                    cout << name << " laughs and taunts the ghost";
                }
                else if (g.Slevel > 7 && g.Slevel <= 10){
                    cout << name << " gets a shaky voice";
                }
            }
        }    
};

int main(){
    Poltergeist g1("Ahmer", 4);
    Banshee g2("Aashir", 6);
    ShadowGhost g3("Arshia", 9);
    ShadowPoltergeist g4("Laiba", 2);
    ShadowBanshee g5("Azeem", 8);
    PoltergeistBanshee g6("Sadaf", 7);
    HauntedHouse h1("Bhoot Bangla", g1, g3, g4), h2("Haunted Haweli", g2, g5, g6), h3("Scary Shack", g1, g5, g3);
    Visitor visitors[4] = {Visitor("Hamza", 5), Visitor("Salar", 7), Visitor("Ayesha", 3), Visitor("Rabia", 9)};
    visit(h1, visitors);
    cout<<"\n";
    visit(h2, visitors);
    cout<<"\n";
    visit(h3, visitors);
    Ghost g7 = g5+g6;
    cout<<g7;
}

void visit(const HauntedHouse &h , Visitor v[4]){
	cout<<"In "<<h.name;
    for (int i = 0; i < 3; ++i) {
        h.ghosts[i].haunting();
        cout<<"\n";
    }
    for (int i = 0; i < 4; ++i) {
        v[i].reactToGhost(h.ghosts[0]);
        cout<<"\n";
    }
}
