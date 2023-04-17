#include <stdio.h>

int main(){

	float n, /*added number*/
	a=0, /*average of chunk*/
	b=0; /*changed chunk*/
	
	int count=0, /*number of variables*/
	flag=0; /*for the after first number control*/

	const float p1=0.5,
	p2=20;

	FILE* fp1, /*input file*/
	*fp2; /*output file*/

	fp1 = fopen ("input.txt","r");
	fp2 = fopen ("output.txt","w");

	fscanf (fp1,"%f",&n);

	while (!feof(fp1)){

		if (count==0){ /*only for start*/

			a=n;
			count++;
			fprintf (fp2,"%.4f ",n);

		}

		else {
		
			if (flag==1){ /*for first of each line numbers*/

				fprintf (fp2,"%.4f ",a);
				flag=0;		

			}

			fscanf (fp1,"%f",&n);	
			if (feof(fp1)){
				fprintf(fp2,"average: %.4f \n",a); /*for last average*/
				break;
			}
			count++;		
			b = ((a*(count-1))+n)/count;

			if (!(b > a*(1+p1) || b < a*(1-p1) || a > n*p2 || a < n/p2)){ /*equation*/

				fprintf (fp2,"%.4f ",n);
				a=b;
				}

			else {

				fprintf(fp2,"average: %.4f \n",a);
				a=n;
				count=1;
				flag++;
			}

		}
	}

	fclose (fp1);
	fclose (fp2);

	return 0;

}
