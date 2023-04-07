double A, B;
int outercount = 0;
while (bestsq > N_TOLER && outercount < CYCLES) {
    double delt = 2.0;
    double m[3] = {1.0, 0.0, 0.0}; // inner loop transformation
    int count = 0;

    // inner while loop
    while (bestsq > N_TOLER && count < CYCLES) {
        int gotOne = 0; // indication: which of 6 ways is best improvement
        for (int j = 0; j < 3; j++) {
            double holdp_m = m[j];
            m[j] = m[j] + delt;
            double newnorm = Centroid(T, m);
            m[j] = holdp_m; // reset to continue trying
            if (newnorm < bestsq) {
                bestsq = newnorm;
                gotOne = j + 1;
            } else { // try opposite direction
                m[j] = m[j] - delt;
                newnorm = Centroid(T, m);
                m[j] = holdp_m; // reset
                if (newnorm < bestsq) {
                    bestsq = newnorm;
                    gotOne = -(j + 1);
                }
            }
        } // end of for loop

        // if moving in 6 directions didn't improve, then cut delt
        if (gotOne == 0) {
            delt = delt / 2;
        } else { // success: which change was the best?
            if (gotOne == 1) {
                m[0] = m[0] + delt;
            } else if (gotOne == 2) {
                m[1] = m[1] + delt;
            } else if (gotOne == 3) {
                m[2] = m[2] + delt;
            } else if (gotOne == -1) {
                m[0] = m[0] - delt;
            } else if (gotOne == -2) {
                m[1] = m[1] - delt;
            } else if (gotOne == -3) {
                m[2] = m[2] - delt;
            }
        } // end of if/else
        count = count + 1;
    } // end of while
