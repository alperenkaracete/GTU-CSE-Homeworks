#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 512
#define MAX_ISLANDS 100

void print_islands_to_file (int world[MAX_VALUE][MAX_VALUE],int row,int column,int ocean_level);

int main(){

	int world[MAX_VALUE][MAX_VALUE], /*Input variables*/
	i=0, /*For loops*/
	j=0, /*For loops*/
	ocean_level, /*Takes ocean level*/
	count=0,
	row=0, /*Row number*/
	column=0; /*Column number*/

	char a; /*Controlling file charachters*/

	FILE *input; /*Input file*/

	input = fopen ("input.txt","r");

	while (!feof(input)){ /*File rading to array*/

		if (count==0){ /*Taking ocean level*/

			fscanf (input,"%d",&ocean_level);
			count++;
		}
		
		if (j==0){

			fscanf (input,"%d",&world[i][j]);
			j++;
		}

		a=fgetc(input);

		if (a=='\n'){

			if (j==0 && count==1){

				i=-1;
				count++;
			}

			if(i==2){

				row=j; /*Storing row number in a variable*/
			}
			i++;
			j=0;
		}

		else if (a==' '){

			fscanf (input,"%d",&world[i][j]); /*Getting numbers from file*/
			j++;			
		}

	}

	column=i; /*Storing column number in a variable*/
	
	print_islands_to_file (world,row,column,ocean_level); /*Finding islands and printing file function*/

	return 0;
}

void print_islands_to_file (int world[MAX_VALUE][MAX_VALUE],int row,int column,int ocean_level){

	int i=0,
	j=0,
	count=0, /*For controlling where island has started*/
	number_of_islands=0, /*Total Islands*/
	x[MAX_ISLANDS], /*Islands x coordinates*/
	y[MAX_ISLANDS], /*Islands y coordinates*/
	starting_x, /*Starting x coordinate*/
	starting_y; /*Starting y coordinate*/

	FILE *coordinates; /*Output file*/

	coordinates = fopen ("output.txt","w");

	for (i=0;i<column;i++){ /*Column part*/

		for (j=0;j<row;j++){ /*Row part*/

			if (i==0 && j==0){ /*First land control*/

				if (world[i][j]>ocean_level && world[i][j+1]>ocean_level){

					x[number_of_islands]=i;
					y[number_of_islands]=j;
					number_of_islands++;
					count=0;
				}

				else if (world[i][j]>ocean_level && world[i+1][j]>ocean_level){

					x[number_of_islands]=i;
					y[number_of_islands]=j;
					number_of_islands++;
					count=0;
				}
			}

			else if (i==0 && world[i][j]>ocean_level){ /*Where column is zero we dont have to control up*/

				if (world[i][j]>ocean_level && world[i-1][j]<ocean_level && world[i][j-1]<ocean_level){

					x[number_of_islands]=i;
					y[number_of_islands]=j;
					number_of_islands++;
					count=1;
				}

				else if (world[i][j]>ocean_level && count==1){

					x[number_of_islands]=starting_x;
					y[number_of_islands]=starting_y;
					number_of_islands++;
					count=0;
				}

			}

			else if (i!=row-1){ /*Controlling middle part*/

				if (j==0){

					if (world[i][j]>ocean_level && world[i-1][j]<ocean_level){

						starting_x=i;
						starting_y=j;
						count=1;
					}
				}

				if (world[i][j]>ocean_level && count==0 && world[i-1][j]<ocean_level && world[i][j-1]<ocean_level){

					starting_x=i;
					starting_y=j;
					count=1;
				}

				if (count==1 && world[i-1][j]<ocean_level && world[i][j-1]<ocean_level){

					x[number_of_islands]=starting_x;
					y[number_of_islands]=starting_y;
					number_of_islands++;
					count=0;
				}

				if (world[i-1][j]>ocean_level){

					count=0;
				}
			}

			else if (i==row-1){ /*Controlling bottom part*/

				if (world[i][j]>ocean_level && count==0 && world[i-1][j]<ocean_level){

					starting_x=i;
					starting_y=j;
					count=1;
				}

				else if (count==1 && world[i-1][j]<ocean_level){

					x[number_of_islands]=starting_x;
					y[number_of_islands]=starting_y;
					number_of_islands++;
					count=0;
				}

				if (world[i-1][j]>ocean_level){

					count=0;
				}
			}

		}
	}

	fprintf(coordinates, "%d\n", number_of_islands); /*Printing number of islands*/
	for (i=0;i<number_of_islands;i++){

		fprintf (coordinates,"%d %d\n",x[i],y[i]); /*Printing coordinates to file*/
	}

}