#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class pixel{ /*Its class for images pixel.RGB*/

    public:
    int red, /*Stores Red data*/
    green, /*Stores Green data*/
    blue; /*Stores Blue data*/
};

class ppmImage{ /*PPM Image class*/

    public:
    ppmImage (const string file_name){ /*Read and assign object from file constructor*/

        int i=0,j=0; /*For loops*/
    
        pixel temp; /*For storing pixel value,then push it to 1D vector*/

        vector <pixel> temp_vec; /*For storing pixel value with 1 dimension.Then push it to 2D vector*/

        ifstream ppmFile(file_name);
        ppmFile >> image_format; /*Reading image format from file*/
        if (image_format!="P3"){ /*Controlling image format*/

            cout << "Wrong File Input" << endl;
        }

        else { /*If format is true*/

            ppmFile >> row; /*Reads variables*/
            ppmFile >> column;
            ppmFile >> maximum_color_value;
            if (maximum_color_value<0 || maximum_color_value>255){ /*If maximum color is wrong exit*/

                cout << "Wrong File Input" << endl;
            }

            else { /*Else read pixel values*/

                for (i=0;i<row;i++){

                    for (j=0;j<column;j++){

                        ppmFile >> temp.red;
                        ppmFile >> temp.green;                        
                        ppmFile >> temp.blue;
                        temp_vec.push_back(temp); /*Push temp pixel variables 1D vector*/
                        }
                    image_values.push_back(temp_vec); /*Push temp pixel vector variables 2D vector*/
                    temp_vec.clear(); /*Clear temp 1D vector for new variables*/
                    }
                }
            }
            ppmFile.close();
        }

    ppmImage(){ /*Default constructor*/
        
    };

    ppmImage (int dimension_row, int dimension_col){ /*Create a white ppm image for given dimensions.Constructor*/

        pixel temp; /*Temp variable for push 1D temp vector.*/

        vector <pixel> temp_vec; /*Temp variable for push 2D vector*/

        row=dimension_row; /*Saves row and columns for white image*/
        column=dimension_col;

        int i=0,j=0; /*for loops*/

        image_format="P3"; /*White images variable's*/
        maximum_color_value=255;
        temp.red=255;
        temp.green=255;                        
        temp.blue=255;

        for (j=0;j<column;j++){ /*Push pixel temp to 1d vector repeat same operation because vaeiables are same*/
            temp_vec.push_back(temp);  
        }              

        for (i=0;i<row;i++){

            image_values.push_back(temp_vec); /*Push pixel vector to 2d vector repeat same operation because vaeiables are same*/
        }

    }

    int read_file (const string read_file_name){ /*Read from file and save it to the object*/

    int i=0,j=0;

    ifstream ppmRead(read_file_name); /*Input file*/
    ppmRead >> image_format; /*Take image format from file*/
    if (image_format!="P3"){ /*If wrong return 0*/

        return 0;
    }

    else {  /*Else read other variables and coppy to object*/
        ppmRead >> row;
        ppmRead >> column;   
        ppmRead >> maximum_color_value;

        if (maximum_color_value<0 || maximum_color_value>255){ /*Control max color value if it is not true exit*/

            return 0;
        }

        else { /*If true create size for pixel variables*/
            
            image_values.resize(row); /*Makes size for first dimension*/
            for (i=0;i<column;i++){
            
                image_values[i].resize(column); /*Makes size for second dimension*/
            }

            for (i=0;i<row;i++){ /*Takes pixel values from file and coppy it object*/
            
                for (j=0;j<column;j++){
                
                    ppmRead >> image_values[i][j].red;
                    ppmRead >> image_values[i][j].green;
                    ppmRead >> image_values[i][j].blue; 
                    }
                }
            ppmRead.close(); 
            return 1; 
            }
        }  
    } 

    int save_file (const string file_name) const{ /*Takes object and writes its variable to file*/

    int i=0,j=0;

    ofstream ppmWrite(file_name);
    if (image_format!="P3" || maximum_color_value<0 || maximum_color_value>255){ /*Controls value's of object if they are not true exit*/

        return 0;
    }
    ppmWrite << image_format << endl; /*If they are writes them to file*/
    ppmWrite << row << " " << column << endl;
    ppmWrite << maximum_color_value << endl;

    for (i=0;i<row;i++){ /*Write pixel values to file*/

        for (j=0;j<column;j++){

            ppmWrite << image_values[i][j].red << " ";
            ppmWrite << image_values[i][j].green << " ";
            ppmWrite << image_values[i][j].blue << " ";
            }

        ppmWrite << endl;
        } 
    ppmWrite.close();
    return 1;
    }        
    
    int print_dimension(){ /*Printes dimensions of an object*/

        cout << "Row:" << row << endl <<"Column:" << column << endl;
    }
    int return_pixel_information (int rw, int clmn, int choice){ /*Returns pixel information of a coordinate.rw and clmn coordinate.Choice value selects 0 red or 1 green or 2 blue pixel*/

        if (rw >=row || clmn >=column){

            return 0;
        }

        else if (choice==0){ 

            return image_values[rw][clmn].red;
        }

        else if (choice==1){

            return image_values[rw][clmn].green;
        }

        else if (choice==2){

            return image_values[rw][clmn].blue;
        }                
    }

    int change_pixel (ppmImage& b, int choice,int r,int c) { /*changes one individual pixel or coppy it another object for red c=1 for green c=2 for blue=3*.I used () operator for take values*/

        int temp;

        if (choice==1){

            image_values[r][c].red=b(r,c,choice);
        }

        else if (choice==2){

            image_values[r][c].green=b(r,c,choice);
        }

        else if (choice==3){

            image_values[r][c].blue=b(r,c,choice);
        }

        else {

            return 0;
        }
    }

    int swap_pixel (ppmImage& b, int choice,int r,int c) { /*Swaps 1 pixel with another.Used for swap function.I used () operator for take values*/

        int temp;

        if (choice==1){ /*If 1 change red and green*/

            temp=b(r,c,choice);
            image_values[r][c].red=b(r,c,choice+1);
            image_values[r][c].green=temp;
        }

        else if (choice==2){ /*If 2 change red and blue*/

            temp=b(r,c,choice+1);
            image_values[r][c].blue=b(r,c,choice-1);
            image_values[r][c].red=temp;
        }

        else if (choice==3){ /*If 3 change blue and green*/

            temp=b(r,c,choice);
            image_values[r][c].blue=b(r,c,choice-1);
            image_values[r][c].green=temp;
        }

        else {

            return 0;
        }
    }    
    
    int get_row () const{ /*Returns row value of object*/

        return row;
    }
    int get_column () const{ /*Returns column value of object*/

        return column;
    }

    void create_object(const ppmImage& obj){ /*Creates new 2D vector pixel object resize it and fills it whit source*/

        image_format=obj.image_format; /*Fills values with source objects values */
        row=obj.row;
        column=obj.column;
        maximum_color_value=obj.maximum_color_value;
        image_values.resize(row);
        
        for (int i=0;i<column;i++){ /*Creates size for pixel values*/
            
            image_values[i].resize(column);
        }
        
    }

    ppmImage operator+ (const ppmImage& b){ /*Overloads + operator.Adds two ppmImage objects pixels*/

        ppmImage add; /*New object for adding operation*/
        int i=0,j=0;

        if (row!=b.row && column!=b.column){ /*Controls dimensions*/

            return add;
        }

        else {

            add.image_values.resize(row); /*Create size for add object*/
            for (i=0;i<row;i++){

                add.image_values[i].resize(column);
            }

            add.image_format=image_format; /*Takes other values from any other object*/
            add.maximum_color_value=maximum_color_value;
            add.row=row;
            add.column=column;

            for (i=0;i<row;i++){ /*Adds pixel values and returns add.If pixel value is greter than 255 asing it to 255*/

                for (j=0;j<column;j++){

                    add.image_values[i][j].red=image_values[i][j].red+b.image_values[i][j].red;
                    if (add.image_values[i][j].red>255){

                        add.image_values[i][j].red=255;
                    }

                    add.image_values[i][j].green=image_values[i][j].green+b.image_values[i][j].green;
                    if (add.image_values[i][j].green>255){

                        add.image_values[i][j].green=255;
                    }

                    add.image_values[i][j].blue=image_values[i][j].blue+b.image_values[i][j].blue;
                    if (add.image_values[i][j].blue>255){

                        add.image_values[i][j].blue=255;
                    }                    
                }

            }
            return add;
        }
    }

    ppmImage operator- (const ppmImage& b){ /*Overloads - operator.Subtracts one object to another*/

        ppmImage sub; /*Create new object for subtract*/
        int i=0,j=0;

        if (row!=b.row && column!=b.column){ /*Control dimensions*/

            return sub;
        }

        else {

            sub.image_values.resize(row); /*Creates size for sub object to save pixel values in there*/
            for (i=0;i<row;i++){

                sub.image_values[i].resize(column);
            }

            sub.image_format=image_format; /*Takes other variables from another object*/
            sub.maximum_color_value=maximum_color_value;
            sub.row=row;
            sub.column=column;

            for (i=0;i<row;i++){ /*Subtract two objects pixel values and assign it to sub object then return it.If value is lower than zero asign it to 0.*/

                for (j=0;j<column;j++){

                    sub.image_values[i][j].red=image_values[i][j].red-b.image_values[i][j].red;
                    if (sub.image_values[i][j].red<0){

                        sub.image_values[i][j].red=0;
                    }

                    sub.image_values[i][j].green=image_values[i][j].green-b.image_values[i][j].green;
                    if (sub.image_values[i][j].green<0){

                        sub.image_values[i][j].green=0;
                    }

                    sub.image_values[i][j].blue=image_values[i][j].blue-b.image_values[i][j].blue;
                    if (sub.image_values[i][j].blue<0){

                        sub.image_values[i][j].blue=0;
                    }                    
                }

            }
            return sub;
        }
    }

    friend ostream& operator << (ostream &output,const ppmImage& source){ /*Overloads << operator.Prints object values to stdout*/

        int i=0,j=0;

        output << source.image_format << endl;
        output << source.row << " " << source.column << endl;
        output << source.maximum_color_value << endl;

        for (i=0;i<source.row;i++){

            for (j=0;j<source.column;j++){

                output << source.image_values[i][j].red << " ";
                output << source.image_values[i][j].green << " ";
                output << source.image_values[i][j].blue << " ";
            }

            output << endl;
        }          

    }

    int& operator () (int row_val,int col_val,int pix_val){ /*Returns pixel information of a coordinate.row and colmun coordinate.Choice value selects 1 red or 2 green or 3 blue pixel and returns*/

        if (row_val < row && col_val< column){

            if (pix_val==1){

                return image_values[row_val][col_val].red;
            }

            else if (pix_val==2){

                return image_values[row_val][col_val].green;
            }

            else if (pix_val==3){

                return image_values[row_val][col_val].blue;
            }
        }

    } 

    private: /*Private datas*/
    string image_format; /*Takes image format "P3" */
    int row, /*Row value*/
    column, /*Column Value*/
    maximum_color_value;    /*Takes maximum color value 255*/
    vector<vector<pixel>> image_values; /*Creates 2D pixel vector*/

};

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
int write_ppm(const string destination_ppm_file_name,const ppmImage& source_object);
int test_addition (const string filename_image1,const string filename_image2,const string filename_image3); 
int test_subtraction (const string filename_image1,const string filename_image2,const string filename_image3);
int test_print (const string filename_image1); 
ppmImage single_color (ppmImage source, int color_choice);
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);


int main(int argc,char **argv){

    if (isdigit(argv[1][0])==0){ /*Controls first arguement if its a number*/


    }

    else if (argv[1][0]-'0'>=8){ /*Controls maximum choice*/


    }

    else if (argv[2][0]=='\0'){ /*Controls third arguement*/


    }

    else {
    
        int choice;
        string f1name=argv[2];
        choice=argv[1][0]-'0'; /*Turns arguement 1 to integer and assing it to choice*/
        ppmImage ppm_file;
        
        bool control;

        switch (choice){

            case 1:

                if (argc!=5){
                
                    /*Exit*/
                }

                else {

                    test_addition (argv[2],argv[3],argv[4]);
                }
                break;

            case 2:
                
                if (argc!=5){
                
                    /*Exit*/
                }

                else {

                    test_subtraction (argv[2],argv[3],argv[4]);
                }
                break;

            case 3:
                control=read_ppm(f1name,ppm_file);
                if (control==1){
                    swap_channels(ppm_file,2);
                    write_ppm("ppm_filename_2.ppm",ppm_file);
                }
                break;

            case 4:
                control=read_ppm(f1name,ppm_file);
                if (control==1){
                    swap_channels(ppm_file,3);
                    write_ppm("ppm_filename_2.ppm",ppm_file);
                }
                break;

            case 5:{
                control=read_ppm(f1name,ppm_file);
                if (control==1){
                    ppmImage single_clr;
                    single_clr=single_color(ppm_file,1);
                    write_ppm("ppm_filename_2.ppm",single_clr);
                }
                break;
            }

            case 6:{
                control=read_ppm(f1name,ppm_file);
                if (control==1){
                    ppmImage single_clr;
                    single_clr=single_color(ppm_file,2);
                    write_ppm("ppm_filename_2.ppm",single_clr);
                }
                break;
            }

           case 7:{
                control=read_ppm(f1name,ppm_file);
                if (control==1){
                    ppmImage single_clr;
                    single_clr=single_color(ppm_file,3);
                    write_ppm("ppm_filename_2.ppm",single_clr);
                }
                break;
            }
                                                                                      
        }
    }
}

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){ /*reads ppm data from file stores data in object .If succes return 1 else 0*/

    bool control; /*For return value*/
    control=destination_object.read_file(source_ppm_file_name);

    if (control){

        return 1;
    }

    else {

        return 0;
    }
}

int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){ /*reads ppm data from object prints data to file. If succes return 1 else 0*/

    bool control; /*For return value*/
    control=source_object.save_file(destination_ppm_file_name);    

    if (control){

        return 1;
    }

    else {

        return 0;
    }    
}

int test_addition (const string filename_image1,const string filename_image2,const string filename_image3){ /*Adds two object to each other return 1 for succes else 0*/

    ppmImage a,b,sum; /*SUm variables*/
    bool control1,control2;
    control1=a.read_file(filename_image1);
    control2=b.read_file(filename_image2);
    
    if (control1==1 && control2==1){ /*If all file reads are succesfull make adding operation*/
        sum=a+b;
        sum.save_file(filename_image3);
        return 1;
    }

    else {

        return 0;
    }

}

int test_subtraction (const string filename_image1,const string filename_image2,const string filename_image3){ /*Subtracks two object to each other return 1 for succes else 0*/
 
    ppmImage a,b,sub; /*Subtract variables*/
    bool control1,control2;
    control1=a.read_file(filename_image1);
    control2=b.read_file(filename_image2);
    
    if (control1==1 && control2==1){ /*If all file reads are succesfull make subtraction operation*/
        sub=a-b;
        sub.save_file(filename_image3);
        return 1;
    }

    else {

        return 0;
    }
    
}

int test_print (const string filename_image1){ /*Reads from file a ppm image stores it in object then prints object with << operator.For succes return 1 else 0*/

    ppmImage ppm1;
    bool control;
    control=ppm1.read_file(filename_image1);
    if (control){

        cout << ppm1;
        return 1;
    }

    else {

        return 0;
    }
}

int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){ /*Swap two pixel with each other for 1 red and green, 2 red and blue, 3 blue and green.If succes return 1 else 0*/

    int i=0,j=0,row,column;

    row=image_object_to_be_modified.get_row(); /*Takes row and column information*/
    column=image_object_to_be_modified.get_column();

    if (swap_choice==1){

        for (i=0;i<row;i++){

            for (j=0;j<column;j++){

                image_object_to_be_modified.swap_pixel(image_object_to_be_modified,swap_choice,i,j); /*Changes every red and green pixel with each other for al dimensions*/
            }
        }
        return 1;
    }

    else if (swap_choice==2){

        for (i=0;i<row;i++){

            for (j=0;j<column;j++){

                image_object_to_be_modified.swap_pixel(image_object_to_be_modified,swap_choice,i,j); /*Changes every red and blue pixel with each other for all dimensions*/
            }
        }       
        return 1;
    }

    else if (swap_choice==3){

        for (i=0;i<row;i++){

            for (j=0;j<column;j++){

                image_object_to_be_modified.swap_pixel(image_object_to_be_modified,swap_choice,i,j); /*Changes every green and blue pixel with each other for all dimensions*/
            }
        }        
        return 1;
    }

    else {

        return 0;
    }           
}

ppmImage single_color (ppmImage source, int color_choice){ /*Take copy of 1 pixel.Makes other 0.For 1 takes red pixel,2 takes green pixel,3 takes blue pixel.Save it from new object.Then return new object*/

    int i=0,j=0,row,column;
    ppmImage single_color;
    single_color.create_object(source); /*Creates size for new object*/
    row=source.get_row(); /*Takes its row and column from source object*/
    column=source.get_column();

    for (i=0;i<row;i++){

        for (j=0;j<column;j++){

            single_color.change_pixel(source,color_choice,i,j); /*Takes all choiced pixel for all dimensions*/
        }
    }

    return single_color;

}
