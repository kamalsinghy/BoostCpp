#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

int main()
{
    shared_memory_object shdmem{open_or_create, "Boost", read_write};
    shdmem.truncate(1024);
    std::cout << shdmem.get_name() << std::endl;
    offset_t size;
    if (shdmem.get_size(size)) {
        std::cout << size << std::endl;
    }

    mapped_region region{shdmem, read_write};
    std::cout << std::hex << region.get_address() << std::endl;
    std::cout << std::dec << region.get_size() << std::endl;

    mapped_region region2{shdmem, read_only};
    std::cout << std::hex << region2.get_address() << std::endl;
    std::cout << std::dec << region2.get_size() << std::endl;

    auto *i1 = static_cast<int*>(region.get_address());
    *i1 = 99;
    auto *i2 = static_cast<int*>(region2.get_address());
    std::cout << *i2 << std::endl;

    bool removed = shared_memory_object::remove("oost");
    std::cout << std::boolalpha << removed << std::endl;
}
