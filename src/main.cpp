#include <exception>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdint>

#include "SignedInteger.hpp"

int main()
{
    try
    {
        SignedInteger ui4( 4 );
        SignedInteger ui8( 8 );

        ui4 = -8;
        ui4 = ui4 + 2;

        ui8 = 16;
        ui8 = ui4;

        std::cout
            << "Unsigned integer with: " << ui4.GetBitSize() << std::endl
            << "Bit representation: " << ui4.ToString( true ) << std::endl
            << "Value: " << ui4.ToString() << std::endl
            << "Max +: " << ui4.GetMaxPositive() << std::endl
            << "Max -: " << ui4.GetMaxNegative() << std::endl;
    }
    catch( std::exception* ex )
    {
        std::cout << ex->what();
    }

	return 0;
}
