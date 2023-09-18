//
//  File.swift
//  Client
//
//  Created by Ben Shutt on 13/09/2023.
//  Copyright © 2023 Ben Shutt. All rights reserved.
//

import Foundation

struct File {

    var url: URL
    var fileType: FileType

    var data: Data {
        get throws {
            try Data(contentsOf: url)
        }
    }

    private init(url: URL, fileType: FileType) {
        self.url = url
        self.fileType = fileType
    }

    init?(url: URL) {
        let pathExtension = url.pathExtension.lowercased()
        let fileType = FileType.allCases.first { fileType in
            fileType.pathExtensions.contains(pathExtension)
        }
        guard let fileType else { return nil }
        self.init(url: url, fileType: fileType)
    }
}

// MARK: - File Type

extension File {

    enum FileType: String, CaseIterable {
        case jpeg
        case png
        case heic

        case mov
        case mp4
    }
}

private extension File.FileType {

    var pathExtensions: Set<String> {
        var set =  Set([rawValue])
        guard case .jpeg = self else { return set }
        set.insert("jpg")
        return set
    }
}
