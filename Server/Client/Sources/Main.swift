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

    var directoryURL: URL {
        URL(filePath: (directory as NSString).expandingTildeInPath)
    }

    mutating func run() async throws {
        let imageFiles = try ImageDirectory(url: directoryURL).validate()
        for imageFile in imageFiles {
            try await Request(imageFile: imageFile).execute()
        }
    }
}
