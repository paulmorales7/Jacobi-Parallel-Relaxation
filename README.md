Jacobi Parallel Relaxation with Broadcast, Aggregation, and Convergence

added a Barrier function and Aggregation Finction
Used this statement to initialize the A array: Defining why we are looking for a small conversion tolerance and need to use small numbers
 (rand() % 200) / 200.0
Define tolerance as:  .003

Used this statement for output 

    for(i = 0; i <= n + 1; i++){
            cout << "Row:  " << i << "   Result" <<endl;
            for(j = 0; j <= n+1; j++){
            if((j > 0) && (j % 10) == 0){
                cout << endl;
            }
            cout << A[i][j] << "  ";
            }
        cout << endl;
    }
