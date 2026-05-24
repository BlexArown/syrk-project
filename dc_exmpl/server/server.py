#!/usr/bin/env python3

import http.server
import socketserver

PORT = 1234

handler = http.server.SimpleHTTPRequestHandler

with socketserver.TCPServer(("", PORT), handler) as httpd:
    print(f"Server started on port {PORT}")
    httpd.serve_forever()
