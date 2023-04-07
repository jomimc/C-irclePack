#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void rand_bdry_pts(vector<double> graphX, vector<double> graphY, int M, vector<double>& bdryX, vector<double>& bdryY) {
    // check consistency, close up, get length
    int graphCount = graphX.size();
    if (graphCount < 3 || M < 3 || graphCount != graphY.size()) {
        cout << "Poor data in \"rand_bdry_pts\"" << endl;
        bdryX.clear();
        bdryY.clear();
        return;
    }

    // close up if necessary
    if (abs(graphX[0] - graphX[graphCount - 1]) > 0.001 && abs(graphY[0] - graphY[graphCount - 1]) > 0.001) {
        graphX.push_back(graphX[0]);
        graphY.push_back(graphY[0]);
        graphCount++;
    }

    // mark off by polygon length
    vector<double> length_marks(graphCount);
    for (int i = 1; i < graphCount; i++) {
        length_marks[i] = length_marks[i - 1] + sqrt(pow(graphX[i] - graphX[i - 1], 2) + pow(graphY[i] - graphY[i - 1], 2));
    }

    // find M random ordered param spots in [0,length]
    vector<double> arc_spots(M);
    for (int i = 0; i < M; i++) {
        arc_spots[i] = (double)rand() / RAND_MAX * length_marks[graphCount - 1];
    }
    sort(arc_spots.begin(), arc_spots.end());

    // convert by interpolation to Complex points on graph
    int spot = 1;
    double last_length = length_marks[spot - 1];
    double next_length = length_marks[spot];
    double setlength = next_length - last_length;
    bdryX.resize(M);
    bdryY.resize(M);
    for (int i = 0; i < M; i++) {
        while (arc_spots[i] < last_length) {
            spot++;
            last_length = length_marks[spot - 1];
            next_length = length_marks[spot];
            setlength = next_length - last_length;
        }
        while (arc_spots[i] > next_length) {
            spot++;
            last_length = length_marks[spot - 1];
            next_length = length_marks[spot];
            setlength = next_length - last_length;
        }

        double ratio = (arc_spots[i] - last_length) / setlength;
        bdryX[i] = graphX[spot - 1] + ratio * (graphX[spot] - graphX[spot - 1]);
        bdryY[i] = graphY[spot - 1] + ratio * (graphY[spot] - graphY[spot - 1]);
    }
}

int main() {
    // example usage
    vector<double> graphX = {0, 1, 2, 3, 4};
    vector<double> graphY = {0, 1, 0, 1, 0};
    int M = 5;
    vector<double> bdryX, bdryY;
    rand_bdry_pts(graphX, graphY, M, bdryX, bdryY);
    for (int i = 0; i < M; i++) {
        cout << bdryX[i] << " " << bdryY[i] << endl;
    }
    return 0;
}
