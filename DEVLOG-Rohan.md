# Dev Log:

This document must be updated daily every time you finish a work session.

## Rohan Sen

### 2026-01-06 - Preliminary docs
- README filled out
- PROPOSAL uploaded
- code dump from networking lab

### 2026-01-06 HW - Preliminary docs
- adjustments to code from networking lab to work
- integration of a username system
- new files for shared memory stuff

### 2026-01-07 - Planning
- Adjusted to use Select
- researched gtk

### 2026-01-07 HW - GTK Research
- started creating GTK skeleton


### 2026-01-08 - GTK UI
- Textbox implemetned, need to connect to rest of code

### 2026-01-08 HW - GTK Progress
- Figured out how to install GTK on linux (sudo apt install libgtk-4-dev) using a vm
- Started merging the client logic into the gtk, though will have to update properly with actual code from Matthew

### 2026-01-08 - GTK Progress
- Researched and worked on the activate function, which should bind to the textbox and send the message on enter
- still cant test on school computer
- cleaned up files

### 2026-01-11 - GTK Done-ish
- Overhauled the connect code for the client to use all the weird GTK functions
- Fixed the client logic for updating the chat stream
- UI renders on linux, doesn't hang but is ugly

### 2026-01-12 (3am) - Working
- Can send and recieve messages between active clients in one big group chat.

### 2026-01-12 - Researching
- Figuring out how to do scrolling in the window.
- Works on school computers now.

### 2026-01-12 HW - Visual Improvements
- The window sized is now fixed, with a scroll view for the content
- Scrolling automatically moves to the bottom with each new message, like a real messenger app
- fixed makefile issue
- UI mostly there, awaiting username functionality

### 2026-01-13 - debug
- multi computer connection works now

### 2026-01-13 HW - UI
- allow the user to change servers through a text box

### 2026-01-14 - unsuccessful
- spent period attempting to fix the server switcher

### 2026-01-14 HW - server switcher & file save
- I think the fix for the server switcher was really simple, will test tomorrow
- added in the saving the chat to a file then sending it to whoever joins fresh to catch them up.

### 2026-01-15 - finalizing
- testing/sorting out the remainder of bugs with username connection
- debugged the enter username on join
- presently fixing the reset chat on disconnect, so the other chat doesn't show it

### 2026-01-15 HW - video
- polishing for the save to file system were needed so the chain of messages was clean (no excess newlines)
- bug fixing for presentation, had to fix issues where the usernames were stored after disconnect improperly
- added signal handling to safely shut server and let users know