#include <stdio.h>

#define line_number 4

int main(){

	float coordinate_x=0,
	coordinate_y=0,
	sum_coordinate_x1=0,  /*takes addition of class1's x point*/
	sum_coordinate_y1=0,  /*takes addition of class1's y point*/	
	sum_coordinate_x2=0,  /*takes addition of class2's x point*/
	sum_coordinate_y2=0,  /*takes addition of class2's y point*/	
	average_point_x1=0,  /*clas1 x point's average*/
	average_point_y1=0,	 /*clas1 y point's average*/
	average_point_x2=0,  /*clas2 x point's average*/
	average_point_y2=0,  /*clas2 y point's average*/
	line_connecting_two_average_points_x_coefficient,  /*x's coefficient*/
	line_connecting_two_average_points_y_coefficient,  /*y's coefficient*/
	line_connecting_two_average_points_x_variable,     /*x's variable*/
	line_connecting_two_average_points_y_variable,	   /*y's variable*/		
	mid_point_x=0,  /*mid point of two x point*/
	mid_point_y=0,	/*mid point of two y point*/
	seperate_line_coordinate_x_coefficient,	/*x's coefficient*/
	seperate_line_coordinate_y_coefficient,	/*y's coefficient*/
	seperate_line_coordinate_x_variable,	/*x's variable*/
	seperate_line_coordinate_y_variable,	/*y's variable*/
	slope=0;  /*slope of line*/ 

	int i=0;

	for (i=0;i<line_number;i++){

		scanf ("%f %f",&coordinate_x,&coordinate_y );
		
		if (i<line_number/2){

			sum_coordinate_x1+=coordinate_x;	/*Takes class 1 x points and sum them*/
			sum_coordinate_y1+=coordinate_y;	/*Takes class 1 y points and sum them*/

		}

		else {
			
			sum_coordinate_x2+=coordinate_x;	/*Takes class 2 x points and sum them*/
			sum_coordinate_y2+=coordinate_y;	/*Takes class 2 y points and sum them*/

		}

	}

	average_point_x1 = sum_coordinate_x1/(line_number/2); /*average point x axis of class 1*/
	average_point_y1 = sum_coordinate_y1/(line_number/2); /*average point y axis of class 1*/
	average_point_x2 = sum_coordinate_x2/(line_number/2); /*average point x axis of class 2*/
	average_point_y2 = sum_coordinate_y2/(line_number/2); /*average point y axis of class 2*/

	line_connecting_two_average_points_x_coefficient  = average_point_y2-average_point_y1;  /*I used formula.It is equation of which two points are known.*/
	line_connecting_two_average_points_x_variable  = (average_point_y2-average_point_y1)*(-average_point_x2);  /*I used formula.It is equation of which two points are known.*/
	line_connecting_two_average_points_y_coefficient = average_point_x2-average_point_x1;  /*I used formula.It is equation of which two points are known.*/
	line_connecting_two_average_points_y_variable = (average_point_x2-average_point_x1)*(-average_point_y2);  /*I used formula.It is equation of which two points are known.*/			

	mid_point_x = (average_point_x1+average_point_x2)/2; /*mid point x axis*/
	mid_point_y = (average_point_y1+average_point_y2)/2; /* mid point y axis*/	

	if (average_point_x2-average_point_x1==0){ /*Different formula for divide by zero situation. (y2-y1)*(x-x2) = (x2-x1)*(y-y2)*/

		seperate_line_coordinate_x_coefficient = 1; /*x's coefficient*/
		seperate_line_coordinate_x_variable = -mid_point_x;  /*x's variable*/	

	}

	else if (average_point_y2-average_point_y1==0){ /*Different formula slope zero situation. (y2-y1)*(x-x2) = (x2-x1)*(y-y2)*/

		seperate_line_coordinate_y_coefficient = 1; /*y's coefficient*/
		seperate_line_coordinate_y_variable = -mid_point_y;  /*y's variable*/	

	}	

	else {

		slope = -1/((average_point_y2-average_point_y1)/(average_point_x2-average_point_x1)); /*slope of seperate line*/

		seperate_line_coordinate_x_coefficient = -slope;  /*I used formula.It is equation of which two points and slope are known.*/ 
		/*We take slope negative because if lines are perpendicular to each other their slopes multiply is equal to -1.*/
		seperate_line_coordinate_x_variable = (-slope)*(-mid_point_x);  /*I used formula.It is equation of which two points and slope are known.*/		
		seperate_line_coordinate_y_coefficient = 1;  /*I used formula.It is equation of which two points and slope are known.*/
		seperate_line_coordinate_y_variable = -(mid_point_y);  /*I used formula.It is equation of which two points and slope are known.*/		

	}

	while(1){

		if(scanf ("%f %f",&coordinate_x,&coordinate_y)==2){
		

			if ((seperate_line_coordinate_x_coefficient*coordinate_x+seperate_line_coordinate_x_variable+seperate_line_coordinate_y_coefficient*coordinate_y+seperate_line_coordinate_y_variable)<0 && slope<0 
			|| (seperate_line_coordinate_x_coefficient*coordinate_x+seperate_line_coordinate_x_variable+seperate_line_coordinate_y_coefficient*coordinate_y+seperate_line_coordinate_y_variable)>0 && slope>0 ){
			/*In that if I have 2 condition.First condition: If slope < 0 and when use x,y values in equation if result to <0 so it is in class 1.	
			                                Second condition: If slope > 0 and when use x,y values in equation if result to >0 so it is in class 1.	because slope changes line situations.*/
				printf ("class1\n");
								
			}

			else if ((seperate_line_coordinate_x_coefficient*coordinate_x+seperate_line_coordinate_x_variable+seperate_line_coordinate_y_coefficient*coordinate_y+seperate_line_coordinate_y_variable)>0 && slope<0 
			|| (seperate_line_coordinate_x_coefficient*coordinate_x+seperate_line_coordinate_x_variable+seperate_line_coordinate_y_coefficient*coordinate_y+seperate_line_coordinate_y_variable)<0 && slope>0 ){
			/*In that if I have 2 condition.First condition: If slope < 0 and when use x,y values in equation if result >0 so it is in class 2.	
			                                Second condition: If slope > 0 and when use x,y values in equation if result <0 so it is in class 2.	because slope changes line situations.*/
				printf ("class2\n");			
			}

			else if (average_point_y2-average_point_y1==0 || average_point_y1<0){ /*if slope infinite use that*/

				if (coordinate_y<0){
					printf ("class1\n");

					}

				else {
					printf ("class2\n");

				}
			}

			else if (average_point_y2-average_point_y2==0 || average_point_y1>0 ){ /*if slope infinite use that*/

				if (coordinate_y>0){
					printf ("class1\n");

					}

				else {
					printf ("class2\n");

				}
			}			

		}

		
		else {

			break;
		}	

	} 

	return 0;

}