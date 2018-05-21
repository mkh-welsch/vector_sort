// this programm builds the header only file.
// call it from the root.
// c++ ./dev/build_vector_sort.cpp -o ./dev/build_vector_sort -std=c++14
// ./dev/build_vector_sort
// generates vector_sort.hpp


#include <iostream>
#include <string>
#include <fstream>

#include "avx_static_sort_generator.cpp"


bool attach( const char* path_to_srce_file, std::ostream& dest_file  )
{
    std::ifstream srce_file( path_to_srce_file ) ;
    if( srce_file )
    {
        dest_file << srce_file.rdbuf() << std::endl;
        return true ;
    }
    else
    {
        std::cerr << "error: could not open " << path_to_srce_file << '\n' ;
        return false ;
    }
}

int main(){

unsigned long switchPoint = 32;


std::ofstream combined_file( "vector_sort.hpp" ) ;

attach("dev/header.cpp",  combined_file );
attach("dev/avx2_cas.cpp",  combined_file );

combined_file << " namespace vector_sort{ namespace internal{ unsigned long switchPoint = "<< switchPoint << "; } } " << std::endl << std::endl;

print_avx_static_sort(switchPoint); // generates the "avx_static_sort.cpp" file in the directory

attach("dev/avx_static_sort.cpp",  combined_file );
attach("dev/avx_dualpivot_sort.cpp",  combined_file );
attach("dev/footer.cpp",  combined_file );


return 0;
}