int main() {
	
	int i;
	int j;
	int swap;
	int a[4];
	

	for(i = 0; i < 4; i = i +1) {
		for(j = 0; j < 4 - i; j = j + 1){
			if( a[i] < a[j]) {
				swap = a[i];
				a[i] = a[j];
				a[j] = swap;
			}
		}
	}
}