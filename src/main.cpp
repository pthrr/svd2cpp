#include "class_builder.h"
#include "xml_parser.h"

#include <cxxopts.hpp>

#include <iostream>

auto main( int argc, char** argv ) -> int
{
    // Create and configure options for the program
    cxxopts::Options options{ "svd2cpp", "Parser from svd files to C++ header" };
    options.add_options()( "i, input", "File with .svd extention to be parsed",
        cxxopts::value< std::string >() )( "h, help", "Print help" );

    std::string input_file;
    auto result{ options.parse( argc, argv ) };

    try {
        if( result.count( "help" ) ) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        if( result.count( "input" ) != 1 ) {
            std::cout << "Missing input file!" << std::endl;
            return 1;
        }

        input_file = result["input"].as< std::string >();
    }
    catch( const std::exception& EX ) {
        std::cout << EX.what() << std::endl;
        return 2;
    }

    //Try to parse the file
    XmlParser xml_parser{ input_file };

    if( auto err = xml_parser.isError() ) {
        std::cout << "There was an error while reading " << input_file << ":" << std::endl
                  << *err << std::endl;
        return 3;
    }

    xml_parser.parseXml();
    ClassBuilder classBuilder( result, xml_parser.getDeviceInfo(), xml_parser.getPeripherals() );
    classBuilder.setupBuilders();
    classBuilder.build();

    std::cout << classBuilder.getStream().str() << std::endl;
}
