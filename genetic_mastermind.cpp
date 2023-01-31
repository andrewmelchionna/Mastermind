#include <iostream>
#include<cmath>
#include<math.h>
#include<cstdlib>
#include<time.h>
#include <vector>

using namespace std;

void initializepop(vector<int> &popvector1, int n, int maxpop);
double fitness(vector<double> &fitnessvector, int integertocheckfitnessof, bool vectorofconfigs, vector<int> black, vector<int> white, int spaces, int colors, int maxpop, vector<int> guesslog,vector<int> population, int round);
vector<int> feedbackgenerator(int actualconfig, int guessconfig, int colors, int spaces);
vector<int> parentselector(int maxpop, vector<double> fitnessvector);
int childbirther(int spaces, int colors, int parent1, int parent2);
int guessnominator(vector<int> population, int pop2, vector<double> &fitnessvector, vector<int> black, vector<int> white, int spaces, int colors, int maxpop, vector<int> guesslog, int round);
vector<int> confignumbertoconfigvector(int l, int spaces, int colors);
int exp(int i, int j);

int main () {
	srand(time(NULL));

	int spaces = 3;
	int colors = 5;

	/*cout << "How many possible colors are in our game?" << endl;
	cin >> colors;

	cout << "How many spaces are in our game?" << endl;
	cin >> spaces;*/

	int maxpop = 5;
	int maxchild = 5;
	int maxrounds = 10;
	//^^ COME BACK AND MAKE THE VECTOR SIZE DYNAMIC, ELIMINATING MAXROUNDS ^^
	
	int n = exp(colors,spaces);
	int round = 0;
	int child;
	int pop2;
	int potentialchild;
	int i;
	

	vector<int> black(maxrounds);
	vector<int> white(maxrounds);
	vector<int> popvector1(maxpop,n);
	vector<int> popvector2(maxpop,n);
	vector<int> guesslog(maxrounds,n);
	vector<double> fitnessvector(maxpop);

	int initialguess = colors + 1;

	vector<int> guessthisvector(spaces);
	guessthisvector = confignumbertoconfigvector(initialguess,spaces,colors);
	guesslog[0] = initialguess;


/*	cout << "Guess the following code: " << endl;
	for(i=0; i<spaces; i++){
		cout << guessthisvector[i] << " ";
	}

	cout << "Number of black pegs: " << endl;
	cin >> black[0];
	cout << "Number of white pegs: " << endl;
	cin >> white[0];*/
black[0] = 1;
white[0] = 0;
	vector<int> parentvector(2);
	

	do{
		
		round++;
		pop2 = 0;
		initializepop(popvector1,n,maxpop);
		fitness(fitnessvector, 0, true, black, white, spaces, colors, maxpop, guesslog, popvector1, round);
	
		do{	

			parentvector = parentselector(maxpop, fitnessvector);


			potentialchild = childbirther(spaces, colors, parentvector[0], parentvector[1]);
cout<< "test" << endl;
			child++;
			//if(fitness(fitnessvector, potentialchild, false, black, white, spaces, colors, maxpop, guesslog, pop1vector, round) > double(1)/maxpop){
				popvector2[pop2] = potentialchild;
				pop2++;
			//}
	cout << pop2;
	
		}while(child < maxchild && pop2 < maxpop);

cout << "test" << endl;
		guesslog[round] = guessnominator(popvector2, pop2, fitnessvector,  black, white, spaces, colors, maxpop, guesslog, round);
		guessthisvector = confignumbertoconfigvector(guesslog[round], spaces, colors);
		for(i=0; i< spaces; i++){
			cout << guessthisvector[i] << " ";
		}
cout << "test" << endl;		
		cout << "Number of black pegs: " << endl;
		cin >> black[round];
		cout << "Number of white pegs: " << endl;
		cin >> white[round];

	}while(black[i] != spaces && round < maxrounds);
	

	return 0;
}


void initializepop(vector<int> &popvector1, int n, int maxpop){
	int i,j;
	int randomnumber;
	vector<int> isthisconfigpresent(n,0);
	
	for(i = 0; i < maxpop; i++){
		randomnumber = rand();
		for(j = 0; j < n; j++){
			if(randomnumber < (j+1)*double(RAND_MAX)/n){
				if(isthisconfigpresent[i] == 0){
					popvector1[i] = j;
					break;
				}else{
					i--;
					break;
				}
			}
		}
	}
}

double fitness(vector<double> &fitnessvector, int integertocheckfitnessof, bool vectorofconfigs, vector<int> black, vector<int> white, int spaces, int colors, int maxpop, vector<int> guesslog,vector<int> population, int round){
	int i,j;
	int totalfitness=0;
	if(vectorofconfigs == true){
		for(i = 0; i < maxpop; i++){
			fitnessvector[i] = 0;
			for(j = 0; j < round; j++){
				fitnessvector[i] = fitnessvector[i] + 2*abs(feedbackgenerator(guesslog[j],population[i],colors,spaces)[0]-black[j]) + abs(feedbackgenerator(guesslog[j],population[i],colors,spaces)[1] - white[j]) + 2*spaces*j;
			}
		}
	}else{
		for(j = 0; j < round; j++){
			totalfitness = totalfitness + 2*abs(feedbackgenerator(guesslog[j],integertocheckfitnessof,colors,spaces)[0]-black[j]) + abs(feedbackgenerator(guesslog[j],integertocheckfitnessof,colors,spaces)[1] - white[j]) + 2*spaces*j;
		}
		totalfitness = double(totalfitness)/maxpop;
	}
	if(vectorofconfigs == true){
		for(i = 0; i < maxpop; i++){
			totalfitness = totalfitness + fitnessvector[i];
		}
	
		for(i = 0; i < maxpop; i++){
			fitnessvector[i] = fitnessvector[i]/double(totalfitness);
		}
	}
	return totalfitness;
	
}

vector<int> feedbackgenerator(int actualconfig, int guessconfig, int colors, int spaces){
	
	int i;	

	vector<int> feedback(2,0);
	vector<int> actualconfigvector = confignumbertoconfigvector(actualconfig, spaces, colors);
	vector<int> guessconfigvector = confignumbertoconfigvector(guessconfig, spaces, colors);
	vector<int> alreadyyieldedblack(spaces,0);
	vector<int> colorcount(colors,0);

	for(i = 0; i < spaces; i++){
		if(actualconfigvector[i] == guessconfigvector[i]){
			feedback[0]++;
			alreadyyieldedblack[i] = 1;
		}else{
			colorcount[actualconfigvector[i]]++;
		}
	}

	for(i = 0; i < spaces; i++){
		if(colorcount[guessconfigvector[i]] > 0 && alreadyyieldedblack[i] == 0){
			colorcount[guessconfigvector[i]]--;
			feedback[1]++;	
		}
	}

	return feedback;
}

vector<int> parentselector(int maxpop, vector<double> fitnessvector){

	int i,j;
	vector<int> parent(2);
	int randomnumber;
	int pacer = 0;
	bool havesecondparent = false;
	randomnumber = rand();
	for(i = 0; i < maxpop; i++){
		if(randomnumber < pacer + ceil(fitnessvector[i]*double(RAND_MAX))){
			parent[0] = i;
			break;
		} else{
			pacer = pacer + ceil(fitnessvector[i]*double(RAND_MAX));
		}
	}


	randomnumber = rand();
	do{
		pacer = 0;
		for(i = 0; i < maxpop; i++){
			if(randomnumber < pacer + ceil(fitnessvector[i]*double(RAND_MAX))){
				if(i != parent[0]){
					parent[1] = i;
					havesecondparent = true;
					break;
				}else{
					break;
				}
			} else{
				pacer = pacer + ceil(fitnessvector[i]*double(RAND_MAX));
			}
		}	
	}while(havesecondparent == false);
	
	return parent;
	
}

int childbirther(int spaces, int colors, int parent1, int parent2){

	bool doublecrossover;
	bool foundgood2pts = false;
	int i,randomnumber;
	int cpt1, cpt2,temp;
	vector<int> parent1vector = confignumbertoconfigvector(parent1, spaces, colors);
	vector<int> parent2vector = confignumbertoconfigvector(parent2, spaces, colors);
	vector<int> potentialchildvector(spaces);
	


	if(rand()%2 == 0){
		doublecrossover = false;
	}else{
		doublecrossover = true;
	}


	randomnumber = rand();
	for(i=0; i <= spaces; i++){
		if(randomnumber < i*double(RAND_MAX)/(spaces+1)){
			cpt1 = i;
			break;
		}		
	}

	if(doublecrossover == false){
		for(i = 0; i < spaces && i < cpt1; i++){
			potentialchildvector[i] = parent1vector[i];
		}
		for(i = cpt1; i < spaces; i++){
			potentialchildvector[i] = parent2vector[i];
		}
		
	}else{
		do{	
			randomnumber = rand();
			for(i=0; i <= spaces; i++){
				if(randomnumber < i*double(RAND_MAX)/(spaces+1)){
					if(i != cpt1){
						cpt2 = i;
						if(cpt1 > cpt2){
							temp = cpt2;
							cpt2 = cpt1;
							cpt1 = temp;
						}
						foundgood2pts = true;
						break;
					} else{
						break;
					}
				}		
			}	
		}while(foundgood2pts == false);

		for(i = 0; i < spaces && i < cpt1; i++){
			potentialchildvector[i] = parent1vector[i];
		}
		for(i = cpt1; i < cpt2 && i < spaces; i++){
			potentialchildvector[i] = parent2vector[i];
		}
		for(i = cpt2; i < spaces; i++){
			potentialchildvector[i] = parent1vector[i];
		}
	}
}

int guessnominator(vector<int> population, int pop2, vector<double> &fitnessvector, vector<int> black, vector<int> white, int spaces, int colors, int maxpop, vector<int> guesslog, int round){
	int i;
	fitness(fitnessvector, 0, false, black, white, spaces, colors, maxpop, guesslog, population, round);
	int guess;
	int pacer = 0;
	int randomnumber;
	randomnumber = rand();
	for(i = 0; i < pop2; i++){
		if(randomnumber < pacer + ceil(fitnessvector[i]*double(RAND_MAX))){
			guess = i;
			break;
		} else{
			pacer = pacer + ceil(fitnessvector[i]*double(RAND_MAX));
		}
	}	
	return guess;
	
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