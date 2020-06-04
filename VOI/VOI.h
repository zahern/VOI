#pragma once
#include <vector>
using namespace std;

class VOI
{public:
	int actions;
	int states;
	vector<vector<double>> action_mat;
	vector<vector<double>> value_mat;
	vector<double> EV_action_state;
	vector<double> prob_state;
	vector<double> QAL;
	VOI(int s, int a) {
		states = s;
		actions = a;
		action_mat.resize(states);
		EV_action_state.resize(states);
		prob_state.resize(states);
		value_mat.resize(actions);
		QAL.resize(states);


		for (int i = 0; i < actions; i++) {
			value_mat[i].resize(states);
		}

		for (int i = 0; i < states; i++) {
			action_mat[i].resize(states);
			//EV_action_state[i].resize(states);
		}
	}
};

//state 1 - first disease
//state 2 - 2nd disease
//state 3 - 3rd disease
//action 4 - disease 2 and 3