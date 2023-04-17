#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class gate{

    public:

    virtual int evaluate(){ /*Calculation function its virtual because of polymorphsim*/

        return input_value;
    }

    void set_two_name_inputs (string inp1, string inp2){ /*Sets two names for inputs*/

        input1=inp1;
        input2=inp2;
    }
        
    void set_input_value(int value){ /*Inserts input value*/

        input_value=value;
    }

    string get_first_name (){ /*Returns first input name*/

        return input1;
    }

    string get_second_name (){ /*Returns second input name*/

        return input2;
    }    

    void set_gate_name(string gte_name){ /*Sets get name*/

        gate_name=gte_name;
    }

    string get_gate_name(){ /*Returns gate name*/

        return gate_name;
    }

    void set_name(string val_name){ /*Sets operation name*/

        name=val_name;
    }

    string get_name(){ /*gets operation name*/

        return name;
    }

    void set_output_count(int count){ /*Output number*/

        output_count=count;
    }

    int get_input_count(){ /*Input number*/

        return output_count;
    }

    void set_gate_number (int number){ /*Sets gate number*/

        gate_number=number;
    }

    void set_gate_type (string type){ /*Sets gate type*/

        gate_type=type;
    }

    string get_gate_type (){ /*Returns gate type*/

        return gate_type;
    }


    void set_outputname (string o1, string o2, string o3 , string o4){ /*Sets outputs*/

        output1_name=o1;
        output2_name=o2;
        output3_name=o3;
        output4_name=o4;                        
    }

    void set_first_gatee (gate* p){ 

        input1p = p;
       
    }

    void set_second_gatee (gate* p){

        input2p = p;
       
    }           

    private:

    int input_count=0,
    output_count=0,
    output_value;
    string name, /*Gate name for searchin*/
    gate_name, /*Gate name*/
    gate_type, /*Gate type*/
    output1_name, /*Output for decoder*/
    output2_name, /*Output for decoder*/
    output3_name, /*Output for decoder*/
    output4_name, /*Output for decoder*/
    input1,/*first Input name*/
    input2;/*second Input name */
    int input_value,
    gate_number=0;
    gate *input1p, /*Gaters for assigning pointer*/
    *input2p;

};

class inputs :public gate{ /*Input for input assigning gate*/

    public:

    void set_input_value(int value){

        input_value=value;
    }    

    private:
    string name;
    int input_value;

};

class and_gate :public gate{ /*And class for and gate operation*/

    public:

    int evaluate(){

        int temp1,
        temp2;

        temp1=input1p->evaluate();
        temp2=input2p->evaluate();
        cout << "work!";
        return temp1 && temp2;
    }

    private:
    string gate_name,
    input1_name,
    input2_name;
    gate *input1p,
    *input2p;
    int output_value;
};

class or_gate :public gate{ /*Or class for or gate operation*/

    public:

    int evaluate(){

        int temp1,
        temp2;

        temp1=input1->evaluate();
        temp2=input2->evaluate();

        return temp1 || temp2;
    } 

    private:
    string gate_name,
    input1_name,
    input2_name;
    gate *input1,
    *input2;
    int output_value;
};

class not_gate :public gate{ /*Not gate class for or gate operation*/

    public:

    int evaluate(){

        int temp,

        temp1=input->evaluate();

        return !temp;
    }  

    private:
    string gate_name,
    input_name;
    gate *input;
    int output_value;
};

class flipflop_gate :public gate{ /*Flip flop gate*/

    public:

    int evaluate(){

        int temp,

        temp1=input->evaluate();

        if (former_out==0 && temp==1){

            former_out=1;
            return temp;
        }

        else if (former_out==1 && temp==1){

            former_out=0;
            return !temp;
        }

        else if (former_out==1 && temp==0){

            return !temp;
        }

        else {

            return temp;
        }
    }  

    private:
    string gate_name,
    input_name;
    gate *input;
    int output_value;
    int former_out=0;
};

class decoder_gate :public gate{

    public:

    int evaluate(){

        int temp1,
        temp2;

        temp1=input1->evaluate();
        temp2=input2->evaluate();

        if (temp1==0 && temp2==0){

            output1_value=1;
        }

        else if (temp1==0 && temp2==1){

            output2_value=1;
        }

        else if (temp1==1 && temp2==0){

            output3_value=1;
        }

        else if (temp1==1 && temp2==1){

            output4_value=1;
        }
    }

    void set_outputname (string o1, string o2, string o3 , string o4){

        output1_name=o1;
        output2_name=o2;
        output3_name=o3;
        output4_name=o4;                        
    } 

    private:
    string inp1,
    inp2,
    output1_name,
    output2_name,
    output3_name,
    output4_name;
    int output1_value,
    output2_value,
    output3_value,
    output4_value;
    gate *input1,
    *input2;
    int output_value;
};

void read_circuit (gate **values,string filename);
void read_input_file (gate **values,string filename);

int main(){

    gate** circuit;
    
    read_circuit (circuit,"circuit.txt");

}

void read_circuit (gate **values,string filename){

    ifstream circuit_comp (filename);

    int i=0;

    char control;
    string temp;
    int gate_number=0,    
    output_gate_number=0,
    input_gate_number=0,
    input_number=0,
    output_number=0,
    and_gate_number=0,
    flipflop_gate_number=0,
    or_gate_number=0,
    not_gate_number=0,
    decoder_gate_number=0;

    while (!circuit_comp.eof()){


        circuit_comp >> temp;
        control=circuit_comp.get();        
        //cout << control;

        if (temp=="INPUT"){

            circuit_comp >> temp;   
            while (temp[0]>='a' && temp[0]<='z'){

                circuit_comp >> temp;
                control=circuit_comp.get();
                if (control=='\n'){

                    gate_number++;
                }                                
                input_number++;
            }

            input_gate_number++;
        }

        if (temp=="OUTPUT"){

            circuit_comp >> temp;   
            while (temp[0]>='a' && temp[0]<='z'){

                circuit_comp >> temp;
                control=circuit_comp.get();
                if (control=='\n'){

                    gate_number++;
                }                       
                output_number++;
            }

            output_gate_number++;
        }

        if (temp=="AND"){

            and_gate_number++;
        }

        if (temp=="OR"){

            or_gate_number++;
        }

        if (temp=="NOT"){

            not_gate_number++;
        }

        if (temp=="FLIPFLOP"){

            flipflop_gate_number++;
        }

        if (temp=="DECODER"){

            decoder_gate_number++;
        }                                            

        if (control=='\n'){

            gate_number++;
        }
    }

    gate_number=gate_number-input_gate_number-output_gate_number;
    gate_number+=input_number;

    gate **a = new gate*[gate_number];

    gate *total_inputs = new inputs; 

    circuit_comp.close();
    circuit_comp.open(filename);

    while (!circuit_comp.eof()){

        circuit_comp >> temp;

        if (temp=="INPUT"){

            circuit_comp >> temp;           
            
            while (temp[0]>='a' && temp[0]<='z' && !circuit_comp.eof()){
                
                a[i]= new (inputs);
                a[i][0].set_name(temp);
                a[i][0].set_gate_type("inp");
                i++;
                circuit_comp >> temp;                

            }

        }

        else if (temp=="OUTPUT"){

            circuit_comp >> temp;
        }

        if (temp=="AND"){

            circuit_comp >> temp;           
            
            while (temp[0]>='a' && temp[0]<='z' && !circuit_comp.eof()){
                
                
                string temp2;
                a[i]= new (and_gate);
                a[i][0].set_gate_type("and");                
                a[i][0].set_gate_name(temp);
                circuit_comp >> temp;
                circuit_comp >> temp2;
                a[i][0].set_two_name_inputs (temp,temp2);
                i++;
                circuit_comp >> temp;                                

            }

        }

        if (temp=="OR"){

            circuit_comp >> temp;           
            
            while (temp[0]>='a' && temp[0]<='z' && !circuit_comp.eof()){
                
                
                string temp2;
                a[i]= new (or_gate);
                a[i][0].set_gate_type("or");                
                a[i][0].set_gate_name(temp);
                circuit_comp >> temp;
                circuit_comp >> temp2;
                a[i][0].set_two_name_inputs (temp,temp2);
                i++;
                circuit_comp >> temp;                                

            }

        }

        if (temp=="NOT"){

            circuit_comp >> temp;           
            
            while (temp[0]>='a' && temp[0]<='z' && !circuit_comp.eof()){
                
                a[i]= new (not_gate);
                a[i][0].set_gate_type("not");
                a[i][0].set_gate_name(temp);
                circuit_comp >> temp;
                a[i][0].set_name (temp);
                i++;
                circuit_comp >> temp;                                

            }

        }

        if (temp=="FLIPFLOP"){

            circuit_comp >> temp;           
            
            while (temp[0]>='a' && temp[0]<='z' && !circuit_comp.eof()){
                
                a[i]= new (not_gate);
                a[i][0].set_gate_type("fp");
                a[i][0].set_gate_name(temp);
                circuit_comp >> temp;
                a[i][0].set_name (temp);
                i++;
                circuit_comp >> temp;                                

            }

        }

        if (temp=="DECODER"){

            circuit_comp >> temp;
            string temp2;
            control = 'e';           
            
            while (temp[0]>='a' && temp[0]<='z' && control != '\0' && !circuit_comp.eof()){
                
                a[i]= new (decoder_gate);
                a[i][0].set_gate_type("dec");
                string temp3,temp4;
                circuit_comp >> temp2;
                circuit_comp >> temp3;
                circuit_comp >> temp4;
                if (control == 'e'){                
                    a[i][0].set_outputname (temp,temp2,temp3,temp4);
                    circuit_comp >> temp;
                    circuit_comp >> temp2;                   
                    i++;
                    control = 'h';                        
                }
            }
        }                                     
    }
    string second_file_name = "input.txt";

    ifstream input (second_file_name);

    int number;
    i=0;
    int j,
    count;

    inputs **inputtt = new inputs*[input_number];

    for (i=0;i<input_number;i++){

        inputtt[i] = dynamic_cast <inputs*> (a[i]);
    }

    while (!input.eof()){

        for (i=0;i<input_number;i++){

            input >> temp;
            j= stoi(temp);
            inputtt[i]->set_input_value(j);
        }
        if (i==4){

            for (i=4;i<gate_number;i++){

                count=i-1;
                for (count=i-1;count>=0;count--){

                    if (a[i][0].get_gate_type()=="not" || a[i][0].get_gate_type()=="fp"){

                        if(a[i][0].get_first_name() == a[count][0].get_name()){

                            a[i][0].set_first_gatee(a[count]);
                        }
                    }

                    else if (a[i][0].get_gate_type()=="and" || a[i][0].get_gate_type()=="or"){

                        if(a[i][0].get_first_name() == a[count][0].get_name()){

                            a[i][0].set_first_gatee(a[count]);
                            
                        }

                        if(a[i][0].get_second_name() == a[count][0].get_name()){

                            a[i][0].set_second_gatee(a[count]);
                        }     
                    }
                }
            }

            /*if (i==gate_number){ /*I tried using evaluation but it does not worked*/

                count=input_number;
                for (count=input_number;count<gate_number;count++){

                    if (a[i][0].get_gate_type()=="and"){

                        and_gate *b ;
                        b =dynamic_cast <and_gate*> (a[i]);
                        cout << b[0].evaluate();

                    }
                }
            }*/
        }
    }

}

