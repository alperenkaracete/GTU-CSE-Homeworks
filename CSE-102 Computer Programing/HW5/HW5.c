#include <stdio.h>

void recursive_print_file (FILE *output,int count,int i,char input[250]); /*Recursive function for print file*/
void read_file (char input[250]); /* Reading file array*/

int main(){

	int i=0, /*For array control */
	count=0; /*For couinting -'s   */

	FILE *output;

	output = fopen ("output.txt","w"); /*For printing values*/

	char input[250]; /*Takes inputs*/
	read_file (input); /*Read files and writs array*/
	recursive_print_file (output,count,i,input); /*Recursive function*/
}		

void read_file (char input[250]){

	int i=0; /*For edding end string charachter*/

	FILE *inputs; 

	inputs = fopen ("input.txt","r");

	while (!feof(inputs)){

		fscanf (inputs,"%c",&input[i]); /*Reading file*/
		i++;
	}

	input[i-2]='\0'; /*Adding end of string*/

}

void recursive_print_file (FILE *output,int count,int i,char input[250]){

	if (input[i]=='\0'){ /*If end of string finnish recursive*/

		/*Finish*/
		fclose (output); 
	}

	else if (input[i]=='('){ /*If ( count */

		count++; /*For counting -'s */

		if (input[i+1]!='(' && input[i+1]!=')' && input[i+1]!=','){

			for (int j=0;j<count;j++){ /*For printing -'s*/

				fprintf (output,"%c",'-'); /*Printing file to -  */

			}
		}

		recursive_print_file (output,count,i+1,input);
	}

	else if (input[i]!='(' && input[i]!=')' && input[i]!=','){ /*For printing charachters*/



		fprintf (output,"%c",input[i]);
		recursive_print_file (output,count,i+1,input);		
	}

	else if (input[i]==','){ /*If , then printf new line charachter to file*/

		fprintf (output,"%c",'\n');

		if (input[i+1]!='(' && input[i+1]!=')' && input[i+1]!=','){ /*If there is a charachter after , then print -  */

			for (int j=0;j<count;j++){

				fprintf (output,"%c",'-');

			}
		}

		recursive_print_file (output,count,i+1,input);		
	}

	else if (input[i]==')'){ /* If ) so reduce count */

		count--;

		recursive_print_file (output,count,i+1,input);		
	}


}