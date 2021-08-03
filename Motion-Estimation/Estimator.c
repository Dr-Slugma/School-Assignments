#define FRAME_LONG 320
#define FRAME_HIGH 240

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void input(uint8_t** data, char* fileName){
	FILE *imagein;
	int row, col, ch_int,i,j;
	imagein = fopen(fileName, "r+");
	if (imagein == NULL) {
		printf("Error opening file");
		fflush(stdout);
		exit(8);
	}
	for(i = 0; i < 15; i++){//Flushes the intial header
		char c = fgetc(imagein);
	}
	for(i = 0; i < FRAME_HIGH; i++){//Grabs the values
		for(j = 0; j < FRAME_LONG; j++){
			data[i][j] = fgetc(imagein);
		}
	} 
	fclose(imagein);
}

int sumOfAbsoluteDifferences(uint8_t** array1, uint8_t** array2, int x, int y, int m, int n){
	register int diff = 0;//START OF SECOND SAD
	register int sad  = 0;
	register int i = 16;
	register int j;
	int a_temp;
	int b_temp;
	do{
		i--;
		j = 15;
		a_temp = array1[i+x][15+y];
		b_temp = array2[i+m][15+n];
			do{
				j--;
				diff = a_temp - b_temp;
				a_temp = array1[i+x][j+y];
				b_temp = array2[i+m][j+n];
				if (diff < 0) {
					sad -= diff;
				}else{
					sad += diff;
				}
			}while(j != 0);
			diff = a_temp - b_temp;
			if (diff < 0) {
				sad -= diff;
			}else{
				sad += diff;
			}
		}while(i != 0);
	return sad;
}

void SADexecutor(uint8_t** array1, uint8_t** array2){
	int array[15][20][3];
	uint16_t m,n,k,l;
	int minSAD;
	uint8_t y;
	uint8_t x = 15;
	do{
		x--;
		y = 20;
		do{
			y--;
			minSAD = sumOfAbsoluteDifferences(array1,array2, x*16, y*16, x*16, y*16);
			array[x][y][0] = 0;
			array[x][y][1] = 0;
			if(minSAD != 0){
				for((m = x*16-64) >= 0 ? m : (m = 0),(k = x*16+64) <= 224 ? k : (k = 224); m < k; m++){
					for((n = y*16-64) >= 0 ? n : (n = 0),(l = y*16+64) <= 304 ? l : (l = 304); n < l; n++){
						register int diff = 0;//START OF SECOND SAD
						register int sad  = 0;
						register int i = 16;
						register int j;
						int a_temp;
						int b_temp;
						do{
								i--;
								j = 15;
								a_temp = array1[i+x][15+y];
								b_temp = array2[i+m][15+n];
								
								do{
									j--;
									diff = a_temp - b_temp;
									a_temp = array1[i+x][j+y];
									b_temp = array2[i+m][j+n];
									if (diff < 0) {
									sad -= diff;
									}else{
									sad += diff;
									}
								}while(j != 0);
								diff = a_temp - b_temp;
								if (diff < 0) {
								sad -= diff;
								}else{
								sad += diff;
								}
							}while(i != 0);//END FO SECOND SAD
						if((sad < minSAD) || (sad == minSAD && x*16 - m + y*16 - n < x*16 - array[x][y][0] + y*16 - array[x][y][1])){
							minSAD = sad;
							array[x][y][0] = m - x*16;
							array[x][y][1] = n - y*16;
							
						}
					}
				}
			}//printf("\nX = %d, Y = %d: SADval=%d mVal=%d nVal= %d\n",x,y,minSAD,array[x][y][0],array[x][y][1]);
			array[x][y][2] = minSAD;
		}while(y != 0);
	}while(x != 0);
}

int main() {
	//Allocates memory for 2 photos and 2 arrays
	int i;
	uint8_t** array1 = (uint8_t**)malloc(FRAME_HIGH*FRAME_LONG*sizeof(uint8_t));
	for(i = 0; i < FRAME_HIGH; i++) array1[i] = (uint8_t *)malloc(FRAME_LONG * sizeof(uint8_t));
	input(array1,"1.pgm");
	uint8_t** array2 = (uint8_t**)malloc(FRAME_HIGH*FRAME_LONG*sizeof(uint8_t));
	for(i = 0; i < FRAME_HIGH; i++) array2[i] = (uint8_t *)malloc(FRAME_LONG * sizeof(uint8_t));
	input(array2,"2.pgm");
	
	SADexecutor(array1,array2);
	
	return 0;
}