// VOI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "VOI.h"
#include <algorithm>
int main()
{
    VOI v(4, 4);
    double dis1 = 0.6;
    double dis2 = 0.4;
    double dis3 = 0.1;
    
    //only disease 1
    v.prob_state[0] = dis1 * (1 - dis2) * (1 - dis3) / (1 - (1 - dis1) * (1 - dis2) * (1 - dis3));
    v.prob_state[1] = dis2 *(1-dis3)/ (1 - (1 - dis1) * (1 - dis2) * (1 - dis3));
    v.prob_state[2] = dis3 * (1 - dis2) / (1 - (1 - dis1) * (1 - dis2) * (1 - dis3));
    v.prob_state[3] = dis2*dis3/ (1 - (1 - dis1) * (1 - dis2) * (1 - dis3));

    v.QAL[0] = 0;
    v.QAL[1] = -2;
    v.QAL[2] = -5;
    v.QAL[3] = -7;
    
    for (int e = 0; e < v.action_mat.size(); e++) {
        for (int ee = 0; ee < v.action_mat[e].size(); ee++) {
            v.action_mat[e][e] += v.QAL[e] * v.prob_state[ee];
        }
    }
    


    for (int a = 0; a < v.actions -1; a++) {
        for (int s = 0; s < v.states; s++) {

            v.value_mat[a][s] = v.QAL[s];

           
        }
    }
    /*
    v.value_mat[1][1] = -.5;

    v.value_mat[1][3] = -5.5;

    v.value_mat[2][2] = -2;
    v.value_mat[2][3] = -4;
   


    v.value_mat[3][1] = -.5;
    v.value_mat[3][2] = -2;
    v.value_mat[3][3] = -2.5;
    */
    v.value_mat[1][0] = -.5;
    v.value_mat[1][1] = -.5;
    v.value_mat[1][2] = -5.5;
    v.value_mat[1][3] = -5.5;

    v.value_mat[2][0] = -2;
    v.value_mat[2][1] = -4;
    v.value_mat[2][2] = -2;
    v.value_mat[2][3] = -4;


    v.value_mat[3][0] = -2.5;
    v.value_mat[3][1] = -2.5;
    v.value_mat[3][2] = -2.5;
    v.value_mat[3][3] = -2.5;


    double evc=0;
    double maxe;

    vector<vector<double>>trans_vec;
    trans_vec = v.value_mat;
    for (int i = 0; i < v.value_mat.size(); i++) {
        for (int j = 0; j < v.value_mat[i].size(); j++) {
            trans_vec[j][i] = v.value_mat[i][j];
        }
    }

    for (int a = 1; a < v.action_mat.size(); a++) {
        maxe = *max_element(trans_vec[a].begin(), (trans_vec[a].end()));

        evc += maxe * v.prob_state[a];
    }


    //action do nothing

    vector<double> max;
    double evuc = 0;
    max.resize(4);
    for (int e = 0; e < v.action_mat.size(); e++) {
        for (int ee = 0; ee < v.action_mat[e].size(); ee++) {
           max[e] += v.prob_state[ee] * trans_vec[ee][e];
        }
    }
    evuc = *max_element(max.begin(), (max.end()));


    double evpi = evc - evuc;
//q1a) yes it is evc - .5 > evunc
    cout << endl;


    //q1b)
    for (int qaly = 0; qaly < 100; qaly++) {
        v.value_mat[0][0] = -0*qaly;
        v.value_mat[0][1] = -2*qaly;
        v.value_mat[0][2] = -5*qaly;
        v.value_mat[0][3] = -7*qaly;



        v.value_mat[1][0] = -.5;
        v.value_mat[1][1] = -.5;
        v.value_mat[1][2] = -.5 -5*qaly;
        v.value_mat[1][3] = -.5 -5*qaly;

        v.value_mat[2][0] = -2;
        v.value_mat[2][1] = -2 -2*qaly;
        v.value_mat[2][2] = -2;
        v.value_mat[2][3] = -2 -2*qaly;


        v.value_mat[3][0] = -2.5;
        v.value_mat[3][1] = -2.5;
        v.value_mat[3][2] = -2.5;
        v.value_mat[3][3] = -2.5;




        trans_vec = v.value_mat;
        for (int i = 0; i < v.value_mat.size(); i++) {
            for (int j = 0; j < v.value_mat[i].size(); j++) {
                trans_vec[j][i] = v.value_mat[i][j];
            }
        }

        evc = 0;
        for (int a = 1; a < v.action_mat.size(); a++) {
            maxe = *max_element(trans_vec[a].begin(), (trans_vec[a].end()));

            evc += maxe * v.prob_state[a];
        }


        //action do nothing

        vector<double> max;
        double evuc = 0;
        max.clear();
        max.resize(4);
        for (int e = 0; e < v.action_mat.size(); e++) {
            for (int ee = 0; ee < v.action_mat[e].size(); ee++) {
                max[e] += v.prob_state[ee] * trans_vec[ee][e];
            }
        }
        evuc = *max_element(max.begin(), (max.end()));


        double evpi = evc - evuc;

        cout << endl;






    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
