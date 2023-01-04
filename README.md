# Context Menu Hash Generator 

A simple utility that allows the user to generate the xxHash of a selected file
in the Finder by right clicking and selecting the Quick Action. The generated checksum
is copied to the clipboard for use by the user. 

## Installing
An installer package has been created for arm64 and can be downloaded in the releases section.
Additional installers will be made available in due course. 

Once installed, it maybe necessary to enable the quick action. This is only needed
if the action cannot be seen when right clicking a file. The steps to do this are as follows:
- Right click any file
- Navigate down the context menu to Quick Actions 
- Within the submenu of Quick Actions select Customize
- Check the tick box for the xxHash service within the extensions preference pane

When right-clicking files from now on, the service should be visible. 

## Roadmap

- Refactor code into class based design, simplify and comment
- Write tests to ensure that the hash generation is operating correctly
- Check for memory leaks
- Add Md5 checksum 
- Add recursive checksum for supporting the right click of folders
- Add .MHL file generation 
- Add .MHL file verification