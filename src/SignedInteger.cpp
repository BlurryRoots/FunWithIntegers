#include <exception>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>

#include "SignedInteger.hpp"

long long int SignedInteger::Pow2( long long int n ) const
{
    return ( (long long int)1 << n );
}

void SignedInteger::Cleanup()
{
    delete [] this->bits;
}

SignedInteger::SignedInteger( std::size_t someBitSize )
    : bitSize( someBitSize ),
      bits( new bool[someBitSize] )

{
    if( someBitSize > (sizeof( long long int ) * 8) )
    {
        this->Cleanup();

        std::stringstream ss;
        ss << "Max integer size is " 
           << sizeof( long long int )*8 << "bit!";

        throw new std::range_error( 
            ss.str().c_str() 
        );
    }
    else if( someBitSize == 0 )
    {
        this->Cleanup();

        std::stringstream ss;
        ss << "BitSize == 0, seriously?!";
        throw new std::range_error( 
            ss.str().c_str() 
        );                
    }

    for( std::size_t i = 0; i < this->bitSize; ++i )
    {
        this->bits[i] = true;
    }            

    this->maxNegativeValue = 
        -1 * this->Pow2( this->bitSize - 1 );
    this->maxPositiveValue = 
        -1 * this->maxNegativeValue - 1;
}

SignedInteger::~SignedInteger()
{
    this->Cleanup();
}

void SignedInteger::SetBit( std::size_t someN, bool someValue )
{
    if( someN >= this->bitSize )
    {
        throw new std::range_error( 
            "Given position is out of memory range!" 
        );
    }

    this->bits[someN] = someValue;
}

void SignedInteger::SetValue( long long int someValue )
{
    if( someValue > this->maxPositiveValue )
    {
        this->Cleanup();
        throw new std::range_error( "Value bigger than positive maximum!" );
    }
    else if( someValue < this->maxNegativeValue )
    {
        this->Cleanup();
        throw new std::range_error( "Value smaller than negative maximum!" );
    }

    for( std::size_t i = 0; i < this->bitSize; ++i )
    {
        this->bits[i] = false;
    }

    //if someValue == 0 do nothing
    if( someValue == 0 ) return;

    bool isNegative = (someValue < 0);         
    std::size_t exponent = this->bitSize - 1;
    long long int exponentValue = 0;

    someValue = 
        (isNegative ? 
            ((long long int)-1) * someValue 
            : someValue);

    while( someValue > 0 && exponent >= 0 )
    {
        exponentValue = this->Pow2( exponent );

        if( someValue >= exponentValue )
        {
            this->bits[exponent] = true;
            someValue -= exponentValue;
        }

        --exponent;
    }

    if( isNegative )
    {       
        bool carry = true;
        
        for( std::size_t i = 0; i < this->bitSize; ++i )
        {
            //invert
            this->bits[i] = ! this->bits[i];

            //and add 1
            bool sum = this->bits[i] ^ carry;
            carry = this->bits[i] && carry;

            this->bits[i] = sum;
        }
    }
}

const SignedInteger& SignedInteger::operator=( const SignedInteger& someOther )
{
    if( this->GetBitSize() != someOther.GetBitSize() )
    {
        std::stringstream ss;
        ss << "Could not assign integer of bit size " << someOther.GetBitSize() << " to " << this->GetBitSize();
        throw new std::range_error( ss.str() );
    }

    this->SetValue( someOther.GetValue() );

    return (*this);
}

const SignedInteger& SignedInteger::operator=( const long long int someValue )
{
    this->SetValue( someValue );

    return (*this);
}

const SignedInteger& SignedInteger::operator+( const long long int someValue )
{
    this->SetValue( this->GetValue() + someValue );

    return (*this);
}

const SignedInteger& SignedInteger::operator-( const long long int someValue )
{
    this->SetValue( this->GetValue() - someValue );

    return (*this);
}

const SignedInteger& SignedInteger::operator*( const long long int someValue )
{
    this->SetValue( this->GetValue() * someValue );

    return (*this);
}

const SignedInteger& SignedInteger::operator/( const long long int someValue )
{
    this->SetValue( this->GetValue() / someValue );

    return (*this);
}

std::size_t SignedInteger::GetBitSize() const
{
    return this->bitSize;
}

long long int SignedInteger::GetMaxPositive() const
{
    return this->maxPositiveValue;
}

long long int SignedInteger::GetMaxNegative() const
{
    return this->maxNegativeValue;
}

long long int SignedInteger::GetValue() const
{
    long long int value = 0;

    if( this->bits[this->bitSize-1] )
    {
        bool carry = true;
        bool inverted = false;
        bool withCarry = false;

        //invert, add 1, and accumulate value
        for( std::size_t i = 0; i < this->bitSize; ++i )
        {
            inverted = ! this->bits[i];
            withCarry =  inverted != carry;
            carry = inverted && carry;

            value = 
                ( withCarry ? 
                    value + this->Pow2( (long long int)i ) 
                    : value );
        }
        
        value = -1 * value;
    }
    else
    {
        for( std::size_t i = 0; i < this->bitSize; ++i )
        {
            value = 
                ( this->bits[i] ? 
                    value + this->Pow2( (long long int)i ) 
                    : value );
        }
    }

    return value;
}       

std::string SignedInteger::ToString( bool inBits ) const
{
    std::stringstream ss;
    if( inBits )
    {
        for( std::size_t i = 0; i < this->bitSize; ++i )
        {
            ss << this->bits[(this->bitSize - 1) - i];
        }
    }
    else
    {
        ss << this->GetValue();
    }

    return ss.str();
}