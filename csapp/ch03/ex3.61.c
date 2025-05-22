int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k) {
    int j;
    int result = 0;

    int* Arow = &(A[i][0]);
    int* BCol = &(B[0][k]);
    for(j=0;j<n;j++)
        result += Arow[j] * (*(BCol + (j * n)));

    return result;
}