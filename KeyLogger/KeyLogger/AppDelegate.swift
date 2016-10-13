//
//  AppDelegate.swift
//  KeyLogger
//
//  Created by stamefusa on 2016/09/22.
//  Copyright (c) 2016年 stamefusa. All rights reserved.
//

import Cocoa
import AppKit
import Foundation

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    @IBOutlet weak var window: NSWindow!

    func applicationDidFinishLaunching(aNotification: NSNotification) {
        // Insert code here to initialize your application
        print("Hello!")
        NSEvent.addGlobalMonitorForEventsMatchingMask(NSEventMask.MouseMovedMask, handler: self.mouseHandler)
        NSEvent.addGlobalMonitorForEventsMatchingMask(NSEventMask.KeyDownMask, handler: self.keyHandler)
    }

    func applicationWillTerminate(aNotification: NSNotification) {
        // Insert code here to tear down your application
    }

    func mouseHandler(event: NSEvent!)
    {
        print(NSDate())
        println("mouse moved!")
     
        let random_num = arc4random_uniform(300)
        print(random_num)
        if (random_num < 2) {
            println("success")
            let task = NSTask()
            task.launchPath = "/usr/bin/python"
            task.arguments = ["/Users/stamefusa/Dropbox/Public/dev/centerpc/mouse.py"]
            task.launch()
            task.waitUntilExit()
        }
    }
    
    func keyHandler(event: NSEvent!)
    {
        print(NSDate())
        println("key pressed")
        
        let random_num = arc4random_uniform(50)
        print(random_num)
        if (random_num < 2) {
            println("success")
            let task = NSTask()
            task.launchPath = "/usr/bin/python"
            task.arguments = ["/Users/stamefusa/Dropbox/Public/dev/centerpc/key.py"]
            task.launch()
            task.waitUntilExit()
        }
    }

}

