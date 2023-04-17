#include "Field.h"

    
    template <typename T>
    Field<T>::Field(T content)	/*Constructor method for base class.*/
    	{
    		this->content = content;
    	}

    template <typename T>
    T Field<T>::GetContent() const	/*Gets the content of field.*/
    	{
    		return this->content;
    	}

    template <typename T>        	        
    void Field<T>::SetContent(T content)	/*Sets the content of field.*/
    {
    	this->content = content;
    }

    template class Field<int>; /*These are for preventing undefined reference*/
    template class Field<string>; /*These are for preventing undefined reference*/