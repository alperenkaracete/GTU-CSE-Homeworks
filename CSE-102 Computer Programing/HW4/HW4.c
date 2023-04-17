#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int read_values (double values[100]);
void read_polynomial (char polynomial[1000],double nums[1000]);
void calculate_eva (double xs_coefficient[1000],double variable,int xs_exponent[1000],double values[100],char polynomial[1000],double nums[1000],int count);

int main(){

	int count;
	double values[100],
	nums[1000];
	char polynomial [1000];

	count=read_values (values);
	read_polynomial (polynomial,nums);

	double xs_coefficient[500],
	variable=0;


	int xs_exponent[500];

	calculate_eva (xs_coefficient,variable,xs_exponent,values,polynomial,nums,count);

}

int read_values (double values[100]){

	int i=0,
	count;

	double temp;

	FILE *value_file;

	value_file = fopen ("values.txt","r");

	while (!feof(value_file)){

		fscanf (value_file,"%lf",&values[i]);
		i++;
		count++;
	}
	values[i]='\0';
	i=0;

	return count;
}

void read_polynomial (char polynomial[1000],double nums[1000]){

	int count=0,
	i=0,
	j=0;

	char *num,
	temp[1000];

	FILE *polynomial_file;

	polynomial_file = fopen ("polynomial.txt","r");

	while (!feof(polynomial_file)){

		fscanf (polynomial_file,"%c",&polynomial[i]);

		if (polynomial[i]=='x' || polynomial[i]=='X'){

			count++;
		}

		else if (polynomial[i]==' '){
			i--;
		}

		i++;

	}
	count--;
	if (polynomial[i]=='.'){
		polynomial[i-3]='\0';
	}

	else if (polynomial[i-3!='.']){
		polynomial[i-2]='\0';
	}

	strcpy (temp,polynomial);

	num = strtok (temp," x+-^");

	while (num!=NULL){

		nums[j]=atof(num);
		num = strtok (NULL," x+-^");	
		j++;

	}
	j=0;
	
}

void calculate_eva (double xs_coefficient[1000],double variable,int xs_exponent[1000],double values[100],char polynomial[1000],double nums[1000],int count){

	int i=0,
	j=0,
	flag=0,
	temp,
	count2=0,
	z=0;

	double result=0,
	power=0;

	FILE *eva;

	eva = fopen ("evaluations.txt","w");

	while (polynomial[i]!='\0'){

		if (i==0 && polynomial[i]=='x'){

			if (polynomial[i+1]!='^'){
				xs_coefficient[j]=1;
				xs_exponent[j]=1;
				j++;
			}

			else if (polynomial[i+1]=='^'){
				xs_exponent[j]=polynomial[i+2];
				xs_coefficient[j]=1;
				j++;
			}
		
		}

		else if (i!=0 &&(polynomial[i]>'0' && polynomial[i]<='9') && (polynomial[i-1]=='+' || polynomial[i-1]=='-')){

			temp=i;
			temp++;

			if (polynomial[temp]=='\0'){

				variable = variable+nums [count2];
				count2++;
			}	

			else {
				
				while (polynomial[temp]!='+' && polynomial[temp]!='-'){

					if (polynomial[temp]=='x'){
						flag++;
					}
					temp++;
				}

				if (flag==0){
					variable = variable+nums [count2];
					count2++;		
				}

				flag=0;
			}
		}

		else if (polynomial[i]=='x' && (polynomial[i-1]>'0' && polynomial[i-1]<='9')){

			if (polynomial[i+1]!='^'){
				xs_coefficient[j]=nums[count2];
				xs_exponent[j]=1;
				j++;
			}

			else if (polynomial[i+1]=='^'){
				xs_coefficient[j]=nums[count2];
				count2++;				
				xs_exponent[j]=nums[count2];				
				j++;
			}

			count2++;
		}

		else if (polynomial[i]=='x'){

			if (polynomial[i+1]!='^'){
				xs_coefficient[j]=1;
				xs_exponent[j]=1;
				j++;
			}

			else if (polynomial[i+1]=='^'){
				xs_coefficient[j]=1;			
				xs_exponent[j]=nums[count2];				
				j++;
			}

		}		
		i++;
	}
	i=0;
	j=0;


	for (i=0;i<count-1;i++){
	
		z=0;
		while (polynomial[z]!='\0'){

			if (z==0){

				power=pow (values[i],xs_exponent[j]);
				result=result+power*xs_coefficient[j];	
				j++;					

			}

			if (polynomial[z]=='-'){

				power=pow (values[i],xs_exponent[j]);
				result=result-power*xs_coefficient[j];	
				j++;	
			}

			if (polynomial[z]=='+'){

				power=pow (values[i],xs_exponent[j]);
				result=result+power*xs_coefficient[j];	
				j++;		
			}
			z++;
		}
		fprintf (eva,"%.2lf \n",result);		
		result=0;
		j=0;
	}

}				
