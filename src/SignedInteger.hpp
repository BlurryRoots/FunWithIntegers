#ifndef _SIGNEDINTEGER_
#define _SIGNEDINTEGER_

class SignedInteger
{
    private:
        std::size_t bitSize;

        bool* bits;

        long long int maxPositiveValue;
        long long int maxNegativeValue;

        long long int Pow2( long long int n ) const;

        void Cleanup();


    public:
        SignedInteger( std::size_t someBitSize );

        ~SignedInteger();

        void SetBit( std::size_t someN, bool someValue );

        void SetValue( long long int someValue );

        const SignedInteger& operator=( const SignedInteger& someOther );

        const SignedInteger& operator=( const long long int someValue );

        const SignedInteger& operator+( const long long int someValue );

        const SignedInteger& operator-( const long long int someValue );

        const SignedInteger& operator*( const long long int someValue );

        const SignedInteger& operator/( const long long int someValue );

        std::size_t GetBitSize() const;

        long long int GetMaxPositive() const;

        long long int GetMaxNegative() const;

        long long int GetValue() const; 

        std::string ToString( bool inBits = false ) const;
};

#endif