#include<iostream>
#include<tuple>
using namespace std;

class Robot
{
    private:
        string name;
        int hits;

    public:

    Robot():name("unnamed"),hits(0) {};
    

    Robot(string name):name(name), hits(0) {};
    
    void hitBall(int &ballX, int &ballY, const string &direction)
    {
        if(direction == "up")
        {
            ballY++;
        } else if(direction == "down") {
            ballY--;
        } else if(direction == "right") {
            ballX++;
        } else if(direction == "left") {
            ballX--;
        }
        hits++;
    }

    int getHits()
    {
        return hits;
    }
};

class Ball
{
    private:
        int x;
        int y;

    public:
        Ball(): x(0),y(0) {};

        Ball(int x, int y): x(x), y(y) {};

        int getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        void move(int dx, int dy)
        {
            x += dx;
            y += dy;
        }

        tuple<int, int> getPosition()
        {
            return make_tuple(x, y);
        }
};

class Goal
{
    private:
        int x;
        int y;

    public:
        Goal()
        {
            x = 3;
            y = 3;
        }

        bool isGoalReached(int ballX, int ballY)
        {
            return (ballX == x && ballY == y);
        }
};

class Team
{
    private:
        string teamName;
        Robot *robot;

    public:
        Team(string n, Robot *r)
        {
            teamName = n;
            robot = r;
        }

        Robot* getRobot()
        {
            return robot;
        }

        string getTeamName()
        {
            return teamName;
        }
};

class Game
{
    private:
        Team* teamOne;
        Team* teamTwo;
        Ball ball;
        Goal goal;

    public:
        Game(Team *t1, Team *t2)
        {
            teamOne = t1;
            teamTwo = t2;
        }

        void resetBall()
        {
            ball = Ball(0, 0);
        }

        void play(Team *t1)
        {
            Robot* robot = t1->getRobot();

            cout << "Team " << t1->getTeamName() << " playing now\n";

            while(!goal.isGoalReached(ball.getX(), ball.getY()))
            {
                string dir;
                cout << "Enter direction of the hit (up/down/right/left):";
                cin >> dir;
                if(dir != "up" && dir != "down" && dir != "right" && dir != "left")
                {
                    cout << "Invalid direction!\n";
                    continue;
                }
                int ballX = ball.getX();
                int ballY = ball.getY();
                robot->hitBall(ballX, ballY, dir);
                ball.move(ballX - ball.getX(), ballY - ball.getY());
                cout << "Ball position: (" << ball.getX() << ", " << ball.getY() << ")" << endl;
            }
            cout << "Team " << t1->getTeamName() << " has reached the goal in " << robot->getHits() << " hits\n";
        }

        void declareWinner()
        {
            int hits1 = teamOne->getRobot()->getHits();
            int hits2 = teamTwo->getRobot()->getHits();

            cout << teamOne->getTeamName() << " hits: " << hits1 << endl;
            cout << teamTwo->getTeamName() << " hits: " << hits2 << endl;

            if(hits1 < hits2)
            {
                cout << "--WINNER--Team\n " << teamOne->getTeamName();
            }
            else if(hits1 > hits2)
            {
                cout << "--WINNER--\nTeam " << teamTwo->getTeamName();
            }
            else
            {
                cout << "Game Tied!\n";
            }
        }

        void startGame()
        {
            cout << "-----GAME START-----\n";
            play(teamOne);
            resetBall();
            play(teamTwo);
            declareWinner();
        }
};

int main()
{
    Robot robot1("P1");
    Robot robot2("P2");
    Team teamOne("A", &robot1);
    Team teamTwo("B", &robot2);
    Game game(&teamOne, &teamTwo);
    game.startGame();
    return 0;
}
