//
//  ImageDirectory.swift
//  Client
//
//  Created by Ben Shutt on 13/09/2023.
//  Copyright © 2023 Ben Shutt. All rights reserved.
//

import Foundation

/// Encapsulate the logic of the image directory
struct ImageDirectory {

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

    /// Get the image files printing when a file is not a valid image
    /// - Returns: Valid image files
    func validate() throws -> [ImageFile] {
        let imageFiles = try forEach { url in
            let imageFile = ImageFile(url: url)
            if imageFile == nil {
                print("Unsupported image URL: '\(url)'")
            }
            return imageFile
        }

        if imageFiles.isEmpty {
            print("No images found in: '\(url)'")
        } else {
            print("\(imageFiles.count) image file(s) found in: '\(url)'")
        }

        return imageFiles
    }
}
