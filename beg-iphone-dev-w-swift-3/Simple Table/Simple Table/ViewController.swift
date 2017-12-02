//
//  ViewController.swift
//  Simple Table
//
//  Created by chenjianlong on 2017/12/2.
//  Copyright © 2017年 MyCompany. All rights reserved.
//

import UIKit

class ViewController: UIViewController,
            UITableViewDataSource, UITableViewDelegate {
    private let dwarves = [
        "Sleepy", "Sneezy", "Bashful", "Happy",
        "Doc", "Grumpy", "Dopey",
        "Thorin", "Dorin", "Nori", "Ori",
        "Balin", "Dwalin", "Fili", "Kili",
        "Oin", "Gloin", "Bifur", "Bofur",
        "Bombur"
    ]
    let simpleTableIdentifier = "SimpleTableIdentifier"

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK:-
    // MARK: Table View Data Source Methods
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return dwarves.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: simpleTableIdentifier)
        if (cell == nil) {
            cell = UITableViewCell(style: UITableViewCellStyle.default, reuseIdentifier: simpleTableIdentifier)
        }
        
        let image = UIImage(named: "star")
        cell?.imageView?.image = image
        let highlightedImage = UIImage(named: "star2")
        cell?.imageView?.highlightedImage = highlightedImage
        
        if indexPath.row < 7 {
            cell?.detailTextLabel?.text = "Mr Disney"
        } else {
            cell?.detailTextLabel?.text = "Mr Tokien"
        }
        
        cell?.textLabel?.text = dwarves[indexPath.row]
        cell?.textLabel?.font = UIFont.boldSystemFont(ofSize: 50)
        return cell!
    }
    
    // MARK:-
    // MARK: Table View delegate Methods
    func tableView(_ tableView: UITableView, indentationLevelForRowAt indexPath: IndexPath) -> Int {
        return indexPath.row % 4
    }
    
    func tableView(_ tableView: UITableView, willSelectRowAt indexPath: IndexPath) -> IndexPath? {
        if indexPath.row == 0 {
            return nil
        } else if (indexPath.row % 2 == 0) {
            return IndexPath(row: indexPath.row + 1, section: indexPath.section)
        } else {
            return indexPath
        }
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let rowValue = dwarves[indexPath.row]
        let message = "You selected \(rowValue)"
        let controller = UIAlertController(title: "Row Selected", message: message, preferredStyle: .alert)
        let action = UIAlertAction(title: "Yes I Did", style: .default, handler: nil)
        controller.addAction(action)
        present(controller, animated: true, completion: nil)
    }
}

