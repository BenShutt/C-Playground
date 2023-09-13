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

    var data: Data { // TODO
        switch imageType {
        case .jpeg: return Data()
        case .png: return Data()
        case .heic: return Data()
        }
    }

    private init(url: URL, imageType: ImageType) {
        self.url = url
        self.imageType = imageType
    }

    init?(url: URL) {
        let pathExtension = url.pathExtension.lowercased()
        let imageType = ImageType.allCases.first { $0.rawValue == pathExtension }
        guard let imageType else { return nil }
        self.init(url: url, imageType: imageType)
    }
}
