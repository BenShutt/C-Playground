//
//  Main.swift
//  Client
//
//  Created by Ben Shutt on 13/09/2023.
//  Copyright © 2023 Ben Shutt. All rights reserved.
//

import Foundation
import ArgumentParser

@main
struct Main: AsyncParsableCommand {

    static let configuration = CommandConfiguration(
        abstract: "A Swift command-line executable for interfacing with the server."
    )

    @Option(help: "URL to the directory of images to upload to the server")
    var directory: String

    /// Map `directory` to `URL`
    var directoryURL: URL {
        URL(filePath: directory)
    }

    mutating func run() async throws {
        print("Hello, World - \(directoryURL)")
    }
}
