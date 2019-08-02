
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
#include <sax/iostream.hpp>
#include <string>
#include <type_traits>
#include <vector>

namespace fs = std::filesystem;

#include <SFML/Extensions.hpp>
#include <SFML/Graphics.hpp>
#include <sfc/svg.hpp>

/*
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/replace.hpp>

[[maybe_unused]] std::string& wildcard_to_regex ( std::string& wild_card_ ) noexcept {
    // http://stackoverflow.com/questions/3300419/file-name-matching-with-wildcard
    boost::replace_all ( wild_card_, "\\", "\\\\" );
    boost::replace_all ( wild_card_, ".", "\\." );
    boost::replace_all ( wild_card_, "+", "\\+" );
    boost::replace_all ( wild_card_, "{", "\\{" );
    boost::replace_all ( wild_card_, "}", "\\}" );
    boost::replace_all ( wild_card_, "[", "\\[" );
    boost::replace_all ( wild_card_, "]", "\\]" );
    boost::replace_all ( wild_card_, "(", "\\(" );
    boost::replace_all ( wild_card_, ")", "\\)" );
    boost::replace_all ( wild_card_, "^", "\\^" );
    boost::replace_all ( wild_card_, "$", "\\$" );
    boost::replace_all ( wild_card_, "#", "\\#" );
    boost::replace_all ( wild_card_, "/", "\\/" );
    boost::replace_all ( wild_card_, " ", "\\ " );
    boost::replace_all ( wild_card_, "	", "\\	" );
    boost::replace_all ( wild_card_, "?", "." );
    boost::replace_all ( wild_card_, "*", ".*" );
    return wild_card_;
}

[[nodiscard]] bool is_wildcard ( std::string const & s_ ) noexcept {
    return boost::find_first ( s_, "*" ) || boost::find_first ( s_, "?" );
}
*/

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
