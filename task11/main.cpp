#include "CompPrimes.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Count, valTest) {
    std::cout << prime<1>::value << std::endl; 
    std::cout << prime<2>::value << std::endl; 
    std::cout << prime<3>::value << std::endl; 
    std::cout << prime<4>::value << std::endl;
    std::cout << prime<5>::value << std::endl;
    std::cout << prime<100>::value << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
