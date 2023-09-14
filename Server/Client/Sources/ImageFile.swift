//
//  ImageFile.swift
//  Client
//
//  Created by Ben Shutt on 13/09/2023.
//  Copyright © 2023 Ben Shutt. All rights reserved.
//

import Foundation
import AppKit

struct ImageFile {

    enum ImageType: String, CaseIterable {
        case jpeg
        case png
        case heic
    }

    var url: URL
    var imageType: ImageType

    var data: Data {
        get throws {
            try Data(contentsOf: url)
        }
    }

    private init(url: URL, imageType: ImageType) {
        self.url = url
        self.imageType = imageType
    }

    init?(url: URL) {
        let pathExtension = url.pathExtension.lowercased()
        let imageType = ImageType.allCases.first { imageType in
            imageType.pathExtensions.contains(pathExtension)
        }
        guard let imageType else { return nil }
        self.init(url: url, imageType: imageType)
    }
}

extension ImageFile.ImageType {

    var pathExtensions: Set<String> {
        var set =  Set([rawValue])
        guard case .jpeg = self else { return set }
        set.insert("jpg")
        return set
    }
}
