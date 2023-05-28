#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cwctype>
#include <algorithm>
#include <string>
using namespace std;

//create class to store order attributes;
class order{
	public:
	  string Cl_Ord_Id;
	  string Instrument;
	  int side;
	  int quantity;
	  int price;
	//create constructor to assign the values for (orders's attributes) object's members; 
	order(string Id,string Name,int Side,int Quantity,int Price){
		Id = Cl_Ord_Id;
		Name = Instrument;
		Side = side;
		Quantity = quantity;
		Price = price;
	}
	
};
//function for get the execution report
void output(string Id,string Name,string Side,string Quantity,string Price,string reason,string execution_status){
		fstream fout;
		fout.open("execution_report.csv",ios::out | ios::app);
		fout << Id << ","
             << Name << ","
             << Side << ","
             << execution_status<<","
             << Quantity << ","
             << Price << ","
             << reason<<"\n";
        fout.close();
}
// check the client order id, is it a alphanumerical or not
bool isAlphaNumeric(const std::string &str)
{
	return std::all_of(str.begin(), str.end(), ::isalnum);
}
	
void read_record()
{
  
    // File pointer
    fstream fin;
    // create dynamic array to store data as belongs to its structure
    vector<order>execution;
    // string variables
    string line;
    // Open an existing file
    fin.open("..\\orders.csv", ios::in);
    // extract data from each row
    while(getline(fin,line)){
        stringstream x(line);
	    string Cl_Ord_Id;
	    string Instrument;
	    int side;
	    int quantity;
	    int price;
	    string reason="";
	    string temp1,temp2,temp3;
	    stringstream s(line);
    	getline(s,Cl_Ord_Id,',');
    	getline(s,Instrument,',');
    	//convert the variable types (string to int)
    	getline(s,temp1,',');
    	side = atoi(temp1.c_str());
    	getline(s,temp2,',');
    	quantity = atoi(temp2.c_str());
    	getline(s,temp3,'.');
    	price = atoi(temp3.c_str());
    	//insert data into struct
    	order orders(Cl_Ord_Id ,Instrument,side,quantity,price);
    	//set Reject as a default option for execution_result before start the validation process
    	string execution_result ="Reject";
    	
    	//validation process
    	//Is there are empty fields were there? 
	    if(Cl_Ord_Id!="" || Instrument!="" || temp1!="" || temp2!="" || temp3!=""){
	    //Is the Client Order valid or not?
	     if(Cl_Ord_Id!="" && isAlphaNumeric(Cl_Ord_Id)){
          if(Instrument!="" &&(Instrument=="Rose" || Instrument=="Orchid" || Instrument=="Lotus" || Instrument=="Lavender" || Instrument=="Tulip" ) ) 
		   { 
			  if(temp1!="" && (side==1 || side == 2))
			  {  
				  if(temp3!="" && price >0)
				  {
					  if(temp2!="" && quantity%10==0 && quantity >=10  && quantity<=1000)
					  {
	        	                execution.push_back(orders);
	        	                execution_result = "New";
	        	            }
							else{
								reason = "invalid size";
							}
				  }
				  else{
					   reason = "invalid price";
				  }
			  }
			  else{
				   reason = "invalid side";
			  }
	    	}
			else{
				 reason = "invalid Instrument";
			}
		}
		else{
			reason = "invalid Client Order Id";
		}
		}
		else{
			reason = "Empty field";
		}
		output(Cl_Ord_Id ,Instrument,temp1,temp2,temp3,reason,execution_result);
	}   
}

//main function
int main(){
	read_record();
}