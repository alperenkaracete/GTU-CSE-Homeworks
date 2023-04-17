#include <stdio.h>
#include <string.h>

void fill_arrays (char txt2_inputs[100][250]); /*Array texts from file and fills array.*/
void compare_arrays (char txt2_inputs[100][250],char word[10]); /*Array compares words and text file's content. */

int main(){

	char txt2_inputs[100][250], /*Takes file content.*/
	word[10]; /*Takes file word content.*/

	fill_arrays (txt2_inputs);
	compare_arrays (txt2_inputs,word);

	return 0;	

}

void fill_arrays (char txt2_inputs[100][250]){

	int i=0, /*Array's x axis*/
	j=0; /*Array's y axis*/

	FILE *input; /*Text file 2*/

	input = fopen ("input2.txt","r");

	while (!feof(input)){

		txt2_inputs[i][j]=fgetc(input);

		if (txt2_inputs[i][j]=='\n'){
			i++;
			j=-1;
		}

		j++;
	}

	txt2_inputs[i][j]='\0'; /*Make arrays last member \0*/

	fclose (input);

}

void compare_arrays (char txt2_inputs[100][250],char word[10]){

	int i=0, /*Array's x axis*/
	j=0, /*Array's y axis*/
	k=0, /*Controls how many time compares loop will execute*/
	z=0, /*Control for word variable*/
	length=0, /*Takes length of word*/
	count=0; /*Compares if there is different letters in word and txt2_inputs*/

	FILE *words,
	*output;

	words = fopen ("input1.txt","r"); /*Word text file*/
	output = fopen ("output.txt","w"); /*Output text file*/

	while (!feof(words)){

		fscanf (words,"%s",word); /*Takes words from file*/

		while (word[z]!='\0' && txt2_inputs[i][j]!='\0'){ 

			if (txt2_inputs[i][j]=='\n'){ /*Controls enter if variable is enter increase x axis value and makes y axis value zero*/

				j=0;
				i++;

			}

			else if(word[z]==txt2_inputs[i][j]){ /*If first letters are same for both arrays enters for control other letters.*/ 

				if(word[z+1]==txt2_inputs[i][j+1]){ /*Compares arrays horizontally*/

					length= strlen (word); /*Calculates how long the word is*/

					for (k=0;k<length;k++){ /*Compares loop*/
						if(word[k]!=txt2_inputs[i][j+k]){

							count++;

						}

					}

					if (count==0){ /*If there is no different letter writes file*/
						fprintf(output, "%s (%d,%d) Horizontal\n",word,i+1,j+1 ); /*Writes variables to output file */
						i=0;
						j=0;
						z=length; /*Make z max value to end loop**/											
					}
					count=0;

				}

				else if(word[z+1]==txt2_inputs[i+1][j]){ /*Compares arrays vertically*/

					length= strlen (word); /*Calculates how long the word is*/

					for (k=0;k<length;k++){ /*Compares loop*/

						if(word[k]!=txt2_inputs[i+k][j]){

							count++;
						}
					}

					if (count==0){ /*If there is no different letter writes file*/
						fprintf(output, "%s (%d,%d) Vertical\n",word,i+1,j+1 );
						i=0;
						j=0;
						z=length;  /*Make z max value to end loop**/
					}	
					count=0;

				}
			}
				
			j++;			
			
		}
		j=0;
		z=0;
		count=0;		
		for (i=0;i<10;i++){

			word[i]='\0';
		}
		i=0;		
	}
	fclose (words);
	fclose (output);
}




