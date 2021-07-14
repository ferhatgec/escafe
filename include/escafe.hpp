// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//
// escafe - parser & generator for escape sequences (external whitespace sequence support (\w))
// 
// github.com/ferhatgec/escafe

#ifndef ESCAFE_ESCAFE_HPP
#define ESCAFE_ESCAFE_HPP

#include <iostream>
#include <string>

namespace escafe {

    static std::string run(const std::string& data) noexcept {
        std::string __data;

        bool is_escape = false,
             is_ansi   = false;

        std::string collect;

        for(auto& ch : data) {
            if(!is_ansi && !collect.empty()) {
                if(collect == "033") {
                    __data.append("\033"); 
                } else if(collect == "x1b") {
                    __data.append("\x1b");
                } collect.clear();
            }

            if(is_escape) {
                switch(ch) {
                    case '\'': {
                        __data.push_back('\''); is_escape = false;
                        break;
                    }

                    case '"': {
                        __data.push_back('\"'); is_escape = false;
                        break;
                    }

                    case '?': {
                        __data.push_back('\?'); is_escape = false;
                        break;
                    }

                    case '\\': {
                        __data.push_back('\\'); is_escape = false;
                        break;
                    }

                    case 'a': {
                        __data.push_back('\a'); is_escape = false;
                        break;
                    }

                    case 'b': {
                        if(is_ansi) {
                            collect.push_back('b');

                            is_escape = false;
                            is_ansi = false;

                            break;
                        }

                        __data.push_back('\b'); is_escape = false;
                        break;
                    }

                    case 'f': {
                        __data.push_back('\f'); is_escape = false;
                        break;
                    }

                    case 'n': {
                        __data.push_back('\n'); is_escape = false;
                        break;
                    }

                    case 'r': {
                        __data.push_back('\r'); is_escape = false;
                        break;
                    }

                    case 't': {
                        __data.push_back('\t'); is_escape = false;
                        break;
                    }

                    case 'v': {
                        __data.push_back('\v'); is_escape = false;
                        break;
                    }

                    case 'w': {
                        __data.push_back(' '); is_escape = false;
                        break;
                    }

                    case 'x': {
                        is_ansi = true;  collect.push_back('x');
                        break;
                    }

                    case '0': {
                        if(!is_ansi) { is_ansi = true; }
                        
                        if(is_ansi) {
                            collect.push_back('0');
                        } break;
                    }

                    case '1': {
                        if(is_ansi) {
                            collect.push_back('1');
                        } break;
                    }

                    case '3': {
                        if(collect.back() == '3') { is_escape = is_ansi = false; }

                        //if(is_ansi) {
                            collect.push_back('3');
                        //} 

                        break;
                    }

                    default: {
                        is_escape = false;  
                        break;
                    }
                } continue;
            }

            if(ch == '\\') {
                is_escape = true; continue;
            } __data.push_back(ch);
        }

        return __data;
    }
}

#endif // ESCAFE_ESCAFE_HPP