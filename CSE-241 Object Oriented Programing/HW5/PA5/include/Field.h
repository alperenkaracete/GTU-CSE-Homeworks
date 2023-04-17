#ifndef FIELD_H
#define FIELD_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


template <typename T>
class Field  /*Base class called Field, all fields inherits from base class. */
    {
    public:
    	enum FieldType /*For determining type of input*/
    	{
    		Title = 0,
    		Authors = 1,
    		Year = 2,
    		Tags = 3,
    		Artists = 4,
    		Genre = 5,
    		Director = 6,
    		Starring = 7,
    		EmptyField = 999,
    	};

    	Field() {} /*Main Constructor*/
    	
        Field(T content);	/*Constructor method for base class.*/

    	T GetContent() const;	/*Gets the content of field.*/

    	void SetContent(T content);	/*Sets the content of field.*/

    	static FieldType Transform(string fieldName) /*Determines and Returns file type*/
    	{
    		if (fieldName == "title")
    			return FieldType::Title;
    		else if (fieldName == "tags")
    			return FieldType::Tags;
    		else if (fieldName == "year")
    			return FieldType::Year;
    		else if (fieldName == "authors")
    			return FieldType::Authors;
    		else if (fieldName == "artists")
    			return FieldType::Artists;
    		else if (fieldName == "director")
    			return FieldType::Director;
    		else if (fieldName == "starring")
    			return FieldType::Starring;
    		else if (fieldName == "genre")
    			return FieldType::Genre;
    		else
    			return FieldType::EmptyField;
    	}

    private:
    	T content;	//Content in type T.

    };

#endif
