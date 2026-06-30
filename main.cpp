#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <iterator>
#include <fstream>

#include <windows.h>

using namespace std;

/*
    Decription: Create and solve your own questions to prepare for exams.
    Author: jo.percht@gmail.com
*/

//CONSTANTS 1
time_t timestamp = time(&timestamp);
struct tm datetime = *localtime(&timestamp);
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static auto randomizer = default_random_engine {seed};
static HANDLE hConsole;
const string name = "HCW Tester";
vector<string> 
    mark_true = {"True", "Yes", "t", "y"}, 
    mark_false = {"False", "No", "f", "n"};
int 
    score = 0,
    i = 0,
    release = 0,
    serial = 0,
    modified_d = 0,
    modified_m = 0,
    modified_y = 0;

//TEMPLATES
template<typename Iter, typename RandomGenerator>
Iter random_select(Iter start, Iter end, RandomGenerator& g) {
    uniform_int_distribution<> dis(0, distance(start, end) - 1);
    advance(start, dis(g));
    return start;
}

//FUNCTIONS
string tab(int i = 1) {
    string s = "";

    while(i > 0) {
        s += "   ";
        --i;
    }

    return s;
}

string date(const int& d, const int& m, const int& y) {
    if(d < 10) return '0' + to_string(modified_d * 1000000 + modified_m * 10000 + modified_y);
    return to_string(modified_d * 1000000 + modified_m * 10000 + modified_y);
}

bool publish(const string& s) {
    return s == "dev -p";
}
bool update(const string& s) {
    return s == "dev -u";
}
bool quit(const string& s) {
    return s == "q";
}
bool back(const string& s) {
    return s == "r";
}

auto trim = [](string &s){
    while(!s.empty() && isspace((unsigned char)s.front())) s.erase(s.begin());
    while(!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
};

void lowercase(string& s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){return std::tolower(c);});
}

int read_in(string& s) {
    getline(cin, s);
    lowercase(s);
    trim(s);

    if(back(s)) {
        cout << endl;
        return 0;
    }
    else if(quit(s)) {
        cout << endl;
        return -1;
    }
    else if(update(s)) {
        modified_d = datetime.tm_mday;
        modified_m = datetime.tm_mon + 1;
        modified_y = datetime.tm_year + 1900;
        ofstream version_out("version.txt");

        version_out <<
        release << endl <<
        ++serial << endl <<
        modified_d << endl <<
        modified_m << endl <<
        modified_y;

        version_out.close();

        SetConsoleTextAttribute(hConsole, 5);
        cout << endl << "Updated: ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << name << " v" << release << '.' << serial << '.' << date(modified_d, modified_m, modified_y) << endl << endl;
        return -1;
    }
    else if(publish(s)) {
        serial = 0;
        modified_d = datetime.tm_mday;
        modified_m = datetime.tm_mon + 1;
        modified_y = datetime.tm_year + 1900;
        ofstream version_out("version.txt");

        version_out <<
        ++release << endl <<
        serial << endl <<
        modified_d << endl <<
        modified_m << endl <<
        modified_y;

        version_out.close();

        SetConsoleTextAttribute(hConsole, 5);
        cout << endl << "Released: ";
        SetConsoleTextAttribute(hConsole, 15);
        cout << name << " v" << release << '.' << serial << '.' << date(modified_d, modified_m, modified_y) << endl << endl;
        return -1;
    }

    return 1;
}

//OPERATOR OVERLOADS 1
vector<string> operator+(const string& s, const vector<string> &vs) {
    vector<string> out = vs;

    out.insert(out.begin(), s);

    return out;
}

vector<string> operator+(const vector<string> &vs, const string& s) {
    vector<string> out = vs;
    out.push_back(s);

    return out;
}

vector<string> operator+(const vector<string> &vs1, const vector<string> &vs2) {
    vector<string> out = vs1;
    for(const string& s : vs2) {
        out.push_back(s);
    }

    return out;
}

ostream &operator<<(ostream &os, const vector<string> &vs) {
    if(vs.size() == 1) {
        return os << vs[0];
    }
    else if(vs.size() < 1) return os;
    for (size_t i = 0; i < vs.size(); ++i) os << tab() << (i + 1) << ". " << vs[i] << endl;

    return os;
}

class Slut {
    private:
        //VARS
        int setting = 0;
        string spacing = tab(2);
        const vector<vector<string>> phrases = {
            {"Hai :3", "Hello there!", "Greetings traveler!", "Hi!", "<- Slut", "Egg!", "<- Babygurl", "They say I'm the bomb"},
            {"+1 Yay!", "+1 Great job!", "+1 Good job!", "+1 Good girl!", "+1 Wehehehe...", "+1 Mnghngnmnng...", "+1 I love you"},
            {"I am so informed!", "Wahh!", "Look at text", "Bah bah bah bang!", "So informative...", "Wow!", "Knowledge!"},
            {"+0 Nuh uh!", "+0 Sorry!", "+0 Stupid...", "+0 Wrong!", "+0 Idiot!", "+0 So close!", "+0 Nope!", "+0 You when you're wrong"},
            {"You did it!", "<- Perfect", "You're the best!", "HAHAHAHAAA!!", "Muhehehehe...", "I think you're cool AF"},
            {"You pass!", "<- No longer clocky", "Well, at least you didn't fail", "You know more than 60% of exam content", "You're mid"},
            {"AHHHHHHHHHH!!", "NOOOOOOOOO!!", "NOOOO WHY?!", "I hate my freaking chud life...", "Derpressed...", "Why so bad...", "You're a freaking chud!", "WAHHHH I HATE YOU!!", "You're stupid!", "You suck!", "Boo!", "Maybe next time"},
            {"Hello?", "Are you there?", "You didn't even type anything...", "Honk shoo mimimimiii...", "<- Sleeping", "I'm bored!", "Why not type something?"}
        };

        //FUNCTIONS
        bool lim_setting(const int& i) const {return !(i < 0 || i > 7);}

    public:
        //CONSTRUCTORS
        Slut() {}

        //GETTERS
        const int& get_set() const {
            return setting;
        }

        const string& space() const {
            return spacing;
        }

        //SETTERS
        const Slut& set(const int& i = 0, const string& s = "") {
            if(lim_setting(i)) setting = i;
            if(!s.empty()) spacing = s;

            return *this;
        }

        //FUNCTIONS
        const string& speak() const {
            return *random_select(phrases[setting].begin(), phrases[setting].end(), randomizer);
        }
};

//OPERATOR OVERLOADS 2
ostream& operator<<(ostream& os, const Slut& s) {
    switch(s.get_set()) {
        case 0:
        case 7:
            os <<
            s.space() << "{\\____/}" << endl <<
            s.space() << "(- ⩊  -)" << tab() << s.speak() << endl <<
            s.space() << " (    )っ" << endl <<
            s.space() << "  U¯¯U" << endl << endl;
            break;
        case 1:
        case 4:
            os <<
            s.space() << "{\\____/}" << endl <<
            s.space() << "(> ⩊  <)" << tab() << s.speak() << endl <<
            s.space() << " (    )っ" << endl <<
            s.space() << "  U¯¯U" << endl << endl;
            break;
        case 2:
        case 5:
            os <<
            s.space() << "{\\____/}" << endl <<
            s.space() << "(° ⩊  °)" << tab() << s.speak() << endl <<
            s.space() << " (    )っ" << endl <<
            s.space() << "  U¯¯U" << endl << endl;
            break;
        case 3:
        case 6:
            os <<
            s.space() << "{\\____/}" << endl <<
            s.space() << "(╥ ⩊  ╥)" << tab() << s.speak() << endl <<
            s.space() << " (    )っ" << endl <<
            s.space() << "  U¯¯U" << endl << endl;
            break;
    }
    return os;
}

//CONSTANTS 3
static Slut slut;

class Option {
    private:
        vector<string> text;
        bool value;

    public:
        //CONSTRUCTORS
        Option(const vector<string>& t, const bool& v) : text(t), value(v) {}

        //GETTERS
        const vector<string>& get_all_text() const {
            return text;
        }

        const bool& get_value() const {
            return value;
        }

        //FUNCTIONS
        string get_text() const {
            if(text.empty()) return "";
            return text[0];
        }
};

//OPERATOR OVERLOADS 3
ostream &operator<<(ostream &os, const Option& o) {
    return os << o.get_text();
}

ostream &operator<<(ostream &os, const vector<Option>& vo) {
    if(vo.size() == 1) return os << vo[0];
    else if(vo.size() < 1) return os;
    for (size_t i = 0; i < vo.size(); ++i) os << tab() << (i + 1) << ". " << vo[i] << endl;

    return os;
}

class Question {
    private:
        string text, answer_in;
        vector<Option> options;
        vector<vector<string>> answers;
        int setting;

    public:
        //GETTERS
        const vector<Option>& get_options() const {
            return options;
        }

        //OPERATOR OVERLOADS
        vector<Question> operator+(const vector<Question>& vq) const {
            vector<Question> out = vq;

            out.push_back(*this);

            return out;
        }
        vector<Question> operator+=(vector<Question>& vq) {
            vq.push_back(*this);

            return vq;
        }

        //FUNCTIONS 1
        vector<vector<string>> comp_answers() const {
            vector<vector<string>> ans;

            for(const Option& o : options) {
                if(o.get_value()) ans.push_back(o.get_all_text());
            }

            return ans;
        }

        //CONSTRUCTORS
        Question(const string& t, const vector<Option>& o, const int& set) : text(t), options(o) {
            answers = comp_answers();
            if(set >= -1 && set <= 3) setting = set;
            else {
                SetConsoleTextAttribute(hConsole, 5);
                cerr << "Failed to build Question!" << endl;

                return;
            }
        }
        Question(const string& t, const vector<Option>& o) : text(t), options(o) {
            answers = comp_answers();
            setting = 0;
        }

        //FUNCTIONS 2
        vector<string> get_answers() const {
            vector<string> vs;

            if(setting != -1) {
                for(vector<string> s : answers) {
                    if(!s.empty()) vs.push_back(s[0]);
                }
            }
            else {
                for(vector<string> s : answers) {
                    if(!s.empty()) vs.push_back(s[s.size() - 1]);
                }
            }

            return vs;
        }

        int ask() {
            SetConsoleTextAttribute(hConsole, 15);
            cout << text << endl << endl;
            
            SetConsoleTextAttribute(hConsole, 15);
            if(!answers.empty() && setting != 1) {
                if(setting == 0) {
                    shuffle(options.begin(), options.end(), randomizer);
                }
                
                SetConsoleTextAttribute(hConsole, 7);
                cout << options << endl;
            }
            SetConsoleTextAttribute(hConsole, 11);
            cout << "Your answer: ";
            
            if(!answers.empty()) {
                int i = 0;
                vector<string> answers_found;
                for(const vector<string>& va : answers) {
                    bool found = 0, digit = 1;

                    SetConsoleTextAttribute(hConsole, 15);
                    if(answers.size() > 1) {
                        if(i == 0) cout << endl << endl << tab() << ++i << ". ";
                        else cout << tab() << ++i << ". ";
                    }
                    int code = read_in(answer_in);
                    if(code < 1) return code;

                    if(answer_in != "") {
                        for(const char& c : answer_in) {
                            if(!isdigit(c)) digit = 0;
                        }
                        if(digit && count(answers_found.begin(), answers_found.end(), answer_in) == 0) {
                            if(stoi(answer_in) - 1 < options.size()) {
                                if(options[stoi(answer_in) - 1].get_value() && setting != 1) {
                                    found = 1;
                                }
                            }
                        }
                        if(found == 0) {
                            for(string a : va) {
                                lowercase(a);
                                trim(a);
                                if(answer_in == a && count(answers_found.begin(), answers_found.end(), answer_in) == 0) {
                                    found = 1;
                                }
                            }
                        }
                        answers_found.push_back(answer_in);
                    }
                    
                    if(!found) {
                        cout << endl;
                        if(setting == 3) return 0;
                        if(setting != 2) {
                            vector<string> vs = get_answers();
                            SetConsoleTextAttribute(hConsole, 4);
                            if(answer_in == "") {
                                if(vs[0] != "") {
                                    if(answers.size() > 1) cout << slut.set(7) << tab() << "Correct answers: " << endl << endl << get_answers() << endl;
                                    else cout << slut.set(7) << tab() << "Correct answer: " << get_answers() << endl << endl;
                                }
                                else cout << slut.set(7) << tab() << "Statement was correct!" << endl << endl;
                            }
                            else if(vs[0] != "") {
                                if(answers.size() > 1) cout << slut.set(3) << tab() << "Correct answers: " << endl << endl << get_answers() << endl;
                                else cout << slut.set(3) << tab() << "Correct answer: " << get_answers() << endl << endl;
                            }
                            else cout << slut.set(3) << tab() << "Statement was correct!" << endl << endl;
                            SetConsoleTextAttribute(hConsole, 5);
                            cout << "Score: ";
                            SetConsoleTextAttribute(hConsole, 4);
                            cout << score << endl << endl;
                        }

                        return 1;
                    }
                }

                if(setting < 2) {
                    vector<string> vs = get_answers();
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << endl;
                    if(setting != -1) cout << slut.set(1);
                    else if(vs[0] != "") cout << slut.set(1) << tab() << "Correct! " << vs << endl << endl;
                    else cout << slut.set(1) << tab() << "Correct answer!" << endl << endl;
                    SetConsoleTextAttribute(hConsole, 5);
                    cout << "Score: ";
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << ++score << endl << endl;
                }
                else cout << endl;
            }
            else {
                SetConsoleTextAttribute(hConsole, 15);
                int code = read_in(answer_in);
                if(code < 1) return code;

                if(setting < 2) {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << endl;
                    if(answer_in == "") {
                        if(options.size() > 1) cout << slut.set(7) << tab() << "Correct answers: " << endl << endl << options << endl;
                        else cout << slut.set(7) << tab() << "Correct answer: " << options << endl << endl;
                    }
                    else {
                        if(options.size() > 1) cout << slut.set(2) << tab() << "Correct answers: " << endl << endl << options << endl;
                        else cout << slut.set(2) << tab() << "Correct answer: " << options << endl << endl;
                    }
                    SetConsoleTextAttribute(hConsole, 5);
                    cout << "Score: ";
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << score << endl << endl;
                }
                else cout << endl;
            }

            return 1;
        }
};

//OPERATOR OVERLOADS 4
vector<Question> operator+(const vector<Question>& vq1, const vector<Question>& vq2) {
    vector<Question> out = vq1;

    for(const Question& q : vq2) {
        out.push_back(q);
    }

    return out;
}
vector<Question> operator+=(vector<Question>& vq1, const vector<Question>& vq2) {
    for(const Question& q : vq2) {
        vq1.push_back(q);
    }

    return vq1;
}

class Exam {
    private:
        string name;
        vector<Question> quests;

    public:
        //CONSTRUCTORS
        Exam(const string& n, const vector<Exam>& ve) : name(n) {
            for(const Exam& e : ve) {
                quests += e.quests;
            }
        }
        Exam(const string& n, const Exam& e) : name(n), quests(e.quests) {}
        Exam(const string& n, const vector<Question>& qs) : name(n), quests(qs) {}
        Exam(const string& n) : name(n) {}

        //GETTERS
        const string& get_name() const {
            return name;
        }

        const vector<Question>& get_quests() const {
            return quests;
        }

        // OPERATOR OVERLOADS
        Exam operator+(const Question& q) const {
            Exam out = *this;

            out.quests.push_back(q);

            return out;
        }
        Exam operator+=(const Question& q) {
            quests.push_back(q);

            return *this;
        }

        Exam operator+(const Exam& e) const {
            Exam out = *this;

            out.quests += e.quests;

            return out;
        }
        Exam operator+=(const Exam& e) {
            quests += e.quests;

            return *this;
        }

        Exam operator+(const vector<Exam> &ve) const {
            Exam out = *this;

            for(Exam e : ve) {
                for(const Question& q : e.get_quests()) {
                    out.quests.push_back(q);
                }
            }

            return out;
        }
        Exam operator+=(const vector<Exam> &ve) {
            for(Exam e : ve) {
                for(const Question& q : e.get_quests()) {
                    quests.push_back(q);
                }
            }

            return *this;
        }

        //FUNCTIONS
        void add(const string& text, const vector<vector<string>>& vs, const vector<bool>& vb = {}, int set = 0) {
            int lim = vs.size();
            vector<Option> vo;

            if(vb.empty()) {
                for(int i = 0; i < lim; ++i) {
                    vo.push_back(Option(vs[i], 0));
                }
                quests.push_back(Question(text, vo, 1));
            }
            else {
                if(lim != vb.size()) {
                    SetConsoleTextAttribute(hConsole, 5);
                    cerr << "Failed to build Question!" << endl;

                    return;
                }
                for(int i = 0; i < lim; ++i) {
                    vo.push_back(Option(vs[i], vb[i]));
                }
                quests.push_back(Question(text, vo, set));
            }
        }

        int size() const {
            int s = 0;
            for(const Question& q : quests) {
                if (!q.get_options().empty() && !q.get_answers().empty()) ++s;
            }

            return s;
        }

        int true_size() const {
            return quests.size();
        }

        int solve() {
            score = 0;
            const int max_score = size();
            int size = true_size(), q_curr = 1;
            
            SetConsoleTextAttribute(hConsole, 5);
            cout << "Exam: " << name << endl << endl <<
            "* * * START * * *" << endl << endl;
            shuffle(begin(quests), end(quests), randomizer);
            for(Question& q : quests) {
                SetConsoleTextAttribute(hConsole, 5);
                cout << '[' << to_string(q_curr) << '/' + to_string(size) << "] ";

                int code = q.ask();
                if(code < 1) return code;

                ++q_curr;
            }

            SetConsoleTextAttribute(hConsole, 5);
            cout << "* * * FINISHED * * *" << endl << endl <<
            "Exam: " << name << endl << endl <<
            "Your exam score: " << score << '/' << max_score << endl << endl;
            if(score == max_score) {
                SetConsoleTextAttribute(hConsole, 2);
                cout << slut.set(4) << "   Perfect score!" << endl << endl;
                SetConsoleTextAttribute(hConsole, 5);
                cout << "- - - RESTART - - -" << endl << endl;

                return 2;
            }
            else if (score * 100 >= max_score * 60) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << slut.set(5) << "    You passed!" << endl << endl;
                SetConsoleTextAttribute(hConsole, 5);
                cout << "- - - RESTART - - -" << endl << endl;

                return 1;
            }
            SetConsoleTextAttribute(hConsole, 4);
            cout << slut.set(6) << "    You failed!" << endl << endl;
            SetConsoleTextAttribute(hConsole, 5);
            cout << "- - - RESTART - - -" << endl << endl;

            return 0;
        }
};

class Topic {
    private:
        string name;
        vector<Exam> exams;

    public:
        //CONSTRUCTORS
        Topic(const string& s, const vector<Exam>& ve) : name(s), exams(ve) {};
        Topic(const string& s) : name(s) {};

        //GETTERS
        const string& get_name() const {
            return name;
        }

        //FUNCTIONS
        int size() const {
            return exams.size();
        }

        void add(const Exam& e) {
            exams.push_back(e);
        }

        int run() {
            string answer_in;
            Exam chosen("null");
            string te;
            int i = 0, k = 1;

            SetConsoleTextAttribute(hConsole, 5);
            cout << "[Exams] ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << name << endl << endl;

            SetConsoleTextAttribute(hConsole, 7);
            for(Exam& e : exams) {
                SetConsoleTextAttribute(hConsole, 7);
                cout << tab() << ++i << ". " << e.get_name();
                SetConsoleTextAttribute(hConsole, 5);
                cout << " (";
                SetConsoleTextAttribute(hConsole, 7);
                cout << to_string(e.true_size());
                SetConsoleTextAttribute(hConsole, 5);
                cout << ')' << endl;
            }
            cout << endl;

            SetConsoleTextAttribute(hConsole, 11);
            cout << "Your answer: ";

            SetConsoleTextAttribute(hConsole, 15);
            int code = read_in(answer_in);
            if(code < 1) return code;

            for(Exam& e : exams) {
                te = e.get_name();
                lowercase(te);
                trim(te);

                if(te == answer_in || answer_in == to_string(k)) {
                    chosen = e;

                    cout << endl;
                    if(chosen.solve() < 0) return -1;
                    if(run() < 0) return -1;

                    return 0;
                }

                ++k;
            }
            cout << endl;

            return 0;
        }
};

class Tester {
    private:
        vector<Topic> topics;

    public:
        //CONSTRUCTORS
        Tester(const vector<Topic>& vf) : topics(vf) {};
        Tester() {};

        //FUNCTIONS
        void add(const Topic& f) {
            topics.push_back(f);
        }

        int run() {
            string answer_in;
            Topic chosen("null");
            string tt;
            int i = 0, k = 1;

            SetConsoleTextAttribute(hConsole, 5);
            cout << "[Topics] ";
            SetConsoleTextAttribute(hConsole, 15);
            cout << name << endl << endl;

            SetConsoleTextAttribute(hConsole, 7);
            for(Topic& t : topics) {
                SetConsoleTextAttribute(hConsole, 7);
                cout << tab() << ++i << ". " << t.get_name();
                SetConsoleTextAttribute(hConsole, 5);
                cout << " (";
                SetConsoleTextAttribute(hConsole, 7);
                cout << to_string(t.size());
                SetConsoleTextAttribute(hConsole, 5);
                cout << ')' << endl;
            }
            cout << endl;

            SetConsoleTextAttribute(hConsole, 11);
            cout << "Your answer: ";

            SetConsoleTextAttribute(hConsole, 15);
            int code = read_in(answer_in);
            if(code < 1) return code;

            for(Topic& t : topics) {
                tt = t.get_name();
                lowercase(tt);
                trim(tt);

                if(tt == answer_in || answer_in == to_string(k)) {
                    chosen = t;
                    
                    cout << endl;
                    if(chosen.run() < 0) return -1;
                    if(run() < 0) return -1;
                    return 0;
                }

                ++k;
            }
            cout << endl;

            return 0;
        }
};

int main() {
    //CONSTANTS 1
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    string file_in;
    ifstream version_in("version.txt");

    while(getline(version_in, file_in)) {
        lowercase(file_in);
        trim(file_in);

        switch(i) {
            case 0:
                release = stoi(file_in);
                break;
            case 1:
                serial = stoi(file_in);
                break;
            case 2:
                modified_d = stoi(file_in);
                break;
            case 3:
                modified_m = stoi(file_in);
                break;
            case 4:
                modified_y = stoi(file_in);
                break;
        }

        ++i;
    }
    version_in.close();

    vector<string> 
        mark_true_menu = {"Yes", "True", "y", "t"},
        mark_false_menu = {"No", "False", "n", "f"};
    Question run = {"Ready to start your exam?", {
        Option({mark_true_menu}, 1),
        Option({mark_false_menu}, 0)
    }, 3};

    /*
        add() templates:
            myExam.add(string text, vector<vector<string>> answers, vector<bool> answer_values);                Regular
            myExam.add(string text, vector<vector<string>> answers, vector<bool> answer_values, int setting);   setting(-1 = display last answers, 0 = regular, 1 = options hidden, 2 = answers hidden, not graded, 3 = answers hidden)
            myExam.add(string text, vector<vector<string>> answers);                                            Options hidden, not graded

            neta.add("", {
                {}
            }, {});
    */

    //EXAMS
    Exam neta_net_recap("Networking Recap");
    neta_net_recap.add("What does IETF stand for?", {
        {"Internet Engineering Task Force"}
    }, {1}, 1);
    neta_net_recap.add("What does RFC stand for?", {
        {"Request for Comments"}
    }, {1}, 1);
    neta_net_recap.add("Who publishes the RFC?", {
        {"Internet Engineering Task Force", "IETF"}
    }, {1}, 1);
    neta_net_recap.add("The Internet Engineering Task Force is an open global community of network designers, operators, vendors, and researchers producing technical specifications for the evolution of the Internet architecture and the smooth operation of the Internet.", {
        {mark_true + ""},
        {mark_false}
    }, {1, 0}, -1);
    neta_net_recap.add("List all Layers of the OSI Model in order:", {
        {"Physical Layer", "Physical"},
        {"Data Link Layer", "Data Link", "Link Layer", "Link"},
        {"Network Layer", "Network"},
        {"Transport Layer", "Transport"},
        {"Session Layer", "Session"},
        {"Presentation Layer", "Presentation"},
        {"Application Layer", "Application"}
    }, {1, 1, 1, 1, 1, 1, 1}, 1);
    neta_net_recap.add("What is an IP Address?", {
        {"Internet Protocol"},
        {"A numeric label assigned to a Network Interface Controller (NIC)"},
        {"A unique identifier in the network"}
    });
    neta_net_recap.add("Name 5 Application Layer Protocols:", {
        {"DHCP", "FTP", "SMTP", "HTTP", "SSH", "Telnet", "SFTP", "HTTPS", "BGP", "POP3", "IMAP", "SCP", "DNS", "BOOTP", "SNMP", "Syslog", "NTP", "RIP", "RIP2"},
        {"HTTP", "DHCP", "FTP", "SMTP", "Telnet", "SFTP", "HTTPS", "BGP", "POP3", "IMAP", "SCP", "DNS", "BOOTP", "SNMP", "Syslog", "NTP", "RIP", "RIP2", "SSH"},
        {"FTP", "DHCP", "SMTP", "HTTP", "Telnet", "SFTP", "HTTPS", "BGP", "POP3", "IMAP", "SCP", "DNS", "BOOTP", "SNMP", "Syslog", "NTP", "RIP", "RIP2", "SSH"},
        {"DNS", "DHCP", "FTP", "SMTP", "HTTP", "Telnet", "SFTP", "HTTPS", "BGP", "POP3", "IMAP", "SCP", "BOOTP", "SNMP", "Syslog", "NTP", "RIP", "RIP2", "SSH"},
        {"SMTP", "DHCP", "FTP", "HTTP", "Telnet", "SFTP", "HTTPS", "BGP", "POP3", "IMAP", "SCP", "DNS", "BOOTP", "SNMP", "Syslog", "NTP", "RIP", "RIP2", "SSH"}
    }, {1, 1, 1, 1, 1}, 1);
    neta_net_recap.add("Name 2 Transport Layer Protocols:", {
        {"TCP", "UDP", "RTP"},
        {"UDP", "TCP", "RTP"}
    }, {1, 1}, 1);
    neta_net_recap.add("IP is a Network Layer Protocol.", {
        {mark_true + ""},
        {mark_false}
    }, {1, 0}, -1);
    neta_net_recap.add("Name 3 Network Layer Protocols:", {
        {"IP", "ARP", "ICMP", "IGMP", "RARP"},
        {"ARP", "ICMP", "IGMP", "RARP", "IP"},
        {"ICMP", "IGMP", "RARP", "IP", "ARP"}
    }, {1, 1, 1}, 1);
    neta_net_recap.add("Which statement is true?", {
        {"SSH operates on the Application and Transport Layer."},
        {"SSH operates solely on the Application Layer."},
        {"SSH operates solely on the Transport Layer."}
    }, {1, 0, 0});
    neta_net_recap.add("Which statement is true?", {
        {"ARP operates on the Network and Data Link Layer."},
        {"ARP operates solely on the Network Layer."},
        {"ARP operates solely on the Data Link Layer."}
    }, {1, 0, 0});
    neta_net_recap.add("Name a physical Protocol:", {
        {"Ethernet", "ALOHA", "CDMA", "GSM", "ISDN"}
    }, {1}, 1);
    neta_net_recap.add("Ethernet operates solely on the Physical Layer.", {
        {mark_true},
        {mark_false + "Ethernet operates on the Physical and Data Link Layer."}
    }, {0, 1}, -1);
    neta_net_recap.add("Name all elements of an IPv4 header:", {
        {"IP Protocol Version Number", "IP Version", "IP version number", "Protocol version number"},
        {"Header Length (Bytes)", "header length"},
        {"Type of Service", "type of data", "data type", "service type"},
        {"Total Datagram Length (Bytes)", "total datagram length", "datagram length", "length"},
        {"16-Bit Identifier", "identifier"},
        {"Flags"},
        {"Fragment Offset", "offset"},
        {"Time to Live", "ttl"},
        {"Upper Layer Protocol to Deliver Payload to", "upper layer protocol", "upper protocol", "upper layer"},
        {"Header Checksum", "checksum"},
        {"32-Bit Source IP Address", "Source IP", "Source IP Address", "Source Address", "Source"},
        {"32-Bit Destination IP Address", "Destination IP Address", "Destination IP", "Destination Address", "Destination"},
        {"Options (If Any)"},
        {"Data (Variable Length, Typically a TCP or UDP Segment)"}
    }, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1);
    neta_net_recap.add("Private IP addresses are routed through the internet.", {
        {mark_true},
        {mark_false + "Public IP addresses are routed through the internet."}
    }, {0, 1}, -1);
    neta_net_recap.add("What is ARP?", {
        {"Address Resolution Protocol (RFC 826)"},
        {"Finds Ethernet (MAC) address of a local IP address"},
        {"Host queries an address and the owner replies"},
    });
    neta_net_recap.add("What is ICMP?", {
        {"Internet Control Message Protocol (RFC 792)"},
        {"Used by hosts & routers to communicate network-level information"},
        {"Error reporting: unreachable host, network, port, protocol"},
        {"Echo request/reply (used by ping)"},
        {"ICMP msgs carried in IP datagrams"}
    });
    neta_net_recap.add("What is DHCP?", {
        {"Dynamic Host Configuration Protocol"},
        {"Assigns a local IP address to a host"},
        {"Gets host started by automatically configuring it"},
        {"Host sends request to server, which grants a lease"},
        {"Encapsulated in UDP datagram"}
    });
    neta_net_recap.add("IP addresses can be hard-coded or assigned through DHCP.", {
        {mark_true + ""},
        {mark_false}
    }, {1, 0}, -1);
    neta_net_recap.add("List all steps in a DHCP interaction in order:", {
        {"Host broadcasts DHCP discover message", "DHCP discover message", "DHCP discover", "discover"},
        {"DHCP server responds with DHCP offer message", "DHCP offer message", "DHCP offer", "offer"},
        {"Host requests IP address with DHCP request message", "DHCP request message", "DHCP request", "request"},
        {"DHCP server sends address with DHCP ack message", "DHCP ack message", "DHCP ack", "ack"}
    }, {1, 1, 1, 1}, 1);

    Exam neta_principles("Network Application Principles");
    neta_principles.add("Which are characteristics of a network application?", {
        {"Runs on different end systems"},
        {"Runs only on servers"},
        {"Communicates over networks"},
        {"Runs on different core systems"},
        {"Client-Server is a network application architecture"},
        {"Peer-To-Peer is a network application architecture"}
    }, {1, 0, 1, 0, 1, 1});

    Exam neta_dns("DNS");

    Exam neta_email("Email");

    Exam neta_hhqf("HTTP, HTTP2, QUIC, FTP");

    Exam neta_transport_layer("Transport Layer");

    Exam neta_nat("NAT");

    Exam neta_firewall("Firewall");

    Exam neta_troubleshooting("Troubleshooting");

    Exam neta_troubleshooting_tools("Troubleshooting Tools");

    Exam neta_all = {"All", {
        neta_net_recap,
        neta_principles,
        neta_dns,
        neta_email,
        neta_hhqf,
        neta_transport_layer,
        neta_nat,
        neta_firewall,
        neta_troubleshooting,
        neta_troubleshooting_tools
    }};

    //FOLDERS
    Topic neta("NETA", {
        neta_all,
        neta_net_recap,
        neta_principles,
        neta_dns,
        neta_email,
        neta_hhqf,
        neta_transport_layer,
        neta_nat,
        neta_firewall,
        neta_troubleshooting,
        neta_troubleshooting_tools
    });

    //TESTERS
    Tester tester({
        neta
    });

    //PROGRAM START
    SetConsoleTextAttribute(hConsole, 5);
    cout << endl << slut << "Welcome to " << name  << " v" << release << '.' << serial << '.' << date(modified_d, modified_m, modified_y) << '!' << endl << endl
    << '[';
    SetConsoleTextAttribute(hConsole, 15);
    cout << 'Q';
    SetConsoleTextAttribute(hConsole, 5);
    cout << "] = Quit" << endl
    << '[';
    SetConsoleTextAttribute(hConsole, 15);
    cout << 'R';
    SetConsoleTextAttribute(hConsole, 5);
    cout << "] = Back" << endl << endl;

    while(run.ask() > 0) {
        if(tester.run()) break;
    }

    return 0;
}
