//
//  ViewController.swift
//  Table Cells
//
//  Created by chenjianlong on 2017/12/2.
//  Copyright © 2017年 MyCompany. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource {
    let cellTableIdentifier = "CellTableIdentifier"
    @IBOutlet var tableView: UITableView!
    let computers = [
        ["Name": "MacBook Air", "Color": "Silver"],
        ["Name": "MacBook Pro", "Color": "Silver"],
        ["Name": "iMac", "Color": "Silver"],
        ["Name": "Mac Mini", "Color": "Silver"],
        ["Name": "Mac Pro", "Color": "Silver"]
    ]
    
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.register(NameAndColorCell.self, forCellReuseIdentifier: cellTableIdentifier)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    // MARK:-
    // MARK: Table View Data Source Methods
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return computers.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: cellTableIdentifier, for: indexPath) as! NameAndColorCell
        let rowData = computers[indexPath.row]
        cell.name = rowData["Name"]!
        cell.color = rowData["Color"]!
        
        return cell
    }
}

