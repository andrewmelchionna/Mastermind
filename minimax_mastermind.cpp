#include <iostream>
#include<cmath>
#include<math.h>
#include<cstdlib>
#include<time.h>
#include <vector>

using namespace std;

int numbertodiscard (int k, int i, int j, vector<int> allowedconfigurations, int n, int spaces, int colors);
void configkiller (vector<int> &allowedconfigurations, int configurationplayed, vector<int> pegs, int round, int n, int spaces, int colors);
int exp(int i, int j);
int numbertodiscard(int k, int i, int j);
vector<int> confignumbertoconfigvector(int l, int spaces, int colors);
void feedback(int configurationplayed, int candidateforsolution, vector<int> &tempfeedbackvector, int spaces, int colors);

int main () {
	int spaces;
	int colors;

	cout << "How many possible colors are in our game?" << endl;
	cin >> colors;

	cout << "How many spaces are in our game?" << endl;
	cin >> spaces;
	
	
	int l;
	int k;
	int i;
	int j;
	int p;
	int n = exp(colors,spaces);

	vector<int> allowedconfigurations(n, 1);
	vector<int> mins(n);
	vector<int> pegs(16);
	vector<int> configurationtoplayvector(spaces);
	
	for (j = 0; j<16; j++){
		pegs[j] = 0;
	}
	



	//initialize mins
	for (l = 0; l < 8; l++) {
		
		for (k = 0; k < n; k++) {
			mins[k] = n;
		}

		int configurationtoplay = 0;
	
		
		for (k = 0; k < n; k++) {
			for (i = 0; i <= spaces; i++) {
				for (j = 0; j <= (spaces-i); j++) {
					p = numbertodiscard(k, i, j, allowedconfigurations, n, spaces, colors);
					if ( p < mins[k] ) {
						mins[k] = p;
					}
				}
			}
		}

		/*cout << "mins" << endl;
		for(j = 0; j<64; j++){
		cout << mins[j];
		}  
		cout << endl;
		*/
		
		for (i = 0; i < n; i++) {
			if (mins[configurationtoplay] < mins[i]) {
				configurationtoplay = i;
			}
		}

		if (mins[configurationtoplay] == 0){
			for(j = 0; j<n; j++){
				if(allowedconfigurations[j] == 1){
					configurationtoplay = j;
				}
			}
		}

		configurationtoplayvector = confignumbertoconfigvector(configurationtoplay, spaces, colors);

		for(i = 0; i<spaces; i++){
			cout << configurationtoplayvector[i] << "  ";
		}

		cout << endl;

		cout << "how many red pegs?" << endl;
		cin >> pegs[(2*l)+0];
		if(pegs[(2*l)+0] == spaces){
			cout << "You've won! Congratulations." << endl;
			return 0;
		}
	
		cout << "how many white pegs?" << endl;
		cin >> pegs[(2*l)+1];
		

		configkiller(allowedconfigurations, configurationtoplay, pegs, l, n, spaces, colors);

		

		/*cout << "allowedconfigs" << endl;
		for(j = 0; j<64; j++){
		cout << allowedconfigurations[j];
		}
		cout << endl;*/
		
	}

	return 0;
}



void configkiller (vector<int> &allowedconfigurations, int configurationplayed, vector<int> pegs, int round, int n, int spaces, int colors){
	int i;
	vector<int> tempfeedbackvector(2);
	for (i = 0; i < n; i++){
		if(allowedconfigurations[i] == 1){
			feedback(configurationplayed, i, tempfeedbackvector, spaces, colors);
			//cout << tempfeedbackvector[0] << "  " << tempfeedbackvector[1] << endl;
			if(tempfeedbackvector[0] != pegs[(2*round)+0] || tempfeedbackvector[1] != pegs[(2*round)+1]) {
				allowedconfigurations[i] = 0;
			}
		}
	}

}	


vector<int> confignumbertoconfigvector(int l, int spaces, int colors){
	vector<int> configvector(spaces);
	
	int i;
	for (i = spaces - 1; i >= 0; i--){
		configvector[spaces - 1 -i] = l/(exp(colors,i));
		l = l - ((l/(exp(colors,i)))*(exp(colors,i)));
	}

	return configvector;

}

int exp(int i, int j){
	int k;
	int answer = 1;
	for (k = 1; k <= j; k++){
		answer = answer*i;
	}
	if (i == 0){
		answer = 0;
	}

	return answer;
}


void feedback(int configurationplayed, int candidateforsolution, vector<int> &tempfeedbackvector, int spaces, int colors){
	//write the feedback you would get if you plugged in configurationplayed, given that the ith configuration is the true one
	
	tempfeedbackvector[0] = 0;
	tempfeedbackvector[1] = 0;

	vector<int> configplayedvector(spaces);
	vector<int> candidateforsolutionvector(spaces);

	configplayedvector = confignumbertoconfigvector(configurationplayed, spaces, colors);
	candidateforsolutionvector = confignumbertoconfigvector(candidateforsolution, spaces, colors);

	int i,j;
	vector<bool> alreadyaccountedforbywhite(3);
	for(i = 0; i < spaces; i++){
		alreadyaccountedforbywhite[i] = false;
	}

	for (i = 0; i < spaces; i++){
		if (configplayedvector[i] == candidateforsolutionvector[i]){
			tempfeedbackvector[0]++;
		} else {
			for (j = 0; j < spaces; j++){
				if (configplayedvector[i] == candidateforsolutionvector[j] && configplayedvector[j] != candidateforsolutionvector[j] && alreadyaccountedforbywhite[j] == false){
					tempfeedbackvector[1]++;
					alreadyaccountedforbywhite[j] = true;
					break;
				}
			}
		}
 	}	
}

int numbertodiscard(int k, int i, int j, vector<int> allowedconfigurations, int n, int spaces, int colors){
	
	int number = 0;
	int l;
	vector<int> feedbackvector(2);
	
	

	for (l = 0; l < n; l++){
		feedback(k, l, feedbackvector, spaces, colors);
		if((feedbackvector[0] != i || feedbackvector[1] != j) && allowedconfigurations[l] == 1){
			number++;
		}
	}

	return number;
}
	
	
			
	
