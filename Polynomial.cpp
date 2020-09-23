//
// Created by marcela gomez on 2019-06-28.
// CSS 343 Summer 2019 Professor Wooyoung Kim
// Program 1: Polynomial Class
// Last modified on 6/30/2019 at 6:31pm
//

#include <iostream>
#include "polynomial.h"

using namespace std;


//------------------------------------------------------------------
// Purpose - Implement the internal representation of a polynomial
// as a doubly linked circular list.
//-----------------------------------------------------------------



// ----------------------Overload operator<<--------------------
// Description: Prints the polynomial with 1 or more terms and
//              an error message if there are 0 terms
// Pre-Condition: user prints uses the operator
// Post Condition: operator<< prints out the polynomial format
// -------------------------------------------------------------
ostream& operator<<( ostream &output, const Polynomial& p )
{
    ;
    //empty polynomial
    if(p.head == nullptr)
    {
        output << "no terms in the polynomial" << endl;
    }

    //only one term in polynomial
    if(p.head->next == p.head)
    {
        output << p.head->next->coeff << "x^" << p.head->next->power << endl;

        output << "only one term in polynomial" << endl;
    }

    // more than one term in the polynomial
    else {
        output << p.head->next->coeff << "x^" << p.head->next->power;     //print 1st term
        p.head->next = p.head->next->next;                  //move to next term
        while (p.head->next != p.head) {
            if (p.head->next->coeff > 0)                   //positive term
            {
                output << " + " << p.head->next->coeff << "x^" << p.head->next->power;
            } else if (p.head->next->coeff == 0)             //zero coeff
            {
                output << " + " << "x^" << p.head->next->power;
            } else                            // negative coeff
            {
                output << " " << p.head->next->coeff << "x^" << p.head->next->power;
            }
            p.head->next = p.head->next->next;
            output << "more than one term in the polynomial" << endl;
        }
        output << endl;   // terminate print
    }
    return output;
}




// ----------------------Default Constructor--------------------
// When construct a Polynomial object without parameter,
// Pre Condition: initialize the size as zero,
// and should construct a dummy header.
// Post Condition: polynomial with dummy header
// -------------------------------------------------------------
Polynomial::Polynomial( ){

    head = new Term;

    head->coeff=0;
    head->power = 0;
    head->next = head;
    head->prev = head;
    size = 0;

    cout << "debug: default constructor" << endl;
}


// ----------------------Constructor----------------------------
// copy constructor set up to copy polynomial terms int newly
// allocated memory as needed for a deep copy constructor
// pre conditions
// post conditions
// -------------------------------------------------------------
Polynomial::Polynomial( const Polynomial& p ) {

    cout << " into copy constructor" << endl;

    // in case list is empty
    if (p.head == nullptr)
    {
        head = nullptr;
        head->prev = nullptr;
        size = 0;
        return;
    }

    Term *temp = p.head->next;  // assigns temp to 1st node

    head = new Term;
    head->coeff = temp->coeff;
    head->power = temp->power;
    head->next = nullptr;
    size++;

    curr = head;

    temp = temp->next;
    while(temp != head)
    {
        curr->next = new Term;
        curr = curr->next;
        curr->coeff = temp->coeff;
        curr->power = temp->power;
        curr->next = nullptr;
        temp = temp->next;
        size++;
    }
}



// ----------------------De-constructor----------------------------
// deletes all nodes and their pointers
// pre conditions
// post conditions
// -------------------------------------------------------------
Polynomial::~Polynomial( ){

    Term *temp;
    temp = head->next;
    while(temp != head)
    {
        Term *next = temp->next;
        delete temp;
        temp = next;
    }
    size = 0;
}



// ----------------------degree---------------------------------
// Returns the degree of a polynomial.
// Pre-condition: the terms are in descending order of powers.
// Post-condition it returns power of 1st term after dummy header.
// p1 = 4x5 + 7x3 - x2 + 9, p1.degree( ) is 5.
// -------------------------------------------------------------
int Polynomial::degree( ) const
{
    cout << " degree" << endl;
    //check for null
    return this->head->next->power;
}



// ----------------------coefficient----------------------------
// Returns the coefficient of the xpower term. For example,
// when p1 = 4x5 + 7x3 - x2 + 9, p1.coefficient(3) is 7
// pre conditions
// post conditions
// -------------------------------------------------------------
double Polynomial::coefficient( const int power ) const {

    cout << " coefficient" << endl;
    Term* curr = this->head;

    while (curr != head) {
        if (power != curr->power) {
            curr = curr->next;
        }
        else
        {
            return curr->coeff;
        }
    }
    return 0;
}



// ----------------------changeCoefficient----------------------------
//Replaces the coefficient of the xpower term with newCoeffcient.
// For instance, p1.changeCoefficient(-3, 7) produces the polynomial
// p1 = -3x7 + 4x5 + 7x3 - x2 + 9
// pre conditions
// post conditions
// ------------------------------------------------------------------
bool Polynomial::changeCoefficient( const double newCoefficient, const int power ) {


    Term *pos;
    if (newCoefficient != 0) {
        insert(pos, newCoefficient, power);
        cout << "new term added to polynomial" << endl;
    }

    else
    {
        pos = new Term;
        pos->coeff = newCoefficient;
        pos->power = power;
        remove(pos);
    }
    return true; //check remove and insert returns

}


// Arithmetic operators

// ----------------------operator+-----------------------------
//
// pre conditions
// post conditions
// -------------------------------------------------------------
Polynomial Polynomial::operator+( const Polynomial& p ) {

    Term* pos1 = p.head;
    Term* pos2 = this->head;

    while (pos1->next != p.head || pos2->next != this->head) {

        //if this.power is bigger move pointer forward
        if (pos2->power > pos1->power)
        {
            pos2 = pos2->next;
        }

        //save power of larger power and store the larger as is
        else if(pos2->power < pos1->power)
        {
           insert(pos1,pos1->coeff,pos1->power );
           pos1 = pos1->next;
        }

        else
        {
            // if power of both terms is the same
            double newCoefficient = pos2->coeff + pos1->coeff;
            pos2->coeff = newCoefficient;
            pos1 = pos1->next;
            pos2 = pos2->next;

        }
    }

    while(pos1->next != p.head)
    {
            insert(pos1, pos1->coeff, pos1->power);
    }
    return *this;
}


// ----------------------(operator-)------------------------------
//
// pre conditions
// post conditions
// -------------------------------------------------------------
Polynomial Polynomial::operator-( const Polynomial& p )
{

    Term* pos1 = p.head;
    Term* pos2 = this->head;

    while (pos1->next != p.head || pos2->next != this->head) {

        //if this.power is bigger move pointer forward
        if (pos2->power > pos1->power)
        {
            pos2 = pos2->next;
        }

            //save power of larger power and store the larger as is
        else if(pos2->power < pos1->power)
        {
            insert(pos1,pos1->coeff,pos1->power);
            pos1 = pos1->next;
        }

        else
        {
            // if power of both terms is the same
            double newCoefficient = pos2->coeff - pos1->coeff;
            pos2->coeff = newCoefficient;
            pos1 = pos1->next;
            pos2 = pos2->next;

        }
    }

    while(pos1->next != p.head)
    {
        insert(pos1, pos1->coeff, pos1->power);
    }
    return *this;
}


// ----------------------operator!=-----------------------------
//
// pre conditions
// post conditions
// -------------------------------------------------------------
bool Polynomial::operator!=( const Polynomial& p ) const
{
    return !(*this == p);
}


bool Polynomial::operator==( const Polynomial& p ) const{

    if(this->size != p.size)
    {
        return false;
    }

    Term* pos1 = p.head;
    Term* pos2 = this->head;

    while (pos1->next != p.head || pos2->next != this->head) {

            if (pos2->power != pos1->power)
            {
                return false;
            }
            if (pos2->coeff != pos1->coeff)
            {
                return false;
            }
    }
    return false;
}


// Assignment operators
// ----------------------operator=-----------------------------
//
// pre conditions
// post conditions
// -------------------------------------------------------------
Polynomial& Polynomial::operator=( const Polynomial& p ){

    // in case list is empty
    if (head == nullptr)
    {
        head = nullptr;
        head->prev = nullptr;
        size = 0;
        //return;
    }

    Term *temp = p.head->next;  // assigns temp to 1st node

    head = new Term;
    head->coeff = temp->coeff;
    head->power = temp->power;
    head->next = nullptr;
    size++;

    curr = head;

    temp = temp->next;
    while(temp != head)
    {
        curr->next = new Term;
        curr = curr->next;
        curr->coeff = temp->coeff;
        curr->power = temp->power;
        curr->next = nullptr;
        temp = temp->next;
        size++;
    }
    return *this;
}


// ---------------------operator+=-----------------------------
//
// pre conditions
// post conditions
// -------------------------------------------------------------
Polynomial& Polynomial::operator+=( const Polynomial& p )
{
    *this = * this + p;
    return *this;
}

// ---------------------operator-=-----------------------------
//
// pre conditions
// post conditions
// -------------------------------------------------------------
Polynomial& Polynomial::operator-=( const Polynomial& p )
{
    *this = * this - p;
    return *this;
}



// ----------------------insert---------------------------------
// Description: This private member function inserts a new
// Term node with newCoefficient and power just before the existing
// Term pointed by the pos pointer. Insert func called above.
// pre -condition: changeCoeff is called
// post conditions: new term inserted
// -------------------------------------------------------------
bool Polynomial::insert( Term* pos, const double newCoefficient, const int power ){


    //create new node from parameters

    struct Term *newTerm;
    newTerm = new(struct Term);
    newTerm->coeff = newCoefficient;
    newTerm->power = power;
    newTerm->next = nullptr;
    newTerm->prev = nullptr;


    //if polynomial is empty
    if (this->head->next == head) {
        cout << "polynomial is empty adding as first term" << endl;
        this->head->next = newTerm;
        newTerm->next = this->head;
        newTerm->prev = this->head;
        this->head->next = newTerm;
        this->head->prev = newTerm;
    }

    else
    {
        //Term* pos2 = this->head;
        pos = this->head->next;
        while (pos != this->head) {

            //if power term is => add newTerm in front
            if (power >= pos->power && pos->prev == head) {
                newTerm->next = pos;
                newTerm->prev = head;
                pos->prev = newTerm;
                pos->prev->next = newTerm;

            }

            else if (power >= pos->power && pos->prev != head) {

                //pos = pos->next;

                newTerm->next = pos;
                newTerm->prev = pos->prev;
                pos->prev->next = newTerm;
                pos->prev = newTerm;
            }

            else {

                if (pos->next == head){
                    //cout << "power of term is smaller add after" << endl;

                    newTerm->next = pos->next;
                    newTerm->prev = pos;

                    pos->next = newTerm;
                    pos->prev->prev = newTerm;
                    return true;



                }
            }
            pos = pos->next;
        }

    }
    size++;
    return true;
}

// ----------------------remove----------------------------
//This private member function deletes the existing Term node pointed
//by the pos pointer. The remove function will be used by changeCoefficient
//to delete an existing term when its coefficient is changed in 0. In
//addition, it will be used by a destructor and the operator= to
// de-allocates all Term nodes.
// -------------------------------------------------------------
bool Polynomial::remove(Term* pos) {


    Term* pos1 = this->head;
    Term* temp = head;

    while (pos1->next != head)
    {
        if(pos1->power == pos->power)
        {
            pos1->next->prev = temp;
            temp->next = pos1->next;
            delete pos;
            return true;
        }
        temp = pos1;
        pos1= pos1->next;
    }
    return false;
    //term is the first one after the sentinel
    /*if (this->head->next == pos)
    {
        this->head->next = pos->next;
        pos->next->prev = pos->prev;
        pos->next = nullptr;
        pos->prev = nullptr;
        //delete pos;
    }

    //term is in the middle
    else if(pos != this->head->next && pos != this->head->prev)
    {
        pos->prev = pos->prev->prev;
        pos->prev->prev = pos->next->next;
        pos->next = nullptr;
        pos->prev = nullptr;
        //delete pos;
    }
    else
    {
        this->head->prev = pos->prev;
        pos->prev->next = this->head;
        pos->next = nullptr;
        pos->prev = nullptr;
        //delete pos;
    }*/
    return true;
}