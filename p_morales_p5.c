#include <stdlib.h>
#include <math.h>
#define n 32
#define tolerance 0.003

float A[n+2][n+2], B[n+2][n+2];
int i,j;
int count;
boolean globaldone;
spinlock Completed, Uncompleted;
float change, maxchange;
boolean done;
int stream higher[n+1], stream lower[n+1];


void LocalBarrier(int i) {
    int dummy;
    if (i > 1) 
    send(higher[i-1], 1);
    if (i < n) {
        send(lower[i+1], 1);
        recv(higher[i], dummy);
    }
    if (i > 1) recv(lower[i], dummy);
}

boolean Aggregate(boolean mydone) {
    boolean result;
    Lock(Completed);
    count = count + 1;
    globaldone = globaldone && mydone;
    if (count < n)
        Unlock(Completed);
    else
        Unlock(Uncompleted);

    Lock(Uncompleted);
    count = count - 1;
    result = globaldone;
    if (count > 0)
        Unlock(Uncompleted);
    else {
        Unlock(Completed);
        globaldone = true;
    }
    return (result);
}

 main() {
    count = 0;
    Unlock(Completed);
    Lock(Uncompleted);
    globaldone = true;
    for (i = 0; i <= n+1; i++) {
        for (j = 0; j <= n+1; j++) {
            A[i][j] = (rand() % 200) / 200.0;
        }
    }
B = A;
    

    forall i = 1 to n do {
        int j;
        float change;
        float maxchange;
        boolean done;
        do {
            maxchange = 0;
            for (j = 1; j <= n; j++) {
                B[i][j] = (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]) / 4;
                change = fabs(B[i][j] - A[i][j]);
                if (change > maxchange) maxchange = change;
            }
            LocalBarrier(i);
            A[i] = B[i];
            done = Aggregate(maxchange < tolerance);
        } while (!done);
    }

        cout.precision(3);
        cout << "Paul- " << endl;
        for (i = 0; i <= n + 1; i++) {
            cout << "Row: " << i << "   Result" << endl;
            for (j = 0; j <= n+1; j++) {
                if ((j > 0) && (j % 10) == 0) {
                    cout << endl;
                }
                cout << A[i][j] << "  ";
            }
            cout << endl;
        }
        return 0;
}
