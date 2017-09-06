//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"
#include <vector>

namespace http {
    namespace server {

        request_handler::request_handler() {}

        void request_handler::handle_request(const request& req, reply& rep)
        {
            // Fill out the reply to be sent to the client.
            rep.status = reply::ok;
            /*
             *struct request
        {
            std::string method;
            std::string uri;
            int http_version_major;
            int http_version_minor;
            std::vector<header> headers;
        };
             */
            rep.content.append(req.method);
            rep.content.append(" ");
            rep.content.append(req.uri);
            rep.content.append(" ");
            rep.content.append("HTTP");
            rep.content.append(" ");
            rep.content.append(std::to_string(req.http_version_major));
            rep.content.append("/");
            rep.content.append(std::to_string(req.http_version_minor));
            rep.content.append("\n");
            for (int i = 0; i < req.headers.size(); i++)
            {
                rep.content.append(req.headers[i].name);
                rep.content.append(": ");
                rep.content.append(req.headers[i].value);
                rep.content.append("\n");
            }

            // rep.headers.resize(2);
            // rep.headers[0].name = "Content-Length";
            // rep.headers[0].value = std::to_string(rep.content.size());
            // rep.headers[1].name = "Content-Type";
            // rep.headers[1].value = "text/html";
        }

        bool request_handler::url_decode(const std::string& in, std::string& out)
        {
            out.clear();
            out.reserve(in.size());
            for (std::size_t i = 0; i < in.size(); ++i)
            {
                if (in[i] == '%')
                {
                    if (i + 3 <= in.size())
                    {
                        int value = 0;
                        std::istringstream is(in.substr(i + 1, 2));
                        if (is >> std::hex >> value)
                        {
                            out += static_cast<char>(value);
                            i += 2;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (in[i] == '+')
                {
                    out += ' ';
                }
                else
                {
                    out += in[i];
                }
            }
            return true;
        }

    } // namespace server
} // namespace http