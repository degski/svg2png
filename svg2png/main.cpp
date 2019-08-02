
// MIT License
//
// Copyright (c) 2019 degski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
