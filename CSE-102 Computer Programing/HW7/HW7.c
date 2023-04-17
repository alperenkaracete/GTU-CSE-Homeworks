#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 10

typedef struct circuit {

	char name[MAX_LENGTH];
	int type;
	char input1[MAX_LENGTH]; 
	char input2[MAX_LENGTH]; 
	int input1_val;
	int input2_val;
	int output;
	int flip_mem;
	struct circuit *gate1;	
	struct circuit *gate2;	

}circuit;

int main(){

	int count=0,
	count_input_value,
	count2=0,
	control,
	j=0,
	i=0,
	read_values[MAX_LENGTH][MAX_LENGTH];

	char name[MAX_LENGTH],
	a;

	FILE *inputs,*values,*output;

	circuit *c;

	inputs = fopen ("circuit.txt","r");
	values = fopen ("input.txt","r");
	output = fopen ("output.txt","w");

	c = (circuit*) malloc (1*sizeof(circuit));	

	while (!feof(inputs)){

		fscanf (inputs,"%s",name);

		if (name[0]=='I' || (name[0]!='A' && name[0]!='O' && name[0]!='N' && name[0]!='F' && count==0) ){

				while (name[0]!='O' && name[0]!='A' && name[0]!='N' && name[0]!='F' ){ 
					
					fscanf (inputs,"%s",name);					
					c = realloc (c, (count+2)*sizeof (circuit));
					if (name[0]>='a' && name[0]<='z'){
						strcpy(c[count].name,name);
						count++;						
						}								
					}		
				count_input_value=count;								
				}					

		if (name[0]=='A'){	

			while (name[0]!='O' && name[0]!='N' && name[0]!='F' && !feof(inputs) ){ 
				
				c = realloc (c, (count+2)*sizeof (circuit));
				c[count].type= 0;
				c[count].output= 1;				
				fscanf (inputs,"%s",name);	
				if (name[0]>='a' && name[0]<='z'){
					strcpy(c[count].name,name);
					count++;					
				}


				for (i=0;i<count-1;i++){

					control = strcmp (c[i].name,name);
					if (control==1){

						if (count2==0){
							
							strcpy(c[count-1].input1,c[i].name);
							c[count-1].input1_val=c[i].output;
							count2++;
							c[count-1].output=c[count-1].output*c[i].output;							
							}

						else {
							
							strcpy(c[count-1].input1,c[i].name);
							c[count-1].input1_val=c[i].output;
							c[count-1].output=c[count-1].output*c[i].output;	
							count2=0;							
							}	
						}
					} 
				}	
			}

		if (name[0]=='O'){	

			while (name[0]!='A' && name[0]!='N' && name[0]!='F' ){ 
				
				c = realloc (c, (count+2)*sizeof (circuit));
				c[count].type= 1;
				c[count].output= 0;				
				fscanf (inputs,"%s",name);	
				if (name[0]>='a' && name[0]<='z'){
					strcpy(c[count].name,name);
					count++;					
				}
			
				for (i=0;i<count-1;i++){

					control = strcmp (c[i].name,name);
					if (control==1){

						if (count2==0){
							
							strcpy(c[count-1].input1,c[i].name);
							c[count-1].input1_val=c[i].output;
							count2++;
							c[count-1].output=c[count-1].output+c[i].output;							
							}

						else {
							
							strcpy(c[count-1].input1,c[i].name);
							c[count-1].input1_val=c[i].output;
							c[count-1].output=c[count-1].output+c[i].output;	
							count2=0;							
							}	
						}
					if (c[count-1].output>0){

						c[count-1].output=1;
						}	
					} 
				}	
			}

		if (name[0]=='N'){

			c = realloc (c, (count+2)*sizeof (circuit));
			c[count].type= 2;
			fscanf (inputs,"%s",name);	
				if (name[0]>='a' && name[0]<='z'){
					strcpy(c[count].name,name);
					count++;					
				}
			for (i=0;i<count-1;i++){

				control = strcmp (c[i].name,name);
				if (control==1){

					if (c[i].output>0){

						c[count-1].output=0;
					}

					else {

						c[count-1].output=1;
					}
				}		
			}
					
		}

		if (name[0]=='F'){

			c = realloc (c, (count+2)*sizeof (circuit));
			c[count].type=3;
			c[count].flip_mem=0;
			fscanf (inputs,"%s",name);	
				if (name[0]>='a' && name[0]<='z'){
					strcpy(c[count].name,name);
					count++;					
				}
			for (i=0;i<count-1;i++){

				control = strcmp (c[i].name,name);
				if (control==1){

					if (c[i].output==0){

						c[count-1].output=c[count-1].flip_mem;
					}

					else {

						if (c[count-1].flip_mem==0){

							c[count-1].output=1;
						}

						else {

							c[count-1].output=0;
						}
					}
				}		
			}						
		}

	}

	control=0;
	i=0;
	j=0;
	while (!feof(values)){

		fscanf (values,"%d",&read_values[i][j]);
		c[j].output=read_values[i][j];
		j++;

		if (j==count_input_value){

			i++;
			j=0;
			fprintf (output,"%d\n",c[count-4].output);
		}

	}


}	