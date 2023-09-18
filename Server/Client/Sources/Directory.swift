//
//  Directory.swift
//  Client
//
//  Created by Ben Shutt on 13/09/2023.
//  Copyright © 2023 Ben Shutt. All rights reserved.
//

import Foundation

/// Encapsulate the logic of the media directory
struct Directory {

    /// Map a `URL` to an optional type
    typealias Operation<Target> = (URL) -> Target?

    /// URL of the directory
    var url: URL

    /// Enumerate the files in `url`
    /// - Parameter operation: Operation to execute on each URL
    /// - Returns: Outputted files
    func forEach<Target>(operation: Operation<Target>) throws -> [Target] {
        try FileManager.default.contentsOfDirectory(
            at: url,
            includingPropertiesForKeys: nil,
            options: [.skipsHiddenFiles]
        ).compactMap { url in
            operation(url)
        }
    }

    /// Get the media files printing when a file is not a valid media
    /// - Returns: Valid media files
    func validate() throws -> [File] {
        let files = try forEach { url in
            let file = File(url: url)
            if file == nil {
                print("Unsupported media URL: '\(url)'")
            }
            return file
        }

        if files.isEmpty {
            print("No media found in: '\(url)'")
        } else {
            print("\(files.count) media file(s) found in: '\(url)'")
        }

        return files
    }
}
