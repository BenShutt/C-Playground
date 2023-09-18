//
//  Request.swift
//  Client
//
//  Created by Ben Shutt on 14/09/2023.
//  Copyright © 2023 Ben Shutt. All rights reserved.
//

import Foundation
import Alamofire

struct Request {

    var file: File

    private var urlComponents: URLComponents {
        var components = URLComponents()
        components.scheme = "http"
        components.host = "localhost"
        components.port = 8000
        components.path = "/api/upload"
        components.queryItems = nil
        return components
    }

    private var headers: HTTPHeaders {
        var headers = HTTPHeaders.default
        headers.add(name: "Accept", value: "application/json")
        headers.add(name: "Content-Type", value: "application/octet-stream")
        headers.add(name: "X-File-Name", value: file.url.lastPathComponent)
        return headers
    }

    private func urlRequest() throws -> URLRequest {
        var request = try URLRequest(
            url: urlComponents,
            method: .post
        )
        request.headers = headers
        request.httpBody = try file.data
        return request
    }

    func request() async throws -> Status {
        try await AF.request(urlRequest())
            .validate()
            .serializingDecodable(Status.self, decoder: JSONDecoder())
            .value
    }

    func execute() async throws {
        let status = try await request()
        let prefix = status.status == 0 ? "Success" : "Failure"
        print("\(prefix) for '\(file.url)'")
    }
}
