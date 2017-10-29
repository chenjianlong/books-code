//
//  ViewController.swift
//  Button Fun
//
//  Created by chenjianlong on 2017/10/29.
//  Copyright © 2017年 MyCompany. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var statusLabel: UILabel!
    @IBAction func buttonPressed(_ sender: UIButton) {
        let title = sender.title(for: .selected)
        let text = "\(title ?? "unknown") button pressed"
        let styledText = NSMutableAttributedString(string: text)
        let attributes = [
            NSAttributedStringKey.font: UIFont.boldSystemFont(ofSize: statusLabel.font.pointSize)
        ]
        let nameRange = (text as NSString).range(of: title!)
        styledText.setAttributes(attributes, range: nameRange)
        statusLabel.attributedText = styledText
    }
}

