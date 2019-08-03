
// GPL 3.0 (see LICENSE.md)
//
// Copyright (c) 2019 degski

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <array>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include <random>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

namespace fs = std::filesystem;

#include <SFML/Extensions.hpp>
#include <SFML/Graphics.hpp>
#include <sfc/svg.hpp>

void replace_all ( std::string & input_, std::string const & from_, std::string const & to_ ) noexcept {
    std::size_t pos = 0u;
    while ( std::string::npos != ( pos = input_.find ( from_, pos ) ) ) {
        input_.replace ( pos, from_.length ( ), to_ );
        pos += to_.length ( );
    }
}

[[maybe_unused]] std::string& wildcard_to_regex ( std::string & wild_card_ ) noexcept {
    // http://stackoverflow.com/questions/3300419/file-name-matching-with-wildcard
    replace_all ( wild_card_, "\\", "\\\\" );
    replace_all ( wild_card_, ".", "\\." );
    replace_all ( wild_card_, "+", "\\+" );
    replace_all ( wild_card_, "{", "\\{" );
    replace_all ( wild_card_, "}", "\\}" );
    replace_all ( wild_card_, "[", "\\[" );
    replace_all ( wild_card_, "]", "\\]" );
    replace_all ( wild_card_, "(", "\\(" );
    replace_all ( wild_card_, ")", "\\)" );
    replace_all ( wild_card_, "^", "\\^" );
    replace_all ( wild_card_, "$", "\\$" );
    replace_all ( wild_card_, "#", "\\#" );
    replace_all ( wild_card_, "/", "\\/" );
    replace_all ( wild_card_, " ", "\\ " );
    replace_all ( wild_card_, "	", "\\	" );
    replace_all ( wild_card_, "?", "." );
    replace_all ( wild_card_, "*", ".*" );
    return wild_card_;
}

[[nodiscard]] bool is_wildcard ( std::string const & s_ ) noexcept {
    return std::string::npos != s_.find ( "*" ) or std::string::npos != s_.find ( "?" );
}

int main ( int argc_, char ** argv_ ) {

    float scale = 1.0;
    if ( 2 == argc_ )
        scale = std::atof ( argv_[ 1 ] );
    for ( auto & it : fs::directory_iterator ( fs::current_path ( ) ) ) {
        if ( ".svg" == it.path ( ).extension ( ) ) {
            // Create image
            sfc::SVGImage img;
            // Don't show debug lines
            img.setMode ( sfc::DrawMode::NORMAL );
            fs::path path = it.path ( );
            // Load SVG image from file
            img.loadFromFile ( path.string ( ) );
            path.replace_extension ( ".png" );
            // Rasterize image & save it to file
            img.rasterize ( scale ).saveToFile ( path.string ( ) );
        }
    }
    return EXIT_SUCCESS;
}
