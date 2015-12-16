int main() {

	int c;
	int m;
	int d;
	int q;
	int k;
	int p;
	int sum;
	int first[5][5];
	int second[5][5];
	int product[5][5];

	for (c = 0; c < m; c = c + 1) {

	for (d = 0; d < q; d = d + 1) {
		for (k = 0; k < p; k = k + 1) {
			sum = sum + first[c][k]*second[k][d];
        }
 
		product[c][d] = sum;
		sum = 0;
      }
    }
}