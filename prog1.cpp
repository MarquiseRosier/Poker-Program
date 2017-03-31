#include <regex>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

string stringify(const vector<string>& playerN){
	string ourString;

	for(vector<string>::size_type i = 0; i < playerN.size(); i++){
		ourString += playerN[i];
	}

	return ourString;
}

int assignPriority(char c){
	if(c == 'A'){
		return 14;
	}
	else if( c == 'K'){
		return 13;
	}
	else if(c == 'Q'){
		return 12;
	}
	else if (c == 'J'){
		return 11;
	}
	else if(c == 'T'){
		return 10;
	}
	else 
		return 0;
}


int checkHands(const vector<string>& playerN){
	string p = stringify(playerN);
	/*cout << p << endl;*/

	if((p.at(1) == p.at(3) == p.at(5) == p.at(7) == p.at(9))){
		return 5;}

		int counter = 0, r1s, r2s, r3s, r4s, r5s;

		string first = string("([1-9])") + string("(") + p.at(1) + ")";
		string second = string("([1-9])") + string("(") + p.at(3) + ")";
		string third = string("([1-9])") + string("(") + p.at(5) + ")";
		string fourth = string("([1-9])") + string("(") + p.at(7) + ")";
		string fifth = string("([1-9])") + string("(") + p.at(9) + ")";
/*
		cout << first << endl;
		cout << second << endl;
		cout << third << endl; 
		cout << fourth << endl;
		cout << fifth << endl;*/

		regex r1(first), r2(second), r3(third), r4(fourth), r5(fifth);

		regex_iterator<string::iterator> rit1(p.begin(), p.end(), r1);
		regex_iterator<string::iterator> rit2(p.begin(), p.end(), r2);
		regex_iterator<string::iterator> rit3(p.begin(), p.end(), r3);
		regex_iterator<string::iterator> rit4(p.begin(), p.end(), r4);
		regex_iterator<string::iterator> rit5(p.begin(), p.end(), r5);


		regex_iterator<string::iterator> rend;

		for(r1s = 0; rit1 != rend; rit1++, r1s++){}
		for(r2s = 0; rit2 != rend; rit2++, r2s++){}
		for(r3s = 0; rit3 != rend; rit3++, r3s++){}
		for(r4s = 0; rit4 != rend; rit4++, r4s++){}
		for(r5s = 0; rit5 != rend; rit5++, r5s++){}

		if(r1s == 5){
			return 5;
		}

		else if(r1s == 4 || r2s == 4){
			return 4;
		}

		else if((r1s == 3 || r2s == 3 || r3s == 3) && (r1s == 2 || r2s == 2 || r3s == 2 || r4s == 2)){
			return 3;
		}

		else if((r1s == 2 || r2s == 2 || r3s == 2 || r4s == 2)){
			return 2;
		}
		else 
			return 0;
}



int main()
{
	string card;
	int counter;

	vector<string> player1(5);
	vector<string> player2(5);
	int p1score;
	int p2score;
	string p1 = stringify(player1);
	string p2 = stringify(player2);

	cin >> counter;

	for(int i = 0; i < counter; i++){
		for(int j = 0; j < 5; j++){
			cin >> card;
			player1.push_back(card);
		}
		for(int k = 0; k < 5; k++){
			cin >> card;
			player2.push_back(card);
		}

		int checkP1 = checkHands(player1);
		int checkP2 = checkHands(player2);

		if(checkP1 > checkP2){
			cout << "PLAYER 1\n";
		}
		else if(checkP1 < checkP2){
			cout << "PLAYER 2\n";
		}
		else if(checkP1 == checkP2){
			p1score = 0;
			p2score = 0;
			for(size_t i = 1; i < p1.size(); i=i+2){
				p1score += assignPriority(p1.at(i));
				if(i == 7){
					p1score += assignPriority(p1.at(9));
					break;
				}
			}
			for(size_t i = 1; i < p2.size(); i=i+2){
				p2score += assignPriority(p2.at(i));
				if(i == 7){
					p2score += assignPriority(p2.at(9));
					break;
				}
			}
			if(p1score == p2score)
			cout << "TIE\n";
			else if(p1score > p2score){
				cout << "PLAYER1\n";
				cout << "TIE\n";}
			else if(p2score > p1score)
				cout << "PLAYER2\n";
		}
		player1.clear();
		player2.clear();
	}
}