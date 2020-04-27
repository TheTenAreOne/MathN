#ifndef MATHN_H_
#define MATHN_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct Real Real;

struct Real{
	int numerator;
	int denominator;
	void (*sum) ( Real, Real, Real * );
	void (*subtraction) ( Real, Real, Real * );
	void (*multiplication) ( Real, Real, Real * );
	void (*division) ( Real, Real, Real * );
	void (*simplify) ( Real * );
	void (*flip) ( Real * );
};

//a: first number, b: second number, r: result
void sum(Real a, Real b, Real * r){
	int ad = a.denominator;
	int bd = b.denominator;
	if(a.denominator != b.denominator){
		a.numerator = a.numerator * bd;
		a.denominator = a.denominator * bd;
		b.numerator = b.numerator * ad;
		b.denominator = b.denominator * ad;
	}
	r->numerator = a.numerator + b.numerator;
	r->denominator = a.denominator;
}

//a: first number, b: second number, r: result
void subtraction(Real a, Real b, Real * r){
	int ad = a.denominator;
	int bd = b.denominator;
	if(a.denominator != b.denominator){
		a.numerator = a.numerator * bd;
		a.denominator = a.denominator * bd;
		b.numerator = b.numerator * ad;
		b.denominator = b.denominator * ad;
	}
	r->numerator = a.numerator - b.numerator;
	r->denominator = a.denominator;
}

//a: first number, b: second number, r: result
void multiplication(Real a, Real b, Real * r){
	r->numerator = a.numerator * b.numerator;
	r->denominator = a.denominator * b.denominator;
}

//a: first number, b: second number, r: result
void division(Real a, Real b, Real * r){
	r->numerator = a.numerator * b.denominator;
	r->denominator = a.denominator * b.numerator;
}

void simplify(Real * r){
	//if they are the same
	if(r->numerator < 0 && r->denominator < 0){
		r->numerator *= -1;
		r->denominator *= -1;
	}
	if(r->numerator == r->denominator){
		r->numerator = 1;
		r->denominator = 1;
		return;
	}
	//if a%b == 0
	if(r->numerator > r->denominator && (r->numerator % r->denominator) == 0){
		r->numerator = r->numerator/r->denominator;
		r->denominator = 1;
		return;
	}
	//if b%a == 0
	if(r->numerator < r->denominator && (r->denominator % r->numerator) == 0){
		r->denominator = r->denominator / r->numerator;
		r->numerator = 1;
		return;
	}
	
	//if there is (a/i && b/i) == 0
	int i;
	for(i = 1; i < 10; i++){
		while((r->numerator / i) == 0 && (r->denominator / i) == 0){
			r->numerator = r->numerator / i;
			r->denominator = r->denominator / i;
		}
	}
	return;
}


//numerator if now denominator and denominator is now numerator
void flip(Real * r){
	int temp;
	temp = r->numerator;
	r->numerator = r->denominator;
	r->denominator = temp;
}


Real newReal(int num, int den){
	Real n;
	n.numerator = num;
	n.denominator = den;
	n.sum = &sum;
	n.subtraction = &subtraction;
	n.multiplication = &multiplication;
	n.division = &division;
	n.simplify = &simplify;
	n.flip = &flip;
	return n;
}


#endif