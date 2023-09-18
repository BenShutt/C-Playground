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

    enum Endpoint {
        case exists
        case upload
    }

    var file: File
    var enpoint: Endpoint

    private var urlComponents: URLComponents {
        var components = URLComponents()
        components.scheme = "http"
        components.host = "localhost"
        components.port = 8000
        components.path = enpoint.path
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
            method: enpoint.method
        )
        request.headers = headers
        request.httpBody = enpoint.hasBody ? try file.data : nil
        return request
    }

    private func request() async throws -> Status {
        try await AF.request(urlRequest())
            .validate()
            .serializingDecodable(Status.self, decoder: JSONDecoder())
            .value
    }

    @discardableResult
    func execute() async throws -> Int {
        let status = try await request().status
        print("Status \(status) for '\(file.url)'")
        return status
    }
}

extension Request.Endpoint {

    var method: HTTPMethod {
        switch self {
        case .exists: return .get
        case .upload: return .post
        }
    }

    var path: String {
        switch self {
        case .exists: return "/api/exists"
        case .upload: return "/api/upload"
        }
    }

    var hasBody: Bool {
        switch self {
        case .exists: return false
        case .upload: return true
        }
    }
}
