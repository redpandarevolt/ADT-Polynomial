// A Polynomial class                                  // Munehiro Fukuda
#ifndef POLYNOMIAL_H                                   // CSS342
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;

class Polynomial {

    // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
    friend ostream& operator<<( ostream &output, const Polynomial& p );


    // Constructor: the default is a 0-degree polynomial with 0.0 coefficient
   public:

      // Default constructor, constructor and deconstructor
      Polynomial( );
      Polynomial( const Polynomial& p );
      ~Polynomial( );


      //Member functions
      //degree: returns the degree of a polynomial
      //coefficient: returns the coefficient of the x^power term.
      //changeCoefficient: replaces the coefficient of the x^power term
      int degree( ) const;
      double coefficient( const int power ) const;
      bool changeCoefficient( const double newCoefficient, const int power );

      double getCoeff();
      int getPower();


      // Arithmetic operators
      Polynomial operator+( const Polynomial& p );
      Polynomial operator-( const Polynomial& p );


      // Boolean comparison operators
      bool operator==( const Polynomial& p ) const;
      bool operator!=( const Polynomial& p ) const;


      // Assignment operators
      Polynomial& operator=( const Polynomial& p );
      Polynomial& operator+=( const Polynomial& p );
      Polynomial& operator-=( const Polynomial& p );

  private:

      struct Term {       // a term on the sparce polynomial
          double coeff;   // the coefficient of each term
          int power;      // the degree of each term
          Term *prev;     // a pointer to the previous higher term
          Term *next;     // a pointer to the next lower term
      };

      int size;         // # terms in the sparce polynomial
      Term *head;       // a pointer to the doubly-linked circular list of
      Term *curr;

      bool insert( Term* pos, const double newCoefficient, const int power );
      bool remove( Term* pos );
      //void print( const string& msg ) const;
};

#endif
