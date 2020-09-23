# ADT-Polynomial

### Summer 2019 Data Structures and Algorithms, UW Bothell 

##### Purpose

This programming assignment exercises dynamic memory allocation, pointer operations, and copy constructor design through designing a doubly-linked circular list with a dummy header. Using such a list, you will implement an ADT polynomial.

 

##### ADT Polynomial

The specification of our ADT polynomial has the following public functions:

 

##### degree( )

Returns the degree of a polynomial. For example, when p1 = 4x5 + 7x3 - x2 + 9, p1.degree( ) is 5.

##### coefficient( power )

Returns the coefficient of the xpower term. For example, when p1 = 4x5 + 7x3 - x2 + 9, p1.coefficient(3) is 7

##### changeCoefficient( newCoefficient, power )

Replaces the coefficient of the xpower term with newCoeffcient. For instance, p1.changeCoefficient(-3, 7) produces the polynomial p1 = -3x7 + 4x5 + 7x3 - x2 + 9

##### arithmetic operations + and -

Add two polynomials or subtract the 2nd polynomial from the 1st one. For instance, assuming p1 = 4x5 + 7x3 - x2 + 9 and p2 = 6x4 + 3x2 + 2x, then the answer of p1 + p2 must be 4x5 + 6x4 + 7x3 + 2x2 + 2x + 9. Note that you do not have to implement operations * and /.

##### boolean comparison operators == and !=

Returns true in == when corresponding terms of two given polynomial matches each other, otherwise false. Needless to say about !=. Note that >, >=, <, and <= are meaningless.

##### assignment operators =, +=, -=

Note that you need to take care of self-assignment when implementing =.

##### output operator <<

The output must have the form of cnx^n + cn-1x^(n-1) + ... + c1x + c0 For example, p1 = -3x7 + 4x5 + 7x3 - x2 + 9 should be printed out in the form of        -3x^7 + 4x^5 + 7x^3 - x^2 + 9. Note that you don't have to implement operator>>.

 

##### A Sparse Polynomial Implementation Using A List

The ADT polynomial can be implemented using a doubly-linked circular list that stores only the terms with nonzero coefficients. For example, you can represent the polynomial p1 = -3x7 + 4x3 + 9 as follows.

To implement the ADT polynomial with this list, you must add the following members in your polynomial class.

##### default constructor

When construct a Polynomial object without parameter, you should initialize the size as zero, and should construct a dummy header. Note that your polynomial is doubly-linked circular list.

##### copy constructor

Takes care of a deep copy of the original link representation.

##### destructor

Takes care of de-allocating all link nodes to the system.

##### struct Term

This structure must be defined as a class private struct and include double coeffocient and int power as well as prev and next pointers, each pointing to a previous and a next Term node

insert( pos, newCoefficient, power )

This private member function inserts a new Term node with newCoefficient and power just before the existing Term pointed by the pos pointer. The insert function will be used bychangeCoefficient to insert a new term.

##### remove( pos )

This private member function deletes the existing Term node pointed by the pos pointer. The remove function will be used by changeCoefficient to delete an existing term when its coefficient is changed in 0. In addition, it will be used by a destructor and the operator= to de-allocates all Term nodes.
