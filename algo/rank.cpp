namespace algo{

    int rank(int** matrix, int M, int Q);
    void perform_elementary_row_operations(int flag, int i, int M, int Q, int** A);
    int find_unit_element_and_swap(int flag, int i, int M, int Q, int** A);
    int swap_rows(int i, int index, int Q, int** A);
    int determine_rank(int m, int M, int Q, int** A);

    #define	MATRIX_FORWARD_ELIMINATION	0
    #define	MATRIX_BACKWARD_ELIMINATION	1

    int rank(int** matrix, int M, int Q){
        int r, m=min(M,Q);

        /* FORWARD APPLICATION OF ELEMENTARY ROW OPERATIONS */
        for (int i=0; i<m-1; i++ ) {
            if ( matrix[i][i] == 1 )
                perform_elementary_row_operations(MATRIX_FORWARD_ELIMINATION, i, M, Q, matrix);
            else { 	/* matrix[i][i] = 0 */
                if ( find_unit_element_and_swap(MATRIX_FORWARD_ELIMINATION, i, M, Q, matrix) == 1 )
                    perform_elementary_row_operations(MATRIX_FORWARD_ELIMINATION, i, M, Q, matrix);
            }
        }

        /* BACKWARD APPLICATION OF ELEMENTARY ROW OPERATIONS */
        for (int i=m-1; i>0; i-- ) {
            if ( matrix[i][i] == 1 )
                perform_elementary_row_operations(MATRIX_BACKWARD_ELIMINATION, i, M, Q, matrix);
            else { 	/* matrix[i][i] = 0 */
                if ( find_unit_element_and_swap(MATRIX_BACKWARD_ELIMINATION, i, M, Q, matrix) == 1 )
                    perform_elementary_row_operations(MATRIX_BACKWARD_ELIMINATION, i, M, Q, matrix);
            }
        }

        r = determine_rank(m, M, Q, matrix);

        return r;
    }

    void perform_elementary_row_operations(int flag, int i, int M, int Q, int** A) {
        int	j, k;

        if ( flag == MATRIX_FORWARD_ELIMINATION ) {
            for ( j=i+1; j<M;  j++ )
                if ( A[j][i] == 1 )
                    for ( k=i; k<Q; k++ )
                        A[j][k] = (A[j][k] + A[i][k]) % 2;
        }
        else {
            for ( j=i-1; j>=0;  j-- )
                if ( A[j][i] == 1 )
                    for ( k=0; k<Q; k++ )
                        A[j][k] = (A[j][k] + A[i][k]) % 2;
        }
    }

    int find_unit_element_and_swap(int flag, int i, int M, int Q, int** A){
        int	index, row_op=0;

        if ( flag == MATRIX_FORWARD_ELIMINATION ) {
            index = i+1;
            while ( (index < M) && (A[index][i] == 0) )
                index++;
                if ( index < M )
                    row_op = swap_rows(i, index, Q, A);
        }
        else {
            index = i-1;
            while ( (index >= 0) && (A[index][i] == 0) )
                index--;
                if ( index >= 0 )
                    row_op = swap_rows(i, index, Q, A);
        }

        return row_op;
    }

    int swap_rows(int i, int index, int Q, int** A){
        int	temp;

        for (int p=0; p<Q; p++ ) {
            temp = A[i][p];
            A[i][p] = A[index][p];
            A[index][p] = temp;
        }

        return 1;
    }

    int determine_rank(int m, int M, int Q, int** A) {
        int rank, allZeroes;

        /* DETERMINE RANK, THAT IS, COUNT THE NUMBER OF NONZERO ROWS */
        rank = m;
        for (int i=0; i<M; i++ ) {
            allZeroes = 1;
            for (int j=0; j<Q; j++)  {
                if ( A[i][j] == 1 ) {
                    allZeroes = 0;
                    break;
                }
            }
            if ( allZeroes == 1 )
                rank--;
        }

        return rank;
    }

}
