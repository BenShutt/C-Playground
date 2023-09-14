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

    var imageFile: ImageFile

    private var urlComponents: URLComponents {
        var components = URLComponents()
        components.scheme = "http"
        components.host = "localhost"
        components.port = 8000
        components.path = "/api/hello"
        components.queryItems = nil
        return components
    }

    private var headers: HTTPHeaders {
        var headers = HTTPHeaders.default
        headers.add(name: "Accept", value: "application/json")
        headers.add(name: "Content-Type", value: "application/octet-stream")
        return headers
    }

    private func urlRequest() throws -> URLRequest {
        var request = try URLRequest(
            url: urlComponents,
            method: .get
        )
        request.headers = headers
        // request.httpBody = try imageFile.data
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
        print("\(prefix) - '\(imageFile.url)'")
    }
}
