#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	capacity = source.capacity;
	terms = source.terms;
	termArray = new Term[capacity];
	for(int i =0; i<terms; i++){
		termArray[i].exp = source.termArray[i].exp;
		termArray[i].coef = source.termArray[i].coef;
	}
}	

// Destructor
Polynomial::~Polynomial()
{
	delete[] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
	if(this == &source) return *this;
	
	delete[] termArray;

	capacity = source.capacity;
	terms = source.terms;
	termArray = new Term[capacity];
	for(int i=0; i<terms; i++){
		termArray[i].exp = source.termArray[i].exp;
		termArray[i].coef = source.termArray[i].coef;
	}
	return *this;

}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
	Polynomial c;
	
	if(terms == 0 && source.terms == 0) return *this;

	int a = 0, b = 0;
	while((a<terms-1) && (b<(source.terms)-1)){
		if(termArray[a].exp == source.termArray[b].exp){			
			float d = termArray[a].coef + source.termArray[b].coef;
			if(d){
				c.CreateTerm(d,termArray[a].exp);
			}
			a++;
			b++;
		}
		else if(termArray[a].exp<source.termArray[b].exp){
			c.CreateTerm(source.termArray[b].coef, source.termArray[b].exp);
			b++;
		}
		else{
			c.CreateTerm(termArray[a].coef, termArray[a].exp);
			a++;
		}

	}
	for(; a<terms-1; a++){
		c.CreateTerm(termArray[a].coef, termArray[a].exp);
	}
	for(; b<(source.terms)-1; b++){
		c.CreateTerm(termArray[b].coef, termArray[b].exp);
	}
	
	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;

	if(terms == 0 && source.terms == 0) return *this;

	int a = 0, b = 0;
	while((a<terms-1) && (b<(source.terms)-1)){
		if(termArray[a].exp == source.termArray[b].exp){			
			float d = termArray[a].coef - source.termArray[b].coef;
			if(d){
				c.CreateTerm(d,termArray[a].exp);
			}
			a++;
			b++;
		}
		else if(termArray[a].exp<source.termArray[b].exp){
			c.CreateTerm(-source.termArray[b].coef, source.termArray[b].exp);
			b++;
		}
		else{
			c.CreateTerm(termArray[a].coef, termArray[a].exp);
			a++;
		}

	}
	for(; a<=terms-1; a++){
		c.CreateTerm(termArray[a].coef, termArray[a].exp);
	}
	for(; b<=(source.terms)-1; b++){
		c.CreateTerm(-termArray[b].coef, termArray[b].exp);
	}
	
	return c;
	
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;
	c.CreateTerm(0,0);
	for(int i = 0; i< terms; i++){
		Polynomial temp;
		for(int j = 0; j<source.terms; j++){
			temp.CreateTerm(termArray[i].coef*source.termArray[j].coef,termArray[i].exp+source.termArray[j].exp);
		}
		c =c+ temp;
	}
	
	return c;	
}

bool Polynomial::operator == (const Polynomial& source)
{
	bool ret;
	
	if(terms!=source.terms){
		ret = false;
	}else{
		ret = true;
		for(int i=0; i<terms; i++){
			if((termArray[i].coef != source.termArray[i].coef) || (termArray[i].exp!=source.termArray[i].exp)){
				ret = false;
				break;
			}
		}
	}
	
	return ret;
}

float Polynomial::Eval(float x)
{
	float ret = 0;
	for(int i = 0; i<terms; i++)
	{	
		float temp = 1;
		for(int j = 0; j<termArray[i].exp; j++)
		{
			temp*=x;
		}
		ret += (temp*termArray[i].coef);
	}
	
	return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;
	
	for(int i=0; i<terms; i++){
		if(termArray[i].exp==0) continue;
		c.CreateTerm(termArray[i].coef*termArray[i].exp, termArray[i].exp-1);
	}	
	return c;	

}

void Polynomial::CreateTerm(const float coef, const int exp)
{
	if(terms == capacity){
		capacity *=2;
		Term *temp = new Term [capacity];
		std::copy(termArray, termArray+terms, temp);
		delete[] termArray;
		termArray = temp;

	}
	termArray[terms].coef = coef;
	termArray[terms++].exp = exp;
	terms++;
	
}

